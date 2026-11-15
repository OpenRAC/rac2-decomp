#include "include_asm.h"
#include "names.h"
extern int g_current_map_index __attribute__((sda));
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
extern void vec_clear_128(void *);
extern int math_random_int_below(int);
extern void STUB_printf(char *, ...);
extern float IntToFloat(int);
extern double __extendsfdf2(float);
extern void FastVecScale(void *, void *, float);
extern float math_random_angle(void), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), math_random_float_range(float,float);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern int SegmentCrossPolyline(int, void *, void *, void *);
extern void *moby_spawn_bolt_pickup(void *, void *, void *, int, int, int);

/* Spawns bolt pickups worth a random amount between low and high, split into the biggest coins that fit,
   and scatters them around the object. The amount is scaled by how fast the player is earning. */
void part_spawn_bolt_pickups(char *object, int low, int high, int flags, int surface, int maximum, float height)
{
    float offset[4], position[4], velocity[4], half[4], end[4], hit[4], correction[4];
    float nearTime, farTime;
    int ones, fives, twenties, fifties, hundreds, fivehundreds, thousands;
    int value, remaining, enabled, quotient;
    float angle, x, y, duration;
    vec_clear_128(offset);
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
    value=math_random_int_below(high-low+1)+low;
    if (D_001A7A00.x0A || D_001A7A00.x0B) value*=2;
    if (value<500 && enabled && D_0018D198[g_current_map_index]) {
        int rate=D_0018D208[g_current_map_index]*3600/D_0018D198[g_current_map_index];
        if (D_001A7A00.x0A || D_001A7A00.x0B) rate/=2;
        #define limit ((int)ref_L00_00321878_01)
        if (rate<limit/2) {
            if (rate<=limit*3/10) {
                STUB_printf(ref_L00_00321878_04);
                value*=5;
            } else {
                STUB_printf(ref_L00_00321878_05,(limit*19/30-rate)/(limit/15));
                value=value*(limit*19/30-rate)/(limit/15);
            }
            if (D_001A7A00.x0B) {
                if(value>limit*10/3) value=limit*10/3;
            } else if(value>limit*5/3) value=limit*5/3;
        } else if (limit<rate) {
            if (limit*7/6<rate) {
                STUB_printf(ref_L00_00321878_06,0x3fb99999a0000000L);
                value/=10;
            } else {
                STUB_printf(ref_L00_00321878_06,__extendsfdf2(IntToFloat((limit*6/5-rate)/(limit*4/15))));
                value=value*(limit*6/5-rate)/(limit*4/15);
            }
            if(value<=0) value=1;
        }
        #undef limit
    }
    remaining=value;
    if (flags & 8) {
        int count = maximum;
#define TAKE(n, denom) quotient = remaining / denom; n = quotient; if (n > count) n = count; \
        count -= n; remaining -= n * denom
#define TAKE_MIN(n, denom) { int taken = count; quotient = remaining / denom; if (quotient <= count) taken = quotient; n = taken; } \
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
#define SPLIT(n, denom) if (remaining >= denom) { quotient = remaining / denom; n = quotient; remaining -= n * denom; }
        SPLIT(thousands, 1000); SPLIT(fivehundreds, 500); SPLIT(hundreds, 100);
        SPLIT(fifties, 50); SPLIT(twenties, 20); SPLIT(fives, 5);
#undef SPLIT
        ones = remaining;
        if (thousands < 0 || fivehundreds < 0 || hundreds < 0 || fifties < 0 || twenties < 0 || fives < 0 || ones < 0) {
            STUB_printf(ref_L00_00321878_07);
            thousands = thousands < 0 ? 0 : thousands; fivehundreds = fivehundreds < 0 ? 0 : fivehundreds;
            hundreds = hundreds < 0 ? 0 : hundreds; fifties = fifties < 0 ? 0 : fifties;
            twenties = twenties < 0 ? 0 : twenties; fives = fives < 0 ? 0 : fives;
            ones = ones < 0 ? 0 : ones;
        }
    }
    while(ones||fives||twenties||fifties||hundreds||fivehundreds||thousands){
        FastVecScale(position,object,0.0009765625f);
        angle=math_random_angle();
        x=math_fast_sin_or_cos_a(angle)*0.01666666753590107f*math_random_float_range(0,3);
        velocity[0]=x;
        y=math_fast_sin_or_cos_b(angle)*0.01666666753590107f*math_random_float_range(0,3);
        velocity[1]=y;velocity[2]=0;
        velocity[2]=math_random_float_range(3.700000047683716f,6)*0.01666666753590107f;
        half[0]=velocity[0];half[1]=velocity[1];half[2]=0;
        vec_scale_to_length(half,half,0.5f);
        FastVecAdd(position,position,half);
        position[2]+=height;
        if(surface>=0){
            duration=120;
            if((float)math_solve_quadratic(&nearTime,&farTime,-0.001500000013038516f,velocity[2]-(-0.001500000013038516f),position[2]-*(float *)(ref_L00_00321878_03[surface]+24))>=1 && nearTime>0 && nearTime<duration)duration=nearTime;
            FastVecScale(end,velocity,duration);
            FastVecAdd(end,end,object+16);
            SegmentCrossPolyline(surface,object+16,end,hit);
            FastVecSub(end,hit,position);
            end[2]=0;
            vec_scale_to_length(correction,end,0.25f);
            FastVecSub(end,end,correction);
            FastVecScale(end,end,1/duration);
            velocity[0]=end[0];velocity[1]=end[1];
        }
        FastVecAdd(velocity,velocity,offset);
        if(thousands){moby_spawn_bolt_pickup(object,position,velocity,flags,1000,enabled);thousands--;}
        else if(fivehundreds){moby_spawn_bolt_pickup(object,position,velocity,flags,500,enabled);fivehundreds--;}
        else if(hundreds){moby_spawn_bolt_pickup(object,position,velocity,flags,100,enabled);hundreds--;}
        else if(fifties){moby_spawn_bolt_pickup(object,position,velocity,flags,50,enabled);fifties--;}
        else if(twenties){moby_spawn_bolt_pickup(object,position,velocity,flags,20,enabled);twenties--;}
        else if(fives){moby_spawn_bolt_pickup(object,position,velocity,flags,5,enabled);fives--;}
        else {moby_spawn_bolt_pickup(object,position,velocity,flags,1,enabled);ones--;}
    }
}
