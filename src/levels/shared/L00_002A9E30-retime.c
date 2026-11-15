/* Source-shape reference: OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/hero_idle_and_animation.c. */
#include "common.h"

typedef struct { u8 pad0[0x10]; u8 count; } AnimationEntry;
/* GNU zero-length array for the variable animation table. */
typedef struct { u8 pad0[0x48]; AnimationEntry *entries[0]; } AnimationTable;
typedef struct AnimationOwner {
    u8 pad0[0x24];
    AnimationTable *table;
    u8 pad28[0x43 - 0x28];
    u8 index;
    u8 pad44[0x5c - 0x44];
    float *scale;
} AnimationOwner;
typedef struct {
    u8 pad0[0xc20];
    float value;
    float scale;
    int unknownC28;
    int flag;
    u8 padC30[8];
    float threshold;
    u8 padC3C[0x2290 - 0xc3c];
    AnimationOwner *owner;
} AnimationResident;
extern AnimationResident D_00189E20_2;
extern float func_002AA2E8(float *, float, float);

float func_L00_002A9E30(float arg0, float arg1, float arg2, float arg3)
{
    float threshold = D_00189E20_2.threshold;
    float step;
    float negone = -1.0f;
    if (threshold < arg0) {
        step = arg0 - threshold;
    } else {
        float rate = 2.0f;
        if (D_00189E20_2.flag == 0)
            rate = 0.5f / D_00189E20_2.scale;
        {
            AnimationOwner *owner = D_00189E20_2.owner;
            int index = owner->index;
            AnimationEntry *entry = owner->table->entries[index];
            int count = entry->count;
            step = arg0 + (rate * (float)count - threshold);
        }
    }
    if (0.0f < arg1) {
        float scale = D_00189E20_2.scale;
        if (D_00189E20_2.flag != 0)
            scale = *D_00189E20_2.owner->scale;
        {
            float value = (arg2 * step) / (arg1 * scale);
            if (arg3 == negone) {
                D_00189E20_2.value = value;
                return negone;
            }
            return ApproachValue(&D_00189E20_2.value, value, arg3);
        }
    }
    return 0.0f;
}
