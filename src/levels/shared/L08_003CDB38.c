#include "common.h"

extern void func_002A0F48(u8 *p);

/* Places the object at the position and rotation stored in its private data. */
void moby_place_at_stored_transform(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    qcopy(moby + 0x10, vars);
    qcopy(moby + 0xF0, vars + 0x10);
    func_002A0F48(moby);
}
