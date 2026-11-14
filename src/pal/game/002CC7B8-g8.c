#include "common.h"

/* func_PAL_002CC950: PAL copy of func_002CBAE0 (src/game/002C7748-g8.c).
 * Menu-source dispatcher. The C logic is identical to USA v1.01 and USA v2.00
 * (src/us2/game/002CCAA0-g8.c) with PAL symbol names. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_PAL_2CC950;
typedef struct { char pad[0x1C4]; int flags; } InputState_PAL_2CC950;
extern MenuState_PAL_2CC950 D_001F2840;
extern InputState_PAL_2CC950 D_001483C4;
extern char D_00269018[];
extern char D_0026A738[];
extern char D_0026A498[];
extern char D_0026A190[];
extern char D_0026A058[];
extern char D_00269B48[];
extern volatile int D_001AB910 __attribute__((sda));
extern int (*D_00210AFC[])(int);
extern void func_PAL_0029D7D0(void);
extern int func_PAL_0029CC28(int);
extern int func_PAL_002D7B68(int);
extern int func_PAL_0029CC98(int);

int func_PAL_002CC950(void)
{
    int result = 0;

    if (D_001F2840.source == D_00269018) {
        if (D_001483C4.flags & 0x910) {
            D_001F2840.state = D_001F2840.value == 4 ? 2 : 1;
            result = 1;
        } else if (D_00210AFC[0](D_001483C4.flags) >= 0) {
            result = 1;
        }
    } else if (D_001F2840.source == D_0026A738) {
        func_PAL_0029D7D0();
    } else if (D_001F2840.source == D_0026A498 && !D_001AB910) {
        func_PAL_0029CC28(0);
    } else if (D_001F2840.source == D_0026A190 && !D_001AB910) {
        if (func_PAL_002D7B68(0))
            D_001F2840.state = D_001F2840.value == 4 ? 2 : 1;
        func_PAL_0029CC98(D_001483C4.flags);
        result = D_001F2840.destination != D_0026A498;
    } else if ((D_001F2840.source == D_0026A058 && !D_001AB910)
               || (D_001F2840.source == D_00269B48 && !D_001AB910)) {
        /* nothing: only the tests remain */
    }
    return result;
}
