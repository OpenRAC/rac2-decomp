#include "include_asm.h"
#include "names.h"
/* func_US2_003481E0, the USA v2.00 copy of func_00347468: the same C without the 0x2e8 and 0x330 label
 * elements, a smaller object (fields 0x60 lower, 0x38 for the selection indices), and func_US2_00280440
 * for the captions. */
extern void object_set_flag_value(void *, int);
extern void object_set_first_float4(void *,float,float,float,float);
extern void gfx_draw_screen_element_stored(void *),hud_draw_colored_quad_widget(void *);
extern void hud_set_widget_value_pair(void *,int,int);
extern char *GetLocalizedString(int);
extern void text_draw_shrunk_to_width_us2(int,int,unsigned long,int,int,int,float);
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
/* Draws the movie gallery detail panel: the selected movie's icon, its frame and its caption, by what has been seen (USA v2.00 copy). */
void item_detail_panel_update_us2(char *menu)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(menu+0x4c4)+*(int *)(menu+0x4c8)*4].id;
 float *origin;
 { char *icon=menu+0x318,*label_a=menu+0x3a0,*label_b=menu+0x3ec;
 object_set_flag_value(icon,0);object_set_flag_value(label_a,0);object_set_flag_value(label_b,0);
 origin=*(float **)(menu+0x438);object_set_first_float4(label_a,origin[0]+ref_00347468_02,origin[1]+ref_00347468_07,0.0f,0.0f);
 origin=*(float **)(menu+0x438);object_set_first_float4(label_b,origin[0]+ref_00347468_01,origin[1]+ref_00347468_06,0.0f,0.0f);
 object_set_first_float4(icon,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(g_movie_seen_flags[id]&1) {
  int x,y;
  hud_set_widget_value_pair(icon,0xea98,0);
  object_set_flag_value(icon,1);object_set_flag_value(label_a,1);object_set_flag_value(label_b,1);
  gfx_draw_screen_element_stored(label_a);gfx_draw_screen_element_stored(label_b);
  origin=*(float **)(menu+0x438);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_shrunk_to_width_us2(x,y,0x80f0f0f0UL,GetLocalizedString(0x3065),-1,0xaf,0.7f);
 } else if(g_movie_seen_flags[id]&4) {
  int x,y;
  hud_set_widget_value_pair(icon,0xea98,1);
  object_set_flag_value(icon,1);object_set_flag_value(label_a,1);object_set_flag_value(label_b,1);
  gfx_draw_screen_element_stored(label_a);gfx_draw_screen_element_stored(label_b);
  origin=*(float **)(menu+0x438);x=(int)(origin[0]+ref_00347468_04);y=(int)(origin[1]+ref_00347468_08);
  text_draw_shrunk_to_width_us2(x,y,0x80f0f0f0UL,GetLocalizedString(0x3064),-1,0xaf,0.7f);
 }
 hud_draw_colored_quad_widget(menu+0x318);
 }
 if(g_movie_seen_flags[id]&0x10) {
  int x,y;
  char *icon=menu+0x318,*label_a=menu+0x3a0,*label_b=menu+0x3ec;
  hud_set_widget_value_pair(icon,0xea98,2);
  object_set_first_float4(icon,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  object_set_flag_value(icon,1);object_set_flag_value(label_a,1);object_set_flag_value(label_b,1);
  origin=*(float **)(menu+0x438);object_set_first_float4(label_a,origin[0]+ref_00347468_02,(origin[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  origin=*(float **)(menu+0x438);object_set_first_float4(label_b,origin[0]+ref_00347468_01,(origin[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  gfx_draw_screen_element_stored(label_a);gfx_draw_screen_element_stored(label_b);
  origin=*(float **)(menu+0x438);x=(int)(origin[0]+ref_00347468_05);y=(int)(origin[1]+ref_00347468_09);
  text_draw_shrunk_to_width_us2(x,y,0x80f0f0f0UL,GetLocalizedString(0x3066),-1,0xaf,0.7f);
  hud_draw_colored_quad_widget(icon);
 }
}
