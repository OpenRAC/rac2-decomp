#include "common.h"

typedef struct { char prefix[0x3C]; int abort; } SequencePlayback;
extern SequencePlayback D_L00_001BEFC0;
extern float D_L00_001B18E0 __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A7478 __attribute__((sda)), D_001A79F0 __attribute__((sda)), D_001A7B90 __attribute__((sda));
typedef struct { char prefix[0x1A0]; union { unsigned long long all; struct { unsigned int low, high; } word; } buttons; } SequenceInput;
extern SequenceInput D_00138180;
extern short D_001A63AC;
extern void func_00288BB8(void *);
extern int func_002B4B70(int, int);
extern void func_L00_002FC7A8(void);
extern void func_002B6658(void);
extern void func_002E5F60(void);
extern void func_L00_002A6DD0(void);
extern float func_002AA2E8(float *, float, float);
extern int func_002B6D28(void);
extern int func_00288BE8(void *);

extern void func_00293D30(void);
extern int func_002F5AF8(void);
extern void func_0029F390(unsigned char *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A0F48(unsigned char *);
extern void func_0027CFD0(void (*)(void *), void *);
extern void func_002ECB70(void *);
extern void func_002A93B0(void *);
extern void func_L00_002D4E58(void *, int);
extern void func_L00_002A70F8(void *);
extern void func_L00_002FCBE8(void);
extern void func_002914B8(void);
extern void func_0029FFB8(void);

extern int D_L00_001BCAC0[];
extern void func_002B7CE0(int);
extern void func_002F5220(void);
extern void func_002B9390(void);
extern int func_L00_003046D0(int);
extern void func_002E4AC8(void);
extern void func_002F52B8(void);

typedef struct {
    char prefix[0x34];
    int time, frame, chunk;
    short end_time, pad42, count, pad46, fade_time;
    char pad4a[14];
    int done;
    char pad5c[0x130];
    unsigned char *actors[0];
} SequenceState;

/* Plays one frame of a cutscene: moves the actors along their paths, fades in, and ends it on time or when the player skips. */
void func_L00_00370408(void) {
    float first[4];
    float second[4];
    int ended;
    unsigned char *object;
    char *path;
    int abort;
    int threshold;
    int complete;
    int i;
    short id;
    if (((SequenceState *)D_L00_001BCAC0)->done) return;
    if (((SequenceState *)D_L00_001BCAC0)->end_time == 0) {
        FlushRequestQueue(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        EndSlotRequest(0, 0);
        return;
    }
    ResetFrameCounters();
    UpdateProbePoints();
    UpdateVisibleObjects();
    RunSoundCallbacks();
    UpdateHeroFrame_L00_2();
    UpdateParticles();
    { int t; ++((SequenceState *)D_L00_001BCAC0)->frame; t = ++((SequenceState *)D_L00_001BCAC0)->time; if (t < 18) {
        ApproachValue(&D_L00_001B18E0, 0.0f, 0.16666667f);
        if (D_L00_001B18E0 > 1.0f) D_L00_001B18E0 = 1.0f;
    }
    }
    if (((SequenceState *)D_L00_001BCAC0)->fade_time <= ((SequenceState *)D_L00_001BCAC0)->time) ResumeMusicStream();
    ended = ((SequenceState *)D_L00_001BCAC0)->time >= ((SequenceState *)D_L00_001BCAC0)->end_time;
    abort = 0;
    if (((SequenceState *)D_L00_001BCAC0)->time > 17 && D_L00_001B18E0 == 0.0f) {
        if (!(((D_001A7A00[2] & 0xFFFF0000) == 0) && D_001A7478 == 0 && gCurrentMapIndex > 0) && (gPadState.buttons.word.high & 0x800)) abort = 1;
        else { unsigned long long v = (gPadState.buttons.all & 0x8000000000FULL) ^ 0x8000000000FULL; abort = 1; if (v) abort = 0; }
    }
    if (abort) {
        D_L00_001BEFC0.abort = 1;
        FlushRequestQueue(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        EndSlotRequest(0, 0);
    } else {
        if (ended) {
            ((SequenceState *)D_L00_001BCAC0)->done = 1;
            if (!LaunchQueuedRequest(&D_L00_001BEFC0)) EndSlotRequest(0, 0);
        } else {
            threshold = gIsPalVideo ? 80 : 96;
            if (((SequenceState *)D_L00_001BCAC0)->frame >= threshold) {
                ++((SequenceState *)D_L00_001BCAC0)->chunk;
                if (D_001A63AC) PumpMusicAndDiscRead(1);
                RelocateWorldObjectParts();
                QueueLevelDataChunk(((SequenceState *)D_L00_001BCAC0)->chunk + 1);
            }
            complete = ApplyCutsceneCameraKey();
            for (i = 0; i < ((SequenceState *)D_L00_001BCAC0)->count; i++) {
                object = ((SequenceState *)D_L00_001BCAC0)->actors[i];
                { int frame = ((SequenceState *)D_L00_001BCAC0)->frame >> 1;
                object[0x41] = frame + 1;
                object[0x40] = frame; }
                update_moby_animation_state(object);
                *(float *)(object + 0x44) = IntToFloat(((SequenceState *)D_L00_001BCAC0)->frame & 1) * 0.5f;
                if (complete && (((SequenceState *)D_L00_001BCAC0)->frame & 1)) *(float *)(object + 0x44) = 1.0f;
                path = *(char **)(object + 0x68);
                FastVecScale(first, path + object[0x40] * 16, 1.0f - *(float *)(object + 0x44));
                FastVecScale(second, path + object[0x41] * 16, *(float *)(object + 0x44));
                FastVecAdd(object + 0x10, first, second);
                object[0x61] = 0xFF;
                func_002A0F48(object);
                if (*(short *)(object + 0xAA) == 0xD54 /* moby class 3412 */) RegisterOverlayDrawCallback(render_environment_mapped_object, object);
                if (object[0x6F]) UpdateMobyGroundCheck(object);
                id = *(short *)(object + 0xAA);
                if (id == 0 || id == 0xF6B /* moby class 3947 */) SetupLevelGlowEffects(object, 0);
                id = *(short *)(object + 0xAA);
                if (id == 10 || id == 0x1159 /* moby class 4441 */ || id == 0x57 /* Clank */ || id == 0xD6B /* moby class 3435 */) update_moby_pulsing_glow_effects(object);
            }
        }
    }
    UpdateTutorialSceneObjects();
    UpdateSoundVoices();
    UpdateLightingEnvironment();
    ComputeLightDirection();
    UpdateIdleFrameCounters();
}
