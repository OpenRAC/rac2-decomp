#include "include_asm.h"

#include "common.h"
extern float g_hero_linked_object_values __attribute__((sda));
extern char g_hero_linked_object_params[];
extern char g_hero_velocity[];
extern int g_control_mode_option;
extern float g_cam_rotation_param;
extern int g_hero_locked_flag;
extern void FastVecAdd(char *, char *, char *);
extern float FastAddRotations(float, float);
extern void TranslateObjectAndView_pal(char *, float *);
extern void func_PAL_L00_00427960(char *);
extern void cam_follow_update_collision(char *);
extern void cam_follow_run_frame_pal(int);
extern void func_PAL_L00_004276D8(char *);

/* Builds the hero's 16-byte block from the hero record and the parameter block, stores the
   table's current blend weight in the global, refines the block's last float with the
   parameter block's own float (the hero's own float only when the global allows it) and
   hands the block to the object's own refresh, which then runs the five owner helpers.
   The retail reaches the blend table through $gp, so this body needs the small-data
   profile (-G8, from this file's name). */
void hero_refresh_linked_object_pal(char *object)
{
    char local[16];
    char *hero = g_hero_velocity;
    char *self = object;
    char *parameters = g_hero_linked_object_params;
    float value = (&g_hero_linked_object_values)[g_control_mode_option];
    float first;

    g_cam_rotation_param = value;
    FastVecAdd(local, hero, parameters);
    first = *(float *)(hero + 12);
    if (g_hero_locked_flag != 0) {
        first = 0.0f;
    }
    *(float *)(local + 12) = FastAddRotations(first, *(float *)(parameters + 12));
    TranslateObjectAndView_pal(self, (float *)local);
    func_PAL_L00_00427960(self);
    cam_follow_update_collision(self);
    cam_follow_run_frame_pal((int)self);
    func_PAL_L00_004276D8(self);
}
