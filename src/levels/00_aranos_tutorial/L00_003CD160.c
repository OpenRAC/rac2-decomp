#include "common.h"

/* -frac2-zero-ti-por: the clear of frame.offset stays por + sq at 0($sp).
 * -g: the nop pair before the div.s of the angle step.
 */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;

extern char D_00189E20[];
#define D_00189EA0 (*(Vec *)(D_00189E20 + 0x80))
#define D_0018C0B0 (*(char **)(D_00189E20 + 0x2290))

typedef struct {
    unsigned char pad[4];
    unsigned char active;
    unsigned char gap[0x13];
    char *object;
    unsigned char tail[0x54];
} SoundSlot;

extern SoundSlot D_00188660[];
extern Vec D_L00_001BF220;
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(int *);
extern int func_002ACBC8(void *, int);
extern void func_L00_003CD658(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002E59B0(void *, int);
extern int func_L00_0035F5A0(int, int, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(void *, float, float, float);
/* The FP arguments travel in their own bank: declaring the last integer after them keeps its setup late. */
extern void *func_002C2210(void *, int, int, int, int, void *, float, float, float, int);
extern void func_002E59F8(int);

/* Moves a ring of light along its heading and resets it after a while, and sprays sparks when the player is close. */
void func_L00_003CD160(unsigned char *obj) {
    struct {
        Vec offset, direction, rotated, position;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *p;
    int i, handle, sign;
    int particle_count;
    char *camera;
    SoundSlot *sound;
    float angle, step, size, yaw, pitch, speed;

    if ((unsigned char)obj[0x20] == 0) {
        *(float *)(obj + 0x18) += 1.5f;
        *(int *)(ctx + 0x200) = 0;
        qcopy(ctx + 0x210, obj + 0x10);
        *(int *)(ctx + 0x204) = 0;
        frame.offset.q = 0;
        frame.offset.f[3] = 1.0f;
        frame.offset.f[2] = 3.0f;
        frame.direction.f[0] = FastSinOrCosA(*(float *)(obj + 0xF8));
        frame.direction.f[1] = FastSinOrCosB(*(float *)(obj + 0xF8));
        angle = 0.0f;
        frame.direction.f[3] = 1.0f;
        frame.direction.f[2] = angle;
        step = 6.283186f / (IntToFloat(9) - 1.0f);
        p = ctx;
        i = 8;
        do {
            BuildAxisAngleQuaternion(&frame.rotated, &frame.direction, angle);
            angle += step;
            --i;
            RotateVectorByQuaternion(p, &frame.offset, &frame.rotated);
            FastVecAdd(p, p, obj + 0x10);
            *(float *)(p + 0xC) = 0.6f;
            p += 0x10;
        } while (i >= 0);
        obj[0x20] = 1;
    }
    if ((unsigned char)obj[0x20] == 1 && FastFloatHelperD((int *)(ctx + 0x208))) {
        obj[0x20] = 2;
    }
    if ((unsigned char)obj[0x20] == 2) {
        frame.offset.f[0] = FastSinOrCosA(*(float *)(obj + 0xF8)) * 0.083333336f;
        frame.offset.f[1] = FastSinOrCosB(*(float *)(obj + 0xF8)) * 0.083333336f;
        frame.offset.f[2] = 0.0f;
        FastVecAdd(obj + 0x10, &frame.offset, obj + 0x10);
        if (++*(int *)(ctx + 0x204) > 0x207) {
            *(int *)(ctx + 0x204) = 0;
            qcopy(obj + 0x10, ctx + 0x210);
        }
        if (IsPointInCuboid(&gHeroPosition, *(int *)(ctx + 0x220))) {
            AddDrawCallbackToList1(DrawScrollingRings, obj);
        }
    }
    camera = (char *)&gHeroPosition;
    if (IsPointInCuboid(camera, *(int *)(ctx + 0x20C))) {
        qcopy(&frame.offset, &gHeroPosition);
        frame.offset.f[2] += 0.75f;
        camera -= 0x80;
        if (TestPointAgainstCollision(&frame.offset, 2, *(char **)(camera + 0x2290), 0.5f)) {
            if (!IsVoicePlayingForOwner(gHeroMoby_0018C0B0, *(int *)(ctx + 0x224))) {
                *(int *)(ctx + 0x224) = StartEffectInSlot(0x18, 4, gHeroMoby_0018C0B0);
            }
            qcopy(&frame.position, &D_L00_001BF220);
            particle_count = 0;
            do {
                size = RandomFloatRange(1.0f, 2.0f);
                sign = RandomIntBelow(2);
                if (!sign) {
                    sign = sign - 1;
                }
                yaw = RandomAngle();
                pitch = RandomFloatRange(0.3490659f, 1.5358898639678955f);
                speed = RandomFloatRange(0.05f, 0.1f);
                BuildSphericalOffset(&frame.direction, speed, yaw, pitch);
                qcopy(&frame.rotated, &frame.position);
                frame.position.f[0] += RandomSignedFloatRange(0.0f, 0.15f);
                --particle_count;
                frame.position.f[1] += RandomSignedFloatRange(0.0f, 0.15f);
                frame.position.f[2] += RandomSignedFloatRange(0.0f, 0.15f);
                SpawnGroundEffectParticle(&frame.position, 15, 0xFF400000, 0, sign, &frame.direction, size * 0.1f, size, 0.006f, 0);
                SpawnGroundEffectParticle(&frame.position, 15, 0x3F7F7F7F, 1, -sign, &frame.direction, size * 0.04f, size * 0.4f, 0.006f, 0);
            } while (particle_count >= 0);
            return;
        }
        /* Stop the sound if it is still the player's. Written out on each path: jump2 merges their tails. */
        handle = *(int *)(ctx + 0x224);
        if (handle != -1) {
            sound = &gSoundState[handle];
            if (sound[1].object == *(char **)(camera + 0x2290) && sound[1].active) {
                StopSoundVoice(handle);
            }
        }
        *(int *)(ctx + 0x224) = -1;
    } else {
        handle = *(int *)(ctx + 0x224);
        if (handle != -1) {
            sound = &gSoundState[handle];
            if (sound[1].object == *(char **)(camera + 0x2210) && sound[1].active) {
                StopSoundVoice(handle);
            }
        }
        *(int *)(ctx + 0x224) = -1;
    }
}
