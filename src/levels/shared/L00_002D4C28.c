#include "names.h"
extern char g_hero_state[];
extern int g_game_l00_mode __attribute__((sda));

extern void SpawnHeroItemMobies(void);

extern void part_spawn_effect_from_record(char *);

extern void update_hero_item_mobys(char *);

extern void level_fade_glow_colors(void);

#ifndef RAC2_T_BASE_2A
#define RAC2_T_BASE_2A
typedef struct {
    unsigned char pad0[0x1270];
    void *f1270;
    void *f1274;
    unsigned char pad1[0x12C0 - 0x1278];
    void *f12C0;
    unsigned char pad2[0x1360 - 0x12C4];
    void *f1360;
    void *f1364;
    void *f1368;
} Base_2A;
#endif

#ifndef RAC2_T_REC_1BCAC0
#define RAC2_T_REC_1BCAC0
typedef struct {
    unsigned char pad0[0x44];
    short count;
    unsigned char pad1[0x18C - 0x46];
    void *list[1];
} Rec_1BCAC0;
#endif

extern Rec_1BCAC0 g_tutorial_probe_context;

/* Set bit 0x800 on list objects of either supported kind, dispatch the level
   updates, then clear bit 0 on the six resident object slots. */
/* Marks level glow objects as drawn, runs the level updates, then clears the visible flag on the resident objects. */
void level_update_glow_objects(char *object)
{
    int i;
    void *listObject;
    unsigned short flags;

    if (g_game_l00_mode != 2 && g_game_l00_mode != 6)
        return;

    if (((Base_2A *)g_hero_state)->f12C0 == 0)
        SpawnHeroItemMobies();

    for (i = 0; i < g_tutorial_probe_context.count; i++) {
        listObject = g_tutorial_probe_context.list[i];
        if (listObject != 0 && (*(short *)((char *)listObject + 0xAA) == 0x50A /* moby class 1290 */ ||
                          *(short *)((char *)listObject + 0xAA) == 0xD54 /* moby class 3412 */)) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags | 0x800;
        }
    }

    part_spawn_effect_from_record(object);
    update_hero_item_mobys(object);
    level_fade_glow_colors();

    {
        void *listObject;
        Base_2A *hero = (Base_2A *)g_hero_state;

        listObject = hero->f12C0;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
        listObject = hero->f1270;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
        listObject = hero->f1274;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
        listObject = hero->f1360;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
        listObject = hero->f1364;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
        listObject = hero->f1368;
        if (listObject != 0) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags & 0xFFFE;
        }
    }
}
