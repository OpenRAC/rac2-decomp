/* Nonmatching camera-region reconstruction, 2026-10-28. No C coverage credit.
 * Seven checks (including one syntax correction); US0/2. Retained diagnostic
 * profile -O2 -G0 -ffunction-sections -fno-gcse produces656/660B. Ordinary
 * pointer declarations656B; macro-addressed pointers648B; pure TI preset
 * copy652B; scoped float and unsplit edges644B; no-split668B. Narrow controls
 * were measured before the broad negative probe. No profile retained in config.
 * Remaining: tangent temporaries / absolute-store address lifetime, preset
 * table/current-index scheduling and destination/source register selection.
 * Reopen with independent original source/lifetime evidence.
 *
 * Observed link-time scalar at+0x174/+0x17C resolves4 in Barlow,11 in Joba
 * in both US releases; PAL catalogue absent. It is not dereferenced and no
 * ordinary allocation at either address is asserted. The existing source
 * convention is L00_00321878-g8.c's `(int)ref_L00_00321878_01` scalar limit.
 * Tables remain incomplete; each chosen32-byte record supplies16B position
 * and scalar at+0x18. This function has no local memory packet or vector.
 * 002ACBC8 returns int, reads complete16B position; 00283198/00283180 and
 * 002A7878 return float from their actual FP argument banks. 0027AB40 uses
 * no incoming arguments and defines no common scalar result. The complete
 * 0046D250 retail body, and actual0046CD68/0046D6A8 definitions, confirm void
 * actor/camera mutation contracts. No ignored result is falsely declared void.
 */

#include "common.h"
extern unsigned char *D_L04_001B1E84 __attribute__((sda));
extern unsigned char *D_L04_001B24DC __attribute__((sda));
extern int D_L04_001B1CB8 SDATA(D_L04_001B1CB8);
extern int D_L04_001B1CBC SDATA(D_L04_001B1CBC);
extern float D_L04_001B1CC0 SDATA(D_L04_001B1CC0);
extern int D_L04_001B1CC4 SDATA(D_L04_001B1CC4);
extern int D_L04_001B1CC8 SDATA(D_L04_001B1CC8);
extern float D_L04_001BDC30;
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_L04_002C6F00[], D_L04_002C7100[];
/* Scalar link-time symbol, never dereferenced. This declaration is an address
 * spelling for the existing relocation convention, not a data-object claim. */
extern unsigned char ref_L04_0046CFB8_00[];
extern int func_002ACBC8(const void *, int);
extern float func_002A7878(float, float), func_00283198(float), func_00283180(float);
extern void func_0027AB40(void);
extern void func_L04_0046CD68(void *, int);
extern void func_L04_0046D250(void *);
extern void func_L04_0046D6A8(void *);

void func_L04_0046CFB8(unsigned char *camera)
{
    unsigned char *record = *(unsigned char **)(D_L04_001B1E84 + *(short *)(camera + 0x84) * 32 + 0x1C);
    unsigned char *actor = D_L04_001B24DC + *(int *)(record + 0x60) * 256;
    int force = 0;
    int i;
    int *indices;
    float angle;
    if (actor[0x20] == 3) {
        D_L04_001B1CB8 = -1;
        indices = (int *)(record + 0x20);
        for (i = 0; i < 16; i++, indices++)
            if (*indices != -1 && func_002ACBC8(actor + 0x10, *indices)) D_L04_001B1CB8 = i;
        if (D_L04_001B1CB8 == -1) {
            if (D_L04_001B1CBC != -1) {
                if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                else D_L04_001B1CC4 = 1;
                func_L04_0046CD68(camera, 1);
                angle = 0.5621705651283264f;
                {
                float tangent = func_00283198(angle);
                tangent /= func_00283180(angle);
                D_L04_001BDC30 = tangent;
                }
                func_0027AB40();
                D_L04_001B1CC8 = 0;
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            force = 1;
        } else {
            if (D_L04_001B1CB8 != D_L04_001B1CBC) {
                if (func_002A7878(0.0f, 1.0f) < 0.65f) {
                    unsigned char *preset;
                    int selected = D_L04_001B1CB8;
                    unsigned char *destination = camera + 0x30;
                    D_L04_001B1CC8 = 1;
                    if (D_001A79F0 == 4 || (int)ref_L04_0046CFB8_00 == 40) preset = D_L04_002C6F00;
                    else preset = D_L04_002C7100;
                    preset += selected * 32;
                    qcopy(destination, preset);
                    D_L04_001B1CC0 = *(float *)(preset + 0x18);
                } else {
                    if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                    else D_L04_001B1CC4 = 1;
                    func_L04_0046CD68(camera, 1);
                    D_L04_001B1CC8 = 0;
                }
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            if (D_L04_001B1CC8) {
                float halfAngle = D_L04_001B1CC0 * 0.5f;
                float tangent = func_00283198(halfAngle);
                tangent /= func_00283180(halfAngle);
                D_L04_001BDC30 = tangent;
                func_0027AB40();
                func_L04_0046D6A8(camera);
            } else force = 1;
        }
    } else force = actor[0xBC] != 0;
    if (force) {
        func_L04_0046D250(camera);
        func_L04_0046D6A8(camera);
    }
}
