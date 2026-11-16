#include "include_asm.h"





#include "common.h"
extern void moby_set_byte_on_group(int, int);
extern int math_fast_float_d(char *);
extern void anim_start_blended_pal(char *, int, int, int);
extern void *D_L06_002E1F00[];

/* func_L06_00420080 is defined in L06_00420080.c. */


/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
void five_state_mechanism_update_pal(char *obj)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&c3, &&c4};
    char *moby = obj;
    char *state;
    unsigned int state_index;

    state_index = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (state_index < 5)
        goto *D_L06_002E1F00[state_index];
    goto done;
c0:
    *(unsigned char *)(moby + 0x20) = 1;
    *(int *)state = 0x4E2;
    goto done;
c1:
    if (*(unsigned char *)(moby + 0xBC) == 0)
        goto done;
    *(unsigned char *)(moby + 0x20) = 2;
    if (*(unsigned char *)(moby + 0x43) != 1)
        anim_start_blended_pal(moby, 1, 0, 0);
    *(int *)(moby + 0x98) = 0;
    goto done;
c2:
    if ((*(unsigned char *)(moby + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(moby + 0x20) = 3;
    if (*(unsigned char *)(moby + 0x43) == 2)
        goto done;
    anim_start_blended_pal(moby, 2, 0, 0);
    goto done;
c3:
    if (math_fast_float_d(state) == 0)
        goto done;
    *(unsigned char *)(moby + 0x20) = 4;
    if (*(unsigned char *)(moby + 0x43) == 3)
        goto done;
    anim_start_blended_pal(moby, 3, 0, 0);
    goto done;
c4:
    if ((*(unsigned char *)(moby + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(moby + 0x20) = 1;
    if (*(unsigned char *)(moby + 0x43) == 0)
        goto tail;
    anim_start_blended_pal(moby, 0, 0, 0);
tail:
    *(int *)(moby + 0x98) = *(int *)(*(int *)(moby + 0x24) + 0x10);
    *(int *)state = 0x4E2;
    moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
    goto done;
done:
    return;
}



extern int func_36C158();
extern int func_36C1B0(float);

/* Starts or stops the actor's glow effect. */
int actor_set_glow_effect_pal(char *obj, int unused, int glow_mode)
{
    char *state = *(char **)(obj + 0x68);
    int result;

    if (glow_mode == 0) {
        result = func_36C158();
    } else {
        result = func_36C1B0(*(float *)(state + 0x31C));
    }
    return result;
}

