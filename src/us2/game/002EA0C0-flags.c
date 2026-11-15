#include "include_asm.h"

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
extern PlaybackState g_hero_moby_default;
extern PlaybackScene g_scene_playback_state;
typedef struct { char pad[0x1A4]; unsigned int pressed; } PlaybackController;
extern PlaybackController g_pad_state;
typedef struct {
    char pad00[0x24];
    int requestedFrame, requestFlags;
    char pad2C[0x40];
    short streamPosition;
    char pad6E[4];
    short mode;
} PlaybackStream;
extern PlaybackStream g_music_state;
typedef struct { char pad[0xB0]; float fieldOfView; } PlaybackScreen;
extern PlaybackScreen D_001B9040;
typedef struct {
    char pad00[0x140];
    float position[4], rotation[4];
    char pad160[0x210];
    float forward[4], right[4], up[4];
} PlaybackCamera;
extern PlaybackCamera g_active_camera;
extern char D_001B4580[], g_hero_state[];
extern char D_00261FE0[], D_001CE4EA[];
extern char D_001A8C30[] __attribute__((sda));
extern char *D_001B1B60[] __attribute__((sda));
extern char *D_001B2148;
extern char *D_001B1C4C[] __attribute__((sda));
extern PlaybackMoby *g_equipment_pieces[];
typedef struct { float x, y, z, w; } PlaybackPoint;
typedef struct { int count; char pad04[0xC]; PlaybackPoint points[1]; } PlaybackCurve;
typedef struct { char pad00[0x10]; unsigned char n10; char pad11[2]; unsigned char n13; char pad14[8]; int a1C[1]; } PlaybackBones;
extern PlaybackCurve *g_path_table[];
extern float g_screen_fade __attribute__((sda));
extern float D_001B15A4 __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern int D_001B1694 __attribute__((sda));
extern int D_001A8B84 __attribute__((sda));
extern int g_current_game_mode __attribute__((sda));
extern unsigned int g_equipment_bits[] __attribute__((sda));
extern short D_0018C31C;
extern float D_001AC1B0[] SDATA(D_001AC1B0);
extern float D_001AC1C0[] SDATA(D_001AC1C0);
extern void game_reset_frame_counters(void), moby_update_visible_objects(void), snd_run_callbacks(void);
extern void stub_empty_3(void), part_update_all(void), gfx_select_packet_buffer_setup(void);
extern void load_select_segment_update_world(int), FadeToBlack(int), UpdateViewContext(void);
extern void moby_mark_spawned(void *), update_moby_animation_state(void *), func_002A0F48(void *);
extern int request_begin_slot(int,int,int,int,int);
extern int request_end_slot(int,int);
extern void mat_get_euler_angles(void *,void *), euler_to_matrix(void *,void *);
extern float coll_probe_ground_height_below(void *,int,float);
extern void transform_vector(void *,void *,void *), FastVecAdd(void *,void *,void *);
extern float FastAddRotations(float,float), IntToFloat(int), fast_subtract_rotations(float,float);
extern void func_00129178(void *), pad_vib_routine_f(void *,void *,float);
extern void pad_vib_routine_g(void *,void *,float), pad_vib_routine_e(void *,void *,float);
extern void FastVecScale(void *,void *,float), moby_run_ground_check(void *);
extern void stub_empty_18(void *), stub_empty_17(void *,int), func_US2_002E72D8(void *);
extern void gfx_register_overlay_draw_callback(void *,void *), gfx_register_world_draw_callback(void *,void *);
extern void render_environment_mapped_object(void), gfx_draw_ground_shadow(void), part_draw_glow_quads(void);
extern float math_fast_sin_or_cos_a(float);
extern void music_Pause(int);
extern s32 UpdateSoundVoices(void);
extern short snd_pump_music_and_disc_read(int);
extern int sceGsSyncV(int);
extern s32 snd_resume_music_stream(void);
extern PlaybackMoby *CreateMoby(int);
extern void SetCamera5Pose(void *,void *,int,int,int);
extern float mat_fast_helper_a(float,float), math_fabs(float);
extern float fast_vec_dist(void *,void *), vec_distance_xy(void *,void *);
extern float math_step_value_toward_target(void *,void *,float,float,float,float);
extern void lerp_vector(void *,void *,void *,float), vec_clear_128(void *);
extern void object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern void copy_matrix3x4(void *,void *), func_002A10E8(void *);
extern void part_spawn_object_sparks(void *,float), ship_spawn_exhaust_puffs(void *);
extern void path_sample_position(void *,int,void *,void *,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_002A1130(void *,int,void *,int);
extern void ship_draw_engine_flames(void *), func_US2_00272378(void), UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void), game_update_idle_frame_counters(void);
extern int func_US2_002E91C0(void);

extern void ref_US2_002EA0C0_00(void), part_update_all(void), gfx_select_packet_buffer_setup(void);
extern void ref_US2_002EA0C0_01(void *), stub_empty_17(void *,int), func_US2_002E72D8(void *);

int func_US2_002EA0C0(void)
{
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float temp[16] __attribute__((aligned(16)));

    int result = 0;

    state->frame++;
    switch (state->mode) {
    case 0:
    case 3:
        game_reset_frame_counters();
        moby_update_visible_objects();
        snd_run_callbacks();
        ref_US2_002EA0C0_00();
        part_update_all();
        scene->streamFrame++;
        scene->frame++;
        {
            int skipIndex, advance, chunkLength;
            for (skipIndex=0; W(D_00261FE0,scene->selected*32 + skipIndex*8)>=0; skipIndex++) {
                if (scene->frame==W(D_00261FE0,scene->selected*32 + skipIndex*8)) {
                    advance=W(D_00261FE0,scene->selected*32 + skipIndex*8+4);
                    chunkLength=g_is_pal_video ? 80 : 96;
                    scene->frame+=advance;
                    scene->streamFrame+=advance;
                    if (scene->streamFrame>=chunkLength) {
                        scene->chunk=scene->frame/chunkLength;
                        load_select_segment_update_world(scene->chunk);
                        scene->streamFrame=scene->frame%chunkLength;
                    }
                    break;
                }
            }
        }
        g_screen_fade-=0.125f;
        if (g_screen_fade<0.0f) g_screen_fade=0.0f;
        {
        int limit, skip;
        limit=g_is_pal_video ? 80 : 96;
        skip=state->skip;
        if ((g_pad_state.pressed&0x9FF) && scene->frame>=13 && g_screen_fade==0.0f && scene->frame<scene->endFrame-30) skip=1;
        if (skip) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            if (state->mode==0) {
                scene->frame=scene->endFrame-30;
                scene->chunk=scene->frame/limit;
                load_select_segment_update_world(scene->chunk);
                scene->streamFrame=scene->frame%limit;
                if (state->skip) state->skip=0;
                else FadeToBlack(4);
                g_screen_fade=1.0f;
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
                g_screen_fade=(scene->frame-j)*0.2f;
                if (g_screen_fade>1.0f) scene->frame=scene->endFrame;
                if (g_screen_fade>1.0f) g_screen_fade=1.0f;
            }
        }
        if (scene->frame>=scene->endFrame) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            gfx_select_packet_buffer_setup();
            D_001B9040.fieldOfView=0.62f;
            UpdateViewContext();
            {
                int cleanupIndex;
                for (cleanupIndex=0;cleanupIndex<scene->objectCount;cleanupIndex++) {
                    PlaybackMoby *object=scene->objects[cleanupIndex];
                    if (object) {
                        object->classData->count--;
                        object->classData->slots[object->classData->count]=0;
                        moby_mark_spawned(object);
                    }
                    if (state->extra) moby_mark_spawned(state->extra);
                }
            }
            state->object->flags&=0xFFFE;
            {
                int resetIndex;
                for (resetIndex=0;g_equipment_pieces[resetIndex];resetIndex++) if (g_equipment_pieces[resetIndex]->mobyState) g_equipment_pieces[resetIndex]->mobyState=8;
            }
            {
                char *p;
                for (p=D_001B1B60[0];B(p,0x20)!=255;p+=0x100) {
                    if (!(B(p,0x20)&0x80) && (H(p,0xAA)==0x4A || H(p,0xAA)==0xCB)) UH(p,0x34)&=0xFF7F;
                }
            }
            if (state->mode==0) {
                if (!request_begin_slot(3,1,4,0,0)) D_001B1694=1;
            } else request_end_slot(0,0);
        } else {
            {
                int chunkLength=g_is_pal_video ? 80 : 96;
                if (scene->streamFrame>=chunkLength) {
                    scene->chunk++;
                    load_select_segment_update_world(scene->chunk);
                }
            }
            mat_get_euler_angles(state->object->matrix,state->object->rotation);
            state->object->rotation[0]=0;
            state->object->rotation[1]=0;
            euler_to_matrix(matrix,state->object->rotation);
            qcopy(point,state->object->position);
            point[2]=coll_probe_ground_height_below(point,0,0.5f);
            {
            char *key, *rotation;
            int last, i;
            float angle;
            key=scene->keys+scene->streamFrame*32;
            last=B(key,0xC);
            rotation=key+0x10;
            D_001B9040.fieldOfView=F(rotation,0xC);
            UpdateViewContext();
            qcopy(g_active_camera.position,key);
            transform_vector(g_active_camera.position,g_active_camera.position,matrix);
            FastVecAdd(g_active_camera.position,g_active_camera.position,point);
            angle=FastAddRotations(F(rotation,8),state->object->rotation[2]);
            func_00129178(temp);
            pad_vib_routine_f(temp,temp,F(key,0x10));
            pad_vib_routine_g(temp,temp,F(rotation,4));
            pad_vib_routine_e(temp,temp,angle);
            g_active_camera.forward[0]=-temp[8]; g_active_camera.right[0]=-temp[0]; g_active_camera.up[0]=temp[4];
            g_active_camera.forward[1]=-temp[9]; g_active_camera.right[1]=-temp[1]; g_active_camera.up[1]=temp[5];
            g_active_camera.forward[2]=-temp[10]; g_active_camera.right[2]=-temp[2]; g_active_camera.up[2]=temp[6];
            {
                for (i=0;i<scene->objectCount;i++) {
                    char *p;
                    PlaybackMoby *object=scene->objects[i];
                    int half=scene->streamFrame>>1;
                    object->frame=half;
                    object->nextFrame=half+1;
                    update_moby_animation_state(object);
                    object->animTime=IntToFloat(scene->streamFrame&1)*0.5f;
                    if (last && (scene->streamFrame&1)) object->animTime=1.0f;
                    p=object->keys;
                    FastVecScale(temp,p+object->frame*16,1.0f-object->animTime);
                    FastVecScale(temp+4,p+object->nextFrame*16,object->animTime);
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
                    if (object->shadowRange) moby_run_ground_check(object);
                    if (object->classId==10) ref_US2_002EA0C0_01(object);
                    if (object->classId==0) stub_empty_17(object,0);
                    if (object->classId==0xD54) {
                        PlaybackMoby *p;
                        int j, cast;
                        object->mobyState=4;
                        func_US2_002E72D8(object);
                        if (!D_001B2148 || H(D_001B2148,0xAA)==0xD54) gfx_register_overlay_draw_callback(render_environment_mapped_object,object);
                        gfx_register_world_draw_callback(gfx_draw_ground_shadow,object);
                        p=0;
                        j=H(D_001A8C30,((g_equipment_bits[0]>>3)&2));
                        for(cast=0;g_equipment_pieces[cast];cast++) {
                            if(g_equipment_pieces[cast]->mobyState>=5) g_equipment_pieces[cast]->mobyState=4;
                            if(j==g_equipment_pieces[cast]->classId) {p=g_equipment_pieces[cast];break;}
                        }
                        if(p) {
                            if(state->mode==0) {
                                int offset,color;
                                offset=D_0018C31C ? 144 : -18;
                                if(scene->frame<504-offset) {
                                    color=(int)((scene->frame-(360.0f-offset))*1.5f);
                                    if(color>255) color=255;
                                    if(color<0) color=0;
                                    p->color=color | (color<<8) | (color<<16);
                                    if(scene->frame>420-offset) {
                                        object->effectScale=(int)((scene->frame-(420.0f-offset))*1.2f);
                                        object->partFlags=0;
                                        gfx_register_world_draw_callback(part_draw_glow_quads,object);
                                    }
                                    if(scene->frame>464-offset) {
                                        D_001B15A4+=0.027f;
                                        if(D_001B15A4>1.0f) D_001B15A4=1.0f;
                                    }
                                } else {
                                    p->color=0xA0A0A0;
                                    D_001B15A4-=0.027f;
                                    if(D_001B15A4<0.0f) D_001B15A4=0.0f;
                                }
                            } else {
                                if(scene->frame<150) {
                                    int color=((150-scene->frame)*255)/150;
                                    p->color=color|(color<<8)|(color<<16);
                                } else {
                                    int color=(int)(math_fast_sin_or_cos_a(IntToFloat((scene->frame&63)-32)*0.09817477f)*80.0f)+120;
                                    p->color=color|(color<<8)|(color<<16);
                                }
                            }
                        }
                    }
                }
            }
            }
            UpdateSoundVoices();
            UpdateLightingEnvironment();
            gfx_compute_light_direction();
            game_update_idle_frame_counters();
        }
        break;
    case 1:
        game_reset_frame_counters();
        moby_update_visible_objects();
        snd_run_callbacks();
        ref_US2_002EA0C0_00();
        part_update_all();
        if (state->frame==0) {
            music_Pause(0);
            snd_pump_music_and_disc_read(0);
            g_music_state.requestedFrame=0x138E;
            g_music_state.requestFlags=0;
            while (g_music_state.mode!=3 || g_music_state.streamPosition>=6000) {
                UpdateSoundVoices();
                sceGsSyncV(0);
            }
            snd_resume_music_stream();
            state->object->opacity=255;
            state->object->updateState=0;
            if (state->curveIndex>=0) {
                char *global;
                state->hero=CreateMoby(0);
                global=g_hero_state;
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
            SetCamera5Pose(g_active_camera.position,g_active_camera.rotation,1,0,0);
            state->cameraBlend=0;
            state->cameraVelocity=0;
            if (state->curveIndex>=0) {
                char *curve;
                float maximum, angle, factor;
                curve=(char *)g_path_table[state->curveIndex];
                maximum=state->cameraBlend;
                {
                    int pathIndex;
                    for (pathIndex=1;pathIndex<W(curve,0)-1;pathIndex++) {
                        char *point=curve+pathIndex*16;
                        {
                            char *previous=curve+(pathIndex-1)*16;
                            angle=mat_fast_helper_a(F(point,0x10)-F(previous,0x10),F(point,0x14)-F(previous,0x14));
                        }
                        {
                            char *next=curve+(pathIndex+1)*16;
                            factor=mat_fast_helper_a(F(next,0x10)-F(point,0x10),F(next,0x14)-F(point,0x14));
                        }
                        F(point,0x1C)=fast_subtract_rotations(angle,factor);
                        if(maximum<math_fabs(F(point,0x1C))) maximum=math_fabs(F(point,0x1C));
                    }
                }
                F(curve,0x1C)=F(curve,0x2C);
                {
                    char *last=curve+(W(curve,0)-1)*16;
                    char *previous=curve+(W(curve,0)-2)*16;
                    angle=mat_fast_helper_a(F(last,0x10)-F(previous,0x10),F(last,0x14)-F(previous,0x14));
                }
                {
                    char *last=curve+(W(curve,0)-1)*16;
                    factor=mat_fast_helper_a(F(curve,0x10)-F(last,0x10),F(curve,0x14)-F(last,0x14));
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
                state->endRotation[1]=mat_fast_helper_a(angle,F(curve,0x18)-F(curve,0x28));
                state->endRotation[2]=mat_fast_helper_a(F(curve,0x20)-F(curve,0x10),F(curve,0x24)-F(curve,0x14));
            }
        }
        if (state->cameraStart>=0 && state->cameraEnd>=0) {
            float angle;
            math_step_value_toward_target(&state->cameraBlend,&state->cameraVelocity,1.0f,0.00018500001f,0.00018500001f,0.008333334f);
            lerp_vector(matrix,D_001B1C4C[0]+state->cameraStart*128+0x30,D_001B1C4C[0]+state->cameraEnd*128+0x30,state->cameraBlend);
            vec_clear_128(matrix+4);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+state->cameraEnd*128,0x74),F(D_001B1C4C[0]+state->cameraStart*128,0x74));
            matrix[5]=angle*state->cameraBlend;
            matrix[5]=FastAddRotations(F(D_001B1C4C[0]+state->cameraStart*128,0x74),matrix[5]);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+state->cameraEnd*128,0x78),F(D_001B1C4C[0]+state->cameraStart*128,0x78));
            matrix[6]=angle*state->cameraBlend;
            matrix[6]=FastAddRotations(F(D_001B1C4C[0]+state->cameraStart*128,0x78),matrix[6]);
            object_copy_vector_to_selected(matrix);
            cam_set_state_rotation(matrix+4);
        }
        if (state->curveIndex>=0) {
            char *p;
            PlaybackBones *bones;
            int *table;
            if (state->frame<120) {
                float angle, factor, blend;
                angle=IntToFloat(state->frame);
                factor=IntToFloat(90);
                blend=(1.0f-math_fast_sin_or_cos_a(angle*(3.1415927f/factor)))*0.5f;
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
                if(g_screen_fade>0.0f) {
                    g_screen_fade-=0.125f;
                    if(g_screen_fade<0.0f) g_screen_fade=0.0f;
                }
                state->object->effectOpacity=(unsigned short)state->frame>>2;
                if(blend<1.0f) part_spawn_object_sparks(state->object,-0.0625f);
            } else {
                PlaybackCurve *curve;
                float step;
                curve=g_path_table[state->curveIndex];
                state->speed+=0.8f;
                if(state->speed>100.0f) state->speed=100.0f;
                if((g_pad_state.pressed&0x50) && g_screen_fade<0.1f) g_screen_fade=0.1f;
                step=state->speed*(1.0f/60.0f)/state->length;
                if((float)curve->count-step*12.0f<state->progress && g_screen_fade<0.1f) g_screen_fade=0.1f;
                if(g_screen_fade>0.0f) {
                    g_screen_fade+=0.1f;
                    if(g_screen_fade>1.0f) g_screen_fade=1.0f;
                }
                if(state->object->effectOpacity<160) state->object->effectOpacity+=8;
                state->progress+=step;
                ship_spawn_exhaust_puffs(state->object);
                if(state->progress>(float)(curve->count-1) || g_screen_fade>=1.0f) D_001A8B84=1;
                else {
                    path_sample_position(curve,1,state->object->position,state->object->rotation,0,state->progress);
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
            p=state->hero->classData;
            bones=(PlaybackBones *)P(p,0x48);
            table=&bones->a1C[bones->n10];
            func_002A1130(table+bones->n13,bones->a1C[0],D_001B4580,B(p,8));
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
            g_screen_fade=1.0f;
        }
        func_US2_002E72D8(state->object);
        gfx_register_overlay_draw_callback(ship_draw_engine_flames,state->object);
        func_US2_00272378();
        UpdateSoundVoices();
        UpdateLightingEnvironment();
        gfx_compute_light_direction();
        game_update_idle_frame_counters();
        break;
    case 2:
        g_current_game_mode=6;
        result=func_US2_002E91C0();
        break;
    }
    return result;
}


