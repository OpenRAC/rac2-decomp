#include "names.h"
/* func_PAL_L19_003ED868, the PAL copy of func_L19_003E9400: the same C, where rename func_00288E18 becomes func_PAL_00289730; scale D_001A7390[0]. */
#include "common.h"
extern u8 g_hero_position[];
extern u8 g_moby_group_flags[];
extern int g_current_map_index __attribute__((sda));
extern u8 g_mover_trigger_flag[1] __attribute__((sda));
extern unsigned int g_frame_counter[1] __attribute__((sda));
extern unsigned int g_linked_mover_start_time[1];
extern u8 *g_linked_object_table __attribute__((sda));
extern u8 *g_moby_l19_array __attribute__((sda));
extern float g_mover_current_value __attribute__((sda));
extern int g_mover_var_index;
extern int IsPointInCuboid(void *, int);
extern void moby_set_state(void *, int, int);
extern int func_PAL_00289730(int,int);
extern int flag_set_first_pending(void *);
extern float mat_fast_helper_a(float,float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int math_fast_float_d(void *);
extern int MemcardSave(int,int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
void func_PAL_L19_003ED868(u8 *obj)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *other, *os;
    if (I(s,0x38) > 0 && IsPointInCuboid(g_hero_position,I(s,0x38))) {
        g_mover_current_value = F((u8 *)((I(s,0x38) << 7) + (int)g_linked_object_table),0x38);
    } else {
        if (*(float *)((int)s + (g_mover_var_index << 2)) > 0.0f)
            g_mover_current_value = *(float *)((int)s + (g_mover_var_index << 2));
    }
    switch (obj[0x20]) {
    case 0:
        obj[0x30] = 0xFF;
        I(s,0x24) = (g_moby_group_flags[I(s,0x20) + g_current_map_index * 16] >> 7) ^ 1;
        moby_set_state(obj,1,-1);
        break;
    case 1:
        if (!g_mover_trigger_flag[0] && IsPointInCuboid(g_hero_position,I(s,0x10)) &&
            (((int)(g_frame_counter[0]) * 5 + 2) / 6) - g_linked_mover_start_time[0] > 3000)
            func_PAL_00289730(0xA12,0x69);
        if (g_moby_group_flags[I(s,0x20) + g_current_map_index * 16] & 0x80) {
            if (I(s,0x24)) moby_set_state(obj,2,-1);
        }
        break;
    case 2:
        other = g_moby_l19_array + (I(s,0x14) << 8);
        os = 0;
        if (other) os = *(u8 **)(other + 0x68);
        if (flag_set_first_pending(obj)) {
            I(s,0x24) = 0;
            if (I(s,0x18) < 0 || I(s,0x1C) < 0 || I(s,0x14) < 0) {
                moby_set_state(obj,1,-1);
                break;
            }
            other[0xBC] = 1;
            I(s,0x28) = I(s,0x2C) = I(os,0x2C);
        }
        qcopy_nc(start,(u8 *)((I(s,0x18) << 8) + (int)g_moby_l19_array) + 0x10);
        start[2] += F(s,0x30);
        qcopy_nc(end,(u8 *)((I(s,0x1C) << 8) + (int)g_moby_l19_array) + 0x10);
        end[2] += F(s,0x34);
        F(os,0x18) = mat_fast_helper_a(end[0]-start[0],end[1]-start[1]);
        FastVecSub(end,end,start);
        {
            float ratio = (float)I(s,0x2C) / (float)I(s,0x28);
            float t = math_fast_sin_or_cos_b((1.0f - ratio) * 3.1415927f + -1.5707964f);
            FastVecScale(end,end,t * 0.45f + 0.45f);
        }
        FastVecAdd(os,start,end);
        if (math_fast_float_d(s + 0x2C)) {
            MemcardSave(0,-1);
            moby_set_state(obj,1,-1);
        }
        break;
    }
}
