/* func_PAL_L01_003DED38, the PAL copy of func_L01_003DA740: the same C at 50 Hz, with the frame
 * constants rescaled and the particle lifetimes passed through the 5/6 scale. */
#include "common.h"
extern s32 D_L01_001B0894 __attribute__((sda));
extern s32 D_L01_001B0898 __attribute__((sda));
extern f32 D_L01_001B089C __attribute__((sda));
extern f32 D_L01_001B08A0 __attribute__((sda));
extern f32 D_L01_001B08A4 __attribute__((sda));
extern f32 D_L01_001B08A8 __attribute__((sda));
extern f32 D_L01_001B08AC __attribute__((sda));
extern f32 D_L01_001B08B0 __attribute__((sda));
extern f32 D_L01_001B08B8 __attribute__((sda));
extern f32 D_L01_001B08BC __attribute__((sda));
extern f32 D_L01_001B08C0 __attribute__((sda));
extern s32 D_L01_001B08C4 __attribute__((sda));
extern s32 D_L01_001B08C8 __attribute__((sda));
extern s32 D_L01_001B08CC __attribute__((sda));
extern f32 D_L01_001B08D0 __attribute__((sda));
extern f32 D_L01_001B08D4 __attribute__((sda));
extern f32 D_L01_001B08D8 __attribute__((sda));
extern f32 D_L01_001B08DC __attribute__((sda));
extern f32 D_L01_001B08E4 __attribute__((sda));
extern f32 D_L01_001B08EC __attribute__((sda));
extern f32 D_L01_001B08F0 __attribute__((sda));
extern f32 D_L01_001B08F4 __attribute__((sda));
extern f32 D_L01_001B08F8 __attribute__((sda));
extern s32 D_L01_001B08FC __attribute__((sda));
extern f32 func_00283248(f32, f32);
extern f32 func_00282E20(void *);
extern f32 func_002A7878(f32, f32);
extern f32 func_00283B98(f32, f32);
extern s32 func_00283CF0(f32);
extern void func_002AF000(void *, f32, f32, f32);
extern u8 *func_002BAA28(void *, void *, void *, s32, s32, s32, s32, s32, s32);
extern s32 func_001163B0(void);
void func_PAL_L01_003DED38(u8 *obj) {
    f32 vel[4] __attribute__((aligned(16)));
    f32 accel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    f32 yaw, pitch, speed, angle;
    s32 i, a, b, c;
    u8 *part;
    u8 *position;
    f32 *dest;
    vel[3]=D_L01_001B08B8;
    accel[3]=D_L01_001B08BC;
    yaw=func_00283248(*(f32 *)state,*(f32 *)(state+4));
    pitch=-func_00283248(func_00282E20(state),*(f32 *)(state+8));
    for(i=0;i<D_L01_001B08C4;i++) {
        dest=pos;
        position=obj+0x10;
        {
            qcopy(dest,position);
        }
        pos[0]+=func_002A7878(-0.065f,0.065f);
        pos[1]+=func_002A7878(-0.065f,0.065f);
        pos[2]+=func_002A7878(-0.065f,0.065f);
        func_002AF000(vel,D_L01_001B08A8*0.020000001f,yaw,pitch);
        vel[2]=func_002A7878(D_L01_001B08AC*0.018000001f,D_L01_001B08AC*0.022000001f);
        angle=func_002A7878(-D_L01_001B08C0,D_L01_001B08C0)*0.01745329424738884f;
        speed=D_L01_001B08B0;
        speed*=0.020000001f;
        angle=func_00283B98(yaw,angle);
        func_002AF000(accel,speed,angle,pitch);
        a=func_00283CF0((func_002A7878(D_L01_001B089C,D_L01_001B089C*2)*5.0f+2.0f)*0.16666667f);
        b=func_00283CF0((func_002A7878(D_L01_001B08A0,D_L01_001B08A0*1.2f)*5.0f+2.0f)*0.16666667f);
        c=func_00283CF0((func_002A7878(D_L01_001B08A4,D_L01_001B08A4*1.2f)*5.0f+2.0f)*0.16666667f);
        part=func_002BAA28(pos,vel,accel,D_L01_001B0894,D_L01_001B0898,a,b,c,-1);
        if(part && (func_001163B0()&1)) part[3]=0x48;
    }
    vel[3]=D_L01_001B08EC;
    accel[3]=D_L01_001B08F0;
    for(i=0;i<D_L01_001B08FC;i++) {
        qcopy(pos,obj+0x10);
        pos[0]+=func_002A7878(-0.2f,0.2f);
        pos[1]+=func_002A7878(-0.2f,0.2f);
        pos[2]+=func_002A7878(-0.2f,0.2f);
        angle=func_002A7878(-D_L01_001B08F8,D_L01_001B08F8)*0.01745329424738884f;
        speed=D_L01_001B08DC;
        speed*=0.020000001f;
        angle=func_00283B98(yaw,angle);
        func_002AF000(vel,speed,angle,pitch);
        angle=func_002A7878(-D_L01_001B08F4,D_L01_001B08F4)*0.01745329424738884f;
        speed=D_L01_001B08E4;
        speed*=0.020000001f;
        angle=func_00283B98(yaw,angle);
        func_002AF000(accel,speed,angle,pitch);
        a=func_00283CF0((func_002A7878(D_L01_001B08D0,D_L01_001B08D0*2)*5.0f+2.0f)*0.16666667f);
        b=func_00283CF0((func_002A7878(D_L01_001B08D4,D_L01_001B08D4*1.2f)*5.0f+2.0f)*0.16666667f);
        c=func_00283CF0((func_002A7878(D_L01_001B08D8,D_L01_001B08D8*1.2f)*5.0f+2.0f)*0.16666667f);
        part=func_002BAA28(pos,vel,accel,D_L01_001B08C8,D_L01_001B08CC,a,b,c,-1);
        if(part && (func_001163B0()&1)) part[3]=0x48;
    }
}
