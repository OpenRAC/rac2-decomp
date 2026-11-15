#include "include_asm.h"
#include "names.h"
extern void func_00335E68(void *, int);
extern void func_00335E38(void *,float,float,float,float);
extern void func_00336320(void *),func_00336A78(void *),func_00336828(void *);
extern void func_00336920(void *,int,int);
extern void func_00336A38(void *,int);
extern int func_00288FB8(int);
extern void func_0027FAA8(int,int,unsigned long,int,int);
typedef struct {int x,y;} MenuIntegerPair;
extern MenuIntegerPair ref_00347468_00[];
extern float ref_00347468_01 __attribute__((sda));
extern float ref_00347468_02 __attribute__((sda));
extern float ref_00347468_03 __attribute__((sda));
extern float ref_00347468_04 __attribute__((sda));
extern float ref_00347468_05 __attribute__((sda));
extern float ref_00347468_06,ref_00347468_07,ref_00347468_08,ref_00347468_09;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char D_001A7A80[] __attribute__((sda));
/* Updates the detail panel of the item under the cursor, showing an icon and label for each flag the item has. */
void func_00347468(char *menu)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(menu+0x4fc)+*(int *)(menu+0x500)*4].id;
 float *origin;
 { char *a=menu+0x378,*b=menu+0x400,*c=menu+0x44c;
 SetFlagValue(a,0);SetFlagValue(b,0);SetFlagValue(c,0);
 origin=*(float **)(menu+0x498);SetFirstFloat4(b,origin[0]+ref_00347468_02,origin[1]+ref_00347468_07,0.0f,0.0f);
 origin=*(float **)(menu+0x498);SetFirstFloat4(c,origin[0]+ref_00347468_01,origin[1]+ref_00347468_06,0.0f,0.0f);
 SetFirstFloat4(a,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(D_001A7A80[id]&1) {
  int x,y;
  SetWidgetField40(menu+0x2e8,GetLocalizedString(0x2fd0));SetWidgetValuePair(a,0xea98,0);
  SetFlagValue(a,1);SetFlagValue(b,1);SetFlagValue(c,1);
  DrawScreenElementAtStoredPosition(b);DrawScreenElementAtStoredPosition(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  DrawTextCenteredSmallFont(x,y,0x80f0f0f0UL,GetLocalizedString(0x31cf),-1);
 } else if(D_001A7A80[id]&4) {
  int x,y;
  SetWidgetField40(menu+0x2e8,GetLocalizedString(0x2fcf));SetWidgetValuePair(a,0xea98,1);
  SetFlagValue(a,1);SetFlagValue(b,1);SetFlagValue(c,1);
  DrawScreenElementAtStoredPosition(b);DrawScreenElementAtStoredPosition(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  DrawTextCenteredSmallFont(x,y,0x80f0f0f0UL,GetLocalizedString(0x31ce),-1);
 }
 DrawAlignedTextLabel(menu+0x2e8);DrawColoredQuadWidget(menu+0x378);
 }
 if(D_001A7A80[id]&0x10) {
  int x,y;char *textWidget=menu+0x330;
  char *a=menu+0x378,*b=menu+0x400,*c=menu+0x44c;
  SetWidgetField40(textWidget,GetLocalizedString(0x2fd1));SetWidgetValuePair(a,0xea98,2);
  SetFirstFloat4(a,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  SetFlagValue(a,1);SetFlagValue(b,1);SetFlagValue(c,1);
  origin=*(float **)(menu+0x498);SetFirstFloat4(b,origin[0]+ref_00347468_02,(origin[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  origin=*(float **)(menu+0x498);SetFirstFloat4(c,origin[0]+ref_00347468_01,(origin[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  DrawScreenElementAtStoredPosition(b);DrawScreenElementAtStoredPosition(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_05);y=(int)(origin[1]+ref_00347468_09);
  DrawTextCenteredSmallFont(x,y,0x80f0f0f0UL,GetLocalizedString(0x31d0),-1);
  DrawColoredQuadWidget(a);DrawAlignedTextLabel(textWidget);
 }
}
