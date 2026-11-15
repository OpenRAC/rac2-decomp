#include "common.h"
/* func_US2_L00_002FD818, the USA v2.00 copy of func_L00_002FCBE8: the same C, where the 4000 objects' call also tests D_001A79F0[0] != 0x33. */
typedef struct {
    char pad0[0x30]; int state, timer; char pad38[12]; short count; char pad46[10]; char *out; char pad54[0x138]; struct StateObject { char pad[0x95]; unsigned char alpha; } *objects[1];
} Context;
extern int g_current_map_index[] __attribute__((sda));
extern float D_L00_001B24B0[4] __attribute__((sda));
extern Context D_L00_001BCAC0;
extern void vec_clear_128(void *);
extern void func_US2_002E72D8(void *);
extern void part_init_effect_table(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void anim_start_startup_animations(void);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void gfx_draw_object_multi_pass(void *);

void func_US2_L00_002FD818(void) {
    int i;
    anim_start_startup_animations();
    for(i=0;i<D_L00_001BCAC0.count;i++) {
            int offset=i*4+0x18C;
            char *obj=*(char **)((char *)&D_L00_001BCAC0+offset);
            if (obj && *(short *)(obj+0xAA)==0xE29) *(unsigned short *)(obj+0x34)|=0x800;
            if (*(short *)(obj+0xAA)==0xD54) func_US2_002E72D8(obj);
            if (obj && *(short *)(obj+0xAA)==4000 && g_current_map_index[0]!=0x33 && *(char **)(obj+0x68)) {
                math_store_angle_update_result(obj,*(char **)(obj+0x68)+12,0x80AAAAD2,0x80396464,0.061086535f);
            }
    }
    if(g_current_map_index[0]==0) {
        if(D_L00_001BCAC0.state==0) {
            if(D_L00_001BCAC0.timer<2) part_init_effect_table(*(char **)((char *)&D_L00_001BCAC0+0x70)+0x24000);
            vec_clear_128(D_L00_001B24B0);
            D_L00_001B24B0[0]=-3.0f;
            { struct StateObject *object=D_L00_001BCAC0.objects[2];
              object->alpha=255;
              gfx_add_draw_callback_first(gfx_draw_object_multi_pass,object); }
        } else if(D_L00_001BCAC0.state==2) {
            if(D_L00_001BCAC0.timer<2) part_init_effect_table(*(char **)((char *)&D_L00_001BCAC0+0x70)+0x24000);
            vec_clear_128(D_L00_001B24B0);
            { struct StateObject *object=D_L00_001BCAC0.objects[1];
              object->alpha=255;
              gfx_add_draw_callback_first(gfx_draw_object_multi_pass,object); }
        }
    }
}
