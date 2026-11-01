#include "include_asm.h"

extern int D_001A79F0 __attribute__((sda));
extern unsigned char ref_L00_00321878_00[] __attribute__((section(".sdata")));
extern char ref_L00_00321878_01[];
extern int ref_L00_00321878_02;
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char x0A;
    unsigned char x0B;
    unsigned char pad0C[0x08];
    int x14;
    unsigned char pad18[0x1A];
    unsigned char x32;
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((section(".sdata")));
extern int D_0018D198[], D_0018D208[];
extern char *ref_L00_00321878_03[];
extern char ref_L00_00321878_04[], ref_L00_00321878_05[], ref_L00_00321878_06[], ref_L00_00321878_07[];
extern void func_00282C88(void *);
extern int func_002A77E0(int);
extern void func_0026FEB8(char *, ...);
extern float func_00283CE0(int);
extern double func_001234F0(float);
extern void func_00282D30(void *, void *, float);
extern float func_002A7940(void), func_00283180(float), func_00283198(float), func_002A7878(float,float);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern int func_002A88A0(float *, float *, float, float, float);
extern void func_002C94C8(int, void *, void *, void *);
extern void func_PAL_00303578(void *, void *, void *, int, int, int);

void func_PAL_L00_00323918(char *object, int low, int high, int flags, int surface, int maximum, float height)
{
    float offset[4], position[4], velocity[4], half[4], end[4], hit[4], correction[4];
    float t0, t1;
    int ones, fives, twenties, fifties, hundreds, fivehundreds, thousands;
    int value, remaining, enabled, q;
    float angle, x, y, duration;
    func_00282C88(offset);
    ones=0; fives=0; twenties=0; fifties=0; hundreds=0; fivehundreds=0; thousands=0;
    if (!(flags & 32) && (unsigned char)object[0xb0] != 255 &&
        (unsigned int)(*(unsigned short *)(object+0xaa)-500) >= 41)
        {
            unsigned int index=(unsigned char)object[0xb0];
            unsigned char *table = ref_L00_00321878_00;
            ref_L00_00321878_02 = table[index] >> 7;
        }
    {
        int allowed = ((flags >> 5)^1)&1;
        enabled=0;
        if (ref_L00_00321878_02) enabled=allowed;
    }
    if (!flags || (!low && !high)) return;
    if (low <= 0) low=1;
    value=func_002A77E0(high-low+1)+low;
    if (D_001A7A00.x0A || D_001A7A00.x0B) value*=2;
    if (value<500 && enabled && D_0018D198[D_001A79F0]) {
        int rate=D_0018D208[D_001A79F0]*3000/D_0018D198[D_001A79F0];
        if (D_001A7A00.x0A || D_001A7A00.x0B) rate/=2;
        #define limit ((int)ref_L00_00321878_01)
        if (rate<limit/2) {
            if (rate<=limit*3/10) {
                func_0026FEB8(ref_L00_00321878_04);
                value*=5;
            } else {
                func_0026FEB8(ref_L00_00321878_05,(limit*19/30-rate)/(limit/15));
                value=value*(limit*19/30-rate)/(limit/15);
            }
            if (D_001A7A00.x0B) {
                if(value>limit*10/3) value=limit*10/3;
            } else if(value>limit*5/3) value=limit*5/3;
        } else if (limit<rate) {
            if (limit*7/6<rate) {
                func_0026FEB8(ref_L00_00321878_06,0x3fb99999a0000000L);
                value/=10;
            } else {
                func_0026FEB8(ref_L00_00321878_06,func_001234F0(func_00283CE0((limit*6/5-rate)/(limit*4/15))));
                value=value*(limit*6/5-rate)/(limit*4/15);
            }
            if(value<=0) value=1;
        }
        #undef limit
    }
    remaining=value;
    if (flags & 8) {
        int count = maximum;
#define TAKE(n, denom) q = remaining / denom; n = q; if (n > count) n = count; \
        count -= n; remaining -= n * denom
#define TAKE_MIN(n, denom) { int t = count; q = remaining / denom; if (q <= count) t = q; n = t; } \
        count -= n; remaining -= n * denom
        TAKE(thousands, 1000);
        if (count > 0) { TAKE_MIN(fivehundreds, 500);
        if (count > 0) { TAKE_MIN(hundreds, 100);
        if (count > 0) { TAKE_MIN(fifties, 50);
        if (count > 0) { TAKE_MIN(twenties, 20);
        if (count > 0) { TAKE(fives, 5);
        if (count > 0) { ones = remaining; if (ones > count) ones = count; }
        }}}}}
#undef TAKE
#undef TAKE_MIN
        if (D_001A7A00.x32) remaining /= D_001A7A00.x32;
        D_001A7A00.x14 += remaining;
    } else {
#define SPLIT(n, denom) if (remaining >= denom) { q = remaining / denom; n = q; remaining -= n * denom; }
        SPLIT(thousands, 1000); SPLIT(fivehundreds, 500); SPLIT(hundreds, 100);
        SPLIT(fifties, 50); SPLIT(twenties, 20); SPLIT(fives, 5);
#undef SPLIT
        ones = remaining;
        if (thousands < 0 || fivehundreds < 0 || hundreds < 0 || fifties < 0 || twenties < 0 || fives < 0 || ones < 0) {
            func_0026FEB8(ref_L00_00321878_07);
            thousands = thousands < 0 ? 0 : thousands; fivehundreds = fivehundreds < 0 ? 0 : fivehundreds;
            hundreds = hundreds < 0 ? 0 : hundreds; fifties = fifties < 0 ? 0 : fifties;
            twenties = twenties < 0 ? 0 : twenties; fives = fives < 0 ? 0 : fives;
            ones = ones < 0 ? 0 : ones;
        }
    }
    while(ones||fives||twenties||fifties||hundreds||fivehundreds||thousands){
        func_00282D30(position,object,0.0009765625f);
        angle=func_002A7940();
        x=func_00283180(angle)*0.020000001f*func_002A7878(0,3);
        velocity[0]=x;
        y=func_00283198(angle)*0.020000001f*func_002A7878(0,3);
        velocity[1]=y;velocity[2]=0;
        velocity[2]=func_002A7878(3.700000047683716f,6)*0.020000001f;
        half[0]=velocity[0];half[1]=velocity[1];half[2]=0;
        func_00282F20(half,half,0.5f);
        func_00282CC0(position,position,half);
        position[2]+=height;
        if(surface>=0){
            duration=120;
            if((float)func_002A88A0(&t0,&t1,-0.0021600001f,velocity[2]-(-0.0021600001f),position[2]-*(float *)(ref_L00_00321878_03[surface]+24))>=1 && t0>0 && t0<duration)duration=t0;
            func_00282D30(end,velocity,duration);
            func_00282CC0(end,end,object+16);
            func_002C94C8(surface,object+16,end,hit);
            func_00282CF0(end,hit,position);
            end[2]=0;
            func_00282F20(correction,end,0.25f);
            func_00282CF0(end,end,correction);
            func_00282D30(end,end,1/duration);
            velocity[0]=end[0];velocity[1]=end[1];
        }
        func_00282CC0(velocity,velocity,offset);
        if(thousands){func_PAL_00303578(object,position,velocity,flags,1000,enabled);thousands--;}
        else if(fivehundreds){func_PAL_00303578(object,position,velocity,flags,500,enabled);fivehundreds--;}
        else if(hundreds){func_PAL_00303578(object,position,velocity,flags,100,enabled);hundreds--;}
        else if(fifties){func_PAL_00303578(object,position,velocity,flags,50,enabled);fifties--;}
        else if(twenties){func_PAL_00303578(object,position,velocity,flags,20,enabled);twenties--;}
        else if(fives){func_PAL_00303578(object,position,velocity,flags,5,enabled);fives--;}
        else {func_PAL_00303578(object,position,velocity,flags,1,enabled);ones--;}
    }
}
