/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* sol-high near miss, USA v1.01, default -O2 -G0 -ffunction-sections.
 * Best check: 1588/1588 bytes, 0 of 4 places; first mismatch at +0x54.
 * This improves the earlier 1580-byte -G8 draft: the save-table branches and
 * prologue now mostly agree. Remaining differences include the save-table
 * address register, conditional lock-flag stores, state/active store order,
 * and the placement of the case-2 entry. Equal size is not an exact match.
 * Incomplete sda arrays recover the tied absolute macros without hoisting;
 * explicitly capturing the camera index before the lock write preserves
 * retail's conditional reload, and sharing the camera-table pointer across
 * both qcopies prevents an extra pointer load. Capturing saveIndex before
 * the activation stores reproduces its earlier load. All declarations follow.
 * -G8 and -mno-split-addresses were worse; do not repeat those blindly.
 * Remaining lock stores need retail's two-word absolute macro form without
 * turning into GP stores in likely slots or splitting the address into a GPR.
 * Corrected the old draft's camera symbols: 0x001B94C0 and 0x001B9780.
 */
#include "common.h"
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
extern void func_L01_00394148(CamMoby *);
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern u8 D_L01_0021E4B0[];
extern char D_00189EA0[];
extern int D_0018A160 NOT_SDA;
extern int D_001A79F0 MACRO_ADDR;
extern CamQuad D_L01_001B94C0[2];
extern char *D_L01_001B264C[] __attribute__((sda));
extern int D_L01_001B1FA8[] __attribute__((sda));
extern int D_L01_001B22A8[] NOT_SDA;
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
extern void func_L01_002C1988(int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
void func_L01_00394240(CamMoby *m)
{
    CamVars *v = m->vars;
    CamQuad position, rotation;
    int saved;
    func_L01_00394148(m);
    switch (m->state) {
    case 0:
        if (v->requireEnabled && (D_0019B2E8[m->index + (D_001A79F0 << 4)] & 0x80)) {
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
        if (D_L01_0021E4B0[0x464 + (s16)m->saveIndex]) goto saved_state;
        saved = D_0019B4A8[((s16)m->saveIndex >> 1) + (D_001A79F0 << 10)];
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
            qcopy(&position, &D_L01_001B94C0[0]);
            qcopy(&rotation, &D_L01_001B94C0[1]);
            if (v->source == -1) func_L00_002B9D60(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_L00_002B9D60(D_L01_001B264C[0] + v->source * 128 + 0x30,
                                  D_L01_001B264C[0] + v->source * 128 + 0x70, 0x6F, 1);
            if (v->mode) func_00335438(&position, &rotation, 2, v->parameter, 0);
            else func_00335438(D_L01_001B264C[0] + v->camera * 128 + 0x30,
                              D_L01_001B264C[0] + v->camera * 128 + 0x70, 0, 0, 0);
            D_L01_001B1FA8[0] = 1;
            m->state = 2;
            m->active = 1;
            { int camera = v->camera;
            if (v->lock) { D_L01_001B22A8[0] = 1; camera = v->camera; }
            { char *base = D_L01_001B264C[0];
            qcopy(&v->position, base + camera * 128 + 0x30);
            qcopy(&v->rotation, base + camera * 128 + 0x70); } }
        }
        if (D_001A79F0 == 19 &&
            (func_002ACBC8(D_00189EA0, v->trigger) || m->active == 1 || func_002B38B8(m)) &&
            (!v->requireHero || D_0018A160)) {
            qcopy(&position, &D_L01_001B94C0[0]);
            qcopy(&rotation, &D_L01_001B94C0[1]);
            if (v->source == -1) func_L00_002B9D60(D_00189EA0, D_00189EA0 + 0x10, 0x6F, 1);
            else func_L00_002B9D60(D_L01_001B264C[0] + v->source * 128 + 0x30,
                                  D_L01_001B264C[0] + v->source * 128 + 0x70, 0x6F, 1);
            if (v->mode) func_00335438(&position, &rotation, 2, v->parameter, 0);
            else if (D_001A79F0 == 19) func_00335438(D_L01_001B264C[0] + v->camera * 128 + 0x30,
                                                 D_L01_001B264C[0] + v->camera * 128 + 0x70, 1, 0, 0);
            else func_00335438(D_L01_001B264C[0] + v->camera * 128 + 0x30,
                              D_L01_001B264C[0] + v->camera * 128 + 0x70, 0, 0, 0);
            { unsigned int saveIndex = m->saveIndex;
            D_L01_001B1FA8[0] = 1;
            m->state = 2;
            m->active = 1;
            if (saveIndex & 1) {
                int level = D_001A79F0;
                int index = (s16)saveIndex;
                u8 *p = D_0019B4A8 + ((index >> 1) + (level << 10));
                if (((*p >> 4) & 7) != 7) *p += 16;
            } else {
                int level = D_001A79F0;
                int index = (s16)saveIndex;
                u8 *p = D_0019B4A8 + ((index >> 1) + (level << 10));
                if ((*p & 7) != 7) ++*p;
            } }
            { int camera = v->camera;
            if (v->lock) { D_L01_001B22A8[0] = 1; camera = v->camera; }
            { char *base = D_L01_001B264C[0];
            qcopy(&v->position, base + camera * 128 + 0x30);
            qcopy(&v->rotation, base + camera * 128 + 0x70); } }
        }
        break;
    case 2:
        if (func_00282948(&v->timer) || m->active != 1) {
            if (v->mode) func_003355A8(2);
            else func_003355A8(0);
            func_L01_002C1988(0);
            if (v->lock) D_L01_001B22A8[0] = 0;
            D_L01_001B1FA8[0] = 0;
            D_L01_001B9780 = 0;
            m->state = 3;
            m->active = 0;
        } else {
            if (v->lock) D_L01_001B22A8[0] = 1;
            func_00335370(&v->position);
            func_003353C8(&v->rotation);
        }
        break;
    case 3:
        if (v->reset && !(D_0019B2E8[m->index + (D_001A79F0 << 4)] & 0x80)) {
            func_002A0430(m->index);
            func_002DF3F8((char *)m + 0x10, (char *)m + 0xF0);
        }
        if (m->active == 1) m->state = 1;
        break;
    }
}
