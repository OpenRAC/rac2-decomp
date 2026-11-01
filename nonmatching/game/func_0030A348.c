/* 1 November 2026: 5860 of 5868 bytes, 173 rows off once relocations are masked, allocation of
   the whole chain loop and the scan pointer equal to retail.  Unit flags as below.  What closed it
   (see docs/MATCHING-BLOCKERS.md, Families F4 and F7): RAC1's two-dimensional chain array
   P2[2][20] of a union vector, per-arm calls to func_002A8E20 (cross-jumped in retail; hit1's two
   extra in-loop refs put it in $fp), &D_002295D0[k].v[1] (the addend hoisted, so madd), block
   scopes that lengthen a movable's life past loop.c's threshold (near-arm vA0 copy, the
   D_00189E20 base), the pre-increment scan loop.  Older notes below are history. */
/* fable (Claude Fable 5.1) 2026-10-28, v2/c03 toolchain (upstream master + PR #348): still a
   near miss, closer than opus-2's draft.  Unit for a retry: src/game/0030A348-g8.c with
       -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   (append that line to config/cflags.txt; take the marker out of 00308600.c).
   check.py: 5828 of 5868 bytes, 0/1 places.  difflib on opcodes 1347/1467; with registers and
   $sp offsets compared (relocation immediates masked) 1110/1467 (opus-2's draft 1094 on the same
   scorer, its own scorer said 1071).
   RAC1 counterpart: update_electric_water_bolt_effect (rac1-decomp
   src/overlays/shared/electric_water.c:644): the same 20-point chain loop with the mirror chain
   points[1][i], the 21-i far arm, the k loop over four 5-point side arcs (p[0], p + j, p[j - 1]
   of a 0x50-byte record) and the three sparks.  RAC2 adds the target scan, the two lock arms,
   the collision test and the two hit records.  RAC1 indexes the arrays directly (no cp2, prev or
   near variables); its copies are qcopy.
   Changes from opus-2's draft, each checked against retail:
   1. `if (i < 10)` / `if (i >= 10)` written inline, no `near` variable: retail's second
      `slti $s0,$s2,0xA` (rows 584 and 631 of the retail listing) is a gcse PRE insertion of the
      (lt i 10) reaching register at the end of the lockA-only arm; a variable gives one slti.
   2. `prev = D_00229170[i - 1]; cp2 = prev + 84;` at the loop top.  loop.c records givs in insn
      order, keeps them in a list in reverse order and emits the inits in list order, so with prev
      discovered first cp2's init is emitted before prev's: cse2 can no longer rewrite it through
      the i-1 giv (make_regs_eqv prefers the giv register, whose last use is later).  Result as
      retail: `addiu $s4,$a0,0x150`, `addiu $s1,$a0,0x10`, the i-1 giv with 7 refs (init 1, lq 2,
      increment 4; retail's slot 0x3A8 has those 4 uses) spilled, and &v80 in $s7.  (`prev` first
      with `cp2 = D_00229170[20 + i]` loses cp2's giv: cse makes the cp2 base a related constant of
      prev's base, `t = base + 336`, life 2, not hoisted, so cp2 is no longer an induction
      variable and is recomputed in the loop; moving cp2's assignment below the prev use changes
      the loop's allocation because the user variable is then not replaceable.)
   What still differs:
   - GPR allocation (the bulk of the remaining lines).  Retail gives &hit1 $fp and spills best
     (0x358), second (0x35C), the i*16 giv (0x39C), the scan pointer giv (0x3AC), &D_001B5200,
     &v90 (0x390) and got (0x360).  Here (tools/regalloc.py; this toolchain's global.c is stock
     allocno_compare, floor_log2(refs)*refs/live, plus a live-range key that is always 0, and
     find_reg pass 1 = registers used so far minus those other allocnos prefer, pass 2 = any):
     &hit1 11 refs / 689 = 0.0479 ranks below best 9/512 = 0.0527, the i*16 giv 11/638 = 0.0517
     (its constant init doubles the live length in update_equiv_regs), second 9/530 = 0.0509,
     &D_001B5200 7/280 = 0.050, the scan giv 7/282 = 0.0496, &v90 11/675 = 0.0489 and got
     10/622 = 0.0482.  Each of those conflicts with $s0-$s7 over its range, so the first one
     allocated takes $fp (best in the scan, then the i*16 giv in the loop) and &hit1 spills to
     0x37C; everything after (reload's round-robin spill registers, delay slots, the hb records'
     $v0/$v1) follows from that.  Retail's order needs &hit1 above 0.0527: 13 refs (one more
     in-loop use, 39/689 = 0.0566) or a live length under 626.  &hit1's refs here are the four
     PRE insertions (gcse "end of bb 1,2,4,5"; bb 2's becomes a cse2 self-copy `r = r` that counts
     twice), a0 of func_002A8C00, a3 of func_00277F48, and in the loop the sq of qcopy(&hit1, vb)
     and a1 of func_002A8E20 (x2 each); its range runs from the insertion blocks before the scan to
     the chain loop's end.  Retail's bytes show exactly the same insertions (rows 68, 87, 116) and
     uses, so what gives retail's &hit1 its priority is not visible; a second `best = 0; second
     = 0;` before the scan (E6/E9) spills best but adds a store retail lacks and leaves the i*16
     giv in $fp.
   - far/near &D_00229440[i] givs: retail keeps the far giv (lower pseudo, slot 0x3A0) primary and
     copies it to the near one (`lw $a0,0x3A0; sw $a0,0x3A4`); here cse2's "(set REG0 REG1) where
     REG0 is the cheapest" rule (cse.c; fires when the previous non-note insn sets REG1 and the
     later-numbered register is canonical, which it is because its increment is emitted later)
     swaps them: near primary, far = copy (`sw $v0,0x3A0; sw $v0,0x39C`, one instruction
     fewer).  Blocking it needs a non-note insn between the two inits, i.e. a giv discovered
     between the near and far D_00229440 uses that keeps its own init; a far-arm z temp
     (`float *zf = cp2 + 2`) did not get one (its DEST_REG giv is eliminated into $s1+0x148).
   - &vA0 near-arm copy: retail hoists it (0x370, one register for the lq and the call's a2); here
     loop.c pass 2 says "regno 567 (life 6), savings 1 not desirable" (61*1*6 = 366 < 368 loop
     insns).  A TImode assignment instead of qcopy changes nothing (E2); cse does not flush at a
     volatile asm in this cse.c, only memory equivalences.
   - D_00229440 base in the preheader: retail `lui $v1; daddu $v0,$v1; addiu $v0,$v0,lo` (a
     surviving copy of the high part), here `lui; addiu` in one register.
   - k loop: D_002295E0[k] as mult/addu here, mtlo/madd in retail; hb.a/hb.b self reloads.
   Declarations: all in this file.
*/
/* opus-2 (Claude Opus 5.5) 2026-10-28, v2/c03 toolchain (upstream master + PR #348): still a
   near miss, closer than opus-1's draft.  Unit for a retry: src/game/0030A348-g8.c with
       -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   (append that line to config/cflags.txt; take the marker out of 00308600.c).  The optional
   -frac2-gcse-unsplit-edges / -frac2-keep-block-order / -frac2-no-null-pointer-checks change
   no byte of it.
   check.py: 5836 of 5868 bytes, 0/1 places (opus-1 draft: 5820).  difflib on opcodes
   1345/1467 (was 1339 on the same scorer); with registers and $sp offsets compared (relocation
   immediates masked) 1071/1467 (was 1024).  With opus-1's block-local declarations, changes 1
   and 3 alone score 1085, plus 4 1077, plus 2 1081: those keep the gcse slot order wrong (5).
   Changes from opus-1's draft, each moving a measured retail feature:
   1. FPRs now equal retail's in the chain loop, the k loop and the tail, through RAC1-style
      variable reuse: `amp` holds both the base (D04 + (D08 - D04) * (CE0(i) * 0.05f), one
      expression: the product is an $f0 temp and D04 stays in $f4) and the near-arm amplitude
      (f21; one global pseudo, so the D20 load is not tied to it); `height` holds both heights
      (f20), and `height = amp * func_00283198(angle) + func_002A78D8(0.0f, 0.1f)` is ONE
      expression, so the sin result is a local temp tied to the product and the local `angle`
      is pushed to f22 by local-alloc; separate `length` (lock arms, f20), `blend` (f21) and a
      local `cm` for the two lengths that stay in $f0; angle0/angle1 shared by the k loop and
      the tail (global, so the tail's 0.0/0.15 constants take f21/f22 first); the k loop's `kf`
      shared by both branches with `kf = kf / func_00283CE0(0xF)` (f20 in both, as retail).
   2. `hit1.kind = 5; hit1.flag = 1;` gives retail's store order and registers (the two hb
      records keep flag first; their $v0/$v1 still differ, see below).
   3. `prev = D_00229170[i - 1]` as a pointer local: loop.c now reduces the i-1 giv (it was
      "not worth while, 378 vs 442": lifetime 2 counts the inline qcopy's BLOCK_BEG note, line
      notes have no luid), so the chain loop has retail's four givs (i*16, far and near
      &D_00229440[i], i-1) and the size went from 5820 to 5836.
   4. `list = D_001EE960; for (sn = 0; (t = list[sn]) != 0; sn++)`: the scan pointer is a giv
      in the last spill slot, as retail's 0x3AC.
   5. Every scalar declared at function level except the chain-loop counter `i` (block around
      that loop, pseudo ~300): k becomes pseudo 161 (opus-1's constraint [161,186] for N=677)
      and gcse's PRE registers come out in retail's order: i*4 first, ..., &vA0, k+1 last
      (slots 0x370..0x394 here = retail 0x378..0x398 minus the two missing early slots).  With
      `i` also at function level it is pseudo 162 and i*4 no longer wraps (needs >= 174).
   What still differs (GPR allocation of four pseudos, then scheduling/delay slots):
   - Retail spills best (0x358), the near-arm &vA0 qcopy-parm copy (0x370) and the i-1 giv
     (0x3A8), and gives &hit1 $fp, &v80 $s7.  Here (tools/regalloc.py, priority =
     floor_log2(refs)*refs/live): i-1 giv 8/326 = 0.0736 takes $s7, &v80 14/663 = 0.0633 takes
     $fp, best 9/512 = 0.0527 takes $s7 in the scan, then i*16 giv 0.0517, second 0.0509,
     &vA0 0.0502, scan giv 0.0496, &v90 0.0489, got 0.0482 and &hit1 11/689 = 0.0479 all spill.
     Retail's result needs &hit1 between &v80 and best (about 13 refs, i.e. one more in-loop
     use, or a shorter life) and the i-1 giv below &hit1 (its 8 refs include cp2's init
     `1213 = 1212 + 336`).  A second `best = 0; second = 0;` before the scan spills best but
     adds a store retail does not have (measured again here: 1079).
   - &vA0 copy: loop pass 2 has 368 insns, "regno 570 (life 6), savings 1 not desirable"
     (61*1*6 = 366); retail hoists it, so its loop is 2 insns shorter or the copy lives 7.
   - hb.a/hb.b record stores: self is reloaded into $v1 here, $v0 in retail (constants 3/5
     swapped); flag,tag,kind and kind,flag,tag orders measured worse.
   - Scan and k-loop scheduling and delay slots follow from the allocation above.
   Declarations: all in this file (types Tgt, TgtClass, Rope, Moby, Hit, Cam, Level, Slot,
   HitResult, Node5, the sda D_001AEDF4..D_001AEE8C floats and the callee prototypes).
*/
/* opus-1 (Claude Opus 5.5) 2026-10-28, v2/c03 toolchain (upstream master + PR #348): still a
   near miss.  Unit for a retry: src/game/0030A348-g8.c with
       -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   (one appended config/cflags.txt line; take the marker out of 00308600.c).
   check.py: 5820 of 5868 bytes, 0/1 places.  difflib on opcodes 1335/1467 (the closer8 body
   below the old headers also gives 1335 here, not its recorded 1360: that was orch/main's cc1);
   with registers and stack offsets compared (relocation immediates masked) 1021/1467, closer8 1018.
   (The same C with s2C0 kept, i.e. only the first two changes below, scores 1037 but has a
   675-bucket gcse table, see 2.)  Changes from closer8, each moving a measured retail feature:
   - `locked` and `reach` are initialised declarations ahead of `st`: st becomes pseudo 103.
   - the chain loop's `i` is declared in a block around that loop, and the held loop uses its own
     `n`: retail's held loop counts down in $a2 (no calls crossed), not in the chain loop's $s2.
   - no `s2C0` local in the k loop (hb.q directly): retail keeps a hoisted copy of &hb (0x374),
     and the unit's insn count then gives gcse retail's table size (see 2).
   How to read retail's spill slots (all measured with tools/regalloc.py dumps, x.i.gcse/.loop):
   1. Global-alloc spills get slots in pseudo order, so the slots name the pseudos: retail 0x350
      self, 0x354 locked, 0x358 best, 0x35C second, 0x360 got, 0x364 nheld, 0x368/0x36C/0x370
      loop-hoisted copies of &v70/&v80/&vA0 (chain loop), 0x374 copy of &hb (k loop), then gcse
      PRE reaching regs 0x378 i*4, 0x37C &s2B0, 0x380 &hb, 0x384 &v60, 0x388 &v70, 0x38C st+0x10,
      0x390 &v90, 0x394 &vA0, 0x398 k+1, then loop.c givs 0x39C i*16, 0x3A0/0x3A4 &D_00229440[i]
      (far/near arm), 0x3A8 &D_00229170[i-1], 0x3AC the scan pointer (loops are scanned last first).
   2. PRE creates its reaching regs in hash-bucket order: bucket = hash % N, N = (max_cuid/2)|1,
      hash(sp+c) = 14030+c, hash(reg r + c) = 14029+r+c, hash(r << s) = 14041+r+s (this cc1's rtx
      codes).  Retail's order then requires st's pseudo in [98,128] and N in 677..699 (with N=675,
      closer8's table, &vA0 wraps to the first slot); for N=677 (this body's table) it requires
      i's pseudo >= 174 (311 here) and k's in [161,186] (112 here, so k+1 still lands before
      &vA0).  In general i and k must lie in [21N-14043, 21N-14031] when declared together.
   3. loop.c: movables move when 61*savings*life >= loop insns, givs reduce when
      63*lifetime*benefit >= loop insns.  Retail hoists the near-arm &vA0 copy (here life 6,
      61*6 = 366 < 368 insns in the second loop pass) and reduces the i-1 giv (here 2*63*3 = 378
      < 442 insns in the first pass).  A pointer biv for D_00229170[i] gave 415 first-pass insns,
      not enough, and scored worse; TImode assignments in the chain loop shorten the copy's life.
   4. Allocation: retail gives &hit1 $fp.  Here the competitors for $fp are the i*16 giv (13 refs,
      live 636 = 318 doubled by update_equiv_regs for its constant init; priority 0.061), best
      (0.053) and second (0.051), all above &hit1 (11 refs, live 688, 0.048); &v80 (0.063) takes
      $s7 as in retail.  closer8's second `best = 0; second = 0;` before the scan spills best
      (live 1020) but then second and the i*16 giv still take $fp.
   Also measured and rejected: the list[n] scan loop (pointer to the last slot as retail, but
   1017 vs 1037 with the other slots shifted); declaring every local at the top (gives N=677,
   i=147, k=148, 1008).  Other differences as in the notes below (k-loop madd, beql/movn, ...).
*/
/* closer8 2026-10-26 (third pass, base rac2-large-functions ab77006e with the dli fix 25c1ac77):
   still a near miss.  Opcode-aligned 1360/1467 (this scorer; 1358 for the previous draft),
   1459 instructions (5836 of 5868 B).  Changes kept here: `(float)i` written inline (gcse's
   reaching-register copy gives retail's cvt into $f20 + mov.s $f23 after func_00283CE0), and
   `base = func_00283CE0(i) * 0.05f; base = D04 + (D08 - D04) * base;` (D_001AEE04 in a temp
   $f4, as retail).  Neither the qzero_nc helper (no qzero here) nor the combined loop-padding
   fixes (d53f2197 + efabf1d2) change a byte of this function.
   Mechanisms measured (variants in claims/func_0030A348/closer8/, ga2.py/an.sh there):
   - Scan loop: `Tgt **list = D_001EE960; for (n = 0; (t = list[n]) != 0; n++)` makes loop.c
     reduce a giv for the walking pointer; loops are scanned last-to-first, so it gets the
     highest pseudo number and retail's LAST spill slot (0x3AC), with the lw in the continue
     delay slots as retail.  With `D_001EE960[n]` the lo_sum stays in the loop ("not
     desirable", 61*1*2 < 173 insns) and no giv forms; with a user pointer p the slot is early.
     It scores lower overall only because the allocation cascade shifts.
   - best/second spill: update_equiv_regs doubles REG_LIVE_LENGTH once per constant set seen
     before the first non-constant set.  A second `best = 0; second = 0;` before the scan
     doubles best again (priority 527 -> 293), so it spills as in retail.
   - The z giv &D_00229170[i][2] ($s7 here) is not combined with &D_00229170[i] because cse
     puts the address in a register shared by the load and the store (not DEST_ADDR).  A
     `float *cp = D_00229170[i]` for the two z statements combines it (0x8($s1), as retail) and
     &v80 then gets $s7 as retail; but the i*16 giv (pri 615) then takes $fp ahead of &hit1
     (pri 480), and best/second/got (508/485) are also above &hit1.  Retail's order needs
     &hit1 above all of them; no spelling found yet.
   - &D_00229170[i - 1] is a giv in retail (0x3A8); here "not worth while, 378 vs 440 insns"
     (lifetime 2 * 63 * benefit 3).  A `float *prev = D_00229170[i - 1]` local gets it reduced
     but into a saved register.
   - Retail keeps two separate &D_00229440[i] givs (0x3A0 for the far arm, 0x3A4 for the near
     arm) and cp2[2] as 0x148($s1); the k loop's i-loop giv is 0x398.
*/
/* WIP 2026-10-26 (second agent): 1346/1467 opcodes equal (was 1267), 5828 B.
   Closed since the header below: qcopy() helper from common.h for every quadword copy
   (asm volatile flushes CSE, so k*0x50 is recomputed and becomes madd as in retail);
   indexed for-loops in the k-loop arms (check_dbra_loop count-down, one tmp pointer);
   abs-diff as a call in each arm, `if (D_001B23E8[k] > D_001B2400[k])` (cross-jumped call,
   beql, no movn); `a2 = 0.0f` before the CA0 test plus a separate `cs` variable (the 0.0
   lives in $f21 as retail); block-local f/w/m; amp's base as its own statement;
   D_001BAF98 as a struct {hit; pad; pos[4]} (retail reads hit as -8 off &pos).
   dli 0xFFFF0000FFFF0000 closed by compiler/dli-leading-ones.
   Still open: allocation (best/second spilled and &hit1 in $fp in retail), scan pointer
   in the last spill slot, chain-loop giv set (retail: separate i-1 and two D_00229440 givs),
   D5E0 madd needs the symbol hoisted (loop.c "not desirable", k loop 223 insns).
   The GCC 2.95 gcse model (compiler/gcse-default 7d7df088) gives identical bytes here.
   Variant with `float *cp = D_00229170[i]` for the z accesses and no cp2 local: 1344, with
   retail's [i][2] giv combination and cp2 giv, but a separate [20+i][2] giv where retail
   uses 0x148($s1). See claims/func_0030A348/NOTE. */
/* func_0030A348 (5868 bytes, 1467 instructions, boot; also 26 per-level copies: family F4, 27
   members, 158 KB), the lock-on tether effect.  NEAR MISS: 5808 of 5868 bytes, 1267 of 1467
   opcodes equal (difflib, registers ignored, 86.4%; the first draft had 1218).  The stack frame
   is equal (-0x440), and so is the local layout up to 0x350; the spill slots 0x350-0x3AC differ
   in assignment.  The INCLUDE_ASM in src/game/00308600.c stays.

   Profile: put this C in src/game/0030A348-g8-qcopy.c with
       -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   (-g: the $LM line labels matter, see "line structure" below; -G8: the D_001AED../EE.. tuning
   floats are gp-relative, declared `__attribute__((sda))` with D_<addr> names; qcopy: lq/sq
   through address registers.)  The compiler is the one with the TImode one-GPR fix (branch
   compiler/ti-zero-reload).

   Step 0: one function, one prologue, one jr $ra, no dead code, no jump tables.

   Source: m2c (mipsee-gcc-c, prototypes from the matched callees) rewritten by hand.  What it is:
   the rope that the player's hand throws at up to two locked targets (Rope = the moby's +0x68
   record: a[4] anchor, b[4] tip, lockA +0x20, lockB +0x38, count +0x3E, four u16 at +0x40 read
   as one u64 for the "nothing pending" tests).  It (1) scores the targets in D_001EE960 by
   distance/angle, keeps the best two, (2) walks 19 chain points in D_00229170 (twenty, plus the
   mirrored second chain at +0x140), wobbling them with the tuning floats and breaking at the
   first point whose segment hits something (func_002761F8), (3) spawns hit records for the
   locked targets, (4) animates four glow nodes (Node5 = five quads, stride 0x50, in the three
   symbols D_002295C0/D0/E0), (5) spawns three sparks with func_002C2210.

   What closed differences since the first draft (all apply to the 26 other members):
   - Line structure.  With -g the assembler pads every div.s that is fewer than two slots after
     a $LM label with nops, so the statement boundaries around each division are visible in the
     bytes.  Retail has separate statements for the two score divisions (fa, fb), for
     `f = DF0(v80); if (f == 0) ... reach / f` (one call, not two), and for `cd = CE0(..);
     reach = f / cd`.  Now all div.s contexts equal retail's except one.
   - De-nested calls.  `D30(dst, ent + 0xE0, DB0(src, ent + 0xE0))` is two statements
     (proj = DB0(..); D30(.., proj)): retail re-reads D_00189E20.ent after the first call
     instead of keeping ent + 0xE0 in a saved register.
   - lockA/lockB length block: `ia = AB1F0(st->lockA)` first, then the copy of the position,
     then D30(.., ia[4]) (retail calls before it copies).
   - `if (locked) D_001AEE58 = 0x207F20; else D_001AEE58 = 0x7F2020;` as two statements (the
     ternary makes a movn here, retail branches).
   - kind test as two nested ifs (0xFE then 0xFD): `&&` is folded into a range test.
   - Arrays indexed by i as float[][4] (D_00229150/60/70, D_00229440) and `cp2` as the only
     pointer local: the loop optimiser then builds the same pointer inductions as retail
     (0x148($cp) for cp2[2], one lui/addiu per symbol).
   - The two hit records are members of one union local `hb` (hb.a.r at +0x10, hb.b.r at +0,
     scratch quad hb.q at +0): retail addresses them $sp-direct (sb 0x2D9($sp)); pointers into a
     char buffer give sb 0x19($a0).
   - D_001B23E0 is an int (sw), the second spark passes -s, the two stores of the k loop come
     before the first func_002A78D8 call (the sh zero fills its delay slot), info->short test
     is `if (x == 1) n = 1` (lh + movz, not lhu + movn).
   - best/second declared after locked: the spill slots then come out locked 0x354, best 0x358.

   What still differs (all of it register allocation, spill, or compiler-model):
   1. Allocation.  Retail keeps &hit1 in $fp and &v80 in $s7 across the candidate scan and the
      chain loop, and spills best/second (0x358/0x35C), got/nheld (0x360/0x364), &s2B0 (0x37C),
      &buf (0x380), &v60 (0x384), &v70 (0x388), st+0x10 (0x38C), &v90 (0x390), &vA0 (0x394)
      and the scan's walking pointer (0x3AC, the last slot).  Here best is spilled too now but
      second stays in $s7 and &s2B0 takes $fp, hit1/v80 are spilled.  tools/regalloc.py cannot
      run on this function (the -dS/-dR dumps abort cc1, "buffer overflow detected"); run cc1
      with -dl -dg only.  The inferred priority floor_log2(refs)*refs/live_length puts
      &hit1 (11 refs, live 690) at 0.048, second (9, 528) at 0.051, the D_001B5200 base (7, 278)
      at 0.050 and &s2B0 (36, 1058) at 0.17, so retail's choice is not a plain priority order
      (retail spills &s2B0 although its priority is highest): another pseudo must hold $fp inside
      its range (the lui $fp,0x1B of D_001B5340 after the chain loop is one).  Nothing tried
      moves them honestly: declaration order, scopes, pointer locals for every array
      combination (32 variants), index vs pointer scan loops, ref-count changes.  The
      decomp-permuter (aligned-diff scorer) reached 505 differing lines from 578 but only by
      duplicating loop bodies under `if (best)`: artifacts, rejected.
   2. k loop, `sym + k * 0x50`.  Retail has mtlo/madd for D_002295D0[k].v[0] and
      &D_002295E0[k] (3 madd + 3 mult in all), this compiler has one mult per arm and shares it
      with the pointer inits (mult count 3).  r5900_madd_profitable_p refuses when the addend's
      def is linked to the madd insn, and gcse/cse share the multiply across the call and the
      do-while loop.  No spelling found that unshares them (statement order, pointer locals,
      D + k * 80 forms).  Needs a compiler look.
   3. dli 0xFFFF0000FFFF0000 (the lockB mask).  Retail: lui $v1,0x8000; dsll $v1,$v1,1;
      ori $v1,$v1,0xFFFF; dsll $v1,$v1,16.  Patch 0052's field expansion gives ori 0xFFFF;
      dsll32 0; ori 0xFFFF; dsll 16 (same length, different bytes) for every spelling of the
      constant, and --r5900-sign-bit does not touch it.  The lockA mask 0x0000FFFF0000FFFF
      matches.  A narrow gas rule (sign bit set, low 16 bits zero, shifted value
      0xFFFFFFFF0000FFFF built as lui 0x8000/dsll 1/ori) would close it; needs
      `tools/build.py all` and tests/test_dli_masks.py.
   4. `d = x >= y ? x - y : y - x` (and the if/else spelling) becomes movn here; retail has
      slt + beql with the subu in the delay slot.
   5. Retail hoists a float 0.0 (mtc1 $zero,$f21) before the scan's `f != 0.0f` compare and
      keeps zero in $f25 for the chain loop's compares; here it is reloaded at each use.
*/
#include "include_asm.h"
#include "common.h"

typedef int V4 __attribute__((mode(TI)));
typedef union { V4 q; float f[4]; } Vec;

/* The lock-on tether: a chain of twenty points that hangs from the player's hand to up to two
   locked targets, its glow spots and sparks. Only the fields this function touches are named. */
typedef struct Tgt {
    char pad0[0x10];
    float pos[4];                       /* 0x10 */
    unsigned char kind;                 /* 0x20 */
    char pad1[3];
    struct TgtClass *cls;               /* 0x24 */
    char pad2[0x98 - 0x28];
    int f98;                            /* 0x98 */
} Tgt;

typedef struct TgtClass {
    char pad0[0x10];
    int f10;                            /* 0x10 */
    char pad1[0x46 - 0x14];
    short id;                           /* 0x46 */
} TgtClass;

typedef struct Rope {
    float a[4];                         /* 0x00 */
    float b[4];                         /* 0x10 */
    Tgt *lockA;                         /* 0x20 */
    char pad1[0x38 - 0x24];
    Tgt *lockB;                         /* 0x38 */
    short pad2;
    short count;                        /* 0x3E */
    union {
        struct {
            unsigned short h40, h42, h44, h46;
        } s;
        unsigned long q;                /* 0x40 */
    } u;
} Rope;

typedef struct Moby {
    char pad0[0x68];
    Rope *rope;                         /* 0x68 */
    char pad1[0xAA - 0x6C];
    unsigned short tag;                 /* 0xAA */
} Moby;

typedef struct Hit {
    float dir[4];                       /* 0x00 */
    char pad0[0x18 - 0x10];
    unsigned char kind;                 /* 0x18 */
    unsigned char flag;                 /* 0x19 */
    unsigned short tag;                 /* 0x1A */
    char pad1[0x30 - 0x1C];
} Hit;

typedef struct Cam {
    char pad0[0x80];
    float x, y;
    char pad1[0x98 - 0x88];
    float f98;
    char pad2[0x2290 - 0x9C];
    char *ent;
} Cam;

typedef struct Level { char pad0[0x12]; unsigned char cur; } Level;
typedef struct Slot { char pad0[4]; unsigned char on; char pad1[0x70 - 5]; float f70; char pad2[0xE0 - 0x74]; } Slot;

extern Level D_00139568;
extern Slot D_00239BA0[];
extern Cam D_00189E20;
extern char D_00189EA0[];
extern char D_0018A560[];
extern int D_001A8CA0;
extern char D_001A8BD0[];
extern int D_001B23E0;
extern short D_001B23E8[], D_001B23F0[], D_001B23F8[], D_001B2400[];
extern float D_001B5200[];
extern char D_001B5340[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_001BAF98;
extern Tgt *D_001EE960[];
extern float D_00229150[][4], D_00229160[][4];
extern Vec P2[2][20] __asm__("D_00229170");
extern V4 D_002292A0;
extern float D_002293F0[];
extern Vec D_00229440[];
extern float D_00229580[];
typedef struct { V4 v[5]; } Node5;
extern Node5 D_002295C0[], D_002295D0[], D_002295E0[];

extern float D_001AEDF4 __attribute__((sda));
extern float D_001AEDF8 __attribute__((sda));
extern float D_001AEDFC __attribute__((sda));
extern float D_001AEE00 __attribute__((sda));
extern float D_001AEE04 __attribute__((sda));
extern float D_001AEE08 __attribute__((sda));
extern float D_001AEE0C __attribute__((sda));
extern float D_001AEE10 __attribute__((sda));
extern float D_001AEE14 __attribute__((sda));
extern float D_001AEE18 __attribute__((sda));
extern float D_001AEE1C __attribute__((sda));
extern float D_001AEE20 __attribute__((sda));
extern float D_001AEE24 __attribute__((sda));
extern float D_001AEE28 __attribute__((sda));
extern float D_001AEE2C __attribute__((sda));
extern float D_001AEE30 __attribute__((sda));
extern float D_001AEE44 __attribute__((sda));
extern float D_001AEE48 __attribute__((sda));
extern float D_001AEE88 __attribute__((sda));
extern float D_001AEE8C __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));

extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277F48(void *, int, char *, void *, float);
extern int func_00282948(void *);
extern int func_00282978(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002831B0(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern float *func_002AB1F0(void *);
extern float func_002ABB18(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002C2210(void *, int, int, int, int, void *, int, float, float, float);
extern void func_00300190(void *, void *);

void func_0030A348(Moby *self)
{
    int locked = D_00239BA0[D_00139568.cur].on != 0;
    float reach = D_001AEDF4 * 0.05f;
    Rope *st = self->rope;
    float v0[4] __attribute__((aligned(16)));
    float va[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float v60[4] __attribute__((aligned(16)));
    float v70[4] __attribute__((aligned(16)));
    float v80[4] __attribute__((aligned(16)));
    float v90[4] __attribute__((aligned(16)));
    float vA0[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float s2B0[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hb __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, nheld;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *t;
    int sn;
    float dist, ang, sa2, cs, sm, score, proj, fa, fb;
    float d0;
    float *ia, *ib;
    Tgt *ta, *tb;
    float length, blend;
    float amp, height, angle, old, cd, cm;
    int fa2;
    Tgt *ht;
    float *hinfo;
    float *tv, apj, *ainfo;
    short an;
    float bpj, *binfo;
    short bn;
    float ksize, kf, ks;
    int j1, j2;
    float *q;
    int spin, spin2;
    float tsize, cd2;
    Vec *prev;
    float proj2, cm2;
    int k;

    D_001AEE0C = func_00283B98(D_001AEE0C, D_001AEE10);
    D_001AEE14 = func_00283BE0(D_001AEE14, D_001AEE18);
    D_001AEE28 = func_00283B98(D_001AEE28, D_001AEE2C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            sn = 0;
            for (t = D_001EE960[0]; t != 0; t = D_001EE960[++sn]) {
                if (t != st->lockA && t != st->lockB) {
                    if (t != 0 && t->cls != 0 && t->cls->id == 5) {
                        if (t->kind != 0xFE) {
 if (t->kind != 0xFD) {
                            if (func_002AB1F0(t) != 0) {
                                func_00282CF0(v0, t->pos, st);
                                if (D_001A8CA0 != 0) {
                                    proj = func_00282DB0(v0, D_00189E20.ent + 0xE0);
                                    func_00282D30(va, D_00189E20.ent + 0xE0, proj);
                                    func_00282CF0(vb, v0, va);
                                    dist = func_00282DF0(vb);
                                } else {
                                    dist = func_00282E20(v0);
                                }
                                if (!(D_001AEDF4 < dist)) {
                                    ang = func_00283C80(D_001B5200[0x158 / 4], func_00283248(t->pos[0] - D_001B5200[0x140 / 4], t->pos[1] - D_001B5200[0x144 / 4]));
                                    if (!(D_001AEDFC < ang)) {
                                        sa2 = 0.0f;
                                        if (D_001A8CA0 != 0) {
                                            func_00282CF0(va, t->pos, D_00189EA0);
                                            proj2 = func_00282DB0(va, D_00189E20.ent + 0xE0);
                                            func_00282D30(vb, D_00189E20.ent + 0xE0, proj2);
                                            func_00282CF0(va, va, vb);
                                            cs = func_00282DB0(va, D_00189E20.ent + 0xC0);
                                            sm = func_00282DF0(va);
                                            if (sm != 0.0f) {
                                                sa2 = 1.5707964f - func_002831B0(cs / sm);
                                                goto tail;
                                            }
                                        } else {
                                            sa2 = func_00283C80(func_00283248(t->pos[0] - D_00189E20.x, t->pos[1] - D_00189E20.y), D_00189E20.f98);
                                        tail:
                                            if (!(D_001AEDF8 < sa2)) {
                                                fa = (D_001AEDFC - ang) / D_001AEDFC;
                                                fb = (D_001AEDF4 - dist) / D_001AEDF4;
                                                score = fa * D_001AEE8C + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = t;
                                                } else if (secondScore < score) {
                                                    second = t;
                                                    secondScore = score;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
}
                    }
                }
            }
        }
    }

    if (best != 0) {
        if (st->lockA != 0) {
            second = best;
        } else {
            st->u.s.h40 = 0;
            st->lockA = best;
            if (func_00282948(&D_001B23E0) != 0)
                D_001B23E0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = func_00282E48(st, best->pos);
        if (d0 < D_001AEDF4 && d0 + func_00282E48(best->pos, second->pos) < D_001AEDF4) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        ia = func_002AB1F0(st->lockA);
        ta = st->lockA;
        qcopy(v0, ta->pos);
        func_00282D30(va, (char *)ta + 0xE0, ia[4]);
        func_00282CC0(v0, v0, va);
        len = func_00282E48(st, v0);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        ib = func_002AB1F0(st->lockB);
        tb = st->lockB;
        qcopy(va, tb->pos);
        func_00282D30(vb, (char *)tb + 0xE0, ib[4]);
        func_00282CC0(va, va, vb);
        reach = (func_00282E48(v0, va) + len) * 0.05f;
    }
    if (locked)
        D_001AEE58 = 0x207F20;
    else
        D_001AEE58 = 0x7F2020;
    func_00282C88(vb);
    func_002A8C00(&hit1, self, 0x210000, vb, D_00239BA0[D_00139568.cur].f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    st->count = 0x14;
    func_00277F48(st, 0x10, D_00189E20.ent, &hit1, 0.3f);
    func_00282CF0(v60, st->b, st);
    func_00282F20(v60, v60, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        func_00282DD8(v70, v60, (char *)&D_00189E20 + 0x2C0);
        func_002ACEC0(v60, v60, v70, 0.17453295f);
    }
    got = 0;
    func_00282D30(v90, v60, reach);
    nheld = 0;
    qcopy(&P2[0][0], st);
    qcopy(&P2[1][0], st);
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_001AEE04 + (D_001AEE08 - D_001AEE04) * (func_00283CE0(i) * 0.05f);
        height = amp * func_00283198(func_002ABB18(D_001AEE0C + (float)i * D_001AEE00));
        height += func_002A78D8(D_001AEE44, D_001AEE48);
        old = D_002293F0[i];
        D_002293F0[i] = height;
        P2[0][i].f[2] = P2[0][i].f[2] - old;
        func_00300190(&P2[0][i], &P2[0][i]);
        func_00282CF0(v70, &P2[0][i], D_00229160[i]);
        func_00282D08(v80, v70, v90, 0.85f);
        cm = func_00282DF0(v80);
        if (cm == 0.0f) {
            prev = &P2[0][i - 1];
            qcopy(&P2[0][i], prev);
        } else {
            func_00282D30(v80, v80, reach / cm);
            func_00282CC0(&P2[0][i], D_00229160[i], v80);
            qcopy(v90, v80);
        }
        P2[0][i].f[2] = P2[0][i].f[2] + height;
        func_00282CF0(v70, &P2[0][i], D_00229160[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                func_00282CF0(s2B0, v0, &P2[0][i]);
                length = func_00282DF0(s2B0);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        cd = func_00283CE0(0x13 - i);
                        reach = length / cd;
                    } else {
                        blend = 0.1f;
                    }
                    func_00282D30(s2B0, s2B0, reach / length);
                    func_00282D08(v90, v90, s2B0, blend);
                }
            } else {
                if (i >= 10)
                    func_00282CF0(s2B0, va, &P2[0][i]);
                else
                    func_00282CF0(s2B0, v0, &P2[0][i]);
                length = func_00282DF0(s2B0);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if ((unsigned)(i - 5) < 5) {
                        blend = 0.7f;
                        cd = func_00283CE0(9 - i);
                        reach = length / cd;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        cd2 = func_00283CE0(0x13 - i);
                        reach = length / cd2;
                    } else {
                        blend = 0.2f;
                    }
                    func_00282D30(s2B0, s2B0, reach / length);
                    func_00282D08(v90, v90, s2B0, blend);
                }
            }
        }
        if (i < 10) {
            angle = func_002ABB18(D_001AEE14 + (float)i * D_001AEE1C);
            amp = D_001AEE20 * func_00283198(func_002ABB18(D_001AEE28 + (float)i * D_001AEE30));
            qcopy(&P2[1][i], &P2[0][i]);
            height = amp * func_00283198(angle) + func_002A78D8(0.0f, 0.1f);
            D_00229580[i] = height;
            P2[1][i].f[2] = P2[1][i].f[2] + height;
            {
                float bearing = func_00283B98(func_00283248(v70[0], v70[1]), 1.5707965f);
                {
                    float radial = D_001AEE24 * func_00283180(angle);
                    vA0[0] = func_00283180(bearing) * radial;
                    vA0[1] = func_00283198(bearing) * radial;
                    vA0[2] = 0.0f;
                    qcopy(&D_00229440[i], vA0);
                }
            }
            func_00282CC0(&P2[1][i], &P2[1][i], vA0);
        } else {
            fa2 = 0x15 - i;
            qcopy(&P2[1][i], &P2[0][i]);
            P2[1][i].f[2] = P2[1][i].f[2] + D_00229580[fa2];
            func_00282CC0(&P2[1][i], &P2[1][i], &D_00229440[fa2]);
            qcopy(vA0, &D_00229440[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            func_00282CF0(vb, &P2[0][i], D_001B5340);
            if (D_001A8CA0 != 0) {
                float cpj = func_00282DB0(vb, D_00189E20.ent + 0xE0);
                {
                    char *ax = D_00189E20.ent + 0xE0;
                    func_00282D30(s2B0, ax, cpj);
                    func_00282CF0(vb, vb, s2B0);
                }
            } else {
                *(int *)&vb[2] = 0;
            }
            cm2 = func_00282DF0(vb);
            if (cm2 == 0.0f)
                vb[2] = 1.0f;
            else
                func_00282D30(vb, vb, 1.0f / cm2);
            vb[3] = 5627.925f;
            qcopy(&hit1, vb);
            got = func_002761F8(D_00229150[i], &P2[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = D_001BAF98.hit;
                if (ht != 0) {
                    hinfo = func_002AB1F0(ht);
                    if (hinfo == 0) {
                        func_002A8E20(ht, &hit1);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        func_002A8E20(ht, &hit1);
                    } else {
                        got = 0;
                        held[nheld++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (got != 0) {
                    qcopy(&P2[0][i], D_001BAF98.pos);
                    st->count = i;
                    qcopy(st->b, D_001BAF98.pos);
                    if (D_001BAF98.hit == 0) {
                        st->lockA = 0;
                        st->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < nheld; n++)
        held[n]->f98 = held[n]->cls->f10;
    if (got == 0)
        qcopy(st->b, &D_002292A0);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hb.q;
        func_00282CF0(s2B0, st->lockA->pos, D_001B5340);
        if (D_001A8CA0 != 0) {
            apj = func_00282DB0(s2B0, D_00189E20.ent + 0xE0);
            func_00282D30(tv, D_00189E20.ent + 0xE0, apj);
            func_00282CF0(s2B0, s2B0, tv);
        } else {
            *(int *)&s2B0[2] = 0;
        }
        an = 5;
        func_00282F20(s2B0, s2B0, 1.0f);
        s2B0[3] = 5627.925f;
        func_002A8C00(&hb.a.r, self, 0x210000, s2B0, D_00239BA0[D_00139568.cur].f70);
        hb.a.r.flag = 3;
        hb.a.r.kind = 5;
        hb.a.r.tag = self->tag;
        func_002A8E20(st->lockA, &hb.a.r);
        ainfo = func_002AB1F0(st->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        st->u.s.h44 = an;
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        func_00282CF0(s2B0, st->lockB->pos, D_001B5340);
        if (D_001A8CA0 != 0) {
            bpj = func_00282DB0(s2B0, D_00189E20.ent + 0xE0);
            func_00282D30(hb.q, D_00189E20.ent + 0xE0, bpj);
            func_00282CF0(s2B0, s2B0, hb.q);
        } else {
            *(int *)&s2B0[2] = 0;
        }
        bn = 5;
        func_00282F20(s2B0, s2B0, 1.0f);
        s2B0[3] = 5627.925f;
        func_002A8C00(&hb.b.r, self, 0x210000, s2B0, D_00239BA0[D_00139568.cur].f70);
        hb.b.r.flag = 3;
        hb.b.r.kind = 5;
        hb.b.r.tag = self->tag;
        func_002A8E20(st->lockB, &hb.b.r);
        binfo = func_002AB1F0(st->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        st->u.s.h46 = bn;
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            qcopy(hb.q, st);
            ksize = 0.4f;
        } else {
            qcopy(hb.q, st->b);
            ksize = 0.5f;
        }
        if (func_00282978(&D_001B23E8[k]) != 0) {
            D_001B23E8[k] = D_001B23F8[k];
            D_001B23F0[k] = 0;
            angle0 = func_002A78D8(0.52359885f, 1.0471977f);
            angle1 = func_002A7878(-1.0471977f, 0.17453295f);
            func_00282D30(s2B0, v60, ksize);
            func_002ACEC0(s2B0, s2B0, D_0018A560, angle1);
            func_002ACEC0(s2B0, s2B0, D_0018A560 + 0x10, angle0);
            qcopy(&D_002295D0[k].v[0], hb.q);
            ks = 1.0f;
            func_00282CC0(&D_002295D0[k].v[1], hb.q, s2B0);
            for (j1 = 2; j1 < 5; j1++) {
                func_00282CF0(hb.q + 4, &D_002295C0[k].v[j1], D_001B5340);
                kf = func_002A7878(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                func_002ACEC0(s2B0, s2B0, hb.q + 4, kf);
                func_00282CC0(&D_002295D0[k].v[j1], &D_002295C0[k].v[j1], s2B0);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                func_00282CF0(q, &D_002295D0[k].v[j2], &D_002295C0[k].v[j2]);
                q[0] = q[0] + func_002A78D8(0.0f, 0.1f);
                q[1] = q[1] + func_002A78D8(0.0f, 0.1f);
                q[2] = q[2] + func_002A78D8(0.0f, 0.1f);
            }
            qcopy(&D_002295D0[k].v[0], hb.q);
            for (j2 = 1; j2 < 5; j2++)
                func_00282CC0(&D_002295D0[k].v[j2], &D_002295C0[k].v[j2], tmp[j2]);
            if (D_001B23E8[k] > D_001B2400[k])
                kf = func_00283CE0(D_001B23E8[k] - D_001B2400[k]);
            else
                kf = func_00283CE0(D_001B2400[k] - D_001B23E8[k]);
            kf = kf / func_00283CE0(0xF);
            D_001B23F0[k] = func_00283CF0((1.0f - kf) * 32.0f);
        }
    }
    {
        angle0 = func_002A78D8(0.52359885f, 1.0471977f);
        angle1 = func_002A7878(-0.52359885f, 1.0471977f);
        func_00282D30(s2B0, v60, D_001AEE88);
        func_002ACEC0(s2B0, s2B0, D_0018A560, angle1);
        func_002ACEC0(s2B0, s2B0, D_0018A560 + 0x10, angle0);
        spin = func_002A7820(1, 8);
        spin = func_002A77E0(2) != 0 ? -spin : spin;
        tsize = func_002A7878(0.2f, 0.6f);
        func_002C2210(st, 0xF, D_001AEE58 | 0x7F000000, 0, spin, s2B0, 1, tsize * 0.3f, tsize, 0.0f);
        func_002C2210(st, 0xF, 0x307F7F7F, 0, -spin, s2B0, 1, tsize * 0.15f, tsize * 0.5f, 0.0f);
        spin2 = func_002A7820(1, 8);
        spin2 = func_002A77E0(2) != 0 ? -spin2 : spin2;
        tsize = func_002A7878(0.15f, 3.0f);
        func_002C2210(st->b, 0xC, D_001AEE58 | 0x7F000000, 0, spin2, D_001A8BD0, 1, tsize * 0.1f, tsize, 0.0f);
    }
}
