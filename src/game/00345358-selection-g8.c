#include "include_asm.h"
#include "names.h"
extern void object_set_flag_value(void *, int);
extern void object_set_first_float4(void *,float,float,float,float);
extern void gfx_draw_screen_element_stored(void *),text_label_draw(void *),hud_draw_colored_quad_widget(void *);
extern void hud_set_widget_value_pair(void *,int,int);
extern void hud_set_widget_field_b(void *,int);
extern int GetLocalizedString(int);
extern void text_draw_centered_small(int,int,unsigned long,int,int);
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
void item_detail_panel_update(char *menu)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(menu+0x4fc)+*(int *)(menu+0x500)*4].id;
 float *origin;
 { char *a=menu+0x378,*b=menu+0x400,*c=menu+0x44c;
 object_set_flag_value(a,0);object_set_flag_value(b,0);object_set_flag_value(c,0);
 origin=*(float **)(menu+0x498);object_set_first_float4(b,origin[0]+ref_00347468_02,origin[1]+ref_00347468_07,0.0f,0.0f);
 origin=*(float **)(menu+0x498);object_set_first_float4(c,origin[0]+ref_00347468_01,origin[1]+ref_00347468_06,0.0f,0.0f);
 object_set_first_float4(a,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(D_001A7A80[id]&1) {
  int x,y;
  hud_set_widget_field_b(menu+0x2e8,GetLocalizedString(0x2fd0));hud_set_widget_value_pair(a,0xea98,0);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_centered_small(x,y,0x80f0f0f0UL,GetLocalizedString(0x31cf),-1);
 } else if(D_001A7A80[id]&4) {
  int x,y;
  hud_set_widget_field_b(menu+0x2e8,GetLocalizedString(0x2fcf));hud_set_widget_value_pair(a,0xea98,1);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_centered_small(x,y,0x80f0f0f0UL,GetLocalizedString(0x31ce),-1);
 }
 text_label_draw(menu+0x2e8);hud_draw_colored_quad_widget(menu+0x378);
 }
 if(D_001A7A80[id]&0x10) {
  int x,y;char *textWidget=menu+0x330;
  char *a=menu+0x378,*b=menu+0x400,*c=menu+0x44c;
  hud_set_widget_field_b(textWidget,GetLocalizedString(0x2fd1));hud_set_widget_value_pair(a,0xea98,2);
  object_set_first_float4(a,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  origin=*(float **)(menu+0x498);object_set_first_float4(b,origin[0]+ref_00347468_02,(origin[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  origin=*(float **)(menu+0x498);object_set_first_float4(c,origin[0]+ref_00347468_01,(origin[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  origin=*(float **)(menu+0x498);x=(int)(origin[0]+ref_00347468_05);y=(int)(origin[1]+ref_00347468_09);
  text_draw_centered_small(x,y,0x80f0f0f0UL,GetLocalizedString(0x31d0),-1);
  hud_draw_colored_quad_widget(a);text_label_draw(textWidget);
 }
}
