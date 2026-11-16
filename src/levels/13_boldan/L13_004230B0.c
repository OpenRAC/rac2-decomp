/* Update the vertical platform, its motion sound, and its pulsing tint.
 * State 1 checks the automatic height transitions after handling its trigger.
 */
#include "common.h"
#define I(p, o) (*(int *)((u8 *)(p)+(o)))
#define P(p, o) (*(u8 **)((u8 *)(p)+(o)))
#define F(p, o) (*(float *)((u8 *)(p)+(o)))
typedef struct {
    u8 pad0[0x88]; float height;
    u8 pad8c[0x33C-0x8C]; u8 *platform;
    u8 pad340[0x2294-0x340]; int mode;
} PlatformHero;
extern PlatformHero g_hero_state;
extern u8 g_sound_state[] NOT_SDA;
extern u8 *g_hit_l13_result;
extern int g_game_l13_frame_counter MACRO_ADDR;
extern void snd_stop_voice(int);
extern int hero_is_current_selected_id(void *);
extern u8 *cam_alloc_override_slot(int);
extern void cam_end_override(void *);
extern void moby_set_state(void *,int,int);
extern int coll_test_point(void *,int,void *,float);
extern int PlayMobySound(int,int,void *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
void UpdateBoldanVerticalPlatform(u8 *moby) {
    u8 *vars=P(moby,0x68);
    u8 oldpos[16] __attribute__((aligned(16)));
    u8 oldrot[16] __attribute__((aligned(16)));
    u8 delta[16] __attribute__((aligned(16)));
    int sound_id;
    unsigned int pulse, color;
    int tickPhase;
    float phase;
    if(g_hero_state.mode==0x82) return;
    qcopy_nc(oldpos,moby+0x10);
    qcopy_nc(oldrot,moby+0xF0);
    switch(moby[0x20]) {
    case 0:
        moby[0x30]=255;
        I(vars,0x7C)=I(vars,0x78);
        I(vars,0x5C)|=1;
        qcopy_nc(vars+0x90,moby+0x10);
        qcopy_nc(vars+0x80,vars+0x90);
        F(vars,0x88)=F(vars,0x98)-F(vars,0x68);
        I(vars,0x60)=I(vars,0x74);
        moby[0x20]=1;
        I(vars,0xB0)=-1;
        I(vars,0x64)=0;
        break;
    case 1:
        sound_id=I(vars,0xB0);
        if(sound_id!=-1) {
            u8 *sound=g_sound_state+sound_id*0x70; if(P(sound,0x88)==moby && sound[0x74]) snd_stop_voice(sound_id);
        }
        I(vars,0xB0)=-1;
        if(hero_is_current_selected_id(moby)) {
            if(F(moby,0x18)==F(vars,0x98)) {
                if(I(vars,0xB4)) {
                    P(vars,0xB8)=cam_alloc_override_slot(5);
                    F(P(vars,0xB8),0)=1.0f;
                    F(P(vars,0xB8),4)=4.5f;
                    I(vars,0xBC)=1;
                }
                moby_set_state(moby,2,-1);
            } else {
                if(I(vars,0xB4)) {
                    P(vars,0xB8)=cam_alloc_override_slot(5);
                    F(P(vars,0xB8),0)=1.0f;
                    F(P(vars,0xB8),4)=4.5f;
                    I(vars,0xBC)=1;
                }
                moby_set_state(moby,3,-1);
            }
        }
        {
            if(F(moby,0x18)-g_hero_state.height>F(vars,0x68)*0.5f && F(moby,0x18)==F(vars,0x98)) moby_set_state(moby,2,-1);
            else if(F(moby,0x18)-g_hero_state.height<-F(vars,0x68)*0.5f && F(moby,0x18)==F(vars,0x88) && g_hero_state.mode!=0x82) moby_set_state(moby,3,-1);
        }
        break;
    case 2:
        if(F(moby,0x18)<=F(vars,0x88)) {
            if(I(vars,0xBC)) { cam_end_override(P(vars,0xB8)); I(vars,0xBC)=0; }
            sound_id=I(vars,0xB0);
            if(sound_id!=-1) { u8 *sound=g_sound_state+sound_id*0x70; if(P(sound,0x88)==moby && sound[0x74]) snd_stop_voice(sound_id); }
            I(vars,0xB0)=-1;
            if(!hero_is_current_selected_id(moby)) moby[0x20]=1;
        } else if(!coll_test_point(moby+0x10,1,moby,2.8f) ||
            (F(moby,0x18)<=g_hero_state.height || (g_hero_state.platform!=0 && g_hero_state.platform==moby) || (g_hit_l13_result && *(short *)(g_hit_l13_result+0xAA)==0xEA3))) {
            { u8 *sound=g_sound_state+I(vars,0xB0)*0x70; if(P(sound,0x88)!=moby || !sound[0x74]) I(vars,0xB0)=PlayMobySound(0,4,moby); }
            math_step_value_toward_target((float *)(moby+0x18),(float *)(vars+0x64),F(vars,0x88),0.00194444449f,0.00166666671f,0.100000009f);
        } else {
            sound_id=I(vars,0xB0);
            if(sound_id!=-1) { u8 *sound=g_sound_state+sound_id*0x70; if(P(sound,0x88)==moby && sound[0x74]) snd_stop_voice(sound_id); }
            I(vars,0xB0)=-1;
        }
        break;
    case 3:
        math_step_value_toward_target((float *)(moby+0x18),(float *)(vars+0x64),F(vars,0x98),0.00194444449f,0.00166666671f,0.100000009f);
        if(F(moby,0x18)>=F(vars,0x98)) {
            if(I(vars,0xBC)) { cam_end_override(P(vars,0xB8)); I(vars,0xBC)=0; }
            sound_id=I(vars,0xB0);
            if(sound_id!=-1) { u8 *sound=g_sound_state+sound_id*0x70; if(P(sound,0x88)==moby && sound[0x74]) snd_stop_voice(sound_id); }
            I(vars,0xB0)=-1;
            if(!hero_is_current_selected_id(moby)) { I(vars,0x60)=I(vars,0x74); --I(vars,0x78); moby[0x20]=1; }
        } else {
            { u8 *sound=g_sound_state+I(vars,0xB0)*0x70; if(P(sound,0x88)!=moby || !sound[0x74]) I(vars,0xB0)=PlayMobySound(0,4,moby); }
        }
        break;
    case 4:
        sound_id=I(vars,0xB0);
        if(sound_id!=-1) { u8 *sound=g_sound_state+sound_id*0x70; if(P(sound,0x88)==moby && sound[0x74]) snd_stop_voice(sound_id); }
        I(vars,0xB0)=-1; break;
    }
    phase=(float)g_game_l13_frame_counter*(1.0f/60.0f);
    tickPhase=(int)phase;
    phase-=(float)tickPhase;
    if(!(tickPhase&1)) phase=1.0f-phase;
    pulse=(int)(phase*255.0f);
    color=(pulse<<8)|0x7F000000;
    I(moby,0x78)=(pulse<<16)|color|pulse;
    FastVecSub(delta,moby+0x10,oldpos);
    mat_combine_and_store(vars+0x20,delta,oldrot,moby+0xF0);
}
