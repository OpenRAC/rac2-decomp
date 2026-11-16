#include "include_asm.h"

#include "common.h"
extern int math_fast_float_d(void *);
extern int math_random_int_range(int, int);
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
extern void get_moby_color(void *, int *, int *, int *);
extern void set_moby_color(void *, int, int, int);
extern int FastTweenColor(unsigned int, unsigned int, float);

/* Counts down the moby's timers and fades its colour towards the glow colour or back to dark (PAL: 50 Hz timings). */
void firefly_update_timers_and_color_pal(L01_003BE4D0_OBJ *moby)
{
    L01_003BE4D0_STATE *state = moby->f68;
    int red, green, blue;
    unsigned int target;
    int color;

    if (moby->fBC != 0) {
        moby->fBC = 0;
        if (state->timer238 < 167) {
            state->timer238 = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
        }
    }
    if (state->f114 != 1) {
        math_fast_float_d(&state->timer238);
    }
    if (moby->f96 <= 0xFFFD) {
        moby->f96 = moby->f96 + 1;
    }
    math_fast_float_d(&state->timer230);
    math_fast_float_d(&state->timer23C);
    /* Pack the current colour as 0x80BBGGRR, then blend it towards the target. */
    get_moby_color(moby, &red, &green, &blue);
    {
        unsigned int alpha_green = (green << 8) | 0x80000000u;
        unsigned int alpha_blue_green = (blue << 16) | alpha_green;
        color = alpha_blue_green | red;
    }
    if (state->f290 != 0 && moby->f20 < 9) {
        target = 0x8040E0F0;
        color = FastTweenColor(color, target, 0.060000002f);
    } else {
        target = 0x00404040;
        color = FastTweenColor(color, target, 0.096f);
    }
    red = color & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = (color >> 16) & 0xFF;
    set_moby_color(moby, red, green, blue);
}

