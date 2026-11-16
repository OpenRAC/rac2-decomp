#include "common.h"

/* Prefix views; the owning storage keeps its unknown extent. */
typedef struct LeanMoby {
    char pad[0x2C];
    float scale;
} LeanMoby;
typedef struct LeanHero {
    char pad000[0x1A8];
    float yaw_error;
    char pad1AC[0x1314 - 0x1AC];
    LeanMoby *item;
    char pad1318[0x2294 - 0x1318];
    int mode;
} LeanHero;
extern char g_hero_state[];

/* The pose fields updated by this function. */
typedef struct Rac2Native_002B8CB8_Record {
    unsigned char prefix_00[0xCC8];
    float f_CC8;
    unsigned char prefix_CCC[0xCF8 - 0xCC8 - 4];
    float f_CF8;
    unsigned char prefix_CFC[0xD04 - 0xCF8 - 4];
    float f_D04;
    float f_D08;
} Rac2Native_002B8CB8_Record;

extern unsigned char g_unlocked_item_flags[] __attribute__((sda));

/* The level frame-time value is reached through $gp. */
extern float g_glow_scale __attribute__((sda));

extern char g_hero_item_attach_records[];
extern float g_hero_l00_float_param[];

extern float math_fabs(float f);

/* Updates mode-2 lean and sway using the hero turn and item moby scale. */
void UpdateHeroLeanAndSwayParameters(void)
{
    LeanMoby *live;
    LeanHero *st = (LeanHero *)g_hero_state;
    float x;
    float y;
    float share;
    float len;
    float scale;

    if (st->item == 0)
        return;
    if (g_unlocked_item_flags[3] != 0)
        g_hero_l00_float_param[0] = g_glow_scale;
    live = st->item;
    scale = 1024.0f / live->scale;
    if (st->mode != 2)
        return;

    x = st->yaw_error;
    y = 0.02f;
    ((Rac2Native_002B8CB8_Record *)g_hero_item_attach_records)->f_D04 = y;
    ((Rac2Native_002B8CB8_Record *)g_hero_item_attach_records)->f_D08 = 0.35f;
    if (1.4f < x)
        x = 1.4f;
    else if (x < -1.4f)
        x = -1.4f;
    y = -x * 1.2f;
    if (75.0f * 3.14159274f / 180.0f < y)
        y = 75.0f * 3.14159274f / 180.0f;
    else if (y < -(75.0f * 3.14159274f / 180.0f))
        y = -(75.0f * 3.14159274f / 180.0f);
    ((Rac2Native_002B8CB8_Record *)g_hero_item_attach_records)->f_CC8 = y;

    share = 0.1f;
    len = math_fabs(x) * share;
    share = len + share;
    if (0.07f < share)
        share = 0.07f;
    ((Rac2Native_002B8CB8_Record *)g_hero_item_attach_records)->f_CF8 = share * scale;
}
