#include "common.h"

extern char *func_3113F0(s32);
extern void func_32AA20(char *, char *);
extern f32 func_2EF670(f32, f32);
extern f32 func_2EF110(f32 *);
extern f32 g_trail_projectile_scale __attribute__((sda));

/* Creates a moby of class 2562 at the given spot, pointing along the given direction, and returns it (or 0 if none was made). */
char *trail_projectile_spawn(char *parent, char *position, f32 *direction, s32 lifetime)
{
    char *new_moby = func_3113F0(0xA02 /* moby class 2562 */);
    char *vars;

    if (new_moby != 0) {
        vars = *(char **)(new_moby + 0x68);
        func_32AA20(new_moby, parent);
        qcopy(new_moby + 0x10, position);
        qcopy(vars, direction);
        *(f32 *)(new_moby + 0xF8) = func_2EF670(direction[0], direction[1]);
        {
            f32 horizontal_length = func_2EF110(direction);
            f32 angle = -func_2EF670(horizontal_length, direction[2]);
            f32 scale = g_trail_projectile_scale;

            *(f32 *)(new_moby + 0xF4) = angle;
            *(s32 *)(vars + 0x30) = 0x78;
            *(s32 *)(vars + 0x38) = lifetime;
            *(f32 *)(new_moby + 0x2C) = *(f32 *)(*(u32 *)(new_moby + 0x24) + 0x24)
                * scale;
        }
    }
    return new_moby;
}
