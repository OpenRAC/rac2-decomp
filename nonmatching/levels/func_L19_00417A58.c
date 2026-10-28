/* func_L19_00417A58 - 580 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Only 3 masked diff lines: retail orders `addiu s1,sp,0x70; addiu
   s2,sp,0x60; addiu s3,zero,0x13` (loop counter init last);
   mine emits s3 init first. Tried: `for(i=19;i>=0;i--)`, `i=19` before loop,
   `i-- >= 0` (worse, +1 insn). */

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern void func_30F0C8(char *a0, s32 a1, EffectVector *a2);
extern void func_2EBC08(float *a0, float *a1, float f12);
extern void func_2EB920(float *a0, float *a1, float *a2);
extern void func_2EB950(float *a0, float *a1, float *a2);
extern float func_3184A0(void);
extern void func_2EAA58(float *a0, s32 a1, s32 a2, s32 a3, float f12, float f13, float f14);
extern float func_318438(float lo, float hi);
extern s32 func_2ECA88(float f12);
extern void func_3184E8(float *a0, float f12, float f13);
extern void func_33D428(float *a0, float *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                        float f12, float f13, float f14);

void func_L19_00417A58(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    EffectVector m[4];
    EffectVector pos;
    EffectVector tmp;
    EffectVector dir;
    EffectVector vel;
    int i;

    func_30F0C8(a0, 0, m);
    qcopy(pos.value, m[3].value);
    func_2EBC08(tmp.value, m[0].value, 0.25f);
    func_2EB920(pos.value, pos.value, tmp.value);
    pos.value[2] += 2.0f;
    func_2EAA58(pos.value, 0x31, 0x60804020, 1, *(float *)(s1 + 0x228) * 2.0f, 0.08f, func_3184A0());
    func_2EAA58(pos.value, 0x31, 0x80808080, 1, *(float *)(s1 + 0x228) * 1.5f, 0.08f, func_3184A0());
    *(float *)(s1 + 0x228) += 0.03f;
    if (*(float *)(s1 + 0x228) < 1.15f) {
        i = 19;
        for (; i >= 0; i--) {
            s32 life = func_2ECA88(func_318438(2.0f, 5.0f));
            func_3184E8(vel.value, 2.5f, 3.0f);
            func_2EB920(vel.value, vel.value, pos.value);
            func_2EB950(dir.value, pos.value, vel.value);
            func_2EBC08(dir.value, dir.value, 0.05f);
            func_33D428(vel.value, dir.value, 0x1E, 0x804020, life, 0, 0x7F, 5,
                        func_3183D8(0.2f, 0.5f) * 211000.0f, 126000.008f, 0.0f);
        }
    }
}
