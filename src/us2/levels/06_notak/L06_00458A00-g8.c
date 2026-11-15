#include "include_asm.h"

#include "common.h"
extern void part_spawn_radial_emitters(char *);
extern void part_spawn_debris_pieces(char *);
extern void object_ring_spin_update(char *);
extern int part_find_owned_effect_slot(char *, int, int);
extern int moby_count_group_not_in_state(int, int);
extern void moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void set_moby_color(char *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(char *);
extern void snd_play_from_global_bank(int, int, int);
extern void func_US2_002B1880(int, int);
extern void part_spawn_shockwave_burst(char *, int, int, int, int, int, int, int, int, int, int, float);
extern void part_spawn_scaled_bolts(char *, int, float);
extern void moby_mark_spawned(char *);
extern int D_L06_001B375C;
extern int D_L06_001B3758[] __attribute__((sda));
extern int D_L06_001B3758_gp SDATA(D_L06_001B3758);
extern int D_L06_001A903C;
extern unsigned char D_001A7A60[32] __attribute__((sda));
typedef struct {
    char pad[0x160];
    float scale;
    int pad164;
    int duration;
    int timer;
    char pad170[0x10];
    float speed;
    int pad184;
    int limit;
} EffectState;
extern EffectState g_camera_state;

void func_US2_L06_00458A00(unsigned char *obj)
{
    char *d = *(char **)(obj + 0x68);
    switch (obj[0x20]) {
    case 0:
        part_spawn_radial_emitters((char *)obj);
        D_L06_001B375C = 10;
        D_L06_001B3758_gp = 0;
        moby_set_state((char *)obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)obj, 0x4010000, 0) &&
            !moby_count_group_not_in_state(*(int *)(d + 0x64), -1) &&
            !moby_count_group_not_in_state(*(int *)(d + 0x68), -1) &&
            !moby_count_group_not_in_state(*(int *)(d + 0x6C), -1) &&
            !moby_count_group_not_in_state(*(int *)(d + 0x60), -1))
            moby_set_state((char *)obj, 3, -1);
        obj[0xA8] = 255;
        break;
    case 3:
        if (flag_set_first_pending((char *)obj)) {
            part_spawn_debris_pieces((char *)obj);
            *(float *)(obj + 0x2C) *= .9f;
            set_moby_color((char *)obj, 255, 127, 127);
            *(unsigned short *)(obj + 0x34) |= 0x200;
            *(int *)(d + 0x130) = 180;
            g_camera_state.speed = .02f;
            g_camera_state.limit = 180;
            g_camera_state.scale = .4f;
            g_camera_state.duration = 120;
            g_camera_state.timer = 0;
            PlayMobySound(0, 0, (char *)obj);
        }
        object_ring_spin_update((char *)obj);
        if (D_L06_001B375C < 127) ++D_L06_001B375C;
        if (math_fast_float_d(d + 0x130)) moby_set_state((char *)obj, 4, -1);
        break;
    case 4:
        if (flag_set_first_pending((char *)obj)) {
            PlayMobySound(1, 0, (char *)obj);
            if (!D_001A7A60[17]) {
                D_001A7A60[17] = 1;
                snd_play_from_global_bank(1, 0, 0);
                func_US2_002B1880(0x1233, -1);
                D_L06_001A903C = 1;
            }
            part_spawn_shockwave_burst((char *)obj + 0x10, 1, 25, 20, 20, 20, 45, 1, 1, 1, 1, 7);
            part_spawn_scaled_bolts((char *)obj, 20, 0);
            D_L06_001B3758[0] = 1;
            g_camera_state.speed = .05f;
            g_camera_state.limit = 180;
            g_camera_state.scale = .05f;
            g_camera_state.duration = 120;
            g_camera_state.timer = 0;
            moby_mark_spawned((char *)obj);
        }
    }
}
