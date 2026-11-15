#include "names.h"
/* Runs the input handler for the object's mode, then sets the positions of its child elements. */
#include "include_asm.h"
#include "names.h"
extern void selection_grid_handle_input(char *, int);
extern void selection_menu_handle_two_entry_input(char *, int);
extern void HandleColumnSelectionInput(char *, int);
extern int D_00138344 __attribute__((section(".data")));
extern int math_ping_pong_blend_values(int,int,int,int,int);
extern int *object_get_fourth_field(void *);
extern void object_set_first_float4(void *,float,float,float,float);
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
int selection_menu_update_layout(char *menu,int buttons,int *outMode)
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
 case 0:*outMode=0;selection_grid_handle_input(menu,buttons);break;
 case 3:*outMode=mode;selection_menu_handle_two_entry_input(menu,buttons);break;
 case 1:*outMode=mode;HandleColumnSelectionInput(menu,buttons);break;
 }
 if(D_00138344&0xf000) math_ping_pong_blend_values(0,0,1,0,1);
 color=object_get_fourth_field(menu+0x17c);
 *color=math_ping_pong_blend_values(0x60442d00,0x70fffeed,20,0,0);
 object_set_first_float4(menu+0x0,ref_L00_00345F70_02+(*(float **)(menu+0x400))[0],ref_L00_00345F70_12[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x4c,ref_L00_00345F70_03+(*(float **)(menu+0x400))[0],ref_L00_00345F70_13[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x98,ref_L00_00345F70_04+(*(float **)(menu+0x400))[0],ref_L00_00345F70_14[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0xe4,ref_L00_00345F70_05+(*(float **)(menu+0x400))[0],ref_L00_00345F70_15[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x130,ref_L00_00345F70_06+(*(float **)(menu+0x400))[0],ref_L00_00345F70_16[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x1c8,offset.x+(*(float **)(menu+0x400))[0],offset.y+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x2e0,ref_L00_00345F70_07+(*(float **)(menu+0x400))[0],ref_L00_00345F70_17[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x298,ref_L00_00345F70_08+(*(float **)(menu+0x400))[0],ref_L00_00345F70_18[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x328,ref_L00_00345F70_09+(*(float **)(menu+0x400))[0],ref_L00_00345F70_19[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x370,ref_L00_00345F70_10+(*(float **)(menu+0x400))[0],ref_L00_00345F70_20[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x3b8,ref_L00_00345F70_11+(*(float **)(menu+0x400))[0],ref_L00_00345F70_21[0]+(*(float **)(menu+0x400))[1],0.0f,0.0f);
 return 0;
}
