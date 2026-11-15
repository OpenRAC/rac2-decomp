#include "common.h"

/* func_002EB1E0 (UpdateScriptedSceneActors), split from 002E7018.c: this unit needs
   -frac2-gcse-unsplit-edges for the skip test's branch layout. */

typedef struct {
    char pad0[0x10];
    float pos[4];                   /* 0x10 */
    char pad20[0x20];
    unsigned char key;              /* 0x40 */
    unsigned char next_key;         /* 0x41 */
    char pad42[2];
    float blend;                    /* 0x44 */
    char pad48[0x19];
    unsigned char alpha;            /* 0x61 */
    char pad62;
    unsigned char flags;            /* 0x63 */
    char pad64[4];
    char *keys;                     /* 0x68: 16-byte key positions */
    char pad6C[0x3E];
    short type;                     /* 0xAA */
} SceneActor;

typedef struct {
    char pad0[0x30];
    int selected;                   /* 0x30 */
    int frame;                      /* 0x34 */
    int tick;                       /* 0x38: two ticks per key */
    int chunk;                      /* 0x3C */
    short end;                      /* 0x40 */
    short pad42;
    short count;                    /* 0x44 */
    short pad46;
    short wait;                     /* 0x48 */
    char pad4A[0x0E];
    int done;                       /* 0x58 */
    char pad5C[0x10];
    int start;                      /* 0x6C */
    int destination;                /* 0x70 */
    char pad74[0x118];
    SceneActor *actors[17];         /* 0x18C */
} Scene2EB1E0;

typedef struct {
    char pad0[0x2290];
    SceneActor *focus;              /* 0x2290 */
} Game2EB1E0;

typedef struct {
    char pad0[0x1A0];
    union {
        unsigned long long held;
        unsigned int words[2];
    } buttons;                      /* 0x1A0 */
} Input2EB1E0;

/* Player state: the word at 0x08 holds both flags, so their test reads it once. */
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char x0A;
    unsigned char x0B;
    unsigned char pad0C[0x08];
    int x14;
} Global001A7A00;

extern Scene2EB1E0 D_001B8840;
extern Game2EB1E0 D_00189E20_9;
extern char D_00138180[];
#define INPUT ((Input2EB1E0 *)D_00138180)
extern char D_001A63A8_3[];
extern SceneActor *D_001B2148;
extern Global001A7A00 D_001A7A00 MACRO_ADDR;
extern int D_001A7478 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001A8BB8 MACRO_ADDR;
extern float D_001B15A0 MACRO_ADDR;

extern void func_002F5220(void);
extern void func_002ED0A0(void);
extern int func_002B6D28(void);
extern void func_002B7CE0(int);
extern void func_002EB598(void);
extern int func_002EB158(int);
extern int func_002F5AF8(void);
extern void func_0029F390(void *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E64A0(void *);
extern void func_002ECB70(void);
extern void func_0027CFD0(void *, void *);
extern void func_002A0F48(void *);
extern void func_0026F788(void *, int);
extern void func_002E4AC8(void);
extern void func_002914B8(void);
extern void func_002F52B8(void);

/* Advances the scripted scene one frame: fades in, lets the player skip once the fade is
   done, pages in the next chunk every 80 or 96 ticks and poses each actor between its two
   current keys. Returns 1 when the player skipped. */
int func_002EB1E0(void)
{
    SceneActor *actor;
    float first[4], last[4];
    float fade;
    int skip, done, camera, i;

    if (gScenePlaybackState.done)
        return 0;
    if (gScenePlaybackState.frame + 1 >= gScenePlaybackState.end) {
        gRequestedGameMode = 0;
        gScenePlaybackState.done = 1;
        return 0;
    }
    ResetFrameCounters();
    UpdateSceneBackdropQuads();
    fade = gScreenFade - 0.34f;
    gScenePlaybackState.tick++;
    gScenePlaybackState.frame++;
    gScreenFade = fade;
    if (fade < 0.0f)
        gScreenFade = 0.0f;
    if (gScenePlaybackState.frame >= gScenePlaybackState.wait)
        ResumeMusicStream();

    skip = 0;
    done = gScenePlaybackState.frame >= gScenePlaybackState.end;
    if (gScenePlaybackState.frame >= 18 && gScreenFade == 0.0f) {
        if ((D_001A7A00.x0A || D_001A7A00.x0B || D_001A7478 || gCurrentMapIndex <= 0)
            && (INPUT->buttons.words[1] & 0x800))
            skip = 1;
        else if ((INPUT->buttons.held & 0x8000000000FULL) == 0x8000000000FULL)
            skip = 1;
    }

    if (skip || done) {
        gScenePlaybackState.done = 1;
        gRequestedGameMode = 0;
    } else {
        int ticks = gIsPalVideo ? 80 : 96;
        if (gScenePlaybackState.tick >= ticks) {
            gScenePlaybackState.chunk++;
            if (*(short *)(D_001A63A8_3 + 4))
                PumpMusicAndDiscRead(1);
            SpawnModelPartMobys();
            LoadSceneChunkData(gScenePlaybackState.chunk + 1);
        }
        camera = ApplyCutsceneCameraKey();
        for (i = 0; i < gScenePlaybackState.count; i++) {
            char *keys;
            int key, type;

            actor = gScenePlaybackState.actors[i];
            key = gScenePlaybackState.tick >> 1;
            actor->next_key = key + 1;
            actor->key = key;
            update_moby_animation_state(actor);
            actor->blend = IntToFloat(gScenePlaybackState.tick & 1) * 0.5f;
            if (camera && (gScenePlaybackState.tick & 1))
                actor->blend = 1.0f;
            keys = actor->keys;
            FastVecScale(first, keys + actor->key * 16, 1.0f - actor->blend);
            FastVecScale(last, keys + actor->next_key * 16, actor->blend);
            FastVecAdd(actor->pos, first, last);
            type = actor->type;
            if (type == 0xD54 /* moby class 3412 */) {
                actor->flags = 8;
                UpdateEquipmentPieces(actor);
                if (!D_001B2148 || D_001B2148->type == type)
                    RegisterOverlayDrawCallback(render_environment_mapped_object, actor);
            }
            actor->alpha = 255;
            func_002A0F48(actor);
            if (actor->type == 0) {
                D_00189E20_9.focus = actor;
                EmptyStubF788(actor, 1);
            }
        }
    }
    UpdateSoundVoices();
    UpdateLightingEnvironment();
    UpdateIdleFrameCounters();
    return skip;
}
