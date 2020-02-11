#!/usr/bin/python
import sys
import re


try: NN = int(sys.argv[1])
except: NN = 768
assert(NN > 0)
assert(NN % 64 == 0)


def print_prologue():
	print('.p2align 2,,3')
	print('.syntax unified')
	print('.text')
	print('')


'''
def print_polyf3_pack():
	bndry = 2 * (NN // 32)
	mod3_regs = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8'] #de-comment it to unroll the loop
#	mod3_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8'] #comment it to unroll the loop
	trit_regs = ['r9', 'r10', 'r11', 'r12']
	bit_reg = 'lr'
	MAX_MOVE = len(mod3_regs) #3 + N + 4 + 1 <= 14
	print('.global polyf3_pack_asm')
	print('.type polyf3_pack_asm, %function')
	print('@ void polyf3_pack_asm(uint32_t* tritOut, uint32_t* mod3In)')
	print('polyf3_pack_asm:')
	print('  push.w {r4-r12, lr}')
#	print('  add.w r2, r0, #%d' % (bndry * 4)) #comment it to unroll the loop
#	print('unit_pack:') #comment it to unroll the loop
	for tmp_count in range(bndry // 2): #de-comment it to unroll the loop
#	for tmp_count in range(1): #comment it to unroll the loop
		for batch in range(0, 16, MAX_MOVE):
			MOVE = min(MAX_MOVE, 16 - batch)
			for it in range(MOVE):
				print('  ldr.w %s, [r1], #4' % (mod3_regs[it]))
			if batch == 0:
				print('  and.w %s, %s, #0x00000001' % (trit_regs[0], mod3_regs[0]))
				print('  and.w %s, %s, #0x00000002' % (trit_regs[1], mod3_regs[0]))
				print('  and.w %s, %s, #0x00010000' % (trit_regs[2], mod3_regs[0]))
				print('  and.w %s, %s, #0x00020000' % (trit_regs[3], mod3_regs[0]))
			begin_id = 0 if batch else 1
			for it in range(begin_id, MOVE):
				print('  and.w %s, %s, #0x00000001' % (bit_reg, mod3_regs[it]))
				print('  orr.w %s, %s, %s, ror #%d' % (trit_regs[0], trit_regs[0], bit_reg, (16 - batch - it) * 2))
				print('  and.w %s, %s, #0x00000002' % (bit_reg, mod3_regs[it]))
				print('  orr.w %s, %s, %s, ror #%d' % (trit_regs[1], trit_regs[1], bit_reg, (16 - batch - it) * 2))
				print('  and.w %s, %s, #0x00010000' % (bit_reg, mod3_regs[it]))
				print('  orr.w %s, %s, %s, ror #%d' % (trit_regs[2], trit_regs[2], bit_reg, (16 - batch - it) * 2))
				print('  and.w %s, %s, #0x00020000' % (bit_reg, mod3_regs[it]))
				print('  orr.w %s, %s, %s, ror #%d' % (trit_regs[3], trit_regs[3], bit_reg, (16 - batch - it) * 2))
		print('  ror.w %s, %s, #1' % (trit_regs[1], trit_regs[1]))
		print('  orr.w %s, %s, %s, ror #15' % (trit_regs[0], trit_regs[0], trit_regs[2]))
		print('  orr.w %s, %s, %s, ror #16' % (trit_regs[1], trit_regs[1], trit_regs[3]))
		print('  str.w %s, [r0], #4' % (trit_regs[0]))
		print('  str.w %s, [r0], #4' % (trit_regs[1]))
#	print('  cmp.w r0, r2') #comment it to unroll the loop
#	print('  bne.w unit_pack') #comment it to unroll the loop
	print('  pop.w {r4-r12, pc}')
'''


def print_polyf3_pack():
	bndry = 2 * (NN // 32)
#	mod3_regs = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	mod3_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	trit_regs = ['r12', 'lr']
#	tmp_regs = ['r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	tmp_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11']
	MAX_MOVE = len(mod3_regs) #3 + N + 2 <= 14
	print('.global polyf3_pack_asm')
	print('.type polyf3_pack_asm, %function')
	print('@ void polyf3_pack_asm(uint32_t* tritOut, uint32_t* mod3In)')
	print('polyf3_pack_asm:')
	print('  push.w {r4-r12, lr}')
	print('  add.w r2, r0, #%d' % (bndry * 4))
	print('unit_pack:')
#	for tmp_count in range(bndry // 2):
	for tmp_count in range(1):
		for batch in range(0, 16, MAX_MOVE):
			MOVE = min(MAX_MOVE, 16 - batch)
			for it in range(MOVE):
				print('  ldr.w %s, [r1], #4' % (mod3_regs[it]))
			for it in range(MOVE):
				print('  bfi.w %s, %s, #%d, #2' % (trit_regs[0], mod3_regs[it], (batch + it) * 2))
				print('  lsr.w %s, %s, #16' % (mod3_regs[it], mod3_regs[it]))
				print('  bfi.w %s, %s, #%d, #2' % (trit_regs[1], mod3_regs[it], (batch + it) * 2))
		print('  and.w %s, %s, #0xaaaaaaaa' % (tmp_regs[0], trit_regs[0]))
		print('  and.w %s, %s, #0x55555555' % (trit_regs[0], trit_regs[0]))
		print('  and.w %s, %s, #0x55555555' % (tmp_regs[1], trit_regs[1]))
		print('  and.w %s, %s, #0xaaaaaaaa' % (trit_regs[1], trit_regs[1]))
		print('  orr.w %s, %s, %s, lsl #1' % (trit_regs[0], trit_regs[0], tmp_regs[1]))
		print('  orr.w %s, %s, %s, lsr #1' % (trit_regs[1], trit_regs[1], tmp_regs[0]))
		print('  str.w %s, [r0], #4' % (trit_regs[0]))
		print('  str.w %s, [r0], #4' % (trit_regs[1]))
	print('  cmp.w r0, r2')
	print('  bne.w unit_pack')
	print('  pop.w {r4-r12, pc}\n')

'''
def print_polyf3_unpack():
	bndry = 2 * (NN // 32)
	trit_regs = ['r3', 'r4']
	mod3_regs = ['r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12', 'lr']
	MAX_MOVE = len(mod3_regs) - 2
	print('.global polyf3_unpack_asm')
	print('.type polyf3_unpack_asm, %function')
	print('@ void polyf3_unpack_asm(uint32_t* mod3Out, uint32_t* tritIn)')
	print('polyf3_unpack_asm:')
	print('  push.w {r4-r12, lr}')
	print('  add.w r2, r1, #%d' % (bndry * 4))
	print('unit_unpack:')
	print('  ldr.w %s, [r1], #4' % (trit_regs[0]))
	print('  ldr.w %s, [r1], #4' % (trit_regs[1]))
	for batch in range(0, 16, MAX_MOVE):
		MOVE = min(MAX_MOVE, 16 - batch)
		for it in range(MOVE):
			coef_id = (batch + it) * 2
			print('  sbfx.w %s, %s, #%d, #1' % (mod3_regs[it], trit_regs[1], coef_id))
			print('  and.w %s, %s, #0x%x' % (mod3_regs[it + 1], trit_regs[0], pow(2, coef_id)))
			if coef_id:
				print('  orr.w %s, %s, %s, lsr #%d' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1], coef_id))
			else:
				print('  orr.w %s, %s, %s' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1]))
			print('  sbfx.w %s, %s, #%d, #1' % (mod3_regs[it + 1], trit_regs[1], coef_id + 1))
			print('  and.w %s, %s, #0x%x' % (mod3_regs[it + 2], trit_regs[0], pow(2, coef_id + 1)))
			print('  orr.w %s, %s, %s, lsr #%d' % (mod3_regs[it + 1], mod3_regs[it + 1], mod3_regs[it + 2], coef_id + 1))
			print('  pkhbt.w %s, %s, %s, lsl #16' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1]))
		for it in range(MOVE):
			print('  str.w %s, [r0], #4' % (mod3_regs[it]))
	print('  cmp.w r1, r2')
	print('  bne.w unit_unpack')
	print('  pop.w {r4-r12, pc}\n')
'''

def print_polyf3_unpack():
	bndry = 2 * (NN // 32)
	trit_regs = ['r3', 'r4']
	mod3_regs = ['r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12', 'lr']
	MAX_MOVE = len(mod3_regs) - 2
	print('.global polyf3_unpack_asm')
	print('.type polyf3_unpack_asm, %function')
	print('@ void polyf3_unpack_asm(uint32_t* mod3Out, uint32_t* tritIn)')
	print('polyf3_unpack_asm:')
	print('  push {r4-r12, lr}')
	print('  add r2, r1, #%d' % (bndry * 4))
	print('unit_unpack:')
	print('  ldr %s, [r1], #4' % (trit_regs[0]))
	print('  ldr %s, [r1], #4' % (trit_regs[1]))
	for batch in range(0, 16, MAX_MOVE):
		MOVE = min(MAX_MOVE, 16 - batch)
		for it in range(MOVE):
			coef_id = (batch + it) * 2
			print('  sbfx %s, %s, #%d, #1' % (mod3_regs[it], trit_regs[1], coef_id))
			print('  and %s, %s, #0x%x' % (mod3_regs[it + 1], trit_regs[0], pow(2, coef_id)))
			if coef_id:
				print('  orr %s, %s, %s, lsr #%d' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1], coef_id))
			else:
				print('  orr %s, %s, %s' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1]))
			print('  sbfx %s, %s, #%d, #1' % (mod3_regs[it + 1], trit_regs[1], coef_id + 1))
			print('  and %s, %s, #0x%x' % (mod3_regs[it + 2], trit_regs[0], pow(2, coef_id + 1)))
			print('  orr %s, %s, %s, lsr #%d' % (mod3_regs[it + 1], mod3_regs[it + 1], mod3_regs[it + 2], coef_id + 1))
			print('  pkhbt %s, %s, %s, lsl #16' % (mod3_regs[it], mod3_regs[it], mod3_regs[it + 1]))
		for it in range(MOVE):
			print('  str %s, [r0], #4' % (mod3_regs[it]))
	print('  cmp r1, r2')
	print('  bne unit_unpack')
	print('  pop {r4-r12, pc}\n')

def print_polyf3_add_packed():
	bndry = 2 * (NN // 32)
	print('.global polyf3_add_packed_asm')
	print('.type polyf3_add_packed_asm, %function')
	print('@ void polyf3_add_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)')
	print('polyf3_add_packed_asm:')
	print('  push.w {r4-r12, lr}')
#	print('  add.w r3, r0, #%d' % (bndry * 4))
#	print('unit_add:')
	for tmp_count in range(bndry // 4):
		print('  ldr.w r4, [r1], #4')
		print('  ldr.w r5, [r1], #4')
		print('  ldr.w r6, [r2], #4')
		print('  ldr.w r7, [r2], #4')
		print('  ldr.w r8, [r1], #4')
		print('  ldr.w r9, [r1], #4')
		print('  ldr.w r10, [r2], #4')
		print('  ldr.w r11, [r2], #4')
		print('  eor.w r12, r5, r6')
		print('  eor.w r5, r4, r7')
		print('  and.w r5, r5, r12')
		print('  eor.w r12, r12, r7')
		print('  eor.w r4, r4, r6')
		print('  orr.w r4, r4, r12')
		print('  eor.w r12, r9, r10')
		print('  eor.w r9, r8, r11')
		print('  and.w r9, r9, r12')
		print('  eor.w r12, r12, r11')
		print('  eor.w r8, r8, r10')
		print('  orr.w r8, r8, r12')
		print('  str.w r4, [r0], #4')
		print('  str.w r5, [r0], #4')
		print('  str.w r8, [r0], #4')
		print('  str.w r9, [r0], #4')
#	print('  cmp.w r0, r3')
#	print('  bne.w unit_add')
	print('  pop.w {r4-r12, pc}\n')


def print_polyf3_sub_packed():
	bndry = 2 * (NN // 32)
	print('.global polyf3_sub_packed_asm')
	print('.type polyf3_sub_packed_asm, %function')
	print('@ void polyf3_sub_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)')
	print('polyf3_sub_packed_asm:')
	print('  push.w {r4-r12, lr}')
#	print('  add.w r3, r0, #%d' % (bndry * 4))
#	print('unit_sub:')
	for tmp_count in range(bndry // 4):
		print('  ldr.w r4, [r1], #4')
		print('  ldr.w r5, [r1], #4')
		print('  ldr.w r6, [r2], #4')
		print('  ldr.w r7, [r2], #4')
		print('  ldr.w r8, [r1], #4')
		print('  ldr.w r9, [r1], #4')
		print('  ldr.w r10, [r2], #4')
		print('  ldr.w r11, [r2], #4')
		print('  eor.w r12, r4, r6')
		print('  eor.w r4, r5, r7')
		print('  orr.w r4, r4, r12')
		print('  eor.w r12, r12, r7')
		print('  eor.w r5, r5, r6')
		print('  and.w r5, r5, r12')
		print('  eor.w r12, r8, r10')
		print('  eor.w r8, r9, r11')
		print('  orr.w r8, r8, r12')
		print('  eor.w r12, r12, r11')
		print('  eor.w r9, r9, r10')
		print('  and.w r9, r9, r12')
		print('  str.w r4, [r0], #4')
		print('  str.w r5, [r0], #4')
		print('  str.w r8, [r0], #4')
		print('  str.w r9, [r0], #4')
#	print('  cmp.w r0, r3')
#	print('  bne.w unit_sub')
	print('  pop.w {r4-r12, pc}\n')


def print_polyf3_mul_packed():
	bndry = 1 * 4
	ldr_regs = ['r3', 'r4', 'r5', 'r6']
	str_regs = ['r7', 'r8', 'r9', 'r10']
	tmp_regs = ['r11', 'r12', 'lr']
	print('.global polyf3_mul_packed_asm')
	print('.type polyf3_mul_packed_asm, %function')
	print('@ void polyf3_mul_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)')
	print('polyf3_mul_packed_asm:')
	print('  push.w {r4-r12, lr}')
	print('  add.w r3, r0, #%d' % (bndry * 4))
	print('  vmov.w s0, r3')
	print('unit_mul:')
	print('  ldr.w %s, [r1], #4' % (ldr_regs[0]))
	print('  ldr.w %s, [r1], #4' % (ldr_regs[1]))
	print('  ldr.w %s, [r2], #4' % (ldr_regs[2]))
	print('  ldr.w %s, [r2], #4' % (ldr_regs[3]))
	for coef_id in range(32):
		if coef_id:
			print('  sbfx.w %s, %s, #%d, #1' % (tmp_regs[0], ldr_regs[0], coef_id))
			print('  sbfx.w %s, %s, #%d, #1' % (tmp_regs[1], ldr_regs[1], coef_id))
			print('  and.w %s, %s, %s' % (tmp_regs[0], tmp_regs[0], ldr_regs[2]))
			print('  eor.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], ldr_regs[3]))
			print('  and.w %s, %s, %s' % (tmp_regs[1], tmp_regs[1], tmp_regs[0]))
			print('  eor.w %s, %s, %s, lsr #1' % (tmp_regs[2], tmp_regs[0], str_regs[1]))
			print('  eor.w %s, %s, %s, lsr #1' % (str_regs[1], tmp_regs[1], str_regs[0]))
			print('  and.w %s, %s, %s' % (str_regs[1], str_regs[1], tmp_regs[2]))
			print('  eor.w %s, %s, %s' % (tmp_regs[2], tmp_regs[2], tmp_regs[1]))
			print('  eor.w %s, %s, %s, lsr #1' % (str_regs[0], tmp_regs[0], str_regs[0]))
			print('  orr.w %s, %s, %s' % (str_regs[0], str_regs[0], tmp_regs[2]))
		else:
			print('  sbfx.w %s, %s, #0, #1' % (str_regs[0], ldr_regs[0]))
			print('  sbfx.w %s, %s, #0, #1' % (str_regs[1], ldr_regs[1]))
			print('  and.w %s, %s, %s' % (str_regs[0], str_regs[0], ldr_regs[2]))
			print('  eor.w %s, %s, %s' % (str_regs[1], str_regs[1], ldr_regs[3]))
			print('  and.w %s, %s, %s' % (str_regs[1], str_regs[1], str_regs[0]))
		print('  bfi.w %s, %s, #%d, #1' % (str_regs[2], str_regs[0], coef_id))
		print('  bfi.w %s, %s, #%d, #1' % (str_regs[3], str_regs[1], coef_id))
	print('  lsr.w %s, %s, #1' % (str_regs[0], str_regs[0]))
	print('  lsr.w %s, %s, #1' % (str_regs[1], str_regs[1]))
	print('  str.w %s, [r0], #4' % (str_regs[2]))
	print('  str.w %s, [r0], #4' % (str_regs[3]))
	print('  str.w %s, [r0], #4' % (str_regs[0]))
	print('  str.w %s, [r0], #4' % (str_regs[1]))
	print('  vmov.w r3, s0')
	print('  cmp.w r0, r3')
	print('  bne.w unit_mul')
	print('  pop.w {r4-r12, pc}\n')

def print_polyf3_lsr():
	ldr_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10']
	str_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10']
	curr_index = 0
	print('.global polyf3_lsr_asm')
	print('.type polyf3_lsr_asm, %function')
	print('@ void polyf3_lsr_asm(uint32_t *tritIn)')
	print('polyf3_lsr_asm:')
	print('  push {r4-r12, lr}')
	print('  mov r1, r0')
	print('  mov r2, r0')

	print('  ldr %s, [r1], #4 // load %d' % (ldr_regs[0], curr_index))
	print('  ldr %s, [r1], #4' % (ldr_regs[1]))
	while (curr_index < 22):
		print('  ldr %s, [r1], #4 // load %d' % (ldr_regs[2], curr_index+1))
		print('  ldr %s, [r1], #4' % (ldr_regs[3]))
		print('  lsr %s, %s, #1' % (ldr_regs[0], ldr_regs[0]))
		print('  lsr %s, %s, #1' % (ldr_regs[1], ldr_regs[1]))
		print('  orr %s, %s, %s, lsl #31' % (ldr_regs[0], ldr_regs[0], ldr_regs[2]))
		print('  orr %s, %s, %s, lsl #31' % (ldr_regs[1], ldr_regs[1], ldr_regs[3]))
		print('  str %s, [r2], #4 // store %d' % (str_regs[0], curr_index))
		print('  str %s, [r2], #4' % (str_regs[1]))
		print('  ldr %s, [r1], #4 // load %d' % (ldr_regs[0], curr_index+2))
		print('  ldr %s, [r1], #4' % (ldr_regs[1]))
		print('  lsr %s, %s, #1' % (ldr_regs[2], ldr_regs[2]))
		print('  lsr %s, %s, #1' % (ldr_regs[3], ldr_regs[3]))
		print('  orr %s, %s, %s, lsl #31' % (ldr_regs[2], ldr_regs[2], ldr_regs[0]))
		print('  orr %s, %s, %s, lsl #31' % (ldr_regs[3], ldr_regs[3], ldr_regs[1]))
		print('  str %s, [r2], #4 // store %d' % (str_regs[2], curr_index+1))
		print('  str %s, [r2], #4' % (str_regs[3]))
		curr_index += 2
	print('  ldr %s, [r1], #4 // load 23' % (ldr_regs[2]))
	print('  ldr %s, [r1], #4' % (ldr_regs[3]))
	print('  lsr %s, %s, #1' % (ldr_regs[0], ldr_regs[0]))
	print('  lsr %s, %s, #1' % (ldr_regs[1], ldr_regs[1]))
	print('  orr %s, %s, %s, lsl #31' % (ldr_regs[0], ldr_regs[0], ldr_regs[2]))
	print('  orr %s, %s, %s, lsl #31' % (ldr_regs[1], ldr_regs[1], ldr_regs[3]))
	print('  str %s, [r2], #4 // store 22' % (str_regs[0]))
	print('  str %s, [r2], #4' % (str_regs[1]))
	print('  lsr %s, %s, #1' % (ldr_regs[2], ldr_regs[2]))
	print('  lsr %s, %s, #1' % (ldr_regs[3], ldr_regs[3]))
	print('  str %s, [r2], #4 // store 23' % (str_regs[2]))
	print('  str %s, [r2], #4' % (str_regs[3]))
	print('  pop {r4-r12, pc}\n')

def print_polyf3_lsl():
	bndry = 2 * (NN // 32)
	num_loops = (NN // 32)
	ldr_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10']
	str_regs = ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10']
	print('.global polyf3_lsl_asm')
	print('.type polyf3_lsl_asm, %function')
	print('@ void polyf3_lsl_asm(uint32_t *tritIn)')
	print('polyf3_lsl_asm:')
	print('  push {r4-r12, lr}')
	print('  adds r3, #0')
#	print('  adds.w r12, r0, #%d' % (bndry * 4))
#	print('  mov.w r1, r0')
#	print('  vmov s0, r0')

	for it in range(0, num_loops, 8):
		print('  ldr %s, [r0, #%d]' % (ldr_regs[0], 8 * it))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[1], 8 * it + 8))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[2], 8 * it + 16))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[3], 8 * it + 24))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[4], 8 * it + 32))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[5], 8 * it + 40))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[6], 8 * it + 48))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[7], 8 * it + 56))
		print('  adcs %s, %s' % (str_regs[0], ldr_regs[0]))
		print('  adcs %s, %s' % (str_regs[1], ldr_regs[1]))
		print('  adcs %s, %s' % (str_regs[2], ldr_regs[2]))
		print('  adcs %s, %s' % (str_regs[3], ldr_regs[3]))
		print('  adcs %s, %s' % (str_regs[4], ldr_regs[4]))
		print('  adcs %s, %s' % (str_regs[5], ldr_regs[5]))
		print('  adcs %s, %s' % (str_regs[6], ldr_regs[6]))
		print('  adcs %s, %s' % (str_regs[7], ldr_regs[7]))
		print('  str %s, [r0, #%d]' % (str_regs[0], 8 * it))
		print('  str %s, [r0, #%d]' % (str_regs[1], 8 * it + 8))
		print('  str %s, [r0, #%d]' % (str_regs[2], 8 * it + 16))
		print('  str %s, [r0, #%d]' % (str_regs[3], 8 * it + 24))
		print('  str %s, [r0, #%d]' % (str_regs[4], 8 * it + 32))
		print('  str %s, [r0, #%d]' % (str_regs[5], 8 * it + 40))
		print('  str %s, [r0, #%d]' % (str_regs[6], 8 * it + 48))
		print('  str %s, [r0, #%d]' % (str_regs[7], 8 * it + 56))

	print('  adds r3, #0')
	for it in range(0, num_loops, 8):
		print('  ldr %s, [r0, #%d]' % (ldr_regs[0], 8 * it + 4))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[1], 8 * it + 12))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[2], 8 * it + 20))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[3], 8 * it + 28))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[4], 8 * it + 36))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[5], 8 * it + 44))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[6], 8 * it + 52))
		print('  ldr %s, [r0, #%d]' % (ldr_regs[7], 8 * it + 60))
		print('  adcs %s, %s' % (str_regs[0], ldr_regs[0]))
		print('  adcs %s, %s' % (str_regs[1], ldr_regs[1]))
		print('  adcs %s, %s' % (str_regs[2], ldr_regs[2]))
		print('  adcs %s, %s' % (str_regs[3], ldr_regs[3]))
		print('  adcs %s, %s' % (str_regs[4], ldr_regs[4]))
		print('  adcs %s, %s' % (str_regs[5], ldr_regs[5]))
		print('  adcs %s, %s' % (str_regs[6], ldr_regs[6]))
		print('  adcs %s, %s' % (str_regs[7], ldr_regs[7]))
		print('  str %s, [r0, #%d]' % (str_regs[0], 8 * it + 4))
		print('  str %s, [r0, #%d]' % (str_regs[1], 8 * it + 12))
		print('  str %s, [r0, #%d]' % (str_regs[2], 8 * it + 20))
		print('  str %s, [r0, #%d]' % (str_regs[3], 8 * it + 28))
		print('  str %s, [r0, #%d]' % (str_regs[4], 8 * it + 36))
		print('  str %s, [r0, #%d]' % (str_regs[5], 8 * it + 44))
		print('  str %s, [r0, #%d]' % (str_regs[6], 8 * it + 52))
		print('  str %s, [r0, #%d]' % (str_regs[7], 8 * it + 60))


#	print('unit_rorlow:')
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[0]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[1]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[2]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[3]))
#	print('  adcs.w %s, %s' % (str_regs[0], ldr_regs[0]))
#	print('  adcs.w %s, %s' % (str_regs[1], ldr_regs[1]))
#	print('  adcs.w %s, %s' % (str_regs[2], ldr_regs[2]))
#	print('  adcs.w %s, %s' % (str_regs[3], ldr_regs[3]))
#	print('  str.w %s, [r0], #8' % (str_regs[0]))
#	print('  str.w %s, [r0], #8' % (str_regs[1]))
#	print('  str.w %s, [r0], #8' % (str_regs[2]))
#	print('  str.w %s, [r0], #8' % (str_regs[3]))
#	print('  cmp.w r0, r1')
#	print('  bne.w unit_rorlow')

#	print('  vmov r0, s0')
#	print('  adds.w r0, #4')
#	print('unit_rorhigh:')
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[0]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[1]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[2]))
#	print('  ldr.w %s, [r0], #8' % (ldr_regs[3]))
#	print('  adcs.w %s, %s' % (str_regs[0], ldr_regs[0]))
#	print('  adcs.w %s, %s' % (str_regs[1], ldr_regs[1]))
#	print('  adcs.w %s, %s' % (str_regs[2], ldr_regs[2]))
#	print('  adcs.w %s, %s' % (str_regs[3], ldr_regs[3]))
#	print('  str.w %s, [r0], #8' % (str_regs[0]))
#	print('  str.w %s, [r0], #8' % (str_regs[1]))
#	print('  str.w %s, [r0], #8' % (str_regs[2]))
#	print('  str.w %s, [r0], #8' % (str_regs[3]))
#	print('  cmp.w r0, r2')
#	print('  bne.w unit_rorhigh')

	print('  pop {r4-r12, pc}\n')

print_prologue()
print_polyf3_pack()
print_polyf3_unpack()
print_polyf3_add_packed()
print_polyf3_sub_packed()
print_polyf3_mul_packed()
print_polyf3_lsr()
print_polyf3_lsl()
