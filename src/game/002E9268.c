#include "common.h"

#define scene (&D_001B8840)
#define state (&D_00152C00)
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define UH(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad00[0xC];
    unsigned char count;
    char pad0D[0x3B];
    int slots[1];
} PlaybackClass;
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char status;
    char pad21[3];
    PlaybackClass *classData;
    char pad28[0xA];
    short drawDistance;
    unsigned short flags;
    char pad36[2];
    unsigned long long colorData;
    unsigned char frame, nextFrame;
    char pad42[2];
    float animTime;
    char pad48[0x10];
    char *joints, *previousJoints;
    unsigned char pad60, animId, opacity, mobyState;
    char pad64[4];
    char *keys;
    char pad6C[3];
    unsigned char shadowRange;
    char pad70[8];
    unsigned int color;
    char pad7C[0x19];
    unsigned char effectOpacity;
    char pad96[2];
    int updateState;
    char pad9C[0xE];
    short classId;
    char padAC[6];
    short partFlags;
    char padB4[8];
    unsigned char effectScale;
    char padBD[3];
    float matrix[12];
    float rotation[4];
} PlaybackMoby;
typedef struct {
    PlaybackMoby *object;
    char pad04[4];
    PlaybackMoby *extra;
    char pad0C[4];
    PlaybackMoby *hero;
    PlaybackMoby *companion;
    char pad18[8];
    short mode, frame;
    short unused24, skip;
    char pad28[0x18];
    int curveIndex, cameraStart, cameraEnd;
    float progress, speed, length, cameraBlend, cameraVelocity;
    char pad60[0xC];
    int fadeStart;
    char pad70[0x20];
    float startPosition[4], endPosition[4], startRotation[4], endRotation[4];
} PlaybackState;
typedef struct {
    char pad00[0x30];
    int selected, frame, streamFrame, chunk;
    short endFrame, unused42, objectCount;
    char pad46[0x22];
    char *keys;
    char pad6C[0x120];
    PlaybackMoby *objects[0];
} PlaybackScene;
extern PlaybackState D_00152C00;
extern PlaybackScene D_001B8840;
typedef struct { char pad[0x1A4]; unsigned int pressed; } PlaybackController;
extern PlaybackController D_00138180;
typedef struct {
    char pad00[0x24];
    int requestedFrame, requestFlags;
    char pad2C[0x40];
    short streamPosition;
    char pad6E[4];
    short mode;
} PlaybackStream;
extern PlaybackStream D_001A63A8;
typedef struct { char pad[0xB0]; float fieldOfView; } PlaybackScreen;
extern PlaybackScreen D_001B9040;
typedef struct {
    char pad00[0x140];
    float position[4], rotation[4];
    char pad160[0x210];
    float forward[4], right[4], up[4];
} PlaybackCamera;
extern PlaybackCamera D_001B5200;
extern char D_001B4580[], D_00189E20[];
extern char D_00261FE0[], D_001CE4EA[];
extern char D_001A8C30[] __attribute__((sda));
extern char *D_001B1B60[] __attribute__((sda));
extern char *D_001B2148;
extern char *D_001B1C4C[] __attribute__((sda));
extern PlaybackMoby *D_00214920[];
typedef struct { float x, y, z, w; } PlaybackPoint;
typedef struct { int count; char pad04[0xC]; PlaybackPoint points[1]; } PlaybackCurve;
typedef struct { char pad00[0x10]; unsigned char n10; char pad11[2]; unsigned char n13; char pad14[8]; int a1C[1]; } PlaybackBones;
extern PlaybackCurve *D_001F1700[];
extern float D_001B15A0 __attribute__((sda));
extern float D_001B15A4 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001B1694 __attribute__((sda));
extern int D_001A8B84 __attribute__((sda));
extern int D_001A8BB0 __attribute__((sda));
extern unsigned int D_001A7AF0[] __attribute__((sda));
extern short D_0018C31C;
extern float D_001AC1B0[] SDATA(D_001AC1B0);
extern float D_001AC1C0[] SDATA(D_001AC1C0);
extern void func_002F5220(void), func_002B6658(void), func_002E5F60(void);
extern void func_0026F718(void), func_002B9390(void), func_002FC138(void);
extern void func_00294070(int), func_0027D330(int), func_0027AB40(void);
extern void func_0029F338(void *), func_0029F390(void *), func_002A0F48(void *);
extern int func_002B49E0(int,int,int,int,int);
extern void func_002B4B70(int,int);
extern void func_002AB6D8(void *,void *), func_00283410(void *,void *);
extern float func_002A89A8(void *,int,float);
extern void func_002830C0(void *,void *,void *), func_00282CC0(void *,void *,void *);
extern float func_00283B98(float,float), func_00283CE0(int), func_00283BE0(float,float);
extern void func_00129178(void *), func_001292C0(void *,void *,float);
extern void func_00129368(void *,void *,float), func_00129218(void *,void *,float);
extern void func_00282D30(void *,void *,float), func_002A9548(void *);
extern void func_0026F790(void *), func_0026F788(void *,int), func_002E64A0(void *);
extern void func_0027CFD0(void *,void *), func_0027CDC8(void *,void *);
extern void func_002ECB70(void), func_002E6B78(void), func_002E7338(void);
extern float func_00283180(float);
extern void func_002B72E8(int), func_002E4AC8(void);
extern short func_002B7CE0(int);
extern int func_001261F0(int);
extern void func_002B6D28(void);
extern PlaybackMoby *func_0029EFD0(int);
extern void func_00335438(void *,void *,int,int,int);
extern float func_00283248(float,float), func_00282C48(float);
extern float func_00282E48(void *,void *), func_00282E80(void *,void *);
extern void func_002AA548(void *,void *,float,float,float,float);
extern void func_00282D08(void *,void *,void *,float), func_00282C88(void *);
extern void func_00335370(void *), func_003353C8(void *);
extern void func_00283678(void *,void *), func_002A10E8(void *);
extern void func_002E8F80(void *,float), func_002E9110(void *);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_002A1130(void *,int,void *,int);
extern void func_002E7B48(void *), func_00272368(void), func_002914B8(void);
extern void func_0029FFB8(void), func_002F52B8(void);
extern int func_002E8368(void);

/* Runs one frame of a story cutscene: moves the camera and every actor along their paths, handles skipping and fades, and ends the scene. */
int func_002E9268(void)
{
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float temp[16] __attribute__((aligned(16)));

    int result = 0;

    state->frame++;
    switch (state->mode) {
    case 0:
    case 3:
        ResetFrameCounters();
        UpdateVisibleObjects();
        RunSoundCallbacks();
        EmptyStubF718();
        UpdateParticles();
        scene->streamFrame++;
        scene->frame++;
        {
            int skipIndex, advance, chunkLength;
            for (skipIndex=0; W(D_00261FE0,scene->selected*32 + skipIndex*8)>=0; skipIndex++) {
                if (scene->frame==W(D_00261FE0,scene->selected*32 + skipIndex*8)) {
                    advance=W(D_00261FE0,scene->selected*32 + skipIndex*8+4);
                    chunkLength=gIsPalVideo ? 80 : 96;
                    scene->frame+=advance;
                    scene->streamFrame+=advance;
                    if (scene->streamFrame>=chunkLength) {
                        scene->chunk=scene->frame/chunkLength;
                        SelectSegmentAndUpdateWorld(scene->chunk);
                        scene->streamFrame=scene->frame%chunkLength;
                    }
                    break;
                }
            }
        }
        gScreenFade-=0.125f;
        if (gScreenFade<0.0f) gScreenFade=0.0f;
        {
        int limit, skip;
        limit=gIsPalVideo ? 80 : 96;
        skip=state->skip;
        if ((gPadState.pressed&0x9FF) && scene->frame>=13 && gScreenFade==0.0f && scene->frame<scene->endFrame-30) skip=1;
        if (skip) {
            if ((unsigned short)((unsigned short)gMusicState.mode-6)>=2) gMusicState.mode=5;
            if (state->mode==0) {
                scene->frame=scene->endFrame-30;
                scene->chunk=scene->frame/limit;
                SelectSegmentAndUpdateWorld(scene->chunk);
                scene->streamFrame=scene->frame%limit;
                if (state->skip) state->skip=0;
                else FadeToBlack(4);
                gScreenFade=1.0f;
            } else {
                if (state->skip) state->skip=0;
                if (scene->frame<5) state->fadeStart=-5;
                else state->fadeStart=scene->frame-1;
            }
        }
        }
        if (state->mode==3) {
            int j;
            j=state->fadeStart;
            if (j==0) j=scene->endFrame-6;
            if (scene->frame>=j) {
                gScreenFade=(scene->frame-j)*0.2f;
                if (gScreenFade>1.0f) scene->frame=scene->endFrame;
                if (gScreenFade>1.0f) gScreenFade=1.0f;
            }
        }
        if (scene->frame>=scene->endFrame) {
            if ((unsigned short)((unsigned short)gMusicState.mode-6)>=2) gMusicState.mode=5;
            SelectPacketBufferSetup();
            D_001B9040.fieldOfView=0.62f;
            UpdateViewContext();
            {
                int cleanupIndex;
                for (cleanupIndex=0;cleanupIndex<scene->objectCount;cleanupIndex++) {
                    PlaybackMoby *object=scene->objects[cleanupIndex];
                    if (object) {
                        object->classData->count--;
                        object->classData->slots[object->classData->count]=0;
                        MarkMobySpawned(object);
                    }
                    if (state->extra) MarkMobySpawned(state->extra);
                }
            }
            state->object->flags&=0xFFFE;
            {
                int resetIndex;
                for (resetIndex=0;gEquipmentPieces[resetIndex];resetIndex++) if (gEquipmentPieces[resetIndex]->mobyState) gEquipmentPieces[resetIndex]->mobyState=8;
            }
            {
                char *scanMoby;
                for (scanMoby=D_001B1B60[0];B(scanMoby,0x20)!=255;scanMoby+=0x100) {
                    if (!(B(scanMoby,0x20)&0x80) && (H(scanMoby,0xAA)==0x4A /* moby class 74 */ || H(scanMoby,0xAA)==0xCB /* Decoy */)) UH(scanMoby,0x34)&=0xFF7F;
                }
            }
            if (state->mode==0) {
                if (!BeginSlotRequest(3,1,4,0,0)) D_001B1694=1;
            } else EndSlotRequest(0,0);
        } else {
            {
                int chunkLength=gIsPalVideo ? 80 : 96;
                if (scene->streamFrame>=chunkLength) {
                    scene->chunk++;
                    SelectSegmentAndUpdateWorld(scene->chunk);
                }
            }
            GetEulerAnglesFromMatrix(state->object->matrix,state->object->rotation);
            state->object->rotation[0]=0;
            state->object->rotation[1]=0;
            euler_to_matrix(matrix,state->object->rotation);
            qcopy(point,state->object->position);
            point[2]=ProbeGroundHeightBelow(point,0,0.5f);
            {
            char *key, *rotation;
            int last, i;
            float angle;
            key=scene->keys+scene->streamFrame*32;
            last=B(key,0xC);
            rotation=key+0x10;
            D_001B9040.fieldOfView=F(rotation,0xC);
            UpdateViewContext();
            qcopy(gActiveCamera.position,key);
            transform_vector(gActiveCamera.position,gActiveCamera.position,matrix);
            FastVecAdd(gActiveCamera.position,gActiveCamera.position,point);
            angle=FastAddRotations(F(rotation,8),state->object->rotation[2]);
            func_00129178(temp);
            SceVibRoutine1292C0(temp,temp,F(key,0x10));
            SceVibRoutine129368(temp,temp,F(rotation,4));
            SceVibRoutine129218(temp,temp,angle);
            gActiveCamera.forward[0]=-temp[8]; gActiveCamera.right[0]=-temp[0]; gActiveCamera.up[0]=temp[4];
            gActiveCamera.forward[1]=-temp[9]; gActiveCamera.right[1]=-temp[1]; gActiveCamera.up[1]=temp[5];
            gActiveCamera.forward[2]=-temp[10]; gActiveCamera.right[2]=-temp[2]; gActiveCamera.up[2]=temp[6];
            {
                for (i=0;i<scene->objectCount;i++) {
                    char *keyTable;
                    PlaybackMoby *object=scene->objects[i];
                    int half=scene->streamFrame>>1;
                    object->frame=half;
                    object->nextFrame=half+1;
                    update_moby_animation_state(object);
                    object->animTime=IntToFloat(scene->streamFrame&1)*0.5f;
                    if (last && (scene->streamFrame&1)) object->animTime=1.0f;
                    keyTable=object->keys;
                    FastVecScale(temp,keyTable+object->frame*16,1.0f-object->animTime);
                    FastVecScale(temp+4,keyTable+object->nextFrame*16,object->animTime);
                    FastVecAdd(object->position,temp,temp+4);
                    transform_vector(object->position,object->position,matrix);
                    FastVecAdd(object->position,object->position,point);
                    object->rotation[2]=state->object->rotation[2];
                    object->animId=255;
                    func_002A0F48(object);
                    if (object->classId==0) {
                        object->shadowRange=0;
                        if (state->mode==0) {
                            if (scene->frame<87) object->shadowRange=24;
                        } else {
                            if (scene->frame>=171) object->shadowRange=24;
                        }
                    } else if (object->classId==10) {
                        object->shadowRange=0;
                        if (state->mode==0) { if (scene->frame<335) object->shadowRange=24; }
                        else if (scene->frame>=209) object->shadowRange=24;
                    }
                    if (object->shadowRange) RunMobyGroundCheck(object);
                    if (object->classId==10) EmptyStubF790(object);
                    if (object->classId==0) EmptyStubF788(object,0);
                    if (object->classId==0xD54 /* moby class 3412 */) {
                        PlaybackMoby *castMoby;
                        int j, cast;
                        object->mobyState=4;
                        UpdateEquipmentPieces(object);
                        if (!D_001B2148 || H(D_001B2148,0xAA)==0xD54 /* moby class 3412 */) RegisterOverlayDrawCallback(render_environment_mapped_object,object);
                        RegisterWorldDrawCallback(DrawGroundShadowQuad,object);
                        castMoby=0;
                        j=H(D_001A8C30,((gEquipmentBits[0]>>3)&2));
                        for(cast=0;gEquipmentPieces[cast];cast++) {
                            if(gEquipmentPieces[cast]->mobyState>=5) gEquipmentPieces[cast]->mobyState=4;
                            if(j==gEquipmentPieces[cast]->classId) {castMoby=gEquipmentPieces[cast];break;}
                        }
                        if(castMoby) {
                            if(state->mode==0) {
                                int offset,color;
                                offset=D_0018C31C ? 144 : -18;
                                if(scene->frame<504-offset) {
                                    color=(int)((scene->frame-(360.0f-offset))*1.5f);
                                    if(color>255) color=255;
                                    if(color<0) color=0;
                                    castMoby->color=color | (color<<8) | (color<<16);
                                    if(scene->frame>420-offset) {
                                        object->effectScale=(int)((scene->frame-(420.0f-offset))*1.2f);
                                        object->partFlags=0;
                                        RegisterWorldDrawCallback(DrawGlowQuadsAroundObject,object);
                                    }
                                    if(scene->frame>464-offset) {
                                        D_001B15A4+=0.027f;
                                        if(D_001B15A4>1.0f) D_001B15A4=1.0f;
                                    }
                                } else {
                                    castMoby->color=0xA0A0A0;
                                    D_001B15A4-=0.027f;
                                    if(D_001B15A4<0.0f) D_001B15A4=0.0f;
                                }
                            } else {
                                if(scene->frame<150) {
                                    int color=((150-scene->frame)*255)/150;
                                    castMoby->color=color|(color<<8)|(color<<16);
                                } else {
                                    int color=(int)(FastSinOrCosA(IntToFloat((scene->frame&63)-32)*0.09817477f)*80.0f)+120;
                                    castMoby->color=color|(color<<8)|(color<<16);
                                }
                            }
                        }
                    }
                }
            }
            }
            UpdateSoundVoices();
            UpdateLightingEnvironment();
            ComputeLightDirection();
            UpdateIdleFrameCounters();
        }
        break;
    case 1:
        ResetFrameCounters();
        UpdateVisibleObjects();
        RunSoundCallbacks();
        EmptyStubF718();
        UpdateParticles();
        if (state->frame==0) {
            music_Pause(0);
            PumpMusicAndDiscRead(0);
            gMusicState.requestedFrame=0x138E;
            gMusicState.requestFlags=0;
            while (gMusicState.mode!=3 || gMusicState.streamPosition>=6000) {
                UpdateSoundVoices();
                GetGsCurrentField(0);
            }
            ResumeMusicStream();
            state->object->opacity=255;
            state->object->updateState=0;
            if (state->curveIndex>=0) {
                char *global;
                state->hero=CreateMoby(0);
                global=gHeroState;
                state->hero->drawDistance=0x1FF;
                state->hero->opacity=255;
                state->hero->updateState=0;
                state->hero->flags|=6;
                state->hero->colorData=*(unsigned long long *)(P(global,0x2290)+0x38);
                if (B(D_001CE4EA,0)!=255 && H(global,0x24FC)==0) {
                    state->companion=CreateMoby(10);
                    state->companion->drawDistance=0x1FF;
                    state->companion->opacity=255;
                    state->companion->updateState=0;
                    state->companion->flags|=6;
                    state->companion->colorData=*(unsigned long long *)(P(global,0x2290)+0x38);
                } else state->companion=0;
            }
            SetCamera5Pose(gActiveCamera.position,gActiveCamera.rotation,1,0,0);
            state->cameraBlend=0;
            state->cameraVelocity=0;
            if (state->curveIndex>=0) {
                char *curve;
                float maximum, angle, factor;
                curve=(char *)gPathTable_001F1700[state->curveIndex];
                maximum=state->cameraBlend;
                {
                    int pathIndex;
                    for (pathIndex=1;pathIndex<W(curve,0)-1;pathIndex++) {
                        char *point=curve+pathIndex*16;
                        {
                            char *previous=curve+(pathIndex-1)*16;
                            angle=FastMatrixHelperA(F(point,0x10)-F(previous,0x10),F(point,0x14)-F(previous,0x14));
                        }
                        {
                            char *next=curve+(pathIndex+1)*16;
                            factor=FastMatrixHelperA(F(next,0x10)-F(point,0x10),F(next,0x14)-F(point,0x14));
                        }
                        F(point,0x1C)=fast_subtract_rotations(angle,factor);
                        if(maximum<FloatAbs(F(point,0x1C))) maximum=FloatAbs(F(point,0x1C));
                    }
                }
                F(curve,0x1C)=F(curve,0x2C);
                {
                    char *last=curve+(W(curve,0)-1)*16;
                    char *previous=curve+(W(curve,0)-2)*16;
                    angle=FastMatrixHelperA(F(last,0x10)-F(previous,0x10),F(last,0x14)-F(previous,0x14));
                }
                {
                    char *last=curve+(W(curve,0)-1)*16;
                    factor=FastMatrixHelperA(F(curve,0x10)-F(last,0x10),F(curve,0x14)-F(last,0x14));
                }
                angle=fast_subtract_rotations(factor,angle);
                factor=0.22689283f/maximum;
                {
                    char *last=curve+(W(curve,0)-1)*16;
                    F(last,0x1C)=angle;
                }
                {
                    int scaleIndex;
                    for(scaleIndex=0;scaleIndex<W(curve,0);scaleIndex++) F(curve+scaleIndex*16,0x1C)*=factor;
                }
                {
                    int rampIndex;
                    for(rampIndex=0;rampIndex<20;rampIndex++) F(curve+rampIndex*16,0x1C)=F(curve+rampIndex*16,0x1C)*0.05f*rampIndex;
                }
                state->length=fast_vec_dist(curve+0x10,curve+0x20);
                state->progress=0;
                state->speed=0;
                /* These copies do not overlap the state pointer/length fields. */
                qcopy_nc(state->startPosition,state->object->position);
                qcopy_nc(state->endPosition,curve+0x10);
                qcopy_nc(state->startRotation,state->object->rotation);
                state->endRotation[0]=F(curve,0x1C);
                angle=vec_distance_xy(curve+0x20,curve+0x10);
                state->endRotation[1]=FastMatrixHelperA(angle,F(curve,0x18)-F(curve,0x28));
                state->endRotation[2]=FastMatrixHelperA(F(curve,0x20)-F(curve,0x10),F(curve,0x24)-F(curve,0x14));
            }
        }
        if (state->cameraStart>=0 && state->cameraEnd>=0) {
            float angle;
            StepValueTowardTarget(&state->cameraBlend,&state->cameraVelocity,1.0f,0.00018500001f,0.00018500001f,0.008333334f);
            lerp_vector(matrix,D_001B1C4C[0]+state->cameraStart*128+0x30,D_001B1C4C[0]+state->cameraEnd*128+0x30,state->cameraBlend);
            ClearVector128(matrix+4);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+state->cameraEnd*128,0x74),F(D_001B1C4C[0]+state->cameraStart*128,0x74));
            matrix[5]=angle*state->cameraBlend;
            matrix[5]=FastAddRotations(F(D_001B1C4C[0]+state->cameraStart*128,0x74),matrix[5]);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+state->cameraEnd*128,0x78),F(D_001B1C4C[0]+state->cameraStart*128,0x78));
            matrix[6]=angle*state->cameraBlend;
            matrix[6]=FastAddRotations(F(D_001B1C4C[0]+state->cameraStart*128,0x78),matrix[6]);
            CopyVectorToSelectedObject(matrix);
            SetCameraStateRotation(matrix+4);
        }
        if (state->curveIndex>=0) {
            char *classData;
            PlaybackBones *bones;
            int *table;
            if (state->frame<120) {
                float angle, factor, blend;
                angle=IntToFloat(state->frame);
                factor=IntToFloat(90);
                blend=(1.0f-FastSinOrCosA(angle*(3.1415927f/factor)))*0.5f;
                if(state->frame>=90) blend=1.0f;
                lerp_vector(state->object->position,state->startPosition,state->endPosition,blend);
                state->object->rotation[0]=state->endRotation[0]*blend;
                angle=fast_subtract_rotations(state->endRotation[1],state->startRotation[1]);
                state->object->rotation[1]=FastAddRotations(state->startRotation[1],angle*blend);
                angle=fast_subtract_rotations(state->endRotation[2],state->startRotation[2]);
                state->object->rotation[2]=FastAddRotations(state->startRotation[2],angle*blend);
                euler_to_matrix(matrix,state->object->rotation);
                copy_matrix3x4(state->object->matrix,matrix);
                func_002A10E8(state->object);
                if(gScreenFade>0.0f) {
                    gScreenFade-=0.125f;
                    if(gScreenFade<0.0f) gScreenFade=0.0f;
                }
                state->object->effectOpacity=(unsigned short)state->frame>>2;
                if(blend<1.0f) SpawnObjectSparks(state->object,-0.0625f);
            } else {
                PlaybackCurve *curve;
                float step;
                curve=gPathTable_001F1700[state->curveIndex];
                state->speed+=0.8f;
                if(state->speed>100.0f) state->speed=100.0f;
                if((gPadState.pressed&0x50) && gScreenFade<0.1f) gScreenFade=0.1f;
                step=state->speed*(1.0f/60.0f)/state->length;
                if((float)curve->count-step*12.0f<state->progress && gScreenFade<0.1f) gScreenFade=0.1f;
                if(gScreenFade>0.0f) {
                    gScreenFade+=0.1f;
                    if(gScreenFade>1.0f) gScreenFade=1.0f;
                }
                if(state->object->effectOpacity<160) state->object->effectOpacity+=8;
                state->progress+=step;
                SpawnShipExhaustPuffs(state->object);
                if(state->progress>(float)(curve->count-1) || gScreenFade>=1.0f) D_001A8B84=1;
                else {
                    SamplePathPosition(curve,1,state->object->position,state->object->rotation,0,state->progress);
                    state->object->rotation[0]=state->object->rotation[3];
                    euler_to_matrix(matrix,state->object->rotation);
                    copy_matrix3x4(state->object->matrix,matrix);
                    func_002A10E8(state->object);
                }
            }
            qcopy_nc(state->hero->rotation,state->object->rotation);
            matrix_mul_vec3(state->hero->position,D_001AC1B0,state->object->matrix);
            FastVecAdd(state->hero->position,state->hero->position,state->object->position);
            func_002A0F48(state->hero);
            classData=state->hero->classData;
            bones=(PlaybackBones *)P(classData,0x48);
            table=&bones->a1C[bones->n10];
            func_002A1130(table+bones->n13,bones->a1C[0],D_001B4580,B(classData,8));
            state->hero->joints=D_001B4580;
            state->hero->previousJoints=D_001B4580;
            if(state->companion) {
                qcopy_nc(state->companion->rotation,state->object->rotation);
                matrix_mul_vec3(state->companion->position,D_001AC1C0,state->object->matrix);
                FastVecAdd(state->companion->position,state->companion->position,state->object->position);
                func_002A0F48(state->companion);
            }
        } else {
            D_001A8B84=1;
            gScreenFade=1.0f;
        }
        UpdateEquipmentPieces(state->object);
        RegisterOverlayDrawCallback(DrawShipEngineFlames,state->object);
        UpdateCameraState();
        UpdateSoundVoices();
        UpdateLightingEnvironment();
        ComputeLightDirection();
        UpdateIdleFrameCounters();
        break;
    case 2:
        gCurrentGameMode=6;
        result=UpdateTransitionScene();
        break;
    }
    return result;
}
