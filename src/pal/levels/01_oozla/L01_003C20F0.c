#include "include_asm.h"

#include "common.h"
extern int func_00282948(void *);
extern int func_002A7820(int, int);
typedef struct L01_003BE4D0_OBJ {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x68 - 0x21];
    struct L01_003BE4D0_STATE *f68;
    char pad6C[0x96 - 0x6C];
    unsigned short f96;
    char pad98[0xBC - 0x98];
    unsigned char fBC;
} L01_003BE4D0_OBJ;
typedef struct L01_003BE4D0_STATE {
    char pad0[0x114];
    int f114;
    char pad118[0x230 - 0x118];
    int timer230;
    char pad234[0x238 - 0x234];
    int timer238;
    int timer23C;
    char pad240[0x290 - 0x240];
    int f290;
} L01_003BE4D0_STATE;
extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A0488(void *, int, int, int);
extern int func_00283D38(unsigned int, unsigned int, float);

void func_PAL_L01_003C20F0(L01_003BE4D0_OBJ *obj)
{
    L01_003BE4D0_STATE *s = obj->f68;
    int red, green, blue;
    unsigned int target;
    int color;

    if (obj->fBC != 0) {
        obj->fBC = 0;
        if (s->timer238 < 167) {
            s->timer238 = ((s32)(func_002A7820(300, 360)) * 5 + 2) / 6;
        }
    }
    if (s->f114 != 1) {
        func_00282948(&s->timer238);
    }
    if (obj->f96 <= 0xFFFD) {
        obj->f96 = obj->f96 + 1;
    }
    func_00282948(&s->timer230);
    func_00282948(&s->timer23C);
    /* Pack the current colour as 0x80BBGGRR, then blend it towards the target. */
    func_002A04B8(obj, &red, &green, &blue);
    {
        unsigned int alpha_green = (green << 8) | 0x80000000u;
        unsigned int alpha_blue_green = (blue << 16) | alpha_green;
        color = alpha_blue_green | red;
    }
    if (s->f290 != 0 && obj->f20 < 9) {
        target = 0x8040E0F0;
        color = func_00283D38(color, target, 0.060000002f);
    } else {
        target = 0x00404040;
        color = func_00283D38(color, target, 0.096f);
    }
    red = color & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = (color >> 16) & 0xFF;
    func_002A0488(obj, red, green, blue);
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L01_003C2688);
