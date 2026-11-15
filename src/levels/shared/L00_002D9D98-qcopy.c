#include "names.h"
/* func_L00_002D9D98: selects the default camera and copies its position and target. */
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char pad0[0x140];
    union { Quad q; float f[4]; } position;
    char pad150[0x40];
    char *active;
    char pad194[0xc];
    float target[3];
    char pad1ac[0xe4];
    short state;
    char pad292[0x172];
    int flags;
} CameraState;
extern CameraState D_L00_001B8C80;
extern char D_L00_001BB1B0[];
extern float g_hero_position[3];
extern char *moby_find_record_by_handle_id(int);
extern void cam_update_follow_hero(void);
extern void moby_call_class_update(char *);
extern void cam_copy_working_data(void);
extern void cam_l00_init_blend_values(void);

void cam_reset_default(void)
{
    CameraState *camera = &D_L00_001B8C80;
    if (camera->active) {
        *(short *)(camera->active+0x8e)=0;
        camera->active[0x7d]=0;
        *(short *)(camera->active+0x7e)=0;
    }
    camera->active=moby_find_record_by_handle_id(0);
    *(short *)(camera->active+0x8e)=1;
    *(char **)(camera->active+0x70)=D_L00_001BB1B0;
    camera->active[0x7d]=0;
    camera->state=0;
    cam_update_follow_hero();
    camera->flags=0;
    moby_call_class_update(camera->active);
    cam_copy_working_data();
    { char *active=camera->active;
      float *position=camera->position.f;
      *(Quad *)position=*(Quad *)(active+0x30);
      { float *out=(float *)(active+0x64);
        out[0]=position[0]; out[1]=position[1]; out[2]=position[2];
      }
      { float *target=camera->target; float *origin=g_hero_position;
        target[0]=origin[0]; target[1]=origin[1]; target[2]=origin[2];
      }
    }
    cam_l00_init_blend_values();
}
