#include "include_asm.h"

#include "common.h"
typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *g_moby_l01_table __attribute__((sda));
extern u8 *g_path_l01_table[] NOT_SDA;
extern f32 vec_distance_xy(void *, void *);
extern s32 point_in_path_xy(void *, void *, s32);
extern f32 math_random_float_range(f32,f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern s32 coll_sweep_from_object(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 coll_cast_object_line(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(f32);
extern u8 *part_spawn_trail(void *, void *, void *, u32, u32, s32, s32, s32, s32);
extern s32 moby_l01_turn_toward_target(void *, void *);
extern f32 func_310648();
extern f32 func_310580(f32 x, f32 y);
extern s32 func_310528(s32 a, s32 b);
extern f32 func_2E3A48(f32 x);
extern f32 func_2E3A60(f32 x);
extern s32 coll_process_hit(f32 radius, void *pos, s32 flag, void *obj, s32 arg);
extern u32 g_contact_moby_list[];
extern s32 math_fast_float_d(void *);
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FloatToInt(f32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
typedef struct { u8 pad[0x80]; f32 position[4]; u8 pad90[0x2AC]; u8 *object; s32 active; } PlayerECC;
extern PlayerECC g_hero_state;
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_nibble_table[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState g_level_save_state_backup;
extern u8 *g_camera_path_configs __attribute__((sda));
extern s32 cam_is_hero_in_trigger(void *);

/* Pulses the object's grey colour until the player touches it (save nibble counter at
   D_0019B4A8) or its id is already collected; then marks it and its linked record active
   and plays sound 0x8A1 once. */
void collectible_marker_update_pal(u8 *moby) {
    f32 position[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 distance;
    s32 shade;
    u16 moby_id;
    u32 color;
    if (!vars) return;
    *(f32 *)(vars + 4) = FastAddRotations(*(f32 *)(vars + 4), 0.12566373f);
    if (moby[0x20] == 0) {
        moby_transform_joint_to_world(moby, 0, position);
        distance = vec_distance_xy(g_hero_state.position, position);
        *(s32 *)(vars + 8) = 0;
        if (g_hero_state.object == moby && g_hero_state.active && distance < 0.5f) {
            u16 object_id;
            object_id = *(u16 *)(moby + 0xB2);
            if (object_id & 1) {
                if (((g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index[0] << 10)] >> 4) & 7) != 7)
                    g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index[0] << 10)] += 16;
            } else {
                if ((g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index[0] << 10)] & 7) != 7)
                    g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index[0] << 10)] += 1;
            }
        }
        if (moby[0xB0] != 255) {
            s32 nibble;
            moby_id = *(u16 *)(moby + 0xB2);
            if (g_level_save_state_backup.collected[(s16)moby_id] != 0) goto activate;
            nibble = g_moby_nibble_table[((s16)moby_id >> 1) + (g_current_map_index[0] << 10)];
            if ((moby_id & 1) ? ((nibble >> 4) & 7) : (nibble & 7)) {
activate:
                moby[0x20] = 1;
                moby[0xBC] = 1;
                if (*(s32 *)vars != -1) g_moby_l01_table[*(s32 *)vars].data[0xBC] = 1;
            }
        }
        shade = FloatToInt((math_fast_sin_or_cos_b(*(f32 *)(vars + 4)) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        color = (shade << 8) | 0x80000000;
        *(u32 *)(moby + 0x78) = (shade << 16) | color | shade;
    } else {
        if (!*(s32 *)(vars + 8)) {
            snd_play_from_class_bank(0, 0, moby, 0x8A1);
            *(s32 *)(vars + 8) = 1;
        }
        *(u32 *)(moby + 0x78) = 0x80208010;
    }
}

