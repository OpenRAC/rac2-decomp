#include "common.h"
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void func_002F5220(void);
extern void func_002F52B8(void);
extern void func_00133220(void);
extern void func_00133230(void);
extern int func_00132028(void);
extern void func_00132A10(int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_0029F390(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void func_002EC1C0(void);
extern char D_00240450[];
extern void func_002ED260(void *);
extern void func_00132AC8(void);
extern int func_001163B0(void);
extern void func_00132858(int);
extern void func_00132828(void);
extern void func_002E80B0(void);
extern void func_00282A60(void *, int, int);
extern void func_00294070(int);
extern void func_002E6A60(void);
extern void func_0027AB40(void);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_002E64A0(int);

typedef struct {
 char pad0[0x10]; float position[4]; char pad20[4]; char *definition;
 char pad28[4]; float scale; char pad30[2]; short draw_flags; char pad34[12];
 unsigned char key, next_key, current_anim, next_anim; float blend;
 char pad48[0x19]; unsigned char alpha, cached_frame, flags; char pad64[4];
 char *keys; char pad6c[0x29]; unsigned char opacity; char pad96[0x14]; short type;
} TransitionActor;
extern float D_001B15A0 MACRO_ADDR;
typedef struct {
 char pad[0xc]; unsigned char count; char gap[0x3b]; void *animations[1];
} AnimationClass;
typedef struct { char pad[0x24]; AnimationClass *definition; } AnimationObject;
typedef struct {
 char pad[0x34]; int frame, tick, page; short duration, pad42, count;
 char pad46[0xe]; int id; char pad58[0x14]; int start, end;
 int entries[70]; char *objects[17];
} TransitionScene;
extern TransitionScene D_001B8840;        /* controller state */
typedef struct {
 char pad[0x2c]; short flag; char pad2e[0x36]; int index, phase;
} TransitionMenu;
extern TransitionMenu D_00152C00;        /* mode block: +0x64 index, +0x68 phase */
extern int D_001B2130_first SDATA(D_001B2130);


extern int D_001B2130[] MACRO_ADDR __attribute__((sda));         /* [0] +0, [1] +4, [3] +0xC */
extern int D_001B2148[] __attribute__((sda));
extern int D_001B2148_first[] __asm__("D_001B2148") __attribute__((sda));         /* null-terminated entity list */
typedef struct { char pad[0x24]; float scale; } ScaleClass;
typedef struct { char pad[0x24]; ScaleClass *definition; int pad28; float scale; } ScaleEntity;
extern ScaleEntity *D_00214920[];         /* null-terminated entity list */
extern int D_001ABEB0 __attribute__((sda));
extern int D_001A7280;
extern int D_001A7280_block[] __asm__("D_001A7280") MACRO_ADDR __attribute__((sda));
extern int D_001B22B0;
typedef struct { int pad, data_offset; char gap[0x48]; int scenes[5]; } TransitionHeader;
typedef struct { int offset, size; } TransitionChunk;
typedef struct { char pad[12]; int start, end, pad14; TransitionHeader *data; } TransitionArchive;
extern TransitionArchive D_001BAEC0;
extern int D_001886D0[];
extern char D_00261F30[];        /* 16-byte entries */
typedef struct { float x, y, z, w; } TransitionVector;
typedef struct { char pad[0xc0]; TransitionVector basis[3]; } MatrixEntity;
extern TransitionVector D_001B20D0 MACRO_ADDR;
extern char D_001AC0C0[] SDATA(D_001AC0C0);
extern char D_001AC0D0[] SDATA(D_001AC0D0);
extern char D_001AC120[] SDATA(D_001AC120);
extern float D_001AC150[] SDATA(D_001AC150);
extern float D_001AC168[] SDATA(D_001AC168);
extern float D_001ABDD4 MACRO_ADDR;
extern float D_001ABF10 __attribute__((sda));
typedef struct { char pad[0xb0]; float fov; } TransitionView;
extern TransitionView D_001B9040;        /* view: +0xB0 float */

/* Runs one frame of the transition scene: moves each object along its path and starts the next scene part when one ends. */
int func_002E8368(void)
{
    float scratchA[4], scratchB[4], mobyMatrix[16];
    float fadeScale;
    int i, nextIndex;

    ResetFrameCounters();
    {
        float newFade = gScreenFade - 0.25f;
        gScenePlaybackState.tick = gScenePlaybackState.tick + 1;
        gScenePlaybackState.frame = gScenePlaybackState.frame + 1;
        gScreenFade = newFade;
        if (newFade < 0.0f)
            gScreenFade = 0.0f;
    }
    if (gScenePlaybackState.frame == 1) {
        int soundIndex;
        SetSoundCurrentBufferFlag();
        soundIndex = gHeroMoby_00152C00.index;
        func_00132A10(D_001B2130[soundIndex], 0, 0x400, 0, 0, 0, 0, (int)D_001886D0 + soundIndex * 0x70);
        ClearSoundFlagAndUpdate();
        snd_Pump();
    }
    if (gScenePlaybackState.frame < gScenePlaybackState.duration) {
        goto running;
    }
    /* the phase has ended */
    for (i = 0; i < gScenePlaybackState.count; i++) {
        AnimationObject *animObject = (AnimationObject *)gScenePlaybackState.objects[i];
        if (animObject != 0) {
            animObject->definition->count--;
            animObject->definition->animations[animObject->definition->count] = 0;
            MarkMobySpawned(animObject);
        }
    }
    if (D_001ABEB0 != 0) {
        StartSequenceForSelectedState();
        D_001ABEB0 = 0;
    }
    InitEffectRecordTable(D_00240450);
    if (D_001A7280 < 2)
        gHeroMoby_00152C00.phase = 0;
    if (gHeroMoby_00152C00.phase < 2) {
        if (gHeroMoby_00152C00.index != 2) {
            func_00132AC8();
            while (snd_Pump() != 0)
                ;
        }
        if (gHeroMoby_00152C00.phase == 0) {
            int randomStep = ((Rand() >> 16) % 3) + 1;
            gHeroMoby_00152C00.index = (gHeroMoby_00152C00.index + randomStep) & 3;
        } else {
            gHeroMoby_00152C00.index = 4;
            SetSoundCurrentBufferFlag();
            SendSoundCommand6(D_001B2130_first);
            SendSoundCommand6(D_001B2130[1]);
            SendSoundCommand6(D_001B2130[3]);
            ClearSoundFlagAndUpdate();
            while (snd_Pump() != 0)
                ;
            func_00132828();
            D_001A7280_block[1] = 0;
            LoadSceneTextureBlock();
        }
        gHeroMoby_00152C00.phase = gHeroMoby_00152C00.phase + 1;
        qcopy(D_001AC0D0, D_001AC0C0);
        ClearMemory(&gScenePlaybackState, 0, 0x1D0);
        {
            int workspace_offset = D_001B22B0;
            TransitionHeader *header;
            TransitionChunk *chunk;
            int data_base;
            int k;
            gScenePlaybackState.start = D_001BAEC0.start + workspace_offset;
            gScenePlaybackState.end = D_001BAEC0.end + workspace_offset;
            header = D_001BAEC0.data;
            data_base = (int)header + header->data_offset;
            chunk = (TransitionChunk *)(data_base + header->scenes[gHeroMoby_00152C00.index]);
            for (k = 0; k < 70 && chunk->size != 0; k++) {
                int offset = chunk->offset + 0x800;
                gScenePlaybackState.entries[k] = data_base + header->scenes[gHeroMoby_00152C00.index] + offset;
                chunk++;
            }
        }
        SelectSegmentAndUpdateWorld(0);
        goto after;
    } else {
        if (D_001A7280_block[1] == 0)
            return 1;
        D_001A7280_block[1] = 0;
        return 1;
    }

running:
    if (!(gScenePlaybackState.tick < 0x60)) {
        gScenePlaybackState.page = gScenePlaybackState.page + 1;
        SelectSegmentAndUpdateWorld(gScenePlaybackState.page);
    }
after:
    SetCameraFromSelectedRecord();
    {
        float current = D_001B9040.fov;
        float minFov = D_001AC168[gHeroMoby_00152C00.index];
        if (current < minFov)
            D_001B9040.fov = minFov;
    }
    UpdateViewContext();
    fadeScale = 1.0f;
    if (gHeroMoby_00152C00.index == 4) {
        fadeScale = (float)(gScenePlaybackState.duration - gScenePlaybackState.frame) / (float)gScenePlaybackState.duration;
        FastVecScale(scratchA, D_001AC120, fadeScale);
        FastVecAdd(D_001AC0D0, D_001AC0D0, scratchA);
    }
    FastVecScale(&D_001B20D0, D_00261F30 + gHeroMoby_00152C00.index * 16, (float)(gScenePlaybackState.frame - 0x78) * (fadeScale * 20.0f));
    D_001ABDD4 = D_001AC150[gHeroMoby_00152C00.index];
    for (i = 0; i < gScenePlaybackState.count; i = nextIndex) {
        TransitionActor *actor;
        int keyIndex, nextKeyIndex;
        float fraction;
        char *keys;
        keyIndex = gScenePlaybackState.tick >> 1;
        actor = (TransitionActor *)gScenePlaybackState.objects[i];
        nextIndex = i + 1;
        fraction = IntToFloat(gScenePlaybackState.tick & 1);
        nextKeyIndex = keyIndex + 1;
        actor->blend = fraction * 0.5f;
        keys = (char *)actor->keys;
        FastVecScale(scratchA, keys + keyIndex * 16, 1.0f - actor->blend);
        FastVecScale(scratchB, keys + nextKeyIndex * 16, actor->blend);
        FastVecAdd(actor->position, scratchA, scratchB);
        {
            char *definition = (char *)actor->definition;
            actor->current_anim = B(definition, 0xC) - 1;
            actor->next_anim = B(definition, 0xC) - 1;
            actor->key = keyIndex;
            actor->next_key = nextKeyIndex;
        }
        update_moby_animation_state(actor);
        actor->draw_flags = 0x1FF;
        if (actor->type == 0xD54 /* moby class 3412 */) {
            if (D_001B2148_first[0] != 0) {
                TransformMobyJointPoint(actor, 0, mobyMatrix);
                {
                    int listIndex = 0;
                    actor->flags = 0;
                    actor->draw_flags = 0;
                    if (D_001B2148_first[0] != 0) {
                        do {
                            int k;
                            B((char *)D_001B2148[listIndex], 0x63) = 0;
                            H((char *)D_001B2148[listIndex], 0x32) = 0x1FF;
                            qcopy((char *)D_001B2148[listIndex] + 0x10, actor->position);
                            for (k = 0; k < 3; k++) {
                                ((MatrixEntity *)D_001B2148[listIndex])->basis[k].x = mobyMatrix[k * 4];
                                ((MatrixEntity *)D_001B2148[listIndex])->basis[k].y = mobyMatrix[k * 4 + 1];
                                ((MatrixEntity *)D_001B2148[listIndex])->basis[k].z = mobyMatrix[k * 4 + 2];
                            }
                            func_002A10E8((void *)D_001B2148[listIndex]);
                            listIndex = listIndex + 1;
                        } while (D_001B2148[listIndex] != 0);
                    }
                }
            } else {
                UpdateEquipmentPieces(gScenePlaybackState.id);
            }
            actor->opacity = 0xE8;
        }
        actor->cached_frame = 0xFF;
        {
            {
                actor->alpha = 0xFF;
            }
        }
        func_002A0F48(actor);
        {
            char *definition = (char *)actor->definition;
            actor->current_anim = B(definition, 0xC) - 1;
            actor->next_anim = B(definition, 0xC) - 1;
            if (gHeroMoby_00152C00.index == 4) {
                int duration = gScenePlaybackState.duration;
                int frame = gScenePlaybackState.frame;
                if (duration - 0x28 < frame) {
                    float scaleFactor = (float)(duration - frame - 4) * 0.027777778f;
                    if (scaleFactor < 0.0f)
                        scaleFactor = 0.0f;
                    actor->scale = F(definition, 0x24) * scaleFactor;
                    D_001ABF10 = scaleFactor;
                    if (D_001B2148_first[0] != 0) {
                        char *entity = (char *)D_001B2148_first[0];
                        F(entity, 0x2C) = F((char *)W(entity, 0x24), 0x24) * scaleFactor;
                    }
                    actor->opacity = (int)(scaleFactor * 232.0f);
                    if (actor->type == 0xD54 /* moby class 3412 */) {
                        if (D_001B2148_first[0] == 0) {
                            int j;
                            gHeroMoby_00152C00.flag = 1;
                            if (gEquipmentPieces[0] != 0) {
                                j = 0;
                                do {
                                    ScaleEntity *entity = gEquipmentPieces[j];
                                    j++;
                                    entity->scale = entity->definition->scale * scaleFactor;
                                } while (gEquipmentPieces[j] != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    UpdateIdleFrameCounters();
    return 0;
}
