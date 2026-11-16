#include "include_asm.h"

#include "common.h"
extern void part_draw_spinning_billboard_pair(void *obj, float f, void *p, void *q);
typedef struct __attribute__((packed)) { unsigned char b[8]; } Blob8;
extern Blob8 g_object_effect_blob __attribute__((nosda));

/* Passes the object to a shared effect routine when it has been set up, with an extra value when a second field is set. */
void object_run_effect_if_active_pal(char *moby)
{
    int *vars = *(int **)(moby + 104);
    if (vars[9] != 0) {
        if (vars[11] == 0) {
            part_draw_spinning_billboard_pair(vars, 1.0f, (char *)vars + 16, 0);
        } else {
            Blob8 blob_copy = g_object_effect_blob;
            part_draw_spinning_billboard_pair(vars, 1.0f, (char *)vars + 16, &blob_copy);
        }
    }
}

