#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
typedef struct __attribute__((packed)) { u64 fields[6]; } AnimationParameters;
typedef struct { char prefix[0x38]; u8 *owner; char suffix[4]; } TargetSlot;
extern TargetSlot D_L09_001C40C0[];
extern char D_L09_001B9A00[];
extern int g_current_map_index MACRO_ADDR;
extern u8 *D_L09_001B285C __attribute__((sda));
extern int D_L09_001A9040 __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern int moby_apply_damage_to_object(void *,void *,int),part_spawn_damage_debris(void *,void *,void *);
extern int math_random_int_below(int),weapon_select_aim_target(void *,int,void *,int,float,float);
extern int moby_is_hero_or_special(void *);
extern void trooper_legs_init(void *),enemy_apply_stored_values_helper(void *);
extern void TransferStateToNearestEligibleObject(void *),part_spawn_small_burst(void *,float),moby_destroy_linked(void *);
extern void trooper_compute_aim_target(void *),shared_counter_release(void *);
extern void moby_update_ground_check(void *),anim_start_blended(void *,int,int,int),moby_set_state(void *,int,int);
extern void FastVecScale(void *,void *,float),SetDeathBits(void *,int,int),moby_mark_spawned(void *);

/* Mirrors the parent's measured 48-byte animation parameter block into its child,
 * releases detached effects and propagates the live target slot.
 */
/* Main per-frame step for the enemy: runs its animation, passes the state on to the torso and removes everything when it dies. */
void trooper_legs_update_frame(u8 *object)
{
    u8 *state = P(object,0x68), *vars, *moved, **effects;
    int before, result, i, remove = 0;
    if (object[0x95] == 0) trooper_legs_init(object);
    if (object[0x31] && fast_vec_dist(object + 0x10, D_L09_001B9A00) < 24.0f) {
        moby_update_ground_check(object); object[0x6F] = 22;
    }
    if (object[0xA8] == 255) {
        u8 *child = P(state,0x2F8);
        if (child && S(child,0xAA) == MOBY_CLASS_MEGACORP_TROOPER_TORSO && child[0x20] != 0xFE && child[0x20] != 0xFD) {
            if (child[0xA8] != 255) {
                int index = child[0xA8];
                TargetSlot *slots = D_L09_001C40C0;
                if (slots[index].owner == child) {
                    object[0xA8] = index;
                    slots[object[0xA8]].owner = object;
                }
            }
        }
    }
    before = object[0x20];
    result = moby_apply_damage_to_object(object, state + 0x50, 0);
    if (g_current_map_index == 9 && S(state,0xC0) != -1) {
        if (!moby_is_hero_or_special(D_L09_001B285C + (S(state,0xC0) << 8))) D_L09_001A9040 = 0;
        S(state,0xC0) = -1;
    }
    if (result) {
        u8 *child;
        enemy_apply_stored_values_helper(object);
        child = P(state,0x2F8);
        if (child) {
            if (result == 4) {
                H(object,0x34) &= 0xEFFF;
                H(P(state,0x2F8),0x34) &= 0xEFFF;
                H(P(state,0x2F8),0x7C) |= 0x300;
                I(state,0x20) = 0;
                moved = P(P(state,0x2F8),0x68);
                *(AnimationParameters *)(moved + 0x20) = *(AnimationParameters *)(state + 0x20);
                part_spawn_damage_debris(P(state,0x2F8), moved + 0x50, moved + 0x20);
                TransferStateToNearestEligibleObject(object);
                part_spawn_small_burst(object,0.4f);
                moby_destroy_linked(object);
                if (before >= 4 && !math_random_int_below(2) && !I(state,0x428) &&
                    I(state,0x2DC) != -1 && I(state,0x2DC) == I(state,0x2B0)) {
                    if (object[0x43] != 17) anim_start_blended(object,17,0,5);
                    F(state,0xB0) = (float)*(s8 *)(state + 0xBF);
                    F(state,0xA4) = (float)*(s8 *)(state + 0xBE);
                    I(state,0xCC) = -1;
                    FastVecScale(state + 0xD0,state + 0xD0,0.05f);
                } else qzero(state + 0xD0);
                {
                    int j;
                    effects = (u8 **)(state + 0x2F0);
                for (j = 0; j < 2; j++) {
                    if (effects[j]) {
                        H(effects[j],0x34) &= 0xFFFD;
                        H(effects[j],0x34) &= 0xFFFE;
                        effects[j][0x31] = 1;
                        effects[j] = 0;
                    }
                } }
            } else {
                vars = P(child,0x68);
                *(AnimationParameters *)(vars + 0x20) = *(AnimationParameters *)(state + 0x20);
                part_spawn_damage_debris(P(state,0x2F8),vars + 0x50,vars + 0x20);
                anim_start_blended(P(state,0x2F8),object[0x43],0,3);
                F(P(state,0x2F8),0x48) = F(object,0x48);
                if (!(H(P(state,0x2F8),0x7C) & 0x80)) {
                    state[0x30F] = 1;
                    if (object[0x95] != 9) moby_set_state(object,13,8);
                }
                { u8 *target = P(state,0x2F8); if (!(H(target,0x7C) & 0x10)) H(target,0x7C) |= 0x100; }
                { u8 *target = P(state,0x2F8); if (!(H(target,0x7C) & 0x20)) H(target,0x7C) |= 0x200; }
                effects = (u8 **)(state + 0x2F0);
                for (i = 0; i < 2; i++) {
                    if (effects[i] && !((H(P(state,0x2F8),0x7C) >> (i+4)) & 1)) {
                        H(effects[i],0x34) &= 0xFFFD;
                        effects[i] = 0;
                    }
                }
            }
        }
    }
    weapon_select_aim_target(object,I(state,0x2D8),0,0,0.0f,0.0f);
    trooper_compute_aim_target(object);
    if (state[0x2E] == 2) remove = 1;
    else {
        u8 *child = P(state,0x2F8);
        if (child && S(child,0xAA) == MOBY_CLASS_MEGACORP_TROOPER_TORSO && child[0x20] != 0xFE && child[0x20] != 0xFD)
            remove = P(child,0x68)[0x2E] == 2;
    }
    if (remove) {
        shared_counter_release(object); moby_destroy_linked(object); TransferStateToNearestEligibleObject(object);
        SetDeathBits(object,0,3); moby_mark_spawned(object);
    }
}
