#include "common.h"
extern int D_001A79F0 MACRO_ADDR;
extern short D_0018A16E NOT_SDA;
extern unsigned char D_0019B278[];
extern char D_00189E20[];
extern int D_L01_001B22A8;
extern float D_L01_001AF50C __attribute__((sda));
extern float D_L01_001AF510 __attribute__((sda));
extern float D_L01_001AF514 __attribute__((sda));
extern float D_L01_001AF51C __attribute__((sda));
extern float D_L01_001AF528 __attribute__((sda));
extern float D_L01_001AF520 __attribute__((sda));
extern float D_L01_001AF524 __attribute__((sda));
extern int D_L01_001AF54C __attribute__((sda));
extern int D_L01_001AF550 __attribute__((sda));
extern int D_L01_001B21B0 __attribute__((sda));
extern int D_L01_001B1FA8 __attribute__((sda));
extern float func_002A7940(void);
extern float func_00283198(float);
extern float func_00283B98(float,float);
extern float func_00282E80(void*,void*);
extern float func_00282C48(float);
extern int func_002A77E0(int);
extern void func_L01_00397950(void*),func_L01_00397A28(void*),func_L01_00397EB0(void*),func_L01_00397110(void*),func_L01_00397C98(void*),func_L01_00397870(void*);
extern void func_002B0A18(int,int),func_0029B3E0(int,int),func_002E5CF8(int,int,void*),func_0029F338(void*),func_002A7750(void*,int,int),func_002A7470(void*,int,int,int);
extern void func_L00_002D2168(int,int,float),func_L00_002B9D60(void*,void*,int,int),func_003355A8(int);
extern int func_00282948(void*);

/* Updates the Platinum Bolt: it floats and spins, throws off sparkles, and is collected when the hero touches it. */
void func_L01_003973A0(unsigned char *moby)
{
    char *vars = *(char **)(moby+0x68);
    int i;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (*(int *)vars == -1 || D_0019B278[*(int *)vars + (gCurrentMapIndex << 2)]) goto remove;
        {
            qcopy_nc(vars+0x10,moby+0x10);
            *(float *)(vars+0x1C)=*(float *)(moby+0xF8);
            *(float *)(moby+0xF0)=RandomAngle();
            *(float *)(moby+0xF4)=RandomAngle();
            *(float *)(moby+0xF8)=RandomAngle();
            ((float *)moby)[0xFC/4]=RandomAngle();
            ((float *)vars)[0x68/4]=D_L01_001AF51C*0.0002908882452175021f;
            ((float *)vars)[0x64/4]=D_L01_001AF520*0.0002908882452175021f;
            ((float *)vars)[0x60/4]=D_L01_001AF524*0.0002908882452175021f;
            if (*(short *)(moby+0x32)<64) *(short *)(moby+0x32)=64;
            moby[0x20]=1;
            InitRandomizedMobyVars(moby);
        }
        break;
    case 1: {
        char *player;
        *(float *)(moby+0x2C)=*(float *)(*(char **)(moby+0x24)+0x24)*D_L01_001AF50C;
        {
            float phase = FastSinOrCosB(*(float *)(moby+0xFC));
            float height = *(float *)(vars+0x18)+D_L01_001AF510+D_L01_001AF514*phase;
            float step = D_L01_001AF51C*0.0002908882452175021f;
            float angle;
            *(float *)(moby+0x18)=height;
            angle=FastAddRotations(*(float *)(moby+0xF0),step);
            step=D_L01_001AF520*0.0002908882452175021f;
            *(float *)(moby+0xF0)=angle;
            angle=FastAddRotations(*(float *)(moby+0xF4),step);
            step=D_L01_001AF524*0.0002908882452175021f;
            *(float *)(moby+0xF4)=angle;
            angle=FastAddRotations(*(float *)(moby+0xF8),step);
            step=D_L01_001AF528*0.0002908882452175021f;
            *(float *)(moby+0xF8)=angle;
            *(float *)(moby+0xFC)=FastAddRotations(*(float *)(moby+0xFC),step);
        }
        DrawBoltGlowRings(moby);
        if (!RandomIntBelow(D_L01_001AF54C)) SpawnSparkleTrailAboveGround(moby);
        player=gHeroState+0x80;
        if (!(vec_distance_xy(moby+0x10,player)<3.0f)) break;
        player -= 0x80;
        if (FloatAbs(*(float *)(moby+0x18)-*(float *)(player+0x88))<2.0f &&
            *(int *)(player+0x24CC) &&
            ((unsigned char)player[0x22B4]==3 || !player[0x22B4])) {
            if (!*(short *)(vars+0xC) && *(int *)(player+0x2294)!=0x31) goto inactive;
            D_L01_001B21B0=180;
            SetEntryValueByIndex(0x124B,-1);
            D_0019B278[*(int *)vars+(gCurrentMapIndex<<2)]=1;
            D_L01_001AF550++;
            MemcardSave(0,-1);
            PlayMobySound(1,0,moby);
        remove:
            MarkMobySpawned(moby);
        }
        break;
    }
    inactive:
        if (*(int *)(vars+0x78)) {
            *(unsigned short *)(moby+0x34) |= 0x41;
            SetMobyState(moby,3,-1);
            break;
        }
        goto initialize;
    case 3:
        if (D_0018A16E) break;
    initialize:
        StartTeleporterArrival(moby);
        break;
    case 2: {
        {
            char *player = gHeroState;
            D_L01_001B22A8=1;
            *(short *)(player+0x1DC)=3;
            UpdateCameraBlendMoby(moby);
            qcopy_nc(moby+0x10,player+0x80);
            player += 0x90;
            qcopy_nc(moby+0xF0,player);
        }
        if ((unsigned char)moby[0x42]==1) {
            UpdateBobbingMoby_L01(moby);
            if (!RandomIntBelow(10)) SpawnSparkleTrailAboveGround(moby);
            if (moby[0x60]&2) {
                if (moby[0x43]) StartAnimationBlended(moby,0,0,0);
                *(unsigned short *)(moby+0x34)|=1;
                moby[0x31]=0;
                for (i=3;i>=0;i--) SpawnSparkleTrailAboveGround(moby);
            }
        }
        {
        char *player = gHeroState;
        if (*(int *)(player+0xC28)&2) set_hero_animation(0,0,30.0f);
        if (!moby[0x42] && FastFloatHelperD(vars+0x6C)) {
            D_L01_001B21B0=180;
            SetEntryValueByIndex(0x124B,-1);
            D_0019B278[*(int *)vars+(gCurrentMapIndex<<2)]=1;
            D_L01_001AF550++;
            D_L01_001B1FA8=0;
            ResetHeroPositionAndDirection(player+0x80,player+0x90,0,0);
            SetCameraModeState(0);
            MemcardSave(0,-1);
            MarkMobySpawned(moby);
        }
        }
        break;
    }
    }
}
