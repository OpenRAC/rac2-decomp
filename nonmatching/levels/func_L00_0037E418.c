/* func_L00_0037E418 - 420 bytes, 27 places (src/levels/shared/L00_0037DD80.c):
   level start-up: clears four tables, runs twelve init routines, spawns the
   object at (5, 5, 5) and resets D_L00_001B26A8/B0/B4.

   Unit: src/levels/shared/L00_0037E418-por-g8.c with
   `-O2 -G8 -ffunction-sections -frac2-zero-ti-por` (the -G8 gives the $gp
   store of D_L00_001ADB2C, the por flag gives retail's `por` + `sq` zero of
   the stack vector).  With those, only the first loop differs: 416 of 420.

   Retail's first loop is not reversed: a pointer from &D_L00_0022FF40[0]
   steps by 0x50 and is compared with `slt` against the end (base + 0x1400),
   with `bnel` and the next `sb` in its delay slot.  GCC reverses it here
   into a count-down (bgez).  Same result for i < 64, i <= 63, i != 64, a
   do-while, a slot pointer in the body and a byte-offset counter. */

#include "include_asm.h"
#include "common.h"

/* func_L00_0037E418 needs -G8 and -frac2-zero-ti-por: retail zeroes the stack vector
   with `por` + `sq` before filling it. */

typedef struct {
    u32 field00, field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;

extern u8 D_L00_00231340[];

typedef struct {
    u8 pad00;
    u8 flag01;
    u8 pad02[0x3E];
    s32 word40;
    u8 pad44[0xC];
} Slot0037E418;

typedef int Ti0037E418 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec0037E418 __attribute__((aligned(16)));
typedef struct { u8 pad[0x34]; unsigned short flags; u8 pad2[0x98 - 0x36]; s32 f98; } Obj0037E418;

extern Slot0037E418 D_L00_0022FF40[];
extern u8 D_L00_00231A60[128][0x20];
extern s32 D_L00_00231950[64];
extern s32 D_L00_00231940[];
extern Obj0037E418 *D_L00_001B26A8[] __attribute__((sda));
extern s32 D_L00_001B26B0[] __attribute__((sda));
extern s32 D_L00_001ADB2C __attribute__((sda));
extern s32 D_L00_001B26B4_sda __attribute__((sda));
extern void func_L00_003BB600(void);
extern void func_L00_003C58E0(void);
extern void func_L00_003CA470(void);
extern void func_L00_003D5320(void);
extern void func_L00_003E5328(void);
extern void func_L00_003ECB00(void);
extern void func_L00_003EF548(void);
extern void func_L00_003F1448(void);
extern void func_L00_00387EF0(void);
extern void func_L00_0038A968(void);
extern void func_L00_003F8E08(void);
extern void func_L00_004115E8(void);
extern Obj0037E418 *func_00382560(Vec0037E418 *);
extern void func_L00_0037FF98(void);

void func_L00_0037E418(void)
{
    int i;
    Vec0037E418 v;
    int off;
    Obj0037E418 *obj;
    OrbitalPairTableView16 *pairs = (OrbitalPairTableView16 *)D_L00_00231340;

    D_L00_001ADB2C = 0;
    for (i = 0; i < 64; i++) {
        D_L00_0022FF40[i].flag01 = 0;
        D_L00_0022FF40[i].word40 = 0;
    }
    for (i = 31; i >= 0; i--)
        pairs[i].field04 = 0;
    for (i = 127; i >= 0; i--)
        *(s32 *)&D_L00_00231A60[i][0x1C] = 0;
    for (i = 63; i >= 0; i--)
        D_L00_00231950[i] = -1;
    D_L00_00231950[64] = 0;
    D_L00_00231940[0] = 0;
    func_L00_003BB600();
    func_L00_003C58E0();
    func_L00_003CA470();
    func_L00_003D5320();
    func_L00_003E5328();
    func_L00_003ECB00();
    func_L00_003EF548();
    func_L00_003F1448();
    func_L00_00387EF0();
    func_L00_0038A968();
    func_L00_003F8E08();
    func_L00_004115E8();
    *(Ti0037E418 *)&v = 0;
    v.x = 5.0f;
    v.y = 5.0f;
    v.z = 5.0f;
    v.w = 1.0f;
    obj = func_00382560(&v);
    D_L00_001B26A8[0] = obj;
    obj->f98 = 0;
    obj->flags |= 2;
    D_L00_001B26B0[0] = 0;
    D_L00_001B26B4_sda = 0;
    func_L00_0037FF98();
}
