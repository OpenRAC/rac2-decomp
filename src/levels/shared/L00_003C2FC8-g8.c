#include "include_asm.h"
#include "names.h"
/* func_L00_003C2FC8: the twin of func_L00_003EE4C0 (aim-assist target query) with its own
 * tuning block; the fire test checks the allowed flag first, state+0x28 is cleared on arming
 * and the state byte is not re-stored. Same -g unit reasons as the twin. */
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
extern AimQueryConfig D_L00_001AFED0;
extern AimTuning g_weapon_l00_table[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_00296020[];
extern unsigned char g_hero_state[];
extern unsigned char g_pad_state[];
extern unsigned char D_00139592[];
extern float D_L00_001AFEC0 __attribute__((sda));
extern float D_L00_001AFEC4 __attribute__((sda));
extern float D_L00_001AFEC8 __attribute__((sda));
extern float D_L00_001AFECC __attribute__((sda));
extern int D_L00_001B28E8;
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
extern int slot_copy_records_to_free(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int PlayMobySound(int, int, char *);
extern char *mini_nuke_projectile_spawn(int, char *, char *);
extern int get_ammo(int);
extern void slot_reset_active(int);
extern int vec_fast_helper_b(void *);
extern void moby_apply_active_effect(void *);
extern void ref_L00_003C2FC8_00(void (*)(void *), void *);

/* Updates the Mini-Nuke moby: picks an aim target and fires when the player presses the button. */
void mini_l00_nuke_update(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *target;
    char *info;
    AimVector position;
    AimQueryConfig config;
    AimVector scratch;
    int allowed;
    moby_transform_joint_to_world((char *)object, 0, (char *)&position);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        anim_start_blended_with_flags(object, 1, 0, 2, 0);
    target = 0;
    if (H->ptr[0x1450 / 4] && H->ptr[0x1450 / 4][0x20] != 0xFE && H->ptr[0x1450 / 4][0x20] != 0xFD) {
        info = (char *)moby_get_private_value_0(H->ptr[0x1450 / 4]);
        if (info && *(float *)info > 0.0f)
            target = H->ptr[0x1450 / 4];
    }
    allowed = 1;
    if (H->i[0x2294 / 4] == 0x1D || H->i[0x2294 / 4] == 1) {
        if (math_fast_float_d(&H->i[0x2534 / 4]) == 0)
            allowed = 0;
    } else {
        H->i[0x2534 / 4] = 0x28;
        if (!target) {
            config = D_L00_001AFED0;
            target = SelectBestTargetInCone(&position, &H->b[0x760], &scratch, 0.392699093f, 0.785398185f,
                                  0, 0, 0, 11.1f, 0.0f, 0.0f, 0, &config);
        }
    }
    CalculateAimedLaunchVelocity(&config, &position, target, 0, D_L00_001AFEC4, D_L00_001AFEC0,
                   D_L00_001AFECC * 0.016666668f, D_L00_001AFEC8 * 0.00027777778f);
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact(&position, &config, state, state + 0x10, object, 0, 0,
                                          D_L00_001AFEC8 * 0.00027777778f);
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        *(int *)(state + 0x2C) = -1;
        *(float *)(state + 0x20) = 0.0f;
        *(int *)(state + 0x28) = 0;
    case 1:
        if (H->i[0x1D8 / 4] >= 21)
            cancel_hero_item_animation();
        if (allowed && *(float *)(state + 0x20) == 0.0f && !H->b[0x22BC] && (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] >= 23) {
            if (weapon_spend_ammo(-1, 1)) {
                D_L00_001B28E8 = 1;
                start_equipped_item_animation();
                *(int *)(state + 0x2C) = slot_copy_records_to_free(D_L00_00296020);
                anim_start_blended_with_flags(object, 2, 0, 2, 0);
                mini_nuke_projectile_spawn((int)object, (char *)&position, (char *)&config);
                PlayMobySound(0, 0, (char *)object);
                {
                AimTuning *tu = &g_weapon_l00_table[D_00139592[0]];
                *(float *)(state + 0x20) = 1.0f / tu->cooldown;
            }
            } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || D_L00_001B28E8 == 1) {
                PlayMobySound(1, 0, (char *)object);
                D_L00_001B28E8 = 0;
            }
            if (!(PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) || !get_ammo(-1) || !H->b[0x22B8]) {
                if (*(int *)(state + 0x2C) >= 0) {
                    slot_reset_active(*(int *)(state + 0x2C));
                    *(int *)(state + 0x2C) = -1;
                }
            }
        }
    }
    vec_fast_helper_b(state + 0x20);
    ref_L00_003C2FC8_00(moby_apply_active_effect, object);
}
