#include "common.h"
extern int sceCdReadClock(void *);
extern void clock_to_local_time(u8 *);
extern u8 *CreateMoby(int);
extern void euler_rotation_basis(void *, void *);
extern int FloatToInt(float);
extern float fast_fmod(float, float);
extern int snd_start_in_slot(int, int, void *);
extern int math_fast_float_d(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
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
void UpdateBoldanClock(u8 *moby) {
    u8 *vars=P(moby,0x68), *a;
    u8 time[16];
    int slo, mlo, hlo, sec, min, hour, hour12;
    float hour_value, hour_angle;
    if (moby[0x20]==0) {
        int initialHour;
        H(moby,0x96)=0; moby[0x20]=1; moby[0x30]=255; H(moby,0x32)=800;
        I(vars,0xC)=0; I(vars,0x20)=0;
        sceCdReadClock(time); clock_to_local_time(time);
        P(vars,0x10)=CreateMoby(0xE9F);
        if (P(vars,0x10)) {
            P(vars,0x10)[0x30]=255; H(P(vars,0x10),0x32)=800;
            P(vars,0x10)[0x31]=1; P(vars,0x10)[0x20]=0;
            *(u64 *)(P(vars,0x10)+0x38)=*(u64 *)(moby+0x38);
            { u8 *hand=P(vars,0x10); qcopy_nc(hand+0x10,moby+0x10); qcopy_nc(hand+0xF0,moby+0xF0);
            euler_rotation_basis(hand+0xC0,hand+0xF0); }
        }
        P(vars,0x14)=CreateMoby(0xEA0);
        if (P(vars,0x14)) {
            P(vars,0x14)[0x30]=255; H(P(vars,0x14),0x32)=800;
            P(vars,0x14)[0x31]=1; P(vars,0x14)[0x20]=0;
            *(u64 *)(P(vars,0x14)+0x38)=*(u64 *)(moby+0x38);
            { u8 *hand=P(vars,0x14); qcopy_nc(hand+0x10,moby+0x10); qcopy_nc(hand+0xF0,moby+0xF0);
            euler_rotation_basis(hand+0xC0,hand+0xF0); }
        }
        a=CreateMoby(0xEA1);
        if(a) {
            a[0x30]=255; H(a,0x32)=800; a[0x31]=1; a[0x20]=0;
            *(u64 *)(a+0x38)=*(u64 *)(moby+0x38);
            qcopy_nc(a+0x10,moby+0x10); qcopy_nc(a+0xF0,moby+0xF0);
            euler_rotation_basis(a+0xC0,P(vars,0x14)+0xF0);
        }
        /* The RTC returns packed BCD hours, minutes and seconds. */
        I(vars,0)=FloatToInt(time[3]); I(vars,8)=FloatToInt(time[2]); I(vars,4)=FloatToInt(time[1]);
        slo=FloatToInt(fast_fmod((float)I(vars,4),16.0f));
        sec=FloatToInt((float)(I(vars,4)/16))*10+slo;
        mlo=FloatToInt(fast_fmod((float)I(vars,8),16.0f));
        min=FloatToInt((float)(I(vars,8)/16))*10+mlo;
        hlo=FloatToInt(fast_fmod((float)I(vars,0),16.0f));
        initialHour=FloatToInt((float)(I(vars,0)/16))*10+hlo;
        I(vars,8)=min; I(vars,4)=sec; I(vars,0)=initialHour;
    }
    if(moby[0x20]==1 && H(moby,0x96)==60) {
        if(++I(vars,4)>=60) { I(vars,4)=0; ++I(vars,8); }
        if(I(vars,8)>=60) { I(vars,8)=0; ++I(vars,0); }
        if(I(vars,0)>=24) I(vars,0)=0;
        hour_value=(float)I(vars,0); hour=FloatToInt(hour_value);
        if(hour_value>12.0f) hour_value-=12.0f;
        hour12=FloatToInt(hour_value);
        if(hour12==0 || hour12==2 || hour12==4 || hour12==6 || hour12==8 || hour12==10 || hour12==12) {
            ClockMoby *a=&D_L13_001B291C[I(vars,0x28)];
            int collision;

            a->flags=(a->flags&0xFFBE)|0x1000;
            collision=I(a->classData,0x10);
            a->flags&=0xFFFD;
            a->collision=collision;
        } else {
            ClockMoby *a=&D_L13_001B291C[I(vars,0x28)];
            a->collision=0; a->flags=(a->flags&0xEFFF)|0x43;
        }
        if(hour==3) {
            if(I(vars,0x24)!=-1) { u8 *a=P(D_L13_001B291C_gp+(I(vars,0x24)<<8),0x68); if(!I(a,0x38)) I(a,0x38)=1; }
        } else {
            if(I(vars,0x24)!=-1) { u8 *a=P(D_L13_001B291C_gp+(I(vars,0x24)<<8),0x68); if(I(a,0x38)) I(a,0x38)=0; }
        }
        if(I(vars,4)==0 && I(vars,8)==0) {
            I(vars,0x18)=snd_start_in_slot(0x10,0x21,moby); I(vars,0xC)=10; I(vars,0x20)=FloatToInt(hour_value);
        }
        H(moby,0x96)=0;
    }
    F(moby,0xF0)=(float)(I(vars,4)*6)*0.01745329424738884f;
    F(P(vars,0x10),0xF0)=((float)I(vars,8)*6.0f+(float)I(vars,4)*0.1f)*0.01745329424738884f;
    hour_angle=(float)I(vars,0); if(hour_angle>12.0f) hour_angle-=12.0f;
    hour_angle *= 30.0f;
    hour_angle += (float)I(vars,8)*0.5f;
    F(P(vars,0x14),0xF0)=hour_angle*0.01745329424738884f;
    if(H(moby,0x96)<65535) ++H(moby,0x96);
    if(math_fast_float_d(vars+0xC) && I(vars,0x20) && !snd_is_voice_playing_for_owner(moby,I(vars,0x18))) {
        I(vars,0x18)=-1; snd_start_in_slot(0x11,0x21,moby); I(vars,0xC)=120; --I(vars,0x20);
    }
}
