#include "include_asm.h"
#include "names.h"

extern void object_init_derived_arrays(void *, void *, void *);
extern unsigned int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void func_PAL_00338688(void *, void *, void *);
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
extern char D_001ADFA0[], D_001ADFC0[], D_001ADFC8[], D_001AE030[], D_001ADFD8[], D_001AE040[];
extern char *D_001A8CFC[] __attribute__((sda));
int func_PAL_003430B0(char *, unsigned int, void *);

void func_PAL_00342DE8(char *self, void *parent)
{
    char *a=self+0xF0, *b, *c, *d, *e;
    int *v;
    object_init_derived_arrays(a,D_001ADFA0,parent);
    *object_get_fourth_field(a)=0x60241700;
    object_set_helper_result(a,D_001A8CFC[0]+0x8710,0x29);
    *(void **)(self+0x1C4)=parent;
    if(parent) {
    v=ui_return_second_arg(16,pool_alloc_cell(parent));
    *(int **)(self+0x1C0)=v;
    v[1]=0; v[2]=0; v[3]=0; v[0]=0;
    }
    *(int *)(self+0x210)=1;
    **(float **)(self+0x1C0)=0.0f;
    (*(float **)(self+0x1C0))[1]=0.0f;
    b=self+0x4C; c=self+0x98; d=self+0x184; e=self+0x13C;
    object_init_derived_arrays(self,D_001ADFC0,parent);
    object_init_derived_arrays(b,D_001ADFC8,parent);
    func_PAL_00338688(c,D_001AE030,parent);
    *object_get_fourth_field(self)=0x55F0C070;
    *object_get_fourth_field(b)=0x70FFFEED;
    object_set_helper_result(self,D_001A8CFC[0]+0x8710,0x5D);
    object_set_helper_result(b,D_001A8CFC[0]+0x8710,0x5E);
    object_set_flag_value(b,0);
    *(int *)(self+0x214)=0;
    *(int *)(self+0x218)=0;
    object_init_derived_c(d,D_001ADFD8,parent);
    *object_get_fourth_field(d)=0x60F0F0B0;
    object_set_second_float4(d,32.0f,32.0f,0.0f,0.0f);
    *object_get_fourth_field(c)=0x80F0F0F0;
    self[0x1D0]=0;
    hud_set_widget_field_b(c,self+0x1D0);
    *(float *)(self+0x1C8)=0.0f;
    *(float *)(self+0x1CC)=0.0f;
    *(int *)(self+0x224)=0;
    object_init_derived_b(e,32,0,D_001AE040,parent);
    widget_set_pos_y(e,5);
    func_PAL_003388E8(e,100);
    meter_set_value(e,0);
    object_set_first_pair(e,0x6049C1FF,0x60001EFF);
    object_set_second_pair(e,0x50F0C070,0x50F0C070);
    text_set_alignment(e,0x80000000);
    widget_store_field(e,0);
    *(int *)(self+0x21C)=4;
    *(int *)(self+0x220)=6;
    func_PAL_003430B0(self,0,0);
}
