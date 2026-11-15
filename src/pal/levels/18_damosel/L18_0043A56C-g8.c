#include "names.h"
/* func_PAL_L18_0043A56C, the PAL copy of func_L18_004354F8: the same C, where the D_L18_001B1630 frame count is scaled to 50 Hz. */
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
void func_PAL_L18_0043A56C(DamoselObject *o) {
    DamoselController *s=o->data;
    float t;
    switch(o->state) {
    case 0:
        qcopy(D_L18_001B3720,o->position);
        D_L18_001B3730=D_L18_001B1658;
        o->animation=0;
        moby_set_state(o,1,-1);
        o->flags|=0x200;
        s->sound=snd_start_in_slot(16,4,o);
        break;
    case 1:
        if(flag_set_first_pending(o)) {
            o->enabled=0; o->flags|=1;
            o->angle=D_L18_001B1634;
            o->alpha=D_L18_001B163C;
            if(ACTIVE(4)) CHILD(4)->command=25;
            if(ACTIVE(0)) CHILD(0)->command=25;
            s->color[0]=D_L18_001B1668_GP; s->color[1]=D_L18_001B1668[1];
        } else if(ACTIVE(0)||ACTIVE(4)) moby_set_state(o,2,-1);
        part_l18_spawn_random_burst(o);
        break;
    case 2:
        if(flag_set_first_pending(o)) {
            o->enabled=1; o->flags&=0xFFFE;
            s->step=FastDiffRots(D_L18_001B1638,D_L18_001B1634);
            s->step /= (float)(((s32)(D_L18_001B1630) * 5 + 2) / 6);
        }
        t=IntToFloat(o->timer);
        t /= (float)(((s32)(D_L18_001B1630) * 5 + 2) / 6);
        o->angle=FastAddRotations(o->angle,s->step);
        o->alpha=math_lerp_int_fraction(D_L18_001B163C,D_L18_001B163D,t);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1668_GP,D_L18_001B1670_GP,t);
        s->color[1]=math_lerp_int_fraction(D_L18_001B1668[1],D_L18_001B1670[1],t);
        part_l18_spawn_random_burst(o);
        if(o->timer>(((s32)(D_L18_001B1630) * 5 + 2) / 6)) moby_set_state(o,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(o)) {
            int n;
            o->angle=D_L18_001B1638; o->alpha=D_L18_001B163D;
            s->color[0]=D_L18_001B1670_GP; s->color[1]=D_L18_001B1670[1];
            o->animation=(*(int *)(o->config+16));
            if(!ACTIVE(4)) CHILD(4)->command=25;
            if(!ACTIVE(0)) CHILD(0)->command=25;
            n=s->sound;
            if(n!=-1) {
                DamoselSound *sound = (DamoselSound *)(g_sound_state+n*0x70);
                if(sound->owner==o && sound->active) snd_stop_voice(n);
            }
            s->sound=-1;
        } else if(!ACTIVE(0)||!ACTIVE(4)) moby_set_state(o,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(o)) {
            o->animation=0;
            s->step=-FastDiffRots(D_L18_001B1638,D_L18_001B1634)/(float)(((s32)(D_L18_001B1630) * 5 + 2) / 6);
            s->sound=snd_start_in_slot(16,4,o);
        }
        t=IntToFloat(o->timer);
        t /= (float)(((s32)(D_L18_001B1630) * 5 + 2) / 6);
        o->angle=FastAddRotations(o->angle,s->step);
        o->alpha=math_lerp_int_fraction(D_L18_001B163D,D_L18_001B163C,t);
        s->color[0]=math_lerp_int_fraction(D_L18_001B1670_GP,D_L18_001B1668_GP,t);
        s->color[1]=math_lerp_int_fraction(D_L18_001B1670[1],D_L18_001B1668[1],t);
        part_l18_spawn_random_burst(o);
        if(o->timer>(((s32)(D_L18_001B1630) * 5 + 2) / 6)) moby_set_state(o,1,-1);
        break;
    }
    if(o->timer<65535) o->timer++;
}
