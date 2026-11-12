#include "include_asm.h"
#include "common.h"

/* func_US2_L02_003C58E0 (USA v2.00, levels 2, 3, 4, 9, 12, 17, 20 and 30): the v2.00 copy of
   func_L02_003C43F0. It uses v2.00's text ids, and its two header labels move up one pixel
   when the display mode is 1. */

extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002FC560(int, unsigned long);
extern char *func_00288FB8(int);
extern void func_0027FBD8(int, int, u64, char *, int);
extern char *D_L02_001A904C;
extern float D_L02_001B3E04;
extern int D_L02_001B3E00;

static __inline__ int menu_coord(float scale, float value, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L02_001B3E00 == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int header_y(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;

    if (D_L02_001B3E00 == active)
        return (int)(scaled + -1.0f);
    return (int)scaled;
}

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_US2_L02_003C58E0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, on, entry;
    float one, zero, half, k, s;

    entry = 0x8710;
    k = 203.0f;
    half = 0.5f;
    on = 1;
    id = func_00336D50(D_L02_001A904C + entry, 0x70);
    y = menu_coord(D_L02_001B3E04, k, half, on);
    one = 1.0f;
    zero = 0.0f;
    s = (float)y;
    func_00300A00(id, 0x60442D00, 258.0f, s, one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x6F), 0x60442D00, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x71), 0x55F0C070, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    id = func_00336D50(D_L02_001A904C + entry, 0x72);
    y = menu_coord(D_L02_001B3E04, k, half, on);
    s = one;
    func_00300A00(id, 0x55F0C070, 258.0f, (float)y, s, s, zero);
    func_002FC560(0x47, 0x5360BUL);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2DF2);
        func_0027FBD8(254, header_y(23.0f, D_L02_001B3E04, half, on), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2DF1);
        func_0027FBD8(262, header_y(23.0f, D_L02_001B3E04, half, on), 0x88FFFFFF, text, -1);
    }
    text = func_00288FB8(0x2DF0);
    func_0027FBD8(254, label_y(text, 373.0f, D_L02_001B3E04, 0.5f, 1), 0x88FFFFFF, text, -1);
}
