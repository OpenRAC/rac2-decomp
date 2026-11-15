#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x, y, z, w;
} Vec5250;
typedef struct {
    u8 pad0[0x80];
    Vec5250 position;    
    u8 pad90[0xF0 - 0x90];
    Vec5250 vF0;         
    u8 pad100[0x120 - 0x100];
    Vec5250 v120;        
    u8 pad130[0x240 - 0x130];
    Vec5250 anchor;      
    u8 pad250[0x264 - 0x250];
    f32 reach;           
    u8 pad268[0x287 - 0x268];
    u8 easing;           
    u8 pad288[0x2D0 - 0x288];
    Vec5250 goal;        
    u8 pad2E0[0x318 - 0x2E0];
    f32 goalZ;           
    f32 x31C;            
    u8 pad320[0x344 - 0x320];
    f32 rate;            
    u8 pad348[0x34E - 0x348];
    s16 lock;            
    u8 pad350[0x22C3 - 0x350];
    u8 vectorMode;       
} Hero5250;
extern Hero5250 g_hero_state;
extern float math_fabs(float);
extern float cam_get_view_space_height(Vec5250 *);
extern float vec_distance_xy(Vec5250 *, Vec5250 *);
extern float vec_spring_to_target(Vec5250 *, Vec5250 *, float *, float, float, float);
extern float math_spring_float_to_goal(float *, float, float *, float, float, float);

/* Eases the hero's position toward its goal unless the lock at +0x34E is held: in vector
 * mode (+0x22C3) the vector at +0x80 follows the one at +0x2D0 while +0x31C is negative,
 * in scalar mode its z follows +0x318 while below it.  Within one step of the goal (the
 * difference below the step from +0xF0 plus 0.01) it snaps there instead when easing is
 * off (+0x287 clear) or the anchor at +0x240 is more than half of +0x264 away; with the
 * lock held or the goal passed, the easing rate at +0x344 is cleared. */
void func_PAL_L00_002B5178(void)
{
    Hero5250 *hero = &g_hero_state;
    float d;

    if (g_hero_state.vectorMode != 0) {
        if (g_hero_state.lock == 0 && g_hero_state.x31C < 0.0f) {
            d = math_fabs(g_hero_state.x31C);
            if (d < math_fabs(cam_get_view_space_height(&hero->vF0)) + 0.01f) {
                if (g_hero_state.easing == 0
                    || vec_distance_xy(&hero->anchor, &hero->position) > g_hero_state.reach * 0.5f) {
                    qcopy(&hero->position, &hero->goal);
                    return;
                }
                vec_spring_to_target(&hero->position, &hero->goal, &hero->rate,
                              0.072000004f, 0.3024f, 0.10000001f);
            } else {
                vec_spring_to_target(&g_hero_state.position, &g_hero_state.goal, &g_hero_state.rate,
                              0.072000004f, 0.3024f, 0.10000001f);
            }
        } else {
            g_hero_state.rate = 0.0f;
        }
    } else {
        if (g_hero_state.lock == 0 && g_hero_state.position.z < g_hero_state.goalZ) {
            d = math_fabs(g_hero_state.position.z - g_hero_state.goalZ);
            if (d < math_fabs(g_hero_state.vF0.z) + 0.01f) {
                if (g_hero_state.easing == 0
                    || vec_distance_xy(&hero->anchor, &hero->position) > g_hero_state.reach * 0.5f) {
                    g_hero_state.position.z = g_hero_state.goalZ;
                    return;
                }
                math_spring_float_to_goal(&hero->position.z, g_hero_state.goalZ, &hero->rate,
                              0.072000004f, 0.24480002f, 0.10000001f);
            } else {
                if (g_hero_state.v120.z < 0.0f) {
                    g_hero_state.position.z -= g_hero_state.v120.z;
                    if (g_hero_state.goalZ < g_hero_state.position.z)
                        g_hero_state.position.z = g_hero_state.goalZ;
                }
                math_spring_float_to_goal(&g_hero_state.position.z, g_hero_state.goalZ, &g_hero_state.rate,
                              0.072000004f, 0.24480002f, 0.10000001f);
            }
        } else {
            g_hero_state.rate = 0.0f;
        }
    }
}

