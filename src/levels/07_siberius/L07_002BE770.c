#include "include_asm.h"
#include "common.h"
extern char *part_alloc(int);
extern int math_random_int_range(int,int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float,float);
extern unsigned char *D_L07_001FEEA4, *D_L07_001FEF00;
extern int D_L07_001B2534 __attribute__((sda));



/* func_L07_002F2C70 is defined in L07_002BE770-g8.isBurst (it reads small data through $gp). */

/* Creates one falling snow particle at source position with source random size, color and spin. */
char *part_spawn_snow(void *source, void *velocity, int isBurst, int useGroup)
{
 char *particle=part_alloc(0x68); char *params;
 if(particle) {
 params=particle+0x20;
 *(int *)(params+0x10)=math_random_int_range(32,80);
 *(int *)(particle+4)=0x808080;
 particle[9]=FloatToInt(2.0f)-16; particle[1]=0; particle[3]=0x48;
 if(math_random_int_below(2)) particle[2]=D_L07_001FEEA4[0]; else particle[2]=D_L07_001FEF00[0];
 *(float *)(particle+12)=math_random_float_range(0.1f,0.24f)*210000.0f;
 particle[8]=math_random_int_below(255);
 qcopy(particle+16,source); qcopy(params,velocity);
 *(short *)(particle+10)=1<<math_random_int_range(6,10);
 if(isBurst) {*(short *)(particle+10)=120; *(int *)(params+20)=1;}
 if(useGroup) *(int *)(particle+4)+=*(int *)(params+16)<<24;
 { float f=math_random_int_range(0,100); int n=D_L07_001B2534; *(float *)(params+12)=f; D_L07_001B2534=n+1; }
 }
 return particle;
}

/* func_L07_00378898 is defined in L07_002BE770-rotation-g8.isBurst ($gp speed table). */

/* func_L07_00378AE0 is defined in L07_002BE770-particle-g8.isBurst. */


/* func_L07_00379180 is defined in L07_002BE770-g8.isBurst (this unit has no $gp access for it). */
