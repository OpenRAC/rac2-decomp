#include "include_asm.h"
/* func_L00_002CA4E0: picks a weighted idle choice for the hero.
 * Built with -fno-rerun-loop-opt: one loop pass leaves -1 inside the first loop (retail
 * keeps the origin pointer in $fp), and the count-down sum loop gives retail's order.
 * The group around `draw = value` ends cse1's block after the call, so the sampling
 * numerator stays a separate 1.0 that cse2 turns into retail's `mov.s $f13,$f21`.
 */
#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef union { Vector q; float f[4]; } ChoiceVector;
typedef struct {
    unsigned char pad0[0xE0]; float origin[4];
    unsigned char pad1[0x1B8 - 0xF0]; int count;
    unsigned char pad2[0x208 - 0x1BC]; short gate;
    unsigned char pad3[0xC28 - 0x20A]; int flags;
    unsigned char pad4[0x2290 - 0xC2C]; void *object;
    unsigned char pad5[0x22A4 - 0x2294]; int mode;
    unsigned char pad6[0x22BB - 0x22A8]; unsigned char byte_22bb;
    unsigned char pad7[0x24CC - 0x22BC]; int state;
} HeroChoiceState;
extern HeroChoiceState D_00189E20;
extern int D_001A79F0 __attribute__((sda));
extern int D_001A7398 __attribute__((sda));
extern unsigned char D_00139568[];
typedef struct { unsigned char pad0[4]; unsigned char active; unsigned char pad1[0xE0 - 5]; } MappedClassEntry;
extern MappedClassEntry D_L00_00262570[];
typedef struct {
    unsigned char pad0[0x50]; int selector;
    unsigned char pad1[4]; float weight;
    unsigned char pad2[4]; int inactive;
    unsigned char pad3[12];
} ChoiceRecord;
extern ChoiceRecord D_L00_0025BC00[4];
extern int D_L00_0025BDB0;
extern int func_L00_002ADEA0(int);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_002A7878(float, float);

int func_L00_002CA4E0(int *selected)
{
    int choices[20], count = 0, index;
    ChoiceRecord *entry;
    ChoiceVector raised, origin;
    float sum, draw, value;
    if (D_00189E20.gate != 0) return 0;
    if (D_00189E20.state == 1) {
        *selected = 3;
        if (D_L00_0025BDB0 != 0) return 0;
        if ((D_00189E20.flags & 2) == 0) return 0;
        return func_002A7878(0.0f, 1.0f) < 0.33f;
    }
    entry = D_L00_0025BC00;
    for (index = 0; index < 4; index++, entry++) {
        float zero = 0.0f;
        int area;
        if (entry->inactive != 0 || entry->weight == zero) continue;
        area = func_L00_002ADEA0(0);
        if (entry->selector != -1 && entry->selector != area) continue;
        if (index == 2) {
            if (D_001A79F0 != 7 && D_001A79F0 != 0x13) continue;
            if (D_00189E20.byte_22bb == 2) continue;
            qcopy(&origin, D_00189E20.origin);
            qcopy(&raised, &origin);
            raised.f[2] += 8.0f;
            if (func_002761F8(&origin, &raised, 2, D_00189E20.object, 0)) continue;
        }
        if (index == 3 && (D_00189E20.mode != 1 || D_00189E20.count > 50 || D_00189E20.state > 1)) continue;
        choices[count++] = index;
    }
    if (!count) return 0;
    sum = 0.0f;
    if (count > 0) {
        int size = sizeof(ChoiceRecord);
        int *p = choices;
        index = count;
        do {
            ChoiceRecord *r = (ChoiceRecord *)((char *)D_L00_0025BC00 + *p * size);
            sum += 1.0f / (float)(int)(r->weight * 60.0f);
            p++;
        } while (--index != 0);
    }
    value = func_002A7878(0.0f, 1.0f);
    do { draw = value; } while (0);
    if (draw < sum) {
        float one, rate;
        ChoiceRecord *table;
        int size;
        int *cursor;
        one = 1.0f;
        table = D_L00_0025BC00;
        size = sizeof(ChoiceRecord);
        rate = 60.0f;
        cursor = choices;
        for (index = 0; index < count; index++, cursor++) {
            int choice = *cursor;
            *selected = choice;
            sum -= one / (float)(int)(*(float *)((char *)table + choice * size + 0x58) * rate);
            if (sum < draw) break;
        }
        if (D_001A7398 == 30 && (D_L00_00262570 + D_00139568[30])->active == 0) {
            if (*selected == 1) *selected = 0x91;
            else if (*selected == 2) *selected = 0x92;
        }
        return 1;
    }
    return 0;
}
