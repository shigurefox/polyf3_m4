#!/usr/bin/python
import sys
import re
import numpy


try: ftn_name = sys.argv[1]
except: ftn_name = 'Karatsuba_mod3_mult_asm'
try: smaller_mult = sys.argv[2]
except: smaller_mult = 'gf_polymul_256x256_mod3'


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
	input_size = int(768 * 2)
	print('  vmov.w lr, s0')
	#print('  mov.w r1, r0')
	#print('  sub.w r0, r0, #%d' % (input_size))
	print('  sub.w r0, r0, #%d' % (input_size * 2 // 6))
	print('  add.w r1, r0, #%d' % (input_size * 2))
	print('%s_print_state_body:' % (ftn_name))
	print('  ldm.w r0!, {r2-r9}')
	print('  stm.w lr!, {r2-r9}')
	print('  cmp.w r0, r1')
	print('  bne.w %s_print_state_body' % (ftn_name))
	print('  add.w sp, sp, #%d' % (input_size * 3))
	print('  pop.w {r4-r12, pc}')


def print_prologue():
	print('.p2align 2,,3')
	print('.syntax unified')
	print('.text')
	print('')


#to_be_optimized: use sp itself w/o the uncanny bug
def print_Karatsuba():
	input_size = int(768 * 2) #768-byte (0, 1, 2) + (0+1, 0+2, 1+2)
	print('.global %s' % (ftn_name))
	print('.type %s,' % (ftn_name), end=' ')
	print('%function')
	print('@ 768x768 mod-3 three-way Karatsuba')
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
	print('  sub.w r1, r5, %d' % (input_size // 6 * 3))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 6 * 3))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 4))
	print('  sub.w r1, r5, %d' % (input_size // 6 * 2))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 6 * 2))
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r0, r5, %d' % (input_size // 3 * 5))
	print('  sub.w r1, r5, %d' % (input_size // 6 * 1))
	print('  sub.w r2, r5, %d' % (input_size // 2 + input_size // 6 * 1))
	print('  bl.w %s' % (smaller_mult))
	print('  vmov.w s0, r4')
	print('  mov.w r0, r5')
	compose_output_coefs()
	copy_output_coefs()

	print('  add.w sp, sp, #%d' % (input_size * 3))
	print('  pop.w {r4-r12, pc}')


#to be optimized: MOVE = 3 for arr_name='c' (r2 available)
def extend_input_coefs(arr_name):
	source_addr = 'r1' if arr_name == 'c' else 'r2'
	tmp_reg = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	count_bndry = (768 // 4) // 3
	MOVE = 2
	print('  mov.w r12, #0x03030303')
	print('  add.w lr, r0, #%d' % (count_bndry * 4))
	print('%s_extend_input_%s_unit:' % (ftn_name, arr_name))
	for rid in range(MOVE):
		print('  ldr.w %s, [%s, #%d]' % (tmp_reg[rid + MOVE * 2], source_addr, count_bndry * 4 * 2))
		print('  ldr.w %s, [%s, #%d]' % (tmp_reg[rid + MOVE], source_addr, count_bndry * 4))
		print('  ldr.w %s, [%s], #4' % (tmp_reg[rid], source_addr))
	for rid in range(MOVE):
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2], tmp_reg[rid]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))

		print('  usub8.w %s, %s, r12' % (tmp_reg[rid], tmp_reg[rid + MOVE * 3]))
		print('  sel.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid], tmp_reg[rid + MOVE * 3]))
		print('  usub8.w %s, %s, r12' % (tmp_reg[rid], tmp_reg[rid + MOVE * 2]))
		print('  sel.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid], tmp_reg[rid + MOVE * 2]))
		print('  usub8.w %s, %s, r12' % (tmp_reg[rid], tmp_reg[rid + MOVE]))
		print('  sel.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid], tmp_reg[rid + MOVE]))
	for rid in range(MOVE):
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], count_bndry * 4 * 2))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], count_bndry * 4))
		print('  str.w %s, [r0], #4' % (tmp_reg[rid + MOVE]))
	print('  cmp.w r0, lr')
	print('  bne.w %s_extend_input_%s_unit' % (ftn_name, arr_name))
	print('  sub.w %s, %s, #%d' % (source_addr, source_addr, count_bndry * 4))
	print('  add.w r0, r0, #%d' % (count_bndry * 4 * 2))


#to_be_optimized: optimal mod-3 timings
def compose_output_coefs():
	input_size = int(768 * 2)
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	MOVE = 2
	print('  mov.w r9, #0x03030303')
	print('  add.w lr, r0, #%d' % (input_size * 2 // 6))
	print('%s_compose_output_A:' % (ftn_name))
	for rid in range(MOVE):
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 5], input_size * 2 // 6 * 5))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 3], input_size * 2 // 6 * 3))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], input_size * 2 // 6 * 2))
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 1], input_size * 2 // 6 * 1))
		print('  ldr.w %s, [r0], #4' % (tmp_reg[rid]))
	for rid in range(MOVE):
		print('  usub8.w %s, r9, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2]))
		print('  usub8.w r10, r9, %s' % (tmp_reg[rid + MOVE]))
		print('  usub8.w %s, r9, %s' % (tmp_reg[rid], tmp_reg[rid]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3], tmp_reg[rid]))
		print('  add.w %s, %s, r10' % (tmp_reg[rid + MOVE * 3], tmp_reg[rid + MOVE * 3]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 2]))
		print('  add.w %s, %s, r10' % (tmp_reg[rid + MOVE * 5], tmp_reg[rid + MOVE * 5]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE * 2]))
	for rid in range(MOVE):
		print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], input_size * 2 // 6 * 4 - (MOVE - rid) * 4))
	for rid in range(MOVE):
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
		print('  and.w r10, %s, r9' % (tmp_reg[rid + MOVE]))
		print('  bic.w %s, %s, r9' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE]))
		print('  add.w %s, r10, %s, lsr #2' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE]))
		print('  usub8.w r10, %s, r9' % (tmp_reg[rid + MOVE]))
		print('  sel.w %s,r10, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE]))
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
	for rid in range(MOVE):
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 1], tmp_reg[rid + MOVE * 1], tmp_reg[rid + MOVE * 3]))
		print('  add.w %s, %s, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 5]))

		print('  and.w r10, %s, r9' % (tmp_reg[rid + MOVE * 1]))
		print('  bic.w %s, %s, r9' % (tmp_reg[rid + MOVE * 1], tmp_reg[rid + MOVE * 1]))
		print('  add.w %s, r10, %s, lsr #2' % (tmp_reg[rid + MOVE * 1], tmp_reg[rid + MOVE * 1]))
		print('  usub8.w r10, %s, r9' % (tmp_reg[rid + MOVE * 1]))
		print('  sel.w %s,r10, %s' % (tmp_reg[rid + MOVE * 1], tmp_reg[rid + MOVE * 1]))

		print('  and.w r10, %s, r9' % (tmp_reg[rid + MOVE * 2]))
		print('  bic.w %s, %s, r9' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2]))
		print('  add.w %s, r10, %s, lsr #2' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2]))
		print('  usub8.w r10, %s, r9' % (tmp_reg[rid + MOVE * 2]))
		print('  sel.w %s,r10, %s' % (tmp_reg[rid + MOVE * 2], tmp_reg[rid + MOVE * 2]))
	for rid in range(MOVE):
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 2], input_size * 2 // 6 * 1 - (MOVE - rid) * 4))
		print('  str.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE * 1], -(MOVE - rid) * 4))
	print('  cmp.w r0, lr')
	print('  bne.w %s_compose_output_B' % (ftn_name))
	print('  sub.w r0, r0, #%d' % (input_size // 6 * 3))


def copy_output_coefs():
	tmp_reg = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	step_total = int(768 * 2 // 4)
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
