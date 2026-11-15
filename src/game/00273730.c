#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern unsigned char *func_002AB220(void *);
extern void func_002B37E8(void *, void *);
extern void func_002AEC18(void *, unsigned int);
extern void func_002833F0(void *, void *);
extern void func_002A10E8(void *);
extern float func_00283198(float);
extern void func_002A7A00(void *, float, float);
extern float func_00282C10(float);
extern void func_0029F390(void *);
extern void func_002A05A8(void *);
extern void func_00273978(void *, int, int, void *, void *, float, unsigned char);
extern void func_00310C88(void);

/* Creates a camera object, inherits the parent's settings and initializes tracking. */
char *func_00273730(char *parent, int mode, int type, int index,
                  void *position, void *rotation, void *target,
                  unsigned char tag, float spread, float speed)
{
    float vector[4];
    char *obj;
    unsigned char *color;
    unsigned int packed = 0;
    obj = CreateMoby(type);
    color = GetMobyPrivateValue4(parent);
    if (color) {
        int green = (color[5] << 8) | (-2147483647 - 1);
        int blue = color[6] << 16;
        packed = blue | green | color[4];
    }
    if (obj) {
        InitChildObjectFromParent(obj, parent);
        if (packed)
            SetMobyLightColor(obj, packed);
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
        spread = FastSinOrCosB(spread * 0.00014544412260875106f);
        RandomDirectionVector(vector, spread, spread);
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
            func_002A05A8(obj);
        }
        InitCameraTracking(obj, mode, index, target, vector, speed, tag);
        if (*(unsigned short *)(obj + 0x7c) & 0x8000) {
            if (*(unsigned short *)(obj + 0x34) & 0x10)
                *(unsigned short *)(obj + 0x34) &= ~0x10;
        }
        *(void (**)(void))(obj + 0x64) = UpdateFadeOutMoby;
    }
    return obj;
}
