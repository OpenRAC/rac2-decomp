#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

extern void func_002A05A8(char *);

extern void anim_start_blended(char *, int, int, int);

extern void moby_set_state(char *, int, int);

extern int math_random_int_below(int);

extern void part_kill(char *);

extern void mem_clear(char *, int, int);

extern void moby_mark_spawned(char *);

extern void moby_detach_manipulator(char *, char *);

extern void AttachManipulator(char *, int, char *);

extern void *CreateMoby(int);

extern void value_set_and_smooth(char *, char *, int, int, float);

extern void moby_copy_joint_transform_to_object(char *, char *, int, int);

extern void gfx_add_draw_callback_third(void (*)(char *), char *);

extern void chainblade_free_chain_links(char *);

extern void chainblade_free_effect_trail(char *);

extern void SpawnJointParticleBursts(char *, int, int);

extern void chainblade_draw_glows(char *);

extern void chainblade_draw_arm_glows(char *);

extern void chainblade_draw_blade_flares(char *);

extern void chainblade_draw_joint_flares(char *, int, int);

extern void chainblade_draw_joint_flare(char *, int);

extern void boss_draw_joint_glow_facing_cam(char *, int);

extern void boss_draw_joint_four_glow(char *);

extern void boss_draw_joint_four_glow_facing_cam(char *);

extern void boss_draw_joint_glow(char *, int);

extern void gfx_update_color_fade(char *, char *);

extern void set_moby_color(char *, int, int, int);

extern void get_moby_color(char *, int *, int *, int *);

extern void moby_update_ground_check(char *);

extern float fast_vec_dist(char *, char *);


extern void heavy_lancer_update(char *);

extern char g_camera_l02_position;

extern int g_moby_l02_pool __attribute__((sda));

extern char *g_active_attacker_robot;

/* func_L02_003D26B0 is defined in L02_003D26B0-aim-g8.c. */

/* func_L02_003D2DE0 is defined in L02_003D2DE0-g16.c. */

/* func_L02_003D4308 is defined in L02_003D4308-g8.c. */

/* Per-frame upkeep for the Chainblade: jet puffs while flying, glow drawing, timers, and a timer reset when it is the target. */
void chainblade_update_effects_timers(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(unsigned char *)(self + 0x95) == 2 ||
        *(unsigned char *)(self + 0x20) == 0x12) {
        SpawnJointParticleBursts(self, 2, 0);
        SpawnJointParticleBursts(self, 3, 1);
    }
    gfx_add_draw_callback_third(chainblade_draw_glows, self);
    if (*(unsigned short *)(self + 0x96) < 0xFFFF) {
        (*(unsigned short *)(self + 0x96))++;
    }
    if (g_active_attacker_robot != 0 &&
        (g_active_attacker_robot == self || *(short *)(g_active_attacker_robot + 0xAA) == MOBY_CLASS_CHAINBLADE)) {
        *(short *)(state + 0x32A) = -1;
    }
    *(unsigned short *)(state + 0x32A) = *(unsigned short *)(state + 0x32A) + 1;
    *(unsigned short *)(state + 0x32E) = *(unsigned short *)(state + 0x32E) + 1;
    value_set_and_smooth(self, state + 0x340, 6, 1, 2.5f);
}

/* func_L02_003D47B0 is matched in L02_003D47B0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Puts the Chainblade back to its idle pose: frees its chain links, plays the idle animation and clears the hit flags. */
void chainblade_reset_to_idle(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(int *)(state + 0x2A0) != 0) {
        chainblade_free_chain_links(self);
    }
    anim_start_blended(self, 0, 0, 3);
    func_002A05A8(self);
    moby_set_state(self, 1, 0);
    *(unsigned short *)(self + 0x34) =
        (*(unsigned short *)(self + 0x34) & 0xEFFF) | 3;
    *(int *)(self + 0x98) = 0;
    *(unsigned char *)(self + 0x31) = 0;
}

/* Remembers which helper unit the Chainblade is working with. */
void chainblade_set_helper(char *self, int helper) {
    *(int *)(*(char **)(self + 0x68) + 0x310) = helper;
}

/* Advances the actor's step counter until the float at +0x20 no longer lies below the share
   (3 - step) / 3 of the count at +0x24, then latches the done flag; once only. */
/* Moves the boss to its next health phase once its health has dropped far enough, and flags the change. */
void chainblade_advance_health_phase(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(short *)(state + 0x318) != 0)
        return;
    (*(short *)(state + 0x31A))++;
    while (*(float *)(state + 0x20) <
           (float)*(short *)(state + 0x24) * (3.0f - (float)*(short *)(state + 0x31A)) * 0.33333334f)
        (*(short *)(state + 0x31A))++;
    *(short *)(state + 0x318) = 1;
}

/* Clears the flag that says a health phase change just happened. */
void chainblade_clear_phase_flag(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(short *)(state + 0x318) != 0) {
        *(short *)(state + 0x318) = 0;
    }
}

/* Tells if the helper unit is active and the boss health has dropped below the current phase limit. */
int chainblade_is_helper_ready(char *self) {
    char *state = *(char **)(self + 0x68);
    char *helper = *(char **)(state + 0x310);
    unsigned char helperState;
    int hit = 0;

    if (helper != 0) {
        helperState = *(unsigned char *)(helper + 0x20);
        if (helperState != 0xFE) {
            if (helperState != 0xFD) {
                if (helperState >= 3) {
                    if (*(float *)(state + 0x20) <
                        (float)*(short *)(state + 0x24) *
                            (3.0f - (float)*(short *)(state + 0x31A)) * 0.33333334f) {
                        hit = 1;
                    }
                }
            }
        }
    }
    return hit;
}

/* Decides if the boss should take off: after a wait, with rising odds the longer it waits. */
int chainblade_should_take_off(char *self) {
    char *state = *(char **)(self + 0x68);
    short timer = *(short *)(state + 0x32E);
    int delta;

    if (timer < 0x12C) {
        return 0;
    }
    if (timer < 0x1F5) {
        delta = 0x1F4 - *(short *)(state + 0x32A);
        if (delta > 0) {
            if (math_random_int_below(delta) != 0) {
                return 0;
            }
        }
    }
    *(short *)(state + 0x32A) = 0;
    *(short *)(state + 0x32E) = 0;
    return 1;
}

/* func_L02_003D4E00 is matched in L02_003D4E00-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D4ED0 is matched in L02_003D4ED0.c (built with -frac2-qcopy). */

typedef int TI128 __attribute__((mode(TI)));

extern void func_321E78(char *, char *, float, float, float, float);

extern void func_322330(char *, char *, float, float, float, float, int);

extern void func_327620(char *, char *, char *, float, float, float);

/* Steers the Chainblade smoothly towards a goal position, a heading and a tilt. */
void chainblade_steer_toward(char *self, TI128 *goal, float heading, float tilt) {
    char *state = *(char **)(self + 0x68);
    TI128 vec = *goal;
    float *v = (float *)&vec;

    func_321E78(self + 0x10, state + 0x1B0, v[0], 0.025f, 0.025f, 1.5000001f);
    func_321E78(self + 0x14, state + 0x1B4, v[1], 0.025f, 0.025f, 1.5000001f);
    func_321E78(self + 0x18, state + 0x1B8, v[2], 0.025f, 0.025f, 1.5000001f);
    func_322330(self + 0xF8, state + 0x1C4, heading, 0.003490659f, 0.003490659f,
                0.22107507f, 0);
    func_322330(self + 0xF4, state + 0x2F0, tilt, *(float *)(state + 0x124),
                *(float *)(state + 0x128), *(float *)(state + 0x12C), 0);
    func_327620(self, state + 0x2F4, state + 0x304, 0.5f, 0.087266475f, -1.0f);
}

/* func_L02_003D5118 is matched in L02_003D5118.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Creates the five chain link objects and prepares the two joint blocks they hang from. */
void chainblade_spawn_chain_links(char *self) {
    char *state = *(char **)(self + 0x68);
    char **slots = (char **)(state + 0x2A0);
    int i;

    mem_clear(state + 0x260, 0, 0x40);
    AttachManipulator(self, 1, state + 0x260);
    mem_clear(state + 0x220, 0, 0x40);
    AttachManipulator(self, 0, state + 0x220);
    for (i = 0; i < 5; i++) {
        char *link = CreateMoby(i + 0xA19 /* moby class 2585 + i */);

        *slots = link;
        if (link != 0) {
            *(unsigned char *)(*slots + 0x30) = 0;
            *(unsigned short *)(*slots + 0x32) = *(unsigned short *)(self + 0x32);
            *(unsigned long long *)(*slots + 0x38) =
                *(unsigned long long *)(self + 0x38);
            *(unsigned short *)(*slots + 0x34) |= 1;
            *(unsigned char *)(*slots + 0x31) = 0;
        }
        slots++;
    }
}

/* Starts a chain throw on one side: shows the five chain links and resets the throw counters. */
void chainblade_start_chain_throw(char *self, int side) {
    char *state = *(char **)(self + 0x68);
    char **slots;
    int i;

    if (side == 1) {
        *(unsigned char *)(state + 0x262) = side;
        *(float *)(state + 0x288) = 0.0001f;
        *(float *)(state + 0x284) = 0.0001f;
        *(float *)(state + 0x280) = 0.0001f;
    } else {
        *(unsigned char *)(state + 0x222) = 1;
        *(float *)(state + 0x248) = 0.0001f;
        *(float *)(state + 0x244) = 0.0001f;
        *(float *)(state + 0x240) = 0.0001f;
    }
    *(short *)(state + 0x320) = 0;
    {
        unsigned char one = 1;

        slots = (char **)(state + 0x2A0);
        for (i = 4; i >= 0; i--) {
            if (slots[0] != 0) {
                *(unsigned short *)(slots[0] + 0x34) =
                    *(unsigned short *)(slots[0] + 0x34) & 0xFFFE;
                *(unsigned char *)(slots[0] + 0x31) = one;
                moby_copy_joint_transform_to_object(self, slots[0], side, 0);
            }
            slots++;
        }
    }
    *(short *)(state + 0x31E) = 0;
}

/* func_L02_003D5748 is defined in L02_003D5748-g8-dbg.c. */

/* Ends the chain throw: frees the effect trail, hides the chain links and restores the joint settings. */
void chainblade_end_chain_throw(char *self) {
    char *state = *(char **)(self + 0x68);
    char *trail = *(char **)(state + 0x300);
    char **slots;
    char *node;
    int i;

    if (trail != 0) {
        chainblade_free_effect_trail(trail);
        *(int *)(state + 0x300) = 0;
    }
    *(unsigned char *)(state + 0x222) = 0;
    *(float *)(state + 0x248) = 1.0f;
    *(float *)(state + 0x244) = 1.0f;
    *(float *)(state + 0x240) = 1.0f;
    *(float *)(state + 0x288) = 1.0f;
    *(float *)(state + 0x284) = 1.0f;
    *(float *)(state + 0x280) = 1.0f;
    *(unsigned char *)(state + 0x262) = 0;
    slots = (char **)(state + 0x2A0);
    for (i = 4; i >= 0; i--) {
        node = slots[0];
        if (node != 0) {
            *(unsigned short *)(node + 0x34) = *(unsigned short *)(node + 0x34) | 1;
            *(unsigned char *)(slots[0] + 0x31) = 0;
        }
        slots++;
    }
}

/* Frees the chain links and the effect trail and releases the joint blocks they used. */
void chainblade_free_chain_links(char *self) {
    char *state = *(char **)(self + 0x68);
    char *trail = *(char **)(state + 0x300);
    char **slots;
    char *leftBlock;
    int i;

    if (trail != 0) {
        chainblade_free_effect_trail(trail);
        *(int *)(state + 0x300) = 0;
    }
    leftBlock = state + 0x220;
    slots = (char **)(state + 0x2A0);
    for (i = 4; i >= 0; i--) {
        if (slots[0] != 0) {
            moby_mark_spawned(slots[0]);
            slots[0] = 0;
        }
        slots++;
    }
    if (*(unsigned char *)(state + 0x261) != 0) {
        moby_detach_manipulator(self, state + 0x260);
    }
    if (*(unsigned char *)(state + 0x221) != 0) {
        moby_detach_manipulator(self, leftBlock);
    }
    mem_clear(leftBlock, 0, 0x40);
    mem_clear(leftBlock, 0, 0x40);
}

/* func_L02_003D5CF0 is matched in L02_003D5CF0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern void func_3366A8(char *);

/* Frees every node of a linked effect trail, one after another. */
void chainblade_free_effect_trail(char *node) {
    char *current;

    while (node != 0) {
        current = node;
        node = *(char **)(node + 0x34);
        func_3366A8(current);
    }
}

/* func_L02_003D5E40 is matched in L02_003D5E40-g8.c. */

/* func_L02_003D5F50 is defined in L02_003D26B0-g8.c. */

/* Draws all the glow effects of the Chainblade for the current phase and animation. */
void chainblade_draw_glows(char *self) {
    char *state = self;
    unsigned char mode;

    chainblade_draw_blade_flares(state);
    mode = *(unsigned char *)(state + 0x95);
    if (mode == 2) {
        chainblade_draw_arm_glows(state);
    }
    mode = *(unsigned char *)(state + 0x42);
    if (mode == 2) {
        gfx_draw_curved_path_segments(state);
    }
}

/* Draws the glows at the two arm joints, the second one mirrored. */
void chainblade_draw_arm_glows(char *self) {
    chainblade_draw_joint_flares(self, 2, 0);
    chainblade_draw_joint_flares(self, 3, 1);
}

/* func_L02_003D6388 is matched in L02_003D6388-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Draws the glow flares at both blade joints. */
void chainblade_draw_blade_flares(char *self) {
    chainblade_draw_joint_flare(self, 4);
    chainblade_draw_joint_flare(self, 5);
}

/* func_L02_003D6570 is matched in L02_003D6570-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D6690 is defined in L02_003D6690-helpers-g8.c. */

/* func_L02_003D6A20 is matched in L02_003D6A20-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* Whether the object's variant byte is one of the later ones. */
/* Tells if the Chainblade's state number is 3 or higher. */
int chainblade_is_state_active(char *self) {
    return *(unsigned char *)(self + 0x20) >= 3;
}

/* func_L02_003D7330 is defined in L02_003D7330-g8.c. */

extern void matrix_mul_vec3(void *, void *, void *);

extern void FastVecAdd(void *, void *, void *);

extern float mat_fast_helper_a(float, float);

extern int FloatToInt(float);

extern void armed_enemy_setup(char *, int);

extern void actor_revive(char *, int);

extern void flamethrower_robot_wake(char *, int);

extern void blade_ball_wake(char *, int);

typedef struct {
    char pad0[0x80];
    float x;
    float y;
} L02_003D7900_Hero;

extern L02_003D7900_Hero g_hero_state;

/* Builds a four-float vector and hands it to the two vector helpers, tints the three colour
   records of the actor's state from it, then walks the three actors the state points at:
   each gets the angle to the hero written at 0xF8 and the behaviour its type selects. */
/* Places the three actors the Chainblade was holding around its body, turns each towards the hero, resets each by its type, then lets go of them. */
void chainblade_release_held_actors(char *self) {
    float anchor[4];
    char *state = *(char **)(self + 0x68);
    char *actor;
    int i;
    int count;

    anchor[0] = 0.0f;
    anchor[1] = -9.0f;
    anchor[2] = -3.3f;
    anchor[3] = 0.0f;
    matrix_mul_vec3(anchor, anchor, self + 0xC0);
    FastVecAdd(anchor, anchor, self + 0x10);
    if (*(char **)(state + 0x10) != 0) {
        *(float *)(*(char **)(state + 0x10) + 0x10) = anchor[0] - 2.0f;
        *(float *)(*(char **)(state + 0x10) + 0x14) = anchor[1];
        *(float *)(*(char **)(state + 0x10) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x10) + 0x1C) = anchor[3];
    }
    if (*(char **)(state + 0x14) != 0) {
        *(float *)(*(char **)(state + 0x14) + 0x10) = anchor[0];
        *(float *)(*(char **)(state + 0x14) + 0x14) = anchor[1] + 1.0f;
        *(float *)(*(char **)(state + 0x14) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x14) + 0x1C) = anchor[3];
    }
    if (*(char **)(state + 0x18) != 0) {
        *(float *)(*(char **)(state + 0x18) + 0x10) = anchor[0];
        *(float *)(*(char **)(state + 0x18) + 0x14) = anchor[1] - 1.0f;
        *(float *)(*(char **)(state + 0x18) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x18) + 0x1C) = anchor[3];
    }
    actor = *(char **)(state + 0x10);
    for (count = 0, i = 0; i < 3; i++) {
        L02_003D7900_Hero *hero = &g_hero_state;

        if (i == 1) {
            actor = *(char **)(state + 0x14);
        }
        if (i == 2) {
            actor = *(char **)(state + 0x18);
        }
        if (actor == 0) {
            continue;
        }
        *(int *)(actor + 0xF0) = 0;
        *(int *)(actor + 0xF4) = 0;
        *(float *)(actor + 0xF8) =
            mat_fast_helper_a(hero->x - *(float *)(actor + 0x10),
                          hero->y - *(float *)(actor + 0x14));
        *(int *)(actor + 0xFC) = 0;
        switch (*(short *)(actor + 0xAA)) {
        case 0x9CA: /* moby class 2506 */
            armed_enemy_setup(actor, 0);
            break;
        case 0xB22: /* moby class 2850 */
            actor_revive(actor, 0);
            break;
        case 0xC3B: /* Megacorp Security Robot - Flamethrower */
            flamethrower_robot_wake(actor, 0);
            break;
        case 0xC3E: /* PX6 BladeBall */
            *(float *)(actor + 0x18) = *(float *)(actor + 0x18) + 0.5f;
            blade_ball_wake(actor, FloatToInt((float)count * 0.16666667f));
            break;
        }
    }
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x18) = 0;
}

/* func_L02_003D91A0 is defined in L02_003D91A0.c. */

/* Updates the turret's linked object each frame: animates it, copies its tint, draws effects and hides it when the camera is very close. */
void turret_update_linked_object(char *self) {
    char *state = *(char **)(self + 0x68);
    int red, green, blue;

    gfx_update_color_fade(self, state + 0x140);
    if (*(short *)(state + 0x140) == 0) {
        if (*(short *)(state + 0x27E) == 0) {
            set_moby_color(self, *(int *)(state + 0x270),
                          *(int *)(state + 0x274), *(int *)(state + 0x278));
            *(short *)(state + 0x27E) = 1;
        }
    } else {
        *(short *)(state + 0x27E) = 0;
    }
    get_moby_color(self, &red, &green, &blue);
    set_moby_color(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)),
        red, green, blue);
    gfx_add_draw_callback_third(heavy_lancer_update, self);
    if (*(unsigned char *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, &g_camera_l02_position) < 64.0f) {
            moby_update_ground_check(self);
            *(unsigned char *)(self + 0x6F) = 0x3C;
        }
    }
    *(float *)(self + 0x74) = 1.0f;
    if (*(unsigned short *)(self + 0x96) <= 0xFFFE) {
        *(unsigned short *)(self + 0x96) += 1;
    }
}


extern void *moby_transform_joint_to_world(char *, int, void *);

extern void coll_project_point_on_segment(void *, void *, void *, char *);

extern void FastVecSub(void *, void *, void *);

extern void FastVecScale(void *, void *, float);

extern void make_hit_descriptor(void *, char *, int, void *, float);

extern int coll_process_hit(float, void *, int, char *, void *);

typedef struct {
    char pad0[0x18];
    unsigned char b18;
    unsigned char b19;
    unsigned short h1a;
    char pad1c[0x14];
} L02_003DAB68_Rec;

/* Runs only while the state's target pointer (+0x240) is set.  The word at +0x98 of the object
   table entry the state selects (+0x244) is zeroed for the duration and put back at the end.
   Four rounds, for the joint pairs (1, 2), (3, 4), (5, 6) and (7, 8): the two joint positions
   (func_0029FCC0), func_L00_0031BDC0 on them and the target's position, the offset from the
   actor's position to its result, a vector made of the offset's first two floats turned a
   quarter turn, scaled by func_00282D30 (2.0) and completed with 1.0 and 5627.925, an effect
   record started from it (func_002A8C00), and two func_00277F48 calls on that record (0.65 and
   0.95). */
/* Fires four beam hits from pairs of joints at the target, each leaving a hit effect. */
void turret_spawn_beam_hits(char *self) {
    char *state = *(char **)(self + 0x68);
    float jointStart[4];
    float jointEnd[4];
    float hit[4];
    float diff[4];
    float perp[4];
    L02_003DAB68_Rec rec;
    char *obj;
    int saved;
    char *selfPos;
    float *offset;
    int i;
    int startJoint;
    int endJoint;
    float one;

    if (*(int *)(state + 0x240) != 0) {
        obj = (char *)((*(int *)(state + 0x244) << 8) + g_moby_l02_pool);
        one = 1.0f;
        saved = *(int *)(obj + 0x98);
        *(int *)(obj + 0x98) = 0;
        offset = diff;
        selfPos = self + 0x10;
        for (i = 0; i < 4; i++) {
            startJoint = i * 2 + 1;
            endJoint = i * 2 + 2;
            moby_transform_joint_to_world(self, startJoint, jointStart);
            moby_transform_joint_to_world(self, endJoint, jointEnd);
            coll_project_point_on_segment(hit, jointStart, jointEnd, *(char **)(state + 0x240) + 0x10);
            FastVecSub(offset, hit, selfPos);
            perp[0] = -diff[1];
            perp[1] = diff[0];
            perp[2] = 0.0f;
            FastVecScale(perp, perp, 2.0f);
            perp[2] = one;
            perp[3] = 5627.925f;
            make_hit_descriptor(&rec, self, 0x10001, perp, (float)*(unsigned char *)(state + 0x35));
            rec.b18 = 0;
            rec.b19 = 1;
            rec.h1a = *(unsigned short *)(self + 0xAA);
            coll_process_hit(0.65f, hit, 0, self, &rec);
            coll_process_hit(0.95f, jointEnd, 0, self, &rec);
        }
        *(int *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + g_moby_l02_pool + 0x98) = saved;
    }
}

/* Updates the joints and effects of the linked object one by one. */
void turret_update_linked_joints(char *self) {
    boss_draw_joint_glow_facing_cam(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)), 0);
    boss_draw_joint_glow_facing_cam(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)), 1);
    boss_draw_joint_glow(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)), 5);
    boss_draw_joint_glow(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)), 6);
    boss_draw_joint_four_glow(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)));
    boss_draw_joint_four_glow_facing_cam(
        (char *)(g_moby_l02_pool +
                 (*(int *)(*(char **)(self + 0x68) + 0x244) << 8)));
}

/* func_L02_003DAE60 is matched in L02_003DAE60-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DAF90 uses its dedicated G16 vector unit. */



/* func_L02_003DB030 is matched in L02_003DB030-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DB158 is matched in L02_003DB158-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */



/* func_L02_003DB200 is matched in L02_003DB200-g8.c (built with -frac2-zero-ti-por). */

/* Switches the object to state 7. */
void moby_switch_to_state_seven(char *self) {
    moby_set_state(self, 7, -1);
}
