/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G0 -ffunction-sections.
 * us: 09_dobbo: 1196 bytes, expected 1216; us2: ABSENT; pal: ABSENT.
 * Complete region monitor and persistent forty-entry enemy scan, including signed moby state
 * tests, its exceptional cursor-advance path, hint gates and time comparison. External data
 * extents remain open. Global-base allocation, countdown structure and modulo lowering differ.
 * Reopen: Independent global-base and scan-loop source witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(u32 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
extern u8 D_001395B8[],D_0018C958[],D_0018C750[],D_00189EA0[];
extern int D_001397C4;
extern u8 D_001A7A6C,D_001A7B0D,D_001A7B0F;
extern short D_001A7A18;
extern u32 D_001A7390;
extern int D_L09_001A9040,D_L09_001A903C;
extern u8 *D_L09_001B285C,*D_L09_001B2860;
extern int func_002ACBC8(void *,int),func_00288E18(int,int),func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);

/* Monitors four hero regions and incrementally counts the active enemy classes.
 * The forty-entry scan cursor and its accumulated count survive across calls.
 */
void func_L09_003E3288(u8 *object)
{
    u8 *state = P(object,0x68),*moby,*hero = D_00189EA0;
    int i,index,kind;
    if (object[0x20] == 0) {
        object[0x20] = 1; object[0x30] = 255; I(state,0x10) = 0;
        if (D_001395B8[0x7A] >= 126) D_001395B8[0x7A] = 125;
        if (D_001395B8[0x79] >= 126) D_001395B8[0x79] = 125;
        I(state,0x2C) = 0;
    }
    if (object[0x20] != 1) return;
    if (D_L09_001A9040 && !D_001A7A6C) {
        for (i = 39; i >= 0; i--) {
            index = I(state,0x58);
            moby = D_L09_001B285C + (index << 8);
            kind = S(moby,0xAA);
            if (kind == 0xD0F || kind == 0xD57 || kind == 0xD30 || kind == 0xCBC || kind == 0xD90) {
                if ((kind == 0xD30 && S(P(moby,0x68),0x3D6)) ||
                    (kind == 0xD0F && moby[0x20] == 5)) {
                    I(state,0x58) = index + 1;
                    continue;
                }
                if ((s8)moby[0x20] >= 0) I(state,0x5C)++;
            }
            I(state,0x58)++;
            if ((u32)(D_L09_001B285C + (I(state,0x58) << 8)) >= (u32)D_L09_001B2860) {
                if (!I(state,0x5C) && !D_001A7A6C) {
                    D_001A7A6C = 1;
                    func_002E5E58(1,0,0);
                    func_002B0A18(0x1233,-1);
                    D_L09_001A903C = 1;
                }
                I(state,0x58) = 0; I(state,0x5C) = 0;
            }
        }
    }
    if (!H(D_0018C958,0x42C) && D_001397C4 < 0 && !D_001A7B0D &&
        func_002ACBC8(hero,I(state,0))) func_00288E18(0xA02,0x59);
    if (func_002ACBC8(hero,I(state,4))) I(state,0x10) = 1;
    if (I(hero - 0x80,0x2294) == 57 && !I(hero - 0x80,0x1B8) && I(state,0x10))
        D_001395B8[0x7A]++;
    if (D_001A7A18 <= 0 && func_002ACBC8(hero,I(state,4)) &&
        (unsigned)D_001395B8[0x7A] % 5 == 4 && !I(state,0x1C) && I(hero,0x2214) != 57) {
        if (I(D_0018C958,0x3E0) >= 0) func_00288E18(0x9FB,0x52);
        I(state,0x1C) = 1; D_001395B8[0x7A]++;
    }
    if (func_002ACBC8(hero,I(state,8)) && I(hero - 0x80,0x2294) == 57 && !I(hero - 0x80,0x1B8))
        D_001395B8[0x79]++;
    if (!D_001A7B0F && func_002ACBC8(hero,I(state,8)) &&
        (unsigned)D_001395B8[0x79] % 5 == 4 && !I(state,0x18) && I(hero,0x2214) != 57) {
        if (I(D_0018C958,0x404) >= 0) func_00288E18(0x9FE,0x55);
        I(state,0x18) = 1; D_001395B8[0x79]++;
    }
    if (func_002ACBC8(hero,I(state,12)) &&
        (!H(D_0018C750,0x1BC) || D_001A7390 - U(D_0018C750,0x1C0) > 432000u) &&
        D_001395B8[0x7D] < 3 && !I(state,0x14)) {
        if (I(D_0018C958,0x2C0) >= 0) func_00288E18(0x9E3,0x3A);
        D_001395B8[0x7D]++; I(state,0x14) = 1;
    }
}
