#include "names.h"
/* func_PAL_L02_00391A00, the PAL copy of func_L00_00385370: the same C, where the timers in fields
   0x1C, 0x84, 0xC and 0x10 take the 50 Hz scale. */
#include "include_asm.h"
#include "common.h"
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern float math_random_float_range(float,float);
extern int math_fast_float_d(int *);
extern void surface_grid_build_control(void *);
extern void func_PAL_00304D90(void *);
extern void surface_grid_update_heights(void *);
extern void func_PAL_00303F38(void *);
extern void func_PAL_00305348(void *);
extern void surface_grid_draw(void *);
extern void gfx_add_draw_callback_second(void (*)(void *),void *);
extern void moby_set_state(unsigned char *,unsigned char,int);
extern int flag_set_first_pending(unsigned char *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
typedef struct { float x,y,a,b; float pad[4]; } Spark;
extern Spark g_rise_fall_sparks[];
void func_PAL_L02_00391A00(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        FIELD(int,work,0x1C)=((s32)FIELD(int,work,0x1C)*5+2)/6;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        surface_grid_build_control(object);
        FIELD(int,work,0x8C)=((s32)FIELD(int,work,0x84)*5+2)/6;
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            int alpha=255;
            object[0x30]=alpha;
            for(i=0;i<64;++i) {
                g_rise_fall_sparks[i].a=math_random_float_range(0.5f,2);
                g_rise_fall_sparks[i].b=math_random_float_range(0.002f,0.006f);
            }
        }
        moby_set_state(object,1,-1);return;
    case 1:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,2,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(flag_set_first_pending(object)){FIELD(int,work,0x20)=((s32)FIELD(int,work,12)*5+2)/6;FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,4,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(flag_set_first_pending(object)){FIELD(int,work,0x20)=((s32)FIELD(int,work,16)*5+2)/6;FIELD(int,work,4)=0;}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))func_PAL_00304D90(object);
    surface_grid_update_heights(object);func_PAL_00303F38(object);func_PAL_00305348(object);
    gfx_add_draw_callback_second(surface_grid_draw,object);
}
