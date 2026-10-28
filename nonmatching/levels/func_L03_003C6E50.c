/* func_L03_003C6E50 - 448 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Goes at the end of L03_00399230-g8.c (it already declares D_L03_001B2A1C as
   u8 * sda; the draft uses an alias D_L03_001B2A1C_abs[] sda for retail's
   absolute lui/lw, and drops the duplicate func_2F0000 decl). 444 B vs 448 B.
   Open: register numbering (retail s0=state, s1=i, s2=s0+4 hoisted, s3=obj,
   s6=lui 0x1C hoisted); hoists of `s0+4` and `lui s6,0x1C` before the loop
   are not reproduced. Not tried: ids pointer local, base pointer local for
   D_9840. */

extern char *D_L03_001B2A1C_abs[] __attribute__((sda));
extern char *D_L03_001B2B0C[] __attribute__((sda));
extern int D_L03_001B1150 __attribute__((sda));
extern float D_L03_001B1154 __attribute__((sda));
extern float D_L03_001B1158 __attribute__((sda));
extern char D_L03_001B9840[];
extern s32 func_321988(char *a0, s32 a1);
extern void func_3C7AA0(char *a0, float *a1);
extern void func_2EEF78(float *a0);
extern float func_2EF190(float *a0, float *a1);
extern float func_2EF670(float a, float b);

void func_L03_003C6E50(char *a0, float *a1, float *a2)
{
    char *s0 = *(char **)(a0 + 0x68);
    char *s3 = D_L03_001B2A1C_abs[0] + (*(s32 *)s0 << 8);
    float v[4];
    s32 i;
    s32 sel;

    if (*(s32 *)(s0 + 0x30) == -1 || func_321988(s3 + 0x10, *(s32 *)(s0 + 0x10 + *(s32 *)(s0 + 0x30) * 4)) == 0) {
        for (i = 0; i < 3; i++) {
            if (i == *(s32 *)(s0 + 0x30))
                continue;
            if (*(s32 *)(s0 + 0x10 + i * 4) == -1)
                continue;
            if (func_321988(s3 + 0x10, *(s32 *)(s0 + 0x10 + i * 4)) != 0) {
                *(s32 *)(s0 + 0x30) = i;
                break;
            }
        }
    }
    sel = *(s32 *)(s0 + 0x30);
    D_L03_001B1150 = sel;
    qcopy(a1, D_L03_001B2B0C[0] + (*(s32 *)(s0 + 4 + sel * 4) << 7) + 0x30);
    qcopy(a2, D_L03_001B2B0C[0] + (*(s32 *)(s0 + 4 + sel * 4) << 7) + 0x70);
    func_3C7AA0(s3, v);
    func_2EEF78(a2);
    a2[1] = func_2F0000(-func_2EF670(func_2EF190(a1, v), v[2] - a1[2]), D_L03_001B1154 * 0.017453292f);
    a2[2] = func_2EF670(v[0] - a1[0], v[1] - a1[1]);
    *(float *)(D_L03_001B9840 + 0x3D4) = D_L03_001B1158;
    *(u8 *)(D_L03_001B9840 + 0x3E9) = 1;
    *(u8 *)(D_L03_001B9840 + 0x3E8) = 0;
}
