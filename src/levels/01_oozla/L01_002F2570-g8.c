#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
/* The clear proves an 80-byte state span; this view covers that span. */
typedef struct TrailCamera {
    float target[4];
    float position[4];
    float unused20;
    float distance;
    unsigned char tail[0x28];
} TrailCamera;

/* Resident view through the transform used here; later fields are not described. */
typedef struct HeroView {
    char prefix[0x5C0];
    char *camera;
    char gap5C4[0x16C];
    float transform[16];
} HeroView;
extern HeroView D_00189E20;
extern int D_001A79F0;
extern int D_L01_001A9460 __attribute__((sda));
extern int D_L01_001A9464 __attribute__((sda));
extern int D_L01_001AF240;
typedef struct SceneManager {
    char prefix[0x30];
    int mode;
    int frame;
    char gap38[0xC];
    short count;
    char gap46[0x146];
    char *entries[0];
} SceneManager;
extern SceneManager D_L01_001BD1C0;
extern TrailCamera D_L01_001C5F90;

extern void func_L00_002FC980(void);
extern void func_002E64A0(char *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern void func_00282A60(void *, unsigned int, int);
extern void func_002833F0(void *, void *);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0030CAD0(char *);
extern void func_0030CCD0(char *);
extern void func_0030D430(void *);
extern void func_L01_002F21F0(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern char *func_L01_002F1FD0(float, float, float);

/* Per-frame level script for the Oozla intro scene. It tweaks a few objects and runs the trailing camera that follows the player. */
void func_L01_002F2570(void)
{
    int i;
    char *actor;
    char *trail;
    Quadword angle;

    StartStartupAnimations();
    for (i = 0; i < D_L01_001BD1C0.count; ++i) {
        actor = D_L01_001BD1C0.entries[i];
        if (actor && *(short *)(actor + 0xAA) == 0xE29 /* moby class 3625 */) {
            *(unsigned short *)(actor + 0x34) |= 0x800;
        }
        if (*(short *)(actor + 0xAA) == 0xD54 /* moby class 3412 */)
            UpdateEquipmentPieces(actor);
        if (actor && *(short *)(actor + 0xAA) == 0xFA0 /* TV Screens */ && *(char **)(actor + 0x68))
            StoreAngleUpdateResult(actor, (float *)(*(char **)(actor + 0x68) + 0xC),
                             0x80AAAAD2, 0x80396464, 0.061086535453796387f);
    }

    if (gCurrentMapIndex == 1) {
        if (D_L01_001BD1C0.mode == 1) {
            TrailCamera *camera = &D_L01_001C5F90;
            gHeroState.camera = D_L01_001BD1C0.entries[2];
            trail = D_L01_001BD1C0.entries[3];
            if (D_L01_001BD1C0.frame == D_L01_001A9460) {
                ClearMemory(camera, 0, sizeof(TrailCamera));
                D_L01_001AF240 = 1;
                camera->distance = 0.8f;
            }
            if (D_L01_001A9460 < D_L01_001BD1C0.frame &&
                D_L01_001BD1C0.frame < D_L01_001A9464) {
                angle = 0;
                ((float *)&angle)[2] = -0.13f;
                euler_rotation_basis(gHeroState.transform, &angle);
                camera->distance += (12.0f - camera->distance) * 0.07f;
                TransformMobyJointToWorld(trail, 0, (char *)camera);
                vec_scale_to_length(camera->position, gHeroState.transform,
                             camera->distance);
                FastVecAdd(camera->position, camera->target,
                             camera->position);
                InitializeBoltPointChain(trail);
                UpdateBeamChainPoints(trail);
                AddDrawCallbackToList3(DrawBeamRibbonsLevelVariant, trail);
            } else {
                gHeroState.camera = 0;
            }
        }
        if (D_L01_001BD1C0.mode == 3) {
            trail = FindNearestTvScreen(0.0f, 0.0f, 0.0f);
            AddDrawCallbackToList1(BuildShipTrailMeshFromSource, trail);
        }
    }
}
