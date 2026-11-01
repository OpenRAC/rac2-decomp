#include "include_asm.h"

#include "common.h"
typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad0000[0x80];
    float position[4];
    char pad0090[0x8];
    float yaw;
    char pad009C[0x54];
    char motionState[0xA0];
    char pad0190[0x10];
    float targetYaw;
    char pad01A4[0x14];
    int modeTimer;
    char pad01BC[0xA6C];
    int animFlags;
    int animBusy;
    char pad0C30[0x5F0];
    int canInteract;
    char pad1224[0x16];
    unsigned char interactBusy;
    char pad123B[0xD];
    int groundState;
    char pad124C[0xD64];
    float stickY;
    float stickX;
    char pad1FB8[0x2D8];
    char * moby;
    int moveState;
    char pad2298[0x1C];
    unsigned char disabled;
} CrankPlayer;
extern CrankPlayer D_00189E20;
extern float D_00189EB8[];
extern char D_0019B4A8[], D_0019B2E8[];
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char D_001A7A45;
typedef struct { char pad[0x464]; unsigned char collected[0]; } CrankLevelState;
extern CrankLevelState D_L06_0021E830;
typedef struct { float position[4]; float rotation[4]; } CrankCamera;
extern CrankCamera D_L06_001B9840;
extern char D_L06_0021DC20[];
extern char *D_L06_001B290C MACRO_ADDR, *D_L06_001FB760[];
extern int D_L06_001B9890[];
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern float D_L06_001B06E8 SDATA(D_L06_001B06E8);
extern char *D_L06_001B290C_sda SDATA(D_L06_001B290C);
extern float func_00283B98(float,float);
extern float func_00282E80(void *,void *);
extern float func_00283C80(float,float);
extern float func_00283248(float,float);
extern float func_00282C48(float);
extern int func_L00_0032EF10(int,int,int);
extern float func_00282E48(void *,void *);
extern int func_PAL_L00_002C4480(int,int);
extern void func_00335438(void *,void *,int,int,int);
extern void func_003353C8(void *);
extern void func_00335370(void *);
extern void func_L06_00478548(float,float);
extern void func_003355A8(int);
extern float func_002AA2E8(void *,float,float);
extern float func_00283BE0(float,float);
extern void func_L06_0039A2F0(void *,int,void *,int,void *);
extern void func_002A0430(int);
extern void func_002DF3F8(void *,void *);
extern int func_002E5CF8(int,int,void *);
extern float func_00282E20(void *);
extern void func_00282D90(void *,void *,float);
extern void func_00283410(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DB0(void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_PAL_L00_002D2668(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_002AA3A8(void *,void *,float,float,float,float);
extern void func_002AA800(void *angle, float target, int direction, float step);
extern float func_002A89A8(void *,int,float);
extern void func_00282A88(void *,int);

/* Bolt crank interaction, completion tracking and player motion around the crank. */
void func_PAL_L06_0041DED0(char *obj)
{
    float matrix[16];
    V input, motion, facing, axis, temp, delta;
    float distance;
    char *ctx=P(obj,0x68);
    float angle, turn, inputLength, targetYaw, heroZ, groundHeight, difference;
    int i, clear;
    unsigned short id;
    unsigned char *save;
    char *nearby;
    int packed;
    if (!ctx) { F(obj,0xF8)=func_00283B98(F(obj,0xF8),0.12566373f); return; }
    if (D_00189E20.moveState!=0x37 && U(obj,0x20)==3) {
        U(obj,0x20)=1;
        if (D_L06_001B9890[0]) func_003355A8(4);
        return;
    }
    switch (U(obj,0x20)) {
    case 0:
        F(ctx,0x3C)=F(obj,0x18); U(obj,0x20)=1; break;
    case 1:
        id=*(unsigned short *)(obj+0xB2);
        if (D_L06_0021E830.collected[(short)id]) goto used;
        packed=U(D_0019B4A8,((short)id>>1)+(D_001A79F0<<10));
        if ((id&1) ? ((packed>>4)&7) : (packed&7)) {
used:
            U(obj,0x20)=5; F(obj,0x18)-=0.5f; F(ctx,0)=1.0f; break;
        }
        if (func_00282E80(obj+0x10,D_00189E20.position)<1.75f && !D_00189E20.interactBusy && !D_00189E20.disabled
            && func_00283C80(D_00189E20.yaw,func_00283248(F(obj,0x10)-D_00189E20.position[0],F(obj,0x14)-D_00189E20.position[1]))<1.5707965f
            && func_00282C48(D_00189E20.position[2]-0.3f-F(obj,0x18))<0.2f && D_00189E20.groundState==10
            && D_00189E20.canInteract && func_L00_0032EF10(0x80,6,0) && (unsigned)I(ctx,0x14)>=26
            && F(obj,0x18)==F(ctx,0x3C) && F(ctx,0)<1.0f) {
            I(ctx,0x14)=0; clear=1; D_L06_001B06E8=0;
            for(i=0,nearby=D_L06_001FB760[0]; nearby; nearby=D_L06_001FB760[++i]) {
                if(func_00282E48(obj+0x10,nearby+0x10)<3.25f) {clear=0;break;}
            }
            if(clear) {
                func_PAL_L00_002C4480(0x37,1);
                func_00335438(D_L06_001B9840.position,D_L06_001B9840.rotation,3,0x96,0);
                func_003353C8(D_L06_001B290C+(I(ctx,0x20)<<7)+0x70);
                func_00335370(D_L06_001B290C+(I(ctx,0x20)<<7)+0x30);
                func_L06_00478548(F(ctx,0x28),F(ctx,0x2C));
                U(obj,0x20)=3; I(ctx,0x24)=0; F(ctx,0x18)=F(ctx,0)*6.2831854820251465f*F(ctx,0x30);
            }
            break;
        }
        if(F(ctx,0)<1.0f) {
            I(ctx,0x14)++;
            func_002AA2E8(ctx,0.0f,0.02f);
            if(F(ctx,0)>0.0f) F(obj,0xF8)=func_00283BE0(F(obj,0xF8),F(ctx,0x30)*0.12566371f);
            F(obj,0x18)+=0.010000001f;
            if(F(obj,0x18)>=F(ctx,0x3C)) F(obj,0x18)=F(ctx,0x3C);
        } else if(I(ctx,0x38)) {
            if(I(ctx,0x34)!=-1 && !(U(D_0019B2E8,U(obj,0xB0)+(D_001A79F0_gp<<4))&0x80)) {
                func_L06_0039A2F0(ctx,4,obj,2,D_L06_0021DC20); func_002A0430(U(obj,0xB0));
                if(I(ctx,0x34)!=-1) func_002DF3F8(D_L06_001B290C+(I(ctx,0x34)<<7)+0x30,D_L06_001B290C+(I(ctx,0x34)<<7)+0x70);
            }
            F(obj,0x18)-=0.010000001f;
            if(F(obj,0x18)<=F(ctx,0x3C)-0.5f) F(obj,0x18)=F(ctx,0x3C)-0.5f;
        }
        break;
    case 3:
        temp.q=0; temp.f[2]=D_L06_001B9840.rotation[2]; axis.q=temp.q;
        angle=func_00283248(D_00189E20.position[0]-F(obj,0x10),D_00189E20.position[1]-F(obj,0x14));
        if((func_L00_0032EF10(0x80,6,0) && D_00189E20.modeTimer>=51) || F(ctx,0)==1.0f) {
            func_PAL_L00_002C4480(0,1);
            if(I(ctx,0x38)) {U(obj,0x20)=1;}
            else
            if(F(ctx,0)==1.0f) {
                func_L06_0039A2F0(ctx,4,obj,2,D_L06_0021DC20); U(obj,0x20)=4;
                id=*(unsigned short *)(obj+0xB2);
                if(id&1) {
                    save=(unsigned char *)D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));
                    if(((*save>>4)&7)!=7) *save+=16;
                } else {
                    save=(unsigned char *)D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));
                    if((*save&7)!=7) ++*save;
                }
                func_002E5CF8(0,0,obj);
                if(I(ctx,0x34)!=-1 && !(U(D_0019B2E8,U(obj,0xB0)+(D_001A79F0_gp<<4))&0x80)) {
                    func_L06_0039A2F0(ctx,4,obj,2,D_L06_0021DC20); func_002A0430(U(obj,0xB0));
                    if(I(ctx,0x34)!=-1) func_002DF3F8(D_L06_001B290C_sda+(I(ctx,0x34)<<7)+0x30,D_L06_001B290C_sda+(I(ctx,0x34)<<7)+0x70);
                }
            }
            func_003355A8(3); break;
        }
        input.f[1]=-D_00189E20.stickY; input.f[0]=-D_00189E20.stickX;
        inputLength=func_00282E20(&input);
        if(inputLength>1.0f) func_00282D90(&input,&input,inputLength);
        func_00283410(matrix,&axis); func_002830C0(&input,&input,matrix);
        facing.f[0]=func_00283180(F(D_00189E20.moby,0xF8));
        facing.f[1]=func_00283198(F(D_00189E20.moby,0xF8)); I(&facing,8)=0;
        difference=func_00282DB0(&facing,&input)-F(ctx,0x1C);
        if(difference>0.0022f) difference=0.0022f;
        if(difference< -0.0022f) difference= -0.0022f;
        F(ctx,0x1C)+=difference;
        if(F(ctx,0x1C)>0.07400001f) F(ctx,0x1C)=0.07400001f;
        if(F(ctx,0x1C)<0) F(ctx,0x1C)=0;
        if(func_00282C48(F(ctx,0x1C))<0.00055f) F(ctx,0x1C)=0;
        func_00282F20(&motion,&facing,F(ctx,0x1C));
        if((D_00189E20.animFlags&2) && U(D_00189E20.moby,0x43)==0x44) func_PAL_L00_002D2668(0x3F,0,6.0f);
        if(U(D_00189E20.moby,0x43)!=0x44 && !D_00189E20.animBusy) {
            if(U(D_00189E20.moby,0x42)==0x40 && func_00282C48(F(ctx,0x1C))==0) func_PAL_L00_002D2668(0x3F,0,12.0f);
            else if(U(D_00189E20.moby,0x42)==0x3F) {if(F(ctx,0x1C)>0) func_PAL_L00_002D2668(0x40,0,12.0f);}
            else if(U(D_00189E20.moby,0x42)==0x40 && F(ctx,0x1C)>0.044400007f) func_PAL_L00_002D2668(0x41,0,12.0f);
            else if(U(D_00189E20.moby,0x42)==0x41 && F(ctx,0x1C)<0.029600004f) func_PAL_L00_002D2668(0x40,0,13.0f);
        }
        heroZ=D_00189E20.position[2]; func_00282CC0(D_00189E20.position,D_00189E20.position,&motion);
        turn=func_00283248(D_00189E20.position[0]-F(obj,0x10),D_00189E20.position[1]-F(obj,0x14));
        motion.f[0]=func_00283180(turn)*1.05f; motion.f[1]=func_00283198(turn)*1.05f; I(&motion,8)=0;
        func_00282CC0(&temp,obj+0x10,&motion); func_00282CF0(&delta,&temp,D_00189E20.position);
        I(&delta,8)=0; distance=-func_00282E20(&delta);
        func_002AA3A8(&distance,&D_L06_001B06E8,0.0f,0.0216f,0.43200004f,0.14000002f);
        func_00282F20(&delta,&delta,D_L06_001B06E8); func_00282CC0(D_00189E20.position,D_00189E20.position,&delta);
        D_00189E20.position[2]=heroZ;
        if (D_001A7A45) D_00189E20.targetYaw=func_00283B98(-1.5707964f,turn);
        else D_00189E20.targetYaw=func_00283B98(1.5707964f,turn);
        {
        /* The yaw is part of the player state at offset 0x98. */
        float *playerYaw=D_00189EB8;
        CrankPlayer *player=(CrankPlayer *)((char *)playerYaw-0x98);
        func_002AA800(playerYaw,player->targetYaw,0,0.12566373f);
        F(ctx,0x24)+=0.00392f;
        player->position[2]-=F(ctx,0x24)-2.0f;
        groundHeight=func_002A89A8(player->position,0,0.5f);
        player->position[2]-=2.0f;
        if(player->position[2]<groundHeight) {player->position[2]=groundHeight; I(ctx,0x24)=0;}
        if(U(player->moby,0x43)!=0x44) {
            targetYaw=func_00283B98(0.26179942f,turn);
            func_002AA800(obj+0xF8,targetYaw,0,0.062831864f);
            if(func_00283BE0(F(obj,0xF8),targetYaw)>1.0471977f) F(obj,0xF8)=func_00283BE0(F(obj,0xF8),1.0471977f);
            else if(func_00283BE0(F(obj,0xF8),targetYaw)< -1.0471977f) F(obj,0xF8)=func_00283B98(F(obj,0xF8),1.0471977f);
        }
        F(ctx,0x18)+=func_00283C80(turn,angle);
        F(ctx,0)=F(ctx,0x18)/(F(ctx,0x30)*6.2831854820251465f);
        if(F(ctx,0)>1) F(ctx,0)=1;
        if(F(ctx,0)<0) F(ctx,0)=0;
        func_00282A88(D_00189E20.motionState,0xA0);
        }
        break;
    case 4: {
        float bottom;
        F(obj,0x18)-=0.010000001f;
        bottom=F(ctx,0x3C)-0.5f;
        if(F(obj,0x18)<=bottom) {
            F(obj,0x18)=bottom;
            U(obj,0x20)=5;
            F(ctx,0)=1.0f;
        }
        break;
    }
    case 5: F(ctx,0)=1.0f; break;
    }
}
