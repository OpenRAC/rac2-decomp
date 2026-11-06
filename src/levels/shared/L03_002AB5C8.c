#include "include_asm.h"
#include "common.h"

typedef union { int quad __attribute__((mode(TI))); struct { float x, y, z, w; } f; } HopVector;
/* Player (Ratchet) state block in the level's data, reached through D_L03_00189E20. */
typedef struct {
    HopVector field_0;
    unsigned char pad_10[0x10];
    HopVector field_20;
    unsigned char pad_30[0x68];
    float rot_z;
    unsigned char pad_9C[0x54];
    float vel_x;
    float vel_y;
    unsigned char pad_F8[0x68];
    HopVector field_160;
    unsigned char pad_170[0x4];
    float field_174;
    unsigned char pad_178[0x18];
    HopVector field_190;
    float facing_angle;
    float field_1A4;
    float field_1A8;
    unsigned char pad_1AC[0x4];
    float field_1B0;
    float field_1B4;
    int state_time;
    unsigned char pad_1BC[0x18c];
    short field_348;
    short field_34A;
    unsigned char pad_34C[0x108];
    float field_454;
    unsigned char pad_458[0x18];
    HopVector field_470;
    HopVector field_480;
    unsigned char pad_490[0x4];
    float field_494;
    unsigned char pad_498[0x6];
    unsigned char field_49E;
    unsigned char pad_49F[0xf];
    short field_4AE;
    unsigned char pad_4B0[0xc];
    float field_4BC;
    float field_4C0;
    float field_4C4;
    unsigned char pad_4C8[0xc];
    int field_4D4;
    float field_4D8;
    float field_4DC;
    unsigned char pad_4E0[0x10];
    HopVector field_4F0;
    unsigned char pad_500[0x20];
    float field_520;
    short field_524;
    unsigned char pad_526[0x7];
    unsigned char field_52D;
    unsigned char pad_52E[0x532];
    HopVector field_A60;
    unsigned char pad_A70[0x14];
    float field_A84;
    unsigned char pad_A88[0x1b0];
    float anim_time;
    unsigned char pad_C3C[0x804];
    HopVector field_1440;
    unsigned char pad_1450[0x4];
    short field_1454;
    unsigned char pad_1456[0x2];
    float field_1458;
    unsigned char pad_145C[0xe38];
    int state;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x23];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x1f4];
    float field_24B8;
} HopPlayer;
#define HOP_PLAYER (*(HopPlayer *)D_L03_00189E20)
extern int D_L03_001A8FF0[] __attribute__((sda));
extern float D_L03_001A7DC0[] __attribute__((sda));
typedef struct {
    unsigned char pad_0[0x158];
    float angle;
    unsigned char pad_15C[0x214];
    HopVector basis;
} HopSavedState;
extern unsigned char D_L03_001B9840[];
#define HOP_SAVED (*(HopSavedState *)D_L03_001B9840)
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002D3BD8(float, void *, void *);
extern void func_L00_002D3798(void *, void *, float);
extern void func_L00_002B3EF8(float, float, float, int);
extern void func_L01_002B6948(float);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L00_002D3B58(float, void *, void *);
extern float func_00283C80(float, float);
extern float func_002AA898(float *, float *, int, float, float, float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002AA0F0(float, float, float);
extern float func_L00_002D3A58(void *);

/* Object (moby) header: its state pointer and class id. */
typedef struct {
    unsigned char pad_0[0x68];
    unsigned char *state;
    unsigned char pad_6C[0x3e];
    short type;
} Moby;

/* Particle record returned by func_002BDCE8; its payload follows at 0x20. */
typedef struct {
    unsigned char pad_0[4];
    int mode;
    unsigned char pad_8[2];
    unsigned char alpha;
    unsigned char alpha_copy;
} ParticlePayload;

typedef struct {
    unsigned char pad_0[8];
    unsigned char variation;
    unsigned char pad_9;
    union {
        short duration;
        unsigned char duration_lo;
    } life;
    unsigned char pad_C[0x14];
    ParticlePayload payload;
} Particle;

/* Particle emitter inputs; the two register banks retain their EE argument order. */
extern float D_L03_001A8F20[] __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern void func_0029FC20(void *, int, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern Particle *func_002BDCE8(void *, float, float, float, int, void *, float, unsigned int, int);


#define MACRO_ADDR __attribute__((section(".sdata")))

typedef int TI128 __attribute__((mode(TI)));

extern int func_2B3760(int);

extern unsigned char D_L03_00189E20[];

extern int r1_D_L02_0015F04C MACRO_ADDR;

extern int r1_D_L02_00169670[];

extern int func_2EEC20(void *);

extern void func_331270(void *);

extern TI128 D_001A8F20;

extern void func_2EEFB0(void *, void *, void *);

extern void func_2EF020(void *, float);

extern void func_2ECA50(unsigned char *, int, int, int);

extern int D_001AEF60 __attribute__((sda));

extern float func_2EF158(void *, void *);

extern void func_2B8300(int, int, void *);

extern int func_419B10(void *, void *, int, void *, void *, void *, float, float);

extern void func_32D0F0(void *, int, float);

extern float func_2EF670(float, float);



/* func_L03_002ADC00 is in its dedicated zero-vector profile unit. */

void func_L03_002ADCA0(void) {
    unsigned char *g = D_L03_00189E20;

    if (*(short *)(g + 0x6BC) != 0 && *(int *)(g + 0x660) == 0)
        *(float *)(*(unsigned char **)(g + 0x2290) + 0xF4) = *(float *)(g + 0x6B0);
}


extern float func_002AA2E8(float *, float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);
extern float func_00282E80(void *, void *);

void func_L03_002B8D10(void) {
    switch (D_L03_00189E20[0x22B4]) {
    case 0:
        *(float *)(D_L03_00189E20 + 0x258) = 0.8f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.7f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.449999988079071f;
        break;
    case 1:
        *(float *)(D_L03_00189E20 + 0x258) = 0.599999964237213f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.450000017881394f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.3f;
        break;
    }
    {
        unsigned char *g = D_L03_00189E20;
        if (*(int *)(g + 0x229C) == 4) {
            if (*(short *)(g + 0x4AC) < *(int *)(g + 0x1B8) && !g[0x49E])
                *(float *)(g + 0x25C) = *(float *)(g + 0x4B8);
        } else if (*(int *)(g + 0x2294) == 6) {
            *(float *)(g + 0x25C) = 0.5f;
        } else if (*(int *)(g + 0x2294) == 4) {
            *(float *)(g + 0x258) = 0.350000023841858f;
        } else if (*(int *)(g + 0x2294) == 0x7C) {
            *(float *)(g + 0x260) = 0.8f;
        }
    }
    if (!D_L03_00189E20[0x287] || *(int *)(D_L03_00189E20 + 0x22A4) == 0x12 ||
        *(int *)(D_L03_00189E20 + 0x22B0) == 0x12 ||
        (!D_L03_00189E20[0x22B4] && *(float *)(D_L03_00189E20 + 0x254) < 0.53f) ||
        *(int *)(D_L03_00189E20 + 0x229C) == 0x11 || D_L03_00189E20[0x1494] ||
        func_00282E80(D_L03_00189E20 + 0x240, D_L03_00189E20 + 0x80) > *(float *)(D_L03_00189E20 + 0x264) * 0.5f) {
        float *p = (float *)(D_L03_00189E20 + 0x250);
        unsigned char *g = D_L03_00189E20;
        func_002AA2E8(p, *(float *)(g + 0x258), 0.02f);
        func_002AA2E8(p + 1, *(float *)(g + 0x25C), 0.02f);
        func_002AA3A8(p + 5, p + 6, *(float *)(g + 0x260), 0.02f, 0.3f, 0.06666667f);
    }
}

/* Per-state airborne steering of the player: velocity, facing and speed targets. */
void func_L03_002BC430(void) {
    HopVector temp;
    float step, scale;

    if (HOP_PLAYER.state == 10) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x10) {
        if (HOP_PLAYER.state_time > 0x36)
            func_002AA2E8(&HOP_PLAYER.field_520, 0.0069444444961845875f, 0.0019444444915279746f);
        if (HOP_PLAYER.state_time <= 0x36)
            HOP_PLAYER.field_1B0 = HOP_PLAYER.field_454;
        else
            HOP_PLAYER.field_1B0 = 0.05833333730697632f;
        func_L00_002B41B8(0.012222222983837128f, 0.0125f);
        func_L00_002D3BD8(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
        func_L00_002D3798(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, HOP_PLAYER.field_1B4);
        return;
    }

    if (HOP_PLAYER.state == 0x1B) {
        if (HOP_PLAYER.state_time > 0x28) {
            func_L00_002B3EF8(0.04f, 0.2f, 0.2501639127731323f, 0);
            func_L01_002B6948(0.0055555556900799274f);
        }
        if (HOP_PLAYER.anim_time >= 13.0f && HOP_PLAYER.anim_time <= 30.0f) {
            if (HOP_PLAYER.anim_time > 27.0f)
                func_002AA2E8(&HOP_PLAYER.field_4BC, 0.0f, 0.002222222276031971f);
            else
                func_002AA2E8(&HOP_PLAYER.field_4BC, 0.03333333507180214f, 0.002222222276031971f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = func_00282DB0(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        func_00283098(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0x48) {
        if (HOP_PLAYER.anim_time >= 5.0f && HOP_PLAYER.anim_time <= 18.0f) {
            if (HOP_PLAYER.anim_time > 15.0f)
                func_002AA2E8(&HOP_PLAYER.field_4BC, 0.0f, 0.002222222276031971f);
            else
                func_002AA2E8(&HOP_PLAYER.field_4BC, 0.02083333395421505f, 0.002222222276031971f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = func_00282DB0(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        func_00283098(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0xB) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4C4;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_480);
        func_L00_002B3EF8(0.04f, 0.2f, 0.116355299949646f, 0);
        if (HOP_PLAYER.field_4D4 != 3)
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_4D8;
        else
            HOP_PLAYER.field_1B4 = 0.0f;
        if (HOP_PLAYER.field_52D) {
            step = HOP_PLAYER.field_24B8 * 0.0833333358168602f;
            if (step < 0.03333333507180214f)
                step = 0.03333333507180214f;
            func_002AA2E8(&HOP_PLAYER.field_4DC, step, 0.010277777910232544f);
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        } else {
            if (HOP_PLAYER.field_49E && HOP_PLAYER.field_4AE <= 11)
                func_002AA2E8(&HOP_PLAYER.field_4DC, 0.0f, 0.002222222276031971f);
            else
                func_002AA2E8(&HOP_PLAYER.field_4DC, 0.07f, 0.002222222276031971f);
        }
        if (!HOP_PLAYER.field_22C3) {
            HOP_PLAYER.vel_x = func_00283180(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_x *= HOP_PLAYER.field_4DC;
            HOP_PLAYER.vel_y = func_00283198(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_y *= HOP_PLAYER.field_4DC;
        } else {
            func_L00_002D3BD8(HOP_PLAYER.field_4DC, &temp, &HOP_PLAYER.field_470);
            func_L00_002D3B58(0.0f, &temp, &temp);
            func_L00_002D3BD8(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            func_00282CC0(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
        }
        if (!HOP_PLAYER.field_22C3 && !HOP_PLAYER.field_52D) {
            scale = HOP_PLAYER.field_4D8 * func_00283198(func_00283C80(HOP_PLAYER.field_4C4, HOP_PLAYER.field_4C0));
            HOP_PLAYER.vel_x += func_00283180(HOP_PLAYER.field_4C4) * scale;
            HOP_PLAYER.vel_y += func_00283198(HOP_PLAYER.field_4C4) * scale;
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        return;
    }

    if (HOP_PLAYER.state == 0x11) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4F0.f.w;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_4F0);
        if (HOP_PLAYER.state_time > 9)
            func_L00_002B3EF8(0.041999999433755875f, 0.2f, 0.1978040188550949f, -1);
        if (HOP_PLAYER.state_time > 8) {
            if (!HOP_PLAYER.field_348) {
                HOP_PLAYER.vel_x = func_00283180(HOP_PLAYER.facing_angle) * 0.08166667073965073f;
                HOP_PLAYER.vel_y = func_00283198(HOP_PLAYER.facing_angle) * 0.08166667073965073f;
            } else {
                func_L00_002D3BD8(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
                func_00282F20(&temp, &HOP_PLAYER.field_190, 0.08166667073965073f);
                func_00282CC0(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
            }
        }
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x81 && !D_L03_001A8FF0[0]) {
        func_L00_002B3EF8(0.04f, 0.2f, HOP_PLAYER.field_494, 0);
        HOP_PLAYER.field_1B4 = 0.0f;
        return;
    }

    if (HOP_PLAYER.state == 0x2C) {
        float angle = HOP_PLAYER.rot_z;
        float delta;

        HOP_PLAYER.field_1A8 = func_002AA898(&angle, &HOP_PLAYER.field_1A4, 0, HOP_PLAYER.facing_angle,
                                             0.017999999225139618f, 0.2f, 0.12217307090759277f);
        delta = func_00283BE0(angle, HOP_PLAYER.rot_z);
        func_L00_002AA0F0(0.0f, 0.0f, delta);
    } else {
        float oldAngle = HOP_PLAYER.facing_angle;

        qcopy(&temp, &HOP_PLAYER.field_190);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.facing_angle = HOP_SAVED.angle;
            qcopy(&HOP_PLAYER.field_190, &HOP_SAVED.basis);
        }
        func_L00_002B3EF8(0.04f, 0.2f, HOP_PLAYER.field_494, 0);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.field_1458 = oldAngle;
            qcopy(&HOP_PLAYER.field_1440, &temp);
            HOP_PLAYER.facing_angle = oldAngle;
            qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_1440);
        }
    }

    func_L00_002B54F8(0.7f, 0.0f);
    qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);

    step = 0.0055555556900799274f;
    if (HOP_PLAYER.field_1B0 < D_L03_001A7DC0[0] * 0.0033333336468786f) {
        if (HOP_PLAYER.field_229C == 2) {
            float brake = HOP_PLAYER.field_A84;
            float angle = func_L00_002D3A58(&HOP_PLAYER.vel_x);

            func_002AA2E8(&angle, 0.0f, brake);
            func_L00_002D3BD8(angle, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            return;
        }
        if (HOP_PLAYER.field_34A)
            step = 0.003055555745959282f;
        else
            step = HOP_PLAYER.field_524 ? 0.0005555555690079927f : 0.002222222276031971f;
    }

    func_L01_002B6948(step);
}

#undef HOP_PLAYER
#undef HOP_SAVED

/* rac1-decomp src/overlays/shared/camera_001FC308.c: func_L02_001FC308 */
/* Adapted from Lombyte (MIT) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay/camera/001fc008.c, FUN_L02_001fc008. */
void func_L03_002D84F0(int x) {
    int i;

    if (r1_D_L02_0015F04C < 16) {
        for (i = 0; i < r1_D_L02_0015F04C; i++) {
            if (x == r1_D_L02_00169670[i]) {
                return;
            }
        }
        r1_D_L02_00169670[r1_D_L02_0015F04C++] = x;
    }
}




ASM_FUNC("asm/levels", func_L03_002EFB60);


/* Emits two particle groups scaled by the object's transformed basis length. */
void func_L03_00326458(Moby *object)
{
    float matrix[16], point[4], velocity[4];
    float weight, radius, energy;
    short type = object->type;

    if ((type != 0x2EE && type != 0xCE0) || object == 0)
        return;

    func_0029FC20(object, 0, matrix);
    weight = func_00282DF0(matrix) * 0.9746588468551636f;
    if (weight > 1.0f)
        weight = 1.0f;
    energy = weight * 44000.0f + 6000.0f;
    radius = weight * 0.02f + 0.01f;
    func_00282F20(velocity, matrix + 8, weight * -0.025f + -0.025f);

    /* Larger smoke puffs with random spin. */
    {
        int i;
        short duration;
        int mode;
        unsigned char alpha;

        duration = 6;
        mode = 2;
        alpha = 0x50;
        func_00282CC0(point, matrix + 12, velocity);
        i = 1;
        do {
            Particle *particle;
            int spin;

            spin = func_002A77E0(16);
            if (func_002A77E0(2))
                spin = -spin;
            particle = func_002BDCE8(point, radius, 1.0f, 0.75f, spin, D_L03_001A8F20, energy, 0x503030FF, 0);
            if (particle != 0) {
                ParticlePayload *payload = &particle->payload;

                particle->life.duration = duration;
                payload->mode = mode;
                payload->alpha = alpha;
                payload->alpha_copy = particle->life.duration_lo;
            }
            i--;
        } while (i >= 0);
    }

    energy = weight * 25000.0f + 5000.0f;
    radius = weight * 0.015000000596046448f + 0.01f;
    func_00282F20(velocity, matrix + 8, weight * -0.015000000596046448f + -0.01f);

    /* Smaller, short-lived sparks. */
    {
        short duration;
        int mode;
        unsigned char alpha;

        duration = 2;
        mode = 2;
        alpha = 0x7F;
        func_00282CC0(point, matrix + 12, velocity);
        {
            int j;

            j = 4;
            do {
                Particle *particle;

                particle = func_002BDCE8(point, radius, 1.0f, 1.0f, 16, D_L03_001A8F20, energy, 0x7FFFFFFF, 0);
                if (particle != 0) {
                    ParticlePayload *payload = &particle->payload;

                    particle->life.duration = duration;
                    particle->variation = func_002A77E0(255);
                    payload->mode = mode;
                    payload->alpha = alpha;
                    payload->alpha_copy = particle->life.duration_lo;
                }
                j--;
            } while (j >= 0);
        }
    }
}


/* func_L03_00329EF0 is defined in L03_002AB5C8-region.c. */


/* func_L03_00339128 is defined in L03_00339128-qcopy.c. */

void func_L03_00339268(unsigned char *a0) {
    if (*(short *)(a0 + 0xA) == -1)
        return;
    if (func_2EEC20(a0 + 0xA) == 0)
        return;
    func_331270(a0);
}


/* func_L03_0038AB30 is defined in L03_002AB5C8-ribbon.c (its own loop-pass flags). */

/* func_L03_0038B238 is defined in L03_002AB5C8-g8.c (this unit has no $gp access for it). */


void func_L03_0038B390(unsigned char *a0, int a1, int a2, int a3) {
    unsigned char *p = a0;
    int v = a3;

    func_2ECA50(a0, a1, a2, 0x80);
    *(int *)(p + 0x4C) = v;
    *(int *)(p + 0x48) = v;
    *(int *)(p + 0x44) = v;
    *(int *)(p + 0x40) = v;
    *(int *)(p + 0x50) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x58) = 0;
    *(float *)(p + 0x5C) = 1.0f;
    *(float *)(p + 0x60) = 1.0f;
    *(int *)(p + 0x64) = 0;
    *(float *)(p + 0x68) = 1.0f;
    *(float *)(p + 0x6C) = 1.0f;
    *(long long *)(p + 0x70) = 5;
}

extern void func_L03_0038B2E8(void *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float (*D_L03_001FE700[])[4];

/* Effect state hung off an object: four vertex-table indices, a vertex count and an offset. */
typedef struct {
    unsigned char pad_0[0x28];
    int groups[4];
    int count;
    unsigned char pad_3C[0xA4];
    float offset[4];
} VertexGroupState;

/* Adjusts each vertex of the object's groups relative to a computed centre, then offsets it by the state vector. */
void func_L03_0038B408(Moby *object)
{
    float center[4];
    VertexGroupState *state = (VertexGroupState *)object->state;
    float (**table)[4] = D_L03_001FE700;
    float (*vertices)[4];
    int i, j;

    for (i = 0; i < 4; i++) {
        vertices = table[state->groups[i]];
        if (vertices != 0) {
            func_L03_0038B2E8(center, vertices, state->count);
            for (j = 0; j < state->count; j++) {
                func_00282CF0(vertices + j + 1, vertices + j + 1, center);
                func_00282CC0(vertices + j + 1, vertices + j + 1, state->offset);
            }
        }
    }
}




void func_L03_00393228(unsigned char *a0) {
    unsigned char *g = D_L03_00189E20;

    if (*(unsigned char *)(g + 0x22B4) == 0)
        if (func_2EF158(g + 0x80, a0 + 0x10) < 1.7f)
            func_2B8300(1, 0x3F, a0);
}


int func_L03_003A4978(unsigned char *p) { return p[0x20] == 1; }



float func_L03_003C5AB8(unsigned char *);

int func_L03_003C41B8(unsigned char *a0, int a1, int a2) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float f = 0.0f;
    float out;
    int r;

    if (a2 != 0)
        f = func_L03_003C5AB8(a0);
    r = func_419B10(*(void **)(s0 + 0x220), a0 + 0x10, a1, &out, s0 + 0x368, s0 + 0x36C, f,
                    *(float *)(s0 + 0x110));
    func_32D0F0(a0, a1, out);
    return r;
}

/* func_L03_003C4240 is defined in L03_002AB5C8-g8.c (it reads two $gp constants). */

/* func_L03_003C4368 is defined in L03_003C4368-g8.c. */

/* func_L03_003C4468 is defined in L03_003C4468-flags.c. */

/* func_L03_003C4578 is defined in L03_002AB5C8-g8.c (it reads $gp data). */


/* func_L03_003C4A10 is defined in L03_002AB5C8-g8.c (it reads $gp data). */

extern int func_00282948(void *);

extern float func_002A78D8(float, float);

extern float func_002A7878(float, float);

extern int func_002A7820(int, int);

extern int func_002A77E0(int);

/* The level's own copy of the object's tilt routine (func_L03_003C4A10), at another address
   in every level that has it. */
extern void ref_L03_003C4BD8_00(unsigned char *, void *);

/* The position the tilt is measured from: a four-float vector in the boot's resident data. */
extern char D_L00_00189F00[];

void func_L03_003C4BD8(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float u;
    float v;
    int flag;

    if (func_00282948(s0 + 0x384) != 0) {
        if (a0[0x95] == 2) {
            *(float *)(s0 + 0x388) = func_002A78D8(5.0f, 60.0f) * 0.017453294f;
            *(float *)(s0 + 0x38C) = func_002A7878(-20.0f, 0.0f) * 0.017453294f;
            *(int *)(s0 + 0x384) = func_002A7820(30, 45);
            *(int *)(s0 + 0x390) = 0;
        } else {
            *(float *)(s0 + 0x388) = func_002A78D8(5.0f, 20.0f) * 0.017453294f;
            *(float *)(s0 + 0x38C) = func_002A7878(-15.0f, 5.0f) * 0.017453294f;
            flag = (func_002A77E0(4) == 0);
            *(int *)(s0 + 0x390) = flag;
            if (flag) {
                *(int *)(s0 + 0x384) = func_002A7820(180, 300);
            } else {
                *(int *)(s0 + 0x384) = func_002A7820(60, 120);
            }
        }
    }

    if (*(int *)(s0 + 0x390) != 0) {
        ref_L03_003C4BD8_00(a0, D_L00_00189F00);
    } else {
        u = *(float *)(s0 + 0x38C);
        v = *(float *)(s0 + 0x388);
        /* This cc1 emits the two pairs of stores in the opposite order to the source, so the
           pair at 0x324 comes first here to land them at 0x2A4 as the retail has them. */
        *(float *)(s0 + 0x324) = u;
        *(float *)(s0 + 0x328) = v;
        *(float *)(s0 + 0x2A4) = u;
        *(float *)(s0 + 0x2A8) = v;
    }
}

/* The level's entity table base, the group count and the table of group id lists (in the
   resident image: the list of group g ends after its first entry with bit 15 set). */
extern unsigned char *D_L03_001B2A1C __attribute__((sda));

extern int D_L03_001B2A38[] __attribute__((sda));

extern unsigned short *D_L03_001FB5A0[];

/* The part of the object's private state (at +0x68) that these walks read: eight group ids at
   +0x200 and the id of an entity at +0x220. */
typedef struct {
    unsigned char pad0[0x200];
    int ids[8];
    unsigned int ref220;
} L03GroupState;

extern unsigned int func_L03_004197A8(unsigned char *);

extern int func_L03_00419BD8(unsigned int, void *, void *);

extern float func_00282E80(void *, void *);

extern float func_00282C48(float);

/* Returns the entity nearest to the object, within 15.0, among its eight groups, that has bit 12
   of its flags at 0x34 set, a value of 5 at 0x46 of the record at 0x24, a height (at 0x18)
   within 1.5 of the object's and that func_L03_00419BD8 accepts, or 0. */
unsigned char *func_L03_003C4D40(unsigned char *a0) {
    L03GroupState *o = *(L03GroupState **)(a0 + 0x68);
    unsigned short *q;
    unsigned char *e;
    unsigned char *best = 0;
    float bestd = 15.0f;
    float d;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = D_L03_001FB5A0[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == D_L03_001FB5A0[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            if (*(unsigned short *)(e + 0x34) & 0x1000) {
                if (*(short *)(*(unsigned char **)(e + 0x24) + 0x46) == 5) {
                    if (func_00282C48(*(float *)(a0 + 0x18) - *(float *)(e + 0x18)) < 1.5f) {
                        if (func_L03_00419BD8(o->ref220, a0 + 0x10, e + 0x10)) {
                            d = func_00282E80(a0 + 0x10, e + 0x10);
                            if (d < bestd) {
                                bestd = d;
                                best = e;
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
}

/* Returns the entity of class 0xEF9 nearest to the object, within 15.0, among its eight groups
   (func_L03_004197A8 and func_L03_00419BD8 must both accept it), or 0. */
unsigned char *func_L03_003C4F58(unsigned char *a0) {
    L03GroupState *o = *(L03GroupState **)(a0 + 0x68);
    unsigned short *q;
    unsigned char *e;
    unsigned char *best = 0;
    float bestd = 15.0f;
    float d;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = D_L03_001FB5A0[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == D_L03_001FB5A0[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xEF9) {
                if (func_L03_004197A8(e)) {
                    if (func_L03_00419BD8(o->ref220, a0 + 0x10, e + 0x10)) {
                        d = func_00282E80(a0 + 0x10, e + 0x10);
                        if (d < bestd) {
                            bestd = d;
                            best = e;
                        }
                    }
                }
            }
        }
    }
    return best;
}

extern unsigned int func_L03_003CAAC8(unsigned char *, unsigned char *);

/* Returns the first entity of class 0x97A, in the object's eight groups, that
   func_L03_003CAAC8 finds near the object or near the player, or 0. The group table is reached
   through a local pointer: with its address computed once outside the loops, the walk's other
   constants (0x97A, 0xFF, the player's address) all fit loop.c's budget for moving invariants
   out of the walk, as in retail. */
unsigned char *func_L03_003C5128(unsigned char *a0) {
    L03GroupState *o = *(L03GroupState **)(a0 + 0x68);
    unsigned short **tbl = D_L03_001FB5A0;
    unsigned short *q;
    unsigned char *e;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = tbl[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == tbl[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0x97A) {
                if (func_L03_003CAAC8(e, a0 + 0x10))
                    return e;
                if (func_L03_003CAAC8(e, D_L03_00189E20 + 0x80))
                    return e;
            }
        }
    }
    return 0;
}

extern int func_L03_003CA138(unsigned char *);

/* Returns the entity of class 0xE87 or 0xE88 in state 1 nearest to the object, within 14.0,
   among its eight groups, or 0. */
unsigned char *func_L03_003C52D0(unsigned char *a0) {
    L03GroupState *o = *(L03GroupState **)(a0 + 0x68);
    unsigned short *q;
    unsigned char *e;
    unsigned char *best = 0;
    float bestd = 14.0f;
    float d;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = D_L03_001FB5A0[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == D_L03_001FB5A0[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(unsigned short *)(e + 0xAA) == 0xE87 || *(unsigned short *)(e + 0xAA) == 0xE88) {
                if (func_L03_003CA138(e)) {
                    d = func_00282E80(a0 + 0x10, e + 0x10);
                    if (d < bestd) {
                        bestd = d;
                        best = e;
                    }
                }
            }
        }
    }
    return best;
}

extern int func_L03_003CA280(unsigned char *);

/* Returns the entity of class 0xB10, or of class 0xF4D that func_L03_003CA280 accepts (state 1),
   nearest to the object, within 10.0, among its eight groups (entities in state 0xFE or 0xFD are
   skipped), or 0. The group table goes through a local pointer, as in func_L03_003C5128: that is
   what leaves 0xFE out of loop.c's budget for hoisting the walk's constants, as in retail. */
unsigned char *func_L03_003C5488(unsigned char *a0) {
    L03GroupState *o = *(L03GroupState **)(a0 + 0x68);
    unsigned short **tbl = D_L03_001FB5A0;
    unsigned short *q;
    unsigned char *e;
    unsigned char *best = 0;
    float bestd = 10.0f;
    float d;
    int c;
    int i;

    for (i = 0; i < 8; i++) {
        for (q = tbl[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == tbl[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            c = *(short *)(e + 0xAA);
            if (c == 0xB10 || c == 0xF4D) {
                if (c == 0xF4D && func_L03_003CA280(e) == 0)
                    continue;
                d = func_00282E80(a0 + 0x10, e + 0x10);
                if (d < bestd) {
                    bestd = d;
                    best = e;
                }
            }
        }
    }
    return best;
}

INCLUDE_ASM("asm/levels", func_L03_003C5668);

/* func_L03_003C58F0 is defined in L03_002AB5C8-g8.c (it reads the group count through $gp). */

float func_L03_003C5AB8(unsigned char *a0) {
    unsigned char *p = *(unsigned char **)(a0 + 0x68);
    float x = func_2EF670(*(float *)(p + 0x1DC), 1.5f);
    float s;

    if (x > 1.4959966f)
        x = 1.4959966f;
    x = x * 0.2f;
    s = (float)*(int *)(p + 0x360);
    return x * s;
}
