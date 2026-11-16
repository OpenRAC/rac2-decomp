#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x14];
    u8 *target;
    f32 f18;
    f32 f1C;
    f32 f20;
} FollowVars;
extern char g_hero_state[];
extern u32 g_pad_pressed_flags;
extern unsigned int stub_empty_2_pal(int);
extern unsigned int stub_empty_9_pal(int, int);
extern void stub_empty_13(int, int, float);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void gfx_register_world_draw_callback(void (*)(char *), char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern s32 swingshot_hook_spawn_pal(s32 arg0, f32 fparg0);
extern void gfx_draw_wavy_link_strip(char *);


