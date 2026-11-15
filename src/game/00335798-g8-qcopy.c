#include "names.h"
/* func_00335798 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
typedef int TI128 __attribute__((mode(TI)));

extern void *func_00270280(int);
extern void func_00270598(void *, void *, int);
extern int D_001B1504;
extern char D_001B5340[];

/* Sets up an effect entry on the object: stores the user data, builds four vectors and starts it. */
void func_00335798(TI128 *first, TI128 *second, void *userData)
{
    TI128 vecs[4];
    char *obj = (char *)FindRecordByHandleId(0x1B);
    char *table = (char *)D_001B1504;
    short idx = *(short *)(obj + 0x84);
    char *entry = *(char **)(table + idx * 32 + 0x1C);
    char *colorTable;
    int one = 1;

    *(unsigned char *)(entry + 0x1D) = one;
    *(void **)(entry + 0x20) = userData;
    vecs[0] = *first;
    vecs[1] = *second;
    colorTable = (char *)gCameraState_001B5340;
    vecs[2] = *(TI128 *)colorTable;
    vecs[3] = *(TI128 *)(colorTable + 0x10);
    SwitchActiveCamera(obj, &vecs[3], one);
}
