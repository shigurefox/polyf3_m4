#!/usr/bin/python
import sys
import re
import numpy
from math import log2


try: NN = int(sys.argv[1])
except: NN = 256
try: ftn_name = sys.argv[2]
except: ftn_name = 'polyf3_mul%d_packed_asm' % (NN)
assert(log2(NN / 32).is_integer())
LVL = int(log2(NN / 32))


def print_state():
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	input_size = int((NN * pow(1.5, LVL) // 32 * 2) * 4)
	print('  sub.w lr, r0, #%d' % (input_size * 2))
	#print('  sub.w lr, r0, #16')
	print('  vmov.w r0, s0')
	for it in range(3):
		for rid in range(12): print('  ldr.w %s, [lr], #4' % (tmp_reg[rid]))
		for rid in range(12): print('  str.w %s, [r0], #4' % (tmp_reg[rid]))
	print('  add.w sp, sp, #%d' % (input_size * 4))
	print('  pop.w {r4-r12, pc}')


def print_prologue():
	print('.p2align 2,,3')
	print('.syntax unified')
	print('.text')
	print('')


#to_be_optimized: use sp itself w/o the uncanny bug
def print_Karatsuba():
	input_size = int((NN * pow(1.5, LVL) // 32 * 2) * 4)
	print('.global %s' % (ftn_name))
	print('.type %s,' % (ftn_name), end=' ')
	print('%function')
	print('@ %dx%d %d-layer bit-sliced Karatsuba' % (NN, NN, LVL))
	print('@ void %s(uint32_t *h, uint32_t *c, uint32_t *f)' % (ftn_name))
	print('%s:' % (ftn_name))
	print('  push.w {r4-r12, lr}')
	if LVL:
		print('  vmov.w s0, r0')
		print('  sub.w sp, sp, #%d' % (input_size * 4))
		print('  mov.w r0, sp')
		copy_input_coefs('f')
		extend_input_coefs('f')
		copy_input_coefs('c')
		extend_input_coefs('c')
	polyf3_mul32_packed()
	#print_state()
	if LVL:
		compose_output_coefs()
		copy_output_coefs()
		print('  add.w sp, sp, #%d' % (input_size * 4))
	print('  pop.w {r4-r12, pc}')


#to_be_optimized: 'sub.w sp, sp, #(input_size * 6)' merged to one str
def copy_input_coefs(arr_name):
	source_addr = 'r1' if arr_name == 'c' else 'r2'
	tmp_reg = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	if arr_name == 'c': tmp_reg = ['r2'] + tmp_reg
	step_total = int(NN // 32 * 2)
	if step_total < (len(tmp_reg) + 1) * 2:
		tmp_reg.append('lr')
		step_tail = step_total % len(tmp_reg)
		if step_tail < step_total:
			print('  ldm.w %s!, {%s-%s, lr}' % (source_addr, tmp_reg[0], tmp_reg[-2]))
			print('  stm.w r0!, {%s-%s, lr}' % (tmp_reg[0], tmp_reg[-2]))
	else:
		step_tail = step_total % len(tmp_reg)
		print('  add.w lr, r0, #%d' % ((step_total - step_tail) * 4))
		print('%s_copy_input_%s_body:' % (ftn_name, arr_name))
		print('  ldm.w %s!, {%s-%s}' % (source_addr, tmp_reg[0], tmp_reg[-1]))
		print('  stm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
		print('  cmp.w r0, lr')
		print('  bne.w %s_copy_input_%s_body' % (ftn_name, arr_name))
	if step_tail:
		print('  ldm.w %s!, {%s-%s}' % (source_addr, tmp_reg[0], tmp_reg[step_tail - 1]))
		print('  stm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[step_tail - 1]))


def extend_input_coefs(arr_name):
	tmp_reg = ['r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	ext_bndry = NN // 32 * 2
	count_bndry = ext_bndry // 2
	for lvl_id in range(LVL):
		MOVE = 4 if lvl_id < (LVL - 1) else 2
		print('  sub.w r12, r0, #%d' % (ext_bndry * 4))
		if lvl_id:
			print('  mov.w r3, r0')
			print('%s_extend_input_%s_%d_body:' % (ftn_name, arr_name, lvl_id))
		if lvl_id < (LVL - 2):
			print('  add.w lr, r12, #%d' % (count_bndry * 4))
			print('%s_extend_input_%s_%d_unit:' % (ftn_name, arr_name, lvl_id))
		for rid in range(MOVE):
			print('  ldr.w %s, [r12, #%d]' % (tmp_reg[rid + MOVE], count_bndry * 4))
			print('  ldr.w %s, [r12], #4' % (tmp_reg[rid]))
		for rid in range(0, MOVE, 2):
#(C = A + B): idx_a0 = rid, idx_a1 = rid + 1, idx_b0 = rid + MOVE, idx_b1 = rid + MOVE + 1
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + 1], tmp_reg[rid + MOVE]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MOVE + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1]))
			print('  and.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + 1], tmp_reg[rid]))
			print('  orr.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
		print('  stm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[MOVE - 1]))
		if lvl_id < (LVL - 2):
			print('  cmp.w r12, lr')
			print('  bne.w %s_extend_input_%s_%d_unit' % (ftn_name, arr_name, lvl_id))
		if lvl_id:
			print('  add.w r12, r12, #%d' % (count_bndry * 4))
			print('  cmp.w r12, r3')
			print('  bne.w %s_extend_input_%s_%d_body' % (ftn_name, arr_name, lvl_id))
		ext_bndry += (ext_bndry // 2)
		count_bndry //= 2


def polyf3_mul32_packed():
	input_size = int(NN * pow(1.5, LVL) // 32 * 2 * 4)
	offset = input_size * 2
	ldr_regs = ['r3', 'r4', 'r5', 'r6']
	str_regs = ['r7', 'r8', 'r9', 'r10']
	tmp_regs = ['r11', 'r12']
	if LVL:
		print('  add.w lr, r0, #%d' % (offset))
		print('  sub.w r1, r0, #%d' % (input_size))
		print('  sub.w r2, r1, #%d' % (input_size))
		print('%s_mul32_body:' % (ftn_name))
	print('  ldr.w %s, [r1], #4' % (ldr_regs[0]))
	print('  ldr.w %s, [r1], #4' % (ldr_regs[1]))
	print('  ldr.w %s, [r2], #4' % (ldr_regs[2]))
	print('  ldr.w %s, [r2], #4' % (ldr_regs[3]))
	#BYYang's mul32
	print('  and.w %s, %s, %s, asr #31' % (str_regs[2], ldr_regs[0], ldr_regs[2]))
	print('  eor.w %s, %s, %s, asr #31' % (str_regs[3], ldr_regs[1], ldr_regs[3]))
	print('  and.w %s, %s, %s' % (str_regs[3], str_regs[3], str_regs[2]))
	print('  ror.w %s, %s, #31' % (ldr_regs[2], ldr_regs[2]))
	print('  ror.w %s, %s, #31' % (ldr_regs[3], ldr_regs[3]))
	print('  ubfx.w %s, %s, #31, #1' % (str_regs[0], str_regs[2]))
	print('  ubfx.w %s, %s, #31, #1' % (str_regs[1], str_regs[3]))
	print('  and.w %s, %s, %s, asr #31' % (tmp_regs[0], ldr_regs[0], ldr_regs[2]))
	print('  eor.w %s, %s, %s, asr #31' % (tmp_regs[1], ldr_regs[1], ldr_regs[3]))
	print('  and.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], tmp_regs[0]))
	print('  eor.w %s, %s, %s, lsl #1' % (str_regs[3], tmp_regs[0], str_regs[3]))
	print('  eor.w %s, %s, %s, lsl #1' % (tmp_regs[0], tmp_regs[0], str_regs[2]))
	print('  eor.w %s, %s, %s, lsl #1' % (str_regs[2], tmp_regs[1], str_regs[2]))
	print('  eor.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], str_regs[3]))
	print('  and.w %s, %s, %s' % (str_regs[3], str_regs[3], str_regs[2]))
	print('  orr.w %s, %s, %s' % (str_regs[2], tmp_regs[0], tmp_regs[1]))
	for i in range(30):
		print('  ror.w %s, %s, #31' % (ldr_regs[2], ldr_regs[2]))
		print('  ror.w %s, %s, #31' % (ldr_regs[3], ldr_regs[3]))
		print('  and.w %s, %s, %s, asr #31' % (tmp_regs[0], ldr_regs[0], ldr_regs[2]))
		print('  eor.w %s, %s, %s, asr #31' % (tmp_regs[1], ldr_regs[1], ldr_regs[3]))
		print('  and.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], tmp_regs[0]))
		print('  eors.w %s, %s, %s, lsl #1' % (str_regs[3], tmp_regs[0], str_regs[3]))
		print('  adc.w %s, %s, %s' % (str_regs[1], str_regs[1], str_regs[1]))
		print('  eors.w %s, %s, %s, lsl #1' % (tmp_regs[0], tmp_regs[0], str_regs[2]))
		print('  adc.w %s, %s, %s' % (str_regs[0], str_regs[0], str_regs[0]))
		print('  eor.w %s, %s, %s, lsl #1' % (str_regs[2], tmp_regs[1], str_regs[2]))
		print('  eor.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], str_regs[3]))
		print('  and.w %s, %s, %s' % (str_regs[3], str_regs[3], str_regs[2]))
		print('  orr.w %s, %s, %s' % (str_regs[2], tmp_regs[0], tmp_regs[1]))

	print('  str.w %s, [r0], #4' % (str_regs[2]))
	print('  str.w %s, [r0], #4' % (str_regs[3]))
	print('  str.w %s, [r0], #4' % (str_regs[0]))
	print('  str.w %s, [r0], #4' % (str_regs[1]))
	if LVL:
		print('  cmp.w r0, lr')
		print('  bne.w %s_mul32_body' % (ftn_name))


#to_be_optimized: tmp_reg always r1-r12 by using the trick in copy_input
def compose_output_coefs():
	input_size = int((NN * pow(1.5, LVL) // 32 * 2) * 4)
	tmp_reg = ['r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8']
	for fold in range(LVL):
		MOVE = 4 if fold else 2
		unit_num = pow(3, (LVL - 1) - fold)
		unit_size = 2 * pow(2, fold) * 4

		if fold == 0: offset = int(input_size * 2 - unit_size)
		else: offset = int(unit_size * 6 * unit_num - unit_size // 2 - unit_size) 
		print('  sub.w r0, r0, #%d' % (offset))

		if fold < (LVL - 1):
			print('  add.w r12, r0, #%d' % (unit_size * 4 * unit_num))
			print('%s_compose_output_%d_body:' % (ftn_name, fold))
		#op_tmp = op_accum + unit_size
		if fold > 1:
			print('  add.w lr, r0, #%d' % (unit_size))
			print('%s_compose_output_A_%d:' % (ftn_name, fold))
		for rid in range(MOVE):
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], rid * 4))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid + MOVE], unit_size + rid * 4))
		for rid in range(0, MOVE, 2):
#(C = A - B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid, idx_b1 = rid + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE + 1], tmp_reg[rid]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + MOVE], tmp_reg[rid + 1]))
			print('  and.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid], tmp_reg[rid + 1]))
			print('  orr.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
			#print('  sub.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MAX_MOVE], tmp_reg[rid]))
		print('  stm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[MOVE - 1]))
		if fold > 1:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_A_%d' % (ftn_name, fold))
		#op_tmp2 = op_accum - unit_size
			print('  sub.w lr, lr, #%d' % (unit_size))
			print('%s_compose_output_B_%d:' % (ftn_name, fold))
		for rid in range(MOVE):
			print('  ldr.w %s, [r0, #-4]!' % (tmp_reg[rid + MOVE]))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size * 2))
		for rid in range(0, MOVE, 2):
#(C = A - B): idx_a0 = rid + 1, idx_a1 = rid, idx_b0 = rid + MOVE + 1, idx_b1 = rid + MOVE
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + 1], tmp_reg[rid + MOVE + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid], tmp_reg[rid + MOVE + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MOVE]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + 1], tmp_reg[rid + MOVE]))
			print('  orr.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + 1], tmp_reg[rid]))
			print('  and.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE]))
			#print('  sub.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MAX_MOVE]))
		for rid in range(MOVE): print('  str.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size + 4 * (MOVE - 1 - rid)))
		if fold > 1:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_B_%d' % (ftn_name, fold))
		#op_accum = op_tmp2 - unit_size
		#op_tmp = op_accum - unit_size
			print('  sub.w lr, lr, #%d' % (unit_size))
			print('%s_compose_output_C_%d:' % (ftn_name, fold))
		for rid in range(MOVE):
			print('  ldr.w %s, [r0, #-4]!' % (tmp_reg[rid + MOVE]))
			print('  ldr.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size))
		for rid in range(0, MOVE, 2):
#(C = A + B): idx_a0 = rid + 1, idx_a1 = rid, idx_b0 = rid + MOVE + 1, idx_b1 = rid + MOVE
#  eor.w a1, a1, b0 #a1^b0
#  eor.w b0, a0, b0 #a0^b0
#  eor.w a0, a0, b1 #a0^b1
#  eor.w b1, a1, b1 #a1^b0^b1
#  and.w RH, a0, a1 #c1 = (a1^b0) & (a0^b1)
#  orr.w RL, b0, b1 #c0 = (a0^b0) | (a1^b0^b1)
			print('  eor.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MOVE + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1], tmp_reg[rid + MOVE + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + 1], tmp_reg[rid + MOVE]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid], tmp_reg[rid + MOVE]))
			print('  and.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + 1], tmp_reg[rid]))
			print('  orr.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE]))
			#print('  add.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid], tmp_reg[rid + MAX_MOVE]))
		for rid in range(MOVE): print('  str.w %s, [r0, #%d]' % (tmp_reg[rid], unit_size + 4 * (MOVE - 1 - rid)))
		if fold > 1:
			print('  cmp.w r0, lr')
			print('  bne.w %s_compose_output_C_%d' % (ftn_name, fold))
		print('  add.w r0, r0, #%d' % (unit_size * 5))
		if fold < (LVL - 1):
			print('  cmp.w r0, r12')
			print('  bne.w %s_compose_output_%d_body' % (ftn_name, fold))
				
		#cSfS = h_ext + unit_num * unit_size * 4
		MOVE = 4
		print('  sub.w r12, r0, #%d' % (unit_size * 4 * unit_num))
		print('  sub.w lr, r0, #%d' % (unit_size))
		if fold < (LVL - 1):
			print('%s_compose_output_%d_jump:' % (ftn_name, fold))
		if fold:
			print('  add.w r11, r12, #%d' % (unit_size * 2))
			print('%s_compose_output_D_%d:' % (ftn_name, fold))
		print('  ldm.w r12, {%s-%s}' % (tmp_reg[0], tmp_reg[MOVE - 1]))
		print('  ldm.w lr!, {%s-%s}' % (tmp_reg[MOVE], tmp_reg[-1]))
		for rid in range(0, MOVE, 2):
#(C = A - B): idx_a0 = rid + MOVE, idx_a1 = rid + MOVE + 1, idx_b0 = rid, idx_b1 = rid + 1
#  eor.w a0, a0, b0 #a0^b0
#  eor.w b0, a1, b0 #a1^b0
#  eor.w a1, a1, b1 #a1^b1
#  eor.w b1, a0, b1 #a0^b0^b1
#  orr.w RL, a0, a1 #c0 = (a0^b0) | (a1^b1)
#  and.w RH, b0, b1 #c1 = (a1^b0) & (a0^b0^b1)
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE], tmp_reg[rid + MOVE], tmp_reg[rid]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE + 1], tmp_reg[rid]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + MOVE + 1], tmp_reg[rid + MOVE + 1], tmp_reg[rid + 1]))
			print('  eor.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid + MOVE], tmp_reg[rid + 1]))
			print('  and.w %s, %s, %s' % (tmp_reg[rid + 1], tmp_reg[rid], tmp_reg[rid + 1]))
			print('  orr.w %s, %s, %s' % (tmp_reg[rid], tmp_reg[rid + MOVE], tmp_reg[rid + MOVE + 1]))
			#print('  sub.w %s, %s, %s' % (tmp_jump_reg[rid], tmp_jump_reg[rid + MAX_MOVE], tmp_jump_reg[rid]))
		print('  stm.w r12!, {%s-%s}' % (tmp_reg[0], tmp_reg[MOVE - 1]))
		if fold:
			print('  cmp.w r12, r11')
			print('  bne.w %s_compose_output_D_%d' % (ftn_name, fold))
		if fold < (LVL - 1):
			print('  add.w r12, r12, #%d' % (unit_size * 2))
			print('  cmp.w r12, r0')
			print('  bne.w %s_compose_output_%d_jump' % (ftn_name, fold))
		if fold == (LVL - 1): print('  sub.w r0, r12, #%d' % (NN // 32 * 3 * 4))
		else: print('  sub.w r0, r12, #%d' % (unit_size * 2))


def copy_output_coefs():
	tmp_reg = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12']
	print('  vmov.w lr, s0')

	step_total = NN // 32 * 2 * 2
	if step_total < (len(tmp_reg) + 1) * 2:
		tmp_reg = ['r1'] + tmp_reg
		step_tail = step_total % len(tmp_reg)
		if step_tail < step_total:
			print('  ldm.w r0!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
			print('  stm.w lr!, {%s-%s}' % (tmp_reg[0], tmp_reg[-1]))
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
