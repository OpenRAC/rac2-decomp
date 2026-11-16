/* func_PAL_L14_0042ED80, the PAL copy of func_L14_004295D0: the same C, with the rates scaled for 50 Hz. */
#include "common.h"

#define INT_AT(p, n) (*(int *)((p) + (n)))
#define U16_AT(p, n) (*(unsigned short *)((p) + (n)))
#define FLOAT_AT(p, n) (*(float *)((p) + (n)))

typedef struct {
    char pad0[0x10];
    unsigned char hit_anim;   /* 0x10 */
    char pad11[0x30 - 0x11];
    float f30, f34;           /* 0x30 */
    char pad38[0x3C - 0x38];
    float f3c, f40;           /* 0x3C */
    char pad44[0x48 - 0x44];
    int hit_anim_mode;        /* 0x48 */
} DamageBlock;

#define DAMAGE(p) ((DamageBlock *)((p) + 0x140))

extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void enemy_spawn_child_parts(void *, void *, int, int);
extern float coll_get_ground_distance_below(void *, void *, void *);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_init_with_callback(void *);
extern void moby_update_ground_check(void *);
extern float fast_vec_dist(void *, void *);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern void climbing_enemy_die_pal(void *);
extern void group_destroy_attached_parts(void *, void *);
extern int weapon_select_aim_target(void *, int, void *, int, float, float);
extern char g_tether_l14_origin_vec[];
extern int g_moby_l14_pool __attribute__((sda));
extern float g_enemy_turn_degrees __attribute__((sda));
extern int g_enemy_u16_param_a __attribute__((sda));
extern int g_enemy_u16_params[] __attribute__((sda));

/* Initializes the entity on its first frame, then handles the player coming close, damage
   and the state-2 update. */
int enemy_update_common_pal(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float turn;
    if (moby[0x20] == 0) {
        vars[0x48] = FloatToInt(15.0f);
        vars[0x4A] = FloatToInt(9.6f);
        DAMAGE(vars)->hit_anim = 6;
        DAMAGE(vars)->f3c = 0.15f;
        DAMAGE(vars)->hit_anim_mode = 2;
        DAMAGE(vars)->f34 = DAMAGE(vars)->f30 = 1.0f;
        turn = g_enemy_turn_degrees * 0.017453294f;
        DAMAGE(vars)->f40 = FLOAT_AT(moby, 0x18) - 3.0f;
        FLOAT_AT(vars, 0x54) = 0.3f;
        FLOAT_AT(vars, 0x50) = 1.0f;
        FLOAT_AT(vars, 0x78) = 0.120000005f;
        FLOAT_AT(vars, 0x74) = FLOAT_AT(vars, 0x70) = 0.0072000003f;
        FLOAT_AT(vars, 0x68) = FLOAT_AT(vars, 0x64) = 0.005026549f;
        FLOAT_AT(vars, 0x60) = 3.1415927f;
        FLOAT_AT(vars, 0x12C) = math_random_int_below(2) ? -turn : turn;
        U16_AT(vars, 0x132) = ((s32)(g_enemy_u16_param_a) * 5 + 2) / 6;
        U16_AT(vars, 0x134) = ((s32)(g_enemy_u16_params[0]) * 5 + 2) / 6;
        vars[0x2E] = 1;
        qcopy(vars + 0x2E0, moby + 0x10);
        INT_AT(vars, 0x31C) = 1;
        FLOAT_AT(vars, 0x2B4) = 4.0f;
        enemy_spawn_child_parts(moby, vars + 0x300, 0, 2);
        FLOAT_AT(vars, 0x20) = 3.0f;
        U16_AT(vars, 0x24) = 3;
        FLOAT_AT(moby, 0x18) += 0.5f;
        coll_get_ground_distance_below(moby + 0x10, moby, moby + 0x10);
        if (INT_AT(vars, 0x2BC) != -1) {
            moby_set_state(moby, 7, 3);
            if (moby[0x43]) anim_start_blended_pal(moby, 0, 0, 0);
        } else {
            moby_set_state(moby, 1, 0);
            if (moby[0x43] != 2) anim_start_blended_pal(moby, 2, 0, 0);
        }
        if (INT_AT(vars, 0x2B8) != -1)
            moby_init_with_callback((char *)g_moby_l14_pool + INT_AT(vars, 0x2B8) * 256);
    }
    if (moby[0x31] && fast_vec_dist(moby + 0x10, g_tether_l14_origin_vec) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 22;
    }
    if (moby_apply_damage_to_object_pal(moby, (char *)DAMAGE(vars), 0) && FLOAT_AT(vars, 0x20) <= 0.0f) {
        climbing_enemy_die_pal(moby);
        return 1;
    }
    if (vars[0x2E] == 2) {
        if (vars + 0x300)
            group_destroy_attached_parts(moby, vars + 0x300);
        return 1;
    }
    INT_AT(vars, 0x2F0) = weapon_select_aim_target(moby, INT_AT(vars, 0x2B0), 0, 0, FLOAT_AT(vars, 0x2B4), 1.5f);
    return 0;
}
