#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_002A8C28(char *, float, char *, int, float, float, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00277F48(void *, int, void *, void *, float);
extern void func_00282C88(void *);
extern void func_L13_00412748(float, char *, int, int, int, int, int, int, int, int, int);
extern void func_0029F338(char *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void ref_L13_0040D930_01(void *, char *);
extern void ref_L13_0040D930_00(void);
extern float D_L13_001B12CC __attribute__((sda));
typedef struct { char pad[0x18]; char *hit; int flags; Quad normal; } HitResult;
extern HitResult D_L13_001BFD00;
/* Updates the flying projectile moby of class 3751: it moves forward, damages what it hits, and disappears after 240 frames or on impact. */
void func_L13_0040D930(char *obj)
{
    struct { Quad end; char collision[0x30]; Quad scaled; char damage[0x30]; } v;
    char *s = *(char **)(obj + 0x68);
    (*(int *)(s + 0x24))++;
    if (*(int *)(s + 0x24) > 240) {
        SweepCollisionFromObject(obj, 0.6f, obj + 0x10, 0x10001, *(float *)(s + 0x14), 0.0f, 0, 1, 0);
        SetMobyState(obj, 1, -1);
    }
    switch ((unsigned char)obj[0x20]) {
    case 0:
        FastVecAdd(&v.end, obj + 0x10, s);
        make_hit_descriptor(v.collision, obj, 1, s, *(float *)(s + 0x14));
        *(unsigned short *)(v.collision + 0x1A) = *(unsigned short *)(obj + 0xAA);
        if (CollLine(obj + 0x10, &v.end, 0, obj, v.collision)) {
            if (D_L13_001BFD00.hit) {
                if (D_L13_001BFD00.hit != *(char **)(s + 0x10)) {
                    qcopy(&v.scaled, s);
                    FastVecScale(&v.scaled, &v.scaled, 2.0f);
                    ((float *)&v.scaled)[3] = 5627.9248046875f;
                    make_hit_descriptor(v.damage, obj, 0x10001, &v.scaled, *(float *)(s + 0x14));
                    v.damage[0x19] = 1;
                    *(unsigned short *)(v.damage + 0x1A) = *(unsigned short *)(obj + 0xAA);
                    v.damage[0x18] = 0;
                    ProcessCollisionHit(&D_L13_001BFD00.normal, 0, obj, v.damage, 0.3f);
                    SetMobyState(obj, 1, -1);
                    return;
                }
            } else {
                qcopy(&v.scaled, s);
                FastVecScale(&v.scaled, &v.scaled, 3.0f);
                ((float *)&v.scaled)[3] = 5627.9248046875f;
                make_hit_descriptor(v.damage, obj, 0x10001, &v.scaled, *(float *)(s + 0x14));
                v.damage[0x19] = 1;
                *(unsigned short *)(v.damage + 0x1A) = *(unsigned short *)(obj + 0xAA);
                v.damage[0x18] = 0;
                ProcessCollisionHit(&D_L13_001BFD00.normal, 0, obj, v.damage, 0.6f);
                SetMobyState(obj, 1, -1);
                return;
            }
        }
        qcopy(obj + 0x10, &v.end);
        FastVecScale(&v.scaled, s, -0.5f);
        ClearVector128(v.damage);
        break;
    case 1:
        SpawnFlashEffect(0.25f, obj + 0x10, 0, 25, 20, 20, 20, 0, 1, 1, 0);
        MarkMobySpawned(obj);
        return;
    }
    ApplyAxisRotationToQuaternion(obj + 0xE0, obj + 0xE0, obj + 0xD0, D_L13_001B12CC * 0.01745329424738884f);
    ApplyAxisRotationToQuaternion(obj + 0xC0, obj + 0xC0, obj + 0xD0, D_L13_001B12CC * 0.01745329424738884f);
    ref_L13_0040D930_01(ref_L13_0040D930_00, obj);
}
