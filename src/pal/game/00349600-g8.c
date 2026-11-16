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
extern void text_draw_centered_small_fitted(int,int,unsigned long,int,int,int,float);
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
extern unsigned char g_movie_seen_flags[] __attribute__((sda));
/* Shows or hides the item detail panel (movie-seen state texts, icon and frames) for the selected grid entry. (PAL) */
void item_detail_panel_update_pal(char *menu)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(menu+0x574)+*(int *)(menu+0x578)*4].id;
 float *origin;
 { char *icon=menu+0x3c8,*frame_b=menu+0x450,*frame_c=menu+0x49c;
 object_set_flag_value(icon,0);object_set_flag_value(frame_b,0);object_set_flag_value(frame_c,0);
 origin=*(float **)(menu+0x4e8);object_set_first_float4(frame_b,origin[0]+ref_00347468_02,origin[1]+ref_00347468_07,0.0f,0.0f);
 origin=*(float **)(menu+0x4e8);object_set_first_float4(frame_c,origin[0]+ref_00347468_01,origin[1]+ref_00347468_06,0.0f,0.0f);
 object_set_first_float4(icon,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(g_movie_seen_flags[id]&1) {
  int x,y;
  hud_set_widget_field_b(menu+0x318,GetLocalizedString(3828));hud_set_widget_value_pair(icon,0xea98,0);
  object_set_flag_value(icon,1);object_set_flag_value(frame_b,1);object_set_flag_value(frame_c,1);
  gfx_draw_screen_element_stored(frame_b);gfx_draw_screen_element_stored(frame_c);
  origin=*(float **)(menu+0x4e8);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_centered_small_fitted(x,y,0x80f0f0f0UL,GetLocalizedString(4327),-1,175,0.7f);
 } else if(g_movie_seen_flags[id]&4) {
  int x,y;
  hud_set_widget_field_b(menu+0x318,GetLocalizedString(3827));hud_set_widget_value_pair(icon,0xea98,1);
  object_set_flag_value(icon,1);object_set_flag_value(frame_b,1);object_set_flag_value(frame_c,1);
  gfx_draw_screen_element_stored(frame_b);gfx_draw_screen_element_stored(frame_c);
  origin=*(float **)(menu+0x4e8);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_centered_small_fitted(x,y,0x80f0f0f0UL,GetLocalizedString(4326),-1,175,0.7f);
 }
 text_label_draw(menu+0x318);hud_draw_colored_quad_widget(menu+0x3c8);
 }
 if(g_movie_seen_flags[id]&0x10) {
  int x,y;char *label=menu+0x370;
  char *icon=menu+0x3c8,*frame_b=menu+0x450,*frame_c=menu+0x49c;
  hud_set_widget_field_b(label,GetLocalizedString(3829));hud_set_widget_value_pair(icon,0xea98,2);
  object_set_first_float4(icon,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  object_set_flag_value(icon,1);object_set_flag_value(frame_b,1);object_set_flag_value(frame_c,1);
  origin=*(float **)(menu+0x4e8);object_set_first_float4(frame_b,origin[0]+ref_00347468_02,(origin[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  origin=*(float **)(menu+0x4e8);object_set_first_float4(frame_c,origin[0]+ref_00347468_01,(origin[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  gfx_draw_screen_element_stored(frame_b);gfx_draw_screen_element_stored(frame_c);
  origin=*(float **)(menu+0x4e8);x=(int)(origin[0]+ref_00347468_05);y=(int)(origin[1]+ref_00347468_09);
  text_draw_centered_small_fitted(x,y,0x80f0f0f0UL,GetLocalizedString(4328),-1,175,0.7f);
  hud_draw_colored_quad_widget(icon);text_label_draw(label);
 }
}
