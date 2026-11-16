#include "include_asm.h"
#include "common.h"
extern char *CreateMoby();
extern void moby_transform_joint_to_world();
extern void set_moby_color();
extern void func_002A0F48();
extern void anim_start_blended();
typedef int TI __attribute__((mode(TI)));

/* Creates the Swingshot hook moby at the Swingshot's joint, linked to its owner (PAL build). */
s32 swingshot_hook_spawn_pal(s32 swingshot, f32 length) {
    s32 hook;
    s32 hook_vars;

    hook = CreateMoby(0xD1);
    if (hook != 0) {
        hook_vars = (*(s32 *)((s8 *)(hook) + (0x68)));
        (*(f32 *)((s8 *)(hook_vars) + (4))) = length;
        (*(s32 *)((s8 *)(hook_vars) + (0))) = swingshot;
        (*(u8 *)((s8 *)(hook) + (0x30))) = 0xFF;
        (*(s16 *)((s8 *)(hook) + (0x32))) = 0xFF;
        (*(s8 *)((s8 *)(hook) + (0x31))) = 1;
        set_moby_color(hook, 0x80, 0x80, 0x80);
        moby_transform_joint_to_world(swingshot, 0, hook + 0x10);
        (*(TI *)((s8 *)(hook) + (0xC0))) = (*(TI *)((s8 *)(swingshot) + (0xC0)));
        (*(TI *)((s8 *)(hook) + (0xD0))) = (*(TI *)((s8 *)(swingshot) + (0xD0)));
        (*(TI *)((s8 *)(hook) + (0xE0))) = (*(TI *)((s8 *)(swingshot) + (0xE0)));
        if ((*(u8 *)((s8 *)(hook) + (0x43))) != 0) {
            anim_start_blended(hook, 0, 0, 0x8);
        }
        func_002A0F48(hook);
        (*(s8 *)((s8 *)(hook) + (0x20))) = 0;
        (*(u16 *)((s8 *)(hook) + (0x34))) = (*(u16 *)((s8 *)(hook) + (0x34))) | 4;
    }
    return hook;
}
