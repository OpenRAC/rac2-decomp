#include "include_asm.h"

#include "common.h"
typedef float V4_F305058[4] __attribute__((aligned(16)));
extern u8 D_00139568[];
extern char D_00239BA0[];
extern s32 D_001AEC08 __attribute__((sda));
extern void func_0029FCC0(char *, s32, void *);
extern void func_002FE8D8(char *, void *);
extern char *func_002AB1F0(char *);
extern void func_00282D30(void *, char *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_003001E0(void *, void *, void *);
extern void func_PAL_003066B8(char *, void *);
extern s32 func_002E5CF8(s32, s32, char *);
#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: aims the pending hit and counts it down. */
void func_PAL_003062B8(char *obj)
{
    V4_F305058 a, b, c, d, e;
    char *rec = *(char **)(obj + 0x68);
    char *link;
    char *tgt;
    float scale;
    char *ent;

    func_0029FCC0(obj, 1, d);
    func_002FE8D8(obj + 0x10, a);
    if (*(float *)(rec + 0x5C) == 0.0f) {
        if (*(s32 *)(rec + 0x50) != 0) {
            if (*(char **)(rec + 0x68) != 0) {
                link = func_002AB1F0(*(char **)(rec + 0x68));
                tgt = *(char **)(rec + 0x68);
                qcopy(b, tgt + 0x10);
                if (link != 0) {
                    func_00282D30(e, tgt + 0xE0, *(float *)(link + 0x10));
                    func_00282CC0(b, b, e);
                }
                ent = ENTRY();
                scale = *(float *)(ent + 0x50) * 0.020000001f;
                func_00282CF0(c, b, d);
                func_00282F20(c, c, scale);
                func_003001E0(c, c, d);
                func_PAL_003066B8(obj, c);
                func_002E5CF8(0, 0, obj);
                *(s32 *)(rec + 0x40) = ((s32)(D_001AEC08) * 5 + 2) / 6;
                *(s32 *)(rec + 0x44) = 5;
                if (--*(s32 *)(rec + 0x60) <= 0)
                    *(u8 *)(obj + 0x20) = 8;
                ent = ENTRY();
                *(float *)(rec + 0x5C) = 1.0f / *(float *)(ent + 0x54);
            }
        }
    }
}
