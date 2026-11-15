#include "include_asm.h"

#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern float D_L11_001B12C8 __attribute__((sda));

/* Bleeds the ten rotation timers the level keeps beside its state: each armed
   entry loses a sixtieth of the shared rate and clamps at zero, disarming. */
void func_L11_004395C8(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        u8 *armed = (u8 *)(state + 0x380 + i);
        f32 *timer = (f32 *)(state + 0x2F0 + 4 * i);
        if (*armed == 1) {
            f32 left = *timer - D_L11_001B12C8 * 0.016666667f;
            *timer = left;
            if (left < 0.0f) {
                *timer = 0.0f;
                *armed = 2;
            }
        }
    }
}

extern float D_L11_001B1338 __attribute__((sda));

extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_00282A60(unsigned int *, unsigned int, int);
extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);

/* Re-aims the object: resets the measured state, draws a random angle and
   clears the two rotation slots of the state. */
void func_L11_0043A9D8(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    float f20;
    float f0;

    *(unsigned char *)(state + 0x2E) = 3;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(short *)(state + 0x1A8) = 0;
    *(unsigned char *)(state + 0x18A) = 0;
    *(unsigned char *)(obj + 0x31) = 1;
    *(unsigned short *)(obj + 0x34) &= 0xFFFE;
    *(int *)(obj + 0x98) = *(int *)(*(int *)(obj + 0x24) + 0x10);
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x1000) & 0xFFB9;
    *(unsigned char *)(obj + 0x7F) = 0;
    if (*(unsigned char *)(obj + 0x43) != 1)
        func_002A7470(obj, 1, 0, 0);
    f20 = func_002A7878(10.0f, 30.0f) * 0.017453294f;
    if (func_002A77E0(2) != 0)
        f20 = -f20;
    *(float *)(state + 0x2D4) = f20;
    if (func_002A77E0(2) != 0)
        f0 = -D_L11_001B1338;
    else
        f0 = D_L11_001B1338;
    *(short *)(state + 0x2EE) = 0;
    *(float *)(state + 0x2DC) = f0;
    func_00282A60((unsigned int *)(state + 0x220), 0, 0x40);
    AttachManipulator((unsigned char *)obj, 2, (unsigned char *)(state + 0x220));
    func_00282A60((unsigned int *)(state + 0x260), 0, 0x40);
    AttachManipulator((unsigned char *)obj, 3, (unsigned char *)(state + 0x260));
}

extern float D_L11_001B12C4 __attribute__((sda));

extern int D_L11_001B359C;

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_00282F20(void *dst, void *src, float scale);

extern void func_002ACB48(float *p, float f);

extern int func_002A77E0(int n);

extern char *func_L11_004417E8(char *object);

extern void func_L11_004417A8(char *object, int value);

extern void func_L11_0043A680(void *a0, void *a1, float f0, float f1);


/* Aims the object at the entry its state names: crosses the entry with the record,
   jitters the result by a random sixtieth and hands it to the level's own helper.
   The table base is read afresh for each of the three groups, which is how retail
   keeps it in the caller-saved registers. */
void func_L11_004393D8(char *obj, int index, int flag)
{
    char *state = *(char **)(obj + 0x68);
    char *base1;
    char *base2;
    char *base3;
    int offset = index * 4;
    char *entry;
    float v[3];
    float t;
    int r;
    int rec;

    entry = func_L11_004417E8(*(char **)(obj + 0xB8));

    base1 = D_L11_001B359C;
    FastVecSub(v, entry, ((char *)(base1 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))) + 0x10);
    r = func_002A77E0(10) + 15;
    vec_scale_to_length(v, v, (float)r * (1.0f / 60.0f));
    func_002ACB48(v, 1.0f / 60.0f);
    r = func_002A77E0(5) + 5;
    v[2] = (float)r * (1.0f / 60.0f);

    t = 1.0f - ((float)*(short *)(state + 0x378) - 4.0f) * (1.0f / 6.0f);
    if (t > 1.0f)
        t = 1.0f;
    if (t < 0.0f)
        t = 0.0f;

    base2 = D_L11_001B359C;
    InitializeRandomizedObjectMotion(((char *)(base2 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))), v, D_L11_001B12C4 * (1.0f / 3600.0f), t);

    base3 = D_L11_001B359C;
    /* The record's field at 0xB8 takes the object's own handle. */
    *(int *)((char *)((*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8) + (int)base3)
            + 0xB8) = *(int *)(obj + 0xB8);
    rec = (int)((char *)(base3 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8)));
    *(int *)(state + 0x364) = rec;
    if (flag != 0)
        func_L11_004417A8(*(char **)(obj + 0xB8), rec);
    else
        func_L11_004417A8(*(char **)(obj + 0xB8), 0);

    *(unsigned char *)(state + index + 0x380) = 1;
}

typedef int TI128 __attribute__((mode(TI)));

/* The flat quad the effect submits: four positions, four colours, four uv
   pairs and the four GS words (primitive, texture, mode, registers). */
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectQuad;

typedef struct {
    TI128 saved;
    EffectQuad quad;
    float a[4];
    float b[4];
    float c[4];
    TI128 corner;
} EffectQuadFrame;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern char D_L11_001BA8C0[];
extern int D_L11_001B11FC __attribute__((sda));
extern int D_L11_001B1204 __attribute__((sda));
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L11_001B1210[] __attribute__((sda));
extern float D_L11_001B1214[] __attribute__((sda));

/* Draws the first stage of the beam between the state's two end points: each
   side is pulled a tenth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted as one textured quad. */
void func_L11_00434AF8(char *obj, void *q)
{
    EffectQuadFrame f;
    char *st;
    int i;

    f.saved = *(TI128 *)q;
    st = *(char **)(obj + 0x68);
    FastVecSub(f.c, st, st + 0x10);
    FastVecSub(f.a, st, D_L11_001BA8C0);
    FastVecSub(f.b, st + 0x10, D_L11_001BA8C0);
    FastVecCross(f.a, f.a, f.c);
    vec_scale_to_length(f.a, f.a, 0.1f);
    FastVecCross(f.b, f.b, f.c);
    vec_scale_to_length(f.b, f.b, 0.1f);
    f.quad.texture = GetEffectTextureDescriptor(7);
    f.quad.mode = 0x0000ff9000000260UL;
    f.quad.registers = ((unsigned long)D_L11_001B11FC << 32) | 0x48;
    f.quad.primitive = 0;
    f.quad.color[0] = f.quad.color[1] = f.quad.color[2] = f.quad.color[3] = D_L11_001B1204;
    for (i = 0; i < 4; i++) {
        f.quad.uv[i][0] = D_L11_001B1210[i * 2];
        f.quad.uv[i][1] = D_L11_001B1214[i * 2];
    }
    FastVecSub(&f.corner, st, f.a);
    f.quad.position[0] = f.corner;
    FastVecAdd(&f.corner, st, f.a);
    f.quad.position[1] = f.corner;
    FastVecSub(&f.corner, st + 0x10, f.b);
    f.quad.position[2] = f.corner;
    FastVecAdd(&f.corner, st + 0x10, f.b);
    f.quad.position[3] = f.corner;
    draw_world_quad(&f.quad, 0, 0);
}

extern int D_L11_001B1200 __attribute__((sda));
extern int D_L11_001B1208 __attribute__((sda));

/* The second stage: the same quad pulled a twentieth of the way in, drawn
   once with its own texture and then again with the additive overlay. */
void func_L11_00434D00(char *obj, void *q)
{
    EffectQuadFrame f;
    char *st;
    int i;

    f.saved = *(TI128 *)q;
    st = *(char **)(obj + 0x68);
    FastVecSub(f.c, st, st + 0x10);
    FastVecSub(f.a, st, D_L11_001BA8C0);
    FastVecSub(f.b, st + 0x10, D_L11_001BA8C0);
    FastVecCross(f.a, f.a, f.c);
    vec_scale_to_length(f.a, f.a, 0.05f);
    FastVecCross(f.b, f.b, f.c);
    vec_scale_to_length(f.b, f.b, 0.05f);
    f.quad.texture = GetEffectTextureDescriptor(0x13);
    f.quad.mode = 0x0000ff9000000260UL;
    f.quad.registers = ((unsigned long)D_L11_001B1200 << 32) | 0x48;
    f.quad.primitive = 0;
    f.quad.color[0] = f.quad.color[1] = f.quad.color[2] = f.quad.color[3] = D_L11_001B1208;
    for (i = 0; i < 4; i++) {
        f.quad.uv[i][0] = D_L11_001B1210[i * 2];
        f.quad.uv[i][1] = D_L11_001B1214[i * 2];
    }
    FastVecSub(&f.corner, st, f.a);
    f.quad.position[0] = f.corner;
    FastVecAdd(&f.corner, st, f.a);
    f.quad.position[1] = f.corner;
    FastVecSub(&f.corner, st + 0x10, f.b);
    f.quad.position[2] = f.corner;
    FastVecAdd(&f.corner, st + 0x10, f.b);
    f.quad.position[3] = f.corner;
    draw_world_quad(&f.quad, 0, 0);
    f.quad.texture = GetEffectTextureDescriptor(0x10);
    f.quad.mode = 0x0000ff9000000260UL;
    f.quad.registers = 0x8000000048UL;
    f.quad.primitive = 0;
    draw_world_quad(&f.quad, 0, 0);
}
