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

/* Draws the large selection menu page for its fourth mode (USA v2.00 copy). */
void item_grid_build_descriptor_fourth_mode_us2(char *menu)
{
    int desc[23];

    desc[20] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x504);
    desc[21] = ((*(int *)(menu + 0x508) ^ 3) == 0);
    desc[3] = *(int *)(menu + 0x4FC);
    desc[4] = *(int *)(menu + 0x500);
    desc[16] = (int)(menu + 0x4B8);
    desc[9] = (int)&g_item_grid_build_fourth_desc_g;
    desc[14] = 3;
    desc[1] = g_item_grid_build_fourth_desc_a;
    desc[2] = g_item_grid_build_fourth_desc_b;
    desc[0] = (int)g_selection_menu_rows;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x470);
    desc[8] = (int)&g_item_grid_build_fourth_desc_f;
    desc[7] = (int)&g_item_grid_build_fourth_desc_e;
    desc[6] = (int)&g_item_grid_build_fourth_desc_d;
    desc[5] = (int)&g_item_grid_build_fourth_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
}

extern char g_item_grid_second_mode_rows[];
extern int g_item_grid_build_second_desc_a __attribute__((sda));
extern int g_item_grid_build_second_desc_b __attribute__((sda));
extern int g_item_grid_build_second_desc_c __attribute__((sda));
extern int g_item_grid_build_second_desc_d __attribute__((sda));
extern int g_item_grid_build_second_desc_e __attribute__((sda));
extern int g_item_grid_build_second_desc_f __attribute__((sda));
extern int g_item_grid_build_second_desc_g __attribute__((sda));

/* Draws the large selection menu page for its second mode (USA v2.00 copy). */
void item_grid_build_descriptor_second_mode_us2(char *menu)
{
    int desc[23];

    desc[20] = 0;
    desc[14] = 1;
    desc[11] = 0;
    desc[13] = 0;
    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x504);
    desc[21] = ((*(int *)(menu + 0x508) ^ 1) == 0);
    desc[3] = *(int *)(menu + 0x4FC);
    desc[4] = *(int *)(menu + 0x500);
    desc[16] = (int)(menu + 0x4B8);
    desc[9] = (int)&g_item_grid_build_second_desc_g;
    desc[1] = g_item_grid_build_second_desc_a;
    desc[2] = g_item_grid_build_second_desc_b;
    desc[0] = (int)g_item_grid_second_mode_rows;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x470);
    desc[8] = (int)&g_item_grid_build_second_desc_f;
    desc[7] = (int)&g_item_grid_build_second_desc_e;
    desc[6] = (int)&g_item_grid_build_second_desc_d;
    desc[5] = (int)&g_item_grid_build_second_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
}

extern void selection_grid_handle_input_us2(char *, int);
extern void selection_menu_handle_two_entry_input_us2(char *, int);
extern void HandleColumnSelectionInput(char *, int);
extern int g_menu_input_flags __attribute__((section(".data")));
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

/* Updates the selection menu: runs the input handler for the current mode, blends the cursor color and
   places the widgets relative to the menu position; returns 0 (USA v2.00 copy). */
int selection_menu_update_layout_us2(char *menu,int buttons,int *out)
{
 LayoutPair offset;
 int *color;
 int mode;
 *out=*(int *)(menu+0x508);
 *(int *)(menu+0x504)=0;
 mode=*(int *)(menu+0x508);
 ref_L00_00345F70_00=-1;
 offset=ref_L00_00345F70_01;
 switch(mode) {
 case 0:*out=0;selection_grid_handle_input_us2(menu,buttons);break;
 case 3:*out=mode;selection_menu_handle_two_entry_input_us2(menu,buttons);break;
 case 1:*out=mode;HandleColumnSelectionInput(menu,buttons);break;
 }
 if(g_menu_input_flags&0xf000) math_ping_pong_blend_values(0,0,1,0,1);
 color=object_get_fourth_field(menu+0x17c);
 *color=math_ping_pong_blend_values(0x60442d00,0x70fffeed,20,0,0);
 object_set_first_float4(menu+0x0,ref_L00_00345F70_02+(*(float **)(menu+0x470))[0],ref_L00_00345F70_12[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x4c,ref_L00_00345F70_03+(*(float **)(menu+0x470))[0],ref_L00_00345F70_13[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x98,ref_L00_00345F70_04+(*(float **)(menu+0x470))[0],ref_L00_00345F70_14[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0xe4,ref_L00_00345F70_05+(*(float **)(menu+0x470))[0],ref_L00_00345F70_15[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x130,ref_L00_00345F70_06+(*(float **)(menu+0x470))[0],ref_L00_00345F70_16[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x1c8,offset.x+(*(float **)(menu+0x470))[0],offset.y+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x310,ref_L00_00345F70_07+(*(float **)(menu+0x470))[0],ref_L00_00345F70_17[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x2B8,ref_L00_00345F70_08+(*(float **)(menu+0x470))[0],ref_L00_00345F70_18[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x368,ref_L00_00345F70_09+(*(float **)(menu+0x470))[0],ref_L00_00345F70_19[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x3C0,ref_L00_00345F70_10+(*(float **)(menu+0x470))[0],ref_L00_00345F70_20[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
 object_set_first_float4(menu+0x418,ref_L00_00345F70_11+(*(float **)(menu+0x470))[0],ref_L00_00345F70_21[0]+(*(float **)(menu+0x470))[1],0.0f,0.0f);
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
static __inline__ void initDescriptor_462A8(int *desc) { desc[20] = 0; desc[21] = 1; }

/* Draws the large selection menu page for its first mode (USA v2.00 copy). */
void item_grid_draw_page_us2(char *menu)
{
    struct { Word2_462A8 q; int desc[23] __attribute__((aligned(16))); } local;

    local.q = g_info_word_pair_page;

    initDescriptor_462A8(local.desc);
    local.desc[19] = *(int *)(menu + 0x504);
    local.desc[21] = (*(int *)(menu + 0x508) == 0);
    local.desc[3] = *(int *)(menu + 0x4FC);
    local.desc[4] = *(int *)(menu + 0x500);
    local.desc[16] = (int)(menu + 0x4B8);
    local.desc[9] = (int)&g_item_grid_page_desc_g;
    local.desc[1] = g_item_grid_page_desc_a;
    local.desc[2] = g_item_grid_page_desc_b;
    local.desc[0] = (int)g_menu_item_table_second;
    local.desc[17] = (int)(menu + 0x220);
    local.desc[10] = (int)(menu + 0x130);
    local.desc[12] = (int)(menu + 0x17C);
    local.desc[15] = (int)(menu + 0x278);
    local.desc[18] = *(int *)(menu + 0x470);
    local.desc[8] = (int)&g_item_grid_page_desc_f;
    local.desc[7] = (int)&g_item_grid_page_desc_e;
    local.desc[6] = (int)&g_item_grid_page_desc_d;
    local.desc[5] = (int)&g_item_grid_page_desc_c;
    local.desc[14] = 0;
    local.desc[11] = 0;
    local.desc[13] = 0;
    local.desc[20] = (int)&local.q;
    local.desc[22] = 1;
    DrawItemGrid(local.desc);
}
