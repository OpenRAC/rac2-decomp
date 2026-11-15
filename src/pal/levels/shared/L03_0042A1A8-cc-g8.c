#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
typedef float f32;

/* The current level: read through $gp only from a branch delay slot, absolute elsewhere. */
extern s32 g_current_map_index __attribute__((section(".sdata")));

/* One done flag per slot. `sda` on an unsized array makes cc1 emit the `la` macro, so the
   `lui`/`addiu` pair stays together, as in retail. */
extern u8 D_001A7A28[] __attribute__((sda));

extern char g_hero_position[];

extern u8 D_001395D0 __attribute__((nosda));

extern unsigned short D_0018CFB8 __attribute__((nosda));

extern u8 *D_L03_001B1E70 __attribute__((sda));

extern u8 *D_L03_001B2A28 __attribute__((sda));

/* Four offsets of 16 bytes, addressed from $gp: declared as one float so cc1 keeps it small. */
extern f32 D_L03_001B1E80 __attribute__((sda));

extern f32 D_L03_001B1EC0 __attribute__((sda));

extern f32 D_L03_001B1EC4 __attribute__((sda));

extern s32 D_L03_001B1EC8 __attribute__((sda));

extern f32 D_L03_001B1ED0 __attribute__((sda));

extern f32 D_L03_001B1ED4[3] __attribute__((sda));

extern f32 D_L03_001B1EE0 __attribute__((sda));

extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(u8 *);
extern void vec_scale_to_length(u8 *, u8 *, f32);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern void FastVecSub(float *, u8 *, u8 *);
extern float fast_vec_dist(void *, void *);
extern void euler_rotation_basis(void *, void *);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void hud_queue_hint_message(int, int);
extern void func_PAL_L03_0042A5C8(u8 *);
extern void func_PAL_L03_0042A6B0(u8 *);

/* func_PAL_L03_0042A1A8, the PAL copy of func_L03_00424C40: the same C with the spin and speed
   constants scaled to 50 Hz, the particle lifetime as well, and its callees the PAL copies.
   The loop counts up over the table: reversed by loop.c, its counter and pointer are compiler
   pseudos, not user variables that lose their equivalence, so the hoisted divisor is the one
   left without a saved register and is rematerialised in the loop. */
/* A three-state object: state 0 arms it (and on level 5 finds the entity of class 0xFBF),
   state 1 spins its four angles and throws four particles each frame until the player (or that
   entity on level 5) comes near, state 2 marks its slot done and removes it. */
void func_PAL_L03_0042A1A8(u8 *e) {
    u8 *vars = *(u8 **)(e + 0x68);
    f32 mat[12];
    f32 dir[4];
    f32 pos[4];
    f32 (*src)[4];
    u8 *pos0;
    u8 *a;
    u8 *b;
    u8 *p;
    u8 *found;
    s32 n;
    s32 i;
    f32 d;

    switch (e[0x20]) {
    case 0:
        e[0x20] = 1;
        e[0xBC] = 0;
        *(f32 *)(e + 0x2C) = *(f32 *)(*(u8 **)(e + 0x24) + 0x24) * 1.1f;
        if (D_001A7A28[*(s32 *)vars] == 1) {
            moby_mark_spawned(e);
            return;
        }
        if (g_current_map_index == 5 && D_L03_001B1E70 == 0 && (p = D_L03_001B2A28) != 0) {
            s32 id = 0xFBF;     /* in a register: retail compares with `xor`, not `xori` */
            found = 0;
            do {
                if (*(short *)(p + 0xAA) == id)
                    found = p;
                p = *(u8 **)(p + 0x28);
            } while (p != 0);
            D_L03_001B1E70 = found;
        }
        func_PAL_L03_0042A5C8(e);
        return;
    case 1:
        /* Retail keeps the position in two registers (the first test's and a copy for the
           rest); with this unit's -fno-gcse the copy after the first call gives both. */
        a = e + 0x10;
        *(f32 *)(e + 0xF8) = FastAddRotations(*(f32 *)(e + 0xF8), 0.03f);
        d = fast_vec_dist(g_hero_position, a);
        b = a;
        if (d < 1.5f)
            e[0x20] = 2;
        if (g_current_map_index == 5 && D_L03_001B1E70 != 0) {
            if (fast_vec_dist(D_L03_001B1E70 + 0x10, b) < 3.0f)
                e[0x20] = 2;
        }
        pos0 = b;
        *(f32 *)(vars + 0x50) = FastAddRotations(*(f32 *)(vars + 0x50), D_L03_001B1ED0 * 0.0003490659f);
        *(f32 *)(vars + 0x54) = FastAddRotations(*(f32 *)(vars + 0x54), D_L03_001B1ED4[0] * 0.0003490659f);
        *(f32 *)(vars + 0x58) = FastAddRotations(*(f32 *)(vars + 0x58), D_L03_001B1ED4[1] * 0.0003490659f);
        *(f32 *)(vars + 0x5C) = FastAddRotations(*(f32 *)(vars + 0x5C), D_L03_001B1ED4[2] * 0.0003490659f);
        euler_rotation_basis(mat, vars + 0x50);
        src = (f32 (*)[4])&D_L03_001B1E80;
        for (i = 0; i < 4; i++) {
            n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            matrix_mul_vec3(pos, src[i], mat);
            vec_scale_to_length((u8 *)pos, (u8 *)pos, D_L03_001B1EC0);
            FastVecAdd((u8 *)pos, (u8 *)pos, pos0);
            FastVecSub(dir, pos0, (u8 *)pos);
            vec_scale_to_length((u8 *)dir, (u8 *)dir, D_L03_001B1EC4 * 0.020000001f);
            part_spawn_fading_drift(pos, dir, ((s32)(D_L03_001B1EC8) * 5 + 2) / 6, 0x804020, n, 0, 0x6F,
                          math_random_float_range(0.07f, 0.12f) * 210000.0f, 42000.0f, 0.0f, 6);
        }
        *(f32 *)(e + 0xF0) = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x5C)) * D_L03_001B1EE0;
        *(f32 *)(e + 0xF4) = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x5C)) * D_L03_001B1EE0;
        func_PAL_L03_0042A6B0(e);
        return;
    case 2:
        D_001A7A28[*(s32 *)vars] = 1;
        if (*(s32 *)vars == 0)
            D_001395D0 = 1;
        if (D_0018CFB8 == 0)
            hud_queue_hint_message(0xA31, 0x88);
        moby_mark_spawned(e);
        return;
    }
}
