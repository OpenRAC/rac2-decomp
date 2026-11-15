#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad_000[0xBF8];
    int field_BF8;
    char pad_BFC[0x1230 - 0xBFC];
    int field_1230;
    char pad_1234[0x1240 - 0x1234];
    int field_1240;
    char pad_1244[0x1450 - 0x1244];
    int field_1450;
    char pad_1454[0x2294 - 0x1454];
    int field_2294;
    char pad_2298[0x22BC - 0x2298];
    unsigned char field_22BC;
    char pad_22BD[0x2534 - 0x22BD];
    int field_2534;
} HeroState;
typedef struct {
    char pad[0x1A0];
    int field_1A0, field_1A4;
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
extern void func_PAL_002A7E68(char *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern int AcquireEntitySlot(char *, int, void *);
extern unsigned char *level_get_slot_body(int, int);
extern void vec_clear_128(void *), matrix_mul_vec3(void *, void *, void *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern char *func_PAL_L00_003E0120(char *, int, void *, void *);
extern void ref_L00_003EA540_00(void *, char *);

void func_PAL_L00_003EE818(char *self)
{
    float v[4];
    int tmp[4];
    char *st = *(char **)(self + 0x68);
    int ready = 1;
    char *shot;

    if (g_hero_state.field_2294 == 0x1D) {
        if (!math_fast_float_d(&g_hero_state.field_2534))
            ready = 0;
    } else {
        g_hero_state.field_2534 = 33;
    }
    if (*(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
        (*(unsigned char *)(self + 0x60) & 2))
        anim_start_blended_with_flags(self, 1, 0, 2, 0);
    if (g_hero_state.field_1450)
        g_hero_state.field_BF8 = g_hero_state.field_1450;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(st + 0xC) = 0;
        *(int *)st = 0;
        *(int *)(st + 4) = AcquireEntitySlot(self, 0, tmp);
        *(int *)(st + 8) = level_get_slot_body(*(short *)(self + 0xAA), *(int *)(st + 4));
        /* Fall through. */
    case 1:
        if (vec_fast_helper_b(st) && ready && g_hero_state.field_1240 >= 19 &&
            (g_pad_state.field_1A0 & g_hero_state.field_1230) &&
            !g_hero_state.field_22BC && weapon_spend_ammo(-1, 1)) {
            vec_clear_128(v);
            v[1] = -1.0f;
            matrix_mul_vec3(v, v, self + 0xC0);
            moby_transform_joint_to_world(self, 0, D_L00_001B2B90);
            shot = func_PAL_L00_003E0120(self, *(int *)(st + 4), D_L00_001B2B90, v);
            PlayMobySound(0, 0, self);
            if (*(unsigned char *)(self + 0x43) != 2)
                func_PAL_002A7E68(self, 2, 0, 0);
            *(float *)(self + 0x48) = 2.0f;
            if (shot)
                *(char **)(shot + 0xB8) = self;
            {
                int selected = g_item_slot_to_record.selected;
                Entry *entry = &g_weapon_l00_table[selected];
                *(float *)st = 1.0f / entry->rate;
            }
        } else if ((g_pad_state.field_1A4 & g_hero_state.field_1230) &&
                   !get_ammo(-1) && !g_hero_state.field_22BC) {
            PlayMobySound(2, 0, self);
        }
    }
    ref_L00_003EA540_00(meteor_gun_draw_glow, self);
}
