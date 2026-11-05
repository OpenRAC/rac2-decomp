# Authored controls: the same division floor after direct and relaxable loads.
	.text
	.extern small_value,4
	.extern large_value,64

	.globl direct_gp
	.ent direct_gp
direct_gp:
	lwc1 $f12,8($gp)
	div.s $f12,$f12,$f20
	.end direct_gp
	.size direct_gp,.-direct_gp

	.globl small_gp
	.ent small_gp
small_gp:
	lwc1 $f12,small_value
	div.s $f12,$f12,$f20
	.end small_gp
	.size small_gp,.-small_gp

	.globl large_absolute
	.ent large_absolute
large_absolute:
	lwc1 $f12,large_value
	div.s $f12,$f12,$f20
	.end large_absolute
	.size large_absolute,.-large_absolute

	.globl two_gp
	.ent two_gp
two_gp:
	lwc1 $f12,small_value
	lwc1 $f14,small_value
	div.s $f12,$f12,$f14
	.end two_gp
	.size two_gp,.-two_gp

	.globl gp_word
	.ent gp_word
gp_word:
	lwc1 $f12,small_value
	.word 0
	div.s $f12,$f12,$f20
	.end gp_word
	.size gp_word,.-gp_word

# A forward declaration is not assumed to be GP-relative during emission.
	.globl forward_absolute
	.ent forward_absolute
forward_absolute:
	lwc1 $f12,forward_value
	div.s $f12,$f12,$f20
	.end forward_absolute
	.size forward_absolute,.-forward_absolute
	.extern forward_value,64
