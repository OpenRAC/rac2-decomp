#include "include_asm.h"
#include "common.h"
extern void moby_set_state(void *,int,int);
extern int flag_set_first_pending(void *);
extern int snd_start_in_slot(int,int,void *);
extern void part_l18_spawn_random_burst(void *);
extern void snd_stop_voice(int);
extern float FastAddRotations(float,float);
extern float IntToFloat(int);
extern float FastDiffRots(float,float);
extern int math_lerp_int_fraction(int,int,float);
extern float g_fade_angle_start __attribute__((sda)), g_fade_angle_end __attribute__((sda)), g_fade_saved_scale __attribute__((sda));
extern int g_fade_duration_frames __attribute__((sda));
extern int g_fade_color_start[] __attribute__((sda)), g_fade_color_end[] __attribute__((sda));
extern int D_L18_001B1668_GP SDATA(D_L18_001B1668), D_L18_001B1670_GP SDATA(D_L18_001B1670);
extern u8 g_fade_alpha_start __attribute__((sda)), g_fade_alpha_end __attribute__((sda));
extern u8 *g_moby_l18_table;
extern float g_burst_origin_position[] MACRO_ADDR;
extern float g_fade_child_value;
extern u8 g_sound_state[];
typedef struct {
    int child[2];
    int color[2];
    float step;
    int sound;
} DamoselController;
typedef struct {
    u8 pad[0x74], active, gap[0x13];
    void *owner;
} DamoselSound;
typedef struct DamoselObject {
    u8 pad00[0x10];
    float position[4];
    u8 state, pad21[2], alpha;
    u8 *config;
    u8 pad28[9], enabled, pad32[2];
    u16 flags;
    u8 pad36[0x32];
    void *data;
    u8 pad6c[0x2a];
    u16 timer;
    int animation;
    u8 pad9c[0x20], command, padbd[0x37];
    float angle;
    u8 padf8[8];
} DamoselObject;
#define CHILD(n) (s->child[(n)/4]+((DamoselObject *)D_L18_001B281C))
#define ACTIVE(n) (((u8 *)CHILD(n)->data)[0x14])
/* Updates a controller (moby class 3924) for two linked child objects: it fades its effect in while either child is active and fades it out again when one stops, with a sound while it changes. */
void two_child_fade_update(DamoselObject *moby) {
    DamoselController *s=moby->data;
    float progress;
    switch(moby->state) {
    case 0:
        qcopy(g_burst_origin_position,moby->position);
        g_fade_child_value=g_fade_saved_scale;
        moby->animation=0;
        moby_set_state(moby,1,-1);
        moby->flags|=0x200;
        s->sound=snd_start_in_slot(16,4,moby);
        break;
    case 1:
        if(flag_set_first_pending(moby)) {
            moby->enabled=0; moby->flags|=1;
            moby->angle=g_fade_angle_start;
            moby->alpha=g_fade_alpha_start;
            if(ACTIVE(4)) CHILD(4)->command=25;
            if(ACTIVE(0)) CHILD(0)->command=25;
            s->color[0]=D_L18_001B1668_GP; s->color[1]=g_fade_color_start[1];
        } else if(ACTIVE(0)||ACTIVE(4)) moby_set_state(moby,2,-1);
        part_l18_spawn_random_burst(moby);
        break;
    case 2:
        if(flag_set_first_pending(moby)) {
            moby->enabled=1; moby->flags&=0xFFFE;
            s->step=FastDiffRots(g_fade_angle_end,g_fade_angle_start);
            s->step /= (float)g_fade_duration_frames;
        }
        progress=IntToFloat(moby->timer);
        progress /= (float)g_fade_duration_frames;
        moby->angle=FastAddRotations(moby->angle,s->step);
        moby->alpha=math_lerp_int_fraction(g_fade_alpha_start,g_fade_alpha_end,progress);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1668_GP,D_L18_001B1670_GP,progress);
        s->color[1]=math_lerp_int_fraction(g_fade_color_start[1],g_fade_color_end[1],progress);
        part_l18_spawn_random_burst(moby);
        if(moby->timer>g_fade_duration_frames) moby_set_state(moby,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(moby)) {
            int sound_id;
            moby->angle=g_fade_angle_end; moby->alpha=g_fade_alpha_end;
            s->color[0]=D_L18_001B1670_GP; s->color[1]=g_fade_color_end[1];
            moby->animation=(*(int *)(moby->config+16));
            if(!ACTIVE(4)) CHILD(4)->command=25;
            if(!ACTIVE(0)) CHILD(0)->command=25;
            sound_id=s->sound;
            if(sound_id!=-1) {
                DamoselSound *sound = (DamoselSound *)(g_sound_state+sound_id*0x70);
                if(sound->owner==moby && sound->active) snd_stop_voice(sound_id);
            }
            s->sound=-1;
        } else if(!ACTIVE(0)||!ACTIVE(4)) moby_set_state(moby,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(moby)) {
            moby->animation=0;
            s->step=-FastDiffRots(g_fade_angle_end,g_fade_angle_start);
            s->step /= (float)g_fade_duration_frames;
            s->sound=snd_start_in_slot(16,4,moby);
        }
        progress=IntToFloat(moby->timer);
        progress /= (float)g_fade_duration_frames;
        moby->angle=FastAddRotations(moby->angle,s->step);
        moby->alpha=math_lerp_int_fraction(g_fade_alpha_end,g_fade_alpha_start,progress);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1670_GP,D_L18_001B1668_GP,progress);
        s->color[1]=math_lerp_int_fraction(g_fade_color_end[1],g_fade_color_start[1],progress);
        part_l18_spawn_random_burst(moby);
        if(moby->timer>g_fade_duration_frames) moby_set_state(moby,1,-1);
        break;
    }
    if(moby->timer<65535) moby->timer++;
}
