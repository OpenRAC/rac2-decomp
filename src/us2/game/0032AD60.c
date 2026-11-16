#include "include_asm.h"

#include "common.h"
extern unsigned char *g_hit_result[];
extern char g_music_state[];
extern int snd_resume_music_stream(void);
extern void moby_set_byte_on_group(int, int);
extern void STUB_printf(const char *, ...);
extern char g_str_hero_under_falling_debug[];
extern int g_surface_height_tiles[] __attribute__((sda));
extern int g_surface_box_count[] __attribute__((sda));
extern int SampleSurfaceHeightMap(float *, float *, float, float, float);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern int actuator_calc_power_us2(void);

/* Checks whether a falling object is above a surface-grid object and records on it whether it landed, sinking or was over water (v2.00 copy). */
void hero_check_under_falling_object_us2(char *moby)
{
    unsigned char *target = g_hit_result[0];
    char *state = *(char **)(moby + 0x68);
    unsigned char *object;
    unsigned char *object_vars;
    char *probe;
    float aux[4];
    float result[4];
    char *context;
    int mode;

    if (target == 0) {
        if (*(int *)(state + 0x38) != 2)
            return;
    }
    mode = *(int *)(state + 0x38);
    object = target;
    if (mode == 2)
        object = *(unsigned char **)(state + 0x48);
    if (*(short *)(*(char **)(object + 0x24) + 0x46) == 18) {
        object_vars = *(unsigned char **)(object + 0x68);
        if (object_vars != 0) {
            if (*(short *)(object_vars + 0x16) == 0) {
                *(int *)&result[0] = 0;
                if (mode != 2)
                    SampleSurfaceHeightMap(result, aux, *(float *)(moby + 0x10), *(float *)(moby + 0x14), *(float *)(moby + 0x18));
                else
                    SampleSurfaceHeightMap(result, aux, *(float *)(state + 0x20), *(float *)(state + 0x24), *(float *)(state + 0x28));
                probe = *(char **)(object + 0x68);
                if (*(float *)(moby + 0x18) > result[0] && *(float *)(probe + 0xC) == 0.0f) {
                    *(unsigned char **)(state + 0x48) = object;
                    *(int *)(state + 0x38) = 2;
                    return;
                }
                if (object_vars[0x14] == 0) {
                    RippleDisturb(g_surface_height_tiles[0], g_surface_box_count[0], 1, *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.03f);
                    if (actuator_calc_power_us2() == 0) {
                        object[0xBC] += 1;
                        if (object[0xBC] >= 25) {
                            context = g_music_state;
                            if (*(short *)(context + 0x72) == 3 && *(short *)(context + 0x6C) < 6000)
                                snd_resume_music_stream();
                        }
                        if (object[0x21] != 255)
                            moby_set_byte_on_group(object[0x21], object[0xBC]);
                    }
                }
                *(int *)(state + 0x44) = 0;
            } else {
                *(int *)(state + 0x44) = 1;
            }
        } else {
            STUB_printf(g_str_hero_under_falling_debug, *(short *)(object + 0xAA));
        }
        *(int *)(state + 0x38) = 1;
    } else {
        *(int *)(state + 0x38) = 0;
    }
}

