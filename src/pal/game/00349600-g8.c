#include "names.h"
/* func_PAL_00349600, the PAL copy of func_00347468: the same C, where the fields past 0x2e8 move, the
   string ids and sizes change, and the draw call becomes func_PAL_002802D8 with a width limit. */
#include "include_asm.h"
extern void object_set_flag_value(void *, int);
extern void object_set_first_float4(void *,float,float,float,float);
extern void gfx_draw_screen_element_stored(void *),text_label_draw(void *),hud_draw_colored_quad_widget(void *);
extern void hud_set_widget_value_pair(void *,int,int);
extern void hud_set_widget_field_b(void *,int);
extern char *GetLocalizedString(int);
extern void func_PAL_002802D8(int,int,unsigned long,int,int,int,float);
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
void func_PAL_00349600(char *o)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(o+0x574)+*(int *)(o+0x578)*4].id;
 float *v;
 { char *a=o+0x3c8,*b=o+0x450,*c=o+0x49c;
 object_set_flag_value(a,0);object_set_flag_value(b,0);object_set_flag_value(c,0);
 v=*(float **)(o+0x4e8);object_set_first_float4(b,v[0]+ref_00347468_02,v[1]+ref_00347468_07,0.0f,0.0f);
 v=*(float **)(o+0x4e8);object_set_first_float4(c,v[0]+ref_00347468_01,v[1]+ref_00347468_06,0.0f,0.0f);
 object_set_first_float4(a,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(D_001A7A80[id]&1) {
  int x,y;
  hud_set_widget_field_b(o+0x318,GetLocalizedString(3828));hud_set_widget_value_pair(a,0xea98,0);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,GetLocalizedString(4327),-1,175,0.7f);
 } else if(D_001A7A80[id]&4) {
  int x,y;
  hud_set_widget_field_b(o+0x318,GetLocalizedString(3827));hud_set_widget_value_pair(a,0xea98,1);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,GetLocalizedString(4326),-1,175,0.7f);
 }
 text_label_draw(o+0x318);hud_draw_colored_quad_widget(o+0x3c8);
 }
 if(D_001A7A80[id]&0x10) {
  int x,y;char *t=o+0x370;
  char *a=o+0x3c8,*b=o+0x450,*c=o+0x49c;
  hud_set_widget_field_b(t,GetLocalizedString(3829));hud_set_widget_value_pair(a,0xea98,2);
  object_set_first_float4(a,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  object_set_flag_value(a,1);object_set_flag_value(b,1);object_set_flag_value(c,1);
  v=*(float **)(o+0x4e8);object_set_first_float4(b,v[0]+ref_00347468_02,(v[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  v=*(float **)(o+0x4e8);object_set_first_float4(c,v[0]+ref_00347468_01,(v[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_05);y=(int)(v[1]+ref_00347468_09);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,GetLocalizedString(4328),-1,175,0.7f);
  hud_draw_colored_quad_widget(a);text_label_draw(t);
 }
}
