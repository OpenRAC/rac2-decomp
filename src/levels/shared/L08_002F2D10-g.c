#include "common.h"

/* Sound fade step for a moving owner. Built with -g: without it cc1 emits 560 bytes.
 * Each adjustment arm takes its own record pointer; sharing `record` with the first
 * check swaps the a1/a2 scratch registers. */
typedef unsigned int SoundVectorQuad __attribute__((mode(TI)));
typedef union { SoundVectorQuad q; float f[4]; } SoundVector;
struct SoundRecordView { char unknown0[0x7e]; short id; char unknown80[4]; int level; void *owner; };
extern unsigned char D_00188660[];
extern const char D_L08_001AA400[];
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_0026FEB8(const char *, ...);
/* The sound table owner has unknown complete extent. Retail indexes 112-byte
 * records and accesses halfword +0x7e and words +0x84/+0x88 of that address view.
 * The two local vectors and the state's first vector are 16-byte aligned by the
 * retail lq/sq contract; no extra object extent or zero initialization is assumed. */
int func_L08_00339220(unsigned char *owner, unsigned char *state, int low, int high, float distance)
{
    SoundVector position;
    SoundVector difference;
    struct SoundRecordView *record;
    unsigned char *definition;
    int id, current, value;
    float near_distance, far_distance;
    if (*(void **)(state + 0x1c) != owner) return -1;
    record = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
    if (record->owner != owner) return -1;
    id = record->id;
    if (id != *(int *)(state + 0x18)) return -1;
    definition = *(unsigned char **)(*(unsigned char **)(owner + 0x24) + 0x28) + id * 32;
    if (low == -100000) low = *(int *)(definition + 0x10);
    if (high == -100000) high = *(int *)(definition + 0x14);
    current = record->level;
    far_distance = *(float *)(state + 0x14);
    near_distance = *(float *)(state + 0x10);
    if (distance < -999.0f) {
        func_00282CF0(&difference, owner + 0x10, state);
        position.q = difference.q;
        distance = func_00282DF0(&position);
    }
    value = (int)(((float)(high - low) / (far_distance - near_distance)) * (distance - near_distance) + (float)low);
    *(SoundVectorQuad *)state = *(SoundVectorQuad *)(owner + 0x10);
    if (current < value && current < high) {
        int delta = value - current;
        int step = delta < 251 ? delta : 250;
        int next;
        struct SoundRecordView *entry;
        if (step < 50) step = delta;
        entry = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
        next = entry->level + step;
        if (next < high) entry->level = next;
        else entry->level = high;
        return 1;
    }
    if (value < current && low < current) {
        int delta = current - value;
        int step = delta < 251 ? delta : 250;
        int next;
        struct SoundRecordView *entry;
        if (step < 50) step = delta;
        entry = (struct SoundRecordView *)(D_00188660 + *(int *)(state + 0x20) * 0x70);
        next = entry->level - step;
        if (next > low) entry->level = next;
        else entry->level = low;
        func_0026FEB8(D_L08_001AA400, value);
        return 2;
    }
    return 0;
}
