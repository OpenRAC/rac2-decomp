#include "include_asm.h"
#include "names.h"


typedef int s32;
extern void cam_swingshot_update(void);
extern void cam_aim_at_hero(s32);

/* prepares the shared object then hands it to the shared starter */
void shared_object_start_with_value_pal(s32 mode) {
    cam_swingshot_update();
    cam_aim_at_hero(mode);
}

