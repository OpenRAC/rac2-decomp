/* 7 November 2026: exact in USA v2.00 (every place of func_US2_002CCAA0 matches, as below, compiled as a
 * -g8.c unit with `-O2 -G8 -ffunction-sections`), but only with the qualifier `volatile` on D_001AB910, which matched C may not contain
 * (AGENTS.md, "No `volatile` in matched C"). Without it the function is shorter than retail by the
 * rereads or the store sequence the qualifier forces. Reopen with a non-volatile form that keeps retail's
 * reads and stores.
 */
/* func_US2_002CCAA0, the USA v2.00 copy of func_002CBAE0: the same C, where rename func_0029C290 becomes func_US2_0029D0C8; rename func_002D6F38 becomes func_US2_002D7BA0; rename func_0029C300 becomes func_US2_0029D138. */
/* The three handler slots and the string table are read through $gp, so this
 * function needs the -G8 profile of the sibling file. */
extern void (*D_001AA420)(int) __attribute__((sda));
extern void (*D_001AA428)(int) __attribute__((sda));
extern void (*D_001AA42C)(int) __attribute__((sda));
/*
 * The game's global state: the mode 0 case copies one of its fields into another.
 * The struct's own address is the one the retail code forms (lui/addiu) and the two
 * fields are the offsets it uses from it.
 */
typedef struct {
    char reserved_000[0x1248];
    int value_1248;
    char reserved_124C[0x107C];
    int value_22C8;
} GameState_189E20;

extern GameState_189E20 D_00189E20;

/* The menu entries the seven cases hand to func_002D5E70, in the small data area. */
/* Mode dispatcher: two handler slots are called, one mode names a string. */
/* Dispatches on the current menu source. D_00138180's flags word is reached
 * absolutely (the object is large); D_001AB910 is small data and volatile:
 * retail rereads it for every test, including one whose value it discards. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_2CBAE0;
typedef struct { char pad[0x1C4]; int flags; } InputState_2CBAE0;
extern MenuState_2CBAE0 D_001F2840;
extern InputState_2CBAE0 D_00138180;
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

/* Once the menu state has counted ten frames: the fourteen children of its object
 * get their callbacks, each changed choice is saved (0x77 for none), the value is
 * copied to D_001A72D4, texture group 0 is uploaded and groups 2, 3 and 4 (the
 * last two only when sized) are undone before the next state is set. */
typedef struct {
    char pad[0x14];
    int a[8];
    int b[16];
    int c[8];
} GroupTable_2CA5D0;

extern GroupTable_2CA5D0 *D_001B1888;
