#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *level_get_slot_body(int,int);
extern char *level_get_slot_header(int,int);
extern int FastDecTimer(char *);
extern void vec_scale_to_length(char *,char *,float);
extern void FastVecAdd(char *,char *,char *);
extern float D_L00_001B0988 __attribute__((sda));
extern float D_L00_001B09C0 __attribute__((sda));
extern float D_L00_001B099C __attribute__((sda));
#define RECORD (base + *(short *)(state + 0x18) * 0x60)
/* Moves the bolt's trail record along with the bolt each frame and counts its life down.
   Returns 0 when the trail has ended, otherwise 1. */
int vaporizer_bolt_update_trail_sample(char *object)
{
    TI128 step;
    int index;
    char *state = *(char **)(object + 0x68);
    char *base = level_get_slot_body(0xc04 /* Vaporizer */,*(short *)(state + 0x1a));
    base += *(int *)level_get_slot_header(0xc04 /* Vaporizer */,*(short *)(state + 0x1a));
    if (*(short *)(RECORD + 0x50) == 0) return 0;
    if (FastDecTimer(RECORD + 0x52) != 0) {
        *(short *)(RECORD + 0x50) = 0;
        return 0;
    }
    index = *(short *)(state + 0x18);
    qcopy(base + index*0x60 + 0x20,object + 0x10);
    *(float *)(base + index*0x60 + 0x54) += D_L00_001B0988;
    if (*(float *)(RECORD + 0x54) >= 4.0f) *(float *)(RECORD + 0x54) -= 4.0f;
    *(float *)(RECORD + 0x58) += D_L00_001B09C0;
    if (*(float *)(RECORD + 0x58) >= 4.0f) *(float *)(RECORD + 0x58) -= 4.0f;
    vec_scale_to_length((char *)&step,state,D_L00_001B099C * 0.016666668f);
    FastVecAdd(RECORD,RECORD,(char *)&step);
    FastVecAdd(RECORD+0x10,RECORD+0x10,(char *)&step);
    return 1;
}
#undef RECORD
