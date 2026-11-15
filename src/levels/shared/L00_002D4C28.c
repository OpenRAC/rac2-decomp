#include "names.h"
extern char D_00189E20[];
extern int D_L00_001A8F00 __attribute__((sda));

extern void func_L00_002AFBF0(void);

extern void func_L00_002AA178(char *);

extern void func_L00_002B0968(char *);

extern void func_L00_002D4A38(void);

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

extern Rec_1BCAC0 D_L00_001BCAC0;

/* Set bit 0x800 on list objects of either supported kind, dispatch the level
   updates, then clear bit 0 on the six resident object slots. */
/* Marks level glow objects as drawn, runs the level updates, then clears the visible flag on the resident objects. */
void func_L00_002D4C28(char *object)
{
    int i;
    void *listObject;
    unsigned short flags;

    if (D_L00_001A8F00 != 2 && D_L00_001A8F00 != 6)
        return;

    if (((Base_2A *)gHeroState)->f12C0 == 0)
        SpawnHeroItemMobies();

    for (i = 0; i < D_L00_001BCAC0.count; i++) {
        listObject = D_L00_001BCAC0.list[i];
        if (listObject != 0 && (*(short *)((char *)listObject + 0xAA) == 0x50A /* moby class 1290 */ ||
                          *(short *)((char *)listObject + 0xAA) == 0xD54 /* moby class 3412 */)) {
            flags = *(unsigned short *)((char *)listObject + 0x34);
            *(unsigned short *)((char *)listObject + 0x34) = flags | 0x800;
        }
    }

    SpawnEffectFromRecord(object);
    update_hero_item_mobys(object);
    FadeLevelGlowColors();

    {
        void *listObject;
        Base_2A *hero = (Base_2A *)gHeroState;

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
