#include "include_asm.h"

#include "common.h"
extern char D_00189EA0[];
extern char *D_L17_001FE880[];
extern float D_L17_001B0344 __attribute__((sda));
extern int func_002ACBC8(void *, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
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

void func_PAL_L17_003CA030(char *self) {
    SelectMoby *moby = (SelectMoby *)self;
    SelectData *data = moby->data;
    char *target;
    int i;
    for (i = 0; i < 5; i++) {
        if ((data->triggers[i] != -1 || data->current == i) &&
            (func_002ACBC8(D_00189EA0, data->triggers[i]) || data->current == i)) {
            moby->animation = *(int *)(moby->model + 0x10);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->animation = *(int *)(moby->model + 0x10);
            if (data->targets[i] != -1) {
                target = D_L17_001FE880[data->targets[i]];
                qcopy(self + 0x10, target + 0x10);
                *(float *)(self + 0xF8) = func_00283248(*(float *)(target + 0x20) - *(float *)(self + 0x10), *(float *)(target + 0x24) - *(float *)(self + 0x14));
            } else if (data->fallback[i] != -1) {
                if (func_00282E80(self + 0x10, D_L17_001FE880[data->fallback[i]] + 0x10) > 2.0f) {
                    target = D_L17_001FE880[data->fallback[i]];
                    qcopy(self + 0x10, target + 0x10);
                    *(float *)(self + 0xF8) = func_00283248(*(float *)(target + 0x20) - *(float *)(self + 0x10), *(float *)(target + 0x24) - *(float *)(self + 0x14));
                }
            }
            moby->choice = i;
            moby->state = 2;
            moby->timer = 0x80;
            data->cooldown = D_L17_001B0344 * 0.020000001f;
            data->active = 1;
            data->current = -1;
            return;
        }
    }
}
