/* Superseded by src/levels/09_dobbo/L09_003FEAE8-g8.c, 30 October 2026.
 * Current local checks: US 1/1 and US2 1/1; canonical name absent in PAL.
 * The historical draft below split a 64-byte joint matrix into an undersized
 * buffer and a detached position. The C source uses the complete matrix and
 * its actual +0x30 position, canonical helpers and real pointer/int returns.
 * Keep the older measurement as history; it is not a current blocked claim.
 */
/* func_L09_003FEAE8 - 520 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Belongs in L09_003FEA48-g8.c. func_2EA750 decl there must be (float, void*,
   void*) (draft uses va arrays).
   Only diff (5 masked lines): `%` by D_2290 (gp): retail `lw v1,0x2290(gp)`
   divisor in v1 and `mfhi v0`; mine divisor v0, mfhi v1.
   Tried: !(x%y), 0==x%y, (s32) cast, local r = x%y, compare <=0, explicit
   zero test. */

extern float D_L09_001B11C0 __attribute__((sda));
extern float D_L09_001B11D0 __attribute__((sda));
extern s32 D_L09_001B1280 __attribute__((sda));
extern s32 D_L09_001B11B8 __attribute__((sda));
extern u8 D_L09_001B11C8 __attribute__((sda));
extern s32 D_L09_001B11C4 __attribute__((sda));
extern u16 D_L09_001B11CC __attribute__((sda));
extern float func_2EA668(char *a0, char *a1);
extern void func_30D830(char *a0, s32 a1, void *a2);
extern void func_2EA4A0(float *a0, char *a1, float *a2);
extern void func_3AE8C8(float *a0, char *a1, float *a2, s32 a3, s32 t0, float f12, float f13, float f14, float f15);
extern void func_35C830(s32 a0, s32 a1, char *a2);
extern s32 func_2EA140(char *a0);

void func_L09_003FEAE8(char *a0) {
    char *s2 = *(char **)(a0 + 0x68);
    char buf[0x30];
    float vb[4];
    float va[4];

    {
        if (*(u8 *)(s2 + 0x42B) != 0 && func_2EA668(s2 + 0x390, *(char **)(s2 + 0x150) + 0x10) < 3.0f) {
            *(s16 *)(s2 + 0x412) = 600;
            if (*(s16 *)(s2 + 0x426) == 0 && *(u8 *)(s2 + 0x428) == 0) {
                func_30D830(a0, *(u8 *)(s2 + 0x429) + 4, buf);
                if (*(u8 *)(s2 + 0x441) && func_2EA668(s2 + 0x140, s2 + 0x390) < 3.0f) {
                    func_2EA4A0(va, s2 + 0x140, vb);
                } else {
                    func_2EA4A0(va, s2 + 0x390, vb);
                }
                func_2EA750(D_L09_001B11C0 * 0.016666668f, va, va);
                func_3AE8C8(vb, a0, va, 1, 1, (float)*(u8 *)(s2 + 0x34), D_L09_001B11D0, 1.0f, 0.5f);
                if (*(u8 *)(s2 + 0x42A) % D_L09_001B1280 == 0)
                    func_35C830(D_L09_001B11B8, 0, a0);
                *(u8 *)(s2 + 0x429) ^= 1;
                *(u8 *)(s2 + 0x42A) += 1;
                *(u8 *)(s2 + 0x428) = D_L09_001B11C8;
                if (D_L09_001B11C4 < *(u8 *)(s2 + 0x42A)) {
                    *(u8 *)(s2 + 0x42A) = 0;
                    *(u16 *)(s2 + 0x426) = D_L09_001B11CC;
                }
            }
        } else if (*(u8 *)(s2 + 0x428) == 0) {
            if (func_2EA140(s2 + 0x42A) == 0)
                *(u8 *)(s2 + 0x428) = D_L09_001B11C8;
        }
    }
}
