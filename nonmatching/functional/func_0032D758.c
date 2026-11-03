/* functional: high. From the 1 November near miss (756/756 bytes, scheduling-only differences), reread against the boot copy: boot data names (the slot table is D_00236150 here, as the boot code forms it), the two kind tests written out in place of the static helpers, slot stores in retail's order. */
/* func_0032D758: starts a damage-flash effect on an object. Resolves the effect kind (row +0x4C of D_00239BA0, or the
   index itself), needs D_001A7A80[kind] & 8, picks the alternate parameter bank for kinds whose type row says so,
   and for a live, visible, flagged object with health > 0 and no slot yet, fills the first free of 30 slots
   (ticks*60, scale/60, the object's colour or func_002A04B8's). Returns 0 when a slot was filled, else 1. */

#include "common.h"

typedef struct { int active; unsigned char type; char pad[0x47]; short kind; char tail[0x92]; } EffectType_32D758;
typedef struct { float scale; int ticks; char pad[8]; } EffectParams_32D758;
typedef struct { int remaining, color, flags, elapsed; float rate; char *object; int tag, active; } EffectSlot_32D758;

extern EffectType_32D758 D_00239BA0[];
extern unsigned char D_001A7A80[];
extern unsigned char D_00139568[];
extern EffectParams_32D758 D_00236510[2][119];
extern EffectSlot_32D758 D_00236150[];

extern s32 func_002AB1F0(u8 *);
extern s32 func_0032D700(void *);
extern void func_002A04B8(char *, int *, int *, int *);

int func_0032D758(char *self, int index, int arg)
{
    EffectType_32D758 *type;
    EffectSlot_32D758 *slot;
    int kind = D_00239BA0[index].kind;
    int result = 1;
    int alternate, selected, found, i;
    int rgb[3];
    float *health;
    char *colour;

    if (kind == 0)
        kind = index;
    if ((D_001A7A80[kind] & 8) == 0)
        return 1;

    alternate = 0;
    type = &D_00239BA0[D_00139568[kind]];
    selected = 0;
    if (type->active != 0) {
        if (type->type == 2) {
            selected = 1;
        } else if (type->type == 1) {
            switch (kind) {
            case 12: case 14: case 17: case 18: case 53:
                selected = 1;
                break;
            }
        }
    }
    if (selected) {
        alternate = 1;
    } else {
        type = &D_00239BA0[D_00139568[kind]];
        if (type->active != 0 && type->type == 3)
            alternate = 1;
    }

    if (*(short *)(*(char **)(self + 0x24) + 0x46) != 5)
        return 1;
    if ((*(unsigned short *)(self + 0x34) & 0x1000) == 0)
        return 1;
    if (*(signed char *)(self + 0x20) < 0)
        return 1;
    if (*(int *)(self + 0x98) == 0)
        return 1;
    health = (float *)func_002AB1F0((u8 *)self);
    if (health == 0)
        return 1;
    if (*health <= 0.0f)
        return 1;
    if (func_0032D700(self) != -1)
        return 1;

    for (i = 0; i < 30; i++) {
        slot = &D_00236150[i];
        if (slot->object != 0)
            continue;
        slot->object = self;
        slot->remaining = D_00236510[alternate][index].ticks * 60;
        slot->rate = D_00236510[alternate][index].scale * 0.01666667f;
        found = 0;
        if (*(unsigned short *)(self + 0x34) & 0x20) {
            colour = *(char **)(*(char **)(self + 0x68) + 0x10);
            if (colour != 0 && *(short *)colour != 0) {
                rgb[0] = *(unsigned char *)(colour + 4);
                rgb[1] = *(unsigned char *)(colour + 5);
                rgb[2] = *(unsigned char *)(colour + 6);
                found = 1;
            }
        }
        if (!found)
            func_002A04B8(slot->object, &rgb[0], &rgb[1], &rgb[2]);
        slot->active = 1;
        slot->flags = 0x8000;
        slot->tag = arg;
        slot->color = (rgb[2] << 16) + (rgb[1] << 8) + rgb[0];
        result = 0;
        slot->elapsed = 0;
        break;
    }
    return result;
}
