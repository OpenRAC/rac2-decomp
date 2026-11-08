# The assembler's two transfer-delay exemptions (tests/test_mtc1_exemption.py).
# Each pair is assembled once where gas has forgotten its history (prev_insn_valid clear:
# here a section start, so no nop) and once behind a branch delay slot the assembler fills
# with a nop (the nop stays). gas also empties both history slots after every unconditional
# branch without forgetting it; an mtc1 there keeps the nop too: behind b with a nop in its
# slot, or with the previous instruction there when assembled with --r5900-swap-branch-slots,
# behind j, jal and jr (as a second function in one section would be), and behind a b with a
# .p2align padding nop between. The last two cases are known limits, forms cc1 never emits:
# .align and .set reorder forget the history, so an mtc1 behind a b and one of them stays
# exempt.
	.section .text.convert_entry,"ax",@progbits
	.globl	convert_entry
	.ent	convert_entry
convert_entry:
	mtc1	$4,$f0
	cvt.s.w	$f0,$f0
	j	$31
	swc1	$f0,0($5)
	.end	convert_entry

	.section .text.convert_after_branch,"ax",@progbits
	.globl	convert_after_branch
	.ent	convert_after_branch
convert_after_branch:
	lw	$2,0($6)
	addiu	$3,$3,1
	beq	$2,$0,1f
	mtc1	$4,$f0
	cvt.s.w	$f0,$f0
	swc1	$f0,0($5)
1:	j	$31
	.end	convert_after_branch

	.section .text.compare_entry,"ax",@progbits
	.globl	compare_entry
	.ent	compare_entry
compare_entry:
	mtc1	$0,$f0
	c.lt.s	$f12,$f0
	j	$31
	.end	compare_entry

	.section .text.compare_after_branch,"ax",@progbits
	.globl	compare_after_branch
	.ent	compare_after_branch
compare_after_branch:
	lw	$2,0($6)
	addiu	$3,$3,1
	beq	$2,$0,1f
	mtc1	$0,$f0
	c.lt.s	$f12,$f0
1:	j	$31
	.end	compare_after_branch

	.section .text.other_register,"ax",@progbits
	.globl	other_register
	.ent	other_register
other_register:
	mtc1	$5,$f0
	cvt.s.w	$f0,$f0
	j	$31
	.end	other_register

	.section .text.compare_after_b,"ax",@progbits
	.globl	compare_after_b
	.ent	compare_after_b
compare_after_b:
	lw	$2,0($6)
	bne	$2,$0,1f
	b	2f
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
2:	j	$31
	.end	compare_after_b

	.section .text.compare_after_swapped_b,"ax",@progbits
	.globl	compare_after_swapped_b
	.ent	compare_after_swapped_b
compare_after_swapped_b:
	addiu	$3,$3,1
	b	2f
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
2:	j	$31
	.end	compare_after_swapped_b

	.section .text.compare_after_j,"ax",@progbits
	.globl	compare_after_j
	.ent	compare_after_j
compare_after_j:
	j	compare_entry
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
	j	$31
	.end	compare_after_j

	.section .text.compare_after_jal,"ax",@progbits
	.globl	compare_after_jal
	.ent	compare_after_jal
compare_after_jal:
	jal	compare_entry
	mtc1	$0,$f0
	c.lt.s	$f12,$f0
	j	$31
	.end	compare_after_jal

	.section .text.convert_after_jr,"ax",@progbits
	.globl	convert_after_jr
	.ent	convert_after_jr
convert_after_jr:
	j	$31
1:	mtc1	$4,$f0
	cvt.s.w	$f0,$f0
	j	$31
	.end	convert_after_jr

	.section .text.compare_after_aligned_label,"ax",@progbits
	.globl	compare_after_aligned_label
	.ent	compare_after_aligned_label
compare_after_aligned_label:
	addiu	$3,$3,1
	b	2f
	.p2align 3
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
2:	j	$31
	.end	compare_after_aligned_label

	.section .text.limit_after_align,"ax",@progbits
	.globl	limit_after_align
	.ent	limit_after_align
limit_after_align:
	addiu	$3,$3,1
	b	2f
	.align	3
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
2:	j	$31
	.end	limit_after_align

	.section .text.limit_after_set_reorder,"ax",@progbits
	.globl	limit_after_set_reorder
	.ent	limit_after_set_reorder
limit_after_set_reorder:
	addiu	$3,$3,1
	b	2f
	.set	noreorder
	.set	reorder
1:	mtc1	$0,$f0
	c.lt.s	$f12,$f0
2:	j	$31
	.end	limit_after_set_reorder
