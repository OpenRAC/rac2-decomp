/* functional: high. The near-miss draft (744/752 bytes; register allocation and the scheduling of the constant arguments differ) with level 02's callees mapped through functions.tsv (0x457AB0 func_00336D50, 0x387CE0 func_00300A00, 0x382CB8 func_002FC560, 0x2F8570 func_00288FB8, 0x2ED068 func_0027FBD8) and func_0027FBD8 taking its style as the 64-bit word retail passes (0x88FFFFFF zero-extended), as func_002859C8 declares func_0027FAA8; the port's host routine reads its low 32 bits. Same calls, arguments and order as retail. */
/* func_L02_003C43F0 (shared, 8 places): draws a menu panel: four registry sprites (ids 0x70, 0x6F, 0x71,
 * 0x72 of the registry at *0x1A904C + 0x8710) at x 258 and y round(scale*203) with colours 0x60442D00 /
 * 0x55F0C070, sets GS register 0x47 to 0x5360B, then a status text by the object's state byte (+0x20):
 * 7 gives string 0x2F5C at x 254, 5 and 8 give none, others 0x2F5B at x 262 (y round(scale*23)), and
 * always string 0x2F5A at x 254, y round(scale*373). scale is the float at 0x1B3E04.
 * From the near-miss draft nonmatching/levels/func_L02_003C43F0.c. */
#include "common.h"

extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002FC560(int, unsigned long);
extern char *func_00288FB8(int);
extern int func_0027FBD8(int, int, unsigned long, unsigned int, int);
extern char *D_L02_001A904C;
extern float D_L02_001B3E04;

void func_L02_003C43F0(char *obj)
{
    char *text;
    int state;

    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x70), 0x60442D00, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x6F), 0x60442D00, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x71), 0x55F0C070, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x72), 0x55F0C070, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_002FC560(0x47, 0x5360B);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2F5C);
        func_0027FBD8(254, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFF, (unsigned int)text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2F5B);
        func_0027FBD8(262, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFF, (unsigned int)text, -1);
    }
    text = func_00288FB8(0x2F5A);
    func_0027FBD8(254, (int)(D_L02_001B3E04 * 373.0f + 0.5f), 0x88FFFFFF, (unsigned int)text, -1);
}
