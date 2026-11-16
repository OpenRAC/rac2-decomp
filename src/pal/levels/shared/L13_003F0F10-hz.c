/* func_PAL_L13_003F0F10, the PAL copy of func_L13_003ECD48: the same C with the callees are PAL's
   func_PAL_002B1A50 and func_PAL_L00_003FB330. */
#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_OBJ_389848
typedef struct {
    char pad[0xAA];
    short key;          /* +0xAA */
} Obj_389848;
#endif

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(void *);

typedef struct {
    unsigned char pad0[0x20];
    float f20;
    unsigned char pad24[0x50 - 0x24];
    unsigned char sub50[0x11];
    unsigned char b61;
    unsigned char b62;
    unsigned char pad63[0x6A - 0x63];
    unsigned char b6A;
    unsigned char pad6B[0xA8 - 0x6B];
    float fA8;
} L13_CD48Vars;

extern void level_list_add_key(Obj_389848 *object);
/* Updates an enemy that explodes as soon as its health has run out (PAL). */
void enemy_update_explode_pal(unsigned char *moby)
{
    L13_CD48Vars *vars = *(L13_CD48Vars **)(moby + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float back[4] __attribute__((aligned(16)));

    if (moby[0x20] == 0) {
        level_list_add_key((Obj_389848 *)moby);
        moby[0x20] = 1;
    }
    vars->b6A = 2;
    vars->fA8 = 0.01f;
    vars->b61 = 0xFF;
    vars->b62 = 0xFF;
    if (moby_apply_damage_to_object_pal(moby, vars->sub50, 0) != 0) {
        PlayMobySound(0, 0, (char *)moby);
    }
    if (vars->f20 <= 0.0f) {
        qcopy(pos, moby + 0x10);
        vec_scale_to_length(back, moby + 0xD0, -2.0f);
        FastVecAdd(pos, back, pos);
        vec_scale_to_length(forward, moby + 0xC0, 1.5f);
        FastVecAdd(pos, forward, pos);
        SpawnExplosion_pal(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.75f, 20.0f, 1, 0, 0, 0);
        moby_mark_spawned(moby);
    }
}
