/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections.
 * Emitted/retail size: 500/468 bytes.
 * us: 0 of 27 places match.
 * pal: ABSENT.
 * us2: ABSENT.
 * No strict linked build was run for this draft.
 * The current 64-bit identity-return contract introduces eight narrowing instructions across table lookups. Removing explicit casts ties. Reopen after qualifying the original caller domain and return width; do not silently substitute a 32-bit prototype.
 */
#include "common.h"
extern unsigned long func_L00_002D3FB0(unsigned long);
extern int func_L00_002D3FB8(int, int);
/* Three consumed integer inputs, forwarded through func_0029CC50. */
extern void func_L00_00326200(int, int, int);
extern void func_00282C88(void *);
extern int func_00282C30(int);
extern int func_002E5CF8(int, int, void *);
extern int D_00139688[];
extern unsigned char D_00139568[];
extern char D_L00_00262570[];
extern int D_L00_001B19C8[] __attribute__((sda));
extern int D_L00_001B2ADC[] __attribute__((sda));

int func_L00_003D1B50(char *object)
{
    char *state = *(char **)(object + 0x68);
    int previous, change;
    int text;
    float before;
    if ((unsigned char)object[0x20] == 2)
        return 0;
    previous = D_00139688[func_L00_002D3FB0(*(int *)(state + 0x68))];
    before = (float)func_L00_002D3FB8(*(int *)(state + 0x68), *(int *)(state + 0x60));
    if (previous >= D_00139688[func_L00_002D3FB0(*(int *)(state + 0x68))])
        return 0;
    change = D_00139688[func_L00_002D3FB0(*(int *)(state + 0x68))] - previous;
    if (change == 1)
        text = *(short *)(D_L00_00262570 + D_00139568[func_L00_002D3FB0(*(int *)(state + 0x68))] * 0xe0 + 0x3a);
    else
        text = *(short *)(D_L00_00262570 + D_00139568[func_L00_002D3FB0(*(int *)(state + 0x68))] * 0xe0 + 0x38);
    func_L00_00326200(text, change, -1);
    if (before < (float)*(int *)(state + 0x60)) {
        object[0x20] = 2;
        *(float *)(object + 0x2c) *= 1.2f;
        func_00282C88(state);
        *(float *)(state + 0x74) = 0.13333334f;
        if (func_00282C30(D_L00_001B19C8[0] - D_L00_001B2ADC[0]) >= 11) {
            func_002E5CF8(0, 0, object);
            D_L00_001B2ADC[0] = D_L00_001B19C8[0];
        }
    }
    return 1;
}
