/* func_003407F8 - 464 bytes.  Worker attempt, 27 October 2026 (draft below).

   488 B vs 464. Logic decoded: recent-items ring (8 slots of 0x1C at
   **D_001B18D4, ring index state+0x7CC): if item invalid/EA7E flag ->
   func_002E5E58(5,0,0) else remove existing slot of same item (zero +0x18, +0
   = name of D_00139568[0]) then write item at next slot and
   func_002E5E58(4,0,0); finally ring index = idx+1>7?0:idx+1.
   Key diff: retail reads D_001B18D4 via $gp (lw 0x28E4($gp)) in the search
   but via lui/lw into a register in the later block (list = D_001B18D4, then
   lw 0(list) before every access); the call func_002E5E58(5,0,0) arg a0=5 is
   in the delay slot of the first beqz. t2/t3 swapped, 6 insns longer. Tried
   sda incomplete array. */

/* in src/game/0033F030.c (needs MenuState, MenuEntry, func_002E5E58 from the file); remove the INCLUDE_ASM; must come after the typedefs */
