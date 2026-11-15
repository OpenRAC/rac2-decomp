#include "include_asm.h"

#include "common.h"
extern unsigned char *D_001BAF98[];
extern char g_music_state[];
extern int snd_resume_music_stream(void);
extern void moby_set_byte_on_group(int, int);
extern void STUB_printf(const char *, ...);
extern char D_001B0238[];
extern int g_surface_height_tiles[] __attribute__((sda));
extern int D_001B22D8[] __attribute__((sda));
extern int SampleSurfaceHeightMap(float *, float *, float, float, float);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern int func_US2_0026F810(void);

void func_US2_0032AD60(char *self)
{
    unsigned char *target = D_001BAF98[0];
    char *state = *(char **)(self + 0x68);
    unsigned char *object;
    unsigned char *obj_state;
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
        obj_state = *(unsigned char **)(object + 0x68);
        if (obj_state != 0) {
            if (*(short *)(obj_state + 0x16) == 0) {
                *(int *)&result[0] = 0;
                if (mode != 2)
                    SampleSurfaceHeightMap(result, aux, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
                else
                    SampleSurfaceHeightMap(result, aux, *(float *)(state + 0x20), *(float *)(state + 0x24), *(float *)(state + 0x28));
                probe = *(char **)(object + 0x68);
                if (*(float *)(self + 0x18) > result[0] && *(float *)(probe + 0xC) == 0.0f) {
                    *(unsigned char **)(state + 0x48) = object;
                    *(int *)(state + 0x38) = 2;
                    return;
                }
                if (obj_state[0x14] == 0) {
                    RippleDisturb(g_surface_height_tiles[0], D_001B22D8[0], 1, *(float *)(self + 0x10), *(float *)(self + 0x14), 0.5f, -0.03f);
                    if (func_US2_0026F810() == 0) {
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
            STUB_printf(D_001B0238, *(short *)(object + 0xAA));
        }
        *(int *)(state + 0x38) = 1;
    } else {
        *(int *)(state + 0x38) = 0;
    }
}

