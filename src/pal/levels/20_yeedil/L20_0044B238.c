#include "include_asm.h"

#include "common.h"
extern void moby_set_state(int, int, int);
extern void *jtbl_002B5960[];
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern unsigned char g_moby_group_flags[];
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern unsigned char g_moby_group_flags[];
extern int PlayMobySound(int, int, char *);

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed and plays a sound as it starts moving. (PAL) */
void switch_platform_update_pal(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5960[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    goto out;
c1:
    if ((g_moby_group_flags[((unsigned char *)moby)[0xB0] + *(int *)0x1A7A78 * 16] & 0x80) == 0) {
        goto end;
    }
    moby_set_state(moby, 2, -1);
    goto out;
c2:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(state + 0x14) = 0;
        PlayMobySound(0, 0, moby);
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (flag_is_third_pending_set(moby) == 0) {
        goto end;
    }
    moby_set_state(moby, 4, -1);
    goto out;
c4:
    if (flag_set_first_pending(moby) != 0) {
        PlayMobySound(0, 0, moby);
        *(int *)(state + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

