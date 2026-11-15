#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

typedef struct View_00422A30 {
    u8 pad0[0x188C];
    u8 *f188C;
    u8 pad1[0x2290 - 0x1890];
    u8 *f2290;
    s32 f2294;
} View_00422A30;

extern View_00422A30 g_hero_state;

extern float D_L23_001B1910 __attribute__((sda));

extern float D_L23_001B1928 __attribute__((sda));

extern u8 *g_mothership_boss_moby __attribute__((sda));

extern s32 D_L23_001B36E0;

/* A 16-byte global vector: retain the unsplit address form, as in retail. */
extern TI16 D_L23_001B1FB0 MACRO_ADDR;

extern u8 *CreateMoby(s32);

extern void moby_init_child_from_parent(u8 *, u8 *);

extern void mothership_project_point_onto_surface(void *, float);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float gravity_get_center_distance(void *);

extern float fast_vec_dist(void *, void *);

extern float math_fabs(float);

extern float FastVecDot(void *, void *);

extern void FastVecScale(void *, void *, float);

extern s32 mothership_is_held(void);

extern s32 PlayMobySound(s32, s32, u8 *);

/* Creates the follower object for `src` (the effect that tracks `target`, or the hero, or nothing): copies
   the pose rows, fills the state, and when it has a live target works out the direction, the distance and
   the aim test, dropping the target when the aim, the range or the helper says so. */
/* Creates a homing shot. It chooses a target (given, the hero, or none), points the shot
   at it, and drops the target if it is too far, off to the side or blocked. */
u8 *SpawnTrackingEffect(u8 *src, TI16 *pos, u8 *target, s32 track_moby, s32 track_point) {
    u8 *obj;
    u8 *vars;
    TI16 loc[4];
    float target_value;
    float source_value;
    float distance;
    float aim_dot;
    s32 too_far_off;
    u8 *hero;
    TI16 row0;
    TI16 row1;
    TI16 row2;
    TI16 *back_dir;

    obj = CreateMoby(0x118F /* moby class 4495 */);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        moby_init_child_from_parent(obj, src);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * D_L23_001B1910;
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(float *)(vars + 0x1C) = 0.33333334f;
        row0 = *(TI16 *)(src + 0xC0);
        *(TI16 *)(obj + 0xC0) = row0;
        row1 = *(TI16 *)(src + 0xD0);
        *(TI16 *)(obj + 0xD0) = row1;
        row2 = *(TI16 *)(src + 0xE0);
        *(TI16 *)(obj + 0xE0) = row2;
        *(u8 **)(vars + 0x10) = src;
        qcopy(obj + 0x10, pos);
        *(s32 *)(vars + 0x14) = 0x96;
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) + *(float *)(obj + 0x2C);
        vars[0x28] = track_moby;
        vars[0x29] = track_point;
        hero = g_mothership_boss_moby;
        if (target != 0) {
            *(u8 **)(vars + 0x18) = target;
            *(s32 *)(vars + 0x24) = 0x890000;
        } else {
            if (hero != 0) {
                *(u8 **)(vars + 0x18) = hero;
                if (*(s16 *)(hero + 0xAA) == MOBY_CLASS_MOTHERSHIP_BOSS_PART) {
                    *(s32 **)(vars + 0x2C) = &D_L23_001B36E0;
                } else {
                    *(u8 **)(vars + 0x2C) = hero + 0x10;
                }
                *(s32 *)(vars + 0x24) = 0x890000;
            } else {
                *(s32 *)(vars + 0x18) = 0;
                *(s32 *)(vars + 0x24) = 0x890000;
                vars[0x29] = 0;
                vars[0x28] = 0;
            }
        }
        if (src == g_hero_state.f2290) {
            vars[0x29] = 1;
        }
        if (vars[0x28] == 0 && *(s32 *)(vars + 0x18) != 0) {
            qcopy(&loc[0], *(void **)(vars + 0x2C));
            mothership_project_point_onto_surface(&loc[0], 0.0f);
            FastVecSub(vars + 0x30, *(u8 **)(vars + 0x2C), obj + 0x10);
            qcopy(&loc[1], obj + 0x10);
            mothership_project_point_onto_surface(&loc[1], 0.0f);
            FastVecSub(&loc[2], &loc[0], &loc[1]);
            too_far_off = 0;
            vec_scale_to_length(&loc[2], &loc[2], 1.0f);
            vec_scale_to_length(vars + 0x30, vars + 0x30, 1.0f);
            source_value = gravity_get_center_distance(src + 0x10);
            target_value = gravity_get_center_distance(*(u8 **)(vars + 0x2C));
            distance = fast_vec_dist(&loc[0], &loc[1]);
            if (distance < 5.0f) {
                if (math_fabs(source_value - target_value) > 10.0f) {
                    too_far_off = 1;
                }
            }
            qcopy(&loc[3], obj + 0xC0);
            aim_dot = FastVecDot(&loc[2], &loc[3]);
            if ((src == g_hero_state.f2290 && *(*(u8 **)(vars + 0x18) + 0x31) == 0) ||
                aim_dot < D_L23_001B1928 || 50.0f < distance || too_far_off != 0 || mothership_is_held() != 0) {
                *(s32 *)(vars + 0x18) = 0;
            }
            if (src == g_hero_state.f2290) {
                if (*(s32 *)(vars + 0x18) != 0) {
                    g_hero_state.f188C = vars + 0x30;
                } else if (g_hero_state.f2294 == 0x5B) {
                    back_dir = (TI16 *)(src + 0xE0);
                    qcopy(&D_L23_001B1FB0, back_dir);
                    FastVecScale(&D_L23_001B1FB0, &D_L23_001B1FB0, -1.0f);
                    g_hero_state.f188C = (u8 *)&D_L23_001B1FB0;
                    qcopy(vars + 0x30, &D_L23_001B1FB0);
                    vars[0x28] = 0;
                    *(s32 *)(vars + 0x18) = 1;
                    vars[0x29] = 0;
                }
            }
        }
        *(s32 *)(vars + 0x20) = 0;
        PlayMobySound(1, 0, obj);
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x41;
        obj[0xBC] = 0;
    }
    return obj;
}
