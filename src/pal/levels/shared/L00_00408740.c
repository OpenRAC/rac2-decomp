#include "include_asm.h"


typedef unsigned char u8;
typedef unsigned short u16;
struct Fx {
    char pad[0x18];
    u8 kind;
    u8 sub;
    u16 id;
    char pad2[0x14];
};
struct Ent {
    int used;
    u8 mode;
    char pad[0xDB];
};
struct Globals {
    char pad[0x18];
    char *hero;
};
extern struct Globals D_L00_001BF200;
extern char *D_L00_0018C0B0;
extern u8 D_L00_00139588;
extern struct Ent D_L00_00262570[];
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, float, int, void *);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0032F0B8(void *, int, int);
extern void func_PAL_L00_00408D50(void *, int, int);
extern int func_002E5DA0(int, int, void *, int);

void func_PAL_L00_00408978(char *arg, void *p) {
    char *st = *(char **)(arg + 0x68);
    float vec[4];
    struct Fx fx;
    struct Ent *e;
    float scale;
    int is2;
    int is3;
    char *pos = arg + 0x10;

    if (func_002761F8(p, pos, 0, arg, 0) == 0) {
        return;
    }
    if (D_L00_001BF200.hero != 0 && D_L00_001BF200.hero != D_L00_0018C0B0 &&
        (*(short *)(*(char **)(D_L00_001BF200.hero + 0x24) + 0x46) == 5 ||
         (*(u16 *)(D_L00_001BF200.hero + 0x34) & 0x4000) != 0)) {
        func_00282F20(vec, st, 1.0f);
        e = &D_L00_00262570[D_L00_00139588];
        scale = 1.0f;
        is2 = e->used != 0 && e->mode == 2;
        if (is2) {
            scale = 10.0f;
        }
        is3 = e->used != 0 && e->mode == 3;
        if (is3) {
            scale = 15.0f;
        }
        func_002A8C00(&fx, arg, scale, 0x210000, vec);
        fx.sub = 3;
        fx.kind = 5;
        fx.id = *(u16 *)(arg + 0xAA);
        func_002A8E20(D_L00_001BF200.hero, &fx);
        func_PAL_0032F0B8(D_L00_001BF200.hero, 0x4E, *(int *)(*(char **)(st + 0x20) + 0xB8));
        func_PAL_L00_00408D50(pos, 0xA, 1);
    }
    if (D_L00_001BF200.hero == 0) {
        func_PAL_L00_00408D50(arg + 0x10, 0xF, 0);
    }
    func_002E5DA0(7, 0, arg, 0xE79);
    arg[0x20] = 2;
}

