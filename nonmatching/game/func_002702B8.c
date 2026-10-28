/* func_002702B8, 12 bytes at 0x002702B8 in the boot and all 27 levels.
   Not an independently callable function: the previous body returns at 0x002702AC
   with its delay slot at 0x002702B0; a nop fills 0x002702B4. This extent is
   daddu $v0,$zero,$zero / nop / sw $zero,0($a0), then falls through across a nop
   into the next function's prologue at 0x002702C8. The level copies have the same
   neighborhood. All 28 disassemblies have no direct branch/call reference to the
   extent, and the aligned literal-pointer scan found no reference to any placement.
   A plain C zeroing store compiles to sw / jr $ra / daddu in the same 12 bytes, so
   it cannot reproduce this fallthrough. Retained only as catalogue-defect evidence;
   no C is deposited. See docs/LEVELS.md. */
