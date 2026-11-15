#include "include_asm.h"
#include "common.h"

extern float D_L00_001AFA40 __attribute__((sda));

typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;

extern OBJ2 *D_L00_001AFBC0 __attribute__((sda));

typedef struct OBJ3 {
    char pad0[0x98];
    int f98;
} OBJ3;

extern int D_L00_001AFD7C __attribute__((sda));

extern OBJ3 *D_L00_0023DBA0[];

extern int D_L00_0023DCA0[];

/* Adds a pull toward the middle of the play area to a speed, stronger when close to the middle. */
void func_L00_003B7260(float x, float y, float unused_step, float *p, float *q)
{
    float s = -(D_L00_001AFA40 * 0.000277777785f) / (x * x + y * y);

    *p = *p + x * s;
    *q = *q + y * s;
}

/* Sets a flag on the current active helper object, if there is one. */
void func_L00_003B8138(void)
{
    OBJ2 *p = D_L00_001AFBC0;
    if (p != 0)
        p->f68->f28 = 1;
}

/* Puts back the saved values for all the listed objects. */
void func_L00_003B92D0(void)
{
    int n = D_L00_001AFD7C;
    int i;

    for (i = 0; i < n; i++)
        D_L00_0023DBA0[i]->f98 = D_L00_0023DCA0[i];
}

/* Saves a value from each listed object and then clears it. */
void func_L00_003B9290(void)
{
    int n = D_L00_001AFD7C;
    int i;

    for (i = 0; i < n; i++) {
        D_L00_0023DCA0[i] = D_L00_0023DBA0[i]->f98;
        D_L00_0023DBA0[i]->f98 = 0;
    }
}

extern int D_L00_001AFB98 __attribute__((sda));

extern int D_L00_001AFBA8 __attribute__((sda));

extern char D_L00_001AFBB0[];

extern void func_115DA8();

extern void func_2E95C0();

/* Draws the two players' scores on screen. */
void func_L00_003B7908(void *object)
{
    float buf[16];
    int *p = (int *)(*(char **)((char *)object + 0x68) + 0x58);
    int *q = &D_L00_001AFB98;
    int i;
    int *r = &D_L00_001AFBA8;

    for (i = 1; i >= 0; i--) {
        func_115DA8(buf, D_L00_001AFBB0, *p);
        p++;
        func_2E95C0(q[0], q[1], r[0], buf, -1);
        q += 2;
        r++;
    }
}

extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C3150(void *, void *, int, int, float, int, int);
extern int D_L00_001AFB68 __attribute__((sda));
extern float D_L00_001AFAE8 __attribute__((sda));
extern float D_L00_001AFAEC;
extern int D_L00_001AFB0C[] __attribute__((sda));
extern float D_L00_001AFAFC;
extern int D_L00_001AFB70[2] __attribute__((sda));

/* Throws out a burst of small coloured particles from a position, like an explosion. */
void func_L00_003B7680(char *object, float *position)
{
    float point[4], velocity[4];
    int i;
    for (i = 0; i < D_L00_001AFB68; i++) {
        unsigned char kind, random;
        int *color;
        RandomDirectionVector(point, 0.0f, 0.333f);
        FastVecAdd(point, point, position);
        RandomDirectionVector(velocity, D_L00_001AFAE8 * (1.0f / 60.0f), D_L00_001AFAEC * (1.0f / 60.0f));
        kind = RandomIntRange(D_L00_001AFB0C[1], D_L00_001AFB0C[2]);
        color = &D_L00_001AFB70[(unsigned char)object[0xbc]];
        random = RandomIntBelow(255);
        SpawnHeroRelativeParticle(point, velocity, *color, kind, D_L00_001AFAFC, random, 0);
    }
}

typedef int Quad __attribute__((mode(TI)));
extern int func_001163B0(void);
extern void func_001163A0(int);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float);
extern void func_00283098(void *, void *, void *);
extern int D_L00_001AFB78 __attribute__((sda));
extern int D_L00_001AFB80[2];
extern float D_L00_001AFB88 __attribute__((sda));
extern float D_L00_001AFB8C;
extern float D_L00_001AFB90[2];
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20[] MACRO_ADDR;

/* Spawns a few random particles in front of the camera each frame for the minigame background. */
void func_L00_003B77A8(char *object)
{
    union { Quad q; float f[4]; } vectors[2];
    char *state = *(char **)(object + 0x68);
    int saved = Rand();
    int i = 0;
    Srand(*(int *)(state + 0x68));
    while (i < D_L00_001AFB78) {
        float speed, blend;
        int color;
        unsigned char random;
        vectors[1].q = 0;
        vectors[1].f[0] = 20.0f;
        i++;
        vectors[1].f[1] = RandomSignedFloatRange(0.0f, D_L00_001AFB88);
        vectors[1].f[2] = RandomSignedFloatRange(0.0f, D_L00_001AFB8C);
        vectors[0].q = vectors[1].q;
        matrix_mul_vec3(&vectors[0], &vectors[0], gCameraPosition_L00 + 0x230);
        FastVecAdd(&vectors[0], &vectors[0], gCameraPosition_L00);
        speed = RandomFloatRange(D_L00_001AFB90[0], D_L00_001AFB90[1]);
        blend = RandomFloatRange(0.0f, 1.0f);
        color = FastTweenColor(D_L00_001AFB80[0], D_L00_001AFB80[1], blend);
        random = RandomIntBelow(255);
        SpawnHeroRelativeParticle(&vectors[0], D_L00_001A8F20, color, 2, speed, random, 0);
    }
    Srand(saved);
}
