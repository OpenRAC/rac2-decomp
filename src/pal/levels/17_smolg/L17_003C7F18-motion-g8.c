#include "common.h"

/* func_PAL_L17_003C7F18, the PAL copy of func_L17_003C4090: the same C, where the frame
   counts become the 50 Hz (x * 300 + 2) / 6, the 60-frame flash cycle 50 and its 15-frame
   flash 12, and the per-frame angles grow by 6/5. */

/* The instance data of the bobbing object. */
typedef struct {
    float bobPhase;             /* 0x00 */
    float bobOffset;            /* 0x04 */
    float swayPhase;            /* 0x08 */
    float tiltPhase;            /* 0x0C */
    float rise;                 /* 0x10: height of the upper rest above the lower one */
    int state;                  /* 0x14 */
    int timer;                  /* 0x18 */
    float baseZ;                /* 0x1C */
    float minRise;              /* 0x20 */
    float maxRise;              /* 0x24 */
    float minWait;              /* 0x28: seconds */
    float maxWait;              /* 0x2C */
    float riseTime;             /* 0x30 */
    float fallTime;             /* 0x34 */
    float spinSpeed;            /* 0x38: radians per frame */
    int sound;                  /* 0x3C */
    int stopped;                /* 0x40 */
} BobberVars;

typedef struct {
    u8 pad0[0x10];
    float position[4];          /* 0x10 */
    u8 pad20[0x68 - 0x20];
    BobberVars *vars;           /* 0x68 */
    u8 pad6C[0x78 - 0x6C];
    int color;                  /* 0x78 */
    u8 pad7C[0xA8 - 0x7C];
    u8 impactSlot;              /* 0xA8 */
    u8 padA9[0xB2 - 0xA9];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xF0 - 0xB4];
    float rotation[4];          /* 0xF0 */
} Moby;

/* The sound voices are 0x70-byte records after the pool's 0x70-byte header.
   SoundVoice views voice n from record n, so its offsets include the header. */
typedef struct {
    u8 bytes[0x70];
} SoundRecord;

typedef struct {
    u8 pad0[0x74];
    u8 active;                  /* 0x74 */
    u8 pad75[0x88 - 0x75];
    Moby *owner;                /* 0x88 */
} SoundVoice;

/* The frame counter is an incomplete array: it keeps its absolute address
   load, while the complete tuning scalars use GP addressing. The -g profile
   keeps retail's div.s hazards. */
extern int D_L17_001B2748[] __attribute__((sda));
extern float D_L17_001B0248 __attribute__((sda));
extern float D_L17_001B024C __attribute__((sda));
extern float D_L17_001B0250 __attribute__((sda));
extern float D_L17_001B0254 __attribute__((sda));
extern float D_L17_001B0258 __attribute__((sda));
extern char D_00189EA0[];          /* the hero's position */
extern SoundRecord D_00188660[];
extern char D_L17_001A8F20[] MACRO_ADDR;

extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283B98(float, float);
extern float func_00282E80(void *, void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern int func_00282948(int *);
extern int func_002E5CF8(int, int, void *);
extern int func_002A9640(void *, int, int);
extern float func_00283CE0(int);
extern void func_002AEE70(void *, float *, float *, float, float, float);
extern void func_002AEF28(void *, float *, float *, float, float, float);
extern void func_002E59F8(int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int,
                          int, int, int, float, float);
extern void func_002B0A68(void *, int, void *, int, float, float, float, float);
extern void func_L00_00326110(void *, int, float);
extern void func_0029F338(void *);

/* Rests at a low and a high height in turn, easing each move along a cosine,
   while bobbing, swaying and spinning; plays its sound while the hero is near
   and is destroyed when hit. */
void func_PAL_L17_003C7F18(Moby *moby)
{
    BobberVars *vars = moby->vars;
    float spin;
    float ratio;
    int color;
    int flash;

    /* Flash bright for 12 frames of every 50, phased by the instance id. */
    flash = (D_L17_001B2748[0] + moby->uid) % 50 < 12;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;
    if (vars->stopped == 1)
        return;

    switch (vars->state) {
    case 0:
        /* First update: pick the rise, the spin and a random point in the cycle. */
        vars->baseZ = moby->position[2];
        vars->rise = func_002A7878(vars->minRise, vars->maxRise);
        spin = func_002A7878(0.0052359886f, 0.015707966f);
        if (func_002A77E0(2))
            spin = -spin;
        vars->spinSpeed = spin;
        vars->sound = -1;
        if (func_002A77E0(2)) {
            moby->position[2] += vars->rise;
            vars->state = 3;
        } else {
            vars->state = 1;
        }
        vars->timer = func_002A7820(func_00283CF0((vars->minWait * 300.0f + 2.0f) * 0.16666667f),
                                    func_00283CF0((vars->maxWait * 300.0f + 2.0f) * 0.16666667f));
        vars->timer = func_002A7820(0, vars->timer);
        break;

    case 1:
        /* Resting low. */
        if (func_00282948(&vars->timer)) {
            vars->timer = func_00283CF0((vars->riseTime * 300.0f + 2.0f) * 0.16666667f);
            vars->state = 2;
        }
        moby->position[2] = vars->baseZ;
        break;

    case 2:
        /* Rising. */
        if (func_00282948(&vars->timer)) {
            moby->position[2] = vars->baseZ + vars->rise;
            vars->state = 3;
            vars->timer = func_002A7820(func_00283CF0((vars->minWait * 300.0f + 2.0f) * 0.16666667f),
                                        func_00283CF0((vars->maxWait * 300.0f + 2.0f) * 0.16666667f));
        } else {
            ratio = func_00283CE0(vars->timer) / ((vars->riseTime * 300.0f + 2.0f) * 0.16666667f);
            moby->position[2] = vars->baseZ +
                vars->rise * (func_00283180(ratio * 3.141593f) * 0.5f) +
                vars->rise * 0.5f;
        }
        break;

    case 3:
        /* Resting high. */
        if (func_00282948(&vars->timer)) {
            vars->timer = func_00283CF0((vars->fallTime * 300.0f + 2.0f) * 0.16666667f);
            vars->state = 4;
        }
        moby->position[2] = vars->baseZ + vars->rise;
        break;

    case 4:
        /* Falling. */
        if (func_00282948(&vars->timer)) {
            moby->position[2] = vars->baseZ;
            vars->state = 1;
            vars->timer = func_002A7820(func_00283CF0((vars->minWait * 300.0f + 2.0f) * 0.16666667f),
                                        func_00283CF0((vars->maxWait * 300.0f + 2.0f) * 0.16666667f));
        } else {
            ratio = func_00283CE0(vars->timer) / ((vars->fallTime * 300.0f + 2.0f) * 0.16666667f);
            moby->position[2] = vars->baseZ +
                vars->rise * (func_00283180((1.0f - ratio) * 3.141593f) * 0.5f) +
                vars->rise * 0.5f;
        }
        break;
    }

    /* The periods are in seconds: 0.0003490659 is one degree per second, in radians per 50 Hz frame. */
    func_002AEE70(moby, &vars->bobPhase, &vars->bobOffset, D_L17_001B024C,
                  360.0f / D_L17_001B0248 * 0.0003490659f, moby->position[2]);
    func_002AEF28(moby, &vars->swayPhase, &vars->tiltPhase, D_L17_001B0250,
                  360.0f / D_L17_001B0254 * 0.0003490659f,
                  360.0f / D_L17_001B0258 * 0.0003490659f);
    moby->rotation[2] = func_00283B98(moby->rotation[2], vars->spinSpeed);

    if (func_00282E80(moby->position, D_00189EA0) < 80.0f) {
        SoundVoice *voice = (SoundVoice *)&D_00188660[vars->sound];
        if (voice->owner != moby || !voice->active)
            vars->sound = func_002E5CF8(0, 4, moby);
    } else {
        int sound = vars->sound;
        if (sound != -1) {
            SoundVoice *voice = (SoundVoice *)&D_00188660[sound];
            if (voice->owner == moby && voice->active)
                func_002E59F8(sound);
        }
        vars->sound = -1;
    }

    if (func_002A9640(moby, 0x4010000, 0)) {
        func_0032C700(moby->position, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 10.0f, 20.0f);
        func_002B0A68(moby, 127, D_L17_001A8F20, 255, 3.0f, 6.0f, 3.0f, 6.0f);
        func_L00_00326110(moby, 9, 0);
        func_0029F338(moby);
    } else {
        moby->impactSlot = 255;
    }
}
