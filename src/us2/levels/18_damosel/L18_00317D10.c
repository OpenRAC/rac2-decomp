/* func_US2_L18_00317D10, the USA v2.00 copy of func_L18_003170F8: the same scene update, where
 * class 0xFA0's effect is skipped while D_001A79F0 is 0x33.  That test adds a constant to the
 * object scan, and the wording below follows from loop.c's movable threshold (61, less 3 per
 * move, times savings and lifetime, against the loop's insn count).  v1.01's unit needs
 * -fmove-all-movables; this one does not, because retail hoists 0x33 only in the second loop pass,
 * after the scan pointer's init.
 *
 * The scan loop's bottom test reads the count through `scene`, set in the body.  That makes 49
 * insns rather than 51, so the first pass takes 0xFA0 and leaves 0x33.  The entry test compares
 * `i`, as a for loop's does: combine then reissues `i = 0` without its REG_EQUAL note, and `i` is
 * not given a doubled live length that would lose it $s1 to the scan pointer.
 *
 * In the timed-explosion loop, `timing` and `spots` are set first and the two times held in
 * locals, for the lifetimes that carry those constants past the first pass's threshold.  With the
 * table address hoisted there, `spot` is reduced in the first pass, `j` only counts by the second,
 * and the second pass reverses it. */
#include "common.h"

typedef struct {
    unsigned char pad00[0x30];
    int mode, timer;
    unsigned char pad38[0xC];
    short count;
    unsigned char pad46[0x146];
    unsigned char *objects[256];
} Scene18;

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0xCA];
} SceneMoby;

typedef struct {
    float position[4];
    int time;
    float scale;
    int cameraRelative;
    float shake;
} ExplosionSpot;

typedef struct {
    unsigned char pad00[0x140];
    float position[4];
    unsigned char pad150[0x10];
    float shake;
    int pad164, shakeTime, shakeTimer;
    unsigned char pad170[0x10];
    float secondaryShake;
    int pad184, secondaryShakeTime;
    unsigned char pad18C[0x370 - 0x18C];
    float matrix[12];
} SceneCamera;

extern Scene18 D_L18_001BD4C0;
extern int D_001A79F0 __attribute__((sda));
extern SceneMoby *D_L18_001B281C MACRO_ADDR;
extern SceneMoby *D_L18_001B2820 MACRO_ADDR;
extern SceneCamera D_L18_001B9680;
extern ExplosionSpot D_L18_00287D10[];

extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, unsigned int, unsigned int, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

void func_US2_L18_00317D10(void)
{
    float position[4] __attribute__((aligned(16)));
    int i, j, k, timer;
    unsigned char *object, *state;
    SceneMoby *moby;
    ExplosionSpot *spot, *spots;
    Scene18 *scene, *timing;
    int shakeTime, secondaryShakeTime;

    func_L00_002FC980();
    i = 0;
    if (i < D_L18_001BD4C0.count) do {
        scene = &D_L18_001BD4C0;
        object = scene->objects[i];
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
        }
        if (*(short *)(object + 0xAA) == 0xD54) {
            func_002E64A0(object);
        }
        if (object && *(short *)(object + 0xAA) == 0xFA0 && D_001A79F0 != 0x33) {
            state = *(unsigned char **)(object + 0x68);
            if (state) {
                func_L00_00326048(object, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
            }
        }
        i++;
    } while (i < scene->count);
    if (D_001A79F0 != 18 || D_L18_001BD4C0.mode != 4) {
        return;
    }
    if (D_L18_001BD4C0.timer == 1) {
        for (k = 0; &D_L18_001B281C[k] < D_L18_001B2820; k++) {
            moby = &D_L18_001B281C[k];
            moby->flags |= 0x41;
        }
    }
    for (j = 0; j < 13; j++) {
        timing = &D_L18_001BD4C0;
        spots = D_L18_00287D10;
        timer = timing->timer;
        spot = &spots[j];
        if (timer == spot->time) {
            qcopy(position, spot->position);
            if (spot->cameraRelative) {
                func_00283098(position, position, D_L18_001B9680.matrix);
                func_00282CC0(position, position, D_L18_001B9680.position);
            }
            func_0032C700(position, 0, 25, 20, 20, 20, 45, 1, spot->scale, 20.0f, 1, 1, 0, 0);
            if (spot->shake > 0.0f) {
                shakeTime = 55;
                secondaryShakeTime = 70;
                D_L18_001B9680.shakeTime = shakeTime;
                D_L18_001B9680.secondaryShakeTime = secondaryShakeTime;
                D_L18_001B9680.shakeTimer = 0;
                D_L18_001B9680.shake = spot->shake * 0.08f;
                D_L18_001B9680.secondaryShake = spot->shake * 0.07f;
            }
        }
    }
}
