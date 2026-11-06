/* func_PAL_L01_002F3E90, the PAL copy of func_L01_002F2570: the same C, where the frame limits take the
   50 Hz scale, the step and angle constants change, and the third actor test also requires D_001A79F0 != 0x33. */
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
extern void func_PAL_002E7270(char *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern void func_00282A60(void *, unsigned int, int);
extern void func_002833F0(void *, void *);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_0030DEC0(char *);
extern void func_PAL_0030E0E0(char *);
extern void func_PAL_0030E850(void *);
extern void func_L01_002F21F0(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern char *func_L01_002F1FD0(float, float, float);

void func_PAL_L01_002F3E90(void)
{
    int i;
    char *actor;
    char *trail;
    Quadword angle;

    func_L00_002FC980();
    for (i = 0; i < D_L01_001BD1C0.count; ++i) {
        actor = D_L01_001BD1C0.entries[i];
        if (actor && *(short *)(actor + 0xAA) == 0xE29) {
            *(unsigned short *)(actor + 0x34) |= 0x800;
        }
        if (*(short *)(actor + 0xAA) == 0xD54)
            func_PAL_002E7270(actor);
        if (actor) {
            int kind = 0xFA0;
            if (*(short *)(actor + 0xAA) == kind && D_001A79F0 != 0x33 && *(char **)(actor + 0x68))
                func_L00_00326048(actor, (float *)(*(char **)(actor + 0x68) + 0xC),
                                 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }

    if (D_001A79F0 == 1) {
        if (D_L01_001BD1C0.mode == 1) {
            TrailCamera *camera = &D_L01_001C5F90;
            D_00189E20.camera = D_L01_001BD1C0.entries[2];
            trail = D_L01_001BD1C0.entries[3];
            if (D_L01_001BD1C0.frame == (((int)(D_L01_001A9460) * 5 + 2) / 6)) {
                func_00282A60(camera, 0, sizeof(TrailCamera));
                D_L01_001AF240 = 1;
                camera->distance = 0.8f;
            }
            if ((((int)(D_L01_001A9460) * 5 + 2) / 6) < D_L01_001BD1C0.frame &&
                D_L01_001BD1C0.frame < (((int)(D_L01_001A9464) * 5 + 2) / 6)) {
                angle = 0;
                ((float *)&angle)[2] = -0.13f;
                func_002833F0(D_00189E20.transform, &angle);
                camera->distance += (12.0f - camera->distance) * 0.08400001f;
                func_0029FCC0(trail, 0, (char *)camera);
                func_00282F20(camera->position, D_00189E20.transform,
                             camera->distance);
                func_00282CC0(camera->position, camera->target,
                             camera->position);
                func_PAL_0030DEC0(trail);
                func_PAL_0030E0E0(trail);
                func_L00_002E6EF8(func_PAL_0030E850, trail);
            } else {
                D_00189E20.camera = 0;
            }
        }
        if (D_L01_001BD1C0.mode == 3) {
            trail = func_L01_002F1FD0(0.0f, 0.0f, 0.0f);
            func_L00_002E6CF0(func_L01_002F21F0, trail);
        }
    }
}
