#include "include_asm.h"
#include "names.h"


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
extern struct Globals g_collision_result;
extern char *D_L00_0018C0B0;
extern u8 D_L00_00139588;
extern struct Ent g_weapon_l00_table[];
extern int CollLine(void *, void *, int, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, float, int, void *);
extern void QueueMobyImpact(void *, void *);
extern void func_PAL_0032F0B8(void *, int, int);
extern void func_PAL_L00_00408D50(void *, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);

void func_PAL_L00_00408978(char *arg, void *p) {
    char *st = *(char **)(arg + 0x68);
    float vec[4];
    struct Fx fx;
    struct Ent *e;
    float scale;
    int is2;
    int is3;
    char *pos = arg + 0x10;

    if (CollLine(p, pos, 0, arg, 0) == 0) {
        return;
    }
    if (g_collision_result.hero != 0 && g_collision_result.hero != D_L00_0018C0B0 &&
        (*(short *)(*(char **)(g_collision_result.hero + 0x24) + 0x46) == 5 ||
         (*(u16 *)(g_collision_result.hero + 0x34) & 0x4000) != 0)) {
        vec_scale_to_length(vec, st, 1.0f);
        e = &g_weapon_l00_table[D_L00_00139588];
        scale = 1.0f;
        is2 = e->used != 0 && e->mode == 2;
        if (is2) {
            scale = 10.0f;
        }
        is3 = e->used != 0 && e->mode == 3;
        if (is3) {
            scale = 15.0f;
        }
        make_hit_descriptor(&fx, arg, scale, 0x210000, vec);
        fx.sub = 3;
        fx.kind = 5;
        fx.id = *(u16 *)(arg + 0xAA);
        QueueMobyImpact(g_collision_result.hero, &fx);
        func_PAL_0032F0B8(g_collision_result.hero, 0x4E, *(int *)(*(char **)(st + 0x20) + 0xB8));
        func_PAL_L00_00408D50(pos, 0xA, 1);
    }
    if (g_collision_result.hero == 0) {
        func_PAL_L00_00408D50(arg + 0x10, 0xF, 0);
    }
    snd_play_from_class_bank(7, 0, arg, 0xE79);
    arg[0x20] = 2;
}

