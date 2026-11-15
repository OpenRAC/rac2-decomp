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
extern PlatformHero D_00189E20;
extern u8 D_00188660[] NOT_SDA;
extern u8 *D_L13_001BFD18;
extern int D_L13_001B2448 MACRO_ADDR;
extern void func_002E59F8(int);
extern int func_L00_00324120(void *);
extern u8 *func_L00_002D70A0(int);
extern void func_L00_002D7140(void *);
extern void func_002A7750(void *,int,int);
extern int func_00277258(void *,int,void *,float);
extern int func_002E5CF8(int,int,void *);
extern void func_002AA548(float *,float *,float,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
void func_L13_004230B0(u8 *moby) {
    u8 *vars=P(moby,0x68);
    u8 oldpos[16] __attribute__((aligned(16)));
    u8 oldrot[16] __attribute__((aligned(16)));
    u8 delta[16] __attribute__((aligned(16)));
    int soundId;
    unsigned int pulse, color;
    int tickPhase;
    float phase;
    if(gHeroState.mode==0x82) return;
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
        soundId=I(vars,0xB0);
        if(soundId!=-1) {
            u8 *sound=gSoundState+soundId*0x70; if(P(sound,0x88)==moby && sound[0x74]) StopSoundVoice(soundId);
        }
        I(vars,0xB0)=-1;
        if(IsCurrentSelectedId(moby)) {
            if(F(moby,0x18)==F(vars,0x98)) {
                if(I(vars,0xB4)) {
                    P(vars,0xB8)=AllocCameraOverrideSlot(5);
                    F(P(vars,0xB8),0)=1.0f;
                    F(P(vars,0xB8),4)=4.5f;
                    I(vars,0xBC)=1;
                }
                SetMobyState(moby,2,-1);
            } else {
                if(I(vars,0xB4)) {
                    P(vars,0xB8)=AllocCameraOverrideSlot(5);
                    F(P(vars,0xB8),0)=1.0f;
                    F(P(vars,0xB8),4)=4.5f;
                    I(vars,0xBC)=1;
                }
                SetMobyState(moby,3,-1);
            }
        }
        {
            if(F(moby,0x18)-gHeroState.height>F(vars,0x68)*0.5f && F(moby,0x18)==F(vars,0x98)) SetMobyState(moby,2,-1);
            else if(F(moby,0x18)-gHeroState.height<-F(vars,0x68)*0.5f && F(moby,0x18)==F(vars,0x88) && gHeroState.mode!=0x82) SetMobyState(moby,3,-1);
        }
        break;
    case 2:
        if(F(moby,0x18)<=F(vars,0x88)) {
            if(I(vars,0xBC)) { EndCameraOverride(P(vars,0xB8)); I(vars,0xBC)=0; }
            soundId=I(vars,0xB0);
            if(soundId!=-1) { u8 *sound=gSoundState+soundId*0x70; if(P(sound,0x88)==moby && sound[0x74]) StopSoundVoice(soundId); }
            I(vars,0xB0)=-1;
            if(!IsCurrentSelectedId(moby)) moby[0x20]=1;
        } else if(!TestPointAgainstCollision(moby+0x10,1,moby,2.8f) ||
            (F(moby,0x18)<=gHeroState.height || (gHeroState.platform!=0 && gHeroState.platform==moby) || (D_L13_001BFD18 && *(short *)(D_L13_001BFD18+0xAA)==0xEA3))) {
            { u8 *sound=gSoundState+I(vars,0xB0)*0x70; if(P(sound,0x88)!=moby || !sound[0x74]) I(vars,0xB0)=PlayMobySound(0,4,moby); }
            StepValueTowardTarget((float *)(moby+0x18),(float *)(vars+0x64),F(vars,0x88),0.00194444449f,0.00166666671f,0.100000009f);
        } else {
            soundId=I(vars,0xB0);
            if(soundId!=-1) { u8 *sound=gSoundState+soundId*0x70; if(P(sound,0x88)==moby && sound[0x74]) StopSoundVoice(soundId); }
            I(vars,0xB0)=-1;
        }
        break;
    case 3:
        StepValueTowardTarget((float *)(moby+0x18),(float *)(vars+0x64),F(vars,0x98),0.00194444449f,0.00166666671f,0.100000009f);
        if(F(moby,0x18)>=F(vars,0x98)) {
            if(I(vars,0xBC)) { EndCameraOverride(P(vars,0xB8)); I(vars,0xBC)=0; }
            soundId=I(vars,0xB0);
            if(soundId!=-1) { u8 *sound=gSoundState+soundId*0x70; if(P(sound,0x88)==moby && sound[0x74]) StopSoundVoice(soundId); }
            I(vars,0xB0)=-1;
            if(!IsCurrentSelectedId(moby)) { I(vars,0x60)=I(vars,0x74); --I(vars,0x78); moby[0x20]=1; }
        } else {
            { u8 *sound=gSoundState+I(vars,0xB0)*0x70; if(P(sound,0x88)!=moby || !sound[0x74]) I(vars,0xB0)=PlayMobySound(0,4,moby); }
        }
        break;
    case 4:
        soundId=I(vars,0xB0);
        if(soundId!=-1) { u8 *sound=gSoundState+soundId*0x70; if(P(sound,0x88)==moby && sound[0x74]) StopSoundVoice(soundId); }
        I(vars,0xB0)=-1; break;
    }
    phase=(float)D_L13_001B2448*(1.0f/60.0f);
    tickPhase=(int)phase;
    phase-=(float)tickPhase;
    if(!(tickPhase&1)) phase=1.0f-phase;
    pulse=(int)(phase*255.0f);
    color=(pulse<<8)|0x7F000000;
    I(moby,0x78)=(pulse<<16)|color|pulse;
    FastVecSub(delta,moby+0x10,oldpos);
    CombineTransformsAndStore(vars+0x20,delta,oldrot,moby+0xF0);
}
