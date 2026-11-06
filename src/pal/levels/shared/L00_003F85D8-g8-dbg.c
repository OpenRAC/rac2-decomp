/* func_PAL_L00_003F85D8, the PAL copy of func_L00_003F4210: the same C at 50 Hz, with the trail
   lifetime scaled, per-frame speeds 0.02 instead of 1/60, and a slowdown scaled by 1.2.
   Updates a bouncing explosive projectile: flight with a particle trail, bounces that lose speed,
   a fading slide after the fourth bounce, then an explosion that damages everything in range.
   Needs -g (pre-div.s nop pairs) and hazard labels (two branch targets). The length is stored
   to the member before it is scaled: that store is deleted after allocation, but until then it
   keeps the call result alive past the multiplication, which ties the product to the scale. */
#include "common.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct {
    Vector impulse;
    int owner, flags;
    unsigned char enabled, kind;
    unsigned short object_class;
    float damage;
    int active;
} DamageRequest;

typedef struct { float r, g, b; } Color;
typedef struct {
    unsigned char pad[0x10];
    Vector velocity;
    int timer;
    char *owner;
    short particle_timer, bounces;
    float fade_scale;
} ProjectileState;
/* The hit pointer is outside the GP-relative displacement range. */
extern char *D_L00_001BF218 NOT_SDA;
typedef struct {
    char pad[0x18];
    char *owner;
    int flags;
    Vector position, pad30, normal;
} Collision;
extern Collision D_L00_001BF200;
extern int D_L00_001A8FF0;
extern Vector D_L00_001A8F20 __attribute__((sda)) NOT_SDA;
extern char *D_L00_001C3280[];
extern unsigned char D_00139587 NOT_SDA;
typedef struct {
    unsigned char pad[0x74];
    float damage;
    unsigned char rest[0x68];
} DamageTableRow;
extern DamageTableRow D_L00_00262570[];
extern Color D_L00_001B0920;
extern float D_L00_001B0900 __attribute__((sda));
extern int D_L00_001B0904 __attribute__((sda));
extern float D_L00_001B0908 __attribute__((sda));
extern float D_L00_001B090C __attribute__((sda));
extern float D_L00_001B0918 __attribute__((sda));
extern float D_L00_001B091C __attribute__((sda));
extern int func_00277258(Vector *, int, char *, float);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern void func_00282CC0(Vector *, const Vector *, const Vector *);
extern void func_00282CF0(Vector *, const Vector *, const Vector *);
extern void func_L00_003252A8(void *, void *, int);
extern void func_00282D30(Vector *, const Vector *, float);
extern float func_00282DB0(const Vector *, const Vector *);
extern void func_L00_0031D670(Vector *, const Vector *, const Vector *, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern char *func_PAL_002BE9A8(Vector *, float, float, float, int, const Vector *, float, int, int);
extern int func_002761F8(Vector *, Vector *, int, char *, int);
extern void func_00282F20(Vector *, const Vector *, float);
extern void func_00283028(Vector *, const Vector *, const Vector *);
extern int func_002E5CF8(int, int, char *);
extern void func_00282F70(Vector *, const Vector *, float);
extern float func_00282E20(const Vector *);
extern void func_003001E0(Vector *, const Vector *, const Vector *);
extern int func_00283CF0(float);
extern void func_00300190(void *, void *);
extern int func_002E5DA0(int, int, char *, int);
extern void func_PAL_002AC718(void *, float, void *, float, void *, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_002A8BD0(char *, int, int, float);
extern int func_00277F48(Vector *, int, char *, DamageRequest *, float);
extern int func_PAL_00335DD0(char *, int, int);
extern void func_0029F338(void *);
extern float func_00283B98(float, float);

void func_PAL_L00_003F85D8(char *object)
{
    union {
        DamageRequest request;
        Color color;
        struct { Vector end, normal, scaled; } motion;
    } scratch;
    Vector point, temporary, vertical, tangent;
    ProjectileState *state = *(ProjectileState **)(object + 0x68);
    char *particle;
    char **hit;
    int count, i, spin, crossed;
    int red, green, blue;
    float speed, fade, damage, dot, minimum;

    if (func_00277258((Vector *)(object + 0x10), 0, object, 0.64999998f) != 0 &&
        D_L00_001BF218 != 0 && D_L00_001BF218 != state->owner)
        *(unsigned char *)(object + 0x20) = 3;
    if (func_00282948(&state->timer) != 0)
        *(unsigned char *)(object + 0x20) = 3;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
    case 1:
        func_00282CC0(&scratch.motion.end, (Vector *)(object + 0x10), (&state->velocity));
        func_L00_003252A8(object, &scratch.motion.normal, 0);
        func_00282D30(&scratch.motion.scaled, &scratch.motion.normal, state->velocity.v[3]);
        func_00282CC0((&state->velocity), (&state->velocity), &scratch.motion.scaled);
        if (D_L00_001A8FF0 != 0) {
            if (*(unsigned char *)(object + 0x20) == 1 && func_00282DB0((&state->velocity), &scratch.motion.normal) > 0.0f)
                *(unsigned char *)(object + 0x20) = 0;
        } else if (*(unsigned char *)(object + 0x20) == 1) {
            if (state->velocity.v[2] < 0.0f)
                *(unsigned char *)(object + 0x20) = 0;
        }
        func_00282978(&state->particle_timer);
        if (state->particle_timer != 0) {
            for (i = 0; i < 3; ++i) {
                float one = 1.0f;
                float third = 0.3333f;
                float life;
                QuadWord copy = ((Vector *)(object + 0x10))->word;
                temporary.word = copy;
                func_L00_0031D670(&point, &temporary, &scratch.motion.end, (float)i * third);
                spin = func_002A77E0(6);
                if (func_002A77E0(2) != 0) spin = -spin;
                fade = func_00283CE0(((s32)(D_L00_001B0904) * 5 + 2) / 6);
                life = (float)state->particle_timer / fade * 45000.0f + 5000.0f;
                particle = func_PAL_002BE9A8(&point, 0.025f, one, one, spin, &D_L00_001A8F20,
                                        life, (int)0x80808080, 1);
                if (particle != 0) {
                    char *properties;
                    *(short *)(particle + 0xa) = 100;
                    properties = particle + 0x20;
                    *(int *)(properties + 4) = 2;
                    *(unsigned char *)(properties + 0xa) = 127;
                    *(unsigned char *)(properties + 0xb) = *(unsigned char *)(particle + 0xa);
                }
            }
        }
        if (func_002761F8((Vector *)(object + 0x10), &scratch.motion.end, 0, object, 0) != 0 &&
            (D_L00_001BF200.owner == 0 || D_L00_001BF200.owner != state->owner))
            qcopy((Vector *)(object + 0x10), &D_L00_001BF200.position);
        else
            qcopy((Vector *)(object + 0x10), &scratch.motion.end);
        if (D_L00_001A8FF0 != 0) {
            func_00282CF0(&point, (Vector *)(object + 0x10), &D_L00_001BF200.position);
            crossed = func_00282DB0(&point, &scratch.motion.normal) > 0.0f;
        } else {
            crossed = ((Vector *)(object + 0x10))->v[2] - D_L00_001BF200.position.v[2] < 0.0f;
        }
        if (func_00277258((Vector *)(object + 0x10), 0, object, D_L00_001B0900) == 0) break;
        if (*(unsigned char *)(object + 0x20) != 0 && !crossed) break;
        if (D_L00_001BF200.owner != 0 && D_L00_001BF200.owner == state->owner) break;
        func_00282F20(&point, &D_L00_001BF200.normal, D_L00_001B0900);
        func_00282CC0((Vector *)(object + 0x10), &D_L00_001BF200.position, &point);
        func_00283028((&state->velocity), (&state->velocity), &D_L00_001BF200.normal);
        func_002E5CF8(1, 0, object);
        if (*(unsigned char *)(object + 0x20) == 0) {
            *(unsigned char *)(object + 0x20) = 3;
            ++state->bounces;
            if (state->bounces == 1) {
                func_00282F70((&state->velocity), (&state->velocity), D_L00_001B091C * 0.020000001f);
                if (D_L00_001A8FF0 != 0) {
                    dot = func_00282DB0((&state->velocity), &scratch.motion.normal);
                    func_00282D30(&temporary, &scratch.motion.normal, -dot);
                    func_00282CF0(&vertical, (&state->velocity), &temporary);
                    func_00282D30(&temporary, &temporary, D_L00_001B0918);
                    func_00282CC0((&state->velocity), &vertical, &temporary);
                } else {
                    state->velocity.v[2] *= D_L00_001B0918;
                }
                func_003001E0((&state->velocity), (&state->velocity), (Vector *)(object + 0x10));
            } else {
                func_00282D30(&temporary, (&state->velocity), D_L00_001B0918);
                speed = func_00282E20(&temporary);
                minimum = D_L00_001B0908 * 0.020000001f;
                if (speed < minimum) {
                    func_00282F70((&state->velocity), (&state->velocity), minimum);
                    if (D_L00_001A8FF0 != 0) {
                        dot = func_00282DB0((&state->velocity), &scratch.motion.normal);
                        func_00282D30(&vertical, &scratch.motion.normal, -dot);
                        func_00282CF0(&tangent, (&state->velocity), &vertical);
                        func_00282D30(&vertical, &vertical, D_L00_001B0918);
                        func_00282CC0((&state->velocity), &tangent, &vertical);
                    } else {
                        state->velocity.v[2] *= D_L00_001B0918;
                    }
                    func_003001E0((&state->velocity), (&state->velocity), (Vector *)(object + 0x10));
                } else {
                    qcopy((&state->velocity), &temporary);
                }
            }
        }
        if (state->bounces >= 4) {
            *(unsigned char *)(object + 0x20) = 2;
            if (D_L00_001A8FF0 != 0) {
                dot = func_00282DB0((&state->velocity), &scratch.motion.normal);
                func_00282D30(&temporary, &scratch.motion.normal, -dot);
                func_00282CF0((&state->velocity), (&state->velocity), &temporary);
            } else state->velocity.v[2] = 0.0f;
            {
                float min;
                state->velocity.v[3] = func_00282E20(&state->velocity);
                state->velocity.v[3] *= D_L00_001B0918;
                min = D_L00_001B0908 * 0.020000001f;
                if (state->velocity.v[3] < min)
                    state->velocity.v[3] = min;
            }
            func_00282F20((&state->velocity), (&state->velocity), state->velocity.v[3]);
            func_003001E0((&state->velocity), (&state->velocity), (Vector *)(object + 0x10));
            state->fade_scale = 1.0f / func_00283CE0(state->timer);
        }
        break;
    case 2:
        scratch.color = D_L00_001B0920;
        fade = (float)state->timer * state->fade_scale;
        red = func_00283CF0((scratch.color.r - 255.0f) * fade + 255.0f);
        green = func_00283CF0(scratch.color.g * fade);
        blue = func_00283CF0(scratch.color.b * fade);
        {
            float slowdown = (D_L00_001B090C - 1.0f) * 1.2f + 1.0f;
            float min = D_L00_001B0908 * 0.020000001f;
            unsigned int packed = blue << 16;
            packed |= 0xff000000;
            packed |= green << 8;
            packed |= red;
            *(unsigned int *)(object + 0x78) = packed;
            state->velocity.v[3] *= slowdown;
            if (state->velocity.v[3] < min)
                state->velocity.v[3] = min;
        }
        func_00282F20((&state->velocity), (&state->velocity), state->velocity.v[3]);
        func_00282CC0((Vector *)(object + 0x10), (Vector *)(object + 0x10), (&state->velocity));
        func_00300190((Vector *)(object + 0x10), (Vector *)(object + 0x10));
        break;
    case 3:
        damage = ((DamageTableRow *)(D_00139587 * 0xe0 + (int)D_L00_00262570))->damage;
        func_002E5DA0(5, 0, object, 0xb02);
        func_PAL_002AC718(object, 0.0f, (&state->velocity), 0.0f, (Vector *)(object + 0x10), 5, 2, 4,
                     6.0f, 2.0f, 9.0f, 1.0f, 0, 15.0f, 1, 1, -1, 0, 0x810001);
        func_002A8BD0((char *)&scratch.request, (int)object, 0x810000, damage);
        scratch.request.enabled = 2;
        scratch.request.kind = 1;
        scratch.request.object_class = *(unsigned short *)(object + 0xaa);
        count = func_00277F48((Vector *)(object + 0x10), 0x10, object, &scratch.request, 6.0f);
        if (count > 0) {
        int remaining = count;
        hit = D_L00_001C3280;
        do {
            func_PAL_00335DD0(*hit, 61, *(int *)(object + 0xb8));
            ++hit;
            --remaining;
        } while (remaining != 0);
        }
        func_0029F338(object);
        return;
    }
    if (*(unsigned char *)(object + 0x20) < 2) speed = func_00282E20(&state->velocity);
    else if (*(unsigned char *)(object + 0x20) == 2) speed = state->velocity.v[3];
    else return;
    {
        float lo = 0.004f;
        float hi = 0.120000005f;
        float ratio;
        if (speed < lo) speed = lo;
        if (speed > hi) speed = hi;
        speed -= lo;
        ratio = speed / (hi - lo);
        *(float *)(object + 0xf4) = func_00283B98((ratio * 7.0f + 1.0f) * 0.017453294f,
                                               *(float *)(object + 0xf4));
    }
}
