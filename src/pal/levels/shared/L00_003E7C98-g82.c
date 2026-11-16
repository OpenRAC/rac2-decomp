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
extern char *func_PAL_L00_003F9060(void *, void *, int, int);
extern void ApplyAreaHitOrEmitParticles_pal(char *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int coll_process_hit(void *, int, void *, void *, float);
extern int moby_is_in_special_class_range(char *);
extern char *part_spawn_ground_effect(void *, int, unsigned int, int, int, float, float, void *, float, int);

/* Aim and spawn a beam, then flash four layers around its muzzle. */
void AimAndSpawnBeamWithMuzzleFlashes_pal(char *moby)
{
    Vector origin, velocity, targetPosition, delta, unit;
    char *state = *(char **)(moby + 0x68);

    char *beam;
    float speed = (g_weapon_l00_table + g_item_slot_to_record[0x17])->speed * 0.020000001f;
    int mode;
    char *model;
    char *collision;
    if (H->h[4726] == 1) {
        moby_transform_joint_to_world(moby, 0, (char *)origin);
        vec_scale_to_length(velocity, moby+0xD0, -speed);
    } else {
        moby_transform_joint_to_world(moby, 0, (char *)origin);
        vec_scale_to_length(velocity, (&H->f[472]), speed);
    }
    *(int *)(state + 0x10) = gfx_add_point_light(origin, 10.0f, 0.0f, 0xFF0000FF);
    *(int *)(state + 0x14) = 25;
    mode = 0;
    if (H->i[1344]) {
        mode = 1;
        math_compute_aim_direction((char *)velocity, (char *)origin, speed, 128.0f, 0.34906590f);
    } else if (H->ptr[766]) {
        vec_compute_object_to_target(H->ptr[766], (char *)origin, (char *)velocity, speed);
    }
    if (g_active_tether_object) {
        char *target = *(char **)(state + 0x2C);
        if ((target && H->i[1344]) || (H->ptr[766] && !H->i[1344])) {
            if (target)
                qcopy(targetPosition, (target + 0x10));
            else
                /* lq ignores the low four address bits: this reads the quadword holding +0xBF8. */
                qcopy(targetPosition, &H->ptr[766]);
            FastVecSub(delta, targetPosition, origin);
            vec_scale_to_length(unit, velocity, 1.0f);
            FastVecScale(velocity, unit, FastVecDot(unit, delta) + 3.0f);
            mode = 2;
        }
    }
    FastVecScale(targetPosition, moby+0xD0, -1.5f);
    FastVecAdd(targetPosition, targetPosition, moby + 0x10);
    FastVecScale(delta, moby + 0xC0, 0.275f);
    FastVecAdd(targetPosition, targetPosition, delta);
    if (coll_process_hit(targetPosition, 1, H->ptr[2212], 0, 1.0f) &&
        (((collision = g_collision_result[6]) && (model = *(char **)(collision + 0x24)) && *(short *)(model + 0x46) == 5) ||
         moby_is_in_special_class_range(g_collision_result[6]))) {
        ApplyAreaHitOrEmitParticles_pal(moby, targetPosition);
    } else {
        beam = func_PAL_L00_003F9060(origin, velocity, *(int *)(state + 0x18), mode);
        if (beam)
            *(char **)(beam + 0xB8) = moby;
    }
    *(VectorBits *)unit = 0;
    part_spawn_ground_effect(origin, 8, 0x401050FF, 2, 1, 7.0f, 0.1f, unit, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0x401050FF, 2, -1, 5.0f, 0.1f, unit, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0xC0FFFFFF, 2, 1, 3.5f, 0.1f, unit, 0.0f, 1);
    part_spawn_ground_effect(origin, 8, 0xB0FFFFFF, 2, -1, 2.5f, 0.1f, unit, 0.0f, 1);
}
