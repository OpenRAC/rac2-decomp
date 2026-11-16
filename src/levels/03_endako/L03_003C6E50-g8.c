#include "common.h"
extern char *g_moby_record_base;
typedef struct { char pad[0x30]; float pos[4]; char pad2[0x30]; float rot[4]; } Record;
extern Record *g_linked_effect_records;
extern int g_remote_view_index __attribute__((sda));
extern float g_remote_view_angle __attribute__((sda)), g_remote_view_fov __attribute__((sda));
typedef struct { char pad[0x3d4]; float f; char pad2[0x10]; char b0,b1; } AimState;
extern AimState g_hero_l03_state_alias;
typedef struct { int index; int indices[3]; int handles[8]; int current; } SelectState;
extern int func_321988(void *, int);
extern void moby_copy_position_and_height(void *, void *);
extern void func_2EEF78(void *);
extern float func_2EF190(void *, void *);
extern float func_2EF670(float, float);
extern float func_2F0000(float, float);
/* Picks which camera anchor to use and outputs its position and a rotation that looks at the target. */
void camera_select_remote_view(char *obj, float *pos, float *rot)
{
    float target[4];
    int i;
    SelectState *state = *(SelectState **)(obj+0x68);
    char *source = g_moby_record_base + state->index * 0x100;

    if (state->current == -1 || !func_321988(source+0x10, state->handles[state->current])) {
        for(i=0;i<3;i++) {
            if(i == state->current) continue;
            if(state->handles[i] == -1) continue;
            if(func_321988(source+0x10, state->handles[i])) {
                state->current=i;
                break;
            }
        }
    }
    g_remote_view_index = state->current;
    { Record *base = g_linked_effect_records; int index = state->indices[state->current];
    qcopy(pos,base[index].pos);
    qcopy(rot,base[index].rot); }
    moby_copy_position_and_height(source,target);
    func_2EEF78(rot);
    rot[1]=func_2F0000(-func_2EF670(func_2EF190(pos,target),target[2]-pos[2]),g_remote_view_angle*0.017453294f);
    rot[2]=func_2EF670(target[0]-pos[0],target[1]-pos[1]);
    g_hero_l03_state_alias.f=g_remote_view_fov;
    g_hero_l03_state_alias.b1=1;
    g_hero_l03_state_alias.b0=0;
}
