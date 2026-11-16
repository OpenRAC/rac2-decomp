#include "names.h"
/* func_00349D58: initialises the HUD widget's text, sprites and fade keys. A unit of its own for
 * -frac2-keep-float-pun-source (config/cflags.txt): a colour read twice keeps its word in $v0, set
 * after the previous call, with one mtc1 into a saved FPR; a colour read once folds to li.s
 * (docs/build/compiler-notes.md). WriteBits is the one spelling for every colour. Same-file C calls and
 * prototypes differ from 00345358.c, so it cannot live there. */
static __inline__ float WriteBits(unsigned int bits)
{
    float f;
    *(unsigned int *)&f = bits;
    return f;
}

extern void *pool_alloc_cell(void *);
extern void *ui_return_second_arg(int, void *);
extern void object_init_derived_arrays(void *,void *,void *);
extern void object_init_derived_b(void *,int,int,void *,void *);
extern void object_set_helper_result(void *,void *,int);
extern void object_set_first_pair(void *,unsigned int,unsigned int);
extern void object_set_second_pair(void *,unsigned int,unsigned int);
extern void text_set_alignment(void *,unsigned int);
extern void meter_set_max(void *,int);
extern void widget_set_pos_y(void *,int);
extern int *object_get_fourth_field(void *);
extern float *object_get_second_field(void *);
extern void fade_init(void *,void *);
extern void effect_set_field_84(void *,int);
extern void fade_set_field_2c(void *,void *);
extern void fade_set_field_80(void *,void *);
extern void fade_set_speed(void *,float);
extern void effect_set_field_20(void *,int);
extern void fade_set_parameter_row(void *,int,float,float,float,float,float);
extern void anim_set_key_range(void *,int,float,float);
extern void fade_start_direction(void *,int);
extern int fade_swap_field_28(void *,int);
extern char g_hud_fade_widget_data_a[],g_hud_fade_widget_data_b[],g_hud_fade_widget_data_c[],g_hud_fade_label_data[];
extern float g_hud_scale __attribute__((sda));
extern int g_hud_mode __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern int g_player_stats __attribute__((sda));

/* Sets up one HUD gauge: its texts, sprites and the fade animations that show, hide and pulse them. */
void hud_fade_widget_init(char *object,char *data,void *context)
{
    int *zeroBlock;
    void *parent;
    char *label;
    char *anim0,*anim1,*anim2,*anim3,*anim4;
    float scaledSize;
    *(void **)(object+0x13c)=context;
    if(context) {
        zeroBlock=ui_return_second_arg(16,pool_alloc_cell(context));
        *(int **)(object+8)=zeroBlock;
        parent=*(void **)(object+0x13c);
        zeroBlock[1]=0;zeroBlock[2]=0;zeroBlock[3]=0;zeroBlock[0]=0;
        zeroBlock=ui_return_second_arg(16,pool_alloc_cell(parent));
        *(int **)(object+0x1c8)=zeroBlock;
        zeroBlock[1]=0;zeroBlock[2]=0;zeroBlock[3]=0;zeroBlock[0]=0;
    }
    object_init_derived_arrays(object+0x10,g_hud_fade_widget_data_a,context);
    object_init_derived_arrays((object+0x5c),g_hud_fade_widget_data_b,context);
    object_init_derived_arrays((object+0xa8),g_hud_fade_widget_data_c,context);
    label=object+0xf4;
    object_init_derived_b(label,146,0,g_hud_fade_label_data,context);
    object_set_helper_result((object+0x5c),data+0x8710,17);
    object_set_helper_result((object+0xa8),data+0x8710,18);
    object_set_first_pair(label,0x8049c1ff,0x80001eff);
    object_set_second_pair(label,0x50f0c070,0x50f0c070);
    text_set_alignment(label,0x60442d00);
    meter_set_max(label,100);
    scaledSize=3.0f*g_hud_scale+0.5f;
    widget_set_pos_y(label,g_hud_mode==1?(int)(scaledSize+1.0f):(int)scaledSize);
    *((int *)object_get_fourth_field((object+0x5c)))=0x60442d00;
    *((int *)object_get_fourth_field((object+0xa8)))=0x55f0c070;
    anim0=object+0x140;
    fade_init(anim0,context);
    effect_set_field_84(anim0,2);
    fade_set_field_2c(anim0,*(void **)(object+0x1c8));
    fade_set_field_80(anim0,object+0x1cc);
    fade_set_speed(anim0,0.005f);
    effect_set_field_20(anim0,2);
    /* 50.0f: a literal or its own local; a local shared with the colours swaps $f20/$f21. */
    fade_set_parameter_row(anim0,0,0.0f,WriteBits(0x80f0c070),50.0f,0.0f,0.0f);
    fade_set_parameter_row(anim0,1,1.0f,WriteBits(0x80f0f0f0),50.0f,0.0f,0.0f);
    anim_set_key_range(anim0,0,0.0f,0.0f);
    fade_start_direction(anim0,1);
    anim1=object+0x1d4;
    fade_init(anim1,context);
    effect_set_field_84(anim1,3);
    fade_set_parameter_row(anim1,0,0.0f,WriteBits(0x442d00),0.0f,0.0f,0.0f);
    fade_set_parameter_row(anim1,1,0.3f,WriteBits(0x60442d00),0.0f,0.0f,0.0f);
    fade_set_parameter_row(anim1,2,1.0f,WriteBits(0x60442d00),0.0f,0.0f,0.0f);
    anim_set_key_range(anim1,1,0.0f,2.0f);
    fade_set_field_2c(anim1,((int *)object_get_fourth_field((object+0x5c))));
    effect_set_field_20(anim1,0);
    fade_set_field_80(anim1,object+0x1cc);
    fade_start_direction(anim1,-1);
    fade_set_speed(anim1,g_is_pal_video?0.14f:0.11666667461395264f);
    anim2=object+0x25c;
    fade_init(anim2,context);
    effect_set_field_84(anim2,3);
    fade_set_parameter_row(anim2,0,0.0f,0.0f,0.0f,0.0f,0.0f);
    fade_set_parameter_row(anim2,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    fade_set_parameter_row(anim2,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    fade_set_field_2c(anim2,((void *)object_get_second_field((object+0x5c))));
    effect_set_field_20(anim2,0);
    fade_set_field_80(anim2,object+0x1d0);
    fade_start_direction(anim2,-1);
    fade_set_speed(anim2,g_is_pal_video?0.14f:0.11666667461395264f);
    fade_swap_field_28(anim2,0);
    anim3=object+0x2e4;
    fade_init(anim3,context);
    effect_set_field_84(anim3,3);
    fade_set_parameter_row(anim3,0,0.0f,WriteBits(0xf0c070),0.0f,0.0f,0.0f);
    fade_set_parameter_row(anim3,1,0.3f,WriteBits(0x55f0c070),0.0f,0.0f,0.0f);
    fade_set_parameter_row(anim3,2,1.0f,WriteBits(0x55f0c070),0.0f,0.0f,0.0f);
    anim_set_key_range(anim3,1,0.0f,3.0f);
    fade_set_field_2c(anim3,((int *)object_get_fourth_field((object+0xa8))));
    effect_set_field_20(anim3,0);
    fade_set_field_80(anim3,object+0x1cc);
    fade_start_direction(anim3,-1);
    fade_set_speed(anim3,g_is_pal_video?0.14f:0.11666667461395264f);
    anim4=object+0x36c;
    fade_init(anim4,context);
    effect_set_field_84(anim4,3);
    fade_set_parameter_row(anim4,0,0.0f,1.2000000476837158f,1.2000000476837158f,0.0f,0.0f);
    fade_set_parameter_row(anim4,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    fade_set_parameter_row(anim4,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    fade_set_field_2c(anim4,((void *)object_get_second_field((object+0xa8))));
    effect_set_field_20(anim4,0);
    fade_set_field_80(anim4,object+0x1d0);
    fade_start_direction(anim4,-1);
    fade_set_speed(anim4,g_is_pal_video?0.14f:0.11666667461395264f);
    *(int *)(object+0x3f4)=0;
    *(int *)(object+0x400)=-1;
    *(int *)(object+0x3f8)=0;
    /* +4 before +0xC: swapped, sw $zero,0xC issues before the D_001A7A00 load, retail's after. */
    *(int *)(object+4)=g_player_stats;
    *(int *)(object+0xc)=0;
}
