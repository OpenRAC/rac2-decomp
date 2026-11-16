#include "include_asm.h"

#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];
#define H ((Hero *)D_00189E20)
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x50]; float speed; char tail[0x8C]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
extern unsigned char g_item_slot_to_record[];
extern int g_active_tether_object;
extern char *g_collision_result[];
extern void moby_transform_joint_to_world(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern int gfx_add_point_light(void *, float, float, unsigned int);
extern void math_compute_aim_direction(char *, char *, float, float, float);
extern void vec_compute_object_to_target(char *, char *, char *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern char *beam_spawn_moving_pal(void *, void *, int, int);
extern int coll_process_hit(void *, int, void *, void *, float);
extern int moby_is_in_special_class_range(char *);
extern int beam_test_segment_hit_pal(char *, void *);
extern char *part_spawn_ground_effect(void *, int, unsigned int, int, int, float, float, void *, float, int);

/* Aim and spawn a beam, then flash four layers around its muzzle. */
void beam_fire_with_muzzle_flash_pal(char *moby)
{
    Vector origin, velocity, target_position, delta, unit;
    char *state = *(char **)(moby + 0x68);
    char *beam;
    float speed = (g_weapon_l00_table + g_item_slot_to_record[0x17])->speed * 0.020000001f;
    int mode;
    if (H->h[4726] == 1) {
        moby_transform_joint_to_world(moby, 0, (char *)origin);
        vec_scale_to_length(velocity, moby + 0xD0, -speed);
    } else {
        moby_transform_joint_to_world(moby, 0, (char *)origin);
        vec_scale_to_length(velocity, (&H->f[472]), speed);
    }
    *(int *)(state + 0x10) = gfx_add_point_light(origin, 15.0f, 0.0f, 0x7F608060);
    *(int *)(state + 0x14) = 25;
    mode = 0;
    if (H->i[1344]) {
        mode = 1;
        math_compute_aim_direction((char *)velocity, (char *)origin, speed, 128.0f, 0.34906590f);
    } else if (H->ptr[766]) {
        vec_compute_object_to_target(H->ptr[766], (char *)origin, (char *)velocity, speed);
    }
    if (g_active_tether_object) {
        char *target = *(char **)(state + 0x30);
        if ((target && H->i[1344]) || (H->ptr[766] && !H->i[1344])) {
            if (target)
                qcopy(target_position, (target + 0x10));
            else
                /* lq ignores the low four address bits: this reads the quadword holding +0xBF8. */
                qcopy(target_position, &H->ptr[766]);
            FastVecSub(delta, target_position, origin);
            mode = 2;
            vec_scale_to_length(unit, velocity, 1.0f);
            FastVecScale(velocity, unit, FastVecDot(unit, delta) + 3.0f);
        }
    }
    beam = beam_spawn_moving_pal(origin, velocity, *(int *)(state + 0x18), mode);
    if (beam)
        *(char **)(beam + 0xB8) = moby;
    if (coll_process_hit(origin, 1, H->ptr[2212], 0, 1.0f) && g_collision_result[6]) {
        char *model = *(char **)(g_collision_result[6] + 0x24);
        if ((model && *(short *)(model + 0x46) == 5) || moby_is_in_special_class_range(g_collision_result[6]))
            beam_test_segment_hit_pal(beam, g_collision_result[6] + 0x10);
    }
    *(VectorBits *)target_position = 0;
    part_spawn_ground_effect(origin, 8, 0x4010FF10, 2, 1, 7.0f, 0.1f, target_position, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0x4010FF10, 2, -1, 5.0f, 0.1f, target_position, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0xC0FFFFFF, 2, 1, 3.5f, 0.1f, target_position, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0xB0FFFFFF, 2, -1, 2.5f, 0.1f, target_position, 0.0f, 1);
}
