/* Retained reconstruction,30 October2026; not linked and no matching credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * 424/428 bytes; us 0/1, us2 0/1, pal absent.
 * Reviewed qcopy replaces the old volatile-TI stack spelling while retaining the
 * complete 16-byte union. Explicit source/destination cursors and late field snapshots
 * recover more of the loop/tail. Save ordering, loop setup and one instruction still
 * differ; -g ties. No fictitious stack argument or register pin is introduced.
 */
#include "common.h"

/* The 128-bit unit the copies move. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(void *out, void *in1, void *in2);

extern void func_L11_0046BC08(void *self);

extern void func_L14_00422498(void *self);

extern void func_L00_002E6EF8(void *self, void *other);

extern void func_L14_004228C0(char *object);

extern int func_00291308(void *a, int b, float c, float d);

extern int D_L14_001B1618 __attribute__((sda));
extern int D_L14_001B1680 __attribute__((sda));
extern int D_L14_001B1684 __attribute__((sda));
extern float D_L14_001B1688 __attribute__((sda));
extern float D_L14_001B168C __attribute__((sda));

extern int D_001FE1C0[];
extern char D_002594F0[];

typedef struct {
    int x;
    float y;
    int z;
} L14Vec;

/* The vector the state block holds, and the one the level's pulse adds to it. */
typedef union {
    TI128 q;
    L14Vec v;
} L14Buf;

/* Copies the owner's vector into its state block, eases the state's pulse, adds the pulse to
   the vector, then refreshes the group's live class-0x112B entities and resets the owner. */
void func_L14_004221D8(char *self)
{
    char *s2 = self;
    char *s1;
    char *s0;
    L14Buf buf;
    float f1;
    float f0;
    int count;
    int i;
    int *table;

    s1 = *(char **)(s2 + 0x68);
    s0 = s1 + 0x10;
    qcopy(s1, s2 + 0x10);
    qcopy(s0, s1);

    f1 = *(float *)(s1 + 0x20);
    f0 = (6.0f - f1) * 0.07f + 12.0f;
    f1 = f1 + f0;
    *(float *)(s1 + 0x20) = f1;

    buf.v.x = 0;
    buf.v.y = *(float *)(s1 + 0x20);
    buf.v.z = 0;
    func_00282CC0(s0, s1, &buf.v);

    qcopy(&buf, s0);
    D_L14_001B1618 = 20;
    func_L11_0046BC08(s2);

    if (*(int *)(s1 + 0x3C) != 0) {
        func_L14_00422498(s2);
        count = D_L14_001B1618;
        i = count - 4;
        table = &D_001FE1C0[*(int *)(s1 + 0x34)];
        if (i < count) {
            char *src = (char *)*table + i * 16 + 0x10;
            char *dst = D_002594F0 + *(int *)(s1 + 0x38) * 640 + i * 16;
            do {
                qcopy(dst, src);
                i++;
                src += 16;
                dst += 16;
            } while (i < count);
        }
        func_L00_002E6EF8((void *)func_L14_004228C0, s2);
    }

    if (*(unsigned char *)(s2 + 0x20) == 0) {
        *(int *)(s1 + 0x3C) = 0;
        *(int *)(s1 + 0x24) = func_00291308(s1, 0, 0.0f, 0.0f);
        *(unsigned char *)(s2 + 0x20) = 1;
        {
            int steps = D_L14_001B1618;
            int first = D_L14_001B1680;
            int second = D_L14_001B1684;
            float x = D_L14_001B1688;
            float y = D_L14_001B168C;
            *(int *)(s1 + 0x30) = -1;
            *(int *)(s1 + 0x2C) = steps;
            *(int *)(s1 + 0x48) = first;
            *(int *)(s1 + 0x4C) = second;
            *(float *)(s1 + 0x40) = x;
            *(float *)(s1 + 0x44) = y;
        }
    }
}
