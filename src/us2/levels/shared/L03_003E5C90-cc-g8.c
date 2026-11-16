/* func_US2_L03_003E5C90, the USA v2.00 copy of func_L03_003E4680: the same C, where rename func_L03_002C6F08 becomes func_US2_L03_002C7288. */
#include "common.h"
typedef struct MuseumPlayer {
    char pad00[0x40];
    float matrix40[16];
    float position[4];
    char pad90[8];
    float rotation[4];
    char padA8[0x58];
    float velocity[4];
    char pad110[0x112];
    short mode;
    char pad224[0x118];
    char *focus;
    char pad340[0x8E8];
    int flags;
    char padC2C[0x61C];
    int saved;
    char pad124C[0x1044];
    char *animation;
    int animation_id;
    char pad2298[0x30];
    int action;
} MuseumPlayer;
extern MuseumPlayer g_hero_state;
typedef struct MuseumInput {
    char pad[0x1A0];
    union { unsigned long long mask; struct { unsigned low, high; } words; } buttons;
} MuseumInput;
extern MuseumInput g_pad_state;
typedef struct MuseumGameState { char pad[0x33]; unsigned char mode; } MuseumGameState;
extern MuseumGameState g_item_slot_to_record;
extern unsigned char g_moby_nibble_table[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_focus_lock_flag;
typedef struct MuseumCompletion { char pad[0x464]; unsigned char complete[0]; } MuseumCompletion;
extern char g_trigger_l03_flags[];
typedef struct MuseumSound { char pad[0x14]; int handle; char rest[0xC8]; } MuseumSound;
extern char g_item_l03_record_table[];
extern int g_infiltrator_lock_timer;
extern char *g_moby_record_base;
extern char D_L03_001B0C70_gp[] SDATA(D_L03_001B0C70), D_L03_001B0C80_gp[] SDATA(D_L03_001B0C80), D_L03_001B0C90_gp[] SDATA(D_L03_001B0C90);
extern char g_camera_pose_buffer[], g_moby_basis_matrix[];
extern float g_infiltrator_lock_angle NOT_SDA, g_infiltrator_lock_fade MACRO_ADDR;
extern int g_hero_l03_mode;
extern int g_path_puzzle_step_count MACRO_ADDR, g_path_puzzle_timer_max MACRO_ADDR, g_path_puzzle_duration MACRO_ADDR, g_path_puzzle_limit MACRO_ADDR;
extern int g_path_entries[][4];
extern void moby_set_state(char *,int,int), moby_set_flag_bit(char *,int);
extern int flag_set_first_pending(char *);
extern void infiltrator_ball_spawn_for_moby(char *),moby_update_attached_child(char *),gadget_reset_state(char *);
extern int ForceClaimNotice(int,int,int);
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int),hero_start_loader_state(int);
extern int hero_l03_enter_state_us2(int,int);
extern void matrix_mul_vec3(void *,void *,void *),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern float FastAddRotations(float,float),mat_fast_helper_a(float,float),vec_distance_xy(void *,void *);
extern void hero_start_target_state(void *,int,float);
extern int hero_get_target_state_kind(void);
extern void set_hero_animation(int,int,float),cam_set_value_target(int,int,float,float,float,float);
extern void SetCamera5Pose(void *,void *,int,int,int),object_copy_vector_to_selected(void *),cam_set_state_rotation(void *);
extern void vec_clamp_length(void *,float);
extern void StepAngleTowardTarget(void *,int,float,float);
extern float ApproachValue(float *,float,float);
extern int request_begin_slot(int,int,char *,int,int);
extern void set_identity_rotation_rows(void *),vec_clear_128(void *),euler_rotation_basis(void *,void *),cam_reset_entry(int);
extern int PlayMobySound(int,int,char *);
extern void script_queue_keyed_request(int,int);
extern void object_copy_vector_to_selected(void *),cam_set_state_rotation(void *),SetCamera5Pose(void *,void *,int,int,int);
typedef struct { char pad[0x3C]; short a; char p3e[10]; short b; } MenuState;
extern MenuState g_music_state;
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
static __inline__ unsigned int AdvanceMuseumTimer(char *moby) {
    unsigned int value = U(moby,0x96);
    unsigned int old = value++;
    U(moby,0x96) = value;
    return old;
}
typedef struct MuseumDisplayVars { char pad[0x6C]; unsigned short settings; } MuseumDisplayVars;
typedef struct MuseumDisplay { char pad[0x68]; MuseumDisplayVars *vars; } MuseumDisplay;
typedef struct MuseumExhibit {
    int child_ids[2];
    int cleanup_id;
    int track_ids[14];
    unsigned short settings;
    char pad46[2];
    int duration, limit;
    int music, volume;
    MuseumDisplay *display;
    char *pad5C;
    int completed, saved;
    int pad68;
    float fade;
    int resume;
} MuseumExhibit;
/* Runs the Infiltrator lock: waits for the player to press the button, plays the camera move, starts the puzzle and marks the lock as opened when it is solved (USA v2.00). */
void infiltrator_lock_update_us2(char *moby) {
    MuseumExhibit *exhibit = (MuseumExhibit *)P(moby,0x68);
    float vec[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    switch (B(moby,0x20)) {
    case 0: {
        int j, state;
        unsigned short id = U(moby,0xB2);
        char *display_moby;
        if (((MuseumCompletion *)g_trigger_l03_flags)->complete[(short)id]
            || (state = g_moby_nibble_table[((short)id>>1)+(g_current_map_index<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            moby_set_state(moby,8,-1);
            moby_set_flag_bit(moby,1);
            for (j=0;j<2;j++) if (exhibit->child_ids[j]!=-1) moby_set_flag_bit(g_moby_record_base+(exhibit->child_ids[j]<<8),1);
        } else {
            moby_set_state(moby,1,-1);
            infiltrator_ball_spawn_for_moby(moby);
            display_moby=(char *)exhibit->display;
            qcopy(display_moby+0x10,moby+0x10);
            F(display_moby,0x18)+=1.0f;
            U(exhibit->display,0x34)|=1;
            B(exhibit->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (g_hero_state.focus!=moby || g_infiltrator_lock_timer<16 || !g_focus_lock_flag) break;
        ForceClaimNotice(12,0x1342,1);
        if (!load_is_class_cached(((MuseumSound *)g_item_l03_record_table)[g_item_slot_to_record.mode].handle)) {
            LoadClassIntoFreeCacheSlot(((MuseumSound *)g_item_l03_record_table)[g_item_slot_to_record.mode].handle);
            break;
        }
        if (g_pad_state.buttons.words.high&0x10) {
            exhibit->saved=g_hero_state.saved;
            g_hero_state.action=0x33;
            moby_set_state(moby,2,-1);
        }
        break;
    case 2: {
        unsigned int camera_state;
        if (flag_set_first_pending(moby)) {
            matrix_mul_vec3(vec,D_L03_001B0C70_gp,moby+0xC0);
            FastVecAdd(vec,vec,moby+0x10);
            hero_start_target_state(vec,0,FastAddRotations(F(moby,0xF8),3.1415927f));
        }
        camera_state=hero_get_target_state_kind();
        if (camera_state==2) moby_set_state(moby,3,-1);
        else if ((AdvanceMuseumTimer(moby)>=301)) {gadget_reset_state(moby);hero_start_loader_state(0);moby_set_state(moby,1,-1);}
        else if (!camera_state) {gadget_reset_state(moby);moby_set_state(moby,1,-1);}
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) {
            PlayMobySound(0,0,moby);
            hero_l03_enter_state_us2(0x6F,0);set_hero_animation(0x54,0,20.0f);
            FastVecSub(vec,g_camera_pose_buffer,g_hero_state.position);
            matrix_mul_vec3(vec,vec,g_hero_state.matrix40);
            SetCamera5Pose(g_camera_pose_buffer,g_camera_pose_buffer,3,120,0);
            exhibit->fade=0;
        }
        matrix_mul_vec3(vec,D_L03_001B0C70_gp,moby+0xC0);
        FastVecAdd(vec,vec,moby+0x10);
        FastVecSub(g_hero_state.velocity,vec,g_hero_state.position);
        g_hero_state.velocity[2]=0;
        vec_clamp_length(g_hero_state.velocity,0.012500001f);
        StepAngleTowardTarget(g_hero_state.rotation,0,FastAddRotations(F(moby,0xF8),3.1415927f),0.017453296f);
        g_hero_state.mode=3;
        if ((g_hero_state.flags&2) && B(g_hero_state.animation,0x43)==0x54) set_hero_animation(0x55,0,7.0f);
        if (g_hero_state.animation_id!=0x6F) {gadget_reset_state(moby);moby_set_state(moby,1,-1);}
        matrix_mul_vec3(pos,D_L03_001B0C80_gp,&g_hero_state);
        FastVecAdd(pos,pos,g_hero_state.position);
        qzero_nc(rot);
        matrix_mul_vec3(target,D_L03_001B0C90_gp,&g_hero_state);
        FastVecAdd(target,target,g_hero_state.position);
        rot[2]=mat_fast_helper_a(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-mat_fast_helper_a(vec_distance_xy(pos,target),target[2]-pos[2]);
        object_copy_vector_to_selected(pos);cam_set_state_rotation(rot);
        if ((AdvanceMuseumTimer(moby)>=61)) {
            moby_set_state(moby,4,-1);
            exhibit->resume=g_music_state.a==-1?g_music_state.b:g_music_state.a;
            script_queue_keyed_request(exhibit->music,exhibit->volume);
        }
        break;
    case 4: {
        unsigned int elapsed;
        if (flag_set_first_pending(moby)) {
            PlayMobySound(0,0,moby);
            g_infiltrator_lock_angle=0.017453294f;
            cam_set_value_target(30,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        g_hero_state.mode=3;
        if (g_hero_state.animation_id!=0x6F) {gadget_reset_state(moby);moby_set_state(moby,1,-1);break;}
        if ((AdvanceMuseumTimer(moby)<21)) break;
        ApproachValue(&exhibit->fade,1.0f,0.116666675f);
        elapsed=U(moby,0x96);
        g_infiltrator_lock_fade=exhibit->fade;
        if (elapsed<31) break;
        g_infiltrator_lock_angle=1.1243411f;
        cam_set_value_target(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!request_begin_slot(7,1,moby,0,0)) moby_set_state(moby,5,-1);
        break;
    }
    case 5:
        if (g_hero_l03_mode==7) {
            int i;
            qzero_nc(g_camera_pose_buffer);
            infiltrator_ball_spawn_for_moby(moby);
            g_path_puzzle_step_count=0;
            /* Pointer arithmetic, not track_ids[i]: an array field of a BLKmode struct would form exhibit+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(exhibit->track_ids+i)>=0;i++) {
                g_path_entries[i][0]=*(exhibit->track_ids+i);
                g_path_puzzle_step_count++;
                g_path_puzzle_duration=exhibit->duration;
                g_path_puzzle_timer_max=exhibit->duration+120;
                g_path_puzzle_limit=exhibit->limit;
                exhibit->display->vars->settings=exhibit->settings;
            }
            U(exhibit->display,0x34)&=~1;
            B(exhibit->display,0x31)=1;
            U(exhibit->display,0x34)&=~0x80;
            set_identity_rotation_rows(g_moby_basis_matrix);
            vec_clear_128((char *)exhibit->display+0xF0);
            F(exhibit->display,0xF4)=-1.5707964f;
            euler_rotation_basis((char *)exhibit->display+0xC0,(char *)exhibit->display+0xF0);
            moby_set_state(moby,6,-1);
        } else if ((AdvanceMuseumTimer(moby)>=6)) {
            gadget_reset_state(moby);
            script_queue_keyed_request(exhibit->resume,exhibit->volume);
            moby_set_state(moby,1,-1);
        }
        break;
    case 6:
        if (g_hero_l03_mode==7) {set_identity_rotation_rows(g_moby_basis_matrix);moby_update_attached_child(moby);break;}
        gadget_reset_state(moby);
        script_queue_keyed_request(exhibit->resume,exhibit->volume);
        if (exhibit->cleanup_id!=-1) cam_reset_entry(exhibit->cleanup_id);
        if (exhibit->completed) {
            moby_set_state(moby,7,-1);
            if (B(moby,0xB0)!=255) {
                unsigned short id;
                unsigned char *p;
                id=U(moby,0xB2);
                if (id&1) {p=g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));if (((*p>>4)&7)!=7) *p+=16;}
                else {p=g_moby_nibble_table+(((short)id>>1)+(g_current_map_index<<10));if ((*p&7)!=7) ++*p;}
            }
            if (g_current_map_index==19) {
                int j;
                for (j=0;j<2;j++) if (exhibit->child_ids[j]!=-1) moby_set_flag_bit(g_moby_record_base+(exhibit->child_ids[j]<<8),1);
            }
        } else {hero_start_loader_state(0);moby_set_state(moby,1,-1);}
        break;
    case 7: {
        int j;
        moby_set_flag_bit(moby,1);
        for (j=0;j<2;j++) if (exhibit->child_ids[j]!=-1) moby_set_flag_bit(g_moby_record_base+(exhibit->child_ids[j]<<8),1);
        hero_start_loader_state(0);moby_set_state(moby,8,-1);
        break;
    }
    }
}
