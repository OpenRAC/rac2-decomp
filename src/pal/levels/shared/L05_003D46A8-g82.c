#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuad __attribute__((mode(TI)));
typedef union {
    ProjectileQuad q;
    float f[4];
} ProjectileVector;
extern float D_L05_001AFC28 __attribute__((sda));
extern float D_L05_001AFC30 __attribute__((sda));
extern float D_L05_001AFC4C __attribute__((sda));
extern float D_L05_001AFC50 __attribute__((sda));
extern char D_L05_001BFB30[], D_L05_001BFB20[];
extern u8 *D_L05_001FF240[] NOT_SDA;
extern char *func_002ED688(void *);
extern int func_00283CF0(float);
extern float func_00282DF0(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern int func_00282948(void *);
extern int func_00278E78(void);
extern int func_00277258(void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L05_003D1058(void *,void *,void *,void *,float,float,float);
extern void func_PAL_L05_003D50B0(void *,void *,void *);
extern void func_002E5DA0(int,int,void *,int);
extern void func_0029F338(void *);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern char *func_002BD8B0(void *,void *,int,int,int,int,float);

/* Steers the projectile, tests its lifetime and collisions, and emits its trail. */
void func_PAL_L05_003D4868(char *obj)
{
    ProjectileVector old, temp, delta, velocity;
    char *data = *(char **)(obj+0x68);
    int collision, i;
    float length;
    qcopy(&old, obj + 0x10);
    if (*(char **)(data+0x10) && *(int *)(func_002ED688(*(char **)(data+0x10))+0x110)==1) {
        if (*(int *)(data+0x18)<func_00283CF0(1.0f / *(float *)(data+0x1c))-3) {
            length=func_00282DF0(data);
            func_00282CF0(data,*(char **)(data+0x10)+0x10,obj+0x10);
            func_00282F20(data,data,length);
        } else {
            float turn = D_L05_001AFC28;
            if (*(int *)(data+0x24)) {
                func_00282CF0(&temp, *(char **)(data + 0x10) + 0x10, obj + 0x10);
                length = func_00282DF0(data);
                func_00282F20(data, &temp, length);
            } else {
                func_L05_003D1058(obj + 0x10, data, *(char **)(data + 0x10),
                                   data + 0x14, turn, D_L05_001AFC30, 0.0f);
            }
        }
        temp.q = 0;
        temp.f[2] = 1.0f;
        func_00282F20(obj + 0xC0, data, 1.0f);
        func_00282DD8(obj + 0xD0, obj + 0xC0, &temp);
        func_00282F20(obj + 0xD0, obj + 0xD0, 1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    func_00282CC0(obj+0x10,obj+0x10,data);
    if (*(int *)(data+0x24)) {
        *(float *)(obj+0x2c)+=0.025f;
        if (*(float *)(obj+0x2c)>*(float *)(*(char **)(obj+0x24)+0x24)*0.75f)
            *(float *)(obj+0x2c)=*(float *)(*(char **)(obj+0x24)+0x24)*0.75f;
    } else {
        *(float *)(obj+0x2c)+=0.05f;
        if (*(float *)(obj+0x2c)>*(float *)(*(char **)(obj+0x24)+0x24))
            *(float *)(obj+0x2c)=*(float *)(*(char **)(obj+0x24)+0x24);
    }
    if (func_00282948(data+0x18)) goto destroy;
    {
        if (*(float *)(obj+0x10)<2.0f || *(float *)(obj+0x10)>1021.0f ||
            *(float *)(obj+0x14)<2.0f || *(float *)(obj+0x14)>1021.0f ||
            *(float *)(obj+0x18)<2.0f || *(float *)(obj+0x18)>1021.0f) goto destroy;
        if (func_00278E78()!=6) {
            collision = 0;
            if (func_00277258(obj+0x10,16,*(void **)(data+0x20),*(int *)(data+0x24)?D_L05_001AFC50:D_L05_001AFC4C)) {
                collision = 1;
                qcopy(obj + 0x10, D_L05_001BFB30);
            }
            if (collision || func_002761F8(&old,obj+0x10,16,*(void **)(data+0x20),0)) goto impact;
        }
    }
    goto emit;
impact:
    {
        func_PAL_L05_003D50B0(obj,data,obj+0x10);
        func_002E5DA0(7,0,obj,0xfbf);
        qcopy(obj+0x10,D_L05_001BFB20);
destroy:
        func_0029F338(obj);
        return;
    }
emit:
    qcopy(&temp,&old);
    func_00282CF0(&delta,obj+0x10,&old);
    func_00282D30(&delta,&delta,0.3330000042915344f);
    for (i=3;i>=0;i--) {
        float a, b;
        char *effect;
        func_00282CC0(&temp,&temp,&delta);
        a = func_002A7940();
        b = func_002A7940();
        func_002AF000(&velocity,0.015000001f,a,b);
        if (*(int *)(data+0x24)) {
            effect=func_002BD8B0(&temp,&velocity,0x4fff0040,0x1fff0040,8,1,30000.0f);
            if (effect)
                effect[2] = D_L05_001FF240[97][7];
            effect=func_002BD8B0(&temp,&velocity,0x4fff2040,0x1fff2040,8,1,15000.0f);
        } else {
            effect=func_002BD8B0(&temp,&velocity,0x4f00ffff,0x1f00ffff,8,1,30000.0f);
            if (effect)
                effect[2] = D_L05_001FF240[97][7];
            effect=func_002BD8B0(&temp,&velocity,0x4f20ffff,0x1f20ffff,8,1,15000.0f);
        }
        if (effect)
            effect[2] = D_L05_001FF240[97][7];
    }
}
