#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

extern int math_random_int_below(int);
extern u8 *part_spawn_gravity_fade(void *, void *, int, unsigned, int, int, int,
                          float, float, float, int);
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern u8 *D_L18_001FF414[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float weapon_compute_shot_launch_speed(void *, void *, int, float, float);
extern u8 *fireball_spawn(void *, void *, void *, int, float, float);


/* func_L18_003F80A0 is in L18_003F80A0-state-g8.c. */

/* func_L18_003F8A98 is in L18_003F8A98.c. */

extern void func_0033A0B0(u8 *arg0, u8 *arg1);
extern void func_0033DD38(u8 *arg0, u8 *arg1, s32 arg2, float arg3, float arg4);
extern void func_00340BD8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, float arg4);
extern void func_00337920(u8 *arg0);
extern float func_00308A98();
extern u8 D_001C97C0[];

/* Updates the enemy's body each frame: runs its animation helpers, clears its hit
   flags, and switches it to a new state when the hero's spot is close. */
void enemy_update_body_parts(u8 *moby) {
    u8 *thisMoby = moby;
    u8 *vars = *(u8 **)(thisMoby + 0x68);
    func_0033A0B0(moby, vars + 0x50);
    func_0033DD38(thisMoby, vars + 0x680, 1, 0.029999999329447746f,
                  0.30000001192092896f);
    func_0033DD38(thisMoby, vars + 0x600, 0, 0.029999999329447746f,
                  0.30000001192092896f);
    func_00340BD8(thisMoby, vars + 0x770, 2, 1, 2.5f);
    if (*(u16 *)(thisMoby + 0x96) <= 0xFFFEu) {
        *(u16 *)(thisMoby + 0x96) = *(u16 *)(thisMoby + 0x96) + 1;
    }
    *(u16 *)(vars + 0x766) = 0;
    *(u16 *)(vars + 0x768) = 0;
    *(u16 *)(vars + 0x76A) = 0;
    if (*(u8 *)(thisMoby + 0x31) != 0) {
        if (func_00308A98(thisMoby + 0x10, D_001C97C0) < 24.0f) {
            func_00337920(thisMoby);
            *(u8 *)(thisMoby + 0x6F) = 0x16;
        }
    }
}

extern void gfx_draw_billboard_quad(void *arg0, s32 arg1, u32 arg2, s32 arg3, float arg4,
                          float arg5, float arg6);
extern void moby_transform_joint_to_world(s32 arg0, s32 arg1, void *arg2);

/* Spawns two quick glow flashes at one of the object's joints. */
void part_spawn_joint_glow_flashes(u8 *moby) {
    u8 jointPos[0x10];
    moby_transform_joint_to_world((s32)moby, 5, jointPos);
    gfx_draw_billboard_quad(jointPos, 0x2E, 0x80FFFFFFu, 1, 0.25f, 0.0f, 0.0f);
    gfx_draw_billboard_quad(jointPos, 0xC, 0x80F0F020u, 1, 0.25f, 0.0f, 0.0f);
}

/* func_L18_003F90A0 is in L18_003F90A0-g8.c. */

/* func_L18_003FB308 is in L18_003FB308-g8.c. */

/* func_L18_003FB620 is in L18_003FB620-particles.c (-G32 settings record). */

/* func_L18_003FD858 is in L18_003FD858-g8.c. */

extern u16 *D_L18_001FB320[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_0019B2E8[];

extern s32 IsPointInCuboid(u8 *, s32);

/* The part of the object's state both tests read: two lists of four ids (a at 0x00, b at 0x10),
   the halfword flags that go with them (c at 0x20, d at 0x28) and the word at 0x74. */
typedef struct {
    s32 a[4];
    s32 b[4];
    s16 c[4];
    s16 d[4];
    u8 pad30[0x74 - 0x30];
    s32 f74;
} DamosElState;

/* Returns 0 while the word at 0x74 is -1 and 1 when it is 1, when the table byte of the object has
   bit 7 set, or when func_002ACBC8 accepts one of the flagged ids of list a. Otherwise it walks
   the groups of the flagged ids of list b: it returns 1 only when there is such a group and none
   of its entities (state other than 0xFE and 0xFD) has bit 0 of its halfword at +0x34 clear, and
   then drops the ids of list b whose flag is set. */
/* Checks whether the door's open condition is met. */
s32 door_check_open_condition(u8 *moby, u8 *heroPos)
{
    DamosElState *state = *(DamosElState **)(moby + 0x68);
    s32 i;
    s32 ok;
    s32 any;
    u16 *p;
    u8 *e;

    if (state->f74 == -1)
        return 0;
    if (state->f74 == 1)
        return 1;
    if (D_0019B2E8[moby[0xB0] + g_current_map_index * 16] & 0x80)
        return 1;
    for (i = 0; i < 4; i++) {
        if (state->a[i] == -1)
            continue;
        if (state->c[i] == 0)
            continue;
        if (IsPointInCuboid(heroPos, state->a[i]))
            return 1;
    }
    any = 0;
    ok = 1;
    for (i = 0; i < 4 && ok; i++) {
        if (state->b[i] == -1)
            continue;
        if (state->d[i] == 0)
            continue;
        any = 1;
        for (p = D_L18_001FB320[state->b[i]];
             (state->b[i] & 0xFF) != 0xFF && state->b[i] <= D_L18_001B2838[0] &&
             p != 0 && ((s16)p[-1] >= 0 || p == D_L18_001FB320[state->b[i]]);
             p++) {
            e = g_moby_l18_table[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    if ((*(u16 *)(e + 0x34) ^ 1) & 1) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
    }
    if (ok && any) {
        for (i = 0; i < 4; i++) {
            if (state->d[i] != 0)
                state->b[i] = -1;
        }
    }
    return ok && any;
}

/* The same test with the flags read the other way round: 1 while the word at 0x74 is -1, 0 when it
   is 1 or the table byte has bit 7 set, 1 when func_002ACBC8 accepts one of the unflagged ids of
   list a, and the group walk of func_L18_003FDAB8 over the unflagged ids of list b. */
/* Checks whether the door's close condition is met. */
s32 door_check_close_condition(u8 *moby, u8 *heroPos)
{
    DamosElState *state = *(DamosElState **)(moby + 0x68);
    s32 i;
    s32 ok;
    s32 any;
    u16 *p;
    u8 *e;

    if (state->f74 == -1)
        return 1;
    if (state->f74 == 1)
        return 0;
    if (D_0019B2E8[moby[0xB0] + g_current_map_index * 16] & 0x80)
        return 0;
    for (i = 0; i < 4; i++) {
        if (state->a[i] == -1)
            continue;
        if (state->c[i] != 0)
            continue;
        if (IsPointInCuboid(heroPos, state->a[i]))
            return 1;
    }
    any = 0;
    ok = 1;
    for (i = 0; i < 4 && ok; i++) {
        if (state->b[i] == -1)
            continue;
        if (state->d[i] != 0)
            continue;
        any = 1;
        for (p = D_L18_001FB320[state->b[i]];
             (state->b[i] & 0xFF) != 0xFF && state->b[i] <= D_L18_001B2838[0] &&
             p != 0 && ((s16)p[-1] >= 0 || p == D_L18_001FB320[state->b[i]]);
             p++) {
            e = g_moby_l18_table[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    if ((*(u16 *)(e + 0x34) ^ 1) & 1) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
    }
    if (ok && any) {
        for (i = 0; i < 4; i++) {
            if (state->d[i] != 0)
                state->b[i] = -1;
        }
    }
    return ok && any;
}

/* func_L18_0042EBB8 is in L18_0042EBB8-g8.c. */

/* func_L18_0042F308 is in L18_0042F308.c. */

extern int *D_L18_001FE480[];


extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);

/* Wakes the leader after its trigger fires and sends it moving. */
void leader_start_moving(u8 *moby) {
    s32 *classDef;
    if (*(u8 *)(moby + 0x20) != 1) return;
    classDef = *(s32 **)(moby + 0x24);
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(moby + 0x98) = classDef[4];
    moby_set_state(moby, 3, -1);
}

/* func_L18_0042F7B8 is in L18_0042F7B8-g8.c. */

/* func_L18_0042FBC8 is in L18_0042FBC8-g8.c. */

extern void extermibot_init_parts(u8 *a0);
extern void extermibot_update_hits(u8 *a0);
extern void extermibot_update_states(u8 *a0);
extern void extermibot_aim_torso(u8 *a0);
extern void extermibot_update_parts(u8 *a0);

/* Runs the boss each frame: sets it up in state 0, does nothing in state 1,
   and otherwise runs its four sub-updates. */
void extermibot_update_subsystems(u8 *moby) {
    u8 state = *(u8 *)(moby + 0x20);
    if (state == 0) {
        extermibot_init_parts(moby);
        return;
    }
    if (state == 1) return;
    extermibot_update_hits(moby);
    extermibot_update_states(moby);
    extermibot_aim_torso(moby);
    extermibot_update_parts(moby);
}

/* func_L18_004302B0 is in L18_004302B0.c. */

/* func_L18_004308F0 is matched in L18_004308F0.c (built with -frac2-hazard-labels). */


/* func_L18_00432070 is in L18_00432070.c. */

/* func_L18_00432310 is in L18_00432310.c. */

extern float mat_fast_helper_a(float, float);

/* Picks the aim mode (1 or 2) and stores the angle from the object to the given point. */
void extermibot_set_aim_toward_point(u8 *moby, float *target, s32 flag) {
    u8 *vars = *(u8 **)(moby + 0x68);
    *(u16 *)(vars + 0x808) = (flag != 0) ? 2 : 1;
    *(float *)(vars + 0x7A4) = mat_fast_helper_a(target[0] - *(float *)(moby + 0x10),
                                           target[1] - *(float *)(moby + 0x14));
}

extern float vec_distance_xy(u8 *arg0);

/* Returns 1 when the object's position vector is shorter than 3.8. */
s32 extermibot_is_position_short(u8 *moby) {
    if (vec_distance_xy(moby + 0x10) < 3.8f) return 1;
    return 0;
}

/* Returns the length of the object's position vector, less 30 or less 10 depending on a flag. */
float extermibot_get_position_length_offset(u8 *moby) {
    float length = vec_distance_xy(moby + 0x10);
    if (*(s16 *)(*(u8 **)(moby + 0x68) + 0x7FC) != 0) return length - 30.0f;
    return length - 10.0f;
}

extern float func_00308FB0(float arg0, float arg1);
extern float func_003099E8(float arg0, float arg1);

/* Like func_L18_00432718, the flag at +0x7FC selects an arm, but here both arms
   compile to the same code: cross-jumping after scheduling merges them, and only
   the flag's lh (unused in retail) and the separately scheduled blocks remain. */
/* Returns the angle the target must turn to face the given point (minus a quarter turn). */
float extermibot_get_turn_angle_to_point(u8 *moby, float *point)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    float angle;

    if (*(s16 *)(vars + 0x7FC) != 0) {
        target = *(u8 **)(vars + 0x7C0);
        angle = func_00308FB0(point[0] - *(float *)(target + 0x10), point[1] - *(float *)(target + 0x14));
        angle = func_003099E8(*(float *)(target + 0xF8), angle);
        return angle - 1.5707964897155762f;
    }
    target = *(u8 **)(vars + 0x7C0);
    angle = func_00308FB0(point[0] - *(float *)(target + 0x10), point[1] - *(float *)(target + 0x14));
    angle = func_003099E8(*(float *)(target + 0xF8), angle);
    return angle - 1.5707964897155762f;
}

extern s32 CollLine(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);

/* Returns 1 when nothing blocks the line from the linked part to the given point. */
s32 extermibot_is_path_to_point_clear(u8 *moby, s32 point) {
    s32 partPos[4];
    moby_transform_joint_to_world(*(s32 *)(*(s32 *)(moby + 0x68) + 0x7C8), 0, partPos);
    return CollLine(partPos, (void *)point, 0x16, 0, 0) == 0;
}

/* Returns 1 unless the flag is set and its counter is still below 0x97. */
s32 extermibot_is_cooldown_finished(s32 a0) {
    u8 *vars = (u8 *)*(s32 *)(a0 + 0x68);
    s32 result = 0;
    if (*(s16 *)(vars + 0x7FC) != 0) {
        if (*(s16 *)(vars + 0x804) < 0x97) goto done;
    }
    result = 1;
done:
    return result;
}

/* Returns 1 when the target is facing the given point within a small angle. */
s32 extermibot_is_facing_point(u8 *moby, float *point) {
    float angle = func_00308FB0(point[0] - *(float *)(moby + 0x10),
                            point[1] - *(float *)(moby + 0x14));
    u8 *vars = *(u8 **)(moby + 0x68);
    if (*(s16 *)(vars + 0x7FC) != 0) {
        return func_003099E8(*(float *)(*(u8 **)(vars + 0x7C0) + 0xF8), angle) <
               0.03490658849477768f;
    }
    return func_003099E8(*(float *)(*(u8 **)(vars + 0x7C0) + 0xF8), angle) <
           0.00872664712369442f;
}

extern u16 *D_L18_001FB320[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));

/* Looks through the object's group (state word 0x7B4) for the entity of class 0xB69, other than
   the two states 0xFE and 0xFD and with bit 0 of its halfword at +0x34 clear, nearest to the
   object (the callee measures the distance between the two +0x10 positions); keeps it in the
   state's +0x7B8 word and tells whether there is one. A group word of -1 means no group. */
s32 extermibot_find_nearest_protopet(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u16 *p;
    u8 *e;
    u8 *found;
    float best;
    float d;

    if (*(s32 *)(state + 0x7B4) == -1)
        return 0;
    found = 0;
    best = 1000.0f;
    for (p = D_L18_001FB320[*(s32 *)(state + 0x7B4)];
         (*(s32 *)(state + 0x7B4) & 0xFF) != 0xFF && *(s32 *)(state + 0x7B4) <= D_L18_001B2838[0] &&
         p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == D_L18_001FB320[*(s32 *)(state + 0x7B4)]);
         p++) {
        e = g_moby_l18_table[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == MOBY_CLASS_PROTOPET) {
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    if ((*(u16 *)(e + 0x34) ^ 1) & 1) {
                        d = ((float (*)(u8 *, u8 *))vec_distance_xy)(moby + 0x10, e + 0x10);
                        if (d < best) {
                            found = e;
                            best = d;
                        }
                    }
                }
            }
        }
    }
    *(u8 **)(state + 0x7B8) = found;
    return found != 0;
}

extern void moby_set_controller_speed_limits(u8 *arg0, float, float, float, float);

/* Sets the turning and speed limits for slow movement. */
void extermibot_set_slow_limits(u8 *moby) {
    moby_set_controller_speed_limits(moby, 0.0055555557f, 0.05333334f, 0.027925272f, 0.8377582f);
}

/* Sets the turning and speed limits for fast movement. */
void extermibot_set_fast_limits(u8 *moby) {
    moby_set_controller_speed_limits(moby, 0.1388889f, 0.18333334f, 0.027925272f, 0.8377582f);
}

extern u8 D_00190000[];
extern void snd_stop_voice(s32 arg0);
extern int PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern void moby_mark_spawned(void *arg0);
extern char *SpawnExplosion(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                           s32 arg6, s32 arg7, float arg8, float arg9, s32 arg10, s32 arg11,
                           s32 arg12, s32 arg13);

/* Destroys a piece and its three linked parts, stops its sound, and makes an explosion. */
void extermibot_destroy_piece_and_parts(u8 *moby) {
    u8 *vars;
    s32 voiceSlot;
    vars = *(u8 **)(moby + 0x68);
    voiceSlot = *(s32 *)(vars + 0x7F0);
    if (voiceSlot != -1) {
        u8 *voice = D_00190000 - 0x79A0 + voiceSlot * 0x70;
        if (*(u32 *)(voice + 0x88) != (u32)moby) goto end;
        if (voice[0x74] == 0) goto end;
        snd_stop_voice(voiceSlot);
    }
end:
    *(s32 *)(vars + 0x7F0) = -1;
    SpawnExplosion(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
    PlayMobySound(6, 0, moby);
    if (*(u32 *)(vars + 0x7C0)) {
        moby_mark_spawned(*(void **)(vars + 0x7C0));
        *(u32 *)(vars + 0x7C0) = 0;
    }
    if (*(u32 *)(vars + 0x7C4)) {
        moby_mark_spawned(*(void **)(vars + 0x7C4));
        *(u32 *)(vars + 0x7C4) = 0;
    }
    if (*(u32 *)(vars + 0x7C8)) {
        moby_mark_spawned(*(void **)(vars + 0x7C8));
        *(u32 *)(vars + 0x7C8) = 0;
    }
    moby_mark_spawned(moby);
}

/* If the piece is in state 4, changes it to its next states and clears its counter. */
void extermibot_release_group_piece(u8 *moby) {
    u8 *vars;
    if (*(u8 *)(moby + 0x20) != 4) return;
    vars = *(u8 **)(moby + 0x68);
    moby_set_state(moby, 6, 1);
    moby_set_state(moby, 5, -1);
    *(u16 *)(vars + 0x7FA) = 0;
}

/* Shrinks a piece and its three linked parts to half size, turns off their collision, and puts the piece in state 2. */
void extermibot_shrink_piece_and_parts(u8 *object, int reason) {
    u8 *state;

    if (object[0x20] == 2)
        return;
    state = *(u8 **)(object + 0x68);
    *(int *)(state + 0x7EC) = reason;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(object + 0x98) = *(int *)(*(u8 **)(object + 0x24) + 0x10);
    *(u16 *)(object + 0x34) &= 0xFFFD;
    *(float *)(state + 0x7E8) = 0.5f;
    *(float *)(object + 0x2C) = *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.5f;
    if ((*(u8 **)(state + 0x7C0))) {
        *(u16 *)((*(u8 **)(state + 0x7C0)) + 0x34) &= 0xFFBE;
        *(u16 *)((*(u8 **)(state + 0x7C0)) + 0x34) |= 0x1000;
        *(int *)((*(u8 **)(state + 0x7C0)) + 0x98) = *(int *)(*(u8 **)((*(u8 **)(state + 0x7C0)) + 0x24) + 0x10);
        *(int *)((*(u8 **)(state + 0x7C0)) + 0x98) = 0;
        *(u16 *)((*(u8 **)(state + 0x7C0)) + 0x34) &= 0xFFFD;
        *(float *)((*(u8 **)(state + 0x7C0)) + 0x2C) = *(float *)(*(u8 **)((*(u8 **)(state + 0x7C0)) + 0x24) + 0x24) *
                                 *(float *)(state + 0x7E8);
    }
    if ((*(u8 **)(state + 0x7C4))) {
        *(u16 *)((*(u8 **)(state + 0x7C4)) + 0x34) &= 0xFFBE;
        *(u16 *)((*(u8 **)(state + 0x7C4)) + 0x34) |= 0x1000;
        *(int *)((*(u8 **)(state + 0x7C4)) + 0x98) = *(int *)(*(u8 **)((*(u8 **)(state + 0x7C4)) + 0x24) + 0x10);
        *(int *)((*(u8 **)(state + 0x7C4)) + 0x98) = 0;
        *(u16 *)((*(u8 **)(state + 0x7C4)) + 0x34) &= 0xFFFD;
        *(float *)((*(u8 **)(state + 0x7C4)) + 0x2C) = *(float *)(*(u8 **)((*(u8 **)(state + 0x7C4)) + 0x24) + 0x24) *
                                 *(float *)(state + 0x7E8);
    }
    if ((*(u8 **)(state + 0x7C8))) {
        *(u16 *)((*(u8 **)(state + 0x7C8)) + 0x34) &= 0xFFBE;
        *(u16 *)((*(u8 **)(state + 0x7C8)) + 0x34) |= 0x1000;
        *(int *)((*(u8 **)(state + 0x7C8)) + 0x98) = *(int *)(*(u8 **)((*(u8 **)(state + 0x7C8)) + 0x24) + 0x10);
        *(int *)((*(u8 **)(state + 0x7C8)) + 0x98) = 0;
        *(u16 *)((*(u8 **)(state + 0x7C8)) + 0x34) &= 0xFFFD;
        *(float *)((*(u8 **)(state + 0x7C8)) + 0x2C) = *(float *)(*(u8 **)((*(u8 **)(state + 0x7C8)) + 0x24) + 0x24) *
                                 *(float *)(state + 0x7E8);
    }
    moby_set_state(object, 2, 1);
    *(u16 *)(object + 0x34) &= 0xEFFF;
    *(short *)(state + 0x7FA) = 0;
}


/* If the piece is in state 2, moves it to state 3 and makes it visible. */
void extermibot_advance_piece_to_state(u8 *moby) {
    u8 *vars;
    if (*(u8 *)(moby + 0x20) != 2) return;
    vars = *(u8 **)(moby + 0x68);
    moby_set_state(moby, 3, 1);
    *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x1000;
    *(u16 *)(vars + 0x7FA) = 0;
}

/* Hands every entity of the object's group (byte 0x21) to func_L18_00432AD0. */
void extermibot_release_all_group_pieces(u8 *arg0)
{
    u16 *p;
    u8 *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L18_001FB320[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L18_001B2838[0] && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L18_001FB320[arg0[0x21]])) {
        e = g_moby_l18_table[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        extermibot_release_group_piece(e);
        p++;
    }
}

/* Returns 1 when the object is in one of its attack states. */
s32 extermibot_is_in_attack_state(u8 *moby) {
    s32 state = *(u8 *)(moby + 0x20);
    s32 result = 0;
    if ((state & 0xFF) == 8) goto one;
    if ((state & 0xFF) == 13) goto one;
    if ((u32)(state - 9) >= 4) goto done;
    if (*(u8 *)(moby + 0x94) != 8) goto done;
one:
    result = 1;
done:
    return result;
}

extern void func_00335388(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

/* Plays the same animation on the object and its two linked parts unless they already show it. */
void extermibot_set_anim_on_parts(u8 *moby, s32 animId, s32 a2, s32 a3) {
    u8 *vars = *(u8 **)(moby + 0x68);
    if (*(u8 *)(moby + 0x43) != animId) {
        func_00335388(moby, animId, a2, a3);
    }
    if (*(u8 **)(vars + 0x7C0) != 0) {
        if (*(u8 *)(*(u8 **)(vars + 0x7C0) + 0x43) != animId) {
            func_00335388(*(u8 **)(vars + 0x7C0), animId, a2, a3);
        }
    }
    if (*(u8 **)(vars + 0x7C4) != 0) {
        if (*(u8 *)(*(u8 **)(vars + 0x7C4) + 0x43) != animId) {
            func_00335388(*(u8 **)(vars + 0x7C4), animId, a2, a3);
        }
    }
}

extern void part_spawn_spark_first_bone_alt(u8 *a0);
extern void part_spawn_spark_first_bone(u8 *a0);
extern void gfx_draw_beam_from_bone_point(u8 *a0, s32 a1);
extern void part_spawn_spark_second_bone(u8 *a0, s32 a1);

/* Runs the update helpers for the object's two linked parts. */
void extermibot_update_linked_parts(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    if (*(u8 **)(vars + 0x7C0) != 0) {
        part_spawn_spark_first_bone_alt(moby);
        if ((*(u16 *)(*(u8 **)(vars + 0x7C0) + 0x7C) & 2) != 0) {
            part_spawn_spark_first_bone(moby);
        }
    }
    if (*(u8 **)(vars + 0x7C4) == 0) return;
    gfx_draw_beam_from_bone_point(moby, 0);
    gfx_draw_beam_from_bone_point(moby, 1);
    part_spawn_spark_second_bone(moby, 2);
    part_spawn_spark_second_bone(moby, 3);
    part_spawn_spark_second_bone(moby, 4);
}

/* Fires a shot: spawns two sparkles, then a projectile aimed toward a target point, with a sound. */
void extermibot_fire_shot_at_target(u8 *moby)
{
    float pos[4], delta[4], end[4], vel[4];
    u8 *vars = *(u8 **)(moby + 0x68), *shot, *particle;
    int colorSeed;
    float launchHeight;

    if (*(s16 *)(vars + 0x7FC) == 0)
        return;
    *(s16 *)(vars + 0x804) = 0;
    moby_transform_joint_to_world(*(s32 *)(vars + 0x7C8), 0, pos);
    colorSeed = math_random_int_below(255);
    particle = part_spawn_gravity_fade(pos, D_L18_001A8F20, 3, 0x808080, colorSeed, 127, 16,
                            840000.0f, 840000.0f, 0.0f, 0);
    if (particle)
        particle[2] = D_L18_001FF414[0][0];
    particle = part_spawn_gravity_fade(pos, D_L18_001A8F20, 3, 0x608080, (colorSeed + 128) % 255,
                            127, 16, 840000.0f, 840000.0f, 0.0f, 0);
    if (particle)
        particle[2] = D_L18_001FF414[0][0];
    FastVecSub(delta, vars + 0x760, pos);
    vec_scale_to_length(delta, delta, 0.3f);
    FastVecAdd(pos, pos, delta);
    vec_scale_to_length(delta, delta, 3.0f);
    FastVecSub(end, vars + 0x760, delta);
    launchHeight = weapon_compute_shot_launch_speed(pos, end, 0, 0.25f, -0.0019444444915279746f);
    FastVecSub(vel, end, pos);
    vel[2] = 0.0f;
    vec_scale_to_length(vel, vel, 0.25f);
    vel[2] = launchHeight;
    shot = fireball_spawn(moby, pos, vel, 30, 0.0019444444915279746f,
                         (float)vars[0x35]);
    PlayMobySound(7, 0, moby);
    *(float *)(shot + 0x2C) = 0.005f;
}

/* Starts the attack timer by clearing one counter and setting another to 1. */
void extermibot_start_attack_timer(s32 moby) {
    u8 *vars = (u8 *)*(s32 *)(moby + 0x68);
    if (*(s16 *)(vars + 0x7FC) != 0) return;
    *(u16 *)(vars + 0x804) = 0;
    *(u16 *)(vars + 0x806) = 1;
}

/* Clears the attack counters. */
void extermibot_clear_attack_counters(s32 moby) {
    u8 *vars = (u8 *)*(s32 *)(moby + 0x68);
    *(u16 *)(vars + 0x804) = 0;
    *(u16 *)(vars + 0x806) = 0;
}
