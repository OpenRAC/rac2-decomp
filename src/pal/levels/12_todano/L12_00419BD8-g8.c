#include "common.h"

/* func_PAL_L12_00419BD8, the PAL copy of func_L12_00414C60: the same C, with the timer
   period scaled to 50 Hz and the per-frame steps at 0.02 and 0.04. */

extern f32 D_L12_001B1810 __attribute__((sda));
extern s32 D_L12_001B1828 __attribute__((sda));
extern f32 D_L12_001B1814 __attribute__((sda));
extern f32 vec_distance_xy(void *, void *);
extern s32 FastDecTimer(void *);
extern s32 guard_is_line_of_sight_blocked(void *, s32, s32, s32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_spawn_aimed_effect(void *, void *, f32, void *);

typedef struct { char pad[0x2F0]; u8 *slots[2]; } SlotVars;

void func_PAL_L12_00419BD8(u8 *self)
{
    u8 *v = *(u8 **)(self + 0x68);
    s32 near = 1;
    s32 side, shift;
    u8 *h;
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    if (!(vec_distance_xy(self+0x10, *(u8 **)(v+0x200)+0x10) < D_L12_001B1814)) near=0;
    if (*(u8 **)(v+0x2F8) == 0) return;
    if (!FastDecTimer(v+0x2E4)) return;
    side = (*(u16 *)(self+0x96) / (((s32)D_L12_001B1828 * 5 + 2) / 6)) & 1;
    shift = side ? 5 : 4;
    if ((*(u16 *)(*(u8 **)(v+0x2F8)+0x7C) >> shift) & 1) {
        if (!guard_is_line_of_sight_blocked(self,1,0,*(u8 *)(v+0x30D)!=0)) return;
        h = ((SlotVars *)v)->slots[side];
        if (h && *(s16 *)(h+0xAA)==0xD66 && h[0x20]!=0xFE && h[0x20]!=0xFD) {
            *(u16 *)(v+0x2E4)=((s32)D_L12_001B1828 * 5 + 2) / 6;
            moby_transform_joint_to_world(((SlotVars *)v)->slots[side],0,a);
            FastVecSub(b,v+0x1F0,a);
            vec_scale_to_length(b,b,D_L12_001B1810 * 0.020000001f);
            if (!near && !v[0x30D]) {
                if (b[2] > 0.040000003f) b[2]=0.040000003f;
                else if (b[2] < -0.040000003f) b[2]=-0.040000003f;
            }
            vec_scale_to_length(b,b,D_L12_001B1810 * 0.020000001f);
            moby_spawn_aimed_effect(self,b,(f32)v[0x34],a);
        }
    } else *(u16 *)(v+0x2E4)=((s32)D_L12_001B1828 * 5 + 2) / 6;
}
