#include "common.h"

/* func_US2_L01_00395620, the USA v2.00 copy of func_L01_00394240
   (L01_002A7248-cam.c): the same C, plus two calls of this level's
   ref_L01_00394240_02(0x6F, 1) (func_US2_L01_002BEEA8 in Oozla, a per-level
   function): after the second trigger's save-slot update and before the
   camera update in state 2. That function returns a value on every path
   (`daddu $v0,$zero,$zero` on its early exits), so it is declared int; the
   ignored result is what puts the lock flag in $v1 after the first call.

   func_L01_00394240 has a unit of its own because it calls func_L01_00394148
   with the moby, which that function's (void) definition in L01_002A7248.c
   does not accept. func_L01_00394148 is this level's copy of the helper
   func_L04_00423178(object), which tests kinds instead of the object's id, so
   its parameter went unused. Retail still sets up the call: the move of the
   moby into $a0 takes the issue slot beside `sd $s3` and is deleted after
   scheduling ($a0 already holds it). That puts `li $s2,1` after `sd $s4`. */
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
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00335438(void *, void *, int, int, int);
extern int func_002B38B8(void *);
extern int func_00282948(void *);
extern void func_003355A8(int);
extern void ref_L01_00394240_01(int);
extern int ref_L01_00394240_02(int, int); /* result unused here */
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
void func_US2_L01_00395620(CamMoby *m)
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
            if (v->source == -1) func_L00_002B9D60(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_L00_002B9D60(&D_L01_001B264C[0][v->source].forward[3],
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
            if (v->source == -1) func_L00_002B9D60(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_L00_002B9D60(&D_L01_001B264C[0][v->source].forward[3],
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
            ref_L01_00394240_02(0x6F, 1);
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
            ref_L01_00394240_02(0x6F, 1);
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
