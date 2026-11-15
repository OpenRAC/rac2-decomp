#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad_000[0xBF8];
    int heldWeapon;
    char pad_BFC[0x1230 - 0xBFC];
    int buttonMask;
    char pad_1234[0x1240 - 0x1234];
    int frameCount;
    char pad_1244[0x1450 - 0x1244];
    int selectedWeapon;
    char pad_1454[0x2294 - 0x1454];
    int mode;
    char pad_2298[0x22BC - 0x2298];
    unsigned char locked;
    char pad_22BD[0x2534 - 0x22BD];
    int cooldown;
} HeroState;

typedef struct {
    char pad[0x1A0];
    int pressed, released;
} InputState;

typedef struct {
    char pad[0x1D];
    unsigned char selected;
} Selection3EA540;

typedef struct {
    char pad[0x54];
    float rate;
    char rest[0x88];
} Entry;

extern HeroState g_hero_state;
extern InputState g_pad_state;
extern Selection3EA540 g_item_slot_to_record;
extern Entry g_weapon_l00_table[];
extern char D_L00_001B2B90[] __attribute__((sda));

extern void meteor_gun_draw_glow(void);
extern int math_fast_float_d(void *), vec_fast_helper_b(void *);
extern int weapon_spend_ammo(int, int), get_ammo(int);
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern void anim_start_blended(char *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern int AcquireEntitySlot(char *, int, void *);
extern unsigned char *level_get_slot_body(int, int);
extern void vec_clear_128(void *), matrix_mul_vec3(void *, void *, void *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern char *projectile_spawn_small(char *, int, void *, void *);
extern void ref_L00_003EA540_00(void *, char *);

/* Updates the Meteor Gun weapon: fires a shot when the player presses the button and the gun is ready. */
void meteor_gun_update(char *self)
{
    float v[4];
    int tmp[4];
    char *vars = *(char **)(self + 0x68);
    int ready = 1;
    char *shot;

    if (g_hero_state.mode == 0x1D) {
        if (!math_fast_float_d(&g_hero_state.cooldown))
            ready = 0;
    } else {
        g_hero_state.cooldown = 40;
    }
    if (*(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
        (*(unsigned char *)(self + 0x60) & 2))
        anim_start_blended_with_flags(self, 1, 0, 2, 0);
    if (g_hero_state.selectedWeapon)
        g_hero_state.heldWeapon = g_hero_state.selectedWeapon;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(vars + 0xC) = 0;
        *(int *)vars = 0;
        *(int *)(vars + 4) = AcquireEntitySlot(self, 0, tmp);
        *(int *)(vars + 8) = level_get_slot_body(*(short *)(self + 0xAA), *(int *)(vars + 4));
        /* Fall through. */
    case 1:
        if (vec_fast_helper_b(vars) && ready && g_hero_state.frameCount >= 23 &&
            (g_pad_state.pressed & g_hero_state.buttonMask) &&
            !g_hero_state.locked && weapon_spend_ammo(-1, 1)) {
            vec_clear_128(v);
            v[1] = -1.0f;
            matrix_mul_vec3(v, v, self + 0xC0);
            moby_transform_joint_to_world(self, 0, D_L00_001B2B90);
            shot = projectile_spawn_small(self, *(int *)(vars + 4), D_L00_001B2B90, v);
            PlayMobySound(0, 0, self);
            if (*(unsigned char *)(self + 0x43) != 2)
                anim_start_blended(self, 2, 0, 0);
            *(float *)(self + 0x48) = 2.0f;
            if (shot)
                *(char **)(shot + 0xB8) = self;
            {
                int selected = g_item_slot_to_record.selected;
                Entry *entry = &g_weapon_l00_table[selected];
                *(float *)vars = 1.0f / entry->rate;
            }
        } else if ((g_pad_state.released & g_hero_state.buttonMask) &&
                   !get_ammo(-1) && !g_hero_state.locked) {
            PlayMobySound(2, 0, self);
        }
    }
    ref_L00_003EA540_00(meteor_gun_draw_glow, self);
}
