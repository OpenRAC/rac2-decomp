#include "include_asm.h"

#include "common.h"
typedef float V4_F2FFB68[4] __attribute__((aligned(16)));
extern s16 D_001B231A MACRO_ADDR;
extern char D_00239BA0[];
extern char D_00189E20[];
typedef struct { u8 pad[0x1220]; s32 word; } HeroRec50;
typedef struct { u8 pad[0x22E4]; s32 word[1]; } HeroTable;
extern s32 D_001A7398[] MACRO_ADDR;
extern void func_002FF3F8(void);
extern void func_0029F338(void *);
extern s32 func_00294630(s32);
extern void func_00294420(s32);
extern void func_PAL_002B8898(s32);
extern void func_PAL_00295298(s32);
extern char *func_002FF300(s32, s32);

/* Spawns the object for the current mode and hands it the caller's position and rotation. */
char *func_PAL_00300C98(char *obj)
{
    V4_F2FFB68 pos, rot;
    s32 mode = -1;
    s16 id = D_001B231A;
    char *rec;
    char *spawned;
    s32 slot;

    qcopy(pos, obj + 0x10);
    qcopy(rot, obj + 0xF0);
    if (id == 0x4D || id == 0x6B || id == 0x6C) {
        func_002FF3F8();
        mode = 0;
    } else if (id == 0x3D || id == 0x49 || id == 0x5D || id == 0x5E) {
        func_002FF3F8();
        mode = 1;
    } else {
        func_0029F338(obj);
        rec = D_00239BA0 + id * 0xE0;
        if (func_00294630(*(s32 *)(rec + 0x14)) == 0) {
            func_00294420(*(s32 *)(rec + 0x14));
            func_PAL_002B8898(1);
        }
        func_PAL_00295298(*(s32 *)(rec + 0x14));
    }
    rec = D_00239BA0 + id * 0xE0;
    spawned = func_002FF300(*(s32 *)(rec + 0x14), mode);
    if (spawned != 0) {
        qcopy(spawned + 0x10, pos);
        qcopy(spawned + 0xF0, rot);
        if (mode < 0) {
            slot = *(s32 *)(rec + 0xC);
            D_001A7398[slot] = 0;
            ((HeroRec50 *)(D_00189E20 + slot * 0x50))->word = 0;
            ((HeroTable *)D_00189E20)->word[slot] = 0;
        }
    }
    return spawned;
}
