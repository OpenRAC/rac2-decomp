/* Runs the input handler for the object's mode, then sets the positions of its child elements. */
#include "include_asm.h"
#include "names.h"
extern void func_003458F8(char *, int);
extern void func_00345B78(char *, int);
extern void func_00345D58(char *, int);
extern int D_00138344 __attribute__((section(".data")));
extern int func_002A9588(int,int,int,int,int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *,float,float,float,float);
extern int ref_L00_00345F70_00 __attribute__((sda));
typedef struct {float x,y;} LayoutPair;
extern LayoutPair ref_L00_00345F70_01 __attribute__((section(".data")));
extern float ref_L00_00345F70_02 __attribute__((sda));
extern float ref_L00_00345F70_03 __attribute__((sda));
extern float ref_L00_00345F70_04 __attribute__((sda));
extern float ref_L00_00345F70_05 __attribute__((sda));
extern float ref_L00_00345F70_06 __attribute__((sda));
extern float ref_L00_00345F70_07 __attribute__((sda));
extern float ref_L00_00345F70_08 __attribute__((sda));
extern float ref_L00_00345F70_09 __attribute__((sda));
extern float ref_L00_00345F70_10 __attribute__((sda));
extern float ref_L00_00345F70_11 __attribute__((sda));
extern float ref_L00_00345F70_12[] __attribute__((sda));
extern float ref_L00_00345F70_13[] __attribute__((sda));
extern float ref_L00_00345F70_14[] __attribute__((sda));
extern float ref_L00_00345F70_15[] __attribute__((sda));
extern float ref_L00_00345F70_16[] __attribute__((sda));
extern float ref_L00_00345F70_17[] __attribute__((sda));
extern float ref_L00_00345F70_18[] __attribute__((sda));
extern float ref_L00_00345F70_19[] __attribute__((sda));
extern float ref_L00_00345F70_20[] __attribute__((sda));
extern float ref_L00_00345F70_21[] __attribute__((sda));
/* Runs the pad handler for the menu's current mode, then moves all its parts to their places. */
int func_00345F70(char *menu,int buttons,int *outMode)
{
 LayoutPair offset;
 int *color;
 int mode;
 *outMode=*(int *)(menu+0x498);
 *(int *)(menu+0x494)=0;
 mode=*(int *)(menu+0x498);
 ref_L00_00345F70_00=-1;
 offset=ref_L00_00345F70_01;
 switch(mode) {
 case 0:*outMode=0;HandleSelectionGridInput(menu,buttons);break;
 case 3:*outMode=mode;HandleTwoEntrySelectionInput(menu,buttons);break;
 case 1:*outMode=mode;HandleColumnSelectionInput(menu,buttons);break;
 }
 if(D_00138344&0xf000) PingPongBlendValues(0,0,1,0,1);
 color=GetFieldC(menu+0x17c);
 *color=PingPongBlendValues(0x60442d00,0x70fffeed,20,0,0);
 SetFirstFloat4(menu+0x0,ref_L00_00345F70_02+(*(float **)(menu+0x400))[0],ref_L00_00345F70_12[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x4c,ref_L00_00345F70_03+(*(float **)(menu+0x400))[0],ref_L00_00345F70_13[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x98,ref_L00_00345F70_04+(*(float **)(menu+0x400))[0],ref_L00_00345F70_14[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0xe4,ref_L00_00345F70_05+(*(float **)(menu+0x400))[0],ref_L00_00345F70_15[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x130,ref_L00_00345F70_06+(*(float **)(menu+0x400))[0],ref_L00_00345F70_16[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x1c8,offset.x+(*(float **)(menu+0x400))[0],offset.y+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x2e0,ref_L00_00345F70_07+(*(float **)(menu+0x400))[0],ref_L00_00345F70_17[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x298,ref_L00_00345F70_08+(*(float **)(menu+0x400))[0],ref_L00_00345F70_18[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x328,ref_L00_00345F70_09+(*(float **)(menu+0x400))[0],ref_L00_00345F70_19[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x370,ref_L00_00345F70_10+(*(float **)(menu+0x400))[0],ref_L00_00345F70_20[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 SetFirstFloat4(menu+0x3b8,ref_L00_00345F70_11+(*(float **)(menu+0x400))[0],ref_L00_00345F70_21[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 return 0;
}
