#include "names.h"
/* func_PAL_L03_003A7720, the PAL copy of func_L03_003A40A0: the same C, where the turn rates
 * 0.0017453294f and 0.20943955f become 0.0025132746f and 0.25132746f, and the particle time
 * D_L03_001AF510 is read through the 50 Hz scale (x * 5 + 2) / 6 at both of its uses. */
#include "include_asm.h"
#include "names.h"
typedef struct { float x, y, z, w; } SwitchVector;
typedef struct { char pad0[0x80]; float x,y; char pad1[0x2294-0x88]; int mode; } SwitchPlayer;
extern unsigned char g_hero_l03_state_block[] __attribute__((nosda));
extern unsigned char *g_moby_record_base __attribute__((sda));
extern int g_frame_l03_counter[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned char g_moby_group_flags[] __attribute__((nosda));
extern float g_swingshot_particle_scale __attribute__((sda));
extern int g_swingshot_particle_type __attribute__((sda));
extern float g_swingshot_particle_size __attribute__((sda));
extern float g_swingshot_offset_scale __attribute__((sda));
extern void set_moby_color(void *, int, int, int);
extern void global_record_reset(void *);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern void cam_update_aim_target_candidate(void *);
extern int moby_fuse_linked_objects(void *, void *, void *, int, int);

/* Updates a Swingshot node moby: sets it up, aims it at the hero, shoots sparks, and re-arms it when its trigger turns on. (PAL: 50 Hz turn rates and spark times) */
void swingshot_l03_node_update_pal(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *related;
    SwitchVector position;
    SwitchVector velocity;
    float angle, direction;
    int color, random;
    unsigned short flags;
    float *angle_pointer;
    int frame;
    switch (object[0x20]) {
    case 0:
        flags = *(unsigned short *)(object + 0x34) | 0x1000;
        *(unsigned short *)(object + 0x34) = flags;
        if (*(int *)(state + 0x30) != -1 ||
            (*(int *)(state + 0x3C) != -1 &&
             (related = g_moby_record_base + (*(int *)(state + 0x3C) << 8)) != 0 &&
             related[0x20] != 0xFE && related[0x20] != 0xFD)) {
            object[0x30] = 0xFF;
            *(unsigned short *)(object + 0x34) = flags | 0x41;
            object[0x20] = 2;
        } else {
            set_moby_color(object, 0xC0, 0xC0, 0xC0);
            global_record_reset(object);
            object[0x20] = 1;
        }
        break;
    case 1:
        if (*(short *)(object + 0xAA) == 0x323 /* moby class 803 */) {
            angle_pointer = (float *)(object + 0xF8);
            angle = mat_fast_helper_a(((SwitchPlayer *)g_hero_l03_state_block)->x - *(float *)(object + 0x10),
                                  ((SwitchPlayer *)g_hero_l03_state_block)->y - *(float *)(object + 0x14));
            math_approach_target_with_direction_mode(angle_pointer, angle, 0.0025132746f, 0.0025132746f, 0.25132746f, state + 0x38, 0);
            frame = g_frame_l03_counter[0];
            if ((frame & 1) && object[0x31]) {
                direction = 1.0f;
                if (frame & 4)
                    direction = -1.0f;
                vec_scale_to_length(&position, object + 0xD0, direction * g_swingshot_offset_scale);
                vec_scale_to_length(&velocity, &position, -2.0f / ((g_swingshot_particle_scale * 5.0f + 2.0f) * 0.16666667f));
                FastVecAdd(&position, &position, object + 0x10);
                color = FloatToInt((g_swingshot_particle_scale * 5.0f + 2.0f) * 0.16666667f) & 0xFF;
                random = math_random_int_below(0xFF) & 0xFF;
                part_spawn_hero_relative(&position, &velocity, g_swingshot_particle_type, color, random, 0, g_swingshot_particle_size);
            }
        }
        if (((SwitchPlayer *)g_hero_l03_state_block)->mode != 0x2B)
            cam_update_aim_target_candidate(object);
        break;
    case 2:
        if (g_moby_group_flags[*(int *)(state + 0x30) + g_current_map_index[0] * 16] == 0) {
            if (*(int *)(state + 0x3C) == -1)
                return;
            related = g_moby_record_base + (*(int *)(state + 0x3C) << 8);
            if (related && related[0x20] != 0xFE && related[0x20] != 0xFD)
                return;
        }
        *(unsigned short *)(object + 0x34) &= 0xFFBE;
        moby_fuse_linked_objects(object, object + 0x10, object + 0xF0, 0, 0);
        *(int *)(state + 0x30) = -1;
        object[0x20] = 0;
        break;
    default:
        break;
    }
}
