#include "include_asm.h"

#include "common.h"
extern char *part_alloc(int);
extern int math_random_int_range(int,int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float,float);
extern unsigned char *g_snow_particle_color_a, *g_snow_particle_color_b;
extern int g_snow_spawn_counter __attribute__((sda));

/* func_L07_002F2C70 is defined in L07_002BE770-g8.c (it reads small data through $gp). */

char *part_spawn_snow_pal(void *a, void *b, int c, int d)
{
 char *p=part_alloc(0x68); char *q;
 if(p) {
 q=p+0x20;
 *(int *)(q+0x10)=math_random_int_range(32,80);
 *(int *)(p+4)=0x808080;
 p[9]=FloatToInt(2.0f)-16; p[1]=0; p[3]=0x48;
 if(math_random_int_below(2)) p[2]=g_snow_particle_color_a[0]; else p[2]=g_snow_particle_color_b[0];
 *(float *)(p+12)=math_random_float_range(0.1f,0.24f)*210000.0f;
 p[8]=math_random_int_below(255);
 qcopy(p+16,a); qcopy(q,b);
 *(short *)(p+10)=1<<math_random_int_range(6,10);
 if(c) {*(short *)(p+10)=100; *(int *)(q+20)=1;}
 if(d) *(int *)(p+4)+=*(int *)(q+16)<<24;
 { float f=math_random_int_range(0,100); int n=g_snow_spawn_counter; *(float *)(q+12)=f; g_snow_spawn_counter=n+1; }
 }
 return p;
}

