#include "names.h"
/* func_PAL_L19_00428CC0, the PAL copy of func_L19_00423548: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L19_00423270 becomes func_PAL_L19_004289C0; rename func_002B0A18 becomes func_PAL_002B1588; wrap *(float *)(*(u8 **)(object + 0x24) + 0x24) (({e}) * 1.2. */
#include "common.h"

extern int g_current_map_index[] __attribute__((sda));
extern char g_hero_position[];
extern float D_L19_001B1EB0 __attribute__((sda)), D_L19_001B1EB4 __attribute__((sda));
extern float D_L19_001B1EB8 __attribute__((sda)), D_L19_001B1EBC __attribute__((sda));
extern float D_L19_001B1EC0 __attribute__((sda)), D_L19_001B1EC4 __attribute__((sda));
extern float D_L19_001B1EC8 __attribute__((sda));
/* The hero: its state word and another mode word. */
typedef struct {
    char pad0[0x2294];
    int state;
    int pad2298;
    int mode;
} HeroModes;
extern HeroModes g_hero_state;
extern u8 D_0019B4A8[];
/* Player stats: the pending bolt credit at +0x1C. */
typedef struct { u8 pad0[0x1C]; int pendingBolts; } PlayerStats;
extern PlayerStats D_001A7A00 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L19_001A903C[] MACRO_ADDR;
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_L19_004289C0(void *);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern float vec_length_xy(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int text_sum_subtitle_lengths(void);
extern void func_PAL_002B1588(int, int);

void func_PAL_L19_00428CC0(u8 *object)
{
    float direction[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    float distance, movement, threshold;
    switch (object[0x20]) {
    case 0:
        object[0x23] = 0x80;
        *(u32 *)(object + 0x78) = 0xFFAAAAAA;
        *(u16 *)(object + 0x34) |= 0x800;
        object[0x20] = 1;
        if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 0);
        break;
    case 1:
        if (vec_distance_xy(object + 0x10, g_hero_position) < D_L19_001B1EB0 &&
            math_fabs(*(float *)(object + 0x18) - *(float *)(g_hero_position + 8)) < D_L19_001B1EC0) {
            *(float *)state = D_L19_001B1EC4;
            if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 20);
            *(float *)(object + 0x48) = *(float *)state + *(float *)state;
            object[0x20] = 2;
        }
        if (object[0x31]) func_PAL_L19_004289C0(object);
        break;
    case 2:
        if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 20);
        *(float *)state += (1.0f - *(float *)state) * D_L19_001B1EBC;
        *(float *)(object + 0x48) = *(float *)state + *(float *)state;
        FastVecSub(direction, g_hero_position, object + 0x10);
        direction[2] += 0.6f;
        distance = vec_length_xy(direction);
        threshold = 0.12f;
        if (*(int *)(g_hero_position + 0x2214) != 0x31)
            movement = D_L19_001B1EB4 * (*(float *)state * 0.020000001f);
        else {
            movement = D_L19_001B1EB8 * (*(float *)state * 0.020000001f);
            threshold = 0.8f;
        }
        vec_fast_divide_helper(direction, direction, movement);
        FastVecAdd(object + 0x10, object + 0x10, direction);
        if (*(float *)(object + 0x2C) > 0.1f || distance < threshold || distance < movement)
            *(float *)(object + 0x2C) -= D_L19_001B1EC8 * ((*(float *)(*(u8 **)(object + 0x24) + 0x24)) * 1.2f);
        if ((distance < movement &&
             *(float *)(object + 0x2C) < *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.01f) ||
            g_hero_state.mode == 0x14 || g_hero_state.mode == 0x19 ||
            g_hero_state.state == 0x39 || g_hero_state.state == 0x6F) {
            if (*(u8 **)(state + 4)) {
                u8 *linked = *(u8 **)(state + 4);
                int h = *(unsigned short *)(linked + 0xB2);
                if (h & 1) {
                    unsigned char *e = &D_0019B4A8[((short)h >> 1) + (g_current_map_index[0] << 10)];
                    if (((*e >> 4) & 7) != 7) {
                        *e += 0x10;
                    }
                } else {
                    unsigned char *e = &D_0019B4A8[((short)h >> 1) + (g_current_map_index[0] << 10)];
                    if ((*e & 7) != 7) {
                        *e += 1;
                    }
                }
                moby_mark_spawned(*(u8 **)(state + 4));
            }
            D_001A7A00.pendingBolts++;
            snd_play_from_class_bank(3, 0, object, 0x11C7);
            moby_mark_spawned(object);
            if (!text_sum_subtitle_lengths() && !D_001A7A60[6]) {
                D_001A7A60[6] = 1;
                snd_play_from_global_bank(1, 0, 0);
                func_PAL_002B1588(0x1233, -1);
                D_L19_001A903C[0] = 1;
            }
            moby_mark_spawned(object);
        } else func_PAL_L19_004289C0(object);
        break;
    }
}
