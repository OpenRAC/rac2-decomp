#include "names.h"
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

extern s32 func_31D1D8(s32 size);
extern f32 func_3279B8(void);
extern s32 func_3AE870(void *a0, s32 a1);
extern void func_2B71F0(void *a0);
extern void func_31D540(void *a0);
extern u8 D_L08_001B14F0[];

typedef int V4 __attribute__((mode(TI)));

/* Creates a new object (moby class 3704) at a position with a start velocity and a random spin;
   returns it, or 0 if its first setup step fails. */
s32 moby_spawn_spinning_object(void *owner, void *startPos, void *startVel, f32 turnSpeed, f32 moveSpeed)
{
    u8 *moby;
    u8 *position;
    u8 *vars;
    f32 spin;
    s32 result;

    moby = (u8 *)func_31D1D8(0xE78 /* moby class 3704 */);
    if (moby != 0) {
        vars = *(u8 **)(moby + 0x68);
        position = moby + 0x10;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0xBC) = 0;
        *(u8 *)(moby + 0x95) = 0;
        *(u8 *)(moby + 0x20) = 0;
        *(u32 *)(vars + 0x18) = (u32)owner;
        *(V4 *)position = *(V4 *)startPos;
        *(V4 *)vars = *(V4 *)startVel;
        *(f32 *)(vars + 0x14) = turnSpeed * 0.0002908882452175021f;
        *(f32 *)(vars + 0x10) = moveSpeed * 0.00027777778450399637f;
        spin = func_3279B8();
        *(f32 *)(moby + 0xF0) = spin;
        spin = func_3279B8();
        *(f32 *)(moby + 0xF4) = spin;
        spin = func_3279B8();
        *(f32 *)(moby + 0xF8) = spin;
        result = func_3AE870(position, 0);
        *(u32 *)(vars + 0x1C) = result;
        if (result == 0) {
            func_2B71F0(D_L08_001B14F0);
            func_31D540(moby);
            moby = 0;
        }
    }
    return (s32)moby;
}
