#!/usr/bin/python
import sys
import re
import numpy
from math import log2


try: NN = int(sys.argv[1])
except: NN = 256
try: B = int(sys.argv[2])
except: B = 32
try: ftn_name = sys.argv[3]
except: ftn_name = 'Karatsuba_mod3_mult_asm'
try: smaller_mult = sys.argv[4]
except: smaller_mult = ('gf_polymul_%dx%d_mod3' % (B, B))
assert(NN > B)
assert(B % 4 == 0)
assert(log2(NN / B).is_integer())
LVL = int(log2(NN / B))


#assert intIn is an integer
def is_constant(intIn):
	bin_str = numpy.binary_repr(intIn, width=32)
	if len(bin_str.strip('0')) <= 8: return True
	if (bin_str[0 : 8] == bin_str[16 : 24]) and (bin_str[8 : 16] == bin_str[24 : 32]):
		if (bin_str[0 : 8] == '0' * 8): return True
		if (bin_str[8 : 16] == '0' * 8): return True
		if (bin_str[0 : 8] == bin_str[8 : 16]): return True
	return False


def print_prologue():
	print('.p2align 2,,3')
	print('.syntax unified')
	print('.text')
	print('')


#to_be_optimized: use sp itself w/o the uncanny bug
def print_Karatsuba():
	input_size = (NN * pow(1.5, LVL) // 4) * 4
	print('.global %s' % (ftn_name))
	print('.type %s,' % (ftn_name), end=' ')
	print('%function')
	print('@ %dx%d %d-layer mod-3 Karatsuba' % (NN, NN, LVL))
	print('@ void %s(uint8_t *h, uint8_t *c, uint8_t *f)' % (ftn_name))
	print('%s:' % (ftn_name))
	print('  push.w {r4-r12, lr}')

	print('  vmov.w s0, r0')
	offset = int(input_size * 4)
	if (offset < 4096) or is_constant(offset): print('  sub.w sp, sp, #%d' % (offset))
	else:
		print('  sub.w sp, sp, #%d' % (offset % 4096))
		print('  sub.w sp, sp, #%d' % (offset // 4096 * 4096))
	print('  mov.w r0, sp')
	copy_input_coefs('f')
	extend_input_coefs('f')
	copy_input_coefs('c')
	extend_input_coefs('c')
	umlal_mult()

	compose_output_coefs()
	copy_output_coefs()
	if (offset < 4096) or is_constant(offset): print('  add.w sp, sp, #%d' % (offset))
	else:
		print('  add.w sp, sp, #%d' % (offset % 4096))
		print('  add.w sp, sp, #%d' % (offset // 4096 * 4096))
	print('  pop.w {r4-r12, pc}')


#to_be_optimized: 'sub.w sp, sp, #(input_size * 4)' merged to one str
def copy_input_coefs(arr_name):
	source_addr = 'r1' if arr_name == 'c' else 'r2'
	tmp_reg = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	if arr_name == 'c': tmp_reg = ['r2'] + tmp_reg
	step_total = NN // 4
	if step_total < (len(tmp_reg) + 1) * 2:
		tmp_reg.append('lr')
		step_tail = step_total % len(tmp_reg)
		if step_tail < step_total:
			print('  ldm.w %s!, {%s-%s, lr}' % (source_addr, tmp_reg[0], tmp_reg[-2]))
			print('  stm.w r0!, {%s-%s, lr}' % (tmp_reg[0], tmp_reg[-2]))
		tmp_reg.pop()
	else:
		step_tail = step_total % len(tmp_reg)
		print('  add.w lr, r0, #%d' % ((step_total - step_tail) * 4))
		print('%s_copy_input_%s_body:' % (ftn_name, arr_name))
		print('  ldm.w %s!, {%s-%s}' % (source_addr, tmp_reg[0], tmp_reg[-1]))
		print('  stm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
		print('  cmp.w r0, lr')
		print('  bne.w %s_copy_input_%s_body' % (ftn_name, arr_name))
	if step_tail:
		for rid in range(step_tail): print('  ldr.w %s, [%s], #4' % (tmp_reg[rid], source_addr))
		for rid in range(step_tail): print('  str.w %s, [r0], #4' % (tmp_reg[rid]))


#to be optimized: more efficient bndry for NN = 4/8
def extend_input_coefs(arr_name):
	tmp_reg = ['r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	print('  mov.w r3, #0x03030303')
	ext_bndry = NN // 4
	count_bndry = ext_bndry // 2

	for lvl_id in range(LVL):
		offset = int(ext_bndry * 4)
		if (offset < 4096) or is_constant(offset): print('  sub.w r12, r0, #%d' % (offset))
		else:
			print('  sub.w r12, r0, #%d' % (offset % 2048))
			print('  sub.w r12, r12, #%d' % (offset // 2048 * 2048))
		if lvl_id:
			print('  mov.w r2, r0')
			print('%s_extend_input_%s_%d_body:' % (ftn_name, arr_name, lvl_id))
		if count_bndry > 4:
			print('  add.w lr, r12, #%d' % (count_bndry * 4))
			print('%s_extend_input_%s_%d_unit:' % (ftn_name, arr_name, lvl_id))

		MOVE = 3 if count_bndry == 6 else min(4, count_bndry)
		for rid in range(MOVE):
			print('  ldr.w %s, [r12, #%d]' % (tmp_reg[rid + MOVE], count_bndry * 4))
			if rid == (MOVE - 1) and count_bndry <= 4: print('  ldr.w %s, [r12], #%d' % (tmp_reg[rid], 4 + count_bndry * 4))
			else: print('  ldr.w %s, [r12], #4' % (tmp_reg[rid]))
		for rid in range(MOVE):
			print('  add.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MOVE]))
			print('  usub8.w %s, %s, r3' % (tmp_reg[rid + MOVE], tmp_reg[rid]))
			print('  sel.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE], tmp_reg[rid]))
		for rid in range(MOVE): print('  str.w %s, [r0], #4' % (tmp_reg[rid]))

		if count_bndry > 4:
			print('  cmp.w r12, lr')
			print('  bne.w %s_extend_input_%s_%d_unit' % (ftn_name, arr_name, lvl_id))
			if lvl_id: print('  add.w r12, r12, #%d' % (count_bndry * 4))
		if lvl_id:
			print('  cmp.w r12, r2')
			print('  bne.w %s_extend_input_%s_%d_body' % (ftn_name, arr_name, lvl_id))
		ext_bndry += (ext_bndry // 2)
		count_bndry //= 2


def umlal_mult():
	input_size = int((NN * pow(1.5, LVL) // 4) * 4)
	offset = int(input_size * 2)
	print('  vmov.w r4, s0')
	print('  mov.w r5, r0')
	if (input_size < 4096) or is_constant(input_size):
		print('  sub.w r6, r5, #%d' % (input_size))
		print('  sub.w r7, r6, #%d' % (input_size))
	else:
		print('  sub.w r6, r5, #%d' % (input_size % 1024))
		print('  sub.w r6, r6, #%d' % (input_size // 1024 * 1024))
		print('  sub.w r7, r6, #%d' % (input_size % 1024))
		print('  sub.w r7, r7, #%d' % (input_size // 1024 * 1024))
	if (offset < 4096) or is_constant(offset): print('  add.w r8, r5, #%d' % (offset))
	else:
		print('  add.w r8, r5, #%d' % (offset % 2048))
		print('  add.w r8, r8, #%d' % (offset // 2048 * 2048))

	print('%s_schoolbook_body:' % (ftn_name))
	print('  mov.w r1, r6')
	print('  mov.w r2, r7')
	print('  bl.w %s' % (smaller_mult))
	print('  add.w r5, r5, #%d' %(B * 2))
	print('  add.w r6, r6, #%d' %(B))
	print('  add.w r7, r7, #%d' %(B))
	print('  cmp.w r5, r8')
	print('  mov.w r0, r5')
	print('  bne.w %s_schoolbook_body' % (ftn_name))
	print('  vmov.w s0, r4')


#to_be_optimized: more efficient bndry for NN = 4/8
def compose_output_coefs():
	input_size = (NN * pow(1.5, LVL) // 4) * 4
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8']
	tmp_jump_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8']
	print('  mov.w r11, 0x03030303')
	for fold in range(LVL):
		unit_num = pow(3, (LVL - 1) - fold)
		unit_size = B * pow(2, fold)
		if fold == 0: offset = int(input_size * 2 - unit_size)
		else: offset = int(unit_size * 6 * unit_num - unit_size // 2) 
		if (offset < 4096) or is_constant(offset): print('  sub.w r0, r0, #%d' % (offset))
		else:
			print('  sub.w r0, r0, #%d' % (offset % 1024))
			print('  sub.w r0, r0, #%d' % (offset // 1024 * 1024))

		if fold < (LVL - 1):
			offset = unit_size * 4 * unit_num
			if (offset < 4096) or is_constant(offset): print('  add.w r12, r0, #%d' % (offset))
			else:
				print('  add.w r12, r0, #%d' % (offset % 4096))
				print('  add.w r12, r12, #%d' % (offset // 4096 * 4096))
			print('%s_compose_output_%d_body:' % (ftn_name, fold))

		MAX_MOVE = 3 if unit_size == 24 else min(4, unit_size // 4)
		if unit_size > 16:
			print('  add.w lr, r0, #%d' % (unit_size))
			print('%s_compose_output_A_%d:' % (ftn_name, fold))
		#op_tmp = op_accum + unit_size
		for rid in range(MAX_MOVE):
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], rid * 4))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MAX_MOVE], unit_size + rid * 4))
		for rid in range(MAX_MOVE):
			print('  sub.w %s, r11, %s' % (tmp_reg[rid], tmp_reg[rid]))
			print('  add.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MAX_MOVE], tmp_reg[rid])) #1-5
		for rid in range(MAX_MOVE): print('  str.w %s, [r0], #4' % (tmp_reg[rid]))
		if unit_size > 16:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_A_%d' % (ftn_name, fold))

		if unit_size > 16:
			print('  sub.w lr, lr, #%d' % (unit_size))
			print('%s_compose_output_B_%d:' % (ftn_name, fold))
		#op_tmp2 = op_accum - unit_size
		for rid in range(MAX_MOVE):
			print('  ldr.w %s, [r0, #-4]!' % (tmp_reg[rid + MAX_MOVE]))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size * 2))
		for rid in range(MAX_MOVE):
			print('  rsb.w %s, %s, r11, lsl #1' % (tmp_reg[rid + MAX_MOVE], tmp_reg[rid + MAX_MOVE]))
			print('  add.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MAX_MOVE])) #1-7
		for rid in range(MAX_MOVE): print('  str.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size + 4 * (MAX_MOVE - rid - 1)))
		if unit_size > 16:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_B_%d' % (ftn_name, fold))

		if unit_size > 16:
			print('  sub.w lr, lr, #%d' % (unit_size))
			print('%s_compose_output_C_%d:' % (ftn_name, fold))
		#op_accum = op_tmp2 - unit_size
		#op_tmp = op_accum - unit_size
		for rid in range(MAX_MOVE):
			print('  ldr.w %s, [r0, #-4]!' % (tmp_reg[rid + MAX_MOVE]))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size))
		for rid in range(MAX_MOVE):
			print('  add.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MAX_MOVE])) #1-7
		for rid in range(MAX_MOVE): print('  str.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size + 4 * (MAX_MOVE - rid - 1)))
		if unit_size > 16:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_C_%d' % (ftn_name, fold))
		print('  add.w r0, r0, #%d' % (unit_size * 5))
		if fold < (LVL - 1):
			print('  cmp.w r0, r12')
			print('  bne.w %s_compose_output_%d_body' % (ftn_name, fold))


		offset = int(unit_size * 4 * unit_num)
		if (offset < 4096) or is_constant(offset): print('  sub.w r12, r0, #%d' % (offset))
		else:
			print('  sub.w r12, r0, #%d' % (offset % 4096))
			print('  sub.w r12, r12, #%d' % (offset // 4096 * 4096))
		print('  sub.w lr, r0, #%d' % (unit_size))
		if fold < (LVL - 1): print('%s_compose_output_%d_jump:' % (ftn_name, fold))

		MAX_MOVE = 3 if unit_size == 12 else min(4, unit_size * 2 // 4)
		if unit_size > 8:
			print('  add.w r10, r12, #%d' % (unit_size * 2))
			print('%s_compose_output_D_%d:' % (ftn_name, fold))
		#cSfS = h_ext + unit_num * unit_size * 4
		for rid in range(MAX_MOVE): print('  ldr.w %s, [r12, #%d]' % (tmp_jump_reg[rid], rid * 4))
		for rid in range(MAX_MOVE): print('  ldr.w %s, [lr], #4' % (tmp_jump_reg[rid + MAX_MOVE]))
		for rid in range(MAX_MOVE):
			print('  rsb.w %s, %s, r11, lsl #2' % (tmp_jump_reg[rid], tmp_jump_reg[rid]))
			print('  add.w %s, %s, %s' % (tmp_jump_reg[rid], tmp_jump_reg[rid + MAX_MOVE], tmp_jump_reg[rid])) #5-13
			print('  and.w %s, %s, r11' % (tmp_reg[rid + MAX_MOVE], tmp_reg[rid]))
			print('  bic.w %s, %s, r11' % (tmp_reg[rid], tmp_reg[rid]))
			print('  add.w %s, %s, %s, lsr #2' % (tmp_reg[rid], tmp_reg[rid + MAX_MOVE], tmp_reg[rid]))
			print('  usub8.w %s, %s, r11' % (tmp_reg[rid + MAX_MOVE], tmp_reg[rid]))
			print('  sel.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MAX_MOVE], tmp_reg[rid]))
		for rid in range(MAX_MOVE):
			if (rid == MAX_MOVE - 1) and (unit_size <= 8): print('  str.w %s, [r12], #%d' % (tmp_jump_reg[rid], 4 + unit_size * 2))
			else: print('  str.w %s, [r12], #4' % (tmp_jump_reg[rid]))
		if unit_size > 8:
			print('  cmp.w r12, r10')
			print('  bne.w %s_compose_output_D_%d' % (ftn_name, fold))
			print('  add.w r12, r12, #%d' % (unit_size * 2))

		if fold < (LVL - 1):
			print('  cmp.w r12, r0')
			print('  bne.w %s_compose_output_%d_jump' % (ftn_name, fold))
		if fold == (LVL - 1): print('  sub.w r0, r12, #%d' % (unit_size * 2 + NN * 6 // 4))


def copy_output_coefs():
	tmp_reg = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	print('  vmov.w lr, s0')

	step_total = NN * 2 // 4
	if step_total < 2 * (len(tmp_reg) + 1):
		tmp_reg = ['r1'] + tmp_reg
		step_tail = step_total % len(tmp_reg)
		if step_tail < step_total:
			print('  ldm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
			print('  stm.w lr!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
		tmp_reg = tmp_reg[1 : ]
	else:
		step_tail = step_total % len(tmp_reg)
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
