#include "names.h"
/* func_00335798 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
typedef int TI128 __attribute__((mode(TI)));

extern void *moby_find_record_by_handle_id(int);
extern void cam_switch_active(void *, void *, int);
extern int g_camera_definition_table;
extern char g_camera_eye_state[];

/* Sets up an effect entry on the object: stores the user data, builds four vectors and starts it. */
void part_setup_object_effect_entry(TI128 *first, TI128 *second, void *userData)
{
    TI128 vecs[4];
    char *obj = (char *)moby_find_record_by_handle_id(0x1B);
    char *table = (char *)g_camera_definition_table;
    short idx = *(short *)(obj + 0x84);
    char *entry = *(char **)(table + idx * 32 + 0x1C);
    char *colorTable;
    int one = 1;

    *(unsigned char *)(entry + 0x1D) = one;
    *(void **)(entry + 0x20) = userData;
    vecs[0] = *first;
    vecs[1] = *second;
    colorTable = (char *)g_camera_eye_state;
    vecs[2] = *(TI128 *)colorTable;
    vecs[3] = *(TI128 *)(colorTable + 0x10);
    cam_switch_active(obj, &vecs[3], one);
}
