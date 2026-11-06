# The assembler's two transfer-delay exemptions (tests/test_mtc1_exemption.py).
# Each pair is assembled once at a function start (empty history: no nop) and once
# behind a branch delay slot the assembler fills with a nop (the nop stays).
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
