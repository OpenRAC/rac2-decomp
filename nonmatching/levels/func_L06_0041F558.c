/* func_L06_0041F558 - 576 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Right size; every instruction sequence matches except one thing: the two
   func_002AEC48 calls share the constants 0.02f and 0.3f, and cc1 keeps them
   in callee-saved f21 (extra swc1 $f21 in the prologue, shifts everything).
   Retail rebuilds the constants (lui/ori/mtc1) before each call and saves
   only $f20. Need a spelling where the constants are not CSE'd across the
   call. Not found. */

/* replaces the INCLUDE_ASM marker in src/levels/06_notak/L06_0041DED8.c (default -G0 flags) */
extern void func_002AB8C0(void *, void *);
extern int func_00282978(short *);
extern float func_002A89A8(void *, int, float);
extern float func_00282C48(float);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_002B0990(void *, void *, float, int, int);

/* Per-frame update: ages the object, eases its height toward the ground and, when the target
   is in front and the object is in state 2, turns the aim blend toward it. */
void func_L06_0041F558(char *object)
{
    char *state = *(char **)(object + 0x68);
    float ground;
    float turn;
    char *blend;

    func_002AB8C0(object, state + 0x50);
    func_00282978((short *)(state + 0x24A));
    if (*(unsigned short *)(object + 0x96) <= 0xFFFE) {
        *(unsigned short *)(object + 0x96) = *(unsigned short *)(object + 0x96) + 1;
    }
    ground = func_002A89A8(object + 0x10, 0, 0.5f);
    if (func_00282C48(*(float *)(object + 0x18) - ground) < 10.0f) {
        func_002AA3A8((float *)(object + 0x18), (float *)(state + 0x49C), ground, 0.00083333341f,
                      0.010000001f, 0.18000001f);
        if (*(float *)(object + 0x18) < ground) {
            *(float *)(object + 0x18) = ground;
        }
    }
    if (func_00283BE0(*(float *)(object + 0xF8),
                      func_00283248(*(float *)(state + 0x200) - *(float *)(object + 0x10),
                                    *(float *)(state + 0x204) - *(float *)(object + 0x14))) <= 2.6179941f) {
        if (*(unsigned char *)(object + 0x95) == 2) {
            turn = func_00283BE0(func_00283248(*(float *)(state + 0x200) - *(float *)(object + 0x10),
                                               *(float *)(state + 0x204) - *(float *)(object + 0x14)),
                                 *(float *)(object + 0xF8));
            if (turn > 1.3962636f) {
                turn = 1.3962636f;
            } else if (turn < -1.3962636f) {
                turn = -1.3962636f;
            }
            *(float *)(state + 0x588) = turn * 0.75f;
            *(float *)(state + 0x508) = turn * 0.4f;
            blend = state + 0x4A0;
            func_002AEC48(object, blend, 1, 0.02f, 0.3f);
            func_002AEC48(object, state + 0x520, 2, 0.02f, 0.3f);
            func_002B0990(object, blend, 2.5f, 1, 1);
        }
    }
}
