#include "include_asm.h"

#include "common.h"
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void surface_grid_build_control(void *);
extern float math_random_float_range(float, float);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern int flag_set_first_pending(unsigned char *);
extern int math_fast_float_d(int *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void surface_grid_update_wave_tables(void *);
extern void surface_grid_update_heights(void *);
extern void surface_grid_update_us2(void *);
extern void surface_grid_spawn_effect(void *);
extern void surface_grid_draw(void *);
extern void gfx_register_early_draw_callback(void (*)(void *), void *);
extern float g_surface_grid_noise_table[];

/* Runs the surface grid object's state machine: ramps the wave height up, holds it, lets it fall, then updates and draws the grid (v2.00 copy). */
void moby_update_rise_hold_fall_us2(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        surface_grid_build_control(object);
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x8C)=FIELD(int,work,0x84);FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            object[0x30]=255;
            for(i=0;i<64;++i) {
                g_surface_grid_noise_table[i * 8 + 2]=math_random_float_range(0.5f,2);
                g_surface_grid_noise_table[i * 8 + 3]=math_random_float_range(0.002f,0.006f);
            }
        }
        moby_set_state(object,1,-1);return;
    case 1:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,2,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(flag_set_first_pending(object)){FIELD(int,work,0x20)=FIELD(int,work,12);FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,4,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(flag_set_first_pending(object)){FIELD(int,work,4)=0;FIELD(int,work,0x20)=FIELD(int,work,16);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))surface_grid_update_wave_tables(object);
    surface_grid_update_heights(object);surface_grid_update_us2(object);surface_grid_spawn_effect(object);
    gfx_register_early_draw_callback(surface_grid_draw,object);
}
