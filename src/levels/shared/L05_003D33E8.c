#include "include_asm.h"
#include "common.h"

extern char *CreateMoby(int);
extern char D_L05_001B96C0[];
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_spawn_large_explosion(void *, void *);

/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int GlowRingVector __attribute__((mode(TI)));
extern unsigned char ref_L05_00426348_00[];
extern unsigned char ref_L05_004268E8_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);

extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern u32 FastTweenColor(u32, u32, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } GlowRingSprite;
extern GlowRingSprite *part_spawn_fading(void *, u32, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowRingState;

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L05_001B2614 __attribute__((sda));

extern int D_L05_00221D10[];

extern char *moby_get_motion_data(char *object);

extern void moby_init_spawned_sub_object(char *object, int flag);

extern float math_random_float_range(float a, float b);

extern float math_random_angle(void);

extern void vec_build_spherical_offset(char *dst, float a, float b, float c);

extern void FastVecAdd(char *dst, char *src, char *src2);

extern int func_332AB8(int kind);

extern void gfx_add_draw_callback_third(void *, void *);

extern int ref_L05_00424780_00;

extern void moby_mark_spawned(char *);

extern int FastDecTimer(char *);

extern int ref_L05_00424C88_00;

extern void ref_L05_00424C88_01(void *, void *);

extern float D_L05_0023F920[][4][137][4];
extern float D_L05_0024A460[][4][137];
extern float D_L05_0024D020[][4][4];
extern int D_L05_0024CFD0[][4], D_L05_0024CF30[][4], D_L05_0024CF80[][4];
extern float D_L05_001B2F58[] __attribute__((sda)), D_L05_001B2F88[] __attribute__((sda));
extern float D_L05_001B2FB8[] __attribute__((sda)), D_L05_001B2FD0[] __attribute__((sda));
extern int D_L05_001B2F70[] __attribute__((sda)), D_L05_001B2FE8[] __attribute__((sda));
extern int D_L05_001B2FA0[] __attribute__((sda));
extern int func_001163B0(void);
extern void vec_clear_128(void *);

/* Clears the four emitters' 137 vectors of the object's slot, gives each a random speed, and
   starts the emitters around the object's position with random fades and lifetimes. */
void part_reset_emitter_slot_effect(char *obj)
{
    int *st = *(int **)(obj + 0x68);
    char *position = obj + 0x10;
    int i, j;
    float *v;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 137; j++) {
            float speed = math_random_float_range(0.5f, 4.0f);

            vec_clear_128(D_L05_0023F920[*st][i][j]);
            D_L05_0024A460[*st][i][j] = speed;
        }
        /* This slot and the actor position do not contain the private index. */
        qcopy_nc(D_L05_0024D020[*st][i], position);
        D_L05_0024CFD0[*st][i] = 6;
        D_L05_0024CF30[*st][i] = func_001163B0() % 128 + 128;
        D_L05_0024CF80[*st][i] = func_001163B0() % 2 + 6;
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[0] += jitter;
        }
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[1] += jitter;
        }
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[2] += jitter;
        }
    }
    D_L05_001B2F58[*st] = 0.01f;
    D_L05_001B2F70[*st] = 128;
    D_L05_001B2F88[*st] = 0.1f;
    D_L05_001B2FE8[*st] = 6;
    D_L05_001B2FA0[*st] = 128;
    D_L05_001B2FB8[*st] = 0.0f;
    D_L05_001B2FD0[*st] = 0.0f;
}


/* shared native body of family 5a97ab89858c */
/* Fills a four-corner sprite packet with default corners, colours and draw settings. */
void gfx_init_beam_packet(char *packet)
{
    *(long long *)(packet + 112) = 0;
    *(float *)(packet + 8) = -1.0f;
    *(float *)(packet + 24) = 1.0f;
    *(float *)(packet + 40) = -1.0f;
    *(float *)(packet + 56) = 1.0f;
    *(float *)(packet + 4) = -1.0f;
    *(float *)(packet + 36) = 1.0f;
    *(float *)(packet + 52) = 1.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -1.0f;
    *(float *)(packet + 60) = 1.0f;
}


/* Spawns the object's effect: marks the object, takes one record of the shared
   128-byte table by the global index and gives it a random position. */
void moby_init_effect_from_table(char *object)
{
    char *sub = *(char **)(object + 0x68);
    char *table;
    float distance, angleA, angleB;

    *(unsigned char *)(object + 0x20) = 1;
    *(unsigned short *)(object + 0x34) = *(unsigned short *)(object + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(object) + 0x148) = 1;
    moby_init_spawned_sub_object(object, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1C8) = 0x78;
    *(int *)(sub + 0x1C0) = -1;
    *(int *)(sub + 0x1C4) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    distance = math_random_float_range(0.0f, *(float *)table);
    angleA = math_random_angle();
    angleB = math_random_angle();
    vec_build_spherical_offset(object + 0x10, distance, angleA, angleB);
    FastVecAdd(object + 0x10, table + 0x30, object + 0x10);
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(object + 0x2C) = 0.02f;
}




/* func_L05_00418440 is matched in L05_00418440.c (built with -mno-split-addresses). */

extern void equipment_copy_owner_transform(char *, int);

extern void moby_copy_transform(char *, int);

extern void func_002A10E8(int);

/* Walks the state's fifteen id fields: a live one is handed to the level's own
    helper together with the object, then to the shared one. */
/* Keeps the equipment parts that are alive in step with the main object, one by one. */
void moby_sync_equipment_parts(char *object)
{
    char *vars;

    vars = *(char **)(object + 0x68);
    if (*(int *)(vars + 0x40) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x40));
        func_002A10E8(*(int *)(vars + 0x40));
    }
    if (*(int *)(vars + 0x44) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x44));
        func_002A10E8(*(int *)(vars + 0x44));
    }
    if (*(int *)(vars + 0x48) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x48));
        func_002A10E8(*(int *)(vars + 0x48));
    }
    if (*(int *)(vars + 0x4C) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x4C));
        func_002A10E8(*(int *)(vars + 0x4C));
    }
    if (*(int *)(vars + 0x50) != 0) {
        moby_copy_transform(object, *(int *)(vars + 0x50));
        func_002A10E8(*(int *)(vars + 0x50));
    }
    if (*(int *)(vars + 0xAC) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0xAC));
        func_002A10E8(*(int *)(vars + 0xAC));
    }
    if (*(int *)(vars + 0x1F0) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x1F0));
        func_002A10E8(*(int *)(vars + 0x1F0));
    }
    if (*(int *)(vars + 0x1F4) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x1F4));
        func_002A10E8(*(int *)(vars + 0x1F4));
    }
    if (*(int *)(vars + 0x1F8) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x1F8));
        func_002A10E8(*(int *)(vars + 0x1F8));
    }
    if (*(int *)(vars + 0x1FC) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x1FC));
        func_002A10E8(*(int *)(vars + 0x1FC));
    }
    if (*(int *)(vars + 0x200) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x200));
        func_002A10E8(*(int *)(vars + 0x200));
    }
    if (*(int *)(vars + 0x204) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x204));
        func_002A10E8(*(int *)(vars + 0x204));
    }
    if (*(int *)(vars + 0x208) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x208));
        func_002A10E8(*(int *)(vars + 0x208));
    }
    if (*(int *)(vars + 0x274) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x274));
        func_002A10E8(*(int *)(vars + 0x274));
    }
    if (*(int *)(vars + 0x278) != 0) {
        equipment_copy_owner_transform(object, *(int *)(vars + 0x278));
        func_002A10E8(*(int *)(vars + 0x278));
    }
}
/* func_L05_004186D8 is defined in L05_004186D8-g8.c. */




/* func_L05_00419370 is defined in L05_00419370-g8.c. */

/* func_L05_00419888 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B104C through $gp). */


/* func_L05_00419F10 is defined in L05_00419F10-g8.c. */

/* An empty function that does nothing. */
void stub_l05_empty(void)
{
    char buf[0x20];
}

/* func_L05_0041A228 is defined in L05_0041A228-g8.c. */


/* func_L05_0041C1F0 is defined in L05_0041C1F0-g8.c. */

/* Sets up the four glow sprites with random start phases, fixed speeds and sizes. */
void glow_l05_ring_init_state(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float *cursor = (float *)vars;
    int *wordPtr;
    int i;
    int j;
    int value;

    for (i = 3; i >= 0; i--)
        *cursor++ = (float)func_332AB8(0xFF);
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    j = 3;
    wordPtr = (int *)(vars + 0x2C);
    value = 0xFF;
    for (; j >= 0; j--) {
        *wordPtr = value;
        wordPtr = (int *)((char *)wordPtr - 4);
        value -= 0x40;
    }
    *(float *)(vars + 0x30) = 3.0f;
    *(float *)(vars + 0x34) = 3.7f;
    *(float *)(vars + 0x3C) = 3.0f;
    *(float *)(vars + 0x38) = 3.7f;
}





/* func_L05_0041D570 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1348 through $gp). */

/* Sets up the four glow sprites with random start phases, fixed speeds and sizes. */
void glow_l05_ring_init_state_2(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float *cursor = (float *)vars;
    int *wordPtr;
    int i;
    int j;
    int value;

    for (i = 3; i >= 0; i--)
        *cursor++ = (float)func_332AB8(0xFF);
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    j = 3;
    wordPtr = (int *)(vars + 0x2C);
    value = 0xFF;
    for (; j >= 0; j--) {
        *wordPtr = value;
        wordPtr = (int *)((char *)wordPtr - 4);
        value -= 0x40;
    }
    *(float *)(vars + 0x30) = 2.8f;
    *(float *)(vars + 0x34) = 3.5f;
    *(float *)(vars + 0x3C) = 2.8f;
    *(float *)(vars + 0x38) = 3.5f;
}


/* func_L05_0041ED18 is defined in L05_0041ED18-g8.c. */


/* func_L05_00421908 is in L05_003D33E8-reward-g8.c: -G8, with its own jump table. */

/* Registers the object for drawing when its flag is set, and marks it as visible. */
void part_register_draw_if_enabled(char *object)
{
    char *vars = *(char **)(object + 0x68);

    if (*(int *)(vars + 0xC) != 0)
        gfx_add_draw_callback_third(&ref_L05_00424780_00, object);
    *(unsigned short *)(object + 0x34) |= 0x41;
}

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern void ref_L05_004247C8_00(char *, void *);
extern char ref_L05_004247C8_01[];
extern float ref_L05_004247C8_02(void);
extern float ref_L05_004247C8_03(float);
extern float ref_L05_004247C8_04(float);
extern void ref_L05_004247C8_05(float *, float *, char *);
extern void ref_L05_004247C8_06(float *, float *, char *);
extern int ref_L05_004247C8_07(float);
extern void ref_L05_004247C8_08(float *, int, int, int, float, float, float);
extern float ref_L05_004247C8_09(float, float);
extern float ref_L05_004247C8_10(float);

/* Scatters 30 sparkle sprites around the object in a ring, each drawn twice. */
void part_spawn_ring_sparkles(char *object) {
    float point[4];
    char *state;
    int color;
    int grey;
    int i;
    float full;

    full = 128.0f;
    grey = 0x808080;
    state = FLD(object, char *, 0x68);
    ref_L05_004247C8_00(object + 0x10, ref_L05_004247C8_01);
    for (i = 29; i >= 0; i--) {
        float angle = ref_L05_004247C8_02();
        point[0] = 0.0f;
        point[1] = ref_L05_004247C8_03(angle);
        point[2] = -ref_L05_004247C8_04(angle);
        ref_L05_004247C8_05(point, point, object + 0xC0);
        ref_L05_004247C8_06(point, point, object + 0x10);
        ref_L05_004247C8_08(point, 0x13, (ref_L05_004247C8_07(full) << 24) | grey, 1, 0.25f, 0.1f, ref_L05_004247C8_02());
        {
            float half = 0.5f;
            int alpha = ref_L05_004247C8_07(full * half);
            color = FLD(state, int, 8);
            color &= 0xFFFFFF;
            color |= alpha << 24;
            ref_L05_004247C8_08(point, 0x13, color, 1, half, 0.1f, ref_L05_004247C8_02());
        }
    }
    FLD(state, float, 4) = 0.13380859792232513f;
    FLD(state, float, 0) = ref_L05_004247C8_09(FLD(state, float, 0), 0.13380859792232513f);
    ref_L05_004247C8_10(FLD(state, float, 0));
}

/* Sets the colour value of the effect. */
void effect_set_color(char *object, int value)
{
    char *vars = *(char **)(object + 0x68);

    *(int *)(vars + 0x8) = value;
}

/* Turns the effect on or off with the given value. */
void effect_set_enabled(char *object, int value)
{
    char *vars = *(char **)(object + 0x68);

    *(int *)(vars + 0xC) = value;
}

/* Creates a camera-facing burst, sets its lifetime and colors, and shakes
   the camera when a visible burst is nearby. */
char *part_spawn_shockwave_burst(void *pos, int shake, int c20, int c24, int c28,
                         int c2c, int c30, int unused, int c34, int mode,
                         int c38, float scale)
{
    float toward[4], up[4], sphere[4], cameraDir[4];
    char *obj = CreateMoby(0x116A /* moby class 4458 */);
    char *st;

    if (obj) {
        st = *(char **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        obj[0x20] = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        FastVecSub(toward, D_L05_001B96C0, (float *)(obj + 0x10));
        vec_scale_to_length(toward, toward, 1.0f);
        cam_compute_view_direction(obj + 0x10, up, 1);
        qcopy(obj + 0xC0, toward);
        FastVecCross(obj + 0xD0, obj + 0xC0, up);
        vec_scale_to_length((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(short *)st = 60;
        *(short *)(st + 2) = 60;
        *(float *)(st + 8) = scale + scale;
        *(float *)(st + 0xC) = scale * 4.0f;
        *(int *)(st + 0x20) = c20;
        *(int *)(st + 0x24) = c24;
        *(int *)(st + 0x28) = c28;
        *(int *)(st + 0x2C) = c2c;
        *(int *)(st + 0x30) = c30;
        *(int *)(st + 0x34) = c34;
        *(int *)(st + 0x1C) = mode;
        *(int *)(st + 0x38) = c38;
        *(float *)(st + 0x14) = scale;
        *(int *)(st + 0x18) = 0;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            *(short *)(st + 4) = 10;
            *(float *)(st + 0x10) = 0.1f;
            if (fast_vec_dist(pos, D_L05_001B96C0) < 48.0f && shake) {
                char *mgr = D_L05_001B96C0 - 0x140;

                *(int *)(mgr + 0x16C) = 0;
                *(int *)(mgr + 0x168) = 40;
                *(float *)(mgr + 0x160) = 0.075f;
            }
            if (*(int *)(st + 0x18)) {
                FastVecSub(cameraDir, obj + 0x10, (float *)D_L05_001B96C0);
                vec_scale_to_length(cameraDir, cameraDir, 1.0f);
                if (1.5707964f - math_fast_angle_helper(FastVecDot(cameraDir, D_L05_001B96C0 + 0x230)) < 0.45378566f)
                    *(int *)(st + 0x18) = 1;
                else
                    *(int *)(st + 0x18) = 0;
            }
        } else {
            *(short *)(st + 4) = 0;
            *(int *)(st + 0x18) = 0;
        }
        part_spawn_large_explosion(obj, up);
    }
    return obj;
}

/* Counts down two timers; when the first one has run out the object is deleted. */
void timed_effect_update(char *object)
{
    char *vars = *(char **)(object + 0x68);

    if (FastDecTimer(vars) == 0) {
        FastDecTimer(vars + 4);
        ref_L05_00424C88_01(&ref_L05_00424C88_00, object);
    } else {
        moby_mark_spawned(object);
    }
}


/* func_L05_00425058 is defined in L05_00425058-g8.c. */


/* func_L05_004260B8 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B14FC through $gp). */

/* Sets up the four glow sprites with random start phases, fixed speeds and sizes. */
void glow_l05_ring_init_state_3(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float *cursor = (float *)vars;
    int *wordPtr;
    int i;
    int j;
    int value;

    for (i = 3; i >= 0; i--)
        *cursor++ = (float)func_332AB8(0xFF);
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    j = 3;
    wordPtr = (int *)(vars + 0x2C);
    value = 0xFF;
    for (; j >= 0; j--) {
        *wordPtr = value;
        wordPtr = (int *)((char *)wordPtr - 4);
        value -= 0x40;
    }
    *(float *)(vars + 0x30) = 2.4f;
    *(float *)(vars + 0x34) = 3.0f;
    *(float *)(vars + 0x3C) = 2.4f;
    *(float *)(vars + 0x38) = 3.0f;
}

/* Draws four pulsing glow sprites in a short line in front of the object, each fading in. */
void glow_ring_draw_sprites(unsigned char *object)
{
    GlowRingState *glow = *(GlowRingState **)(object + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(GlowRingVector *)src = *(GlowRingVector *)(object + 0x10);
    src[2] += 0.25f;
    FastVecSub(m, ref_L05_00426348_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd((char *)m, (char *)m, (char *)src);

    for (i = 0; i < 4; i++) {
        float v = glow->phase[i] + glow->rate[i];
        u32 color;
        GlowRingSprite *s;
        glow->phase[i] = v;
        if (v >= 255.0f)
            glow->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            glow->phase[i] = v + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        v = math_fabs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x502020FF, 0x102020FF, v);
        s = part_spawn_fading(m, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd((char *)m, (char *)m, (char *)q);
    }
}


/* func_L05_00426568 is defined in L05_00426568-g8.c (it reaches D_L05_001B1500 through $gp). */

/* func_L05_00426658 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1500 through $gp). */

/* Sets up the four glow sprites with random start phases, fixed speeds and sizes. */
void glow_l05_ring_init(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float *cursor = (float *)vars;
    int *wordPtr;
    int i;
    int j;
    int value;

    for (i = 3; i >= 0; i--)
        *cursor++ = (float)func_332AB8(0xFF);
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    j = 3;
    wordPtr = (int *)(vars + 0x2C);
    value = 0xFF;
    for (; j >= 0; j--) {
        *wordPtr = value;
        wordPtr = (int *)((char *)wordPtr - 4);
        value -= 0x40;
    }
    *(float *)(vars + 0x30) = 2.0f;
    *(float *)(vars + 0x34) = 2.5f;
    *(float *)(vars + 0x3C) = 2.0f;
    *(float *)(vars + 0x38) = 2.5f;
}

/* Draws four pulsing glow sprites in a short line in front of the object, each fading in. */
void glow_l05_ring_draw(unsigned char *object)
{
    GlowRingState *glow = *(GlowRingState **)(object + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(GlowRingVector *)src = *(GlowRingVector *)(object + 0x10);
    src[2] += 0.25f;
    FastVecSub(m, ref_L05_004268E8_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd((char *)m, (char *)m, (char *)src);

    for (i = 0; i < 4; i++) {
        float v = glow->phase[i] + glow->rate[i];
        u32 color;
        GlowRingSprite *s;
        glow->phase[i] = v;
        if (v >= 255.0f)
            glow->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            glow->phase[i] = v + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        v = math_fabs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x50207FFF, 0x10207FFF, v);
        s = part_spawn_fading(m, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd((char *)m, (char *)m, (char *)q);
    }
}



/* func_L05_00426BE0 is defined in L05_003D33E8-g8.c (it reaches D_L05_001B1504 through $gp). */

/* Sets up the four glow sprites with random start phases, fixed speeds and sizes. */
void glow_l05_ring_init_2(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float *cursor = (float *)vars;
    int *wordPtr;
    int i;
    int j;
    int value;

    for (i = 3; i >= 0; i--)
        *cursor++ = (float)func_332AB8(0xFF);
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    j = 3;
    wordPtr = (int *)(vars + 0x2C);
    value = 0xFF;
    for (; j >= 0; j--) {
        *wordPtr = value;
        wordPtr = (int *)((char *)wordPtr - 4);
        value -= 0x40;
    }
    *(float *)(vars + 0x30) = 2.5f;
    *(float *)(vars + 0x34) = 3.2f;
    *(float *)(vars + 0x3C) = 2.5f;
    *(float *)(vars + 0x38) = 3.2f;
}




/* func_L05_00427238 lives in L05_003D33E8-g8.c. */

/* func_L05_004276E8 is defined in L05_004276E8-g8.c. */



/* func_L05_00427B20 is defined in L05_00427B20.c. */

/* func_L05_00427E10 lives in L05_00427E10-g8.c. */
