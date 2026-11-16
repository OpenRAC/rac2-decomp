#include "common.h"

/* func_US2_L00_003F51EC, the USA v2.00 copy of func_L00_003F3D70: the same C, where each of the three
 * shots passes a fifth argument to func_US2_L00_003AB8F8: 5, then 5 or 10, then 5 or 15 with a target. */

typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];
extern unsigned char g_pad_state[];

typedef int ShotWord128 __attribute__((mode(TI)));
typedef union { ShotWord128 word; float f[4]; } ShotVector;
typedef struct { char prefix[0x50]; float speed, cooldown; char suffix[0xE0-0x58]; } ShotTuning;
extern ShotTuning g_weapon_l00_table[];

extern unsigned char g_item_slot_to_record[];

extern float g_hk22_speed_scale __attribute__((sda));
extern float g_weapon_effect_scale[];
extern void ReleaseDeadOrExpiredSlots(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int func_US2_L00_002C4560(int, int);
extern void hud_add_moby_marker(void *, unsigned int, int, int, int, int, float, float, float);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_b(void *);
extern int weapon_spend_ammo(int, int);
extern int get_ammo(int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_compute_aim_direction(char *, char *, float, float, float);
extern void vec_compute_object_to_target(char *, char *, char *, float);
extern char *func_US2_L00_003AB8F8(void *, void *, void *, void *, int);
extern void cam_compute_view_direction(char *, char *, int);
extern void math_build_axis_angle_quat(void *, int, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);

void func_US2_L00_003F51EC(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    ShotVector aim, velocity, position, direction, rotation, rotated;
    char *spawn, *target;
    unsigned int color;
    int allowed;
    float speed;
    ShotTuning *entry;
    int second, third;
    if (object[0x20] == 0)
        object[0x20] = 1;
    ReleaseDeadOrExpiredSlots(((Hero *)g_hero_state)->ptr[2212]);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        anim_start_blended_with_flags(object, 1, 0, 2, 0);
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24) * g_hk22_speed_scale;
    g_weapon_effect_scale[0] = 0.1f;
    if (((Hero *)g_hero_state)->i[2213] == 1)
        func_US2_L00_002C4560(0x1D, 1);
    if (((Hero *)g_hero_state)->i[2213] == 0x1D) {
        if (*(float *)state > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else color = 0x600FFF0F;
        hud_add_moby_marker(object, color, 0, 0x27, -1, 4, 2.0f, 0.0f, 90.0f);
    }
    if (((Hero *)g_hero_state)->ptr[1300])
        ((Hero *)g_hero_state)->ptr[766] = ((Hero *)g_hero_state)->ptr[1300];
    allowed = 1;
    if (((Hero *)g_hero_state)->i[2213] == 0x1D) {
        if (!math_fast_float_d(&((Hero *)g_hero_state)->i[2381])) allowed = 0;
    } else ((Hero *)g_hero_state)->i[2381] = 0x28;
    if (vec_fast_helper_b(state) && !((Hero *)g_hero_state)->b[8892] && ((Hero *)g_hero_state)->i[1168] > 22 && allowed) {
        if ((((Hero *)g_pad_state)->u[104] & ((Hero *)g_hero_state)->u[1164]) && weapon_spend_ammo(-1, 1)) {
            moby_transform_joint_to_world((char *)object, 0, (char *)&aim);
            PlayMobySound(0, 0, (char *)object);
            anim_start_blended_with_flags(object, 2, 0, 2, 0);
            speed = (g_weapon_l00_table + g_item_slot_to_record[0x18])->speed * 0.016666668f;
            if (((Hero *)g_hero_state)->h[4726] == 1) {
                vec_scale_to_length(&velocity, object + 0xD0, -speed);
                qcopy(&position, &aim);
            } else {
                vec_scale_to_length(&velocity, &(*(ShotVector *)&((Hero *)g_hero_state)->b[0x760]), speed);
                qcopy(&position, &aim);
                if (((Hero *)g_hero_state)->i[1344])
                    math_compute_aim_direction((char *)&velocity, (char *)&position, speed, 32.0f, 0.6981318f);
            }
            target = 0;
            second = 5;
            third = 5;
            if (((Hero *)g_hero_state)->ptr[766]) {
                vec_compute_object_to_target(((Hero *)g_hero_state)->ptr[766], (char *)&position, (char *)&velocity, speed);
                second = 10;
                target = ((Hero *)g_hero_state)->ptr[766];
                third = 15;
            }
            spawn = func_US2_L00_003AB8F8(&position, &velocity, object, target, 5);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            if (((Hero *)g_hero_state)->h[420] != 0)
                qcopy(&direction, ((Hero *)g_hero_state)->ptr[2212] + 0xE0);
            else
                cam_compute_view_direction((char *)object + 0x10, (char *)&direction, 1);
            math_build_axis_angle_quat(&rotation, (int)&direction, -0.122173056f);
            vec_rotate_by_quaternion(&rotated, &velocity, &rotation);
            spawn = func_US2_L00_003AB8F8(&position, &rotated, object, target, second);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            math_build_axis_angle_quat(&rotation, (int)&direction, 0.122173056f);
            vec_rotate_by_quaternion(&rotated, &velocity, &rotation);
            spawn = func_US2_L00_003AB8F8(&position, &rotated, object, target, third);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            entry = g_weapon_l00_table + g_item_slot_to_record[0x18];
            *(float *)state = 1.0f / entry->cooldown;
        } else if ((((Hero *)g_pad_state)->u[105] & ((Hero *)g_hero_state)->u[1164]) && !get_ammo(-1) && !((Hero *)g_hero_state)->b[8892]) {
            PlayMobySound(0, 0, (char *)object);
        }
    }
}
