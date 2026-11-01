#include "include_asm.h"

#include "common.h"
extern int func_001256D8(void *);
extern void func_00131A98(u8 *);
extern u8 *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern int func_00283CF0(float);
extern float func_00283D00(float, float);
extern int func_L00_0035F5A0(int, int, void *);
extern int func_00282948(void *);
extern int func_002E59B0(void *, int);
typedef struct {
    u8 pad00[0x24];
    u8 *classData;
    u8 pad28[0x34-0x28];
    u16 flags;
    u8 pad36[0x98-0x36];
    int collision;
    u8 pad9C[0x100-0x9C];
} ClockMoby;
extern ClockMoby *D_L13_001B291C NOT_SDA;
extern u8 *D_L13_001B291C_gp SDATA(D_L13_001B291C);
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))

/* Initialize the clock from the console RTC, then advance its hands and hourly sound.
 * The GP view and ordinary view refer to the same moby-array pointer.
 */
void func_PAL_L13_0040B090(u8 *m) {
    u8 *d=P(m,0x68), *a;
    u8 time[16];
    int slo, mlo, hlo, sec, min, hour, t;
    float h, angle;
    if (m[0x20]==0) {
        int initialHour;
        H(m,0x96)=0; m[0x20]=1; m[0x30]=255; H(m,0x32)=800;
        I(d,0xC)=0; I(d,0x20)=0;
        func_001256D8(time); func_00131A98(time);
        P(d,0x10)=func_0029EFD0(0xE9F);
        if (P(d,0x10)) {
            P(d,0x10)[0x30]=255; H(P(d,0x10),0x32)=800;
            P(d,0x10)[0x31]=1; P(d,0x10)[0x20]=0;
            *(u64 *)(P(d,0x10)+0x38)=*(u64 *)(m+0x38);
            { u8 *hand=P(d,0x10); qcopy_nc(hand+0x10,m+0x10); qcopy_nc(hand+0xF0,m+0xF0);
            func_002833F0(hand+0xC0,hand+0xF0); }
        }
        P(d,0x14)=func_0029EFD0(0xEA0);
        if (P(d,0x14)) {
            P(d,0x14)[0x30]=255; H(P(d,0x14),0x32)=800;
            P(d,0x14)[0x31]=1; P(d,0x14)[0x20]=0;
            *(u64 *)(P(d,0x14)+0x38)=*(u64 *)(m+0x38);
            { u8 *hand=P(d,0x14); qcopy_nc(hand+0x10,m+0x10); qcopy_nc(hand+0xF0,m+0xF0);
            func_002833F0(hand+0xC0,hand+0xF0); }
        }
        a=func_0029EFD0(0xEA1);
        if(a) {
            a[0x30]=255; H(a,0x32)=800; a[0x31]=1; a[0x20]=0;
            *(u64 *)(a+0x38)=*(u64 *)(m+0x38);
            qcopy_nc(a+0x10,m+0x10); qcopy_nc(a+0xF0,m+0xF0);
            func_002833F0(a+0xC0,P(d,0x14)+0xF0);
        }
        /* The RTC returns packed BCD hours, minutes and seconds. */
        I(d,0)=func_00283CF0(time[3]); I(d,8)=func_00283CF0(time[2]); I(d,4)=func_00283CF0(time[1]);
        slo=func_00283CF0(func_00283D00((float)I(d,4),16.0f));
        sec=func_00283CF0((float)(I(d,4)/16))*10+slo;
        mlo=func_00283CF0(func_00283D00((float)I(d,8),16.0f));
        min=func_00283CF0((float)(I(d,8)/16))*10+mlo;
        hlo=func_00283CF0(func_00283D00((float)I(d,0),16.0f));
        initialHour=func_00283CF0((float)(I(d,0)/16))*10+hlo;
        I(d,8)=min; I(d,4)=sec; I(d,0)=initialHour;
    }
    if(m[0x20]==1 && H(m,0x96)==50) {
        if(++I(d,4)>=60) { I(d,4)=0; ++I(d,8); }
        if(I(d,8)>=60) { I(d,8)=0; ++I(d,0); }
        if(I(d,0)>=24) I(d,0)=0;
        h=(float)I(d,0); hour=func_00283CF0(h);
        if(h>12.0f) h-=12.0f;
        t=func_00283CF0(h);
        if(t==0 || t==2 || t==4 || t==6 || t==8 || t==10 || t==12) {
            ClockMoby *a=&D_L13_001B291C[I(d,0x28)];
            int collision;

            a->flags=(a->flags&0xFFBE)|0x1000;
            collision=I(a->classData,0x10);
            a->flags&=0xFFFD;
            a->collision=collision;
        } else {
            ClockMoby *a=&D_L13_001B291C[I(d,0x28)];
            a->collision=0; a->flags=(a->flags&0xEFFF)|0x43;
        }
        if(hour==3) {
            if(I(d,0x24)!=-1) { u8 *a=P(D_L13_001B291C_gp+(I(d,0x24)<<8),0x68); if(!I(a,0x38)) I(a,0x38)=1; }
        } else {
            if(I(d,0x24)!=-1) { u8 *a=P(D_L13_001B291C_gp+(I(d,0x24)<<8),0x68); if(I(a,0x38)) I(a,0x38)=0; }
        }
        if(I(d,4)==0 && I(d,8)==0) {
            I(d,0x18)=func_L00_0035F5A0(0x10,0x21,m); I(d,0xC)=8; I(d,0x20)=func_00283CF0(h);
        }
        H(m,0x96)=0;
    }
    F(m,0xF0)=(float)(I(d,4)*6)*0.01745329424738884f;
    F(P(d,0x10),0xF0)=((float)I(d,8)*6.0f+(float)I(d,4)*0.1f)*0.01745329424738884f;
    angle=(float)I(d,0); if(angle>12.0f) angle-=12.0f;
    angle *= 30.0f;
    angle += (float)I(d,8)*0.5f;
    F(P(d,0x14),0xF0)=angle*0.01745329424738884f;
    if(H(m,0x96)<65535) ++H(m,0x96);
    if(func_00282948(d+0xC) && I(d,0x20) && !func_002E59B0(m,I(d,0x18))) {
        I(d,0x18)=-1; func_L00_0035F5A0(0x11,0x21,m); I(d,0xC)=100; --I(d,0x20);
    }
}
