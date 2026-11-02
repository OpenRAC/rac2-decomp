/* functional: high. Same spawn and trail-update cases as retail, with the trail scale clamped to 0..1; register choices differ. */
/* Tier: sol-high (v0708), USA v1.01 game compiler.
 * Best check.py: 1336/1340 bytes, 0 of 1 places match.
 * Compile as a dedicated -g8.c unit with -O2 -G8 -ffunction-sections
 * -mno-split-addresses. All declarations are included below.
 * Typed Object fields recover the initialization block; disabling split
 * addresses recovers retail's data=s1, scratch=s2, point=s3 allocation and
 * the first GP current-level read in state 2. Remaining differences include
 * the state flag load register, camera-direction address hoisting, clamp
 * f0/f1 allocation and annulled store, indexed table setup, and scheduling.
 * The default split-address profile gives 1320 bytes with these types and
 * loses the saved-register assignment; -fno-gcse gives 1292 and a 0x90 frame.
 * A local clamp value, nested condition and separate multiply/store tie.
 * Next: recover the original camera/table access types or macro forms that
 * preserve their address lifetimes without affecting global call addresses.
 * This complete particle-update attempt is retained only, never linked.
 */
#include "common.h"
typedef struct { float x,y,z,w; } V;
extern int D_001A79F0 MACRO_ADDR;
extern int D_L07_001B1E08, D_L07_001C9780;
extern char *D_L07_001AEC08 __attribute__((sda));
extern char *D_L07_001ADAAC MACRO_ADDR;
extern float D_L07_001AEC10[] SDATA(D_L07_001AEC10);
extern float D_L07_001AEC14[] __attribute__((nosda));
typedef struct { V pos; char pad[0x220]; V dir; } Camera;
extern V D_L07_001B9200[];
extern char D_L07_001B90C0[];
extern V D_L07_001B2550;
extern float D_L07_001B2558 __attribute__((nosda));
extern void func_L07_00379020(void *);
extern void func_002A7750(void *,int,int);
extern void func_L02_0031E9E8(void *,float);
extern void func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DF0(void *),func_002A7878(float,float);
extern int func_002A77E0(int),func_002B3868(void *),func_L00_00329520(void *,int);
extern char *func_L07_00336860(void *,void *,int,int);
typedef struct { char pad00[0x20]; unsigned char state; char pad21[0xf]; unsigned char alpha; char pad31[3]; unsigned short flags; char pad36[0x32]; void *data; } Object;
typedef struct { float speed,fall; int enabled; float scale; int group; char pad[0x4c]; V previous; } Data;
void func_L07_00378AE0(Object *obj) {
 V pos,vel,tmp,point;
 Data *data=(Data *)obj->data;
 int j, i;
 float lo,hi;
 switch (obj->state) {
 case 0:
 obj->alpha=255; obj->flags|=0x100;
 if(D_001A79F0==7 && D_L07_001B1E08) {
 func_L07_00379020(obj);func_002A7750(obj,1,-1);
 }
 data->speed=1.5f;data->fall=2.5f;data->enabled=1;
 D_L07_001AEC08=(char *)obj;break;
 case 1:
 i=0;
 if(D_001A79F0==7 && D_L07_001C9780==1) {func_002A7750(obj,2,-1);break;}
 { for(;i<func_002A77E0(2);i++) {
 func_L02_0031E9E8(&pos,15.0f);pos.z+=7.0f;
 func_00282CC0(&pos,&pos,&D_L07_001B9200);
 func_00282D30(&tmp,&D_L07_001B9200[35],4.0f);
 func_00282CC0(&pos,&tmp,&pos);
 func_L02_0031E9E8(&vel,data->speed*(1.0f/60.0f));
 vel.z=-(data->fall*(1.0f/60.0f))*func_002A7878(0.8f,1.2f);
 if(!func_L00_00329520(&pos,data->group))func_L07_00336860(&pos,&vel,0,0);
 }
 }
 func_00282D30(&point,&D_L07_001B9200[35],4.0f);
 func_00282CC0(&tmp,&point,&D_L07_001B9200);
 func_00282CF0(&D_L07_001B2550,&tmp,&data->previous);
 data->scale=func_00282DF0(&D_L07_001B2550)*4.0f;
 if (data->scale > 1.0f) data->scale = 1.0f;
 else if (data->scale < 0.0f) data->scale = 0.0f;
 func_00282D30(&D_L07_001B2550,&D_L07_001B2550,data->scale);
 qcopy_nc(&data->previous,&tmp);break;
 case 2:
 if(func_002B3868(obj))D_L07_001B2558-=60.0f;
 if(D_001A79F0==7 && D_L07_001C9780!=1) {func_002A7750(obj,1,-1);break;}
 if(!D_L07_001ADAAC)break;
 j=*(short *)(D_L07_001ADAAC+0xaa)-0x11d9;
 lo=D_L07_001AEC10[j*2];hi=D_L07_001AEC14[j*2];
 { for(i=5;i>=0;i--) {
 func_00282D30(&tmp,((char *)data+0x30),func_002A7878(-25.0f,25.0f));
 func_00282CC0(&pos,&tmp,((char *)data+0x50));
 func_00282D30(&tmp,((char *)data+0x40),func_002A7878(lo,hi));
 func_00282CC0(&pos,&tmp,&pos);
 func_00282CC0(&pos,&pos,&D_L07_001B9200);
 func_00282CF0(&pos,&pos,D_L07_001ADAAC+0x10);
 pos.z-=*(float *)(D_L07_001B90C0+0x148)-*(float *)(D_L07_001ADAAC+0x18);
 func_L02_0031E9E8(&vel,1.0f/24.0f);
 vel.z=data->fall*(func_002A7878(0.8f,1.2f)*(-1.0f/120.0f));
 func_L07_00336860(&pos,&vel,1,0);
 }
 }
 func_00282CF0(&D_L07_001B2550,&D_L07_001B9200,&data->previous);
 func_00282D30(&tmp,D_L07_001ADAAC+0xc0,1.0f);
 func_00282CC0(&D_L07_001B2550,&tmp,&D_L07_001B2550);
 qcopy_nc(&data->previous,&D_L07_001B9200);break;
 }
}
