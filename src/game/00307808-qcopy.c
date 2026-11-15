#include "include_asm.h"
#include "common.h"

typedef float V4_F307808[4] __attribute__((aligned(16)));

extern u8 D_00139568[];
extern char D_00239BA0[];
extern s32 D_001AEC68 __attribute__((sda));

extern void func_0029FCC0(char *, s32, void *);
extern void func_002FE8D8(char *, void *);
extern char *func_002AB1F0(char *);
extern void func_00282D30(void *, char *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_003001E0(void *, void *, void *);
extern s32 func_002E5DA0(s32, s32, char *, s32);
extern char *func_0031D3E0(void *, void *, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short, void *);

#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: fires the pending shot and counts it down. */
void func_00307808(char *obj)
{
    V4_F307808 a, b, c, d, e;
    char *rec = *(char **)(obj + 0x68);
    char *link;
    char *tgt;
    float scale;
    char *ent;
    char *fx;

    func_0029FCC0(obj, 1, d);
    func_002FE8D8(obj + 0x10, a);
    if (*(float *)(rec + 0x5C) == 0.0f) {
        if (*(s32 *)(rec + 0x50) != 0) {
            if (*(char **)(rec + 0x64) != 0) {
                link = func_002AB1F0(*(char **)(rec + 0x64));
                tgt = *(char **)(rec + 0x64);
                qcopy(b, tgt + 0x10);
                if (link != 0) {
                    FastVecScale(e, tgt + 0xE0, *(float *)(link + 0x10));
                    FastVecAdd(b, b, e);
                }
                ent = ENTRY();
                scale = *(float *)(ent + 0x50) * 0.016666668f;
                FastVecSub(c, b, d);
                vec_scale_to_length(c, c, scale);
                func_002E5DA0(0, 0, obj, 0x1367);
                fx = func_0031D3E0(d, c, 2.0f, 15.0f, 0.5f, 3.0f, 0x50, 0xC8, 1, 0, 0x10E, *(char **)(rec + 0x64));
                if (fx != 0)
                    *(s32 *)(fx + 0xB8) = *(s32 *)(rec + 0x68);
                *(s32 *)(rec + 0x40) = D_001AEC68;
                *(s32 *)(rec + 0x44) = 6;
                if (--*(s32 *)(rec + 0x60) <= 0)
                    *(u8 *)(obj + 0x20) = 8;
                *(float *)(rec + 0x5C) = 0.6666667f;
            }
        }
    }
}
