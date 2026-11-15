#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern char *moby_get_private_value_4(void *);
extern void moby_init_child_from_parent(void *, void *);
extern void moby_set_light_color(void *, unsigned int);
extern void euler_rotation_basis(void *, void *);
extern void func_002A10E8(void *);
extern float math_fast_sin_or_cos_b(float);
extern void vec_random_direction(void *, float, float);
extern float square_root(float);
extern void update_moby_animation_state(void *);
extern void func_PAL_002A0F68(void *);
extern void func_PAL_00273818(void *, int, int, void *, void *, float, unsigned char);
extern void func_PAL_003120C0(void);

/* Creates a camera object, inherits the parent's settings and initializes tracking. */
char *func_PAL_002735D0(char *parent, int mode, int type, int index,
                  void *position, void *rotation, void *target,
                  unsigned char tag, float spread, float speed)
{
    float vector[4];
    char *obj;
    unsigned char *color;
    unsigned int packed = 0;
    obj = CreateMoby(type);
    color = moby_get_private_value_4(parent);
    if (color) {
        int green = (color[5] << 8) | (-2147483647 - 1);
        int blue = color[6] << 16;
        packed = blue | green | color[4];
    }
    if (obj) {
        moby_init_child_from_parent(obj, parent);
        if (packed)
            moby_set_light_color(obj, packed);
        *(Quad *)(obj + 0x10) = *(Quad *)position;
        {
            void *orientation = obj + 0xf0;
            qcopy(orientation, rotation);
            euler_rotation_basis(obj + 0xc0, orientation);
        }
        if (parent) {
            *(float *)(obj + 0x2c) =
                *(float *)(*(char **)(obj + 0x24) + 0x24) *
                (*(float *)(parent + 0x2c) /
                 *(float *)(*(char **)(parent + 0x24) + 0x24));
        }
        func_002A10E8(obj);
        *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x100) & ~0x20;
        if (parent && (*(unsigned short *)(parent + 0x34) & 0x800))
            *(unsigned short *)(obj + 0x34) |= 0x800;
        *(int *)(obj + 0x98) = 0;
        *(char **)(*(char **)(obj + 0x68) + 0x54) = parent;
        spread = math_fast_sin_or_cos_b(spread * 0.00017453295f);
        vec_random_direction(vector, spread, spread);
        spread = spread * spread;
        vector[3] = square_root(1.0f - spread);
        if (mode == 1) {
            if (parent) {
                obj[0x42] = parent[0x43];
                obj[0x43] = parent[0x43];
            }
            update_moby_animation_state(obj);
            *(int *)(obj + 0x48) = 0;
            *(int *)(obj + 0x44) = 0;
            func_PAL_002A0F68(obj);
        }
        func_PAL_00273818(obj, mode, index, target, vector, speed, tag);
        if (*(unsigned short *)(obj + 0x7c) & 0x8000) {
            if (*(unsigned short *)(obj + 0x34) & 0x10)
                *(unsigned short *)(obj + 0x34) &= ~0x10;
        }
        *(void (**)(void))(obj + 0x64) = func_PAL_003120C0;
    }
    return obj;
}
