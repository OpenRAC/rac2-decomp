#include "names.h"
/* func_L00_003A3F30: firing effect and input-controlled cooldown. Hero fields go through the
 * union view. Its own unit for -g: the line label before the cooldown division gives retail's
 * pre-div.s nop. */
#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)
extern u8 g_hero_state[];
extern u8 g_pad_state[];
extern float D_L00_001AF624 __attribute__((sda));
extern float D_L00_0025C64C NOT_SDA;
extern int D_L00_001B2860;
extern unsigned char D_00139580[];
typedef struct { char prefix[0x54]; float fireRate; char tail[0x88]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void ReleaseDeadOrExpiredSlots(void *);
extern void hero_l00_set_action(int, int);
extern int get_ammo(int);
extern void hud_add_moby_marker(void *, unsigned int, int, int, int, int, float, float, float);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_b(void *);
extern int weapon_spend_ammo(int, int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern int PlayMobySound(int, int, char *);
extern char *hero_fire_effect_from_facing(void *, void *);

/* Update the firing effect and its input-controlled cooldown. */
/* Per-frame update for the Seeker Gun moby: plays the firing effect and sets the cooldown from the fire button. */
void seeker_gun_update(char *moby)
{
    float position[4];
    float *cooldown = *(float **)(moby + 0x68);
    int ready;
    if (*(unsigned char *)(moby + 0x20) == 0)
        *(unsigned char *)(moby + 0x20) = 1;
    if (*(unsigned char *)(moby + 0x42) == *(unsigned char *)(moby + 0x43) &&
        (*(unsigned char *)(moby + 0x60) & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    ReleaseDeadOrExpiredSlots(H->ptr[0x2290 / 4]);
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L00_001AF624;
    D_L00_0025C64C = 0.1f;
    if (H->i[0x2294 / 4] == 1)
        hero_l00_set_action(29, 1);
    if (H->i[0x2294 / 4] == 29) {
        unsigned int color;
        if (*cooldown > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(moby, color, 0, 0x27, -1, 4, 2.0f, 0.0f, 90.0f);
    }
    if (H->ptr[0x1450 / 4])
        H->ptr[0xBF8 / 4] = H->ptr[0x1450 / 4];
    ready = 1;
    if (H->i[0x2294 / 4] == 29) {
        if (math_fast_float_d(&H->i[0x2534 / 4]) == 0)
            ready = 0;
    } else
        H->i[0x2534 / 4] = 40;
    if (vec_fast_helper_b(cooldown) && !H->b[0x22BC] &&
        (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] > 22 && ready) {
        if (weapon_spend_ammo(-1, 1)) {
            char *effect;
            D_L00_001B2860 = 1;
            moby_transform_joint_to_world(moby, 0, (char *)position);
            PlayMobySound(1, 0, moby);
            anim_start_blended_with_flags(moby, 2, 0, 2, 0);
            effect = hero_fire_effect_from_facing(position, moby);
            if (effect)
                *(char **)(effect + 0xB8) = moby;
        } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || D_L00_001B2860 == 1) {
            PlayMobySound(0, 0, moby);
            D_L00_001B2860 = 0;
        }
        {
            WeaponEntry *entry = &g_weapon_l00_table[D_00139580[0]];
            *cooldown = 1.0f / entry->fireRate;
        }
    }
}
