/* func_L00_003ADCD8 (456 bytes): own unit, -O2 -G8 -ffunction-sections (from the -g8 name). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int ref_L00_003ADCD8_0 __attribute__((sda));
extern float ref_L00_003ADCD8_1 __attribute__((sda));
extern float ref_L00_003ADCD8_2 __attribute__((sda));
extern int func_1163B0(void);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002A77E0(int);
extern void *func_002C3150(void *,void *,int,int,int,int,float);
/* swap16 is private to this unit: retail swaps the two 16-byte values with lq/lq/sq/sq through the parameters' stack homes, which plain C does not emit. Allowed by owner ruling (2026-11-09). */
static __inline__ void swap16(void *x, void *y) {
    __asm__ __volatile__("lq $2,0x0(%0)\n\tlq $3,0x0(%1)\n\tsq $2,0x0(%1)\n\tsq $3,0x0(%0)"
                         : : "r"(x), "r"(y) : "$2", "$3", "memory");
}
/* Throws sparks from one moby to another moby of the same kind. */
void func_L00_003ADCD8(char *first, char *second)
{
 float offset[4], position[4], delta[4];
 int i, count;
 unsigned char color;
 float distance;
 if(!second || *(short *)(second+0xAA)!=*(short *)(first+0xAA)) return;
 if((unsigned char)second[0x20]!=0xFE) { if((unsigned char)second[0x20]!=0xFD) {
 for(i=0;i<ref_L00_003ADCD8_0;) {
   if(func_1163B0()&1)
     swap16(&first, &second);
   i++;
   *(TI128 *)position=*(TI128 *)(first+0x10);
   count=FloatToInt(RandomFloatRange(ref_L00_003ADCD8_1*0.5f,ref_L00_003ADCD8_1));
   color=count;
   FastVecSub(delta,second+0x10,position);
   *(TI128 *)offset=*(TI128 *)delta;
   distance=FastVecLength(offset);
   FastVecScale(offset,offset,RandomFloatRange(0,0.9f));
   add_vectors(delta,position,offset);
   vec_scale_to_length(offset,offset,RandomFloatRange(1.0f/6.0f,distance/IntToFloat(count*4)));
   { int c=RandomIntBelow(255);
   SpawnHeroRelativeParticle(position,offset,0x604040FF,color,(unsigned char)c,0,ref_L00_003ADCD8_2); }
 }
}
}
}
