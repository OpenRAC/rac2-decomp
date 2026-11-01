#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *func_0029EFD0(void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(char *, char *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_00282948(void *);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[];
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, unsigned int, int, float);
extern void func_L04_00358868(void *, unsigned int, int, int, float);
extern unsigned char *func_L04_0035F3E0(void *, void *, int, float);
extern void func_L04_003F9C60(void *, int);
extern void func_0029F338(void *);
extern float func_002A7AA8(float, float, float, float, float);
extern char D_L04_001B0448[];
extern char D_L04_001B9680[];
extern char D_L04_001B98D0[];
extern float func_00282E80(void *, void *);
extern int func_00278E78(void);
extern float func_00283B98(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
typedef struct __attribute__((packed, aligned(4))) { long a; int b; } TurnRecord;

/* Moves a homing shot with its trail of followers; breaks up on contact, on timeout or out of bounds. */
void func_PAL_L04_003FD8F0(unsigned char *m)
{
    float old[4];
    TurnRecord turn = *(TurnRecord *)D_L04_001B0448;
    SweepProbe probe;
    float delta[4], random[4], spark[4], velocity[4];
    unsigned char *v = *(unsigned char **)(m + 0x68), *particle;
    int i, count, age;
    unsigned char **trail;
    float scale, length;
    qcopy(old, (m + 0x10));
    func_00282CC0(m + 0x10, m + 0x10, v);
    if (*(float *)(m + 0x10) < 0 || *(float *)(m + 0x14) < 0 ||
        *(float *)(m + 0x18) < 0 || 64.0f < func_00282E80(m + 0x10, D_L04_001B9680)) {
        func_L04_003F9C60(m, 0);
        func_0029F338(m);
        return;
    }
    probe.owner = *(void **)(v + 0x18);
    probe.flags = 0x30000;
    probe.radius = 13;
    probe.active = 1;
    *(QuadWord *)probe.v = *(QuadWord *)v;
    func_00282F70(&probe, &probe, 1);
    probe.v[2] = 1;
    probe.v[3] = 5627.9248046875f;
    probe.mode = 1;
    probe.enabled = 1;
    probe.kind = *(unsigned short *)(m + 0xAA);
    if (func_00282948(v + 0x10)) {
        func_L04_003F9C60(m, 0);
        func_0029F338(m);
        return;
    }
    if (func_002761F8(old, m + 0x10, 0, *(void **)(v + 0x18), &probe)) {
        if (!func_00278E78()) {
            if (*(int *)(v + 0x10) >= 3) *(int *)(v + 0x10) = 2;
        } else {
            qcopy((m + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = func_002A7878(-1, 1);
                random[1] = func_002A7878(-1, 1);
                random[2] = func_002A7878(-1, 1);
                *(QuadWord *)delta = *(QuadWord *)random;
                func_00283028(random, v, D_L04_001BFB00);
                func_00282F20((char *)delta, (char *)delta, func_00282DF0(random) * 0.5f);
                func_00282CC0(random, random, delta);
                func_00282F20((char *)random, (char *)random, func_002A7878(0.060000002f, 0.120000005f));
                func_L04_00358AE8(m + 0x10, random, 0x7F2F4F6F, func_002A7820(8, 12), 30000);
            }
            func_L04_003F9C60(m, 0);
            func_0029F338(m);
            return;
        }
    }
    *(float *)(m + 0xF4) = func_00283B98(*(float *)(m + 0xF4), ((float *)&turn)[1]);
    age = *(int *)(v + 0x14) - *(int *)(v + 0x10);
    if (age < 11) scale = (func_00283CE0(age) / func_00283CE0(11)) * 0.15f;
    else scale = 0.15f;
    func_00282CF0(delta, old, m + 0x10);
    func_00282F20((char *)delta, (char *)delta, scale);
    qcopy(random, (m + 0x10));
    { unsigned char *head = *(unsigned char **)(v + 0x1C);
      if (head) qcopy(head + 0x10, random); }
    for (count = 0; count < 16; count++) {
        particle = ((unsigned char **)(v + 0x20))[count];
        if (particle) {
            func_00282CC0(particle + 0x10, random, delta);
            qcopy(random, (particle + 0x10));
            *(float *)(particle + 0x10) += func_002A78D8(0, 0.075f);
            *(float *)(particle + 0x14) += func_002A78D8(0, 0.075f);
            *(float *)(particle + 0x18) += func_002A78D8(0, 0.075f);
            func_00282D30(delta, delta, 0.85f);
        }
    }
    if (func_002A77E0(5) == 0) {
        func_00282DD8(spark, delta, D_L04_001B98D0);
        func_002ACEC0(spark, spark, delta, func_002A78D8(0, 3.1415927f));
        length = func_00282DF0(spark);
        if (length != 0) {
            func_00282D30(velocity, spark, func_002A7878(0.010000001f, 0.040000003f) / length);
            func_L04_00358AE8(m + 0x10, velocity, 0x7F2F4F6F, func_002A7820(8, 12), 30000);
        }
    }
}
