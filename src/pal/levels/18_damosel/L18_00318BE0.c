/* func_PAL_L18_00318BE0, the PAL copy of func_L18_003170F8: per-frame update of Damosel's scene.
 * The object scan is the one in func_L05_00314E28, with a level test added to its last case; then,
 * in mode 4, a 13-entry table sets off an explosion, with an optional camera shake, when the scene
 * timer reaches an entry's time, scaled for 50 Hz.
 *
 * Unlike the USA copy this one needs no -fmove-all-movables: the scale makes the spot loop too long
 * for loop.c to hoist everything, and retail stops at 0.08f, leaving 58 and 0.07f in the loop.  That
 * takes the shake stores in channel order, and the scene, table and id locals, whose longer
 * lifetimes let loop.c hoist those values in its first pass. */
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
extern void func_PAL_002E7270(void *);
extern void func_L00_00326048(void *, void *, unsigned int, unsigned int, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

void func_PAL_L18_00318BE0(void)
{
    float position[4] __attribute__((aligned(16)));
    int i, j, k;
    unsigned char *object, *state;
    SceneMoby *moby;
    ExplosionSpot *spot, *table;
    Scene18 *scene;

    func_L00_002FC980();
    for (i = 0; i < D_L18_001BD4C0.count; i++) {
        object = D_L18_001BD4C0.objects[i];
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
        }
        if (*(short *)(object + 0xAA) == 0xD54) {
            func_PAL_002E7270(object);
        }
        if (object) {
            int type = 0xFA0;

            if (*(short *)(object + 0xAA) == type && D_001A79F0 != 51) {
                state = *(unsigned char **)(object + 0x68);
                if (state) {
                    func_L00_00326048(object, state + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
                }
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
        scene = &D_L18_001BD4C0;
        table = D_L18_00287D10;
        spot = &table[j];
        if (scene->timer == (((int)(spot->time) * 5 + 2) / 6)) {
            qcopy(position, spot->position);
            if (spot->cameraRelative) {
                func_00283098(position, position, D_L18_001B9680.matrix);
                func_00282CC0(position, position, D_L18_001B9680.position);
            }
            func_PAL_L00_003FB330(position, 0, 25, 20, 20, 20, 45, 1, spot->scale, 20.0f, 1, 1, 0, 0);
            if (spot->shake > 0.0f) {
                D_L18_001B9680.shakeTime = 46;
                D_L18_001B9680.shake = spot->shake * 0.08f;
                D_L18_001B9680.shakeTimer = 0;
                D_L18_001B9680.secondaryShakeTime = 58;
                D_L18_001B9680.secondaryShake = spot->shake * 0.07f;
            }
        }
    }
}
