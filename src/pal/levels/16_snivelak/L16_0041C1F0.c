#include "include_asm.h"
#include "common.h"

/* func_PAL_L16_0041D030, the PAL copy of func_L16_00417DB0: the same C, where both spin steps
   scale by 1.2 for 50 Hz and the second func_002C2210 argument 15 becomes 12. */

typedef int Vector128 __attribute__((mode(TI)));
typedef struct {
    Vector128 player, velocity, previous, point;
} SparkWorkspace;

extern char *D_L16_001B2B1C MACRO_ADDR;
/* Resident position and collision pointer, at +0 and +0x2210. */
extern struct {
    float position[4];
    char pad[0x2200];
    char *collision;
} D_00189EA0;
extern struct {
    char pad[0x18];
    char *owner;
    char pad1[4];
    Vector128 point;
} D_L16_001BFF40;
/* These offsets are relative to a 0x70-stride sound anchor, not an array element extent. */
struct SoundAnchor {
    char pad[0x74];
    unsigned char active;
    char pad1[0x13];
    char *owner;
};
extern char D_00188660[];

extern int func_002ACBC8(void *, int);
extern float func_002A7878(float, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L14_003F0E68(void *);
extern int func_002A8508(int, int);
extern int func_00277258(void *, int, void *, float);
extern int func_002E5CF8(int, int, char *);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern void func_002AF000(float *, float, float, float);
extern float func_002A78D8(float, float);
/* The integer and FP argument banks retain their independent EE ABI order. */
extern void *func_002C2210(void *, int, unsigned int, float, float, int, int, void *, float, int);
extern void func_002E59F8(int);

/* Animate the emitter and spawn three sparks at the qualifying collision point. */
void func_PAL_L16_0041D030(char *object)
{
    SparkWorkspace local;
    char *state = *(char **)(object + 0x68);
    char *target;
    struct SoundAnchor *sound;
    float speed, firstAngle, secondAngle, magnitude;
    int i, index, handle;

    if (*(unsigned char *)(object + 0x20) == 0) {
        object[0x20] = 1;
        *(int *)(object + 0x98) = 0;
        *(unsigned short *)(object + 0x34) |= 0x41;
    }
    if (*(unsigned char *)(object + 0x20) == 1) {
        target = D_L16_001B2B1C + *(int *)state*0x100;
        if (target == 0 || *(unsigned char *)(target + 0x20) == 0xfe || *(unsigned char *)(target + 0x20) == 0xfd) {
            if (func_002ACBC8(&D_00189EA0, *(int *)(state + 8)) != 0) {
                int snapshot = *(int *)(*(char **)(object + 0x24) + 0x10);
                object[0x20] = 2;
                *(int *)(object + 0x98) = snapshot;
            }
        }
    }
    if (*(unsigned char *)(object + 0x20) != 2)
        return;
    *(float *)(state + 0x10) += *(float *)(state + 0x14) * 1.2f;
    *(float *)(state + 0x18) += *(float *)(state + 0x1c) * 1.2f;
    if (*(float *)(state + 0x10) >= 8.0f)
        *(float *)(state + 0x10) -= 8.0f;
    if (*(float *)(state + 0x18) >= 8.0f)
        *(float *)(state + 0x18) -= 8.0f;
    *(float *)(state + 0x14) = func_002A7878(0.003f, 0.005f);
    *(float *)(state + 0x1c) = func_002A7878(0.001f, 0.0025f);
    func_L00_002E6EF8(func_L14_003F0E68, object);
    if (func_002A8508(*(int *)(state + 4), -1) == 0) {
        *(int *)(object + 0x98) = 0;
        object[0x20] = 3;
    }
    qcopy(&local.player, &D_00189EA0);
    ((float *)&local.player)[2] = ((float *)&local.player)[2] + 0.75f;
    if (func_00277258(&local.player, 0, D_00189EA0.collision, 0.5f) != 0 && D_L16_001BFF40.owner != 0 && *(short *)(D_L16_001BFF40.owner + 0xaa) == 0x10fb) {
        qcopy(&local.point, &D_L16_001BFF40.point);
        {
            char *audioBank = D_00188660;
            for (i = 2; i >= 0; i--) {
                int loopHandle = *(int *)(state + 12);
                struct SoundAnchor *loopSound = (struct SoundAnchor *)(audioBank + 0x70*loopHandle);
                if (loopSound->owner != object || loopSound->active == 0)
                    *(int *)(state + 12) = func_002E5CF8(1, 4, object);
                speed = func_002A7878(1.0f, 2.0f);
                index = func_002A77E0(2);
                if (index == 0)
                    index--;
                firstAngle = func_002A7940();
                secondAngle = func_002A7878(0.3490658998f, 1.535889864f);
                magnitude = func_002A7878(0.05f, 0.1f);
                func_002AF000((float *)&local.velocity, magnitude, firstAngle, secondAngle);
                qcopy(&local.previous, &local.point);
                ((float *)&local.point)[0] += func_002A78D8(0.0f, 0.15f);
                ((float *)&local.point)[1] += func_002A78D8(0.0f, 0.15f);
                ((float *)&local.point)[2] += func_002A78D8(0.0f, 0.15f);
                func_002C2210(&local.point, 12, 0xff803040u, speed*0.1f, speed, 0, index, &local.velocity, 0.006f, 0);
            }
        }
        return;
    }
    handle = *(int *)(state + 12);
    if (handle != -1) {
        sound = (struct SoundAnchor *)(D_00188660 + 0x70*handle);
        if (sound->owner == object && sound->active != 0)
            func_002E59F8(handle);
    }
    *(int *)(state + 12) = -1;
}
