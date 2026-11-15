#include "names.h"
#include "moby_classes.h"
/* func_L03_003A40A0 (716 bytes, 12 places). The turn call uses func_002AAA00's real prototype,
 * float (void *out, float, float, float, float, void *in, int), and func_L03_0043AC40 takes the
 * object. D_L03_001B2548 and D_001A79F0 are read in retail's absolute macro form (lui/lw into
 * one register): sda incomplete arrays read as [0]. The case 0 stores are written 0x30, 0x34,
 * 0x20, and the table index is the field plus the row. */
#include "include_asm.h"
#include "names.h"
typedef struct { float x, y, z, w; } SwitchVector;
typedef struct { char pad0[0x80]; float x,y; char pad1[0x2294-0x88]; int mode; } SwitchPlayer;
extern unsigned char D_L03_00189E20[] __attribute__((nosda));
extern unsigned char *D_L03_001B2A1C __attribute__((sda));
extern int g_frame_l03_counter[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned char D_0019B2E8[] __attribute__((nosda));
extern float D_L03_001AF510 __attribute__((sda));
extern int D_L03_001AF514 __attribute__((sda));
extern float D_L03_001AF518 __attribute__((sda));
extern float D_L03_001AF51C __attribute__((sda));
extern void set_moby_color(void *, int, int, int);
extern void global_record_reset(void *);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern void cam_update_aim_target_candidate(void *);
extern int moby_fuse_linked_objects(void *, void *, void *, int, int);

/* Updates a Swingshot node moby: sets it up, aims it at the hero, shoots sparks, and re-arms it when its trigger turns on. */
void swingshot_node_update(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *related;
    SwitchVector position;
    SwitchVector velocity;
    float angle, direction;
    int color, random;
    unsigned short flags;
    float *anglePointer;
    int row;
    int inputBits;
    switch (object[0x20]) {
    case 0:
        flags = *(unsigned short *)(object + 0x34) | 0x1000;
        *(unsigned short *)(object + 0x34) = flags;
        if (*(int *)(state + 0x30) != -1 ||
            (*(int *)(state + 0x3C) != -1 &&
             (related = D_L03_001B2A1C + (*(int *)(state + 0x3C) << 8)) != 0 &&
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
        if (*(short *)(object + 0xAA) == MOBY_CLASS_SWINGSHOT_NODE_2) {
            anglePointer = (float *)(object + 0xF8);
            angle = mat_fast_helper_a(((SwitchPlayer *)D_L03_00189E20)->x - *(float *)(object + 0x10),
                                  ((SwitchPlayer *)D_L03_00189E20)->y - *(float *)(object + 0x14));
            math_approach_target_with_direction_mode(anglePointer, angle, 0.0017453294713050127f, 0.0017453294713050127f, 0.20943955f, state + 0x38, 0);
            inputBits = g_frame_l03_counter[0];
            if ((inputBits & 1) && object[0x31]) {
                direction = 1.0f;
                if (inputBits & 4)
                    direction = -1.0f;
                vec_scale_to_length(&position, object + 0xD0, direction * D_L03_001AF51C);
                vec_scale_to_length(&velocity, &position, -2.0f / D_L03_001AF510);
                FastVecAdd(&position, &position, object + 0x10);
                color = FloatToInt(D_L03_001AF510) & 0xFF;
                random = math_random_int_below(0xFF) & 0xFF;
                part_spawn_hero_relative(&position, &velocity, D_L03_001AF514, color, random, 0, D_L03_001AF518);
            }
        }
        if (((SwitchPlayer *)D_L03_00189E20)->mode != 0x2B)
            cam_update_aim_target_candidate(object);
        break;
    case 2:
        if (D_0019B2E8[*(int *)(state + 0x30) + g_current_map_index[0] * 16] == 0) {
            if (*(int *)(state + 0x3C) == -1)
                return;
            related = D_L03_001B2A1C + (*(int *)(state + 0x3C) << 8);
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
