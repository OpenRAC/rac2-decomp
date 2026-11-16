#include "include_asm.h"
#include "names.h"

extern void object_init_derived_arrays(void *, void *, void *);
extern unsigned int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_c(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_b(void *, void *);
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void func_PAL_003388E8(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, unsigned int, unsigned int);
extern void object_set_second_pair(void *, unsigned int, unsigned int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern char g_menu_backdrop_desc[], g_menu_frame_desc[], g_menu_panel_desc[], g_menu_hud_label_desc_alt[], g_menu_icon_desc[], g_menu_bar_desc[];
extern char *g_resident_data_base[] __attribute__((sda));
int grid_menu_update_selection_pal(char *, unsigned int, void *);

/* Sets up a menu grid: its backdrop, frame, panel, label, icon and progress bar, then selects the first entry (PAL). */
void grid_menu_init_pal(char *self, void *parent)
{
    char *backdrop=self+0xF0, *panel, *label, *icon, *bar;
    int *allocation;
    object_init_derived_arrays(backdrop,g_menu_backdrop_desc,parent);
    *object_get_fourth_field(backdrop)=0x60241700;
    object_set_helper_result(backdrop,g_resident_data_base[0]+0x8710,0x29);
    *(void **)(self+0x1C4)=parent;
    if(parent) {
    allocation=ui_return_second_arg(16,pool_alloc_cell(parent));
    *(int **)(self+0x1C0)=allocation;
    allocation[1]=0; allocation[2]=0; allocation[3]=0; allocation[0]=0;
    }
    *(int *)(self+0x210)=1;
    **(float **)(self+0x1C0)=0.0f;
    (*(float **)(self+0x1C0))[1]=0.0f;
    panel=self+0x4C; label=self+0x98; icon=self+0x184; bar=self+0x13C;
    object_init_derived_arrays(self,g_menu_frame_desc,parent);
    object_init_derived_arrays(panel,g_menu_panel_desc,parent);
    hud_init_widget_defaults_pal(label,g_menu_hud_label_desc_alt,parent);
    *object_get_fourth_field(self)=0x55F0C070;
    *object_get_fourth_field(panel)=0x70FFFEED;
    object_set_helper_result(self,g_resident_data_base[0]+0x8710,0x5D);
    object_set_helper_result(panel,g_resident_data_base[0]+0x8710,0x5E);
    object_set_flag_value(panel,0);
    *(int *)(self+0x214)=0;
    *(int *)(self+0x218)=0;
    object_init_derived_c(icon,g_menu_icon_desc,parent);
    *object_get_fourth_field(icon)=0x60F0F0B0;
    object_set_second_float4(icon,32.0f,32.0f,0.0f,0.0f);
    *object_get_fourth_field(label)=0x80F0F0F0;
    self[0x1D0]=0;
    hud_set_widget_field_b(label,self+0x1D0);
    *(float *)(self+0x1C8)=0.0f;
    *(float *)(self+0x1CC)=0.0f;
    *(int *)(self+0x224)=0;
    object_init_derived_b(bar,32,0,g_menu_bar_desc,parent);
    widget_set_pos_y(bar,5);
    func_PAL_003388E8(bar,100);
    meter_set_value(bar,0);
    object_set_first_pair(bar,0x6049C1FF,0x60001EFF);
    object_set_second_pair(bar,0x50F0C070,0x50F0C070);
    text_set_alignment(bar,0x80000000);
    widget_store_field(bar,0);
    *(int *)(self+0x21C)=4;
    *(int *)(self+0x220)=6;
    grid_menu_update_selection_pal(self,0,0);
}
