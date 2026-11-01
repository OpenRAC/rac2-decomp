#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x80]; Vec position; } PlayerView;
typedef struct {
    char pad0[0x20];
    char body[0x3C];
    int flags;
    Vec home;
    char pad70[0x10];
    int down;
    int timer;
    int sound;
    float travel;
    int startDown;
    float upperZ;
    float lowerZ;
    int active;
    float speed;
    int contact;
} Lift;
extern PlayerView D_00189E20;
typedef struct { char pad[0x74]; unsigned char active; char pad75[0x13]; void *owner; char pad8c[0x70-0x8c+0x70]; } SoundSlot;
extern struct { char pad[0x70]; } D_00188660[];
extern unsigned char D_0019B2E8[], D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
typedef struct { char pad[0x464]; unsigned char locked[1]; } Entry;
extern Entry D_L01_0021E4B0;
extern int func_L00_00324120(void *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_002A7750(void *, int, int);
extern float func_002AA548(float *, float *, float, float, float, float);
extern int func_002ACBC8(void *, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002B3868(void *);
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);

#define Z(o) (*(float *)((o) + 0x18))
#define W(o) (*(unsigned short *)((o) + 0xB2))
#define SLOT(id) ((SoundSlot *)&D_00188660[id])

void func_L01_003B9798(unsigned char *obj)
{
    Vec old, oldRot, delta;
    Lift *s = *(Lift **)(obj + 0x68);
    int id;
    unsigned char *p;
    int w;
    int v, v2;
    unsigned char *q;
    int w2;
    unsigned int u;

    qcopy(old, obj + 0x10);
    qcopy(oldRot, obj + 0xF0);
    switch (obj[0x20]) {
    case 0:
        s->active = 0;
        s->flags |= 1;
        qcopy(s->home, obj + 0x10);
        obj[0x20] = 1;
        if (s->startDown == 0) {
            s->upperZ = s->home[2];
            s->lowerZ = s->travel;
            s->down = 0;
        } else {
            s->down = 1;
            s->upperZ = s->travel;
            s->lowerZ = s->home[2];
        }
        s->timer = 0;
        s->sound = -1;
        break;
    case 1:
        if (func_L00_00324120(obj)) {
            s->active = 1;
            w = W(obj);
            if (w & 1) {
                p = &D_0019B4A8[((short)w >> 1) + (D_001A79F0 << 10)];
                u = *p;
                if (((u >> 4) & 7) != 7) {
                    *p = u + 0x10;
                }
            } else {
                p = &D_0019B4A8[((short)w >> 1) + (D_001A79F0 << 10)];
                u = *p;
                if ((u & 7) != 7) {
                    *p = u + 1;
                }
            }
            if (s->down == 0) {
                func_002A7750(obj, 3, -1);
                if (!func_002E59B0(obj, s->sound)) {
                    s->sound = func_002E5CF8(0, 4, obj);
                }
            } else {
                func_002A7750(obj, 2, -1);
                if (!func_002E59B0(obj, s->sound)) {
                    s->sound = func_002E5CF8(0, 4, obj);
                }
            }
        }
        if (func_00282C48(Z(obj) - D_00189E20.position[2]) > 3.0f && s->down == 0 && Z(obj) > D_00189E20.position[2]) {
            if (s->active != 1 && !(D_0019B2E8[obj[0xB0] + (D_001A79F0 << 4)] & 0x80)) {
                w2 = W(obj);
                if (D_L01_0021E4B0.locked[(short)w2] == 0) {
                    v = D_0019B4A8[((short)w2 >> 1) + (D_001A79F0 << 10)];
                    if (w2 & 1) {
                        if (((v >> 4) & 7) != 0) goto play;
                        goto second;
                    }
                    if ((v & 7) == 0) goto second;
                }
            }
play:
            if (!func_002E59B0(obj, s->sound)) {
                s->sound = func_002E5CF8(0, 4, obj);
            }
            func_002A7750(obj, 3, -1);
            break;
        }
second:
        if (func_00282C48(Z(obj) - D_00189E20.position[2]) > 3.0f && s->down == 1 && D_00189E20.position[2] > Z(obj)) {
            if (s->active != 1 && !(D_0019B2E8[obj[0xB0] + (D_001A79F0 << 4)] & 0x80)) {
                w2 = W(obj);
                if (D_L01_0021E4B0.locked[(short)w2] == 0) {
                    v2 = D_0019B4A8[((short)w2 >> 1) + (D_001A79F0 << 10)];
                    if (w2 & 1) {
                        if (((v2 >> 4) & 7) != 0) goto play2;
                        break;
                    }
                    if ((v2 & 7) == 0) break;
                }
            }
play2:
            if (!func_002E59B0(obj, s->sound)) {
                s->sound = func_002E5CF8(0, 4, obj);
            }
            func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        qcopy(delta, obj + 0x10);
        delta[2] = s->upperZ;
        if (func_00282E48(obj + 0x10, delta) > 0.04f) {
            func_002AA548((float *)(obj + 0x18), (float *)&s->speed, delta[2], 0.00194444449f, 0.00166666671f, 0.100000009f);
            s->timer++;
        } else if (!func_L00_00324120(obj)) {
            id = s->sound;
            s->down = 0;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                func_002E59F8(id);
            }
            s->sound = -1;
            func_002A7750(obj, 1, -1);
            qcopy(obj + 0x10, delta);
            s->timer = 0;
        } else {
            id = s->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                func_002E59F8(id);
            }
            s->sound = -1;
        }
        break;
    case 3:
        func_002B3868(obj);
        if (s->lowerZ < Z(obj)) {
            if (Z(obj) - D_00189E20.position[2] < 2.8f && Z(obj) > D_00189E20.position[2]) {
                if (func_002ACBC8((char *)&D_00189E20 + 0x80, s->contact) == 0) {
                    func_002AA548((float *)(obj + 0x18), (float *)&s->speed, s->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                    s->timer++;
                }
            } else {
                func_002AA548((float *)(obj + 0x18), (float *)&s->speed, s->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                s->timer++;
            }
        } else if (!func_L00_00324120(obj) && Z(obj) <= s->lowerZ) {
            id = s->sound;
            s->down = 1;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                func_002E59F8(id);
            }
            s->sound = -1;
            func_002A7750(obj, 1, -1);
            s->timer = 0;
        } else {
            id = s->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                func_002E59F8(id);
            }
            s->sound = -1;
        }
        break;
    }
    func_00282CF0(delta, obj + 0x10, old);
    func_002AD6F0(s->body, delta, oldRot, obj + 0xF0);
}
