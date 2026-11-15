#include "include_asm.h"
#include "names.h"

extern void func_423000();
extern void func_423240();
extern void func_423358();
extern void func_423B30();
extern void func_423BD8();

void func_PAL_L14_004284F8(char *a0)
{
    if (*(unsigned char *)(a0 + 0x20) == 0) {
        func_423000(a0);
    } else {
        func_423240(a0);
        func_423358(a0);
        func_423B30(a0);
        func_423BD8(a0);
    }
}


extern int moby_step_at_own_position_factor(char *object, float factor);
extern int moby_step_at_own_position(char *object);
extern int moby_step_controller(char *object, char *bone, float factor);
extern int moby_turn_toward_target_and_step(char *object, char *bone, float factor);
extern void *jtbl_002AA360[];

/* Dispatches on the owner's animation step and plays the matching bone animation. */
void func_PAL_L14_004290A8(char *object)
{
    static void * volatile tab[] = { &&cA, &&cC };
    char *state;
    unsigned int sel;

    sel = *(unsigned char *)(object + 0x42) - 1;
    state = *(char **)(object + 0x68);
    if (sel < 19) {
        goto *jtbl_002AA360[sel];
    }
    goto end;
cA:
    if (*(short *)(state + 0x776) != 0) {
        moby_step_at_own_position_factor(object, *(float *)(state + 0x744));
    } else {
        moby_step_at_own_position(object);
    }
    goto out;
cC:
    if (*(short *)(state + 0x77A) != 0) {
        moby_step_controller(object, state + 0x700, *(float *)(state + 0x768));
    } else {
        moby_turn_toward_target_and_step(object, state + 0x700, *(float *)(state + 0x740));
    }
out:
end:
    return;
}

#include "common.h"
extern char D_L14_001B9500[];
extern char D_L14_001B9500[];
extern void func_PAL_002AC3C0(char *a0, void *a1);
extern void moby_update_eased_node(char *a0, void *a1, int a2, float a3, float a4);
extern float fast_vec_dist(char *a0, void *a1);
extern void moby_update_ground_check(char *a0);

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
void func_PAL_L14_00429150(char *a0)
{
    char *s1;
    float f20;
    float f21;

    s1 = *(char **)(a0 + 0x68);
    f21 = 0.0432f;
    f20 = 0.43200004f;
    func_PAL_002AC3C0(a0, s1 + 0x50);
    moby_update_eased_node(a0, s1 + 0x680, 1, f21, f20);
    moby_update_eased_node(a0, s1 + 0x600, 0, f21, f20);
    if (*(unsigned short *)(a0 + 0x96) <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = *(unsigned short *)(a0 + 0x96) + 1;
    *(unsigned short *)(s1 + 0x776) = 0;
    *(unsigned short *)(s1 + 0x778) = 0;
    *(unsigned short *)(s1 + 0x77A) = 0;
    if (*(unsigned char *)(a0 + 0x31) != 0) {
        if (fast_vec_dist(a0 + 0x10, D_L14_001B9500) < 24.0f) {
            moby_update_ground_check(a0);
            *(unsigned char *)(a0 + 0x6F) = 0x16;
        }
    }
}

