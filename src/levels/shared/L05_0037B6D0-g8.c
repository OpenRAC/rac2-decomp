#include "common.h"

/* The gate's word at $gp-0x2B14 is a small index into a table of live sub-objects. */
extern int D_L05_001AC4DC __attribute__((sda));

extern char D_L05_00221D10[];
extern char D_L05_00225DD0[];

extern char *func_379CA0(char *object);
extern int func_37CDB0(char *object);

extern int func_L05_003CFC28(int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);

/* The reach table the object's id indexes, at $gp+0xB78. */
extern float D_L05_001AFB68 __attribute__((sda));

extern int D_001A79F0;

extern char *func_002ED688(char *object);

extern void func_L05_00379FA0(char *, int, int, int, float, float, float, float, int, int, int);

extern int func_002A77E0(int);

extern void func_002E5DA0(int, int, char *, int);

/* Decides whether the object may take its next step: the gate must be open, the looked-up
 * sub-object must exist, its handle must match the one the gate's table names, it must not be
 * already counting, its two counters must be ordered, and its state must be neither 3 nor 0xD.
 * The last test writes 0 rather than branching. */
int func_L05_0037B888(char *a0)
{
    char *object = a0;
    char *sub = func_379CA0(a0);
    char *gate = D_L05_00221D10;
    int ready = 1;

    if (*(int *)(gate + 0x2C) == 1)
        return 0;
    if (sub == 0)
        return 0;
    if (*(short *)(object + 0xAA) != *(short *)(((char **)D_L05_00225DD0)[D_L05_001AC4DC] + 0xAA))
        return 0;
    if (*(int *)(sub + 0x118) == 1)
        return 0;
    if (*(int *)(gate + 0xC) >= *(int *)(gate + 0x20))
        return 0;
    if (func_37CDB0(object) == 3)
        return 0;
    if (func_37CDB0(object) == 0xD)
        ready = 0;
    return ready;
}

/* Gives the object a random reach, three random angles and a random cone, and writes the
 * scaled results into its state. */
void func_L05_003CF9C8(char *obj)
{
    char *s0 = obj;
    char *s1 = *(char **)(obj + 0x68);
    float f0;
    float f1;
    float f20;
    float f21;
    float f22;
    int idx;

    *(unsigned char *)(s0 + 0x30) = 0xFF;
    *(unsigned short *)(s0 + 0x32) = 0x1FF;
    idx = func_L05_003CFC28(*(short *)(s0 + 0xAA));
    f21 = 0.0f;
    f20 = 0.01745329424738884f;
    f22 = 1.0f;
    f1 = *(float *)(s0 + 0x2C) * *(float *)((char *)&D_L05_001AFB68 + 4 * idx);
    *(float *)(s0 + 0x2C) = f1;
    f0 = func_002A7940();
    *(float *)(s0 + 0xF0) = f0;
    f0 = func_002A7940();
    *(float *)(s0 + 0xF4) = f0;
    f0 = func_002A7940();
    *(float *)(s0 + 0xF8) = f0;
    f0 = func_002A7878(f21, 0.5f) * f20;
    *(float *)(s1 + 0x0) = f0;
    f0 = func_002A7878(f21, f22) * f20;
    *(float *)(s1 + 0x4) = f0;
    f0 = func_002A7878(f21, 2.0f) * f20;
    *(float *)(s1 + 0x8) = f0;
    *(float *)(s1 + 0xC) = f22;
}

/* Spawns the object's effect once its guards clear, then runs the timer and marks the run.
 * The two words of the effect's parameters are the same in both calls, so the compiler
 * loads the constant once and copies it into the two argument registers. */
void func_L05_003D0420(char *obj)
{
    char *s1 = *(char **)(obj + 0x68);
    char *r;

    r = func_002ED688(obj);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x1B8) != 0)
        return;
    if (*(unsigned char *)(obj + 0x20) == 1) {
        if (D_001A79F0 == 0xF)
            func_L05_00379FA0(obj, 0x60008000, 1, 0, 0.6f, 2.0f, 1.0f, 1.0f, 0, -1, 0);
        else
            func_L05_00379FA0(obj, 0x60008000, 1, 0, 1.0f, 2.0f, 1.0f, 1.0f, 0, -1, 0);
    }
    if (func_002A77E0(3) == 0)
        func_002E5DA0(0, 0, obj, 0x957);
    *(int *)(s1 + 0x1B8) = 0x14;
}

extern void func_L05_003CFB90(char *, char *);
extern float func_00282E48(void *, void *);

typedef struct {
    char pad000[0x140];
    float f140[4];
    char pad150[0x10];
    float f160;
    int f164;
    int f168;
    int f16C;
} ShakeCamera_003CFAB8;
extern ShakeCamera_003CFAB8 D_L05_001B9580;

/* When the camera is within the object's reach and the object is not class 0x956, passes the
 * camera position to func_L05_003CFB90, calls func_002E5DA0 and starts a camera shake (weaker
 * and shorter for class 0x955). The shake stores are the same in both arms; cross-jumping
 * shares them after scheduling. */
void func_L05_003CFAB8(char *obj)
{
    float reach = *(float *)((char *)&D_L05_001AFB68 + 4 * func_L05_003CFC28(*(short *)(obj + 0xAA)));

    if (func_00282E48(obj + 0x10, D_L05_001B9580.f140) <= reach && *(short *)(obj + 0xAA) != 0x956) {
        func_L05_003CFB90(obj, (char *)D_L05_001B9580.f140);
        func_002E5DA0(7, 0, obj, 0xFBF);
        if (*(short *)(obj + 0xAA) == 0x955) {
            D_L05_001B9580.f160 = 0.05f;
            D_L05_001B9580.f168 = 0x1E;
            D_L05_001B9580.f16C = 0;
        } else {
            D_L05_001B9580.f160 = 0.15f;
            D_L05_001B9580.f168 = 0x3C;
            D_L05_001B9580.f16C = 0;
        }
    }
}

/* The twenty-four 0xB0-byte records at D_L05_00233560 (the layout L05_0037B6D0.c uses). */
typedef struct {
    float f[38];
    int timer;
    char *owner;
    int active;
    int pad;
    int dying;
    int pad2;
} Record233560;

/* The hit record func_00277F48 submits (func_L05_00397F48 builds the same one). */
typedef struct {
    float v[4];
    char *owner;
    int flags;
    unsigned char kind;
    unsigned char mode;
    unsigned short id;
    float value;
    int one;
} HitRecord97B30;

extern Record233560 D_L05_00233560[24];
extern char D_L05_001BFB20[];
extern char D_L05_001BFB30[];
extern float D_L05_001AEBE8 __attribute__((sda));
extern float D_L05_001AEBE4 __attribute__((sda));
extern float D_L05_001AEBE0 __attribute__((sda));
extern float D_L05_001AEBDC __attribute__((sda));

extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);
extern int func_00282948(void *);
extern void func_L05_003D1E60(void *, int, int);
extern void func_0029F338(void *);
extern void func_002AF000(void *, float, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L05_00398378(void *, void *, int);
extern void func_L05_00398618(char *);
extern void func_L05_00398018(char *);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern int func_00277F48(void *, float, int, char *, void *);
extern int func_00278E78(void);
extern int func_00277258(void *, float, int, void *);
extern void func_L05_00397F48(char *, char *, char *);
extern void func_L05_00424990(char *, int, int, int, int, int, int, int, int, int, int, float);

/* Moves the projectile along its velocity, slowing it and spinning its two angles. When its life
   runs out or it leaves the 2..1021 box it releases all twenty-four records, bursts and removes
   itself. Each time its second timer expires it throws a hit record towards a random point 21
   units away. On hitting the world it submits its hit record, bursts and removes itself. */
void func_L05_00397B30(char *obj)
{
    float old[4];
    float target[4];
    HitRecord97B30 hit;
    char *state = *(char **)(obj + 0x68);
    float speed;
    int i;
    int collided;

    qcopy(old, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, state);
    speed = func_00282DF0(state);
    if (*(int *)(state + 0x24))
        speed *= 0.986f;
    else
        speed *= 0.982f;
    func_00282F20(state, state, speed);
    *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8), 0.05f);
    *(float *)(obj + 0xF4) = func_00283B98(*(float *)(obj + 0xF4), 0.03f);

    if (func_00282948(state + 0x18)) {
        for (i = 0; i < 24; i++)
            D_L05_00233560[i].owner = 0;
        func_L05_003D1E60(obj + 0x10, 0, 0);
        func_0029F338(obj);
        return;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        for (i = 0; i < 24; i++)
            D_L05_00233560[i].owner = 0;
        func_L05_003D1E60(obj + 0x10, 0, 0);
        func_0029F338(obj);
        return;
    }

    if (func_00282948(state + 0x28)) {
        func_002AF000(target, 21.0f, func_002A7940(), func_002A7940());
        func_00282CC0(target, target, obj + 0x10);
        if (func_002761F8(obj + 0x10, target, 0, obj, 0))
            qcopy(target, D_L05_001BFB20);
        func_L05_00398378(obj, target, 1);
        func_L05_00398618(obj);
        func_L00_002E6EF8(func_L05_00398018, obj);

        hit.owner = obj;
        hit.flags = 0x810000;
        if (*(int *)(state + 0x24))
            hit.value = D_L05_001AEBE8;
        else
            hit.value = D_L05_001AEBE4;
        hit.one = 1;
        qcopy(hit.v, state);
        func_00282F20(hit.v, hit.v, 1.0f);
        hit.kind = 3;
        hit.v[3] = 5627.925f;
        hit.mode = 2;
        hit.id = *(unsigned short *)(obj + 0xAA);
        if (*(int *)(state + 0x24))
            speed = D_L05_001AEBE0;
        else
            speed = D_L05_001AEBDC;
        func_00277F48(obj + 0x10, speed, 1, *(char **)(state + 0x20), &hit);
    }

    if (func_00278E78() != 6) {
        collided = 0;
        if (func_00277258(obj + 0x10, 1.0f, 16, *(void **)(state + 0x20))) {
            collided = 1;
            qcopy(obj + 0x10, D_L05_001BFB30);
        }
        if (collided || func_002761F8(old, obj + 0x10, 16, *(void **)(state + 0x20), 0)) {
            qcopy(obj + 0x10, D_L05_001BFB20);
            func_L05_00397F48(obj, state, obj + 0x10);
            if (*(int *)(state + 0x24))
                func_L05_00424990(obj + 0x10, 0, 50, 30, 30, 30, 40, 1, 1, 1, 1, 2.0f);
            func_L05_003D1E60(obj + 0x10, 0, 0);
            func_0029F338(obj);
        }
    }
}
