#include "names.h"
/* func_PAL_L13_004280E8, the PAL copy of func_L13_004230B0: the same C, where rename func_L00_002D70A0 becomes func_PAL_L00_002D7850; expr 0.016666668f becomes 0.02f; scale I(d,0x74); scale I(d,0x78); lit 6 becomes 5. */
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
extern u8 *D_L13_001BFD18;
extern int D_L13_001B2448 MACRO_ADDR;
extern void snd_stop_voice(int);
extern int hero_is_current_selected_id(void *);
extern u8 *func_PAL_L00_002D7850(int);
extern void cam_end_override(void *);
extern void moby_set_state(void *,int,int);
extern int coll_test_point(void *,int,void *,float);
extern int PlayMobySound(int,int,void *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
void func_PAL_L13_004280E8(u8 *m) {
    u8 *d=P(m,0x68);
    u8 oldpos[16] __attribute__((aligned(16)));
    u8 oldrot[16] __attribute__((aligned(16)));
    u8 delta[16] __attribute__((aligned(16)));
    int n;
    unsigned int c, color;
    int tickPhase;
    float f;
    if(g_hero_state.mode==0x82) return;
    qcopy_nc(oldpos,m+0x10);
    qcopy_nc(oldrot,m+0xF0);
    switch(m[0x20]) {
    case 0:
        m[0x30]=255;
        I(d,0x7C)=I(d,0x78);
        I(d,0x5C)|=1;
        qcopy_nc(d+0x90,m+0x10);
        qcopy_nc(d+0x80,d+0x90);
        F(d,0x88)=F(d,0x98)-F(d,0x68);
        I(d,0x60)=(((int)(I(d,0x74)) * 5 + 2) / 6);
        m[0x20]=1;
        I(d,0xB0)=-1;
        I(d,0x64)=0;
        break;
    case 1:
        n=I(d,0xB0);
        if(n!=-1) {
            u8 *sound=g_sound_state+n*0x70; if(P(sound,0x88)==m && sound[0x74]) snd_stop_voice(n);
        }
        I(d,0xB0)=-1;
        if(hero_is_current_selected_id(m)) {
            if(F(m,0x18)==F(d,0x98)) {
                if(I(d,0xB4)) {
                    P(d,0xB8)=func_PAL_L00_002D7850(5);
                    F(P(d,0xB8),0)=1.0f;
                    F(P(d,0xB8),4)=4.5f;
                    I(d,0xBC)=1;
                }
                moby_set_state(m,2,-1);
            } else {
                if(I(d,0xB4)) {
                    P(d,0xB8)=func_PAL_L00_002D7850(5);
                    F(P(d,0xB8),0)=1.0f;
                    F(P(d,0xB8),4)=4.5f;
                    I(d,0xBC)=1;
                }
                moby_set_state(m,3,-1);
            }
        }
        {
            if(F(m,0x18)-g_hero_state.height>F(d,0x68)*0.5f && F(m,0x18)==F(d,0x98)) moby_set_state(m,2,-1);
            else if(F(m,0x18)-g_hero_state.height<-F(d,0x68)*0.5f && F(m,0x18)==F(d,0x88) && g_hero_state.mode!=0x82) moby_set_state(m,3,-1);
        }
        break;
    case 2:
        if(F(m,0x18)<=F(d,0x88)) {
            if(I(d,0xBC)) { cam_end_override(P(d,0xB8)); I(d,0xBC)=0; }
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=g_sound_state+n*0x70; if(P(sound,0x88)==m && sound[0x74]) snd_stop_voice(n); }
            I(d,0xB0)=-1;
            if(!hero_is_current_selected_id(m)) m[0x20]=1;
        } else if(!coll_test_point(m+0x10,1,m,2.8f) ||
            (F(m,0x18)<=g_hero_state.height || (g_hero_state.platform!=0 && g_hero_state.platform==m) || (D_L13_001BFD18 && *(short *)(D_L13_001BFD18+0xAA)==0xEA3))) {
            { u8 *sound=g_sound_state+I(d,0xB0)*0x70; if(P(sound,0x88)!=m || !sound[0x74]) I(d,0xB0)=PlayMobySound(0,4,m); }
            math_step_value_toward_target((float *)(m+0x18),(float *)(d+0x64),F(d,0x88),0.0028000001f,0.0024f,0.120000005f);
        } else {
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=g_sound_state+n*0x70; if(P(sound,0x88)==m && sound[0x74]) snd_stop_voice(n); }
            I(d,0xB0)=-1;
        }
        break;
    case 3:
        math_step_value_toward_target((float *)(m+0x18),(float *)(d+0x64),F(d,0x98),0.0028000001f,0.0024f,0.120000005f);
        if(F(m,0x18)>=F(d,0x98)) {
            if(I(d,0xBC)) { cam_end_override(P(d,0xB8)); I(d,0xBC)=0; }
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=g_sound_state+n*0x70; if(P(sound,0x88)==m && sound[0x74]) snd_stop_voice(n); }
            I(d,0xB0)=-1;
            if(!hero_is_current_selected_id(m)) { I(d,0x60)=(((int)(I(d,0x74)) * 5 + 2) / 6); --I(d,0x78); m[0x20]=1; }
        } else {
            { u8 *sound=g_sound_state+I(d,0xB0)*0x70; if(P(sound,0x88)!=m || !sound[0x74]) I(d,0xB0)=PlayMobySound(0,4,m); }
        }
        break;
    case 4:
        n=I(d,0xB0);
        if(n!=-1) { u8 *sound=g_sound_state+n*0x70; if(P(sound,0x88)==m && sound[0x74]) snd_stop_voice(n); }
        I(d,0xB0)=-1; break;
    }
    f=(float)D_L13_001B2448*(0.02f);
    tickPhase=(int)f;
    f-=(float)tickPhase;
    if(!(tickPhase&1)) f=1.0f-f;
    c=(int)(f*255.0f);
    color=(c<<8)|0x7F000000;
    I(m,0x78)=(c<<16)|color|c;
    FastVecSub(delta,m+0x10,oldpos);
    mat_combine_and_store(d+0x20,delta,oldrot,m+0xF0);
}
