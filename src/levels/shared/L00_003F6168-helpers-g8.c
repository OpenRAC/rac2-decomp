#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *level_get_slot_body(int,int);
extern char *level_get_slot_header(int,int);
extern int FastDecTimer(char *);
extern void vec_scale_to_length(char *,char *,float);
extern void FastVecAdd(char *,char *,char *);
extern float g_vaporizer_trail_age_step __attribute__((sda));
extern float g_vaporizer_trail_scale_step __attribute__((sda));
extern float g_vaporizer_trail_step_speed __attribute__((sda));
#define RECORD (base + *(short *)(state + 0x18) * 0x60)
/* Moves the bolt's trail record along with the bolt each frame and counts its life down.
   Returns 0 when the trail has ended, otherwise 1. */
int vaporizer_bolt_update_trail_sample(char *object)
{
    TI128 step;
    int index;
    char *state = *(char **)(object + 0x68);
    char *base = level_get_slot_body(MOBY_CLASS_VAPORIZER,*(short *)(state + 0x1a));
    base += *(int *)level_get_slot_header(MOBY_CLASS_VAPORIZER,*(short *)(state + 0x1a));
    if (*(short *)(RECORD + 0x50) == 0) return 0;
    if (FastDecTimer(RECORD + 0x52) != 0) {
        *(short *)(RECORD + 0x50) = 0;
        return 0;
    }
    index = *(short *)(state + 0x18);
    qcopy(base + index*0x60 + 0x20,object + 0x10);
    *(float *)(base + index*0x60 + 0x54) += g_vaporizer_trail_age_step;
    if (*(float *)(RECORD + 0x54) >= 4.0f) *(float *)(RECORD + 0x54) -= 4.0f;
    *(float *)(RECORD + 0x58) += g_vaporizer_trail_scale_step;
    if (*(float *)(RECORD + 0x58) >= 4.0f) *(float *)(RECORD + 0x58) -= 4.0f;
    vec_scale_to_length((char *)&step,state,g_vaporizer_trail_step_speed * 0.016666668f);
    FastVecAdd(RECORD,RECORD,(char *)&step);
    FastVecAdd(RECORD+0x10,RECORD+0x10,(char *)&step);
    return 1;
}
#undef RECORD
