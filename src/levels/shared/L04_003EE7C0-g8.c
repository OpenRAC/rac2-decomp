#include "include_asm.h"
#include "names.h"
/* func_L04_003EE7C0: the level-04 copy of func_L00_003C2FC8 (aim-assist target query),
 * over level 04's tuning block and tables. Same -g unit reasons as the twin. */
typedef int AimWord128 __attribute__((mode(TI)));
typedef union { AimWord128 word; float f[4]; } AimVector;
typedef struct { unsigned int words[5]; } AimQueryConfig;
typedef struct { char prefix[0x54]; float cooldown; char suffix[0xE0-0x58]; } AimTuning;
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; unsigned char *ptr[0x980]; } Hero;
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)
struct Rac2Native_5f824a0e369ccf7b_src_record {
    unsigned char b0,b1,b2,b3;
    unsigned short s4,s6,s8,s10,s12;
    unsigned char e,f;
};
extern AimQueryConfig g_nuke_l04_aim_query_config;
extern AimTuning g_item_l04_record_table[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_nuke_src_records[];
extern unsigned char g_hero_state[];
extern unsigned char g_pad_state[];
extern unsigned char g_gravity_bomb_weapon_index[];
extern float g_nuke_launch_param_b __attribute__((sda));
extern float g_nuke_launch_param_a __attribute__((sda));
extern float g_nuke_l04_launch_speed __attribute__((sda));
extern float g_nuke_launch_height __attribute__((sda));
extern int g_nuke_pressed_flag;
extern void moby_transform_joint_to_world(char *, int, char *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern char *moby_get_private_value_0(unsigned char *);
extern int math_fast_float_d(void *);
extern unsigned char *SelectBestTargetInCone(void *, void *, void *, float, float, int, int, int, float, float, float, int, AimQueryConfig *);
extern void CalculateAimedLaunchVelocity(void *, void *, void *, int, float, float, float, float);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, void *, int, int, float);
extern void cancel_hero_item_animation(void);
extern int weapon_spend_ammo(int, int);
extern void start_equipped_item_animation(void);
extern int actuator_play_waves(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int PlayMobySound(int, int, char *);
extern char *mini_nuke_projectile_spawn(int, char *, char *);
extern int get_ammo(int);
extern void actuator_end_looping_waves(int);
extern int vec_fast_helper_b(void *);
extern void moby_apply_active_effect(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);

/* Updates the player's Mini-Nuke: finds an aim target and, when the fire button is pressed, launches the shot and starts its sound. */
void mini_l04_nuke_update(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *aimTarget;
    char *targetInfo;
    AimVector position;
    AimQueryConfig config;
    AimVector scratch;
    int allowed;
    moby_transform_joint_to_world((char *)moby, 0, (char *)&position);
    if (moby[0x42] == moby[0x43] && (moby[0x60] & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    aimTarget = 0;
    if (H->ptr[0x1450 / 4] && H->ptr[0x1450 / 4][0x20] != 0xFE && H->ptr[0x1450 / 4][0x20] != 0xFD) {
        targetInfo = (char *)moby_get_private_value_0(H->ptr[0x1450 / 4]);
        if (targetInfo && *(float *)targetInfo > 0.0f)
            aimTarget = H->ptr[0x1450 / 4];
    }
    allowed = 1;
    if (H->i[0x2294 / 4] == 0x1D || H->i[0x2294 / 4] == 1) {
        if (math_fast_float_d(&H->i[0x2534 / 4]) == 0)
            allowed = 0;
    } else {
        H->i[0x2534 / 4] = 0x28;
        if (!aimTarget) {
            config = g_nuke_l04_aim_query_config;
            aimTarget = SelectBestTargetInCone(&position, &H->b[0x760], &scratch, 0.392699093f, 0.785398185f,
                                  0, 0, 0, 11.1f, 0.0f, 0.0f, 0, &config);
        }
    }
    CalculateAimedLaunchVelocity(&config, &position, aimTarget, 0, g_nuke_launch_param_a, g_nuke_launch_param_b,
                   g_nuke_launch_height * 0.016666668f, g_nuke_l04_launch_speed * 0.00027777778f);
    *(int *)(vars + 0x24) = coll_trace_projectile_to_impact(&position, &config, vars, vars + 0x10, moby, 0, 0,
                                          g_nuke_l04_launch_speed * 0.00027777778f);
    switch (moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        *(int *)(vars + 0x2C) = -1;
        *(float *)(vars + 0x20) = 0.0f;
        *(int *)(vars + 0x28) = 0;
    case 1:
        if (H->i[0x1D8 / 4] >= 21)
            cancel_hero_item_animation();
        if (allowed && *(float *)(vars + 0x20) == 0.0f && !H->b[0x22BC] && (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] >= 23) {
            if (weapon_spend_ammo(-1, 1)) {
                g_nuke_pressed_flag = 1;
                start_equipped_item_animation();
                *(int *)(vars + 0x2C) = actuator_play_waves(g_nuke_src_records);
                anim_start_blended_with_flags(moby, 2, 0, 2, 0);
                mini_nuke_projectile_spawn((int)moby, (char *)&position, (char *)&config);
                PlayMobySound(0, 0, (char *)moby);
                {
                AimTuning *tuning = &g_item_l04_record_table[g_gravity_bomb_weapon_index[0]];
                *(float *)(vars + 0x20) = 1.0f / tuning->cooldown;
            }
            } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || g_nuke_pressed_flag == 1) {
                PlayMobySound(1, 0, (char *)moby);
                g_nuke_pressed_flag = 0;
            }
            if (!(PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) || !get_ammo(-1) || !H->b[0x22B8]) {
                if (*(int *)(vars + 0x2C) >= 0) {
                    actuator_end_looping_waves(*(int *)(vars + 0x2C));
                    *(int *)(vars + 0x2C) = -1;
                }
            }
        }
    }
    vec_fast_helper_b(vars + 0x20);
    gfx_add_draw_callback_third(moby_apply_active_effect, moby);
}
