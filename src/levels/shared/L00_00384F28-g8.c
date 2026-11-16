#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"
extern unsigned char *g_moby_array_last[] __attribute__((sda));
extern unsigned char *g_goal_object_list[] __attribute__((sda));
extern unsigned char *g_moby_array_end_sentinel[] __attribute__((sda));
extern void goal_controller_update(void *);


/* func_L00_00383B90 passes its object in a0; this handler does not read it. */
/* Runs the update function of every live object of the same kind as the first one, plus every hover bomb. */
void sheep_board_update_same_class(void *self)
{
    unsigned char *object=g_moby_array_end_sentinel[0];
    short classId=*(short *)(g_goal_object_list[0]+0xAA);
    while ((unsigned int)object < (unsigned int)g_moby_array_last[0]) {
        if (object && *(short *)(object+0xAA)==classId && object[0x20]!=0xFE && object[0x20]!=0xFD && object!=g_goal_object_list[0])
            (*(void (**)(void *))(object+0x64))(object);
        else if (object && *(short *)(object+0xAA)==MOBY_CLASS_HOVERBOMB_PROJECTILE && object[0x20]!=0xFE && object[0x20]!=0xFD && *(void (**)(void *))(object+0x64)==goal_controller_update)
            (*(void (**)(void *))(object+0x64))(object);
        object+=0x100;
    }
}
