#include "include_asm.h"
#include "names.h"

extern void DrawItemGrid(int *);
extern char g_selection_menu_rows[];
extern int g_item_grid_build_fourth_desc_a __attribute__((sda));
extern int g_item_grid_build_fourth_desc_b __attribute__((sda));
extern int g_item_grid_build_fourth_desc_c __attribute__((sda));
extern int g_item_grid_build_fourth_desc_d __attribute__((sda));
extern int g_item_grid_build_fourth_desc_e __attribute__((sda));
extern int g_item_grid_build_fourth_desc_f __attribute__((sda));
extern int g_item_grid_build_fourth_desc_g __attribute__((sda));

void func_PAL_00348520(char *o)
{
    int f[23];

    f[20] = 0;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x504);
    f[21] = ((*(int *)(o + 0x508) ^ 3) == 0);
    f[3] = *(int *)(o + 0x4FC);
    f[4] = *(int *)(o + 0x500);
    f[16] = (int)(o + 0x4B8);
    f[9] = (int)&g_item_grid_build_fourth_desc_g;
    f[14] = 3;
    f[1] = g_item_grid_build_fourth_desc_a;
    f[2] = g_item_grid_build_fourth_desc_b;
    f[0] = (int)g_selection_menu_rows;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x470);
    f[8] = (int)&g_item_grid_build_fourth_desc_f;
    f[7] = (int)&g_item_grid_build_fourth_desc_e;
    f[6] = (int)&g_item_grid_build_fourth_desc_d;
    f[5] = (int)&g_item_grid_build_fourth_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}

extern char g_item_grid_second_mode_rows[];
extern int g_item_grid_build_second_desc_a __attribute__((sda));
extern int g_item_grid_build_second_desc_b __attribute__((sda));
extern int g_item_grid_build_second_desc_c __attribute__((sda));
extern int g_item_grid_build_second_desc_d __attribute__((sda));
extern int g_item_grid_build_second_desc_e __attribute__((sda));
extern int g_item_grid_build_second_desc_f __attribute__((sda));
extern int g_item_grid_build_second_desc_g __attribute__((sda));

void func_PAL_00348628(char *o)
{
    int f[23];

    f[20] = 0;
    f[14] = 1;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x504);
    f[21] = ((*(int *)(o + 0x508) ^ 1) == 0);
    f[3] = *(int *)(o + 0x4FC);
    f[4] = *(int *)(o + 0x500);
    f[16] = (int)(o + 0x4B8);
    f[9] = (int)&g_item_grid_build_second_desc_g;
    f[1] = g_item_grid_build_second_desc_a;
    f[2] = g_item_grid_build_second_desc_b;
    f[0] = (int)g_item_grid_second_mode_rows;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x470);
    f[8] = (int)&g_item_grid_build_second_desc_f;
    f[7] = (int)&g_item_grid_build_second_desc_e;
    f[6] = (int)&g_item_grid_build_second_desc_d;
    f[5] = (int)&g_item_grid_build_second_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}

extern void selection_grid_handle_input_pal(char *, int);
extern void selection_menu_handle_two_entry_input_pal(char *, int);
extern void HandleColumnSelectionInput(char *, int);
extern int g_menu_input_flags __attribute__((section(".data")));
extern int func_PAL_002A9FA0(int,int,int,int,int);
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

int func_PAL_003480C8(char *o,int buttons,int *out)
{
 LayoutPair offset;
 int *color;
 int mode;
 *out=*(int *)(o+0x508);
 *(int *)(o+0x504)=0;
 mode=*(int *)(o+0x508);
 ref_L00_00345F70_00=-1;
 offset=ref_L00_00345F70_01;
 switch(mode) {
 case 0:*out=0;selection_grid_handle_input_pal(o,buttons);break;
 case 3:*out=mode;selection_menu_handle_two_entry_input_pal(o,buttons);break;
 case 1:*out=mode;HandleColumnSelectionInput(o,buttons);break;
 }
 if(g_menu_input_flags&0xf000) func_PAL_002A9FA0(0,0,1,0,1);
 color=object_get_fourth_field(o+0x17c);
 *color=func_PAL_002A9FA0(0x60442d00,0x70fffeed,20,0,0);
 object_set_first_float4(o+0x0,ref_L00_00345F70_02+(*(float **)(o+0x470))[0],ref_L00_00345F70_12[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x4c,ref_L00_00345F70_03+(*(float **)(o+0x470))[0],ref_L00_00345F70_13[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x98,ref_L00_00345F70_04+(*(float **)(o+0x470))[0],ref_L00_00345F70_14[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0xe4,ref_L00_00345F70_05+(*(float **)(o+0x470))[0],ref_L00_00345F70_15[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x130,ref_L00_00345F70_06+(*(float **)(o+0x470))[0],ref_L00_00345F70_16[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x1c8,offset.x+(*(float **)(o+0x470))[0],offset.y+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x310,ref_L00_00345F70_07+(*(float **)(o+0x470))[0],ref_L00_00345F70_17[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x2B8,ref_L00_00345F70_08+(*(float **)(o+0x470))[0],ref_L00_00345F70_18[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x368,ref_L00_00345F70_09+(*(float **)(o+0x470))[0],ref_L00_00345F70_19[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x3C0,ref_L00_00345F70_10+(*(float **)(o+0x470))[0],ref_L00_00345F70_20[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 object_set_first_float4(o+0x418,ref_L00_00345F70_11+(*(float **)(o+0x470))[0],ref_L00_00345F70_21[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 return 0;
}

typedef struct { unsigned int lo; unsigned int hi; } Word2_462A8;
extern char g_menu_item_table_second[];
extern Word2_462A8 g_info_word_pair_page __attribute__((nosda));
extern int g_item_grid_page_desc_a __attribute__((sda));
extern int g_item_grid_page_desc_b __attribute__((sda));
extern int g_item_grid_page_desc_c __attribute__((sda));
extern int g_item_grid_page_desc_d __attribute__((sda));
extern int g_item_grid_page_desc_e __attribute__((sda));
extern int g_item_grid_page_desc_f __attribute__((sda));
extern int g_item_grid_page_desc_g __attribute__((sda));
static __inline__ void initDescriptor_462A8(int *f) { f[20] = 0; f[21] = 1; }

void func_PAL_00348400(char *o)
{
    struct { Word2_462A8 q; int f[23] __attribute__((aligned(16))); } local;

    local.q = g_info_word_pair_page;

    initDescriptor_462A8(local.f);
    local.f[19] = *(int *)(o + 0x504);
    local.f[21] = (*(int *)(o + 0x508) == 0);
    local.f[3] = *(int *)(o + 0x4FC);
    local.f[4] = *(int *)(o + 0x500);
    local.f[16] = (int)(o + 0x4B8);
    local.f[9] = (int)&g_item_grid_page_desc_g;
    local.f[1] = g_item_grid_page_desc_a;
    local.f[2] = g_item_grid_page_desc_b;
    local.f[0] = (int)g_menu_item_table_second;
    local.f[17] = (int)(o + 0x220);
    local.f[10] = (int)(o + 0x130);
    local.f[12] = (int)(o + 0x17C);
    local.f[15] = (int)(o + 0x278);
    local.f[18] = *(int *)(o + 0x470);
    local.f[8] = (int)&g_item_grid_page_desc_f;
    local.f[7] = (int)&g_item_grid_page_desc_e;
    local.f[6] = (int)&g_item_grid_page_desc_d;
    local.f[5] = (int)&g_item_grid_page_desc_c;
    local.f[14] = 0;
    local.f[11] = 0;
    local.f[13] = 0;
    local.f[20] = (int)&local.q;
    local.f[22] = 1;
    DrawItemGrid(local.f);
}
