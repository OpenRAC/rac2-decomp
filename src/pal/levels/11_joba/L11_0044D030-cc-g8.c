/* func_PAL_L11_0044D030, the PAL copy of func_L11_004475A0: the same C, where rename func_L11_004484A8 becomes func_PAL_L11_0044DF38; rename func_L11_00448908 becomes func_PAL_L11_0044E398; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L02_003D1588 becomes func_PAL_L02_003D55D8; rename func_L02_00333438 becomes func_PAL_L02_00335630; rename func_L01_00321178 becomes func_PAL_L01_00323068; rename func_L02_003D1610 becomes func_PAL_L02_003D5660; rename func_L11_00449C70 becomes func_PAL_L11_0044F730; rename func_002B4FF0 becomes func_PAL_002B5BA8; rename func_L11_00448AA8 becomes func_PAL_L11_0044E538; rename func_L11_00340500 becomes func_PAL_L11_00342578; rename func_002B5278 becomes func_PAL_002B5E30; .... */
#include "common.h"
typedef int Quad004475A0 __attribute__((mode(TI)));
extern void func_L11_00449878(char *);
extern int D_L11_001A8FF4;
extern char D_00189EA0[];
extern char *D_0018C2BC NOT_SDA;
extern void func_PAL_L11_0044DF38(char *);
extern void func_PAL_L11_0044E398(char *);
extern void func_L11_00448848(char *);
extern void func_L11_00449098(char *);
extern void func_PAL_L02_003D55D8(char *);
extern void func_PAL_L02_003D5660(char *);
extern int func_PAL_L11_0044E538(char *);
extern int func_PAL_L11_0044F730(char *);
extern void func_L11_00449AD8(char *,char *);
extern void func_PAL_L11_0044EDC0(char *,void *);
extern float func_L02_003D1820(char *,void *);
extern char *func_L11_004417E8(int);
extern int func_L11_00441808(int,void *);
extern void func_PAL_L02_004009A0(char *,int,int);
extern void func_L01_003E9CF8(char *,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_002B04E0(char *,void *,void *);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_00282E48(void *,void *);
extern float func_L02_002F21C0(void *,void *);
extern int func_002B3890(char *);
extern int func_002B3868(char *);
extern void func_PAL_002A7E68(char *,int,int,int);
extern void func_002A7750(char *,int,int);
extern int func_002A77E0(int);
extern void func_PAL_L02_00335630(char *,void *);
extern void func_PAL_L01_00323068(char *,void *);
extern void func_PAL_002B5BA8(char *,void *,float);
extern void func_PAL_L11_00342578(char *,void *);
extern void func_PAL_002B5E30(char *,float);
extern int func_002B1C20(char *,void *);
extern void func_00282A60(void *,int,int);
extern void func_0029F978(char *,int,void *);
extern void func_002A7A00(void *,float,float);
extern void func_PAL_002B15D8(char *,int,void *,float,float,float,float,int);
extern void func_002B60B0(char *,float,float,float,float);
extern float func_0029F530(char *);
extern void func_PAL_L11_00342558(char *);
extern void func_PAL_002B5E10(char *);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_002AB6D8(void *,void *);
extern void func_L07_00321D68(char *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002B4090(char *,void *,float,float,float);
extern void func_002833F0(void *,void *);

void func_PAL_L11_0044D030(char *self)
{
    float target[4], temp[4], matrix[16];
    char *state;
    char *point, *p;
    float angle, difference, distance, time, old, turn;
    int flags = 0, i;
    state=*(char **)(self+0x68);
    if (*(u8 *)(self+0x20)==1) return;
    if (*(short *)(state+0x36E) && !D_L11_001A8FF4 &&
        *(u8 *)(self+0x20)!=18 && *(u8 *)(self+0x20)!=17) return;
    func_PAL_L11_0044DF38(self);
    if (*(u8 *)(self+0x20)==1) return;
    if (*(short *)(state+0x366)==0) {
        unsigned char phase;
        *(int *)(state+0x350)=0;
        phase=*(u8 *)(self+0x95);
        if (phase!=0 && phase!=2 && phase!=1 && phase!=7 && phase!=8) func_PAL_L11_0044E398(self);
    }
    if (*(char **)(state+0x350)) *(Quad004475A0 *)target=*(Quad004475A0 *)(*(char **)(state+0x350)+0x10);
    else *(Quad004475A0 *)target=*(Quad004475A0 *)D_00189EA0;
    if (*(short *)(state+0x36E)) {
        func_00282CF0(temp,target,self+0x10);
        point=self+0x10;
        angle=0.0f;
        difference=func_002B04E0(self,temp,state+0x2F0);
    } else {
        float x=target[0], y=target[1];
        point=self+0x10;
        x-=*(float *)(self+0x10);
        y-=*(float *)(self+0x14);
        angle=func_00283248(x,y);
        difference=func_00283C80(angle,*(float *)(self+0xF8));
    }
    distance=func_00282E48(point,target);
    switch (*(u8 *)(self+0x95)) {
    case 2:
        if (func_002B3890(self)) {
            p=func_L11_004417E8(*(int *)(self+0xB8));
            if (*(u8 *)(self+0x43)!=3) func_PAL_002A7E68(self,3,0,8);
            *(u8 *)(self+0xBC)=0;
            func_L11_00449AD8(self,p);
            *(u16 *)(self+0x96)=10000;
        }
        if (*(u8 *)(self+0xBC)==1 && *(u16 *)(self+0x96)>250) {
            int choice=func_002A77E0(2);
            switch(choice) {
            case 0: if (*(u8 *)(self+0x43)!=1) func_PAL_002A7E68(self,1,0,8); break;
            case 1: if (*(u8 *)(self+0x43)!=0) func_PAL_002A7E68(self,0,0,8); break;
            }
            *(u16 *)(self+0x96)=func_002A77E0(83);
        }
        if (*(short *)(state+0x366)) func_PAL_L02_003D55D8(self);
        if (*(u8 *)(self+0xBC)==0) {
            p=state+0x330;
            if (func_L02_002F21C0(point,p)<4.0f) *(u8 *)(self+0xBC)=1;
            if (*(short *)(state+0x36E)) func_PAL_L02_00335630(self,p);
            else func_PAL_L01_00323068(self,p);
        } else {
            if (*(short *)(state+0x36E)) func_PAL_L02_00335630(self,point);
            else func_PAL_L01_00323068(self,point);
        }
        break;
    case 5:
        if (*(u8 *)(self+0x60)&2) func_PAL_L02_003D5660(self);
        break;
    case 3:
        if (*(short *)(state+0x36E)) func_PAL_L02_00335630(self,target);
        else if (!func_PAL_L11_0044F730(self)) {
            switch(*(u8 *)(self+0x42)) {
            case 2: func_PAL_L01_00323068(self,target); break;
            case 3: func_PAL_002B5BA8(self,target,*(float *)(state+0x358)); break;
            }
        }
        break;
    case 4:
        if (distance>14.0f) func_PAL_L02_003D55D8(self);
        else if (!func_PAL_L11_0044E538(self)) {
            if (distance<4.0f && difference<0.2617994248867035f) func_002A7750(self,11,-1);
            else if (*(u8 *)(self+0x20)==11 && distance>5.0f) func_002A7750(self,10,-1);
        }
        break;
    case 6:
        if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);
        else func_PAL_002B5E30(self,angle);
        break;
    case 7:
        flags=func_002B1C20(self,state+0x50);
        if (*(float *)(state+0x20)<=1.0f && *(char **)(state+0x354)) {
            *(Quad004475A0 *)temp=*(Quad004475A0 *)(*(char **)(state+0x354)+0x10);
            func_PAL_L11_0044EDC0(self,temp);
        }
        if (*(float *)(state+0x20)<=0.0f && !*(u8 *)(state+0x2B1)) {
            func_00282A60(state+0x2B0,0,0x40);
            func_0029F978(self,3,state+0x2B0);
            *(u8 *)(state+0x2B2)=1;
            *(float *)(state+0x2D8)=0.0001f;
            *(float *)(state+0x2D4)=0.0001f;
            *(float *)(state+0x2D0)=0.0001f;
            func_002A7A00(temp,0.020000001f,0.060000002f);
            func_PAL_002B15D8(self,0x20,temp,3.0f,6.0f,3.0f,6.0f,255);
            if (*(short *)(state+0x36E) && !func_002A77E0(2)) {
                func_002A7750(self,18,8);
                return;
            }
        }

        if ((flags&1) || (*(float *)(state+0x20)<=0.0f && *(u16 *)(self+0x96)>50)) {
            *(int *)(self+0x98)=0;
            func_PAL_L02_004009A0(self,0,-1);
            func_L01_003E9CF8(self,0,func_L11_00449878);
        }
        break;
    }
    switch (*(u8 *)(self+0x20)) {
    case 3:
        if (func_002B3868(self)) {
            *(u8 *)(self+0xBC)=0;
            if (*(u8 *)(self+0x43)!=0) func_PAL_002A7E68(self,0,0,0);
            *(u16 *)(self+0x96)=0;
        }
        if (*(u8 *)(self+0xBC)==0) {
            if (*(short *)(state+0x36C)<*(u16 *)(self+0x96)) {
                if (*(u8 *)(self+0x43)!=3) func_PAL_002A7E68(self,3,0,8);
                *(u8 *)(self+0xBC)=1;
                break;
            }
        }
        if (*(u8 *)(self+0xBC)==1) {
            if (func_L11_00441808(*(int *)(self+0xB8),point)) func_002A7750(self,4,2);
            func_PAL_L01_00323068(self,func_L11_004417E8(*(int *)(self+0xB8)));
        }
        break;
    case 7:
        if (func_002B3868(self)) *(u16 *)(self+0x96)=0;
        if (distance<4.0f || *(u16 *)(self+0x96)>375 || *(int *)(state+0x180)>=26) func_PAL_L02_003D55D8(self);
        break;
    case 6:
        if (distance>14.0f) {
            func_002B60B0(self,0.008f,0.124000005f,0.005026549f,0.5026549f);
            func_002A7750(self,7,3);
            if (*(u8 *)(self+0x43)!=3) func_PAL_002A7E68(self,3,0,8);
        } else if (distance<4.0f || *(int *)(state+0x180)>=26) func_PAL_L02_003D5660(self);
        break;
    case 10:
        time=func_0029F530(self);
        turn=func_L02_003D1820(self,target);
        if (turn>0.01f) {
            func_002A7750(self,9,-1);
            if (*(u8 *)(self+0x43)!=5) func_PAL_002A7E68(self,5,0,8);
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);
            else func_PAL_002B5E30(self,angle);
        } else if (turn< -0.01f) {
            func_002A7750(self,8,-1);
            if (*(u8 *)(self+0x43)!=4) func_PAL_002A7E68(self,4,0,8);
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);
            else func_PAL_002B5E30(self,angle);
        } else if (distance<4.0f) {func_002A7750(self,11,-1);}
        else if (time<2.0f) {
            func_002B60B0(self,0.008f,0.040000003f,0.005026549f,0.5026549f);
            if (*(short *)(state+0x36E)) func_PAL_L02_00335630(self,target);
            else func_PAL_L01_00323068(self,target);
        } else if (time>10.0f && func_0029F530(self)<17.0f) {
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);
            else func_PAL_002B5E30(self,angle);
        } else if (time<20.0f) {
            if (*(short *)(state+0x36E)) func_PAL_L02_00335630(self,target);
            else func_PAL_L01_00323068(self,target);
        } else {
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);
            else func_PAL_002B5E30(self,angle);
        }
        break;
    case 8:
        if (func_L02_003D1820(self,target)> -0.01f) {
            func_002A7750(self,10,-1);
            if (*(u8 *)(self+0x43)!=6) func_PAL_002A7E68(self,6,0,8);
            if (*(short *)(state+0x36E)) func_PAL_L11_00342558(self);else func_PAL_002B5E10(self);
        } else if (func_0029F530(self)>5.0f) {
            old=*(float *)(state+0x130);*(float *)(state+0x130)=0.01745329424738884f;
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);else func_PAL_002B5E30(self,angle);
            *(float *)(state+0x130)=old;
        }
        break;
    case 9:
        if (func_L02_003D1820(self,target)<0.01f) {
            func_002A7750(self,10,-1);
            if (*(u8 *)(self+0x43)!=6) func_PAL_002A7E68(self,6,0,8);
            if (*(short *)(state+0x36E)) func_PAL_L11_00342558(self);else func_PAL_002B5E10(self);
        } else if (func_0029F530(self)>5.0f) {
            old=*(float *)(state+0x130);*(float *)(state+0x130)=0.01745329424738884f;
            if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);else func_PAL_002B5E30(self,angle);
            *(float *)(state+0x130)=old;
        }
        break;
    case 11:
        if (func_002B3868(self) && *(u8 *)(self+0x43)!=1) func_PAL_002A7E68(self,1,0,8);
        if (*(short *)(state+0x36E)) func_PAL_L11_00342578(self,target);else func_PAL_002B5E30(self,angle);
    case 15: case 16:
        if (flags&2) func_PAL_L11_0044E398(self);
        break;
    case 13: case 14:
        if (*(u8 *)(self+0x60)&2) {
            *(short *)(state+0x368)=0;
            if (D_0018C2BC==self) {
                func_002A7750(self,12,5);
                if (*(u8 *)(self+0x43)!=7) func_PAL_002A7E68(self,7,0,8);
            } else func_PAL_L11_0044E398(self);
        }
        func_L11_00449098(self);
        break;
    case 18:
        if (func_002B3868(self)) {
            func_00282CF0(state+0x1A0,func_L11_004417E8(*(int *)(self+0xB8)),point);
            *(float *)(state+0x1A8)=0;
            func_00282F20(state+0x1A0,state+0x1A0,func_002A7878(3.0f,5.0f)*0.020000001f);
            *(short *)(state+0x36E)=0;
            for(i=0;i<3;i++) {
                float *spin=(float *)(state+0x340);
                spin[i]=func_002A7878(240.0f,720.0f)*0.0003490659f;
                qcopy_nc((char *)matrix+i*16,self+0xC0+i*16);
            }
            func_002AB6D8(matrix,self+0xF0);
            if (*(u8 *)(self+0x43)!=13) func_PAL_002A7E68(self,13,0,25);
            *(u16 *)(self+0x34)&=0xEFFF;
        }
        { float gravity=*(float *)(state+0x12C);
          *(float *)(state+0x1A8)=*(float *)(state+0x1A8)-gravity; }
        func_L07_00321D68(self,state+0x1A0);
        func_00282D30(state+0x340,state+0x340,0.98f);
        *(Quad004475A0 *)matrix=0;
        matrix[2]=*(float *)(state+0x30);
        *(Quad004475A0 *)temp=*(Quad004475A0 *)matrix;
        func_002B4090(self,temp,*(float *)(state+0x340),*(float *)(state+0x344),*(float *)(state+0x348));
        func_002833F0(self+0xC0,self+0xF0);
        p=func_L11_004417E8(*(int *)(self+0xB8));
        if (*(float *)(self+0x18)<*(float *)(p+8)+5.0f || !func_002A77E0(450) || *(u16 *)(self+0x96)>300) {
            *(int *)(self+0x98)=0;
            func_PAL_L02_004009A0(self,0,-1);
            func_L01_003E9CF8(self,0,func_L11_00449878);
        }
        break;
    }
    func_L11_00448848(self);
}
