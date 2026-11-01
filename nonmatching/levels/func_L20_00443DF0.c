/* 1 November 2026: still 2 words. Prototype float positions, w[2] = 0.0f, an int-array view, a struct w, a pointer local and a float local for 0.1666 all tie. Next: why sched2 puts the sw between the a0 and a1 moves. */
/* M33 2026-10-26: -frac2-hazard-labels closes the +0xA4 branch target (profile -O2 -G0 -ffunction-sections -frac2-hazard-labels). Left: 2 words, order only: before the func_00282F20 call retail emits sw $zero,0x28($sp) then daddu $a1,$s1 (a1 in the slot); here a1 then the store. Tried int/float zero, &w[0], pointer local, flags -g/-G8. In the permuter. */
/* Near miss, 2026-10-25 wave 10: 548 bytes expected, 548 produced, 0 of 1
   place (20_yeedil @0x00443DF0).  Two instructions differ:
   - +0xA4: retail `b` targets the nop at +0xB0 (offset 0xA), this C targets the
     comparison at +0xB4 (offset 0xB); same target, one label to the left.
   - +0x1D4: this C fills the func_00282F20 call delay slot with `sw $zero,0x28($sp)`
     and sets $a1 before the jal; retail stores the zero before the jal and puts
     `daddu $a1,$s1` in the delay slot.
   Everything else, including both clamps, the constant words and the whole
   vector tail, is byte-identical.  Next hypothesis: the `sw $zero,0x28($sp)` is
   a 4th-component store of the vector at $sp+0x20 written as a separate `s32`
   local (not an int cast on the float array), which may change the scheduler's
   choice of delay-slot instruction; and the +0xA4 label placement may follow
   from writing the negative clamp as an if/else whose `then` is empty.
   The float literals are one ulp above the obvious decimal on purpose: the
   assembler's decimal parser rounds 0.7853982f to 0x3F490FDB, and retail holds
   0x3F490FDC (pi/4), hence 0.78539825f; likewise 0.52359885f for 0x3F060A93. */

extern void func_L20_00443B60(char *, float *, float *, float *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282D30(float *, float *, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, char *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_L03_003D09D0(char *, int, float *, float *, float *, int, int, int);
extern char D_00188660[];

/* Quarter-turn quantiser: the aim snaps to +-pi/6 inside +-pi/4, and to
   +-pi/4 just beyond it.  The frame holds the aim vector, a scaled unit
   vector, the rotated result and the quantised angle. */
void func_L20_00443DF0(char *a0)
{
    char *s2 = a0;
    char *s4 = *(char **)(s2 + 0x68);
    float ang[4];
    float v[4];
    float w[4];
    float t;
    float f;

    t = 0.78539825f;
    func_L20_00443B60(s2, ang, v, &t);
    ang[2] = ang[2] + 1.0f;
    if (t < 0.0f) {
        if (t > -0.52359885f)
            t = -0.52359885f;
        else if (t < -0.78539825f)
            t = -0.78539825f;
    } else {
        if (t > 0.78539825f)
            t = 0.78539825f;
        else if (t < 0.52359885f)
            t = 0.52359885f;
    }
    f = func_00283B98(t, *(float *)(s2 + 0xF8));
    v[0] = func_00283180(f) * 0.16666667f;
    v[1] = func_00283198(f) * 0.16666667f;
    v[2] = -0.033333335f;
    if (func_002A77E0(2) != 0) {
        func_00282D30(w, v, 90.0f);
    } else {
        func_00282D30(w, v, func_002A7878(0.4f, 0.6f) * 180.0f);
    }
    func_00282CC0(w, w, ang);
    func_00282CF0(w, D_00188660, w);
    *(int *)&w[2] = 0;
    func_00282F20(w, w, 0.16666667f);
    func_L03_003D09D0(s2, 0, ang, v, w, 0xB4, 0x258, *(unsigned char *)(s4 + 0x36));
}
