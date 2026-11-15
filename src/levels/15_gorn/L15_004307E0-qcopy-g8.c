#include "names.h"
/* func_L15_004307E0: Gorn's cutscene controller. On the first frame it starts the scene and
   wakes every 0x1211 object, then, once the timer runs out, it builds the camera from the
   object D_L15_001B261C points at (a ray towards it, the distance halved or pulled to -32, a
   basis from the facing and the up vector) and later hands control back.

   The camera position is taken $gp-relative (an SDATA view) but its z is read and written
   absolutely (MACRO_ADDR), D_L15_00221E3C is NOT_SDA, and the basis w components are one
   chained `= 0.0f` in the order 0, 1, 2 (retail stores a float zero with swc1).

   func_0029B3E0 returns int, as its definition in src/game/0029AE78-save-g8.c does and as
   L00_002FC7A8-launch.c tests. With the value-returning call, local-alloc gives the counter
   decrement after it retail's registers (the table pointer in $v0, the counter in $v1); a
   void declaration swaps them. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; u8 *target; char pad1C[4]; Vector pos; } Hit;

extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B1520 __attribute__((sda));
extern int D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B15D0 __attribute__((sda));
extern int D_L15_001B15AC __attribute__((sda));
extern float D_L15_001B1540[4] SDATA(D_L15_001B1540);
/* Retail takes the camera position's address $gp-relative and reaches its z absolutely. */
extern float D_L15_001B1550[4] MACRO_ADDR;
extern float camera_pos[4] SDATA(D_L15_001B1550);
extern int D_L15_00221E3C NOT_SDA;
extern int D_L15_001B2148;
extern u8 *D_L15_001B261C;
extern Hit D_L15_001BFC00;

extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern void *level_find_object_by_class_id(int);
extern int group_count_alive(void *);
extern int math_fast_float_d(void *);
extern void effect_remove_family_mobys(void);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void ship_start_transition(void *, void *, int);
extern void snd_clamp_copy_volumes(void);
extern int MemcardSave(int, int);
extern void moby_set_flag_bit(void *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void gorn_finish_challenge_stage(void *, int);

/* Runs the Gorn cutscene stage: starts the scene, aims the camera at the target, then hands control back. */
void gorn_cutscene_update(u8 *moby)
{
    Vector step;
    Vector ahead;
    Vec up;
    Vector basis[3];
    u8 *vars = *(u8 **)(moby + 0x68);

    if (D_L15_001B1534 == 0) {
        u8 **list;
        int i, count;

        D_L15_00221E3C = 0;
        D_L15_001B1534 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        *(int *)(vars + 0x6C) = 30;
        list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 0xAA) == 0x1211 /* moby class 4625 */)
                entry_spawn_list_objects_with_flag(list[i], 1);
        }
    }
    if (group_count_alive(level_find_object_by_class_id(0x1211 /* moby class 4625 */)) != 0)
        return;
    if (D_L15_001B2148 < 6)
        return;
    if (D_L15_001B15BC == 0) {
        u8 *targetMoby;
        u8 *targetPos;
        float distance;

        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 60;
        effect_remove_family_mobys();
        targetMoby = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
        targetPos = targetMoby + 0x10;
        qcopy(camera_pos, targetPos);
        vec_scale_to_length(step, targetMoby + 0xC0, 196.0f);
        distance = 25.0f;
        FastVecAdd(ahead, targetPos, step);
        if (CollLine(targetPos, ahead, 0, targetMoby, 0) != 0) {
            Hit *hit = &D_L15_001BFC00;

            if (hit->target != 0 && *(short *)(hit->target + 0xAA) == 0x1211 /* moby class 4625 */)
                distance = fast_vec_dist(hit->pos, targetPos);
        }
        if (distance < 16.0f)
            distance = -32.0f;
        else
            distance = distance * 0.5f;
        vec_scale_to_length(step, targetMoby + 0xC0, distance);
        FastVecAdd(camera_pos, camera_pos, step);
        D_L15_001B1550[2] -= 16.0f;
        up.q = 0;
        up.f[2] = 1.0f;
        qcopy(basis[0], targetMoby + 0xC0);
        qcopy(basis[2], up.f);
        FastVecCross(basis[1], basis[0], basis[2]);
        basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
        mat_get_euler_angles(basis, D_L15_001B1540);
        ship_start_transition(camera_pos, D_L15_001B1540, 300);
        moby[0x20] = 3;
        D_L15_001B15BC = 1;
    } else if (D_L15_001B15D0 != 0) {
        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 10;
        D_L15_001B1520++;
        snd_clamp_copy_volumes();
        MemcardSave(0, -1);
        D_L15_001B1520--;
        moby_set_flag_bit(D_L15_001B261C + (*(int *)(vars + 0x28) << 8), 1);
        D_L15_001B15AC = 0;
        D_L15_001B15D0 = 0;
        hero_set_state_value_c(1);
        moby_mark_flag_and_append_to_list(0x10);
    } else if (math_fast_float_d(vars + 0x6C) != 0) {
        entry_init_all_registered();
        gorn_finish_challenge_stage(moby, 0);
    }
}
