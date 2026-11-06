/* func_L18_003170F8: per-frame update of Damosel's scene.  The object scan is the one in
 * func_L05_00314E28; then, in mode 4, a 13-entry table sets off an explosion, with an optional
 * camera shake, when the scene timer reaches an entry's time.  Its own file for
 * -fmove-all-movables (config/cflags.txt): the spot loop has 62 insns against loop.c's movable
 * threshold of 61, and retail hoists all of its constants, the table address included.
 *
 * Reading the moby bounds inside their loop, as RAC1's initialize_hero does, leaves its index
 * unreduced; locals holding the bounds are strength-reduced.  The scene timer is read before the
 * table address so that the hoisted state address comes first. */
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

void func_L18_003170F8(void)
{
    float position[4] __attribute__((aligned(16)));
    int i, j, k, timer;
    unsigned char *object, *state;
    SceneMoby *moby;
    ExplosionSpot *spot;

    func_L00_002FC980();
    for (i = 0; i < D_L18_001BD4C0.count; i++) {
        object = D_L18_001BD4C0.objects[i];
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
        }
        if (*(short *)(object + 0xAA) == 0xD54) {
            func_002E64A0(object);
        }
        if (object && *(short *)(object + 0xAA) == 0xFA0) {
            state = *(unsigned char **)(object + 0x68);
            if (state) {
                func_L00_00326048(object, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
            }
        }
    }
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
        timer = D_L18_001BD4C0.timer;
        spot = &D_L18_00287D10[j];
        if (timer == spot->time) {
            qcopy(position, spot->position);
            if (spot->cameraRelative) {
                func_00283098(position, position, D_L18_001B9680.matrix);
                func_00282CC0(position, position, D_L18_001B9680.position);
            }
            func_0032C700(position, 0, 25, 20, 20, 20, 45, 1, spot->scale, 20.0f, 1, 1, 0, 0);
            if (spot->shake > 0.0f) {
                D_L18_001B9680.shakeTime = 55;
                D_L18_001B9680.secondaryShakeTime = 70;
                D_L18_001B9680.shakeTimer = 0;
                D_L18_001B9680.shake = spot->shake * 0.08f;
                D_L18_001B9680.secondaryShake = spot->shake * 0.07f;
            }
        }
    }
}
