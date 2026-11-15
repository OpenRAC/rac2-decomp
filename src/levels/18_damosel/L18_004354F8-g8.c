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
extern float D_L18_001B1634 __attribute__((sda)), D_L18_001B1638 __attribute__((sda)), D_L18_001B1658 __attribute__((sda));
extern int D_L18_001B1630 __attribute__((sda));
extern int D_L18_001B1668[] __attribute__((sda)), D_L18_001B1670[] __attribute__((sda));
extern int D_L18_001B1668_GP SDATA(D_L18_001B1668), D_L18_001B1670_GP SDATA(D_L18_001B1670);
extern u8 D_L18_001B163C __attribute__((sda)), D_L18_001B163D __attribute__((sda));
extern u8 *g_moby_l18_table;
extern float D_L18_001B3720[] MACRO_ADDR;
extern float D_L18_001B3730;
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
        qcopy(D_L18_001B3720,moby->position);
        D_L18_001B3730=D_L18_001B1658;
        moby->animation=0;
        moby_set_state(moby,1,-1);
        moby->flags|=0x200;
        s->sound=snd_start_in_slot(16,4,moby);
        break;
    case 1:
        if(flag_set_first_pending(moby)) {
            moby->enabled=0; moby->flags|=1;
            moby->angle=D_L18_001B1634;
            moby->alpha=D_L18_001B163C;
            if(ACTIVE(4)) CHILD(4)->command=25;
            if(ACTIVE(0)) CHILD(0)->command=25;
            s->color[0]=D_L18_001B1668_GP; s->color[1]=D_L18_001B1668[1];
        } else if(ACTIVE(0)||ACTIVE(4)) moby_set_state(moby,2,-1);
        part_l18_spawn_random_burst(moby);
        break;
    case 2:
        if(flag_set_first_pending(moby)) {
            moby->enabled=1; moby->flags&=0xFFFE;
            s->step=FastDiffRots(D_L18_001B1638,D_L18_001B1634);
            s->step /= (float)D_L18_001B1630;
        }
        progress=IntToFloat(moby->timer);
        progress /= (float)D_L18_001B1630;
        moby->angle=FastAddRotations(moby->angle,s->step);
        moby->alpha=math_lerp_int_fraction(D_L18_001B163C,D_L18_001B163D,progress);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1668_GP,D_L18_001B1670_GP,progress);
        s->color[1]=math_lerp_int_fraction(D_L18_001B1668[1],D_L18_001B1670[1],progress);
        part_l18_spawn_random_burst(moby);
        if(moby->timer>D_L18_001B1630) moby_set_state(moby,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(moby)) {
            int soundId;
            moby->angle=D_L18_001B1638; moby->alpha=D_L18_001B163D;
            s->color[0]=D_L18_001B1670_GP; s->color[1]=D_L18_001B1670[1];
            moby->animation=(*(int *)(moby->config+16));
            if(!ACTIVE(4)) CHILD(4)->command=25;
            if(!ACTIVE(0)) CHILD(0)->command=25;
            soundId=s->sound;
            if(soundId!=-1) {
                DamoselSound *sound = (DamoselSound *)(g_sound_state+soundId*0x70);
                if(sound->owner==moby && sound->active) snd_stop_voice(soundId);
            }
            s->sound=-1;
        } else if(!ACTIVE(0)||!ACTIVE(4)) moby_set_state(moby,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(moby)) {
            moby->animation=0;
            s->step=-FastDiffRots(D_L18_001B1638,D_L18_001B1634);
            s->step /= (float)D_L18_001B1630;
            s->sound=snd_start_in_slot(16,4,moby);
        }
        progress=IntToFloat(moby->timer);
        progress /= (float)D_L18_001B1630;
        moby->angle=FastAddRotations(moby->angle,s->step);
        moby->alpha=math_lerp_int_fraction(D_L18_001B163D,D_L18_001B163C,progress);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1670_GP,D_L18_001B1668_GP,progress);
        s->color[1]=math_lerp_int_fraction(D_L18_001B1670[1],D_L18_001B1668[1],progress);
        part_l18_spawn_random_burst(moby);
        if(moby->timer>D_L18_001B1630) moby_set_state(moby,1,-1);
        break;
    }
    if(moby->timer<65535) moby->timer++;
}
