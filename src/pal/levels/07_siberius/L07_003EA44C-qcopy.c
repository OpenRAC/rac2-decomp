#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern int math_fast_float_d(char *);
extern void value_set_and_smooth_pal(char *, char *, int, int, float);
extern int g_cutscene_l07_active_flag;
extern void RideMobyBelow(char *);
extern void group_sync_counter(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts_pal(char *, char *, int, void *, float);

/* Clear the two resource slots, step the state counter, refresh the object's
   transform and hand the entity to the shared launcher. */
void entity_finish_update_pal(char *moby)
{
    char *vars;
    char *src_pos;
    char *dst_pos;
    TI128 delta;
    unsigned short frame_count;
    float angle;

    vars = *(char **)(moby + 0x68);
    math_fast_float_d(vars + 0x344);
    math_fast_float_d(vars + 0x348);
    frame_count = *(unsigned short *)(moby + 0x96);
    if (frame_count <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = frame_count + 1;
    group_sync_counter(moby, vars + 0x340);
    src_pos = moby + 0x10;
    dst_pos = vars + 0x2E0;
    FastVecSub(&delta, src_pos, dst_pos);
    *(TI128 *)dst_pos = *(TI128 *)src_pos;
    if (g_cutscene_l07_active_flag != 0)
        RideMobyBelow(moby);
    if (*(unsigned char *)(moby + 0x95) == 2) {
        angle = FastAddRotations(*(float *)(vars + 0x2DC), 0.25132746f);
        *(float *)(vars + 0x2DC) = angle;
        enemy_attach_turn_child_parts_pal(moby, vars + 0x330, 1, &delta, angle);
    } else {
        angle = FastAddRotations(*(float *)(vars + 0x2DC), 0.013962637f);
        *(float *)(vars + 0x2DC) = angle;
        enemy_attach_turn_child_parts_pal(moby, vars + 0x330, 0, &delta, angle);
    }
    value_set_and_smooth_pal(moby, vars + 0x230, 7, 1, 2.5f);
}
