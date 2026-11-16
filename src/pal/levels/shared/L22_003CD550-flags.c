#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
typedef int s32;

/* func_PAL_L22_003CD550, the PAL copy of func_L22_003C9880: the same C, where the rate
 * becomes 1/50, the phase step 0.0003490659f, the 1080 window 900, and every read of the
 * clock D_001A7390 is scaled to 50 Hz.  The window test reads history[31].time after the
 * scaling (retail's load follows the division's zero check), not through a local. */
extern float g_spark_rate_min[] __attribute__((sda));
extern float g_spark_value_min[] __attribute__((sda));
extern int g_spark_color_pair[] __attribute__((sda));
extern int D_L22_001AFF18_gp[] __asm__("D_L22_001AFF18__gp") __attribute__((section(".sdata")));
extern float g_spark_angle_scale[] __attribute__((sda));
extern float g_hero_action_float_param[] __attribute__((sda));
extern unsigned int g_frame_counter[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));

/* The per-subtitle history src/game/00289178.c updates (12-byte rows). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory g_subtitle_history[];

extern void moby_set_state(void *, int, int);
extern f32 math_random_float_range(f32 low, f32 high);
extern int PlayMobySound(int index, int a1, char *a2);
extern int subtitle_request_voice_line(int, int);
extern f32 FastVecDot(void *, void *);
extern void func_PAL_L22_003CD898(char *);
extern void spark_lane_draw(u8 *);
extern void gfx_add_draw_callback_first(void (*)(u8 *), void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern int FastTweenColor(int, int, f32);
extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *a0, void *a1);

void func_PAL_L22_003CD550(u8 *obj)
{
    u8 *ctl = *(u8 **)(obj + 0x68);
    int state = obj[0x20];
    int i;

    switch (state) {
    case 0:
        moby_set_state(obj, 1, -1);
        *(short *)(obj + 0x32) = 255;
        {
            float *offset, *rate, *radius;
            i = 0;
            radius = (float *)(ctl + 0x10);
            rate = (float *)(ctl + 0x30);
            offset = (float *)(ctl + 0x20);
            for (; i < 4; i++) {
                *offset++ = (float)i * 0.25f;
                *rate++ = math_random_float_range(g_spark_rate_min[0], g_spark_rate_min[1]) * 0.020000001f;
                *radius++ = math_random_float_range(g_spark_value_min[0], g_spark_value_min[1]);
            }
        }
        break;
    case 1: {
        u8 *player;
        SubtitleHistory *history;

        if (fast_vec_dist(g_hero_state + 0x80, obj + 0x10) < 3.0f)
            g_hero_action_float_param[0] = *(float *)ctl;
        player = g_hero_state;
        if (*(int *)(player + 0x2294) == 0x81 && *(int *)(player + 0x1B8) == state)
            PlayMobySound(0, 0, (char *)obj);
        history = g_subtitle_history;
        {
            /* unsigned int snapshot: retail tests the u16 with an andi and
             * increments the unmasked value */
            unsigned int count = history[31].count;
            if ((unsigned short)count <= 65534) {
                u8 *player2 = g_hero_state;
                if (*(int *)(player2 + 0x2294) == 0x81)
                    history[31].count = 65535;
                else if (*(u8 **)(player2 + 0x33C) == obj) {
                    /* each arm reads the clock itself: reorg merges the two
                     * reads into the branch's delay slot */
                    if ((unsigned short)count != 0) {
                        if (((s32)g_frame_counter[0] * 5 + 2) / 6 - history[31].time > 900 || history[31].time == 0)
                            subtitle_request_voice_line(2504, 31);
                        else if (history[31].time < ((s32)g_frame_counter[0] * 5 + 2) / 6)
                            history[31].time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
                    } else {
                        history[31].count = count + 1;
                        if (history[31].time < ((s32)g_frame_counter[0] * 5 + 2) / 6)
                            history[31].time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
                        history[31].levels =
                            (history[31].levels | (1 << g_current_map_index[0])) | 0x80000000;
                    }
                }
            }
        }
        if (FastVecDot(obj + 0xE0, g_hero_state + 0x2C0) < -0.6f) {
            func_PAL_L22_003CD898((char *)obj);
            gfx_add_draw_callback_first(spark_lane_draw, obj);
        }
        break;
    }
    }
    if (obj[0x31]) {
        float f;
        *(float *)(ctl + 4) = FastAddRotations(*(float *)(ctl + 4),
                                            g_spark_angle_scale[0] * 0.0003490659f);
        f = math_fast_sin_or_cos_b(*(float *)(ctl + 4));
        f = f * f;
        f = f * f;
        *(int *)(obj + 0x78) = FastTweenColor(D_L22_001AFF18_gp[0], g_spark_color_pair[1], f * f);
    }
}

