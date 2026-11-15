#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern u8 *func_0037B440(s32 a0, s32 a1);
extern s32 func_00332AF8(s32 a0, s32 a1);
extern void func_00329960(u8 *a0, s32 a1, u8 *a2);
extern void func_003298C0(u8 *a0, s32 a1, u8 *a2);
extern void func_00306748(u8 *a0, u8 *a1, u8 *a2);
extern void func_003068F8(u8 *a0, u8 *a1, f32 f12);
extern void func_0037D210(u8 *a0);

/* Spawns a target object at a random point of the given object and gives it a facing. */
void feltzin_target_spawn_random(u8 *moby) {
    TI128 v[6];
    u8 *pw;
    u8 *px;
    u8 *spawned;
    s32 point_index;

    spawned = func_0037B440(0x10F5 /* moby class 4341 */, 1);
    *(TI128 *)&v[0] = 0;
    ((f32 *)&v[0])[2] = 1.0f;
    if (spawned == 0)
        return;
    point_index = func_00332AF8(0, 4);
    pw = (u8 *)&v[1];
    func_00329960(moby, point_index, pw);
    px = (u8 *)&v[2];
    func_003298C0(moby, point_index, px);
    qcopy(spawned + 0x10, pw);
    qcopy(spawned + 0xC0, px);
    func_00306748(spawned + 0xD0, spawned + 0xC0, (u8 *)&v[0]);
    func_003068F8(spawned + 0xD0, spawned + 0xD0, 1.0f);
    func_00306748(spawned + 0xE0, spawned + 0xD0, spawned + 0xC0);
    func_0037D210(spawned);
}
