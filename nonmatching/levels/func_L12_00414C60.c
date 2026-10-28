/* func_L12_00414C60 - 528 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Existing sibling structs (GuardMoby/GuardVars) used. 516 vs 528 B: retail
   keeps a second saved pointer copy (daddu s3,s0,zero after func_00282CF0)
   for the second func_00282F20 / func_L09_003A06B0 calls and 'near' in s4;
   mine propagates the copy (q=p) so s3 is unused, and the nested slot-address
   order (addiu v0,s1,0x2F0; addu) differs. D_L12_001B1828 is read as int
   (divisor) and u16 (lhu) at the same gp offset; draft casts the int read. */

/* append to L12_004149B8-g8.c (existing flags), remove the INCLUDE_ASM marker in L12_004149B8.c */
extern f32 D_L12_001B1810 __attribute__((sda));
extern void *func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L09_003A06B0(void *, void *, float, void *);

/* Steers the guard along the move its bound helper is playing, once the helper's phase bit
   allows it. */
void func_L12_00414C60(void *object) {
    GuardMoby *moby = object;
    GuardVars *vars = moby->vars;
    int near = 1;
    int side;
    int bit;
    GuardMoby **slot;
    float sp0[4];
    float dir[4];
    float *p;
    float *q;

    if (!(func_00282E80(&moby->x, &vars->f200->x) < D_L12_001B1814))
        near = 0;
    if (vars->f2F8 != 0 && func_00282978((s16 *)&vars->f2E4) != 0) {
        side = (moby->f96 / *(s32 *)&D_L12_001B1828) & 1;
        bit = side ? 5 : 4;
        if ((*(u16 *)((char *)vars->f2F8 + 0x7C) >> bit) & 1) {
            if (func_L12_00414AB8(moby, 1, 0, vars->f30D != 0) != 0) {
                slot = &vars->f2F0[side];
                if (*slot != 0 && (*slot)->fAA == 0xD66 && (*slot)->state != 0xFE &&
                    (*slot)->state != 0xFD) {
                    vars->f2E4 = D_L12_001B1828;
                    func_0029FCC0(*slot, 0, sp0);
                    p = dir;
                    func_00282CF0(p, &vars->f1F0, sp0);
                    q = p;
                    func_00282F20(p, p, D_L12_001B1810 * 0.016666668f);
                    if (!near && !vars->f30D) {
                        if (dir[2] > 0.033333335f)
                            dir[2] = 0.033333335f;
                        else if (dir[2] < -0.033333335f)
                            dir[2] = -0.033333335f;
                    }
                    func_00282F20(q, q, D_L12_001B1810 * 0.016666668f);
                    func_L09_003A06B0(moby, q, (float)*(u8 *)((char *)vars + 0x34), sp0);
                }
            }
        } else {
            vars->f2E4 = D_L12_001B1828;
        }
    } 
}
