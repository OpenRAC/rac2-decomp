#include "common.h"

typedef unsigned int Quad8010 __attribute__((mode(TI)));

typedef struct {
    char pad[0x18];
    float z;
    char pad1c[4];
    u8 state;
    char pad21[15];
    u8 alpha;
    char pad31;
    u16 flags;
    char pad34[0x14];
    float speed;
    char pad4c[0x49];
    s8 sound;
    u16 timer;
    char pad98[0x60];
    float angle;
} Object8010;

typedef struct {
    int ids[4];
    int direction;
    float initialHeight;
    float stopFrame;
    int timer;
    int duration;
    int selected;
    int sound;
    float turnSpeed;
    float targetAngle;
} Private8010;

extern char *D_L04_001B24DC __attribute__((sda));
extern char D_L04_001AFFE0[];
extern unsigned char D_00188660[];
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_0029F530(void *);
extern float func_00283198(float);
extern float func_00283CE0(int);
/* Integer and FP parameters retain their order within each EE argument bank. */
extern void func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002833F0(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0026FEB8(void *);

void func_L04_003E8010(char *o)
{
    Object8010 *obj = (Object8010 *)o;
    Private8010 *p = *(Private8010 **)(o + 0x68);
    unsigned char v[16] __attribute__((aligned(16))),
        old[16] __attribute__((aligned(16))),
        delta[16] __attribute__((aligned(16))),
        rot[16] __attribute__((aligned(16)));

    switch (obj->state) {
    case 0: {
        float initialZ = obj->z;

        obj->alpha = 128;
        obj->flags = 128;
        p->initialHeight = initialZ;
        p->stopFrame = 30;
        p->selected = 2;
        p->sound = -1;
        p->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
        if (p->direction)
            p->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
        func_002A7470(o, 1, 0, 0);
        func_002A7750(o, 1, -1);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = D_L04_001B24DC + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                *(int *)(d + 0x5C) |= 1;
                ((Object8010 *)m)->alpha = 128;
                ((Object8010 *)m)->flags = 128;
            }
        }
        if (p->direction)
            func_002A7470(o, 2, 0, 0);
        obj->speed = 1.0f / 3;
        break;
    }
    case 1: {
        char *m;
        float frame;

        frame = func_0029F530(o);
        m = (char *)D_00188660 + p->sound * 0x70;
        if (*(char **)(m + 0x88) != o || !*(u8 *)(m + 0x74))
            p->sound = PlayMobySound(0, 4, o);
        if (!p->direction)
            func_002AAA00(o + 0xF8, p->targetAngle, &p->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        else
            func_002AAA00(o + 0xF8, p->targetAngle, &p->turnSpeed,
                         0.0001939255f, 0.0001939255f, 0.06981318444013596f, 0);
        euler_rotation_basis(o + 0xC0, o + 0xF0);
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = D_L04_001B24DC + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                /* old is a separate stack vector; subsequent accesses use m. */
                qcopy_nc(old, m + 0x10);
                func_0029FCC0(o, i, v);
                *(Quad8010 *)(m + 0x10) = *(Quad8010 *)v;
                *(Quad8010 *)rot = *(Quad8010 *)(m + 0xF0);
                if (p->direction)
                    *(float *)(m + 0xF8) = FastAddRotations(obj->angle, 0.00872664712369442f);
                FastVecSub(delta, m + 0x10, old);
                if (p->selected == i && p->direction)
                    func_002AD6F0(d + 0x20, delta, rot, m + 0xF0);
                else
                    func_002AD6F0(d + 0x20, delta, rot, rot);
            }
        }
        if (frame == p->stopFrame) {
            p->timer = p->duration;
            obj->speed = 0;
            p->stopFrame += 30;
            if (p->stopFrame >= 120)
                p->stopFrame = 0;
            func_002A7750(o, 2, -1);
            p->turnSpeed = 0;
        }
        break;
    }
    case 2: {
        {
            int i = p->sound;
            char *m;

            if (i != -1) {
                m = (char *)D_00188660 + i * 0x70;
                if (*(char **)(m + 0x88) == o && *(u8 *)(m + 0x74))
                    func_002E59F8(i);
            }
            p->sound = -1;
        }
        if (func_00282948(&p->timer)) {
            if (++p->selected >= 4) {
                STUB_printf(D_L04_001AFFE0);
                p->selected = 0;
            }
            p->targetAngle = FastAddRotations(obj->angle, 1.5707964897155762f);
            if (p->direction)
                p->targetAngle = fast_subtract_rotations(obj->angle, 1.5707964897155762f);
            func_002A7750(o, 1, -1);
            obj->z = p->initialHeight;
            obj->speed = 1.0f / 3;
        } else if (p->timer < 25) {
            obj->z = p->initialHeight;
            obj->z += -func_00283198(IntToFloat(p->timer) * 0.1256636083126068f) * 0.25f;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                char *m, *d;
                m = D_L04_001B24DC + (p->ids[i] << 8);
                d = *(char **)(m + 0x68);
                qcopy_nc(old, m + 0x10);
                func_0029FCC0(o, i, v);
                *(Quad8010 *)(m + 0x10) = *(Quad8010 *)v;
                FastVecSub(delta, m + 0x10, old);
                func_002AD6F0(d + 0x20, delta, m + 0xF0, m + 0xF0);
            }
        }
        break;
    }
    }
    if (obj->timer <= 0xFFFE)
        ++obj->timer;
}
