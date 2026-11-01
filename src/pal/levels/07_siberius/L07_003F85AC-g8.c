#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern char *func_0029EFD0(int id);
extern void func_002B37E8(void *, void *);
extern float func_002A7940(void);
extern void func_002833F0(void *, void *);
extern void func_00282F70(void *, void *, float);
extern float func_L00_0031CDD0(float *a, float *b, float *out, float d, float e);
extern void func_00283698(void *, void *);
extern float D_L07_001B0E30 __attribute__((sda));
extern float D_L07_001B0E34 __attribute__((sda));
extern float D_L07_001B0E38 __attribute__((sda));
typedef struct {
    char pad00[0x10];
    float pos[4];           
    char pad20[0x04];
    char *pClass;           
    char pad28[0x04];
    float scale;            
    char pad30[0x04];
    unsigned short flags;   
    char pad36[0x32];
    char *pVars;            
    char pad6C[0x54];
    float mtx[12];          
    float rot[4];           
} F43E0Moby;
typedef struct {
    float offset[4];        
    float vel[4];           
    char *owner;            
    char pad24[0x10];
    float x34;              
} F43E0Vars;

/* Spawn an object of class 0xE1D at POS with a random rotation and the class scale, then aim it
   at TARGET: velocity toward the target at the configured speed, with the vertical component of
   a ballistic arc under the configured gravity (both per 60 Hz frame). With an owner, the
   velocity and the offset from the owner are kept in the owner's frame. Returns the object. */
char *func_PAL_L07_003F8B18(char *a0, char *a1, char *a2, char *a3, float a4)
{
    F43E0Moby *obj = (F43E0Moby *)func_0029EFD0(0xE1D);

    if (obj != 0) {
        F43E0Vars *st;
        float speed, gravity;
        float buf[16];

        func_002B37E8(obj, a0);
        qcopy(obj->pos, a2);
        obj->rot[2] = func_002A7940();
        obj->rot[0] = func_002A7940();
        func_002833F0(obj->mtx, obj->rot);
        obj->flags |= 0x100;
        st = (F43E0Vars *)obj->pVars;
        obj->scale = *(float *)(obj->pClass + 0x24) * D_L07_001B0E38;
        speed = D_L07_001B0E34 * (0.020000001f);
        gravity = D_L07_001B0E30 * (0.00040000002f);
        st->owner = a1;
        func_00282CF0(st->vel, a3, obj->pos);
        func_00282F70(st->vel, st->vel, speed);
        st->vel[2] = func_L00_0031CDD0(obj->pos, (float *)a3, 0, speed, -gravity);
        st->vel[3] = gravity;
        st->x34 = a4;
        if (a1 != 0) {
            func_00283698(buf, a1 + 0xC0);
            func_00283098(st->vel, st->vel, buf);
            func_00282CF0(st->offset, obj->pos, a1 + 0x10);
            func_00283098(st->offset, st->offset, buf);
        }
    }
    return (char *)obj;
}

extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *D_L07_001B22DC __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern u32 D_L07_001B10C0 __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 func_002AA2E8(f32 *value, f32 target, f32 step);
extern void func_002A7750(u8 *a, u8 b, s32 c);
extern void func_0029F338(void *a);
extern f32 func_00283B98(f32 a, f32 b);
extern void func_L00_002E6CF0(void *a, void *b);
extern void func_L07_003F4C18(void *a, void *b, void *c);
extern s32 func_L01_003120A8(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern char func_L07_003F4CC0[];
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern u8 *func_L00_002D70A0(s32);
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 D_L07_001B17D4 __attribute__((sda));
extern f32 D_L07_001B17D8 __attribute__((sda));
extern u8 *D_L07_001B9250 __attribute__((nosda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_L07_001B31A9;
extern u8 D_00189E20[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern f32 func_00282E48(u8 *a, u8 *b);
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern u8 *D_L07_001C36C0[];

/* Advances the object's own state: three step kinds by the 0x20 flag, then the shared
   spin and the two sampled vectors. */
void func_PAL_L07_003F90C8(u8 *a0)
{
    u8 *s1 = a0;
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 v1 = *(u8 *)(a0 + 0x20);
    f32 v[4];
    f32 w[4];

    switch (v1) {
    case 0:
        {
            u32 n = *(u16 *)(s1 + 0x96) + 1;

            *(u16 *)(s1 + 0x96) = n;
            if ((u16)n == 1) {
                break;
            }
            func_002AA2E8((f32 *)(s2 + 0x24), 1.0f, D_L07_001B0E98 * (0.020000001f));
            if (1.0f <= *(f32 *)(s2 + 0x24)) {
                func_002A7750(s1, 1, -1);
            }
        }
        break;
    case 1:
        func_002AA2E8((f32 *)(s2 + 0x24), 0.0f, D_L07_001B0E9C * (0.020000001f));
        if (*(f32 *)(s2 + 0x24) <= 0.0f) {
            func_0029F338(s1);
            return;
        }
        break;
    }
    *(f32 *)(s2 + 0x28) = func_00283B98(*(f32 *)(s2 + 0x28), D_L07_001B0EA0 * 0.0003490659f);
    func_L00_002E6CF0(func_L07_003F4CC0, s1);
    if (0.333f < *(f32 *)(s2 + 0x24)) {
        func_L07_003F4C18(s1, v, w);
        func_L01_003120A8(*(u32 *)(s1 + 0xB8), v, w, 1, *(f32 *)(s2 + 0x2C), 1.0f, 0, 1, 0);
    }
}
