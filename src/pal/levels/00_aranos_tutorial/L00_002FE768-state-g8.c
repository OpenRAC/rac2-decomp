/* func_PAL_L00_002FE768, the PAL copy of func_L00_002FCBE8: the same C, where the angle becomes
   0.07330384f (6/5 of USA's) and the 4000 moby is skipped when D_001A79F0[0] is 0x33. */
#include "common.h"
typedef struct {
    char pad0[0x30]; int state, timer; char pad38[12]; short count; char pad46[10]; char *out; char pad54[0x138]; struct StateObject { char pad[0x95]; unsigned char alpha; } *objects[1];
} Context;
extern int g_current_map_index[] __attribute__((sda));
extern float g_scene_vector[4] __attribute__((sda));
extern Context g_tutorial_probe_context;
extern void vec_clear_128(void *);
extern void update_equipment_pieces_pal(void *);
extern void part_init_effect_table(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void anim_start_startup_animations(void);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void gfx_draw_object_multi_pass(void *);

/* Sets up the scene objects each frame and draws the highlighted screen object for the current step (PAL angle, map 0x33 skips the TV screens). */
void tutorial_scene_objects_update_pal(void) {
    int i;
    anim_start_startup_animations();
    for(i=0;i<g_tutorial_probe_context.count;i++) {
            char *context_base=(char *)&g_tutorial_probe_context;
            char *moby=*(char **)(context_base+0x18C+i*4);
            if (moby && *(short *)(moby+0xAA)==0xE29) *(unsigned short *)(moby+0x34)|=0x800;
            if (*(short *)(moby+0xAA)==0xD54) update_equipment_pieces_pal(moby);
            if (moby && *(short *)(moby+0xAA)== MOBY_CLASS_TV_SCREENS && g_current_map_index[0]!=0x33 && *(char **)(moby+0x68)) {
                math_store_angle_update_result(moby,*(char **)(moby+0x68)+12,0x80AAAAD2,0x80396464,0.07330384f);
            }
    }
    if(g_current_map_index[0]==0) {
        if(g_tutorial_probe_context.state==0) {
            if(g_tutorial_probe_context.timer<2) part_init_effect_table(*(char **)((char *)&g_tutorial_probe_context+0x70)+0x24000);
            vec_clear_128(g_scene_vector);
            g_scene_vector[0]=-3.0f;
            { struct StateObject *object=g_tutorial_probe_context.objects[2];
              object->alpha=255;
              gfx_add_draw_callback_first(gfx_draw_object_multi_pass,object); }
        } else if(g_tutorial_probe_context.state==2) {
            if(g_tutorial_probe_context.timer<2) part_init_effect_table(*(char **)((char *)&g_tutorial_probe_context+0x70)+0x24000);
            vec_clear_128(g_scene_vector);
            { struct StateObject *object=g_tutorial_probe_context.objects[1];
              object->alpha=255;
              gfx_add_draw_callback_first(gfx_draw_object_multi_pass,object); }
        }
    }
}
