#include "names.h"
/* func_PAL_L00_003B14C8, the PAL copy of func_L00_003ADCD8: the same C, where expr 0.16666667f becomes 0.20000002f; wrap func_002A7878(ref_L00_003ADCD8_1*0.5f,ref_L00_003ADCD8_; rename func_1163B0 becomes func_001163B0. */
/* func_PAL_L00_003B14C8 (456 bytes): own unit, -O2 -G8 -ffunction-sections (from the -g8 name). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int ref_L00_003ADCD8_0 __attribute__((sda));
extern float ref_L00_003ADCD8_1 __attribute__((sda));
extern float ref_L00_003ADCD8_2 __attribute__((sda));
extern int func_001163B0(void);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *,void *,float);
extern void add_vectors(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *,void *,int,int,int,int,float);
/* swap16 is private to this unit: retail swaps the two 16-byte values with lq/lq/sq/sq through the parameters' stack homes, which plain C does not emit. Allowed by owner ruling (2026-11-09). */
static __inline__ void swap16(void *x, void *y) {
    __asm__ __volatile__("lq $2,0x0(%0)\n\tlq $3,0x0(%1)\n\tsq $2,0x0(%1)\n\tsq $3,0x0(%0)"
                         : : "r"(x), "r"(y) : "$2", "$3", "memory");
}
/* Spawns sparks that travel from one moby toward another, from a random end (PAL: counts at 50 Hz). */
void part_spawn_sparks_between_mobys_pal(char *from, char *to)
{
 float offset[4], position[4], delta[4];
 int i, count;
 unsigned char color;
 float distance;
 if(!to || *(short *)(to+0xAA)!=*(short *)(from+0xAA)) return;
 if((unsigned char)to[0x20]!=0xFE) { if((unsigned char)to[0x20]!=0xFD) {
 for(i=0;i<ref_L00_003ADCD8_0;) {
   if(func_001163B0()&1)
     swap16(&from, &to);
   i++;
   *(TI128 *)position=*(TI128 *)(from+0x10);
   count=FloatToInt(((math_random_float_range(ref_L00_003ADCD8_1*0.5f,ref_L00_003ADCD8_1)) * 5.0f + 2.0f) * 0.16666667f);
   color=count;
   FastVecSub(delta,to+0x10,position);
   *(TI128 *)offset=*(TI128 *)delta;
   distance=FastVecLength(offset);
   FastVecScale(offset,offset,math_random_float_range(0,0.9f));
   add_vectors(delta,position,offset);
   vec_scale_to_length(offset,offset,math_random_float_range(0.20000002f,distance/IntToFloat(count*4)));
   { int c=math_random_int_below(255);
   part_spawn_hero_relative(position,offset,0x604040FF,color,(unsigned char)c,0,ref_L00_003ADCD8_2); }
 }
}
}
}
