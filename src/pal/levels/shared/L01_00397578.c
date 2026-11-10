#include "include_asm.h"

#include "common.h"

/* func_PAL_L01_00397578, the PAL copy of func_L01_00394240 (L01_002A7248-cam.c): the same
   C, where switching the camera on rescales its timer to 50 Hz, and the trigger taken
   when D_001A79F0[0] is 19 and every frame of the running camera also call
   func_PAL_L01_002BEC60(0x6F, 1)
   (ref_PAL_L01_00397578_00: that function's copy in each level, which returns a value
   nobody reads). As in USA, func_L01_00394148 is called with the moby although its
   parameter went unused: it is this level's copy of func_L04_00423178(object), which
   tests kinds instead of the object's id. Retail still sets up the call: the move of the
   moby into $a0 takes the issue slot beside `sd $s3` and is deleted after scheduling
   ($a0 already holds it). That puts `li $s2,1` after `sd $s4`. */
typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;
typedef struct { MotionVec forward[4]; MotionVec inverse[4]; } MotionPath;
extern MotionPath *D_L01_001B264C[] __attribute__((sda));
extern char D_L01_001B94C0[];
extern char D_00189EA0[];
extern void func_L01_00394148(void *); /* the parameter is unused */

typedef int CamQuad __attribute__((mode(TI)));
typedef struct {
    CamQuad position, rotation;
    int trigger, camera, source, timer, mode, parameter;
    u8 reset, requireEnabled, requireHero, lock;
} CamVars;
typedef struct {
    char pad0[0x20]; u8 state; char pad21[0xF]; u8 field30; char pad31; u16 field32;
    char pad34[0x34]; CamVars *vars; char pad6C[0x3E]; s16 id; u16 group;
    char padAE[2]; u8 index; char padB1; u16 saveIndex; char padB4[8]; u8 active;
} CamMoby;
extern u8 D_0019B2E8[];
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B4A8[];
extern struct { u8 header[0x464]; u8 collected[0]; } D_L01_0021E4B0;
extern int D_0018A160 NOT_SDA;
extern int ref_L01_00394240_00 MACRO_ADDR;
extern int D_L01_001B1FA8[] __attribute__((sda));
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;
extern int D_L01_001B9780 NOT_SDA;
extern char D_L01_002A4370[];
extern void func_0026FEB8(void *, int, int);
extern void func_0029F338(void *);
extern int func_002ACBC8(void *, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_00335438(void *, void *, int, int, int);
extern int func_002B38B8(void *);
extern int func_00282948(void *);
extern void func_003355A8(int);
extern void ref_L01_00394240_01(int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern int ref_PAL_L01_00397578_00(int, int);
void func_PAL_L01_00397578(CamMoby *m)
{
    CamVars *v = m->vars;
    CamQuad position, rotation;
    int saved;
    func_L01_00394148(m);
    switch (m->state) {
    case 0:
        if (v->requireEnabled && (D_0019B2E8[m->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            func_0029F338(m);
        } else if (v->camera == -1) {
            func_0026FEB8(D_L01_002A4370, m->id, m->group);
            func_0029F338(m);
        } else {
            v->timer = ((s32)(v->timer) * 5 + 2) / 6;
            m->field30 = m->field32 = 255;
            m->state = 1;
        }
        break;
    case 1:
        if (D_L01_0021E4B0.collected[(s16)m->saveIndex]) goto saved_state;
        saved = D_0019B4A8[((s16)m->saveIndex >> 1) + (D_001A79F0[0] << 10)];
        if (m->saveIndex & 1) {
            if ((saved >> 4) & 7) goto saved_state;
        } else {
            if (saved & 7) {
            saved_state:
                m->state = 1;
                break;
            }
        }
        if ((func_002ACBC8(D_00189EA0, v->trigger) || m->active == 1) &&
            (!v->requireHero || *(int *)(D_00189EA0 + 0x2C0))) {
            qcopy(&position, D_L01_001B94C0);
            qcopy(&rotation, D_L01_001B94C0 + 16);
            if (v->source == -1) func_PAL_L00_002B9CD8(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_PAL_L00_002B9CD8(&D_L01_001B264C[0][v->source].forward[3],
                                  &D_L01_001B264C[0][v->source].inverse[3], 0x6F, 1);
            if (v->mode) func_00335438(&position, &rotation, 2, v->parameter, 0);
            else func_00335438(&D_L01_001B264C[0][v->camera].forward[3],
                              &D_L01_001B264C[0][v->camera].inverse[3], 0, 0, 0);
            D_L01_001B1FA8[0] = 1;
            m->state = 2;
            m->active = 1;
            if (v->lock) D_L01_001B22A0.busy = 1;
            { int camera = v->camera; MotionPath *base = D_L01_001B264C[0];
            qcopy(&v->position, &base[camera].forward[3]);
            qcopy(&v->rotation, &base[camera].inverse[3]); }
        }
        if (D_001A79F0[0] == 19 &&
            (func_002ACBC8(D_00189EA0, v->trigger) || m->active == 1 || func_002B38B8(m)) &&
            (!v->requireHero || D_0018A160)) {
            qcopy(&position, D_L01_001B94C0);
            qcopy(&rotation, D_L01_001B94C0 + 16);
            if (v->source == -1) func_PAL_L00_002B9CD8(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_PAL_L00_002B9CD8(&D_L01_001B264C[0][v->source].forward[3],
                                  &D_L01_001B264C[0][v->source].inverse[3], 0x6F, 1);
            if (v->mode) func_00335438(&position, &rotation, 2, v->parameter, 0);
            else if (D_001A79F0[0] == 19) func_00335438(&D_L01_001B264C[0][v->camera].forward[3],
                                                 &D_L01_001B264C[0][v->camera].inverse[3], 1, 0, 0);
            else func_00335438(&D_L01_001B264C[0][v->camera].forward[3],
                              &D_L01_001B264C[0][v->camera].inverse[3], 0, 0, 0);
            { unsigned int saveIndex = m->saveIndex;
            u8 *p;
            u8 b;
            D_L01_001B1FA8[0] = 1;
            m->active = 1;
            m->state = 2;
            if (saveIndex & 1) {
                p = &D_0019B4A8[((s16)saveIndex >> 1) + (D_001A79F0[0] << 10)];
                b = *p;
                if (((b >> 4) & 7) != 7) *p = b + 16;
            } else {
                p = &D_0019B4A8[((s16)saveIndex >> 1) + (D_001A79F0[0] << 10)];
                b = *p;
                if ((b & 7) != 7) *p = b + 1;
            } }
            ref_PAL_L01_00397578_00(0x6F, 1);
            if (v->lock) D_L01_001B22A0.busy = 1;
            { int camera = v->camera; MotionPath *base = D_L01_001B264C[0];
            qcopy(&v->position, &base[camera].forward[3]);
            qcopy(&v->rotation, &base[camera].inverse[3]); }
        }
        break;
    case 2:
        if (func_00282948(&v->timer) || m->active != 1) {
            if (v->mode) func_003355A8(2);
            else func_003355A8(0);
            ref_L01_00394240_01(0);
            if (v->lock) D_L01_001B22A0.busy = 0;
            D_L01_001B1FA8[0] = 0;
            D_L01_001B9780 = 0;
            m->state = 3;
            m->active = 0;
        } else {
            if (v->lock) D_L01_001B22A0.busy = 1;
            ref_PAL_L01_00397578_00(0x6F, 1);
            func_00335370(&v->position);
            func_003353C8(&v->rotation);
        }
        break;
    case 3:
        if (v->reset && !(D_0019B2E8[m->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            func_002A0430(m->index);
            func_002DF3F8((char *)m + 0x10, (char *)m + 0xF0);
        }
        if (m->active == 1) m->state = 1;
        break;
    }
}

extern int D_001A7340[] MACRO_ADDR;
extern int D_L00_001AF5A8[];
extern float func_00283CE0(s32);
extern u64 func_0027C878(s32);
extern int func_00283CF0(float);
extern s32 func_002A77E0(s32);
extern void func_0027E018(int, int, int, int, int, int, int, int, s64, u64);

/* Tiles an alpha-blended texture over the current viewport. */
void func_PAL_L01_0039A174(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = func_00283CE0(D_001A7340[2]);
    scale[1] = func_00283CE0(D_001A7340[3]);
    texture = func_0027C878(30);
    rows = D_001A7340[0] / 32 + 1;
    columns = D_001A7340[1] / 32 + 1;
    for (row = 0; row < rows; row++) {
        int *p = D_L00_001AF5A8;
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)*p;
            tick = func_00283CE0(*(int *)(state + 0x140));
            limit = func_00283CE0(75);
            opacity = (tick * 127.5f) / limit;
            color = (func_00283CF0(opacity) << 24) + 0x00FF7F7F;
            u = func_002A77E0(32);
            v = func_002A77E0(32);
            x = func_00283CF0(pos[0] - phase);
            y = func_00283CF0(pos[1] - phase);
            func_0027E018(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}

/* func_PAL_L01_0039AD60, the PAL copy of func_L01_00397950: the same stores, where the second loop
 * scales each value to 50 Hz and counts up. */
void func_PAL_L01_0039AD60(void *arg0) {
    s32 *base = *(s32 **)((u8 *)arg0 + 0x68);
    f32 *values = (f32 *)((u8 *)base + 0x20);
    s32 *slot;
    s32 i;

    for (i = 0; i < 4; i++) {
        *values = (f32)func_002A77E0(0xFF);
        values++;
    }

    *(f32 *)((u8 *)base + 0x30) = -1.0f;
    *(f32 *)((u8 *)base + 0x34) = -2.25f;
    slot = (s32 *)((u8 *)base + 0x40);
    *(f32 *)((u8 *)base + 0x38) = 1.25f;
    *(f32 *)((u8 *)base + 0x3C) = 2.5f;

    for (i = 0; i < 4; i++) {
        slot[i] = ((i * 0x40 + 0x3F) * 5 + 2) / 6;
    }

    *(f32 *)((u8 *)base + 0x50) = 2.5f;
    *(f32 *)((u8 *)base + 0x54) = 3.0f;
    *(f32 *)((u8 *)base + 0x5C) = 2.5f;
    *(f32 *)((u8 *)base + 0x58) = 3.0f;
}
