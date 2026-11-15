#include "include_asm.h"
#include "names.h"

/* The retail clamps use min.s/max.s, requiring this unit's -ffast-math.
 * The measured key-array layout preserves indexed member addressing. */
typedef unsigned char u8;
typedef struct {char pad[0x70];float keys[4];} KeyObject;
extern void fade_start_direction(u8 *,int);
extern float math_eval_cubic_hermite(float, float, float, float, float);
/* Moves an animation forward or backward, finds the two keyframes around its position and blends between them. At the end it stops, repeats or reverses. */
void anim_update_keyframe(char *anim, int advance)
{
 int hiIdx, loIdx, i;
 float blend, *keys;
 if (!*(int *)(anim+0x28)) return;
 loIdx=0;hiIdx=0;
 if (*(int *)(anim+0x1c)==1) {
  float value=*(float *)(anim+0x18);
  if (advance) value+=*(float *)(anim+0x24);
  *(float *)(anim+0x18)=value;
  *(int *)(anim+0x28)=value<=1.0f;
  value=value<=1.0f?value:1.0f;
  *(float *)(anim+0x18)=value;
  for(i=0,keys=(float *)(anim+0x70);i<*(int *)(anim+0x84);i++) {
   int next=hiIdx+1;
   if(next<*(int *)(anim+0x84) && keys[hiIdx]<=value) {loIdx=hiIdx;hiIdx=next;} else break;
  }
 } else {
  float value=*(float *)(anim+0x18);
  if(advance) value-=*(float *)(anim+0x24);
  *(float *)(anim+0x18)=value;
  *(int *)(anim+0x28)=value>=0.0f;
  value=value>=0.0f?value:0.0f;
  *(float *)(anim+0x18)=value;
  keys=(float *)(anim+0x70);
  hiIdx=*(int *)(anim+0x84)-1;loIdx=hiIdx;
  { int j; for(j=hiIdx;j>0;j--) {
   int next=loIdx-1;
   if(next>=0 && value<=((KeyObject *)anim)->keys[loIdx]) {hiIdx=loIdx;loIdx=next;} else break;
  }}
 }
 blend=math_eval_cubic_hermite((*(float *)(anim+0x18)-((KeyObject *)anim)->keys[loIdx])/(((KeyObject *)anim)->keys[hiIdx]-((KeyObject *)anim)->keys[loIdx]),0.0f,*(float *)anim,*(float *)(anim+12),1.0f);
 if(*(int *)(anim+0x2c)) {
  char *target=*(char **)(anim+0x80);char *vt=*(char **)target;
  ((void (*)(void *,int,void *,void *,float))*(void **)(vt+20))(target+*(short *)(vt+16),*(int *)(anim+0x2c),anim+(loIdx*16+0x30),anim+(hiIdx*16+0x30),blend);
 }
 if(!*(int *)(anim+0x28)) {
  switch(*(int *)(anim+0x20)) {
   case 0:break;
   case 1:fade_start_direction((u8 *)anim,*(int *)(anim+0x1c));break;
   case 2:*(int *)(anim+0x1c)=*(int *)(anim+0x1c)==1?-1:1;fade_start_direction((u8 *)anim,*(int *)(anim+0x1c));break;
  }
 }
}
