#include "include_asm.h"

#include "common.h"

extern void *CreateMoby(s32);
extern short D_L10_001B2DB8[4];
extern short D_L10_001B2DC0[4];
extern char D_L10_00234600[];
extern int FastDecTimer(short *);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_signed_float_range(f32, f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void math_l00_interpolate_cubic_vector(void *, void *, void *, void *, void *, f32);

typedef struct { int status; u8 reserved[36]; } GornStatusRecord156;

extern GornStatusRecord156 D_L10_002A3C70[];


/* Report whether any configured status in the selected eleven records is nonzero */
int status_any_record_nonzero(void)
{
    if (D_L10_002A3C70[2].status != 0 ||
        D_L10_002A3C70[3].status != 0 ||
        D_L10_002A3C70[4].status != 0 ||
        D_L10_002A3C70[5].status != 0 ||
        D_L10_002A3C70[8].status != 0 ||
        D_L10_002A3C70[9].status != 0 ||
        D_L10_002A3C70[10].status != 0 ||
        D_L10_002A3C70[11].status != 0 ||
        D_L10_002A3C70[12].status != 0 ||
        D_L10_002A3C70[13].status != 0 ||
        D_L10_002A3C70[14].status != 0)
        return 1;
    return 0;
}

/* Creates a strip-effect object with its supplied vectors and rendering parameters. */
void *CreateEnergyStrip(void *position, void *direction, s32 duration, s32 kind,
                       s32 first, s32 second, float jitter, s32 third, s32 texture,
                       float width, float height, float fade) {
    u8 *object = CreateMoby(0x133E /* moby class 4926 */);
    char *state;
    int i;
    if (object) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        *(u16 *)(object + 0x32) = 255;
        object[0x31] = 1;
        object[0x20] = 0;
        *(s32 *)(state + 0x2C) = kind;
        *(s32 *)(state + 0x10) = duration;
        *(s32 *)(state + 0x14) = first;
        *(s32 *)(state + 0x18) = second;
        *(s32 *)(state + 0x1C) = third;
        *(float *)(state + 0x20) = width;
        *(float *)(state + 0x24) = height;
        *(float *)(state + 0x28) = fade;
        *(s32 *)(state + 0x30) = texture;
        *(float *)(state + 0x34) = jitter;
        qcopy(state, direction);
        qcopy((object + 0x10), position);
        for (i = 2; i >= 0; i--) D_L10_001B2DB8[i] = -1;
    }
    return object;
}

extern void RebuildTimedLightningStripPoints(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern u8 D_L10_0039D9C0[];

/* Refreshes and then hands the constructor at 0x0039D9C0 to the callback list. */
void lightning_strip_refresh_call_ctor(void *moby) {
    RebuildTimedLightningStripPoints(moby);
    gfx_add_draw_callback_third(D_L10_0039D9C0, moby);
}

/* Rebuilds each expired lightning strip and jitters its interior control points. */
void RebuildTimedLightningStripPoints(void *object) {
    f32 point[4];
    f32 direction[4];
    f32 result[4];
    char *self = object;
    char *state = *(char **)(self + 0x68);
    f32 t;
    int strip, i, j;
    for (strip = 0; strip < 4; strip++) {
        if (FastDecTimer(&D_L10_001B2DB8[strip])) {
            D_L10_001B2DB8[strip] = 2;
            D_L10_001B2DC0[strip] = 0;
            qcopy(point, state);
            point[0] += math_random_float_range(0.0f, 0.0f);
            point[1] += math_random_float_range(0.0f, 0.0f);
            point[2] += math_random_float_range(0.0f, 0.0f);
            FastVecSub(direction, point, self + 0x10);
            vec_scale_to_length(direction, direction, 0.5f);
            FastVecAdd(direction, point, direction);
            for (i = 0; i < 8; i++) {
                t = (f32)i * 0.1f;
                if (i == 7) t = 1.0f;
                math_l00_interpolate_cubic_vector(result, self + 0x10, point, direction, direction, t);
                qcopy(((f32 (*)[8][4])D_L10_00234600)[strip][i], result);
            }
            for (j = 1; j < 7; j++) {
                qcopy(result, ((f32 (*)[8][4])D_L10_00234600)[0][j]);
                result[0] += math_random_signed_float_range(0.0f, *(f32 *)(state + 0x34));
                result[1] += math_random_signed_float_range(0.0f, *(f32 *)(state + 0x34));
                result[2] += math_random_signed_float_range(0.0f, *(f32 *)(state + 0x34));
                qcopy(((f32 (*)[8][4])D_L10_00234600)[0][j], result);
            }
        }
    }
}

extern int D_L10_001AEEC0 __attribute__((sda));

extern int math_fast_float_d(void *);

extern void moby_mark_spawned(void *);

extern char D_L10_00234600[];

extern void DrawHrugisRibbon(void *, int, int, int, float, float, float, int, int);

/* Ticks the level's spawn counter down to zero, else spends the record through the effect
   constructor at 0x0039DA48 with the record's own vectors. */
void lightning_build_strip_from_records(void *moby) {
    char *vars = *(char **)((char *)moby + 0x68);

    if (math_fast_float_d(vars + 0x10) == 0) {
        DrawHrugisRibbon(D_L10_00234600, *(int *)(vars + 0x1C), *(int *)(vars + 0x30), 8,
                          *(float *)(vars + 0x24), *(float *)(vars + 0x28),
                          *(float *)(vars + 0x20), *(int *)(vars + 0x14), *(int *)(vars + 0x18));
    } else {
        D_L10_001AEEC0 = D_L10_001AEEC0 - 1;
        if (D_L10_001AEEC0 < 0)
            D_L10_001AEEC0 = 0;
        moby_mark_spawned(moby);
    }
}

/* func_L10_0039DA48 lives in L10_0037D200-ribbon.c. */


/* func_L10_004190F0 lives in L10_004190F0.c. */

extern char *moby_get_motion_data(void *);

extern int math_random_int_below(int);

extern int PlayMobySound(int, int, char *);

/* The engine's effect call: four floats in $f12-$f15, the object in $a0 and seven
   words in $a1-$a3, $t0-$t2. The fourth float sits after the object arguments
   because the retail code sets the registers up in that order. */
extern void SpawnSpaceProjectile(float, float, float, void *, int, int, int, float, int, int, int);

/* Kills the object: the type at 0x20 picks the effect, and the hit state at 0x268
   ends up at 0x19. */
void lightning_object_update_state(void *self)
{
    void *moby = self;
    void *state = *(void **)((char *)moby + 0x68);
    void *motion = moby_get_motion_data(moby);

    if (motion == 0)
        return;
    if (*(int *)((char *)motion + 0x120) == 0)
        return;
    if (*(int *)((char *)state + 0x268) != 0)
        return;
    if (*(unsigned char *)((char *)moby + 0x20) == 2) {
        SpawnSpaceProjectile(0.9f, 13.0f, 4.5f, moby, 0x60000080, 0, 1, 1.0f, 0, -1, 0);
    } else if (*(unsigned char *)((char *)moby + 0x20) == 1) {
        if (math_random_int_below(2) != 0)
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, moby, 0x60800000, 1, 0, 1.0f, 0, -1, 0);
        else
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, moby, 0x60800080, 1, 0, 1.0f, 0, -1, 0);
    }
    if (math_random_int_below(3) == 0)
        PlayMobySound(0, 0, moby);
    *(int *)((char *)state + 0x268) = 0x19;
}


/* func_L10_004235A0 lives in L10_004235A0-g8.c. */

