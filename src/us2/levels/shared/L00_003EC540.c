#include "include_asm.h"

/* func_US2_L00_003EC540, the USA v2.00 copy of func_L00_003EB0C0: the same C, where the entry
   count drops from 80 to 79 and the freed slot (0x40 + 79 * 0x50 = 0x18F0) keeps the z read at
   init, which replaces the -1.0f passed to func_002AEE70. */

extern int D_L00_001C9340;

extern void func_L00_00323448(char *, void *, int, int, int, int, int, int);

extern void func_0029F338(char *);

extern void func_002833F0(void *, void *);

extern float func_00283198(float);

extern void func_002AEE70(char *, void *, void *, float, float, float);

extern void func_002AEF28(char *, float, void *, float, void *, float);

extern void func_00283738(void *, void *, void *);

extern void func_002AB6D8(void *, void *);

extern void func_L00_00323958(char *, void *);

typedef struct {
    long long id;
    int flags;
    int level;
    float angles[3];
    int mode;
    float firstAngle;
    float firstVelocity;
    float secondAngle;
    float secondVelocity;
    float firstSpeed;
    float firstStep;
    float secondSpeed;
    float secondStep;
    char entries[0x4A];
    unsigned char present;
    char pad_8B[2];
    unsigned char update;
    char pad_8E[0x1862];
    float startZ;
} L00_003EC540_State;

void func_US2_L00_003EC540(char *self)
{
    float angles[4];
    char mat[48];
    L00_003EC540_State *st = *(L00_003EC540_State **)(self + 0x68);
    int i;
    int last;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (st->id == -1)
            break;
        {
            /* An int, not a byte constant: reload would otherwise reuse the -1 still in $v0. */
            int alpha = 255;
            *(unsigned char *)(self + 0x30) = alpha;
        }
        func_L00_00323448(self, st->entries, 0x4F, *((int *)&st->id + 1), *(int *)&st->id, st->flags, 7, 0);
        if (!st->present) {
            func_0029F338(self);
            break;
        }
        if (!st->mode) {
            st->update = 1;
            *(unsigned short *)(self + 0x34) |= 0x104;
            func_002833F0(self + 0xC0, self + 0xF0);
        }
        st->startZ = *(float *)(self + 0x18);
        if (st->firstAngle != 0.0f)
            st->firstAngle *= 0.01745329424738884f;
        st->firstVelocity = func_00283198(st->firstAngle) * st->firstSpeed;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L00_001C9340 != st->level)
            break;
        if (st->firstStep > 0.0f)
            func_002AEE70(self, &st->firstAngle, &st->firstVelocity, st->firstSpeed,
                          st->firstStep * 0.0002908882452175021f, st->startZ);
        if (st->secondStep > 0.0f) {
            func_002AEF28(self, st->secondSpeed * 0.01745329424738884f, &st->secondAngle,
                          st->secondStep * 0.0002908882452175021f, &st->secondVelocity, 0.00581776537001133f);
            if (st->update)
                func_002833F0(self + 0xC0, self + 0xF0);
        }
        if (!st->mode) {
            angles[0] = st->angles[0] * 0.0002908882452175021f;
            angles[1] = st->angles[1] * 0.0002908882452175021f;
            angles[2] = st->angles[2] * 0.0002908882452175021f;
            func_002833F0(mat, angles);
            func_00283738(self + 0xC0, self + 0xC0, mat);
            if (st->secondStep > 0.0f)
                func_002AB6D8(self + 0xC0, self + 0xF0);
        } else {
            i = 0;
            do {
                angles[0] = st->angles[0] * 0.0002908882452175021f;
                angles[1] = st->angles[1] * 0.0002908882452175021f;
                angles[2] = st->angles[2] * 0.0002908882452175021f;
                func_002833F0(mat, angles);
                func_00283738(st->entries + i * 0x50, st->entries + i * 0x50, mat);
                last = *(unsigned char *)(st->entries + i * 0x50 + 0x4A);
                i++;
            } while (last != 1);
        }
        func_L00_00323958(self, st->entries);
        break;
    }
}
