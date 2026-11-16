#include "include_asm.h"

#include "common.h"
extern void part_spawn_radial_emitters(char *);
extern void part_spawn_debris_pieces_pal(char *);
extern void object_ring_spin_update_pal(char *);
extern void *part_find_owned_effect_slot(char *, int, int);
extern int moby_count_group_not_in_state(int, int);
extern void moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void set_moby_color(char *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(char *);
extern int snd_play_from_global_bank(int, int, int);
extern void value_set_entry_by_index_pal(int, int);
extern char *moby_spawn_large_explosion_pal(char *, int, int, int, int, int, int, int, int, int, int, float);
extern void part_spawn_scaled_bolts_pal(char *, int, float);
extern void moby_mark_spawned(char *);
extern int g_machine_hit_counter;
extern int g_machine_hit_flag[] __attribute__((sda));
extern int D_L06_001B3758_gp SDATA(D_L06_001B3758);
extern int g_machine_destroyed_flag;
extern unsigned char g_item_enabled_flags[32] __attribute__((sda));
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

/* Runs a destructible machine: it waits until hit, then charges up and finally blows apart with a big effect. */
void destructible_machine_update_pal(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        part_spawn_radial_emitters((char *)moby);
        g_machine_hit_counter = 10;
        D_L06_001B3758_gp = 0;
        moby_set_state((char *)moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)moby, 0x4010000, 0) &&
            !moby_count_group_not_in_state(*(int *)(vars + 0x64), -1) &&
            !moby_count_group_not_in_state(*(int *)(vars + 0x68), -1) &&
            !moby_count_group_not_in_state(*(int *)(vars + 0x6C), -1) &&
            !moby_count_group_not_in_state(*(int *)(vars + 0x60), -1))
            moby_set_state((char *)moby, 3, -1);
        moby[0xA8] = 255;
        break;
    case 3:
        if (flag_set_first_pending((char *)moby)) {
            part_spawn_debris_pieces_pal((char *)moby);
            *(float *)(moby + 0x2C) *= .9f;
            set_moby_color((char *)moby, 255, 127, 127);
            *(unsigned short *)(moby + 0x34) |= 0x200;
            *(int *)(vars + 0x130) = 150;
            g_camera_state.speed = .02f;
            g_camera_state.limit = 150;
            g_camera_state.scale = .4f;
            g_camera_state.duration = 100;
            g_camera_state.timer = 0;
            PlayMobySound(0, 0, (char *)moby);
        }
        object_ring_spin_update_pal((char *)moby);
        if (g_machine_hit_counter < 127) ++g_machine_hit_counter;
        if (math_fast_float_d(vars + 0x130)) moby_set_state((char *)moby, 4, -1);
        break;
    case 4:
        if (flag_set_first_pending((char *)moby)) {
            PlayMobySound(1, 0, (char *)moby);
            if (!g_item_enabled_flags[17]) {
                g_item_enabled_flags[17] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index_pal(0x1233, -1);
                g_machine_destroyed_flag = 1;
            }
            moby_spawn_large_explosion_pal((char *)moby + 0x10, 1, 25, 20, 20, 20, 45, 1, 1, 1, 1, 7);
            part_spawn_scaled_bolts_pal((char *)moby, 20, 0);
            g_machine_hit_flag[0] = 1;
            g_camera_state.speed = .05f;
            g_camera_state.limit = 150;
            g_camera_state.scale = .05f;
            g_camera_state.duration = 100;
            g_camera_state.timer = 0;
            moby_mark_spawned((char *)moby);
        }
    }
}
