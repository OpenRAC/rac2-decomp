#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x1E0];
    short state;
    char pad2[0x14E];
    int a, b;
} HandlerState;
extern void moby_set_state(void *, int, int);
extern int hero_is_current_selected_id(void *);
extern int TryClaimNotice(int, int, int);
extern int D_00138324[];
extern int D_L19_001A8FB4 __attribute__((sda));
extern HandlerState g_hero_state;
extern char *D_L19_001B9A90[];
extern float D_L19_001B2420;
extern char *D_L19_001B2B0C;
extern float ApproachValue(float *, float, float);
extern void func_PAL_L00_00305110(int, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void snd_stop_voice(int);

void func_PAL_L19_004170C8(char *obj)
{
    char *data = *(char **)(obj + 0x68);
    char *target;
    unsigned timer;
    int waiting;
    if (*(u8 *)(obj + 0x20) == 0) {
        *(u8 *)(obj + 0x30) = 255;
        moby_set_state(obj, 1, -1);
        *(int *)(data + 0x18) = -1;
    }
    if (*(u8 *)(obj + 0x20) == 1) {
        if (hero_is_current_selected_id(obj)) {
            if (*(int *)(data + 8) == 0) TryClaimNotice(8, 0x134C, 1);
            else if (*(int *)(data + 8) == 1) TryClaimNotice(8, 0x134E, 1);
            else TryClaimNotice(8, 0x134B, 1);
            if ((D_00138324[0] & 0x10) && D_L19_001A8FB4 == 8 && g_hero_state.state == 0 && *(short *)(D_L19_001B9A90[0]+0x86) != 5) {
                *(u16 *)(obj + 0x96) = 0;
                g_hero_state.state = 2;
                moby_set_state(obj, 2, -1);
            }
        }
    }
    if (*(u8 *)(obj + 0x20) == 2) {
        ApproachValue(&D_L19_001B2420, 1.0f, 0.040000003f);
        timer = *(u16 *)(obj + 0x96);
        waiting = timer++ < 0x1B;
        *(u16 *)(obj + 0x96) = timer;
        if (!waiting) {
            target = D_L19_001B2B0C + (*(int *)(data + 4)<<7);
            g_hero_state.a = 0;
            g_hero_state.b = 0;
            func_PAL_L00_00305110(*(int *)data, *(int *)(data + 0x10));
            func_PAL_L00_002B9CD8(target + 0x30, target + 0x70, 0, 1);
            D_L19_001B2420 = 1.0f;
            moby_set_state(obj, 3, -1);
        } else g_hero_state.state = 2;
    }
    if (*(u8 *)(obj + 0x20) == 3) {
        ApproachValue(&D_L19_001B2420, 0.0f, 0.040000003f);
        if (D_L19_001B2420 <= 0.0f) {
            D_L19_001B2420 = 0.0f;
            moby_set_state(obj, 1, -1);
            if (*(int *)(data + 0x18) != -1) {
                snd_stop_voice(*(int *)(data + 0x18));
                *(int *)(data + 0x18) = -1;
            }
        }
    }
}
