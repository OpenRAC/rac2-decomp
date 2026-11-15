/* func_US2_L15_00432488, the v2.00 copy of func_L15_004307E0: the same C, where the first pass
   also stops the owner's sound and clears its slot id, then deletes D_L15_001B1584 and
   D_L15_001B1588 when their field 0x34 is set. The last stage drops the D_L15_001B1520 count,
   func_L15_00432008 and func_0029B3E0, and calls func_002AD7B8 first instead of last. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; u8 *target; char pad1C[4]; Vector pos; } Hit;

extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B15D0 __attribute__((sda));
extern int D_L15_001B15AC __attribute__((sda));
extern float D_L15_001B1540[4] SDATA(D_L15_001B1540);
/* Retail takes the camera position's address $gp-relative and reaches its z absolutely. */
extern float D_L15_001B1550[4] MACRO_ADDR;
extern float camera_pos[4] SDATA(D_L15_001B1550);
extern int D_L15_00221E3C NOT_SDA;
extern u8 *D_L15_001B1584 __attribute__((sda));
extern u8 *D_L15_001B1588 __attribute__((sda));
extern u8 g_sound_state[];
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
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void moby_set_flag_bit(void *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void func_US2_L15_00432238(void *, int);

void func_US2_L15_00432488(u8 *self)
{
    Vector step;
    Vector ahead;
    Vec up;
    Vector basis[3];
    u8 *vars = *(u8 **)(self + 0x68);

    if (D_L15_001B1534 == 0) {
        u8 **list;
        int i, count;
        u8 *owner = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
        u8 *data = *(u8 **)(owner + 0x68);
        int id = *(int *)(data + 0x270);

        if (id != -1) {
            u8 *entry = g_sound_state + id * 0x70;

            if (*(u8 **)(entry + 0x88) == owner && entry[0x74] != 0)
                snd_stop_voice(id);
        }
        *(int *)(data + 0x270) = -1;
        *(int *)(data + 0x14) = 0;
        D_L15_00221E3C = 0;
        D_L15_001B1534 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        *(int *)(vars + 0x6C) = 30;
        list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 0xAA) == 0x1211)
                entry_spawn_list_objects_with_flag(list[i], 1);
        }
        if (D_L15_001B1584 != 0 && *(unsigned short *)(D_L15_001B1584 + 0x34) != 0) {
            moby_mark_spawned(D_L15_001B1584);
            D_L15_001B1584 = 0;
        }
        if (D_L15_001B1588 != 0 && *(unsigned short *)(D_L15_001B1588 + 0x34) != 0) {
            moby_mark_spawned(D_L15_001B1588);
            D_L15_001B1588 = 0;
        }
    }
    if (group_count_alive(level_find_object_by_class_id(0x1211)) != 0)
        return;
    if (D_L15_001B2148 < 6)
        return;
    if (D_L15_001B15BC == 0) {
        u8 *obj;
        u8 *pos;
        float dist;

        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 60;
        effect_remove_family_mobys();
        obj = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
        pos = obj + 0x10;
        qcopy(camera_pos, pos);
        vec_scale_to_length(step, obj + 0xC0, 196.0f);
        dist = 25.0f;
        FastVecAdd(ahead, pos, step);
        if (CollLine(pos, ahead, 0, obj, 0) != 0) {
            Hit *hit = &D_L15_001BFC00;

            if (hit->target != 0 && *(short *)(hit->target + 0xAA) == 0x1211)
                dist = fast_vec_dist(hit->pos, pos);
        }
        if (dist < 16.0f)
            dist = -32.0f;
        else
            dist = dist * 0.5f;
        vec_scale_to_length(step, obj + 0xC0, dist);
        FastVecAdd(camera_pos, camera_pos, step);
        D_L15_001B1550[2] -= 16.0f;
        up.q = 0;
        up.f[2] = 1.0f;
        qcopy(basis[0], obj + 0xC0);
        qcopy(basis[2], up.f);
        FastVecCross(basis[1], basis[0], basis[2]);
        basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
        mat_get_euler_angles(basis, D_L15_001B1540);
        ship_start_transition(camera_pos, D_L15_001B1540, 300);
        self[0x20] = 3;
        D_L15_001B15BC = 1;
    } else if (D_L15_001B15D0 != 0) {
        if (math_fast_float_d(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 10;
        moby_mark_flag_and_append_to_list(0x10);
        moby_set_flag_bit(D_L15_001B261C + (*(int *)(vars + 0x28) << 8), 1);
        D_L15_001B15AC = 0;
        D_L15_001B15D0 = 0;
        hero_set_state_value_c(1);
    } else if (math_fast_float_d(vars + 0x6C) != 0) {
        entry_init_all_registered();
        func_US2_L15_00432238(self, 0);
    }
}
