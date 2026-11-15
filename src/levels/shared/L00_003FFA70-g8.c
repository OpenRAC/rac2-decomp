#include "include_asm.h"

extern unsigned char *D_L00_001B0CA0 __attribute__((sda));

extern int D_L00_001B2C14 __attribute__((sda));

extern int *D_L00_001B0DB0 __attribute__((sda));

int func_L00_00400F38(char *arg)
{
    unsigned char *p = D_L00_001B0CA0;
    if (!p) {
        return 0;
    }
    return (unsigned int)(p[32] - 5) < 3;
}

int func_L00_00401E28(void)
{
    if (!D_L00_001B0CA0) {
        return 0;
    }
    return D_L00_001B2C14;
}

void func_L00_00402DB8(char *arg)
{
    int *p = D_L00_001B0DB0;
    if (p) {
        int *q = (int *)p[26];
        q[10] = 1;
    }
}

extern void func_L00_00402DB8(char *arg);

void func_L00_004028C0(char *arg, int value)
{
    unsigned char *p = D_L00_001B0CA0;
    int *o;

    if (!p) {
        return;
    }
    o = *(int **)(p + 104);
    p[32] = (arg != 0) ? 5 : 7;
    func_L00_00402DB8(arg);
    if (value != -1) {
        o[24] = value;
    } else {
        o[24] = 10;
    }
}

extern int D_L00_001B19C8_1[] __attribute__((sda));
extern char *D_L00_001B1EA8_1[] __attribute__((sda));
extern float D_L00_001B0C90 __attribute__((sda));

extern float func_002EE2B0(char *a, char *b);
extern void func_00381F80(char *a, char *b);

/* walks the object list once the shared flag is set, stopping at either special state and
   otherwise acting on the entries whose handle reports type 0x13 */
void func_L00_00401D50(char *arg)
{
    char *o;

    if ((D_L00_001B19C8_1[0] & 1) == 0)
        return;

    for (o = D_L00_001B1EA8_1[0]; o != 0; o = *(char **)(o + 40)) {
        unsigned char state = *(unsigned char *)(o + 32);

        if (state == 0xFE)
            return;
        if (state == 0xFD)
            return;
        if (o == 0 || *(int *)(o + 36) == 0 || *(short *)(*(int *)(o + 36) + 70) != 0x13)
            continue;
        if (func_002EE2B0(o + 16, arg + 16) < D_L00_001B0C90)
            func_00381F80(o, arg);
    }
}

extern char D_00189E20[];
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001A8F00;
extern int D_L00_001A8F08;
extern int D_L00_001A8FF4;
extern void func_0029FCC0(void *obj, int a, void *out);
extern void func_002FDF40(void *out, void *pos, int a, int b, float c, float d, float e, float f);
extern int func_002FE5A0(void *a, void *b, void *c, void *d, void *e, void *f, void *g, float h);
extern int func_00300540(int surface);
extern void func_002FE8D8(void *a, void *b);
extern float func_00282DB0(void *a, void *b);
extern int func_00282948(void *timer);
extern int func_L00_002D3F30(int a, int b);
extern int func_002B0CE0(int a, int b, int c);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int a, int b, void *obj);
extern void func_L00_002AF7D0(void);
extern char *func_L00_004005B0(void *pos, void *offset);
/* func_L00_002E6EF8 in most levels; another function in levels 08, 09, 19 and 30 */
extern void ref_L00_004029E8_00(void (*f)(char *), char *arg);
extern void func_L00_00402DD8(char *arg);

/* per-frame update of a four-state object: probes the ground below it (ctx+44 set means
   "not usable now": global flags, a blocking surface, some player states or attached/hit
   object types, or a ground normal too steep), then 0/1 wait for the player's input to
   start (player+0x1E0 = 120 and a sound), 2 spawns a func_L00_004005B0 object after the
   ctx+32 timer, 3 returns to 1 after the timer; D_00189E20 is the player block */
/* Moby update: Tankbot Glove (class 3706). */
void func_L00_004029E8(char *obj)
{
    float pos[4], offset[4], normal[4];
    char *hit;
    int surface, blocked, ready;
    char *ctx = *(char **)(obj + 104);

    {
        char *player = D_00189E20;

        if (*(int *)(player + 0x1244) == 3)
            D_L00_001B0DB0 = 0;
        func_0029FCC0(obj, 0, pos);
        *(int *)(ctx + 44) = 0;
        func_002FDF40(offset, pos, 0, 0, 1.6f, *(int *)(player + 0x2294) == 29 ? 11.0f : 4.5f,
                      0.13333334f, 0.0030555557f);
    }
    *(int *)(ctx + 36) = func_002FE5A0(pos, offset, ctx, ctx + 16, obj, &hit, &surface, 0.0030555557f);
    blocked = func_00300540(surface);
    if (D_L00_001A8F00 != 0 || D_L00_001A8F08 != -2)
        *(int *)(ctx + 44) = 1;
    if (D_L00_001A8FF4 != 0 && *(float *)(ctx + 8) < 462.43f)
        *(int *)(ctx + 44) = 1;
    if (blocked || *(int *)(ctx + 36) == 0 || *(int *)(ctx + 40) == 0) {
        *(int *)(ctx + 44) = 1;
    } else {
        char *player = D_00189E20;
        int state = *(int *)(player + 0x2294);
        char *attached;

        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6
            || state == 116 || state == 129) {
            *(int *)(ctx + 44) = 1;
        } else if (((attached = *(char **)(player + 0x33C)) != 0
                    && (*(short *)(attached + 170) == 0x330 || *(short *)(attached + 170) == 0xB21))
                   || (hit != 0 && (*(short *)(hit + 170) == 0xB21 || *(short *)(hit + 170) == 0xB5B))) {
            *(int *)(ctx + 44) = 1;
        } else {
            func_002FE8D8(ctx, normal);
            if (func_00282DB0(ctx + 16, normal) < 0.75f)
                *(int *)(ctx + 44) = 1;
        }
    }
    {
        char *player = D_00189E20;

        ready = 1;
        if (*(int *)(player + 0x2294) == 29) {
            if (!func_00282948(player + 0x2534))
                ready = 0;
        } else {
            *(int *)(player + 0x2534) = 40;
        }
    }
    switch (*(unsigned char *)(obj + 32)) {
    case 0:
        D_L00_001B0DB0 = (int *)obj;
        obj[32] = 1;
        *(int *)(ctx + 40) = 1;
        *(int *)(ctx + 36) = 0;
    case 1: {
        char *player = D_00189E20;

        if ((D_00138324 & *(int *)(player + 0x1230)) && ready && !*(unsigned char *)(player + 0x22BC)
            && !*(int *)(ctx + 44)) {
            if (func_L00_002D3F30(-1, 1)) {
                *(short *)(player + 0x1E0) = 120;
                func_002B0CE0(6, 0, 1);
                func_L00_002AF568();
                obj[32] = 2;
                *(int *)(ctx + 32) = 12;
                *(int *)(ctx + 40) = 0;
            } else {
                func_002E5CF8(0, 0, obj);
            }
        }
        break;
    }
    case 2:
        if (func_00282948(ctx + 32)) {
            char *spawn = func_L00_004005B0(pos, offset);

            *(char **)(spawn + 184) = obj;
            func_L00_002AF7D0();
            obj[32] = 3;
            *(int *)(ctx + 32) = 5;
        }
        break;
    case 3:
        if (func_00282948(ctx + 32))
            obj[32] = 1;
        break;
    }
    ref_L00_004029E8_00(func_L00_00402DD8, obj);
}
