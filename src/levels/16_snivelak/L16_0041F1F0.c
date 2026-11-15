#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern char *CreateMoby(s32);
extern void moby_init_child_from_parent(char *, s32);
extern void vec_random_direction(char *, f32, f32);
extern void euler_rotation_basis(char *, char *);
extern f32 math_random_signed_float_range(f32, f32);
extern void vec_set_direction_with_complement(char *, char *, f32);
extern void moby_set_light_color(char *, u32);
extern void moby_set_state(char *, s32, s32);
typedef int quad __attribute__((mode(TI)));

/* Creates a spinning fragment and initializes its lifetime and velocity. */
char *part_spawn_spinning_fragment(s32 owner, char *position, char *velocity, s32 kind, f32 speed, f32 life) {
    char *obj = CreateMoby(0x12BE);
    char *st;
    if (obj) {
        moby_init_child_from_parent(obj, owner);
        *(quad *)(obj + 0x10) = *(quad *)position;
        vec_random_direction(obj + 0xF0, -3.141592741012573f, 3.141592741012573f);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        st = *(char **)(obj + 0x68);
        *(u16 *)(obj + 0x34) |= 0x100;
        vec_random_direction(st + 0x10, 1.0f, 1.0f);
        vec_set_direction_with_complement(st + 0x10, st + 0x10, math_random_signed_float_range(180.0f, 360.0f) * 0.01745329424738884f);
        *(quad *)st = *(quad *)velocity;
        *(f32 *)(st + 0x24) = speed;
        *(s32 *)(st + 0x20) = kind;
        *(f32 *)(st + 0x28) = life;
        *(f32 *)(obj + 0x2C) = *(f32 *)(*(char **)(obj + 0x24) + 0x24) * 0.2f;
        moby_set_light_color(obj, 0x800000C0);
        moby_set_state(obj, 0, -1);
    }
    return obj;
}
