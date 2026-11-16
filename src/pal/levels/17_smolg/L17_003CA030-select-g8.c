#include "include_asm.h"

#include "common.h"
extern char g_hero_position[];
extern char *g_path_l17_table[];
extern float g_platform_move_speed __attribute__((sda));
extern int IsPointInCuboid(void *, int);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
typedef struct {
    char pad[0x90];
    float cooldown;
    int active;
    char pad98[0xC];
    int current;
    char gap[8];
    int triggers[5], targets[5], fallback[5];
} SelectData;
typedef struct {
    char pad[0x20];
    unsigned char state;
    char pad21[3];
    char *model;
    char pad28[0xA];
    short timer;
    unsigned short flags;
    char pad36[0x32];
    SelectData *data;
    char pad6C[0x2C];
    int animation;
    char pad9C[0x20];
    unsigned char choice;
} SelectMoby;

/* Checks the five entry slots of a ride platform. When one is selected, the platform moves to
   that slot's start point, turns to face along it and switches to its moving state (PAL: 50 Hz
   timings). */
void ride_platform_select_entry_pal(char *self) {
    SelectMoby *moby = (SelectMoby *)self;
    SelectData *data = moby->data;
    char *target;
    int i;
    for (i = 0; i < 5; i++) {
        if ((data->triggers[i] != -1 || data->current == i) &&
            (IsPointInCuboid(g_hero_position, data->triggers[i]) || data->current == i)) {
            moby->animation = *(int *)(moby->model + 0x10);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->animation = *(int *)(moby->model + 0x10);
            if (data->targets[i] != -1) {
                target = g_path_l17_table[data->targets[i]];
                qcopy(self + 0x10, target + 0x10);
                *(float *)(self + 0xF8) = mat_fast_helper_a(*(float *)(target + 0x20) - *(float *)(self + 0x10), *(float *)(target + 0x24) - *(float *)(self + 0x14));
            } else if (data->fallback[i] != -1) {
                if (vec_distance_xy(self + 0x10, g_path_l17_table[data->fallback[i]] + 0x10) > 2.0f) {
                    target = g_path_l17_table[data->fallback[i]];
                    qcopy(self + 0x10, target + 0x10);
                    *(float *)(self + 0xF8) = mat_fast_helper_a(*(float *)(target + 0x20) - *(float *)(self + 0x10), *(float *)(target + 0x24) - *(float *)(self + 0x14));
                }
            }
            moby->choice = i;
            moby->state = 2;
            moby->timer = 0x80;
            data->cooldown = g_platform_move_speed * 0.020000001f;
            data->active = 1;
            data->current = -1;
            return;
        }
    }
}
