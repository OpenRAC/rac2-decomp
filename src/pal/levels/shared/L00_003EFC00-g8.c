#include "include_asm.h"

#include "common.h"
extern int vec_fast_helper_b(void *);
extern int g_frame_l00_counter __attribute__((sda));
extern float D_L00_001B0748 __attribute__((sda));
extern float D_L00_001B074C __attribute__((sda));
extern float D_L00_001B0750 __attribute__((sda));
extern float D_L00_001B0754 __attribute__((sda));
extern float D_L00_001B0758 __attribute__((sda));
extern int D_L00_001A8F00[] MACRO_ADDR;
extern char D_L00_001B8FF0[];
extern char g_hero_position[];
extern char g_weapon_l00_table[][224];
typedef struct { char pad[0x1F]; unsigned char selected; } Selection3EB8E8;
extern Selection3EB8E8 g_item_slot_to_record;
extern unsigned char *D_L00_001FEA14 NOT_SDA;
extern char D_L00_001A8F20[] __attribute__((sda));
extern void moby_transform_joint_to_world(char *, int, void *);
extern char *moby_get_or_find_target(void *, void *, int, float, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern char *moby_get_private_value_0(char *);
extern int math_random_int_below(int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *func_PAL_L00_003F10D8(void *, char *, char *);
extern int PlayMobySound(int, int, char *);
extern float math_random_float_range(float, float);
typedef struct {
    char pad[0x24];
    unsigned char phase;
    unsigned char shots;
    char pad26[2];
    char *target;
    char pad2C[12];
    int slot;
    float cooldown;
} State3EB8E8;

void func_PAL_L00_003EFC00(char *self, State3EB8E8 *st)
{
    float pos[4], v[4], target[4], dir[4];
    char *obj, *part, *bone;
    int angle;
    float dot;
    char *entry;

    if (!vec_fast_helper_b(&st->cooldown) || g_frame_l00_counter % 4 != st->slot)
        return;
    moby_transform_joint_to_world(self, 1, pos);
    st->phase ^= 1;
    obj = moby_get_or_find_target(pos, D_L00_001B8FF0, 0, D_L00_001B074C * 0.01745329424738884f,
                            D_L00_001B0750 * 0.01745329424738884f, D_L00_001B0748,
                            D_L00_001B074C * 0.01745329424738884f, D_L00_001B0750 * 0.01745329424738884f);
    if (obj) {
        if ((*(short *)(obj + 0xAA) == 0xEE1 || *(short *)(obj + 0xAA) == 0xEC0 || *(short *)(obj + 0xAA) == 0xED4) &&
            *(unsigned char *)(*(char **)(obj + 0x68) + 0x3B1) == 255) {
            st->target = 0;
            return;
        }
        if (*(short *)(obj + 0xAA) == 0xEF4) {
            st->target = 0;
            return;
        }
        st->target = obj;
        if (*(unsigned char *)(self + 0x43) != 2)
            func_PAL_002A7E68(self, 2, 0, 4);
        FastVecSub(v, self + 0x10, g_hero_position);
        dot = FastVecDot(v, self + 0xE0);
        if (D_L00_001A8F00[0] != 2 && *(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
            *(unsigned char *)(self + 0x42) == 2 && dot > 1.1f) {
            qcopy_nc(target, obj + 0x10);
            bone = moby_get_private_value_0(obj);
            if (bone)
                target[2] += *(float *)(bone + 0x10);
            else
                target[2] += D_L00_001B0758;
            angle = math_random_int_below(255);
            part = part_spawn_gravity_fade(pos, D_L00_001A8F20, 2, 0x202080, angle, 127, 16, 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *D_L00_001FEA14;
            part = part_spawn_gravity_fade(pos, D_L00_001A8F20, 2, 0x601080, (angle + 128) % 255, 127, 16,
                                 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *D_L00_001FEA14;
            FastVecSub(dir, target, pos);
            vec_scale_to_length(dir, dir, D_L00_001B0754);
            FastVecAdd(pos, pos, dir);
            func_PAL_L00_003F10D8(pos, self, obj);
            PlayMobySound(0, 0, self);
            {
                int selected = g_item_slot_to_record.selected;
                entry = g_weapon_l00_table[selected];
            }
            dot = math_random_float_range(0.0f, 0.17f);
            st->cooldown = 1.0f / *(float *)(entry + 0x54) + dot;
            st->shots++;
        }
    } else {
        st->target = 0;
    }
}
