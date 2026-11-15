#include "include_asm.h"
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_spark_puff(char *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(s32 *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern unsigned char D_00139574;
/* Partial camera prefix; the measured 0xE0 stride is explicit at use. */
typedef struct { char reserved00[0x70]; float radius; } Camera;
typedef struct { char pad[0x18]; char *object; int count; Quad position; char gap[16]; char normal[16]; } Hit;
extern u8 D_L15_00276FF0[];
extern Hit D_L15_001BFC00;
extern void *g_hero_moby;
extern void *D_L15_001AC810 MACRO_ADDR;



/* Moves a projectile each frame and bounces it off surfaces, counting its hits. */
void projectile_bounce_count_update(unsigned char *object)
{
    float delta[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    char previous[16] __attribute__((aligned(16)));
    char temporary[16] __attribute__((aligned(16)));
    char collision[48] __attribute__((aligned(16)));
    char *position = (char *)object + 0x10;
    char *state;

    *(Quad *)delta = 0;
    state = *(char **)(object + 0x68);
    *(Quad *)normal = 0;
    delta[2] = 0.03333333507180214f;
    normal[2] = 1.0f;
    qcopy(previous, position);
    FastVecAdd(position, position, state);
    cam_compute_view_direction(position, temporary, 0);
    FastVecScale(temporary, temporary, 0.0003055555862374604f);
    part_spawn_spark_puff((char *)object);
    *(void **)(collision + 0x10) = object;
    *(int *)(collision + 0x14) = 0x830000;
    if (*(int *)(state + 0x18) < 0x122)
        *(int *)(collision + 0x14) = 0x830001;
    *(float *)(collision + 0x1c) = ((Camera *)((char *)D_L15_00276FF0 + D_00139574 * 0xe0))->radius;
    *(int *)(collision + 0x20) = 1;
    qcopy(collision, state);
    vec_fast_normalize_helper(collision, collision, 1.0f);
    collision[0x18] = 2;
    *(float *)(collision + 0xc) = 5627.9248046875f;
    *(short *)(collision + 0x1a) = *(unsigned short *)(object + 0xaa);
    *(float *)(collision + 8) = 1.0f;
    collision[0x19] = 1;
    ++*(int *)(state + 0x14);
    if (CollLine(previous, position, 0x10, object, collision)) {
        if (D_L15_001BFC00.object) {
            if ((D_L15_001BFC00.object == g_hero_moby || *(short *)(D_L15_001BFC00.object + 0xaa) == MOBY_CLASS_BOMB_GLOVE) &&
                *(int *)(state + 0x18) >= 0x122)
                goto finished;
            if (*(void **)(D_L15_001BFC00.object + 0x64) == D_L15_001AC810 && *(short *)(D_L15_001BFC00.object + 0xaa) != 0x336 /* moby class 822 */)
                goto finished;
            *(unsigned char *)(object + 0xbc) = 1;
            qcopy(object + 0x10, &D_L15_001BFC00.position);
            vec_fast_normalize(delta, state, D_L15_001BFC00.normal);
            vec_scale_to_length(delta, delta, 0.03333333507180214f);
            vec_scale_to_length(normal, D_L15_001BFC00.normal, 1.0f);
        } else if (D_L15_001BFC00.count > 0) {
            *(unsigned char *)(object + 0xbc) = 1;
            qcopy(position, &D_L15_001BFC00.position);
            vec_fast_normalize(delta, state, D_L15_001BFC00.normal);
            vec_scale_to_length(delta, delta, 0.03333333507180214f);
            vec_scale_to_length(normal, D_L15_001BFC00.normal, 1.0f);
        }
    } else if (math_fast_float_d((s32 *)(state + 0x18))) {
        *(unsigned char *)(object + 0xbc) = 1;
        FastVecAdd(delta, delta, state);
    }
finished:
    if ((unsigned char)object[0xbc]) {
        table_clear_entry_flag(*(int *)(state + 0x1c));
        if (*(int *)(state + 0x14) < 20)
            part_spawn_big_explosion(object, delta, normal);
        else
            part_l00_spawn_impact_burst(object, delta, normal);
    }
}
