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

/* Updates a lift platform: waits for the player, then rides up or down between two heights with sound. */
void func_L01_003B9798(unsigned char *obj)
{
    Vec old, oldRot, delta;
    Lift *lift = *(Lift **)(obj + 0x68);
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
        lift->active = 0;
        lift->flags |= 1;
        qcopy(lift->home, obj + 0x10);
        obj[0x20] = 1;
        if (lift->startDown == 0) {
            lift->upperZ = lift->home[2];
            lift->lowerZ = lift->travel;
            lift->down = 0;
        } else {
            lift->down = 1;
            lift->upperZ = lift->travel;
            lift->lowerZ = lift->home[2];
        }
        lift->timer = 0;
        lift->sound = -1;
        break;
    case 1:
        if (IsCurrentSelectedId(obj)) {
            lift->active = 1;
            w = W(obj);
            if (w & 1) {
                p = &D_0019B4A8[((short)w >> 1) + (gCurrentMapIndex << 10)];
                u = *p;
                if (((u >> 4) & 7) != 7) {
                    *p = u + 0x10;
                }
            } else {
                p = &D_0019B4A8[((short)w >> 1) + (gCurrentMapIndex << 10)];
                u = *p;
                if ((u & 7) != 7) {
                    *p = u + 1;
                }
            }
            if (lift->down == 0) {
                SetMobyState(obj, 3, -1);
                if (!IsVoicePlayingForOwner(obj, lift->sound)) {
                    lift->sound = PlayMobySound(0, 4, obj);
                }
            } else {
                SetMobyState(obj, 2, -1);
                if (!IsVoicePlayingForOwner(obj, lift->sound)) {
                    lift->sound = PlayMobySound(0, 4, obj);
                }
            }
        }
        if (FloatAbs(Z(obj) - gHeroState.position[2]) > 3.0f && lift->down == 0 && Z(obj) > gHeroState.position[2]) {
            if (lift->active != 1 && !(D_0019B2E8[obj[0xB0] + (gCurrentMapIndex << 4)] & 0x80)) {
                w2 = W(obj);
                if (D_L01_0021E4B0.locked[(short)w2] == 0) {
                    v = D_0019B4A8[((short)w2 >> 1) + (gCurrentMapIndex << 10)];
                    if (w2 & 1) {
                        if (((v >> 4) & 7) != 0) goto play;
                        goto second;
                    }
                    if ((v & 7) == 0) goto second;
                }
            }
play:
            if (!IsVoicePlayingForOwner(obj, lift->sound)) {
                lift->sound = PlayMobySound(0, 4, obj);
            }
            SetMobyState(obj, 3, -1);
            break;
        }
second:
        if (FloatAbs(Z(obj) - gHeroState.position[2]) > 3.0f && lift->down == 1 && gHeroState.position[2] > Z(obj)) {
            if (lift->active != 1 && !(D_0019B2E8[obj[0xB0] + (gCurrentMapIndex << 4)] & 0x80)) {
                w2 = W(obj);
                if (D_L01_0021E4B0.locked[(short)w2] == 0) {
                    v2 = D_0019B4A8[((short)w2 >> 1) + (gCurrentMapIndex << 10)];
                    if (w2 & 1) {
                        if (((v2 >> 4) & 7) != 0) goto play2;
                        break;
                    }
                    if ((v2 & 7) == 0) break;
                }
            }
play2:
            if (!IsVoicePlayingForOwner(obj, lift->sound)) {
                lift->sound = PlayMobySound(0, 4, obj);
            }
            SetMobyState(obj, 2, -1);
        }
        break;
    case 2:
        qcopy(delta, obj + 0x10);
        delta[2] = lift->upperZ;
        if (fast_vec_dist(obj + 0x10, delta) > 0.04f) {
            StepValueTowardTarget((float *)(obj + 0x18), (float *)&lift->speed, delta[2], 0.00194444449f, 0.00166666671f, 0.100000009f);
            lift->timer++;
        } else if (!IsCurrentSelectedId(obj)) {
            id = lift->sound;
            lift->down = 0;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                StopSoundVoice(id);
            }
            lift->sound = -1;
            SetMobyState(obj, 1, -1);
            qcopy(obj + 0x10, delta);
            lift->timer = 0;
        } else {
            id = lift->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                StopSoundVoice(id);
            }
            lift->sound = -1;
        }
        break;
    case 3:
        SetFirstPendingFlag(obj);
        if (lift->lowerZ < Z(obj)) {
            if (Z(obj) - gHeroState.position[2] < 2.8f && Z(obj) > gHeroState.position[2]) {
                if (IsPointInCuboid((char *)&gHeroState + 0x80, lift->contact) == 0) {
                    StepValueTowardTarget((float *)(obj + 0x18), (float *)&lift->speed, lift->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                    lift->timer++;
                }
            } else {
                StepValueTowardTarget((float *)(obj + 0x18), (float *)&lift->speed, lift->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                lift->timer++;
            }
        } else if (!IsCurrentSelectedId(obj) && Z(obj) <= lift->lowerZ) {
            id = lift->sound;
            lift->down = 1;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                StopSoundVoice(id);
            }
            lift->sound = -1;
            SetMobyState(obj, 1, -1);
            lift->timer = 0;
        } else {
            id = lift->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                StopSoundVoice(id);
            }
            lift->sound = -1;
        }
        break;
    }
    FastVecSub(delta, obj + 0x10, old);
    CombineTransformsAndStore(lift->body, delta, oldRot, obj + 0xF0);
}
