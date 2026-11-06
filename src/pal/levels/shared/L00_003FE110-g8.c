/* func_PAL_L00_003FE110, the PAL copy of func_L00_003F9A30: the same C, with its timers and
 * per-frame rates scaled to 50 Hz and each spark id local to its own loop. */
#include "common.h"

extern void func_00300190(void *, void *);
extern void func_PAL_L00_004007B0(void);
extern float func_00283B98(float, float);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_0027D098(void *, void *);
extern void func_PAL_L00_003FF050(void);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_003001E0(void *, void *, void *);
extern void *func_002C6DD8(void *, void *, int, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void *func_L00_0033E888(void *, void *, unsigned, unsigned, float, int, int, int, int, int, float);
extern char *func_002BDCE8(float, float, void *, int, void *, unsigned, int, float, float);
extern char D_L00_001A8F20[] __attribute__((sda));
extern float D_L00_001B0AA0 __attribute__((sda));
extern float D_L00_001B0AB4 __attribute__((sda));
extern float D_L00_001B0AAC __attribute__((sda));
extern float D_L00_001B0AB0 __attribute__((sda));
extern int D_L00_001B0AB8 __attribute__((sda));
extern int D_L00_001B0B64 __attribute__((sda));
extern int D_L00_001B0AF0 __attribute__((sda));
extern int D_L00_001B0AF4 __attribute__((sda));
extern float D_L00_001B0B04 __attribute__((sda));
extern float D_L00_001B0B08 __attribute__((sda));
extern float D_L00_001B0AD8 __attribute__((sda));
extern float D_L00_001B0B58 __attribute__((sda));
extern float D_L00_001B0B5C __attribute__((sda));

typedef int EffectQuad __attribute__((mode(TI)));

/* Private state of the emitter, as far as this function uses it. */
typedef struct EffectState {
    float angles[6];
    float height;
    short timer1, timer2;
    u8 pad20[4];
    float scale;
    u8 pad28[0x34 - 0x28];
    short timer3;
    u8 pad36[0x40 - 0x36];
    int f40;
} EffectState;

/* The emitter moby, as far as this function uses it. */
typedef struct Emitter {
    u8 pad00[0x10];
    float pos[4];
    u8 pad20[0x68 - 0x20];
    EffectState *state;
    u8 pad6C[0xC0 - 0x6C];
    float dirC0[4];
    float dirD0[4];
} Emitter;

/* Advance the emitter's angles and timers, emit its initial burst, then spread
 * spinning sparks along a height-dependent segment above the stored ground height.
 */
void func_PAL_L00_003FE110(Emitter *self)
{
    EffectState *state = self->state;
    float a[4], b[4], c[4], d[4], e[4], f[4];
    float x, y, radius, height, ratio;
    char *spark;
    int i, count, remaining;

    func_00300190(self->pos, self->pos);
    func_PAL_L00_004007B0();
    state->angles[0] = func_00283B98(state->angles[0], D_L00_001B0AA0 * 0.01745329424738884f);
    state->angles[1] = func_00283B98(state->angles[1], D_L00_001B0AB4 * 0.01745329424738884f);
    state->angles[2] = func_00283B98(state->angles[2], 0.00436332356184721f);
    state->angles[3] = func_00283B98(state->angles[3], -0.00436332356184721f);
    state->angles[4] = func_00283B98(state->angles[4], D_L00_001B0AAC * 0.01745329424738884f);
    state->angles[5] = func_00283B98(state->angles[5], D_L00_001B0AB0 * 0.01745329424738884f);
    func_00282978(&state->timer2);
    func_00282978(&state->timer3);
    func_00282948(&state->f40);
    if (func_00282978(&state->timer1) && state->timer2 == 0) {
        if (!D_L00_001B0B64)
            func_0029F338(self);
        return;
    }

    func_0027D098((void *)func_PAL_L00_003FF050, self);

    if (state->timer2 >= ((D_L00_001B0AB8 - 6) * 5 + 2) / 6) {
        for (i = 0; i < 20; i++) {
            float angle1, angle2;
            int id;

            func_00282D30(a, self->dirC0, func_002A7878(D_L00_001B0B04, D_L00_001B0B08) * 0.020000001f);
            angle1 = func_002A78D8(0.2617994248867035f, 1.396263599395752f);
            angle2 = func_002A78D8(0.2617994248867035f, 1.396263599395752f);
            func_002AB668(c, self->dirD0, angle1);
            func_002ACDE8(b, a, c);
            func_002AB668(c, self->dirC0, angle2);
            func_002ACDE8(b, b, c);
            id = (func_002A7820(D_L00_001B0AF0, D_L00_001B0AF4) * 5 + 2) / 6;
            func_003001E0(b, b, self->pos);
            func_002C6DD8(self->pos, b, id, D_L00_001B0AD8 * 0.00040000002f);
        }
    }

    if ((unsigned)((unsigned short)state->timer2 - 11) < 22) {
        float z, x, speed;

        z = func_002A7878(-0.9599311947822571f, -1.396263599395752f);
        x = func_002A7940();
        func_002AF000(a, func_002A7878(0.0f, 0.5f) * 0.020000001f, x, z);
        speed = func_002A7878(0.25f, 0.75f) * 210000.0f;
        func_00282D30(b, self->dirC0, -0.45f);
        func_00282CC0(b, self->pos, b);
        c[0] = b[0] + func_002A78D8(0.0f, 0.25f);
        c[1] = b[1] + func_002A78D8(0.0f, 0.25f);
        c[2] = b[2] + func_002A78D8(0.0f, 0.25f);
        func_003001E0(a, a, c);
        func_L00_0033E888(c, a, 0x4F93E5FF, 0x102434EE, speed, func_002A7820(25, 37), 1, -1, -1, 0, 0.5f);
    }

    x = func_00283CE0(state->timer2);
    radius = (D_L00_001B0B5C + (D_L00_001B0B58 - D_L00_001B0B5C) * (x * state->scale)) * 1.5f;
    height = state->height;
    y = self->pos[2] - height;
    if (y > 0.0f && y < radius && state->timer2 >= 22) {
        float factor;

        ratio = y / radius;
        factor = ratio * -0.65f + 0.75f;
        count = func_00283CF0((1.0f - ratio) * 30.0f);
        if (count <= 0)
            count = 1;

        *(EffectQuad *)a = 0;
        a[2] = 1.0f;
        a[3] = 1.0f;
        func_00282DD8(b, a, self->dirC0);
        func_00282F20(b, b, radius * factor);
        qcopy(c, self->pos);
        c[2] = height + 0.25f;
        func_00282CC0(d, c, b);
        func_00282CF0(e, c, b);
        func_00282CF0(f, e, d);
        func_00282D30(f, f, 1.0f / (float)count);

        for (remaining = 0; remaining < count; remaining++) {
            float speed;
            int id;

            id = func_002A77E0(16);
            if (func_002A77E0(2))
                id = -id;
            speed = func_002A7878(0.2f, 1.5f) * 210000.0f;
            spark = func_002BDCE8(0.3f, 1.0f, d, id, D_L00_001A8F20, 0x7F204080, 1, 0.9f, speed);
            func_00282CC0(d, d, f);
            if (spark) {
                char *ext = spark + 0x20;

                *(short *)(spark + 0xA) = (func_002A7820(8, 25) * 5 + 2) / 6;
                spark[9] = func_00283CF0(4.0f) + 64;
                *(int *)(ext + 4) = 2;
                ext[0xA] = func_002A7820(80, 127);
                ext[0xB] = *(unsigned char *)(spark + 0xA);
            }
        }
    }
}
