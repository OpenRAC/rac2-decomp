#include "names.h"
/* func_003478F0 (1,452 bytes, 28 places): the menu grid. The layout scalars are declared yb, xs,
 * xb, ys; the row address is `(short *)((row << 2) * 10 + (int)ids)`, a pointer cast that only
 * sets one addu's operand order (allowed by owner ruling, 13 November 2026).
 * Own unit: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt -frac2-pseudo-base -frac2-gcse-hash-171 -frac2-sched-elapsed-latency
 * (config/cflags.txt; docs/build/compiler-notes.md). Owner standard of 12 November 2026 for
 * the switches.
 */
#include "include_asm.h"
#include "names.h"
extern void object_set_flag_value(void *,int);
extern int object_get_fourth_field(void *);
extern void object_set_first_float4(void *,float,float,float,float);
extern void gfx_draw_screen_element_stored(void *),text_label_draw(void *),hud_draw_colored_quad_widget(void *);
extern void hud_set_widget_value_pair(void *,int,int);
typedef struct {int x,y;} MenuIntegerPair;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern int D_00139868[],g_item_ammo_counts[];
typedef struct { char pad0[0x3c]; unsigned short icon; char pad3e[0x2e]; int max; char pad70[0x18]; unsigned short ammo; char pad8a[0x56]; } MenuWeaponRecord;
extern MenuWeaponRecord ref_003478F0_04[];
extern void meter_set_max(void *,int),meter_set_value(void *,int);
extern void shop_choose_item_colors(int,int *,int *,int *);
extern void object_set_first_pair(void *,int,int);
extern void hud_draw_progress_bar(void *);
extern int stub_empty_19(void *);
extern void *ref_003478F0_05[];
extern void UpdateMenuGridLabels(void *),item_detail_panel_update(void *);
extern int ref_003478F0_00,ref_003478F0_01,ref_003478F0_02,ref_003478F0_03;
extern float ref_003478F0_06,ref_003478F0_07;
extern MenuIntegerPair ref_003478F0_08[],ref_003478F0_09[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair ref_003478F0_10[],ref_003478F0_11[];
/* Draws every slot of the item grid menu: the backdrop, the weapon icon, the ammo bar and the highlight on the selected item. */
void item_grid_menu_draw(char *menu)
{
 if(*(int *)(menu+0x4f8)) {
  int row,col;
  MenuGridEntry *gridEntries=ref_00347468_10;

  gfx_draw_screen_element_stored(menu);gfx_draw_screen_element_stored(menu+0x4c);gfx_draw_screen_element_stored(menu+0x130);
  for(row=0;row<6;row++) {
   short *idField=&gridEntries->id;
   short *idPtr=(short *)((row<<2)*10+(int)idField);
   for(col=0;col<4;col++,idPtr+=5) {

    { int *color=((int *)object_get_fourth_field(menu+0x3b4));
      float yb=(float)ref_003478F0_01;
      float xs=ref_003478F0_06;
      float xb=(float)ref_003478F0_00;
      float ys=ref_003478F0_07;
      *color=0x60241700;
      object_set_first_float4(menu+0x3b4,(xs*(float)col+xb)+(*(float **)(menu+0x498))[0],(ys*(float)row+yb)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
    }
    *((int *)object_get_fourth_field(menu+0x98))=0x30f0c070;
    *((int *)object_get_fourth_field((menu+0x3b4)))=0x60241700;
    object_set_flag_value((menu+0x1c8),0);object_set_flag_value((menu+0x378),0);
    if(g_item_owned_flags[*idPtr]) {
     MenuWeaponRecord *weapons=ref_003478F0_04;
     unsigned char *slots=g_item_slot_to_record;
     hud_set_widget_value_pair((menu+0x378),weapons[slots[*idPtr]].icon,0);

     object_set_first_float4((menu+0x378),(53.5f*(float)col+(float)ref_003478F0_02)+(*(float **)(menu+0x498))[0],(47.0f*(float)row+(float)ref_003478F0_03)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
     if(weapons[slots[*idPtr]].icon==0xea7e) {
      *((int *)object_get_fourth_field((menu+0x378)))=0x80808080;
     } else {
      MenuIntegerPair base=ref_003478F0_08[0],stride=ref_003478F0_09[0];
      int barColorA,barColorB,color;
      meter_set_max((menu+0x1c8),weapons[slots[*idPtr]].max);
      meter_set_value((menu+0x1c8),D_00139868[*idPtr]>>5);

      object_set_first_float4((menu+0x1c8),(float)(stride.x*col+base.x)+(*(float **)(menu+0x498))[0],(float)(stride.y*row+base.y)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
      object_set_flag_value((menu+0x1c8),1);
      barColorA=0;barColorB=0;color=0;
      shop_choose_item_colors(*idPtr,&barColorA,&barColorB,&color);object_set_first_pair((menu+0x1c8),barColorA,barColorB);
      *((int *)object_get_fourth_field((menu+0x378)))=color;
      if(weapons[slots[*idPtr]].max<=0) {meter_set_max((menu+0x1c8),100);meter_set_value((menu+0x1c8),100);}
     }
     if(g_item_ammo_counts[*idPtr]==0) {
      unsigned char *currentSlots=g_item_slot_to_record;
      MenuWeaponRecord *currentWeapons=ref_003478F0_04;
      if(currentWeapons[currentSlots[*idPtr]].ammo!=0) *((int *)object_get_fourth_field(menu+0x3b4))=0x60202080;
     }
     object_set_flag_value((menu+0x378),1);
     if(stub_empty_19(ref_003478F0_05[0])==*idPtr) *((int *)object_get_fourth_field(menu+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=ref_003478F0_10[0],base=ref_003478F0_11[0];

     object_set_first_float4(menu+0x98,(stride.x*(float)col+base.x)+(*(float **)(menu+0x498))[0],(stride.y*(float)row+base.y)+(*(float **)(menu+0x498))[0],0.0f,0.0f);
    }
    gfx_draw_screen_element_stored((menu+0x3b4));hud_draw_colored_quad_widget((menu+0x378));hud_draw_progress_bar((menu+0x1c8));gfx_draw_screen_element_stored(menu+0x98);
   }
  }
  gfx_draw_screen_element_stored(menu+0xe4);gfx_draw_screen_element_stored(menu+0x17c);text_label_draw(menu+0x210);text_label_draw(menu+0x258);text_label_draw(menu+0x2a0);
  UpdateMenuGridLabels(menu);item_detail_panel_update(menu);
 }
}
