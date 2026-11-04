#include "include_asm.h"
#include "common.h"
extern int func_002ED688(unsigned char *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float D_L00_001AC588 __attribute__((sda));

typedef float Vec000[4] __attribute__((aligned(16)));
typedef struct {
    char pad0[0x30];
    float rot[4];   /* 0x30: Euler angles; x is eased and clamped here, y and z follow unk90 */
    float unk40[4]; /* 0x40 */
    char pad50[0x40];
    float unk90[4]; /* 0x90 */
    char padA0[0xA0];
    float unk140;   /* 0x140 */
} Obj002EE000;

extern int func_002EE6A8(unsigned char *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern void func_002A91F0(void *, void *);
extern void func_00283810(void *, void *, void *, float);
extern void func_00283958(void *, void *);
extern float D_001AC244 __attribute__((sda));
extern char *D_001B5390 NOT_SDA;

void func_002EE000(unsigned char *owner)
{
    Obj002EE000 *obj = (Obj002EE000 *)func_002ED688(owner);
    Vec000 old;
    Vec000 temp;
    float sign;
    float a;
    float b;

    if (!obj)
        return;
    if (func_002EE6A8(owner) != 8 && func_002EE6A8(owner) != 9) {
        qcopy(old, obj->rot);
        a = func_00282E20(obj->unk90);
        sign = 1.0f;
        obj->rot[1] = -func_00283248(a, obj->unk90[2]);
        obj->rot[2] = func_00283248(obj->unk90[0], obj->unk90[1]);
        if (func_00283BE0(obj->rot[2], old[2]) < 0.0f)
            sign = -1.0f;
        b = func_00283C80(old[2], obj->rot[2]);
        if (func_002EE6A8(owner) != 2 && func_002EE6A8(owner) != 12) {
            obj->rot[0] *= 0.98f;
            obj->rot[0] += (b * -sign) * (D_001AC244 * 1.4137166738510132f) * 8.0f;
            if (obj->rot[0] > 1.4137166738510132f)
                obj->rot[0] = 1.4137166738510132f;
            else if (obj->rot[0] < -1.4137166738510132f)
                obj->rot[0] = -1.4137166738510132f;
            func_002A91F0(temp, obj->rot);
            func_00283958(temp, owner + 0xC0);
        } else {
            func_002A91F0(temp, obj->rot);
            func_00283810(obj->unk40, obj->unk40, temp, 0.0125f);
            func_00283958(obj->unk40, owner + 0xC0);
        }
    } else {
        char *p = D_001B5390;

        func_00282F20(owner + 0xC0, p + 0x10, obj->unk140);
        func_00282F20(owner + 0xE0, p, -1.0f);
        func_00282F20(owner + 0xD0, p + 0x20, -1.0f);
    }
}

void func_002EE610(unsigned char *owner)
{
    char *data = (char *)func_002ED688(owner);
    if (data) {
        char *vector = data + 0x90;
        float length = func_00282DF0(vector);
        float limit = D_L00_001AC588;
        *(float *)(data + 0x124) = length;
        if (limit < length) {
            func_00282F20(vector, vector, limit);
            *(float *)(data + 0x124) = D_L00_001AC588;
        }
    }
}
