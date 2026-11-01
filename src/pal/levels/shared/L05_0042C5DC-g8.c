#include "include_asm.h"

#include "common.h"
extern float D_L05_001B153C __attribute__((sda));
extern float D_L05_001B1538 __attribute__((sda));
extern float D_L05_001B1534 __attribute__((sda));
extern float D_L05_001B1530 __attribute__((sda));
extern char *D_L05_001BFB18 __attribute__((nosda));
extern void func_00282F20(void *, void *, float);
extern int func_00277F48(void *, float, int, char *, void *);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern char *func_PAL_002BE9A8(void *, float, float, float, float, int, void *, u32, int);
extern int func_002A77E0(int);
typedef int ImpactTI __attribute__((mode(TI)));
typedef union { ImpactTI q; float f[4]; } ImpactVector;
typedef struct {
    ImpactVector pos;
    void *owner;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float scale;
    int one;
} ImpactParams;

/* Queues an impact request (func_00277F48) from the object at pos, then, when the
   object in D_L05_001BFB18 has class 0x956, spawns twenty spark particles there. */
void func_PAL_L05_0042D118(char *object, char *state, float *pos)
{
    ImpactParams p;
    ImpactVector origin, direction;
    int i;
    int spin;
    float a, b;
    float count, speed, spread;
    char *particle, *data;

    p.flags = 0x810000;
    p.owner = object;
    if (*(int *)(state + 0x24))
        p.scale = D_L05_001B153C;
    else
        p.scale = D_L05_001B1538;
    p.one = 1;
    qcopy(&p.pos, state);
    func_00282F20(&p, &p, 1.0f);
    p.pos.f[3] = 5627.925f;
    p.type = 3;
    p.subtype = 2;
    p.id = *(unsigned short *)(object + 0xAA);
    func_00277F48(pos, *(int *)(state + 0x24) ? D_L05_001B1534 : D_L05_001B1530,
                  1, *(char **)(state + 0x20), &p);
    if (D_L05_001BFB18 && *(short *)(D_L05_001BFB18 + 0xAA) == 0x956) {
        count = 20.0f;
        speed = 3.0f;
        spread = 2.0f;
        qcopy(&origin, object + 0x10);
        for (i = 0; (float)i < count; i++) {
            pos[0] = origin.f[0] + func_002A78D8(0.0f, spread);
            pos[1] = origin.f[1] + func_002A78D8(0.0f, spread);
            pos[2] = origin.f[2] + func_002A78D8(0.0f, spread);
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(&direction, 0.060000002f, a, b);
            spin = func_002A7820(-3, 3);
            particle = func_PAL_002BE9A8(pos, 0.0f, 1.0f, 1.0f, speed * 210000.0f, spin,
                                     &direction, 0x7fffffff, 0);
            if (particle) {
                *(short *)(particle + 0xA) = 100;
                data = particle + 0x20;
                particle[8] = func_002A77E0(255);
                particle[3] = 0x44;
                *(int *)(data + 4) = 2;
                data[0xA] = 127;
                data[0xB] = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}
