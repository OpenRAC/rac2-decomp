/* functional: high. From the 2026-10-29 near miss, reread against retail: fixed the hero-timer condition (retail polls +0x2534 when +0x1500 is set or the state is 29) and func_L00_0032A088's second argument (retail passes the slot index still in a1). */
/* func_L00_003B5BF8: update of a hero weapon emitter. State 0 allocates its slot (25 rows of 0x280, a 0x20D0 block,
   a zeroed 25-word table, a second 25-row table) and records the offsets; states 1/2 fire the primary or the
   charged shot when the buttons, ammo and hero state allow, and spawn the shot through func_L00_0041C2D0. */

#include "common.h"

#define I_3B5BF8(p, o) (*(int *)((char *)(p) + (o)))
#define F_3B5BF8(p, o) (*(float *)((char *)(p) + (o)))
#define H_3B5BF8(p, o) (*(short *)((char *)(p) + (o)))
#define B_3B5BF8(p, o) (*(unsigned char *)((char *)(p) + (o)))

typedef struct { char pad[0x54]; float rate; char rest[0x88]; } WeaponEntry_3B5BF8;

extern unsigned char D_00189E20[];
extern unsigned int D_00138320;
extern unsigned char D_0013957E;
extern WeaponEntry_3B5BF8 D_L00_00262570[];

extern void func_L00_003B6158(unsigned char *);
extern void func_L00_003B60E8(void *);
extern int func_L00_002D4040(int);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern int func_L00_00329E90(void *, void (*)(void *), int *);
extern unsigned char *func_L00_0032A088(int, int);
extern int func_L00_00329FF0(int);
extern unsigned char *func_L00_0032A0B8(int, int);
extern void func_00282A88(void *, int);
extern int func_00282948(int *);
extern int func_002829D8(float *);
extern int func_L00_002B3998(float);
extern void func_L00_002AF568(void);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern int func_L00_002D3F30(int, int);
extern int func_002E5CF8(int, int, void *);
extern char *func_L00_0041C2D0(void *, void *, int, int, void *, int);

void func_L00_003B5BF8(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    int existing;
    int slot;
    char *base, *cursor, *table;
    unsigned char *offsets;
    char *held, *shot;
    int third;
    int i;
    int triggered, secondary, finished, allowed;
    unsigned int color;

    func_L00_003B6158(object);

    if (I_3B5BF8(D_00189E20, 0x1500) != 0 || I_3B5BF8(D_00189E20, 0x2294) == 29 || I_3B5BF8(D_00189E20, 0x2294) == 1) {
        if (0.0f < F_3B5BF8(state, 0xC)) {
            if (func_L00_002D4040(-1) != 0)
                color = 0x600000FF;
            else
                color = 0x600FFF0F;
        } else {
            color = 0x600FFF0F;
        }
        func_00273318(object, 1.0f, color, 0, 38, 0.0f, -1, 90.0f, 4);
    }

    switch (object[0x20]) {
    case 0:
        slot = func_L00_00329E90(object, func_L00_003B60E8, &existing);
        I_3B5BF8(state, 0) = slot;
        if (existing == 0) {
            base = (char *)func_L00_0032A088(H_3B5BF8(object, 0xAA), slot);
            cursor = (char *)func_L00_00329FF0((int)(base + 100));
            table = base;
            for (i = 24; i >= 0; i--) {
                *(char **)table = cursor;
                cursor += 0x280;
                table += 4;
            }
            cursor = (char *)func_L00_00329FF0((int)cursor);
            I_3B5BF8(state, 4) = cursor - base;
            func_00282A88(cursor, 0x20D0);
            cursor = (char *)func_L00_00329FF0((int)(cursor + 0x20D0));
            I_3B5BF8(state, 8) = cursor - base;
            for (i = 24; i >= 0; i--)
                ((int *)cursor)[i] = 0;
            cursor = (char *)func_L00_00329FF0((int)(cursor + 100));
            third = cursor - base;
            table = cursor;
            cursor = (char *)func_L00_00329FF0((int)(table + 100));
            for (i = 24; i >= 0; i--) {
                *(char **)table = cursor;
                cursor += 0x280;
                table += 4;
            }
            offsets = func_L00_0032A0B8(H_3B5BF8(object, 0xAA), I_3B5BF8(state, 0));
            I_3B5BF8(offsets, 0) = I_3B5BF8(state, 4);
            I_3B5BF8(offsets, 8) = third;
            I_3B5BF8(offsets, 4) = I_3B5BF8(state, 8);
        }
        object[0x20] = 1;
        H_3B5BF8(state, 0x1C) = 4;
        H_3B5BF8(state, 0x1E) = 0;
        I_3B5BF8(state, 0xC) = 0;
        I_3B5BF8(state, 0x14) = 0;
        I_3B5BF8(state, 0x18) = 0;
        return;

    case 1:
    case 2:
        triggered = 0;
        secondary = 0;
        finished = 0;
        allowed = 1;
        if (I_3B5BF8(D_00189E20, 0x1500) != 0 || I_3B5BF8(D_00189E20, 0x2294) == 29) {
            if (func_00282948((int *)(D_00189E20 + 0x2534)) == 0)
                allowed = 0;
        } else {
            I_3B5BF8(D_00189E20, 0x2534) = 40;
        }

        if (object[0x20] == 1) {
            if (func_002829D8((float *)(state + 0xC)) != 0 && allowed != 0
                && (D_00138320 & I_3B5BF8(D_00189E20, 0x1230)) != 0
                && I_3B5BF8(D_00189E20, 0x1240) >= 23
                && (I_3B5BF8(D_00189E20, 0x1500) != 0 || I_3B5BF8(D_00189E20, 0x2294) == 1
                    || I_3B5BF8(D_00189E20, 0x2294) == 29)
                && func_L00_002D4040(22) != 0) {
                triggered = 1;
                F_3B5BF8(state, 0xC) = 1.0f / D_L00_00262570[D_0013957E].rate;
            }

            if (I_3B5BF8(D_00189E20, 0x2294) == 131 && I_3B5BF8(D_00189E20, 0xC2C) == 0
                && func_L00_002B3998(33.0f) != 0)
                secondary = func_L00_002D4040(22) != 0;

            if (I_3B5BF8(D_00189E20, 0x229C) == 4 && allowed != 0 && B_3B5BF8(D_00189E20, 0x49C) == 0
                && F_3B5BF8(state, 0xC) == 0.0f && (D_00138320 & 0x20) != 0
                && I_3B5BF8(D_00189E20, 0x1240) >= 23 && func_L00_002D4040(22) != 0) {
                func_L00_002AF568();
                held = *(char **)(D_00189E20 + 0xE98);
                if (held != 0) {
                    F_3B5BF8(held, 8) = 0.0f;
                    func_L00_00311080(*(void **)(D_00189E20 + 0x2290), held, I_3B5BF8(D_00189E20, 0x24B0), 1, 1, 1);
                }
                object[0x20] = 2;
                I_3B5BF8(state, 0x10) = 8;
                F_3B5BF8(state, 0xC) = 1.0f / D_L00_00262570[D_0013957E].rate;
            }
        } else if (func_00282948((int *)(state + 0x10)) != 0) {
            finished = 1;
            object[0x20] = 1;
        }

        if (triggered != 0 || secondary != 0 || finished != 0) {
            func_L00_002D3F30(-1, 1);
            func_002E5CF8(2, 0, object);
            shot = func_L00_0041C2D0(object, object + 0x10, triggered, I_3B5BF8(state, 0), *(void **)(state + 0x14), 1);
            if (shot != 0)
                *(void **)(shot + 0xB8) = object;
        }
        return;
    }
}

#undef I_3B5BF8
#undef F_3B5BF8
#undef H_3B5BF8
#undef B_3B5BF8
