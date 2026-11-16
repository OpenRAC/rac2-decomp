#include "include_asm.h"
#include "names.h"

typedef struct { float x,y,z,w; } Point;
typedef struct {
    unsigned char pad0[0x80];
    Point position;
    unsigned char pad90[8];
    float heading;
    unsigned char pad9c[0x2294-0x9c];
    int mode;
    unsigned char pad2298[4];
    int activity;
} PlayerView;
extern unsigned char g_hero_state[];
extern int g_prompt_angle_a __attribute__((sda));
extern int g_prompt_angle_b __attribute__((sda));
extern int g_prompt_hidden_flag;
extern unsigned int g_pad_held_flags __attribute__((nosda));
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int TryClaimNotice(int, int, int);
extern int request_begin_slot(int, int, int, int, unsigned char *);

/* Shows the interact prompt for this object: when the hero is close, facing it and free to act, it claims the notice, and a press of the button starts the request. */
void interact_prompt_update_pal(unsigned char *moby)
{
    unsigned int in_range;
    int claimed;
    float *vars = *(float **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        in_range = 1;
        claimed = 0;
        math_store_angle_update_result((char *)moby, vars,
                          g_prompt_angle_a, g_prompt_angle_b, 0.052359886f);
        if (((PlayerView *)g_hero_state)->activity && ((PlayerView *)g_hero_state)->mode != 3) {
            if (((PlayerView *)g_hero_state)->activity != 1) in_range = 0;
        }
        if (vec_distance_xy(moby + 0x10, &((PlayerView *)g_hero_state)->position) > 3.0f ||
            math_fabs(((PlayerView *)g_hero_state)->position.z - *(float *)(moby + 0x18)) > 0.7f)
            in_range = 0;
        if (FastDiffRots(((PlayerView *)g_hero_state)->heading,
              mat_fast_helper_a(*(float *)(moby + 0x10) - ((PlayerView *)g_hero_state)->position.x,
                            *(float *)(moby + 0x14) - ((PlayerView *)g_hero_state)->position.y)) > 1.5707965f)
            in_range = 0;
        if (((PlayerView *)g_hero_state)->mode == 0x1c || ((PlayerView *)g_hero_state)->mode == 0x31) in_range = 0;
        if (in_range) claimed = TryClaimNotice(1, 0x12EB, 1) != 0;
        if ((g_pad_held_flags & 0x10) && claimed) {
            request_begin_slot(5, 1, (int)moby, 0, 0);
            moby[0x20] = 2;
        }
        break;
    case 2:
        if (!g_prompt_hidden_flag) moby[0x20] = 1;
        break;
    }
}
