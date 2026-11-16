#include "include_asm.h"

#include "common.h"
extern void part_draw_spinning_billboard_pair(void *obj, float f, void *p, void *q);
typedef struct __attribute__((packed)) { unsigned char b[8]; } Blob8;
extern Blob8 g_object_effect_blob __attribute__((nosda));

void object_run_effect_if_active_pal(char *arg)
{
    int *o = *(int **)(arg + 104);
    if (o[9] != 0) {
        if (o[11] == 0) {
            part_draw_spinning_billboard_pair(o, 1.0f, (char *)o + 16, 0);
        } else {
            Blob8 tmp = g_object_effect_blob;
            part_draw_spinning_billboard_pair(o, 1.0f, (char *)o + 16, &tmp);
        }
    }
}

