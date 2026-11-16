#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
extern s32 coll_process_hit(f32, s32, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, float);
extern int StartAttachedEffect_pal(int, int, int);
extern int g_hero_moby;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_weapon_l00_table[];
extern unsigned int g_area_hit_targets[];
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float pos[4];
    unsigned int obj;
    unsigned int magic;
    unsigned char kind;
    unsigned char kind2;
    unsigned short id;
    float len;
    unsigned int count;
} Trail_3A9798;
typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
} Entry262570;

/* Damages everything near a projectile hit and starts the weapon's attached effect on each target. */
void projectile_damage_nearby_on_hit_pal(char *moby, char *direction, char *position)
{
    Trail_3A9798 damage;
    int count;
    int i;
    unsigned int *targets;

    damage.magic = 0x810000;
    damage.len = *(float *)(direction + 0x18);
    damage.count = 1;
    damage.obj = (unsigned int)moby;
    *(TI128 *)damage.pos = *(TI128 *)direction;
    vec_scale_to_length(&damage, &damage, 1.0f);
    damage.pos[3] = 5627.9248046875f;
    damage.kind = 3;
    damage.kind2 = 2;
    damage.id = *(unsigned short *)(moby + 0xAA);
    count = coll_process_hit(6.0f, (int)position, 1, g_hero_moby, (int)&damage);
    if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x19] * 224))->flag != 0) {
        targets = g_area_hit_targets;
        for (i = 0; i < count; i++)
            StartAttachedEffect_pal(g_area_hit_targets[i], 0x46, *(int *)(moby + 0xB8));
    } else {
        targets = g_area_hit_targets;
        for (i = 0; i < count; i++)
            StartAttachedEffect_pal(g_area_hit_targets[i], 0x19, *(int *)(moby + 0xB8));
    }
}
