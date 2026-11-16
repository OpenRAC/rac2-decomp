#include "include_asm.h"


#include "common.h"
extern void moby_set_state(int, int, int);
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern unsigned char g_moby_group_flags[];
extern void *jtbl_002B5980[];
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern unsigned char g_moby_group_flags[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed, like the one above but silent (USA v2.00). */
void switch_platform_quiet_update_us2(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *vars;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    vars = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5980[sel];
c0:
    *(float *)(vars + 0x10) = *(float *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    goto out;
c1:
    if ((g_moby_group_flags[((unsigned char *)moby)[0xB0] + *(int *)0x1A79F8 * 16] & 0x80) == 0) {
        goto end;
    }
    moby_set_state(moby, 2, -1);
    goto out;
c2:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(vars + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, vars + 0x14,
                  *(float *)(vars + 0x10) - *(float *)(vars + 0x0),
                  *(float *)(vars + 0x8), *(float *)(vars + 0x8),
                  *(float *)(vars + 0xC));
    goto out;
c3:
    if (flag_is_third_pending_set(moby) == 0) {
        goto end;
    }
    moby_set_state(moby, 4, -1);
    goto out;
c4:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(vars + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, vars + 0x14, *(float *)(vars + 0x10),
                  *(float *)(vars + 0x8), *(float *)(vars + 0x8),
                  *(float *)(vars + 0xC));
    goto out;
end:
out:
    return;
}

