#!/usr/bin/python
import sys
import re
import numpy


try: ftn_name = sys.argv[1]
except: ftn_name = 'polyf3_mul768_packed_asm'
try: smaller_mult = sys.argv[2]
except: smaller_mult = 'polyf3_mul256_packed_asm'


#assert intIn is an integer
def is_constant(intIn):
	bin_str = numpy.binary_repr(intIn, width=32)
	if len(bin_str.strip('0')) <= 8: return True
	if (bin_str[0 : 8] == bin_str[16 : 24]) and (bin_str[8 : 16] == bin_str[24 : 32]):
		if (bin_str[0 : 8] == '0' * 8): return True
		if (bin_str[8 : 16] == '0' * 8): return True
		if (bin_str[0 : 8] == bin_str[8 : 16]): return True
	return False


def print_state():
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	input_size = int((768 // 32 * 2 * 2) * 4)
	print('  sub.w lr, r0, #%d' % (input_size * 1))
	#print('  mov.w lr, r0')
	print('  vmov.w r0, s0')
	for it in range(16):
		for rid in range(12): print('  ldr.w %s, [lr], #4' % (tmp_reg[rid]))
		for rid in range(12): print('  str.w %s, [r0], #4' % (tmp_reg[rid]))
	print('  add.w sp, sp, #%d' % (input_size * 3))
	print('  pop.w {r4-r12, pc}')


def print_prologue():
	print('.p2align 2,,3')
	print('.syntax unified')
	print('.text')
	print('')


#to_be_optimized: use sp itself w/o the uncanny bug
def print_Karatsuba():
	input_size = int((768 // 32 * 2 * 2) * 4)
	print('.global %s' % (ftn_name))
	print('.type %s,' % (ftn_name), end=' ')
	print('%function')
	print('@ 768x768 bit-sliced three-way Karatsuba')
	print('@ void %s(uint32_t *h, uint32_t *c, uint32_t *f)' % (ftn_name))
	print('%s:' % (ftn_name))
	print('  push.w {r4-r12, lr}')
	print('  vmov.w s0, r0')
	print('  sub.w sp, sp, #%d' % (input_size * 3))
	print('  mov.w r0, sp')

	extend_input_coefs('f')
	extend_input_coefs('c')
	print('  vmov.w r4, s0')
	print('  mov.w r5, r0')
	print('  mov.w r6, r1')
	print('  mov.w r7, r2')
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 1))
	print('  add.w r1, r6, %d' % (input_size // 6 * 1))
	print('  add.w r2, r7, %d' % (input_size // 6 * 1))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 2))
	print('  add.w r1, r6, %d' % (input_size // 6 * 2))
	print('  add.w r2, r7, %d' % (input_size // 6 * 2))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 3))
	print('  sub.w r1, r5, %d' % (input_size // 2 // 3 * 3))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 2 // 3 * 3))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 4))
	print('  sub.w r1, r5, %d' % (input_size // 2 // 3 * 2))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 2 // 3 * 2))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 5))
	print('  sub.w r1, r5, %d' % (input_size // 2 // 3 * 1))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 2 // 3 * 1))
	print('  bl.w %s' % (smaller_mult))
	print('  vmov.w s0, r4')
	print('  mov.w r0, r5')
	compose_output_coefs()
	copy_output_coefs()

	print('  add.w sp, sp, #%d' % (input_size * 3))
	print('  pop.w {r4-r12, pc}')


def extend_input_coefs(arr_name):
	source_addr = 'r1' if arr_name == 'c' else 'r2'
	tmp_reg = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	count_bndry = (768 // 32 * 2) // 3
	MOVE = 2
	print('  add.w lr, r0, #%d' % (count_bndry * 4))
	print('%s_extend_input_%s_unit:' % (ftn_name, arr_name))
	for rid in range(MOVE):
		print('  ldr.w %s, [%s, #%d]' % (tmp_reg[rid + MOVE * 2], source_addr, count_bndry * 4 * 2))
		print('  ldr.w %s, [%s, #%d]' % (tmp_reg[rid + MOVE], source_addr, count_bndry * 4))
		print('  ldr.w %s, [%s], #4' % (tmp_reg[rid], source_addr))
	for rid in range(0, MOVE, 2):
#(C = A + B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid + MOVE * 2, idx_b1 = rid + MOVE * 2 + 1
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 2 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 2 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3 + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 2], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2], tmp_reg[rid + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2 + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))
	for rid in range(MOVE):
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], count_bndry * 4 * 2))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], count_bndry * 4))
		print('  str.w %s, [r0], #4' % (tmp_reg[rid + MOVE]))
	print('  cmp.w r0, lr')
	print('  bne.w %s_extend_input_%s_unit' % (ftn_name, arr_name))
	print('  sub.w %s, %s, #%d' % (source_addr, source_addr, count_bndry * 4))
	print('  add.w r0, r0, #%d' % (count_bndry * 4 * 2))


#to_be_optimized: tmp_reg always r1-r12 by using the trick in copy_input
def compose_output_coefs():
	input_size = int((768 // 32 * 2 * 2) * 4)
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	MOVE = 2
	print('  add.w lr, r0, #%d' % (input_size * 2 // 6))
	print('%s_compose_output_A:' % (ftn_name))
	for rid in range(MOVE):
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 5], input_size * 2 // 6 * 5))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], input_size * 2 // 6 * 3))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], input_size * 2 // 6 * 2))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 1], input_size * 2 // 6 * 1))
		print('  ldr.w %s, [r0], #4' % (tmp_reg[rid]))
	for rid in range(0, MOVE, 2):
#(C = A - B): idx_a0 = rid + MOVE * 3, idx_a1 = rid + MOVE * 3 + 1, idx_b0 = rid, idx_b1 = rid + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 3], tmp_reg[rid + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

#(C = A - B): idx_a0 = rid + MOVE * 3, idx_a1 = rid + MOVE * 3 + 1, idx_b0 = rid + MOVE, idx_b1 = rid +MOVE + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

#(C = A - B): idx_a0 = rid + MOVE * 5, idx_a1 = rid + MOVE * 5 + 1, idx_b0 = rid + MOVE, idx_b1 = rid +MOVE + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

#(C = A - B): idx_a0 = rid + MOVE * 5, idx_a1 = rid + MOVE * 5 + 1, idx_b0 = rid + MOVE * 2, idx_b1 = rid +MOVE * 2 + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 2 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 2 + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

#(C = A - B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid + MOVE * 2, idx_b1 = rid +MOVE * 2 + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 2]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 2 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 2 + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))

#(C = A - B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid, idx_b1 = rid + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE + 1], tmp_reg[rid]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE], tmp_reg[rid + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))
	for rid in range(MOVE):
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 4], input_size * 2 // 6 * 4 - (MOVE - rid) * 4))
	for rid in range(0, MOVE, 2):
#(C = A + B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid + MOVE * 4, idx_b1 = rid + MOVE * 4 + 1
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 4]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 4]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 4 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 4 + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 4 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 4], tmp_reg[rid + MOVE * 4 + 1]))
	for rid in range(MOVE):
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 5], input_size * 2 // 6 * 5 - (MOVE - rid) * 4))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], input_size * 2 // 6 * 3 - (MOVE - rid) * 4))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 1], input_size * 2 // 6 * 1 - (MOVE - rid) * 4))
	print('  cmp.w r0, lr')
	print('  bne.w %s_compose_output_A' % (ftn_name))
	print('  add.w lr, r0, #%d' % (input_size // 6))
	print('  sub.w r0, r0, #%d' % (input_size // 6))
	print('%s_compose_output_B:' % (ftn_name))
	for rid in range(MOVE):
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 5], input_size * 2 // 6 * 5 - input_size // 6))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], input_size * 2 // 6 * 3 - input_size // 6))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], input_size * 2 // 6 * 1))
		print('  ldr.w %s, [r0], #4' % (tmp_reg[rid + MOVE * 1]))
	for rid in range(0, MOVE, 2):
#(C = A + B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid + MOVE * 3, idx_b1 = rid + MOVE * 3 + 1
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 3]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 3]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 3 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3 + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE * 3 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3 + 1]))
#(C = A + B): idx_a0 = rid + MOVE * 2, idx_a1 = rid + MOVE * 2 + 1, idx_b0 = rid + MOVE * 5, idx_b1 = rid + MOVE * 5 + 1
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 5]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 5]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 5 + 1]))
		print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5 + 1], tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 5 + 1]))
		print('  and.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2 + 1], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2 + 1]))
		print('  orr.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5 + 1]))
	for rid in range(MOVE):
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], input_size * 2 // 6 * 1 - (MOVE - rid) * 4))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 1], -(MOVE - rid) * 4))
	print('  cmp.w r0, lr')
	print('  bne.w %s_compose_output_B' % (ftn_name))
	print('  sub.w r0, r0, #%d' % (input_size // 6 * 3))


def copy_output_coefs():
	tmp_reg = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	step_total = int(768 // 32 * 2 * 2)
	step_tail = step_total % len(tmp_reg)
	print('  vmov.w lr, s0')
	print('  add.w r1, r0, #%d' % ((step_total - step_tail) * 4))
	print('%s_copy_output_body:' % (ftn_name))
	print('  ldm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
	print('  stm.w lr!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
	print('  cmp.w r0, r1')
	print('  bne.w %s_copy_output_body' % (ftn_name))
	if step_tail:
		for rid in range(step_tail): print('  ldr.w %s, [r0], #4' % (tmp_reg[rid]))
		for rid in range(step_tail): print('  str.w %s, [lr], #4' % (tmp_reg[rid]))


print_prologue()
print_Karatsuba()
