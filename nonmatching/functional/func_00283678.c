/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_00283678 - 32 bytes, 28 places (the boot and every level), retail at
   0x00283678: lq $1,0($a1) ; lq $2,0x10($a1) ; lq $3,0x20($a1) ;
   sq $1,0($a0) ; sq $2,0x10($a0) ; sq $3,0x20($a0) ; jr $ra ; nop.
   The MMI lq/sq words carry their base register in bits 25-21, their quad
   register in bits 20-16 and their offset in bits 10-0, so the body is a
   48-byte copy from $a1 to $a0 - two pointer arguments, not three.
   The candidate below is that copy, but three things differ: this cc1
   allocates the quad registers $2, $3 and $6 instead of $1, $2 and $3; it
   emits the loads and the stores in another order (with
   -fno-schedule-insns the order comes out right); and it sinks the last
   store into the `jr $ra` delay slot instead of leaving a nop there.
   Current-master rechecks (28 October 2026): the retained ordinary-C form is
   still 28 bytes, 0/28. `-fno-schedule-insns` restores retail's load/store
   order and 32-byte extent only when a temporary volatile destination was
   used, but the quad registers still allocate as $v0/$v1/$a2 rather than
   $at/$v0/$v1. That volatile destination describes ordinary object memory
   falsely and is not a permissible source method; do not retain it. Other
   ordinary pointer/aggregate lifetime orderings tested here keep the same
   register set or reorder the transfers. A 29 October whole-aggregate assignment
   using an aligned three-word `mode(TI)` struct compiled to 52 bytes, 0/28: cc1
   lowered it to six 64-bit `ld`/`sd` transfers plus return, missing the retail
   qword operations. A 29 October probe using three calls to the reviewed
   `qcopy` helper in a dedicated unit emits 48 bytes, 0/28. The helper expands
   each copy into one `lq`/`sq` pair using `$v0`, computes each offset between
   pairs, and therefore cannot reproduce retail's three loads followed by
   three stores with quad registers `$at`/`$v0`/`$v1`. No exact match. */
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;

void func_00283678(void *a0, void *a1) {
    TI128 t0, t1, t2;
    t0 = *(TI128 *)a1;
    t1 = *(TI128 *)((u8 *)a1 + 0x10);
    t2 = *(TI128 *)((u8 *)a1 + 0x20);
    *(TI128 *)a0 = t0;
    *((TI128 *)((u8 *)a0 + 0x10)) = t1;
    *((TI128 *)((u8 *)a0 + 0x20)) = t2;
}
