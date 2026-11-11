/* func_US2_002CCAA0: v2.00's copy of func_002CBAE0 (src/game/002C7748-g8.c), the
 * menu-source dispatcher. The code is v1.01's with every address moved; it is the
 * release's own function because three of its callees changed in v2.00.
 * D_001AB910 is declared volatile as in func_002CBAE0 and func_002CBC58: retail
 * rereads it for every test and keeps one load whose value it discards (the empty
 * D_0025A058/D_00259B48 arm). Without the qualifier the body is 328 bytes, not 376. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_US2_2CCAA0;
typedef struct { char pad[0x1C4]; int flags; } InputState_US2_2CCAA0;
extern MenuState_US2_2CCAA0 D_001F2840;
extern InputState_US2_2CCAA0 D_00138180;
extern char D_00259018[];
extern char D_0025A738[];
extern char D_0025A498[];
extern char D_0025A190[];
extern char D_0025A058[];
extern char D_00259B48[];
extern volatile int D_001AB910 __attribute__((sda));
extern int (*D_00210ACC[])(int);
extern void func_0029CE38(void);
extern int func_US2_0029D0C8(int);
extern int func_US2_002D7BA0(int);
extern int func_US2_0029D138(int);

int func_US2_002CCAA0(void)
{
    int result = 0;

    if (D_001F2840.source == D_00259018) {
        if (D_00138180.flags & 0x910) {
            D_001F2840.state = D_001F2840.value == 4 ? 2 : 1;
            result = 1;
        } else if (D_00210ACC[0](D_00138180.flags) >= 0) {
            result = 1;
        }
    } else if (D_001F2840.source == D_0025A738) {
        func_0029CE38();
    } else if (D_001F2840.source == D_0025A498 && !D_001AB910) {
        func_US2_0029D0C8(0);
    } else if (D_001F2840.source == D_0025A190 && !D_001AB910) {
        if (func_US2_002D7BA0(0))
            D_001F2840.state = D_001F2840.value == 4 ? 2 : 1;
        func_US2_0029D138(D_00138180.flags);
        result = D_001F2840.destination != D_0025A498;
    } else if ((D_001F2840.source == D_0025A058 && !D_001AB910)
               || (D_001F2840.source == D_00259B48 && !D_001AB910)) {
        /* nothing: only the tests remain */
    }
    return result;
}
