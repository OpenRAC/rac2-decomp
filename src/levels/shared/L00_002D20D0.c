/* Carried from rac1-decomp (src/overlays/shared/hero_mapped_animations.c,
   sync_hero_mapped_moby_animation_frames, func_L00_00232B78): the same instructions with
   rac2's offsets. Syncs the hero's second animation (+0x2494) to its main one (+0x2290):
   takes the float at +0xC24, copies the main animation's time and sequence into both
   sequence slots, then looks each slot's id up in its bank of the model. */

#include "common.h"

typedef struct {
    char pad0[0x1C];
    int ids[1];
} AnimBank;

typedef struct {
    char pad0[0x48];
    AnimBank *banks[1];
} AnimModel;

typedef struct {
    char pad0[0x24];
    AnimModel *model;
    char pad28[0x18];
    unsigned char seq[2];
    unsigned char bank[2];
    float f44;
    float f48;
    float f4C;
    char pad50[8];
    int id[2];
} AnimState;

extern char D_00189E20[];

void func_L00_002D20D0(void) {
    char *base = gHeroState;
    AnimState *obj = *(AnimState **)(base + 0x2494);

    if (obj == 0) {
        return;
    }
    obj->f4C = *(float *)(base + 0xC24);
    obj->f44 = *(float *)(*(char **)(base + 0x2290) + 0x44);
    obj->seq[0] = *(unsigned char *)(*(char **)(base + 0x2290) + 0x41);
    obj->seq[1] = *(unsigned char *)(*(char **)(base + 0x2290) + 0x41);
    obj->id[0] = obj->model->banks[obj->bank[0]]->ids[obj->seq[0]];
    obj->id[1] = obj->model->banks[obj->bank[1]]->ids[obj->seq[1]];
}
