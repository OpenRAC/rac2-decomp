#include "include_asm.h"

extern int *D_L00_001B0DB0 __attribute__((sda));
extern char D_00189E20[];
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001A8F00;
extern int D_L00_001A8F08;
extern int D_L00_001A8FF4;
extern void func_0029FCC0(void *obj, int a, void *out);
extern void func_002FDF40(void *out, void *pos, int a, int b, float c, float d, float e, float f);
extern int func_PAL_002FF5F8(void *a, void *b, void *c, void *d, void *e, void *f, void *g, float h);
extern int func_00300540(int surface);
extern void func_002FE8D8(void *a, void *b);
extern float func_00282DB0(void *a, void *b);
extern int func_00282948(void *timer);
extern int func_L00_002D3F30(int a, int b);
extern int func_002B0CE0(int a, int b, int c);
extern void func_PAL_L00_002AF458(void);
extern int func_002E5CF8(int a, int b, void *obj);
extern void func_PAL_L00_002AF6C0(void);
extern char *func_L00_004005B0(void *pos, void *offset);
extern void ref_L00_004029E8_00(void (*f)(char *), char *arg);
extern void func_PAL_L00_00407728(char *arg);

/* per-frame update of a four-state object: probes the ground below it (ctx+44 set means
   "not usable now": global flags, a blocking surface, some player states or attached/hit
   object types, or a ground normal too steep), then 0/1 wait for the player's input to
   start (player+0x1E0 = 120 and a sound), 2 spawns a func_L00_004005B0 object after the
   ctx+32 timer, 3 returns to 1 after the timer; D_00189E20 is the player block */
void func_PAL_L00_00407338(char *obj)
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
                      0.16000001f, 0.0044f);
    }
    *(int *)(ctx + 36) = func_PAL_002FF5F8(pos, offset, ctx, ctx + 16, obj, &hit, &surface, 0.0044f);
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
            *(int *)(player + 0x2534) = 33;
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
                func_PAL_L00_002AF458();
                obj[32] = 2;
                *(int *)(ctx + 32) = 10;
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
            func_PAL_L00_002AF6C0();
            obj[32] = 3;
            *(int *)(ctx + 32) = 4;
        }
        break;
    case 3:
        if (func_00282948(ctx + 32))
            obj[32] = 1;
        break;
    }
    ref_L00_004029E8_00(func_PAL_L00_00407728, obj);
}

#include "common.h"
extern int D_L00_001B043C __attribute__((sda));
extern void func_L00_00402DB8(void);
extern int D_PAL_001B0CD0 __attribute__((sda));

/* Writes the object's state byte (7 when arg0 is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value in the object's slot - 10 when it is -1. */
void func_PAL_L00_004071F0(int arg0, int arg1)
{
    char *p = (char *)D_PAL_001B0CD0;
    int a = arg1;
    char *q;

    if (p == 0)
        return;
    q = *(char **)(p + 0x68);
    if (arg0 != 0)
        p[0x20] = 5;
    else
        p[0x20] = 7;
    func_L00_00402DB8();
    if (a != -1)
        *(int *)(q + 0x60) = ((s32)(a) * 5 + 2) / 6;
    else
        *(int *)(q + 0x60) = 8;
}
