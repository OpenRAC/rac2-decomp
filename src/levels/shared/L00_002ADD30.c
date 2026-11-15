#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* the hero and the pad words, through byte views */
typedef union { u8 b[0x2600]; } Hero_002ADD30;
typedef union { u8 b[0x400]; } Pad_002ADD30;

extern u8 D_00189E20[];
extern u8 D_00138180[];

#define HERO(o, t) (*(t *)&hero->b[(o)])
#define HEROD(o, t) (*(t *)&((Hero_002ADD30 *)D_00189E20)->b[(o)])

extern void func_L00_002ADCF8(void *);

/* the ledge probe, a different routine in level 11 */
extern s32 ref_L00_002ADD30_00(void *, void *, void *, void *, void *, void *, void *, s32, s32);

/* Looks for a ledge in front of the hero while he jumps, climbs or swings; one within the
   reach band (lower with the pad's bit 7) is latched with its position and the probe's
   results. */
/* While the hero is in the air or climbing, looks for a ledge nearby and remembers it if it is in reach. */
void func_L00_002ADD30(void)
{
    f32 from[4];
    f32 at[4];
    f32 *ledge;
    s32 a;
    s32 b;
    f32 c;
    s32 d;
    s32 state;
    f32 rise;
    f32 low;
    Hero_002ADD30 *hero = (Hero_002ADD30 *)gHeroState;

    HERO(0x6EC, s32) = 0;
    if (HERO(0x204, s16) != 0)
        return;
    GetHeroOffsetVector(from);
    state = HERO(0x229C, s32);
    if ((state == 4 && HERO(0x49E, u8) == 0) || state == 2 || state == 0xF) {
        ledge = at;
        if (ref_L00_002ADD30_00(from, &a, ledge, &b, &c, &d, 0, 0, 0) != 0) {
            rise = from[2] - at[2];
            low = -0.7f;
            if (*(u32 *)&((Pad_002ADD30 *)gPadState)->b[0x1A4] & 0x80)
                low = -1.2f;
            if (low < rise && rise < 0.4f) {
                Hero_002ADD30 *h;

                qcopy(&HEROD(0x6D0, TI128), ledge);
                h = (Hero_002ADD30 *)gHeroState;
                *(s32 *)&h->b[0x6E0] = a;
                *(s32 *)&h->b[0x6E4] = b;
                *(f32 *)&h->b[0x6E8] = c;
                *(s32 *)&h->b[0x6FC] = d;
                *(s32 *)&h->b[0x6EC] = 1;
            }
        }
    }
}
