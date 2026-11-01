#include "include_asm.h"

#include "common.h"
extern int func_002ACD38(void *);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern int func_002AD470(void *, void *, void *, void *, void *, void *);
extern void func_002B00D8(void *, float *, float *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_002ABB78(void *);
extern char *func_002AD0B0(char *);
extern int func_002AD5F8(char *, char *, char *, char *, char *, char *);
typedef struct { char prefix[0x18]; char *target; char reserved[0xC]; float height; } ContactView;
extern char ref_L00_00312EB0_00[];

void func_PAL_00314318(unsigned char *object)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    char scratch[16] __attribute__((aligned(16)));
    char *data = *(char **)(object + 0x68);
    float height;
    float gravity;
    int hit = 0;
    ContactView *contact;
    if (!func_002ACD38(object + 0x10)) {
        func_002A7750(object, 5, -1);
        return;
    }
    if (*(char **)(data + 0xC)) {
        qzero_nc(scratch);
        func_002AD470(object, *(char **)(data + 0xC), data + 0x70,
                       scratch, object + 0x10, scratch);
    }
    qcopy(start, object + 0x10);
    func_002B00D8(object + 0x10, start, start, -0.5f);
    qcopy(end, start);
    func_002B00D8(object + 0x10, end, end, 1.5f);
    if (func_002761F8(start, end, 2, object, 0)) {
        hit = 1;
        height = *(float *)(ref_L00_00312EB0_00 + 0x28);
    } else {
        height = end[2];
    }
    if (hit) {
        contact = (ContactView *)ref_L00_00312EB0_00;
        if (contact->target) {
            if (func_002ABB78(contact->target)) {
                float x, y;
                x = *(float *)(contact->target + 0x10);
                *(float *)(data + 0x10) = x;
                *(float *)(object + 0x10) = x;
                y = *(float *)(contact->target + 0x14);
                *(float *)(data + 0x14) = y;
                *(float *)(object + 0x14) = y;
                *(float *)(object + 0x18) = contact->height;
                qcopy(data + 0x10, object + 0x10);
                func_002B00D8(object + 0x10, (float *)(data + 0x10), (float *)(data + 0x10), -0.5f);
            } else if (!*(char **)(data + 0xC) && func_002AD0B0(contact->target)) {
                char *target = contact->target;
                *(char **)(data + 0xC) = target;
                func_002AD5F8((char *)object, target, (char *)object + 0x10,
                               (char *)object + 0xF0, data + 0x70, scratch);
            }
        }
    }
    if (*(float *)(object + 0x18) <= height) {
        *(float *)(object + 0x18) = height;
        object[0xBC] = 0;
        *(int *)(data + 0x50) = 0;
    } else {
        object[0xBC] = 1;
        if (*(char **)(data + 0xC))
            *(float *)(data + 0x78) -= *(float *)(data + 0x50);
        else
            *(float *)(object + 0x18) -= *(float *)(data + 0x50);
        gravity = *(float *)(data + 0x50) + 0.00392f;
        *(float *)(data + 0x50) = gravity < 0.3f ? gravity : 0.3f;
    }
}
