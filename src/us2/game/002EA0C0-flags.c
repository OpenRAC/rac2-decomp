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
    PlaybackClass *class_data;
    char pad28[0xA];
    short draw_distance;
    unsigned short flags;
    char pad36[2];
    unsigned long long color_data;
    unsigned char frame, next_frame;
    char pad42[2];
    float anim_time;
    char pad48[0x10];
    char *joints, *previous_joints;
    unsigned char pad60, anim_id, opacity, moby_state;
    char pad64[4];
    char *keys;
    char pad6C[3];
    unsigned char shadow_radius;
    char pad70[8];
    unsigned int color;
    char pad7C[0x19];
    unsigned char effect_opacity;
    char pad96[2];
    int update_state;
    char pad9C[0xE];
    short class_id;
    char padAC[6];
    short part_flags;
    char padB4[8];
    unsigned char effect_scale;
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
    int curve_index, camera_start, camera_end;
    float progress, speed, length, camera_blend, camera_velocity;
    char pad60[0xC];
    int fade_start;
    char pad70[0x20];
    float start_position[4], end_position[4], start_rotation[4], end_rotation[4];
} PlaybackState;
typedef struct {
    char pad00[0x30];
    int selected, frame, stream_frame, chunk;
    short end_frame, unused42, object_count;
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
    int requested_frame, request_flags;
    char pad2C[0x40];
    short stream_position;
    char pad6E[4];
    short mode;
} PlaybackStream;
extern PlaybackStream g_music_state;
typedef struct { char pad[0xB0]; float field_of_view; } PlaybackScreen;
extern PlaybackScreen g_view_params;
typedef struct {
    char pad00[0x140];
    float position[4], rotation[4];
    char pad160[0x210];
    float forward[4], right[4], up[4];
} PlaybackCamera;
extern PlaybackCamera g_active_camera;
extern char g_hero_joint_buffer[], g_hero_state[];
extern char g_scene_skip_table[], g_hero_class_slot_flags[];
extern char g_robot_part_ids_c[] __attribute__((sda));
extern char *g_moby_pool_end[] __attribute__((sda));
extern char *g_transition_effect_list;
extern char *g_vec_record_table[] __attribute__((sda));
extern PlaybackMoby *g_equipment_pieces[];
typedef struct { float x, y, z, w; } PlaybackPoint;
typedef struct { int count; char pad04[0xC]; PlaybackPoint points[1]; } PlaybackCurve;
typedef struct { char pad00[0x10]; unsigned char n10; char pad11[2]; unsigned char n13; char pad14[8]; int a1C[1]; } PlaybackBones;
extern PlaybackCurve *g_path_table[];
extern float g_screen_fade __attribute__((sda));
extern float g_screen_flash_alpha __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern int g_mode_change_flag __attribute__((sda));
extern int g_frontend_done_flag __attribute__((sda));
extern int g_current_game_mode __attribute__((sda));
extern unsigned int g_equipment_bits[] __attribute__((sda));
extern short g_hud_offset_flag;
extern float g_hero_attach_offset[] SDATA(D_001AC1B0);
extern float g_companion_attach_offset[] SDATA(D_001AC1C0);
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
extern void stub_empty_18(void *), stub_empty_17(void *,int), UpdateEquipmentPieces_us2(void *);
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
extern void ship_draw_engine_flames(void *), cam_update_state_us2(void), UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void), game_update_idle_frame_counters(void);
extern int transition_update_scene_us2(void);

extern void ref_US2_002EA0C0_00(void), part_update_all(void), gfx_select_packet_buffer_setup(void);
extern void ref_US2_002EA0C0_01(void *), stub_empty_17(void *,int), UpdateEquipmentPieces_us2(void *);

/* Runs one frame of a story cutscene: moves the camera and every actor along their paths, handles skipping and fades, and ends the scene (USA v2.00). */
int UpdatePlaybackScene_us2(void)
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
        scene->stream_frame++;
        scene->frame++;
        {
            int skip_index, advance, chunk_length;
            for (skip_index=0; W(g_scene_skip_table,scene->selected*32 + skip_index*8)>=0; skip_index++) {
                if (scene->frame==W(g_scene_skip_table,scene->selected*32 + skip_index*8)) {
                    advance=W(g_scene_skip_table,scene->selected*32 + skip_index*8+4);
                    chunk_length=g_is_pal_video ? 80 : 96;
                    scene->frame+=advance;
                    scene->stream_frame+=advance;
                    if (scene->stream_frame>=chunk_length) {
                        scene->chunk=scene->frame/chunk_length;
                        load_select_segment_update_world(scene->chunk);
                        scene->stream_frame=scene->frame%chunk_length;
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
        if ((g_pad_state.pressed&0x9FF) && scene->frame>=13 && g_screen_fade==0.0f && scene->frame<scene->end_frame-30) skip=1;
        if (skip) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            if (state->mode==0) {
                scene->frame=scene->end_frame-30;
                scene->chunk=scene->frame/limit;
                load_select_segment_update_world(scene->chunk);
                scene->stream_frame=scene->frame%limit;
                if (state->skip) state->skip=0;
                else FadeToBlack(4);
                g_screen_fade=1.0f;
            } else {
                if (state->skip) state->skip=0;
                if (scene->frame<5) state->fade_start=-5;
                else state->fade_start=scene->frame-1;
            }
        }
        }
        if (state->mode==3) {
            int j;
            j=state->fade_start;
            if (j==0) j=scene->end_frame-6;
            if (scene->frame>=j) {
                g_screen_fade=(scene->frame-j)*0.2f;
                if (g_screen_fade>1.0f) scene->frame=scene->end_frame;
                if (g_screen_fade>1.0f) g_screen_fade=1.0f;
            }
        }
        if (scene->frame>=scene->end_frame) {
            if ((unsigned short)((unsigned short)g_music_state.mode-6)>=2) g_music_state.mode=5;
            gfx_select_packet_buffer_setup();
            g_view_params.field_of_view=0.62f;
            UpdateViewContext();
            {
                int cleanup_index;
                for (cleanup_index=0;cleanup_index<scene->object_count;cleanup_index++) {
                    PlaybackMoby *object=scene->objects[cleanup_index];
                    if (object) {
                        object->class_data->count--;
                        object->class_data->slots[object->class_data->count]=0;
                        moby_mark_spawned(object);
                    }
                    if (state->extra) moby_mark_spawned(state->extra);
                }
            }
            state->object->flags&=0xFFFE;
            {
                int reset_index;
                for (reset_index=0;g_equipment_pieces[reset_index];reset_index++) if (g_equipment_pieces[reset_index]->moby_state) g_equipment_pieces[reset_index]->moby_state=8;
            }
            {
                char *p;
                for (p=g_moby_pool_end[0];B(p,0x20)!=255;p+=0x100) {
                    if (!(B(p,0x20)&0x80) && (H(p,0xAA)==0x4A || H(p,0xAA)==0xCB)) UH(p,0x34)&=0xFF7F;
                }
            }
            if (state->mode==0) {
                if (!request_begin_slot(3,1,4,0,0)) g_mode_change_flag=1;
            } else request_end_slot(0,0);
        } else {
            {
                int chunk_length=g_is_pal_video ? 80 : 96;
                if (scene->stream_frame>=chunk_length) {
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
            key=scene->keys+scene->stream_frame*32;
            last=B(key,0xC);
            rotation=key+0x10;
            g_view_params.field_of_view=F(rotation,0xC);
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
                for (i=0;i<scene->object_count;i++) {
                    char *p;
                    PlaybackMoby *object=scene->objects[i];
                    int half=scene->stream_frame>>1;
                    object->frame=half;
                    object->next_frame=half+1;
                    update_moby_animation_state(object);
                    object->anim_time=IntToFloat(scene->stream_frame&1)*0.5f;
                    if (last && (scene->stream_frame&1)) object->anim_time=1.0f;
                    p=object->keys;
                    FastVecScale(temp,p+object->frame*16,1.0f-object->anim_time);
                    FastVecScale(temp+4,p+object->next_frame*16,object->anim_time);
                    FastVecAdd(object->position,temp,temp+4);
                    transform_vector(object->position,object->position,matrix);
                    FastVecAdd(object->position,object->position,point);
                    object->rotation[2]=state->object->rotation[2];
                    object->anim_id=255;
                    func_002A0F48(object);
                    if (object->class_id==0) {
                        object->shadow_radius=0;
                        if (state->mode==0) {
                            if (scene->frame<87) object->shadow_radius=24;
                        } else {
                            if (scene->frame>=171) object->shadow_radius=24;
                        }
                    } else if (object->class_id==10) {
                        object->shadow_radius=0;
                        if (state->mode==0) { if (scene->frame<335) object->shadow_radius=24; }
                        else if (scene->frame>=209) object->shadow_radius=24;
                    }
                    if (object->shadow_radius) moby_run_ground_check(object);
                    if (object->class_id==10) ref_US2_002EA0C0_01(object);
                    if (object->class_id==0) stub_empty_17(object,0);
                    if (object->class_id==0xD54) {
                        PlaybackMoby *p;
                        int j, cast;
                        object->moby_state=4;
                        UpdateEquipmentPieces_us2(object);
                        if (!g_transition_effect_list || H(g_transition_effect_list,0xAA)==0xD54) gfx_register_overlay_draw_callback(render_environment_mapped_object,object);
                        gfx_register_world_draw_callback(gfx_draw_ground_shadow,object);
                        p=0;
                        j=H(g_robot_part_ids_c,((g_equipment_bits[0]>>3)&2));
                        for(cast=0;g_equipment_pieces[cast];cast++) {
                            if(g_equipment_pieces[cast]->moby_state>=5) g_equipment_pieces[cast]->moby_state=4;
                            if(j==g_equipment_pieces[cast]->class_id) {p=g_equipment_pieces[cast];break;}
                        }
                        if(p) {
                            if(state->mode==0) {
                                int offset,color;
                                offset=g_hud_offset_flag ? 144 : -18;
                                if(scene->frame<504-offset) {
                                    color=(int)((scene->frame-(360.0f-offset))*1.5f);
                                    if(color>255) color=255;
                                    if(color<0) color=0;
                                    p->color=color | (color<<8) | (color<<16);
                                    if(scene->frame>420-offset) {
                                        object->effect_scale=(int)((scene->frame-(420.0f-offset))*1.2f);
                                        object->part_flags=0;
                                        gfx_register_world_draw_callback(part_draw_glow_quads,object);
                                    }
                                    if(scene->frame>464-offset) {
                                        g_screen_flash_alpha+=0.027f;
                                        if(g_screen_flash_alpha>1.0f) g_screen_flash_alpha=1.0f;
                                    }
                                } else {
                                    p->color=0xA0A0A0;
                                    g_screen_flash_alpha-=0.027f;
                                    if(g_screen_flash_alpha<0.0f) g_screen_flash_alpha=0.0f;
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
            g_music_state.requested_frame=0x138E;
            g_music_state.request_flags=0;
            while (g_music_state.mode!=3 || g_music_state.stream_position>=6000) {
                UpdateSoundVoices();
                sceGsSyncV(0);
            }
            snd_resume_music_stream();
            state->object->opacity=255;
            state->object->update_state=0;
            if (state->curve_index>=0) {
                char *global;
                state->hero=CreateMoby(0);
                global=g_hero_state;
                state->hero->draw_distance=0x1FF;
                state->hero->opacity=255;
                state->hero->update_state=0;
                state->hero->flags|=6;
                state->hero->color_data=*(unsigned long long *)(P(global,0x2290)+0x38);
                if (B(g_hero_class_slot_flags,0)!=255 && H(global,0x24FC)==0) {
                    state->companion=CreateMoby(10);
                    state->companion->draw_distance=0x1FF;
                    state->companion->opacity=255;
                    state->companion->update_state=0;
                    state->companion->flags|=6;
                    state->companion->color_data=*(unsigned long long *)(P(global,0x2290)+0x38);
                } else state->companion=0;
            }
            SetCamera5Pose(g_active_camera.position,g_active_camera.rotation,1,0,0);
            state->camera_blend=0;
            state->camera_velocity=0;
            if (state->curve_index>=0) {
                char *curve;
                float maximum, angle, factor;
                curve=(char *)g_path_table[state->curve_index];
                maximum=state->camera_blend;
                {
                    int path_index;
                    for (path_index=1;path_index<W(curve,0)-1;path_index++) {
                        char *point=curve+path_index*16;
                        {
                            char *previous=curve+(path_index-1)*16;
                            angle=mat_fast_helper_a(F(point,0x10)-F(previous,0x10),F(point,0x14)-F(previous,0x14));
                        }
                        {
                            char *next=curve+(path_index+1)*16;
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
                    int scale_index;
                    for(scale_index=0;scale_index<W(curve,0);scale_index++) F(curve+scale_index*16,0x1C)*=factor;
                }
                {
                    int ramp_index;
                    for(ramp_index=0;ramp_index<20;ramp_index++) F(curve+ramp_index*16,0x1C)=F(curve+ramp_index*16,0x1C)*0.05f*ramp_index;
                }
                state->length=fast_vec_dist(curve+0x10,curve+0x20);
                state->progress=0;
                state->speed=0;
                /* These copies do not overlap the state pointer/length fields. */
                qcopy_nc(state->start_position,state->object->position);
                qcopy_nc(state->end_position,curve+0x10);
                qcopy_nc(state->start_rotation,state->object->rotation);
                state->end_rotation[0]=F(curve,0x1C);
                angle=vec_distance_xy(curve+0x20,curve+0x10);
                state->end_rotation[1]=mat_fast_helper_a(angle,F(curve,0x18)-F(curve,0x28));
                state->end_rotation[2]=mat_fast_helper_a(F(curve,0x20)-F(curve,0x10),F(curve,0x24)-F(curve,0x14));
            }
        }
        if (state->camera_start>=0 && state->camera_end>=0) {
            float angle;
            math_step_value_toward_target(&state->camera_blend,&state->camera_velocity,1.0f,0.00018500001f,0.00018500001f,0.008333334f);
            lerp_vector(matrix,g_vec_record_table[0]+state->camera_start*128+0x30,g_vec_record_table[0]+state->camera_end*128+0x30,state->camera_blend);
            vec_clear_128(matrix+4);
            angle=fast_subtract_rotations(F(g_vec_record_table[0]+state->camera_end*128,0x74),F(g_vec_record_table[0]+state->camera_start*128,0x74));
            matrix[5]=angle*state->camera_blend;
            matrix[5]=FastAddRotations(F(g_vec_record_table[0]+state->camera_start*128,0x74),matrix[5]);
            angle=fast_subtract_rotations(F(g_vec_record_table[0]+state->camera_end*128,0x78),F(g_vec_record_table[0]+state->camera_start*128,0x78));
            matrix[6]=angle*state->camera_blend;
            matrix[6]=FastAddRotations(F(g_vec_record_table[0]+state->camera_start*128,0x78),matrix[6]);
            object_copy_vector_to_selected(matrix);
            cam_set_state_rotation(matrix+4);
        }
        if (state->curve_index>=0) {
            char *p;
            PlaybackBones *bones;
            int *table;
            if (state->frame<120) {
                float angle, factor, blend;
                angle=IntToFloat(state->frame);
                factor=IntToFloat(90);
                blend=(1.0f-math_fast_sin_or_cos_a(angle*(3.1415927f/factor)))*0.5f;
                if(state->frame>=90) blend=1.0f;
                lerp_vector(state->object->position,state->start_position,state->end_position,blend);
                state->object->rotation[0]=state->end_rotation[0]*blend;
                angle=fast_subtract_rotations(state->end_rotation[1],state->start_rotation[1]);
                state->object->rotation[1]=FastAddRotations(state->start_rotation[1],angle*blend);
                angle=fast_subtract_rotations(state->end_rotation[2],state->start_rotation[2]);
                state->object->rotation[2]=FastAddRotations(state->start_rotation[2],angle*blend);
                euler_to_matrix(matrix,state->object->rotation);
                copy_matrix3x4(state->object->matrix,matrix);
                func_002A10E8(state->object);
                if(g_screen_fade>0.0f) {
                    g_screen_fade-=0.125f;
                    if(g_screen_fade<0.0f) g_screen_fade=0.0f;
                }
                state->object->effect_opacity=(unsigned short)state->frame>>2;
                if(blend<1.0f) part_spawn_object_sparks(state->object,-0.0625f);
            } else {
                PlaybackCurve *curve;
                float step;
                curve=g_path_table[state->curve_index];
                state->speed+=0.8f;
                if(state->speed>100.0f) state->speed=100.0f;
                if((g_pad_state.pressed&0x50) && g_screen_fade<0.1f) g_screen_fade=0.1f;
                step=state->speed*(1.0f/60.0f)/state->length;
                if((float)curve->count-step*12.0f<state->progress && g_screen_fade<0.1f) g_screen_fade=0.1f;
                if(g_screen_fade>0.0f) {
                    g_screen_fade+=0.1f;
                    if(g_screen_fade>1.0f) g_screen_fade=1.0f;
                }
                if(state->object->effect_opacity<160) state->object->effect_opacity+=8;
                state->progress+=step;
                ship_spawn_exhaust_puffs(state->object);
                if(state->progress>(float)(curve->count-1) || g_screen_fade>=1.0f) g_frontend_done_flag=1;
                else {
                    path_sample_position(curve,1,state->object->position,state->object->rotation,0,state->progress);
                    state->object->rotation[0]=state->object->rotation[3];
                    euler_to_matrix(matrix,state->object->rotation);
                    copy_matrix3x4(state->object->matrix,matrix);
                    func_002A10E8(state->object);
                }
            }
            qcopy_nc(state->hero->rotation,state->object->rotation);
            matrix_mul_vec3(state->hero->position,g_hero_attach_offset,state->object->matrix);
            FastVecAdd(state->hero->position,state->hero->position,state->object->position);
            func_002A0F48(state->hero);
            p=state->hero->class_data;
            bones=(PlaybackBones *)P(p,0x48);
            table=&bones->a1C[bones->n10];
            func_002A1130(table+bones->n13,bones->a1C[0],g_hero_joint_buffer,B(p,8));
            state->hero->joints=g_hero_joint_buffer;
            state->hero->previous_joints=g_hero_joint_buffer;
            if(state->companion) {
                qcopy_nc(state->companion->rotation,state->object->rotation);
                matrix_mul_vec3(state->companion->position,g_companion_attach_offset,state->object->matrix);
                FastVecAdd(state->companion->position,state->companion->position,state->object->position);
                func_002A0F48(state->companion);
            }
        } else {
            g_frontend_done_flag=1;
            g_screen_fade=1.0f;
        }
        UpdateEquipmentPieces_us2(state->object);
        gfx_register_overlay_draw_callback(ship_draw_engine_flames,state->object);
        cam_update_state_us2();
        UpdateSoundVoices();
        UpdateLightingEnvironment();
        gfx_compute_light_direction();
        game_update_idle_frame_counters();
        break;
    case 2:
        g_current_game_mode=6;
        result=transition_update_scene_us2();
        break;
    }
    return result;
}


