#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void mat_get_euler_angles(void *, void *);
extern void SetDeathBits(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_and_set_height(void *, void *, void *, int, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern void part_spawn_masked_debris(void *, int, void *, int, float, float, float, float);
extern void moby_mark_spawned(void *);

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct L12Settings {
    u8 pad[0x7C];
    s8 x, y, z, w;
};

/* Level data. */
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001A8FF0 __attribute__((sda));
extern u8 D_L12_001A63A8[];
extern u8 D_L12_001FEAC0[];
extern s16 *D_L12_001FB960[];

extern void func_331870();
extern void func_32F848();
extern void func_32F978(f32);

extern void func_L12_00322AF8(s32, s32);
extern void trigger_apply_settings_to_object();
extern void func_L12_0031E1D0(s32, s32, s32);
extern void func_L12_002F15C8(s32);
extern void func_L12_00326948(s32, s32, s32, f32, f32);
extern void func_L12_003296A8(s32, s32, s32, s32, f32);

extern float vec_distance_xy(void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern float vec_distance_squared_xy(void *, void *);

/* Picks which path point the enemy should walk to next: the one it is on, the nearest one, or the nearest one it can see. */
void enemy_choose_nearest_visible_path_point(s32 moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = *(u8 **)(D_L12_001FEAC0 + (*(s32 *)(state + 0x158) << 2));
    s32 i;
    s32 bestIdx;
    f32 best;
    f32 dist;

    best = vec_distance_xy(moby + 0x10, path + 0x10 + (*(s32 *)(state + 0x264) << 4));
    if (best < 0.5f) {
        *(s32 *)(state + 0x16C) = 0;
        return;
    }
    if (best < 5.0f) {
        if (CollLine(moby + 0x10, path + 0x10 + (*(s32 *)(state + 0x264) << 4), 2, 0, 0) == 0) {
            *(s32 *)(state + 0x16C) = 1;
            return;
        }
    }
    bestIdx = -1;
    best = 1000.0f;
    for (i = 0; i < *(s32 *)path; i++) {
        dist = vec_distance_squared_xy(moby + 0x10, path + 0x10 + i * 16);
        if (dist < best) {
            best = dist;
            bestIdx = i;
        }
    }
    if (best < 0.5f) {
        *(s32 *)(state + 0x264) = bestIdx;
        *(s32 *)(state + 0x16C) = 0;
        return;
    }
    if (CollLine(moby + 0x10, path + 0x10 + i * 16, 2, 0, 0) == 0) {
        *(s32 *)(state + 0x264) = bestIdx;
        *(s32 *)(state + 0x16C) = 1;
        return;
    }
    bestIdx = -1;
    best = 1000.0f;
    for (i = 0; i < *(s32 *)path; i++) {
        if (CollLine(moby + 0x10, path + 0x10 + i * 16, 2, 0, 0) != 0)
            continue;
        dist = vec_distance_squared_xy(moby + 0x10, path + 0x10 + i * 16);
        if (dist < best) {
            best = dist;
            bestIdx = i;
        }
    }
    if (bestIdx == -1) {
        *(s32 *)(state + 0x290) = *(s32 *)(state + 0x290) + 1;
        *(s32 *)(state + 0x16C) = 0;
    } else {
        *(s32 *)(state + 0x264) = bestIdx;
        *(s32 *)(state + 0x16C) = 1;
    }
}

/* func_L12_003E1EE8 is defined in L12_003E1EE8-g8.c. */

/* func_L12_003E20F0 is defined in L12_003E20F0-g8.c. */

/* Tries to take the shared attack slot for this group so only one member attacks at a time. */
void group_try_claim_attack_slot(s32 moby) {
    s32 mobyAlias = moby;
    s32 vars = *(u32 *)(mobyAlias + 0x68);
    s32 ownerIndex = *(s32 *)(*(u32 *)(vars + 0x294));

    if (ownerIndex != -1) {
        s32 mobyBase = D_L12_001B2E9C;
        u8 *owner = (u8 *)((u32)mobyBase + (ownerIndex << 8));

        if (owner != 0) {
            u8 ownerState = *(u8 *)(owner + 0x20);

            if (ownerState != 0xFE) {
                if (ownerState != 0xFD) {
                    if (ownerIndex != ((mobyAlias - mobyBase) >> 8))
                        return;
                }
            }
        }
    }
    func_L12_0031E1D0(mobyAlias, 0xF, 5);
    {
        s32 selfIndex = (mobyAlias - D_L12_001B2E9C) >> 8;

        *(u16 *)(vars + 0x29C) = 0x12C;
        *(s32 *)(*(u32 *)(vars + 0x294)) = selfIndex;
    }
}

/* Gives the shared group attack slot back if this enemy is holding it. */
void group_release_attack_slot(s32 moby) {
    s32 *slot = *(s32 **)(*(u32 *)(moby + 0x68) + 0x294);

    if (*slot == ((moby - D_L12_001B2E9C) >> 8))
        *slot = -1;
}

/* func_L12_003E2460 is defined in L12_003E2460-g8.c. */

/* func_L12_003E3A88 is defined in L12_003E3A88-g8.c. */

/* Turns two of the object's flags on or off, and sets its colour/direction bytes, from the settings given by a trigger. */
void trigger_apply_settings_to_object(int index, struct L12Settings *settings, int enable) {
    u8 *obj = (u8 *)(D_L12_001B2E9C + (index << 8));

    if (!obj)
        return;
    if (enable) {
        if (settings->x > 0)
            *(u16 *)(obj + 0x34) &= ~2;
        else if (settings->x < 0)
            *(u16 *)(obj + 0x34) |= 2;
        if (settings->y > 0 && (!obj || !*(u8 **)(obj + 0x24) ||
            *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18)) {
            obj[0x31] = 1;
            *(u16 *)(obj + 0x34) &= ~1;
        } else if (settings->y < 0 && (!obj || !*(u8 **)(obj + 0x24) ||
                   *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18)) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (settings->w > 0 && *(u8 **)(obj + 0x24))
            *(int *)(obj + 0x98) = *(int *)(*(u8 **)(obj + 0x24) + 0x10);
        else if (settings->w < 0 && *(u8 **)(obj + 0x24))
            *(int *)(obj + 0x98) = 0;
    } else {
        if (settings->x > 0 && (!*(u8 **)(obj + 0x24) ||
            *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18))
            *(u16 *)(obj + 0x34) |= 2;
        else if (settings->x < 0 && (!obj || !*(u8 **)(obj + 0x24) ||
                 *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18))
            *(u16 *)(obj + 0x34) &= ~2;
        if (settings->y > 0 && (!obj || !*(u8 **)(obj + 0x24) ||
            *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18)) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        } else if (settings->y < 0 && (!obj || !*(u8 **)(obj + 0x24) ||
                   *(s16 *)(*(u8 **)(obj + 0x24) + 0x46) != 18)) {
            obj[0x31] = 1;
            *(u16 *)(obj + 0x34) &= ~1;
        }
        if (settings->w > 0)
            *(int *)(obj + 0x98) = 0;
        else if (settings->w < 0)
            *(int *)(obj + 0x98) = *(int *)(*(u8 **)(obj + 0x24) + 0x10);
    }
}

/* Applies a trigger's settings to every object in one group list. */
void trigger_apply_settings_to_group(s32 a0, s32 settings, s32 groupId, s32 enable) {
    s16 *ids = D_L12_001FB960[groupId];

    if (ids != 0) {
        do {
            trigger_apply_settings_to_object(*(u16 *)ids & 0x7FFF, settings, enable);
        } while (*ids++ >= 0);
    }
}

/* func_L12_00407DE8 is defined in L12_00407DE8-qcopy.c. */

/* func_L12_00408050 is defined in L12_00408050-g8.c. */



/* func_L12_00419E40 is defined in L12_00419E40.c. */

/* func_L12_0041A2B8 is defined in L12_0041A2B8-g8.c. */

/* func_L12_0041A460 is defined in L12_0041A460.c. */

/* Updates the enemy's timers and counts up its age, stopping at the maximum. */
void enemy_tick_timers_age(s32 moby) {
    func_L12_00322AF8(moby, *(u32 *)(moby + 0x68) + 0x50);
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
}

/* Near miss: nonmatching/levels/func_L12_0041A578.c - the scan and the returns are right,
   the index lives in $a2 here against retail's in-place `addiu $a1,$a1,1`, and this cc1
   folds the loop back into the float test (`bc1fl`) where retail keeps `bc1t` + `b`. */


/* Adds one to a counter on every Space Tourist in the group. */
void tourist_increment_counters(s32 groupId) {
    s16 *ids = D_L12_001FB960[groupId];
    s32 mobyBase;

    if (ids == 0)
        return;
    mobyBase = D_L12_001B2E9C;
    do {
        u32 offset = (*(u16 *)ids & 0x7FFF) << 8;

        if (*(s16 *)(mobyBase + offset + 0xAA) == MOBY_CLASS_SPACE_TOURIST) {
            u8 *vars = (u8 *)*(u32 *)(mobyBase + offset + 0x68);

            *(u32 *)(vars + 0x798) = *(u32 *)(vars + 0x798) + 1;
        }
    } while (*ids++ >= 0);
}

/* func_L12_00424078 is defined in L12_00424078-g8.c. */

/* func_L12_00426C08 is defined in L12_00426C08-g8.c. */

/* func_L12_004277F0 is defined in L12_004277F0-g8.c. */


/* Counts down the enemy's timers, ages it, and updates its glow effects. */
void hopping_enemy_tick_timers(s32 moby) {
    s32 mobyAlias = moby;
    s32 vars = *(u32 *)(mobyAlias + 0x68);

    func_L12_002F15C8(vars + 0x330);
    func_L12_002F15C8(vars + 0x332);
    if (*(u16 *)(mobyAlias + 0x96) <= 0xFFFE)
        *(u16 *)(mobyAlias + 0x96) = *(u16 *)(mobyAlias + 0x96) + 1;
    vars = vars + 0x280;
    func_L12_00326948(mobyAlias, vars, 0, 0.03f, 0.3f);
    func_L12_003296A8(mobyAlias, vars, 0, 1, 1.8f);
}

/* Wakes up every hopping enemy in the object's group by setting its alert flag. */
void hopping_enemy_alert_group(s32 moby) {
    s32 mobyBase;
    s16 *ids;
    s16 *idList;

    if (*(u8 *)(moby + 0x21) == 0xFF)
        return;
    idList = D_L12_001FB960[*(u8 *)(moby + 0x21)];
    if (idList == 0)
        return;
    ids = idList;
    mobyBase = D_L12_001B2E9C;
    do {
        u32 offset = (*(u16 *)ids & 0x7FFF) << 8;

        if (*(s8 *)(mobyBase + offset + 0x20) >= 0) {
            if (*(s16 *)(mobyBase + offset + 0xAA) == 0x11EB /* moby class 4587 */)
                *(u16 *)(*(u32 *)(mobyBase + offset + 0x68) + 0x336) = 1;
        }
    } while (*ids++ >= 0);
}

/* Plays the death blast of the hopping enemy: sound, sparks and a puff of smoke, then removes it. */
void hopping_enemy_play_death_blast(char *obj) {
    char pos[16];
    union { TI128 q; float f[4]; } offset;
    char dir[16];
    int color;
    if (*(short *)(*(char **)(obj + 0x68) + 0x358))
        mat_get_euler_angles(obj + 0xC0, obj + 0xF0);
    SetDeathBits(obj, 0, 3);
    PlayMobySound(1, 0, obj);
    offset.q = 0;
    offset.f[2] = 0.75f;
    matrix_mul_vec3(pos, &offset, obj + 0xC0);
    FastVecAdd(pos, pos, obj + 0x10);
    part_spawn_explosion_with_sparks(obj, pos, -1, 0.3330000042915344f, 0.0f);
    FastVecSub(dir, obj + 0x10, g_hero_position);
    vec_transform_and_set_height(obj, dir, dir, 0, 0.0f);
    vec_scale_to_length(dir, dir, 0.10000000894069672f);
    color = D_L12_001A8FF0 ? math_random_int_below(0xFF) : 0xFF;
    part_spawn_masked_debris(obj, color & 0x1F, dir, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(obj);
}

/* func_L12_00428040 is defined in L12_003E1CB0-g8.c (it reads the group count through $gp). */

/* func_L12_004281D8 is defined in L12_003E1CB0-g8.c (it reads the colour pair through $gp). */

/* func_L12_00429A50 is defined in L12_00429A50-g8.c. */

/* func_L12_00429D60 is defined in L12_003E1CB0-g8.c. */

