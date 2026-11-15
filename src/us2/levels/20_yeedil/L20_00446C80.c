#include "include_asm.h"

#include "common.h"
extern void moby_set_state(int, int, int);
extern void *jtbl_002B5960[];
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern void math_step_value_toward_target(char *, char *, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern unsigned char D_0019B2E8[];
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern void math_step_value_toward_target(char *, char *, float, float, float, float);
extern unsigned char D_0019B2E8[];
extern int PlayMobySound(int, int, char *);

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
void func_US2_L20_00446C80(char *arg0) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(arg0 + 0x20);
    state = *(char **)(arg0 + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5960[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(arg0 + 0x10);
    moby_set_state(arg0, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)arg0)[0xB0] + *(int *)0x1A79F8 * 16] & 0x80) == 0) {
        goto end;
    }
    moby_set_state(arg0, 2, -1);
    goto out;
c2:
    if (flag_set_first_pending(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
        PlayMobySound(0, 0, arg0);
    }
    math_step_value_toward_target(arg0 + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (flag_is_third_pending_set(arg0) == 0) {
        goto end;
    }
    moby_set_state(arg0, 4, -1);
    goto out;
c4:
    if (flag_set_first_pending(arg0) != 0) {
        PlayMobySound(0, 0, arg0);
        *(int *)(state + 0x14) = 0;
    }
    math_step_value_toward_target(arg0 + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

