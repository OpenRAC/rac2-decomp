#include "names.h"
/* Constructs a menu grid: initializes its sprites, text, anchor and four-by-six selection. */
extern void object_init_derived_arrays(void *, void *, void *);
extern unsigned int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void hud_init_widget_defaults(void *, void *, void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_c(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_b(void *, void *);
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, unsigned int, unsigned int);
extern void object_set_second_pair(void *, unsigned int, unsigned int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern char D_001ADFA0[], D_001ADFC0[], D_001ADFC8[], D_001AE030[], D_001ADFD8[], D_001AE040[];
extern char *D_001A8CFC[] __attribute__((sda));
int grid_menu_update_selection(char *, unsigned int, void *);
void grid_menu_init(char *self, void *parent)
{
    char *widgetE0=self+0xE0, *widget4C, *widget98, *iconWidget, *barWidget;
    int *allocation;
    object_init_derived_arrays(widgetE0,D_001ADFA0,parent);
    *object_get_fourth_field(widgetE0)=0x60241700;
    object_set_helper_result(widgetE0,D_001A8CFC[0]+0x8710,0x29);
    *(void **)(self+0x1B4)=parent;
    if(parent) {
    allocation=ui_return_second_arg(16,pool_alloc_cell(parent));
    *(int **)(self+0x1B0)=allocation;
    allocation[1]=0; allocation[2]=0; allocation[3]=0; allocation[0]=0;
    }
    *(int *)(self+0x200)=1;
    **(float **)(self+0x1B0)=0.0f;
    (*(float **)(self+0x1B0))[1]=0.0f;
    widget4C=self+0x4C; widget98=self+0x98; iconWidget=self+0x174; barWidget=self+0x12C;
    object_init_derived_arrays(self,D_001ADFC0,parent);
    object_init_derived_arrays(widget4C,D_001ADFC8,parent);
    hud_init_widget_defaults(widget98,D_001AE030,parent);
    *object_get_fourth_field(self)=0x55F0C070;
    *object_get_fourth_field(widget4C)=0x70FFFEED;
    object_set_helper_result(self,D_001A8CFC[0]+0x8710,0x5D);
    object_set_helper_result(widget4C,D_001A8CFC[0]+0x8710,0x5E);
    object_set_flag_value(widget4C,0);
    *(int *)(self+0x204)=0;
    *(int *)(self+0x208)=0;
    object_init_derived_c(iconWidget,D_001ADFD8,parent);
    *object_get_fourth_field(iconWidget)=0x60F0F0B0;
    object_set_second_float4(iconWidget,32.0f,32.0f,0.0f,0.0f);
    *object_get_fourth_field(widget98)=0x80F0F0F0;
    self[0x1C0]=0;
    hud_set_widget_field_b(widget98,self+0x1C0);
    *(float *)(self+0x1B8)=0.0f;
    *(float *)(self+0x1BC)=0.0f;
    *(int *)(self+0x214)=0;
    object_init_derived_b(barWidget,32,0,D_001AE040,parent);
    widget_set_pos_y(barWidget,5);
    meter_set_max(barWidget,100);
    meter_set_value(barWidget,0);
    object_set_first_pair(barWidget,0x6049C1FF,0x60001EFF);
    object_set_second_pair(barWidget,0x50F0C070,0x50F0C070);
    text_set_alignment(barWidget,0x80000000);
    widget_store_field(barWidget,0);
    *(int *)(self+0x20C)=4;
    *(int *)(self+0x210)=6;
    grid_menu_update_selection(self,0,0);
}
