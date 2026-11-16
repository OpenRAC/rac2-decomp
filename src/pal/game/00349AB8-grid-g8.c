#include "names.h"
/* func_PAL_00349AB8 (1,452 bytes): the PAL copy of func_003478F0 (src/game/003478F0-grid-g8.c), the
 * menu grid, with the release's larger menu object (fields from 0x258 on moved). Same C and
 * unit flags as the v1.01 copy (config/cflags.txt); its row-address pointer cast is allowed by
 * the same owner ruling (13 November 2026).
 */
#include "include_asm.h"
extern void object_set_flag_value(void *,int);
extern int *object_get_fourth_field(void *);
extern void object_set_first_float4(void *,float,float,float,float);
extern void gfx_draw_screen_element_stored(void *),text_label_draw(void *),hud_draw_colored_quad_widget(void *);
extern void hud_set_widget_value_pair(void *,int,int);
typedef struct {int x,y;} MenuIntegerPair;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern int g_help_entry_state[],g_item_ammo_counts[];
typedef struct { char pad0[0x3c]; unsigned short icon; char pad3e[0x2e]; int max; char pad70[0x18]; unsigned short ammo; char pad8a[0x56]; } MenuWeaponRecord;
extern MenuWeaponRecord ref_PAL_00349AB8_04[];
extern void meter_set_max(void *,int),meter_set_value(void *,int);
extern void shop_choose_item_colors(int,int *,int *,int *);
extern void object_set_first_pair(void *,int,int);
extern void hud_draw_progress_bar(void *);
extern int stub_empty_19(void *);
extern void *ref_PAL_00349AB8_05[];
extern void UpdateMenuGridLabels(void *),item_detail_panel_update(void *);
extern int ref_PAL_00349AB8_00,ref_PAL_00349AB8_01,ref_PAL_00349AB8_02,ref_PAL_00349AB8_03;
extern float ref_PAL_00349AB8_06,ref_PAL_00349AB8_07;
extern MenuIntegerPair ref_PAL_00349AB8_08[],ref_PAL_00349AB8_09[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair ref_PAL_00349AB8_10[],ref_PAL_00349AB8_11[];
void item_grid_menu_draw_pal(char *menu)
{
 if(*(int *)(menu+0x570)) {
  int row,col;
  MenuGridEntry *table=ref_00347468_10;

  gfx_draw_screen_element_stored(menu);gfx_draw_screen_element_stored(menu+0x4c);gfx_draw_screen_element_stored(menu+0x130);
  for(row=0;row<6;row++) {
   short *ids=&table->id;
   short *id=(short *)((row<<2)*10+(int)ids);
   for(col=0;col<4;col++,id+=5) {

    { int *color=((int *)object_get_fourth_field(menu+0x404));
      float y_base=(float)ref_PAL_00349AB8_01;
      float x_step=ref_PAL_00349AB8_06;
      float x_base=(float)ref_PAL_00349AB8_00;
      float y_step=ref_PAL_00349AB8_07;
      *color=0x60241700;
      object_set_first_float4(menu+0x404,(x_step*(float)col+x_base)+(*(float **)(menu+0x4e8))[0],(y_step*(float)row+y_base)+(*(float **)(menu+0x4e8))[1],0.0f,0.0f);
    }
    *((int *)object_get_fourth_field(menu+0x98))=0x30f0c070;
    *((int *)object_get_fourth_field((menu+0x404)))=0x60241700;
    object_set_flag_value((menu+0x1c8),0);object_set_flag_value((menu+0x3c8),0);
    if(g_item_owned_flags[*id]) {
     MenuWeaponRecord *weapons=ref_PAL_00349AB8_04;
     unsigned char *slots=g_item_slot_to_record;
     hud_set_widget_value_pair((menu+0x3c8),weapons[slots[*id]].icon,0);

     object_set_first_float4((menu+0x3c8),(53.5f*(float)col+(float)ref_PAL_00349AB8_02)+(*(float **)(menu+0x4e8))[0],(47.0f*(float)row+(float)ref_PAL_00349AB8_03)+(*(float **)(menu+0x4e8))[1],0.0f,0.0f);
     if(weapons[slots[*id]].icon==0xea7e) {
      *((int *)object_get_fourth_field((menu+0x3c8)))=0x80808080;
     } else {
      MenuIntegerPair base=ref_PAL_00349AB8_08[0],stride=ref_PAL_00349AB8_09[0];
      int bar_color_a,bar_color_b,color;
      meter_set_max((menu+0x1c8),weapons[slots[*id]].max);
      meter_set_value((menu+0x1c8),g_help_entry_state[*id]>>5);

      object_set_first_float4((menu+0x1c8),(float)(stride.x*col+base.x)+(*(float **)(menu+0x4e8))[0],(float)(stride.y*row+base.y)+(*(float **)(menu+0x4e8))[1],0.0f,0.0f);
      object_set_flag_value((menu+0x1c8),1);
      bar_color_a=0;bar_color_b=0;color=0;
      shop_choose_item_colors(*id,&bar_color_a,&bar_color_b,&color);object_set_first_pair((menu+0x1c8),bar_color_a,bar_color_b);
      *((int *)object_get_fourth_field((menu+0x3c8)))=color;
      if(weapons[slots[*id]].max<=0) {meter_set_max((menu+0x1c8),100);meter_set_value((menu+0x1c8),100);}
     }
     if(g_item_ammo_counts[*id]==0) {
      unsigned char *current_slots=g_item_slot_to_record;
      MenuWeaponRecord *current_weapons=ref_PAL_00349AB8_04;
      if(current_weapons[current_slots[*id]].ammo!=0) *((int *)object_get_fourth_field(menu+0x404))=0x60202080;
     }
     object_set_flag_value((menu+0x3c8),1);
     if(stub_empty_19(ref_PAL_00349AB8_05[0])==*id) *((int *)object_get_fourth_field(menu+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=ref_PAL_00349AB8_10[0],base=ref_PAL_00349AB8_11[0];

     object_set_first_float4(menu+0x98,(stride.x*(float)col+base.x)+(*(float **)(menu+0x4e8))[0],(stride.y*(float)row+base.y)+(*(float **)(menu+0x4e8))[0],0.0f,0.0f);
    }
    gfx_draw_screen_element_stored((menu+0x404));hud_draw_colored_quad_widget((menu+0x3c8));hud_draw_progress_bar((menu+0x1c8));gfx_draw_screen_element_stored(menu+0x98);
   }
  }
  gfx_draw_screen_element_stored(menu+0xe4);gfx_draw_screen_element_stored(menu+0x17c);text_label_draw(menu+0x210);text_label_draw(menu+0x268);text_label_draw(menu+0x2c0);
  UpdateMenuGridLabels(menu);item_detail_panel_update(menu);
 }
}
