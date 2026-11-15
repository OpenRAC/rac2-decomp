/* func_PAL_002EA0B0, the PAL copy of func_002E9268: the same C, where frame counts, the skip table
   and the offset thresholds take the 50 Hz scale, step sizes take its inverse, and the callees
   func_0026F718/F788/F790 become their PAL neighbours func_0026F720/F790/F798. */
#include "common.h"

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
extern void request_end_slot(int,int);
extern void mat_get_euler_angles(void *,void *), euler_to_matrix(void *,void *);
extern float coll_probe_ground_height_below(void *,int,float);
extern void transform_vector(void *,void *,void *), FastVecAdd(void *,void *,void *);
extern float FastAddRotations(float,float), IntToFloat(int), fast_subtract_rotations(float,float);
extern void func_00129178(void *), pad_vib_routine_f(void *,void *,float);
extern void pad_vib_routine_g(void *,void *,float), pad_vib_routine_e(void *,void *,float);
extern void FastVecScale(void *,void *,float), moby_run_ground_check(void *);
extern void stub_empty_18(void *), stub_empty_17(void *,int), UpdateEquipmentPieces(void *);
extern void gfx_register_overlay_draw_callback(void *,void *), gfx_register_world_draw_callback(void *,void *);
extern void render_environment_mapped_object(void), gfx_draw_ground_shadow(void), part_draw_glow_quads(void);
extern float math_fast_sin_or_cos_a(float);
extern void music_Pause(int), UpdateSoundVoices(void);
extern short snd_pump_music_and_disc_read(int);
extern int sceGsSyncV(int);
extern void snd_resume_music_stream(void);
extern PlaybackMoby *CreateMoby(int);
extern void SetCamera5Pose(void *,void *,int,int,int);
extern float mat_fast_helper_a(float,float), math_fabs(float);
extern float fast_vec_dist(void *,void *), vec_distance_xy(void *,void *);
extern void math_step_value_toward_target(void *,void *,float,float,float,float);
extern void lerp_vector(void *,void *,void *,float), vec_clear_128(void *);
extern void object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern void copy_matrix3x4(void *,void *), func_002A10E8(void *);
extern void part_spawn_object_sparks(void *,float), ship_spawn_exhaust_puffs(void *);
extern void path_sample_position(void *,int,void *,void *,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_002A1130(void *,int,void *,int);
extern void ship_draw_engine_flames(void *), cam_update_state(void), UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void), game_update_idle_frame_counters(void);
extern int transition_update_scene(void);

int func_PAL_002EA0B0(void)
{
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float temp[16] __attribute__((aligned(16)));

    int result = 0;

    (&g_hero_moby_default)->frame++;
    switch ((&g_hero_moby_default)->mode) {
    case 0:
    case 3:
        game_reset_frame_counters();
        moby_update_visible_objects();
        snd_run_callbacks();
        stub_empty_3();
        part_update_all();
        (&g_scene_playback_state)->streamFrame++;
        (&g_scene_playback_state)->frame++;
        {
            int skipIndex, advance, chunkLength;
            for (skipIndex=0; W(D_00261FE0,(&g_scene_playback_state)->selected*32 + skipIndex*8)>=0; skipIndex++) {
                if ((&g_scene_playback_state)->frame==(W(D_00261FE0,(&g_scene_playback_state)->selected*32 + skipIndex*8)*5+2)/6) {
                    advance=(W(D_00261FE0,(&g_scene_playback_state)->selected*32 + skipIndex*8+4)*5+2)/6;
                    chunkLength=g_is_pal_video ? 80 : 96;
                    (&g_scene_playback_state)->frame+=advance;
                    (&g_scene_playback_state)->streamFrame+=advance;
                    if ((&g_scene_playback_state)->streamFrame>=chunkLength) {
                        (&g_scene_playback_state)->chunk=(&g_scene_playback_state)->frame/chunkLength;
                        load_select_segment_update_world((&g_scene_playback_state)->chunk);
                        (&g_scene_playback_state)->streamFrame=(&g_scene_playback_state)->frame%chunkLength;
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
        skip=(&g_hero_moby_default)->skip;
        if ((g_pad_state.pressed&0x9FF) && (&g_scene_playback_state)->frame>=11 && g_screen_fade==0.0f && (&g_scene_playback_state)->frame<(&g_scene_playback_state)->endFrame-25) skip=1;
        if (skip) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            if ((&g_hero_moby_default)->mode==0) {
                (&g_scene_playback_state)->frame=(&g_scene_playback_state)->endFrame-25;
                (&g_scene_playback_state)->chunk=(&g_scene_playback_state)->frame/limit;
                load_select_segment_update_world((&g_scene_playback_state)->chunk);
                (&g_scene_playback_state)->streamFrame=(&g_scene_playback_state)->frame%limit;
                if ((&g_hero_moby_default)->skip) (&g_hero_moby_default)->skip=0;
                else FadeToBlack(4);
                g_screen_fade=1.0f;
            } else {
                if ((&g_hero_moby_default)->skip) (&g_hero_moby_default)->skip=0;
                if ((&g_scene_playback_state)->frame<5) (&g_hero_moby_default)->fadeStart=-5;
                else (&g_hero_moby_default)->fadeStart=(&g_scene_playback_state)->frame-1;
            }
        }
        }
        if ((&g_hero_moby_default)->mode==3) {
            int j;
            j=(&g_hero_moby_default)->fadeStart;
            if (j==0) j=(&g_scene_playback_state)->endFrame-6;
            if ((&g_scene_playback_state)->frame>=j) {
                g_screen_fade=((&g_scene_playback_state)->frame-j)*0.2f;
                if (g_screen_fade>1.0f) (&g_scene_playback_state)->frame=(&g_scene_playback_state)->endFrame;
                if (g_screen_fade>1.0f) g_screen_fade=1.0f;
            }
        }
        if ((&g_scene_playback_state)->frame>=(&g_scene_playback_state)->endFrame) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            gfx_select_packet_buffer_setup();
            D_001B9040.fieldOfView=0.62f;
            UpdateViewContext();
            {
                int cleanupIndex;
                for (cleanupIndex=0;cleanupIndex<(&g_scene_playback_state)->objectCount;cleanupIndex++) {
                    PlaybackMoby *object=(&g_scene_playback_state)->objects[cleanupIndex];
                    if (object) {
                        object->classData->count--;
                        object->classData->slots[object->classData->count]=0;
                        moby_mark_spawned(object);
                    }
                    if ((&g_hero_moby_default)->extra) moby_mark_spawned((&g_hero_moby_default)->extra);
                }
            }
            (&g_hero_moby_default)->object->flags&=0xFFFE;
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
            if ((&g_hero_moby_default)->mode==0) {
                if (!request_begin_slot(3,1,4,0,0)) D_001B1694=1;
            } else request_end_slot(0,0);
        } else {
            {
                int chunkLength=g_is_pal_video ? 80 : 96;
                if ((&g_scene_playback_state)->streamFrame>=chunkLength) {
                    (&g_scene_playback_state)->chunk++;
                    load_select_segment_update_world((&g_scene_playback_state)->chunk);
                }
            }
            mat_get_euler_angles((&g_hero_moby_default)->object->matrix,(&g_hero_moby_default)->object->rotation);
            (&g_hero_moby_default)->object->rotation[0]=0;
            (&g_hero_moby_default)->object->rotation[1]=0;
            euler_to_matrix(matrix,(&g_hero_moby_default)->object->rotation);
            qcopy(point,(&g_hero_moby_default)->object->position);
            point[2]=coll_probe_ground_height_below(point,0,0.5f);
            {
            char *key, *rotation;
            int last, i;
            float angle;
            key=(&g_scene_playback_state)->keys+(&g_scene_playback_state)->streamFrame*32;
            last=B(key,0xC);
            rotation=key+0x10;
            D_001B9040.fieldOfView=F(rotation,0xC);
            UpdateViewContext();
            qcopy(g_active_camera.position,key);
            transform_vector(g_active_camera.position,g_active_camera.position,matrix);
            FastVecAdd(g_active_camera.position,g_active_camera.position,point);
            angle=FastAddRotations(F(rotation,8),(&g_hero_moby_default)->object->rotation[2]);
            func_00129178(temp);
            pad_vib_routine_f(temp,temp,F(key,0x10));
            pad_vib_routine_g(temp,temp,F(rotation,4));
            pad_vib_routine_e(temp,temp,angle);
            g_active_camera.forward[0]=-temp[8]; g_active_camera.right[0]=-temp[0]; g_active_camera.up[0]=temp[4];
            g_active_camera.forward[1]=-temp[9]; g_active_camera.right[1]=-temp[1]; g_active_camera.up[1]=temp[5];
            g_active_camera.forward[2]=-temp[10]; g_active_camera.right[2]=-temp[2]; g_active_camera.up[2]=temp[6];
            {
                for (i=0;i<(&g_scene_playback_state)->objectCount;i++) {
                    char *p;
                    PlaybackMoby *object=(&g_scene_playback_state)->objects[i];
                    int half=(&g_scene_playback_state)->streamFrame>>1;
                    object->frame=half;
                    object->nextFrame=half+1;
                    update_moby_animation_state(object);
                    object->animTime=IntToFloat((&g_scene_playback_state)->streamFrame&1)*0.5f;
                    if (last && ((&g_scene_playback_state)->streamFrame&1)) object->animTime=1.0f;
                    p=object->keys;
                    FastVecScale(temp,p+object->frame*16,1.0f-object->animTime);
                    FastVecScale(temp+4,p+object->nextFrame*16,object->animTime);
                    FastVecAdd(object->position,temp,temp+4);
                    transform_vector(object->position,object->position,matrix);
                    FastVecAdd(object->position,object->position,point);
                    object->rotation[2]=(&g_hero_moby_default)->object->rotation[2];
                    object->animId=255;
                    func_002A0F48(object);
                    if (object->classId==0) {
                        object->shadowRange=0;
                        if ((&g_hero_moby_default)->mode==0) {
                            if ((&g_scene_playback_state)->frame<73) object->shadowRange=24;
                        } else {
                            if ((&g_scene_playback_state)->frame>=143) object->shadowRange=24;
                        }
                    } else if (object->classId==10) {
                        object->shadowRange=0;
                        if ((&g_hero_moby_default)->mode==0) { if ((&g_scene_playback_state)->frame<279) object->shadowRange=24; }
                        else if ((&g_scene_playback_state)->frame>=174) object->shadowRange=24;
                    }
                    if (object->shadowRange) moby_run_ground_check(object);
                    if (object->classId==10) stub_empty_18(object);
                    if (object->classId==0) stub_empty_17(object,0);
                    if (object->classId==0xD54) {
                        PlaybackMoby *p;
                        int j, cast;
                        object->mobyState=4;
                        UpdateEquipmentPieces(object);
                        if (!D_001B2148 || H(D_001B2148,0xAA)==0xD54) gfx_register_overlay_draw_callback(render_environment_mapped_object,object);
                        gfx_register_world_draw_callback(gfx_draw_ground_shadow,object);
                        p=0;
                        j=H(D_001A8C30,((g_equipment_bits[0]>>3)&2));
                        for(cast=0;g_equipment_pieces[cast];cast++) {
                            if(g_equipment_pieces[cast]->mobyState>=5) g_equipment_pieces[cast]->mobyState=4;
                            if(j==g_equipment_pieces[cast]->classId) {p=g_equipment_pieces[cast];break;}
                        }
                        if(p) {
                            if((&g_hero_moby_default)->mode==0) {
                                int offset,color;
                                offset=D_0018C31C ? 144 : -18;
                                if((&g_scene_playback_state)->frame<((504-offset)*5+2)/6) {
                                    color=(int)(((&g_scene_playback_state)->frame-((360.0f-offset)*5.0f+2.0f)*0.16666667f)*1.8000001f);
                                    if(color>255) color=255;
                                    if(color<0) color=0;
                                    p->color=color | (color<<8) | (color<<16);
                                    if((&g_scene_playback_state)->frame>((420-offset)*5+2)/6) {
                                        object->effectScale=(int)(((&g_scene_playback_state)->frame-((420.0f-offset)*5.0f+2.0f)*0.16666667f)*1.44f);
                                        object->partFlags=0;
                                        gfx_register_world_draw_callback(part_draw_glow_quads,object);
                                    }
                                    if((&g_scene_playback_state)->frame>((464-offset)*5+2)/6) {
                                        D_001B15A4+=0.0324f;
                                        if(D_001B15A4>1.0f) D_001B15A4=1.0f;
                                    }
                                } else {
                                    p->color=0xA0A0A0;
                                    D_001B15A4-=0.0324f;
                                    if(D_001B15A4<0.0f) D_001B15A4=0.0f;
                                }
                            } else {
                                if((&g_scene_playback_state)->frame<125) {
                                    int color=((125-(&g_scene_playback_state)->frame)*255)/125;
                                    p->color=color|(color<<8)|(color<<16);
                                } else {
                                    int color=(int)(math_fast_sin_or_cos_a(IntToFloat(((&g_scene_playback_state)->frame&63)-32)*0.09817477f)*80.0f)+120;
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
        stub_empty_3();
        part_update_all();
        if ((&g_hero_moby_default)->frame==0) {
            music_Pause(0);
            snd_pump_music_and_disc_read(0);
            g_music_state.requestedFrame=0x138E;
            g_music_state.requestFlags=0;
            while (g_music_state.mode!=3 || g_music_state.streamPosition>=6000) {
                UpdateSoundVoices();
                sceGsSyncV(0);
            }
            snd_resume_music_stream();
            (&g_hero_moby_default)->object->opacity=255;
            (&g_hero_moby_default)->object->updateState=0;
            if ((&g_hero_moby_default)->curveIndex>=0) {
                char *global;
                (&g_hero_moby_default)->hero=CreateMoby(0);
                global=g_hero_state;
                (&g_hero_moby_default)->hero->drawDistance=0x1FF;
                (&g_hero_moby_default)->hero->opacity=255;
                (&g_hero_moby_default)->hero->updateState=0;
                (&g_hero_moby_default)->hero->flags|=6;
                (&g_hero_moby_default)->hero->colorData=*(unsigned long long *)(P(global,0x2290)+0x38);
                if (B(D_001CE4EA,0)!=255 && H(global,0x24FC)==0) {
                    (&g_hero_moby_default)->companion=CreateMoby(10);
                    (&g_hero_moby_default)->companion->drawDistance=0x1FF;
                    (&g_hero_moby_default)->companion->opacity=255;
                    (&g_hero_moby_default)->companion->updateState=0;
                    (&g_hero_moby_default)->companion->flags|=6;
                    (&g_hero_moby_default)->companion->colorData=*(unsigned long long *)(P(global,0x2290)+0x38);
                } else (&g_hero_moby_default)->companion=0;
            }
            SetCamera5Pose(g_active_camera.position,g_active_camera.rotation,1,0,0);
            (&g_hero_moby_default)->cameraBlend=0;
            (&g_hero_moby_default)->cameraVelocity=0;
            if ((&g_hero_moby_default)->curveIndex>=0) {
                char *curve;
                float maximum, angle, factor;
                curve=(char *)g_path_table[(&g_hero_moby_default)->curveIndex];
                maximum=(&g_hero_moby_default)->cameraBlend;
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
                (&g_hero_moby_default)->length=fast_vec_dist(curve+0x10,curve+0x20);
                (&g_hero_moby_default)->progress=0;
                (&g_hero_moby_default)->speed=0;
                /* These copies do not overlap the state pointer/length fields. */
                qcopy_nc((&g_hero_moby_default)->startPosition,(&g_hero_moby_default)->object->position);
                qcopy_nc((&g_hero_moby_default)->endPosition,curve+0x10);
                qcopy_nc((&g_hero_moby_default)->startRotation,(&g_hero_moby_default)->object->rotation);
                (&g_hero_moby_default)->endRotation[0]=F(curve,0x1C);
                angle=vec_distance_xy(curve+0x20,curve+0x10);
                (&g_hero_moby_default)->endRotation[1]=mat_fast_helper_a(angle,F(curve,0x18)-F(curve,0x28));
                (&g_hero_moby_default)->endRotation[2]=mat_fast_helper_a(F(curve,0x20)-F(curve,0x10),F(curve,0x24)-F(curve,0x14));
            }
        }
        if ((&g_hero_moby_default)->cameraStart>=0 && (&g_hero_moby_default)->cameraEnd>=0) {
            float angle;
            math_step_value_toward_target(&(&g_hero_moby_default)->cameraBlend,&(&g_hero_moby_default)->cameraVelocity,1.0f,0.00026640002f,0.00026640002f,0.010000001f);
            lerp_vector(matrix,D_001B1C4C[0]+(&g_hero_moby_default)->cameraStart*128+0x30,D_001B1C4C[0]+(&g_hero_moby_default)->cameraEnd*128+0x30,(&g_hero_moby_default)->cameraBlend);
            vec_clear_128(matrix+4);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraEnd*128,0x74),F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraStart*128,0x74));
            matrix[5]=angle*(&g_hero_moby_default)->cameraBlend;
            matrix[5]=FastAddRotations(F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraStart*128,0x74),matrix[5]);
            angle=fast_subtract_rotations(F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraEnd*128,0x78),F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraStart*128,0x78));
            matrix[6]=angle*(&g_hero_moby_default)->cameraBlend;
            matrix[6]=FastAddRotations(F(D_001B1C4C[0]+(&g_hero_moby_default)->cameraStart*128,0x78),matrix[6]);
            object_copy_vector_to_selected(matrix);
            cam_set_state_rotation(matrix+4);
        }
        if ((&g_hero_moby_default)->curveIndex>=0) {
            char *p;
            PlaybackBones *bones;
            int *table;
            if ((&g_hero_moby_default)->frame<100) {
                float angle, factor, blend;
                angle=IntToFloat((&g_hero_moby_default)->frame);
                factor=IntToFloat(75);
                blend=(1.0f-math_fast_sin_or_cos_a(angle*(3.1415927f/factor)))*0.5f;
                if((&g_hero_moby_default)->frame>=75) blend=1.0f;
                lerp_vector((&g_hero_moby_default)->object->position,(&g_hero_moby_default)->startPosition,(&g_hero_moby_default)->endPosition,blend);
                (&g_hero_moby_default)->object->rotation[0]=(&g_hero_moby_default)->endRotation[0]*blend;
                angle=fast_subtract_rotations((&g_hero_moby_default)->endRotation[1],(&g_hero_moby_default)->startRotation[1]);
                (&g_hero_moby_default)->object->rotation[1]=FastAddRotations((&g_hero_moby_default)->startRotation[1],angle*blend);
                angle=fast_subtract_rotations((&g_hero_moby_default)->endRotation[2],(&g_hero_moby_default)->startRotation[2]);
                (&g_hero_moby_default)->object->rotation[2]=FastAddRotations((&g_hero_moby_default)->startRotation[2],angle*blend);
                euler_to_matrix(matrix,(&g_hero_moby_default)->object->rotation);
                copy_matrix3x4((&g_hero_moby_default)->object->matrix,matrix);
                func_002A10E8((&g_hero_moby_default)->object);
                if(g_screen_fade>0.0f) {
                    g_screen_fade-=0.125f;
                    if(g_screen_fade<0.0f) g_screen_fade=0.0f;
                }
                (&g_hero_moby_default)->object->effectOpacity=(unsigned short)(&g_hero_moby_default)->frame>>2;
                if(blend<1.0f) part_spawn_object_sparks((&g_hero_moby_default)->object,-0.075f);
            } else {
                PlaybackCurve *curve;
                float step;
                curve=g_path_table[(&g_hero_moby_default)->curveIndex];
                (&g_hero_moby_default)->speed+=0.8f;
                if((&g_hero_moby_default)->speed>100.0f) (&g_hero_moby_default)->speed=100.0f;
                if((g_pad_state.pressed&0x50) && g_screen_fade<0.1f) g_screen_fade=0.1f;
                step=(&g_hero_moby_default)->speed*0.020000001f/(&g_hero_moby_default)->length;
                if((float)curve->count-step*12.0f<(&g_hero_moby_default)->progress && g_screen_fade<0.1f) g_screen_fade=0.1f;
                if(g_screen_fade>0.0f) {
                    g_screen_fade+=0.1f;
                    if(g_screen_fade>1.0f) g_screen_fade=1.0f;
                }
                if((&g_hero_moby_default)->object->effectOpacity<160) (&g_hero_moby_default)->object->effectOpacity+=8;
                (&g_hero_moby_default)->progress+=step;
                ship_spawn_exhaust_puffs((&g_hero_moby_default)->object);
                if((&g_hero_moby_default)->progress>(float)(curve->count-1) || g_screen_fade>=1.0f) D_001A8B84=1;
                else {
                    path_sample_position(curve,1,(&g_hero_moby_default)->object->position,(&g_hero_moby_default)->object->rotation,0,(&g_hero_moby_default)->progress);
                    (&g_hero_moby_default)->object->rotation[0]=(&g_hero_moby_default)->object->rotation[3];
                    euler_to_matrix(matrix,(&g_hero_moby_default)->object->rotation);
                    copy_matrix3x4((&g_hero_moby_default)->object->matrix,matrix);
                    func_002A10E8((&g_hero_moby_default)->object);
                }
            }
            qcopy_nc((&g_hero_moby_default)->hero->rotation,(&g_hero_moby_default)->object->rotation);
            matrix_mul_vec3((&g_hero_moby_default)->hero->position,D_001AC1B0,(&g_hero_moby_default)->object->matrix);
            FastVecAdd((&g_hero_moby_default)->hero->position,(&g_hero_moby_default)->hero->position,(&g_hero_moby_default)->object->position);
            func_002A0F48((&g_hero_moby_default)->hero);
            p=(&g_hero_moby_default)->hero->classData;
            bones=(PlaybackBones *)P(p,0x48);
            table=&bones->a1C[bones->n10];
            func_002A1130(table+bones->n13,bones->a1C[0],D_001B4580,B(p,8));
            (&g_hero_moby_default)->hero->joints=D_001B4580;
            (&g_hero_moby_default)->hero->previousJoints=D_001B4580;
            if((&g_hero_moby_default)->companion) {
                qcopy_nc((&g_hero_moby_default)->companion->rotation,(&g_hero_moby_default)->object->rotation);
                matrix_mul_vec3((&g_hero_moby_default)->companion->position,D_001AC1C0,(&g_hero_moby_default)->object->matrix);
                FastVecAdd((&g_hero_moby_default)->companion->position,(&g_hero_moby_default)->companion->position,(&g_hero_moby_default)->object->position);
                func_002A0F48((&g_hero_moby_default)->companion);
            }
        } else {
            D_001A8B84=1;
            g_screen_fade=1.0f;
        }
        UpdateEquipmentPieces((&g_hero_moby_default)->object);
        gfx_register_overlay_draw_callback(ship_draw_engine_flames,(&g_hero_moby_default)->object);
        cam_update_state();
        UpdateSoundVoices();
        UpdateLightingEnvironment();
        gfx_compute_light_direction();
        game_update_idle_frame_counters();
        break;
    case 2:
        g_current_game_mode=6;
        result=transition_update_scene();
        break;
    }
    return result;
}
