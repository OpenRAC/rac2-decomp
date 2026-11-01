#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef union { TI128 q; float f[4]; } EffectVector;
struct CollisionFilter { Quad16 direction; int owner, mode; u16 unknown18, objectType; float radius; int active; };
extern char *D_L11_001C0D18 NOT_SDA;
extern int D_L11_001B1CE4 __attribute__((sda));
extern u32 D_L11_001B1CE0 __attribute__((sda));
extern int func_002A8C28(void *, float, float *, int, float, float, int, int, int);
extern void func_002A7750(u8 *, u8, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern int func_002761F8(void *, void *, int, void *, struct CollisionFilter *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, float, float, float, int);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, void *, float, float);
extern void func_0029F338(void *);
extern void func_L11_00450508(u8 *);
extern void func_L00_002E6EF8(void (*)(void *), void *);

void func_PAL_L11_00455B30(u8 *object) {
    EffectVector destination;
    struct CollisionFilter filter;
    EffectVector backward, light;
    char *data = *(char **)(object + 0x68);
    float size, growth, size2, growth2;
    *(int *)(data + 0x24) += 1;
    if (*(int *)(data + 0x24) > 240) {
        func_002A8C28(object, 0.6f, (float *)(object + 0x10), 0x10001, *(float *)(data + 0x14), 0.0f, 0, 1, 0);
        func_002A7750(object, 1, -1);
    }
    switch (object[0x20]) {
    case 0:
        func_00282CC0(&destination, object + 0x10, data);
        func_002A8C00((char *)&filter, (int)object, 1, *(float *)(data + 0x14), (Quad16 *)data);
        filter.objectType = *(u16 *)(object + 0xAA);
        if (func_002761F8(object + 0x10, &destination, 0, object, &filter) || func_00277258(object + 0x10, 0, object, 0.3f)) {
            if (!D_L11_001C0D18 || D_L11_001C0D18 != *(char **)(data + 0x10)) {
                func_002A8C28(object, 0.6f, (float *)(object + 0x10), 0x10001, *(float *)(data + 0x14), 0.0f, 0, 1, 0);
                func_002A7750(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, &destination);
        func_00282D30(&backward, data, -0.5f);
        if (D_L11_001B1CE4) {
            func_00282F20(&light, data, 0.5f);
            func_00282CC0(&light, object + 0x10, &light);
            size = func_002A7878(1.2f, 1.45f) * 210000.0f;
            growth = func_002A7878(0.1f, 0.2f);
            func_002C65A0(&light, &backward, 2, D_L11_001B1CE0, 3, 127, 47, size, growth * 210000.0f, 0.0f, 0);
            func_00282F20(&light, data, -0.03f);
            func_00282CC0(&light, object + 0x10, &light);
            size2 = func_002A7878(0.7f, 0.9f) * 210000.0f;
            growth2 = func_002A7878(0.1f, 0.3f);
            func_002C65A0(&light, &backward, 2, D_L11_001B1CE0, 7, 127, 47, size2, growth2 * 210000.0f, 0.0f, 0);
        }
        break;
    case 1:
        func_PAL_L00_003FB330(object + 0x10, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0.25f, 20.0f);
        func_0029F338(object);
        return;
    }
    func_L00_002E6EF8((void (*)(void *))func_L11_00450508, object);
}
