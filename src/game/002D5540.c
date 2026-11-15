#include "include_asm.h"
#include "names.h"

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void func_0027C540(long);

extern void func_0027C660(void);

void func_0027C540(long);

void func_0027C660(void);

/* 
 * Function: func_002D2EE0
 * 
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void func_0027C540(long arg0);

/* External functions declared with exact aliases from task.externals */
extern void func_0027C540(long param_1);

extern void func_0029CED8(void);

/* Draws a menu page between the start and end of screen drawing. */
long long func_002D5540(void)
{
    SetupGifPaging(0);
    func_0029CED8();
    DoGifPaging();
    return 0;
}

/* func_002D5570 is matched in 002D5540-g8.c (-G8 small data). */

/* Does nothing and returns zero. */
int func_002D55D8(void) {
    return 0;
}

/* func_002D55E0 uses small data in 002D5540-g8.c. */

extern void func_0029CB20(void);

/* Draws a second kind of menu page between the start and end of screen drawing. */
int func_002D5718(void) {
    SetupGifPaging(0);
    func_0029CB20();
    DoGifPaging();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00341CD8(char *, int);
extern void func_00341EB0(char *, char *);
extern char D_00261540[];

/* Sets up the text of a menu page when the menu data is loaded. */
int func_002D5748(void)
{
    if (D_001A8CFC[0] != 0) {
        SetMenuFlagAtOffset8(D_001A8CFC[0] + 0x3E430, 1);
        SetListMenuRecords_00341EB0(D_001A8CFC[0] + 0x3E430, D_00261540);
    }
    return 0;
}

extern int D_00138180[];
extern char D_001F2840[];
extern int func_0029CA70(int);
extern int func_003423B0(unsigned char *);
extern void func_002D5E98(int);

/* Reads the buttons on a menu page: cancel goes back, other keys close it, and confirm sends the chosen entry to the menu request handler. */
int func_002D57A0(void)
{
    int result = 0;
    int *state = gPadState;
    int flags = state[0x1C4 / 4];
    if (flags & 0x10) {
        char *root = gPauseMenuState;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029CA70(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_001A8CFC[0]) {
            char *entry = (char *)GetSelectedListRecordAddress((unsigned char *)(D_001A8CFC[0] + 0x3E1D8));
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            StartMenuAction((int)&request);
        }
    }
    return result;
}


extern void func_0029CAB0(void);

/* Draws a third kind of menu page between the start and end of screen drawing. */
int func_002D5870(void) {
    SetupGifPaging(0);
    func_0029CAB0();
    DoGifPaging();
    return 0;
}

extern void func_003423A8(char *, int);
extern void func_00342380(char *, char *);
extern char D_00261590[];

/* Sets up the text of another menu page when the menu data is loaded. */
int func_002D58A0(void)
{
    if (D_001A8CFC[0] != 0) {
        SetListMenuEnabled(D_001A8CFC[0] + 0x3E1D8, 1);
        SetListMenuRecordTable(D_001A8CFC[0] + 0x3E1D8, D_00261590);
    }
    return 0;
}

extern int D_00138344;
extern void func_0029C3A0(int);

/* Draws a menu page using the current button state. */
int func_002D58F8(void) {
    func_0029C3A0(D_00138344);
    return 0;
}

extern void func_0029C370(void);

/* Draws a fourth kind of menu page between the start and end of screen drawing. */
int func_002D5920(void) {
    SetupGifPaging(0);
    func_0029C370();
    DoGifPaging();
    return 0;
}

extern int D_001C51D4;

/* Clears the saved menu choice to "none". */
int func_002D5950(void) {
    D_001C51D4 = -1;
    return 0;
}

/* Does nothing and returns zero. */
int func_002D5968(void) {
    return 0;
}

extern int D_001A79F0 __attribute__((sda));
extern volatile unsigned char D_001A7C01 __attribute__((sda));
extern int D_001C51D0;
extern int D_001C4FA0[];
extern void func_0027D330(int);
extern void func_002C9C60(float);
extern int func_002E5E58(int, unsigned int, void *);
extern int func_0026F7C8(void);
extern int func_0026F7D0(void);
extern void func_00288CB0(int, int);
extern void func_002B49E0(int, int, int, int, int);
extern int func_0029C410(int);

/* Reads the buttons on the page-select menu: cancel closes, confirm picks the highlighted page and plays a sound or starts the change. */
int func_002D5970(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        char *root;
        int value;
        FadeToBlack(4);
        SetPauseScaleInverse(4.0f);
        root = gPauseMenuState;
        value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                result = -1;
                goto finish;
            default:
                break;
            }
        }
        result = 0;
    } else if (flags & 0xD00) {
        result = 1;
        D_001C51D0 = gCurrentMapIndex;
    } else if (flags & 0x40) {
        int *base = gMapOverlayState;
        if (gCurrentMapIndex != base[0x230 / 4]) {
            result = 1;
            PlaySoundFromGlobalBank(4, 0, 0);
            if (base[0x230 / 4] != 0 && D_001A7C01 == 0 && base[0x230 / 4] == 2) {
                BeginSlotRequest(6, 2, 1, 0x19, 0);
            } else if (EmptyStubF7C8() && EmptyStubF7D0()) {
                SetSmallDataValueAndRefresh(gMapOverlayState[0x230 / 4], 1);
            } else {
                BeginSlotRequest(6, 2, 1, gMapOverlayState[0x230 / 4], 0);
            }
        } else {
            result = 1;
            PlaySoundFromGlobalBank(4, 0, 0);
            FadeToBlack(4);
        }
    } else {
        func_0029C410(flags);
    }
finish:
    return result;
}

extern void func_0029C3E0(void);

/* Draws a fifth kind of menu page between the start and end of screen drawing. */
int func_002D5B08(void) {
    SetupGifPaging(0);
    func_0029C3E0();
    DoGifPaging();
    return 0;
}

extern int func_002D5B58(int, int, int *);

/* Sends a menu request and ignores the result. */
void func_002D5B38(int first, int second) {
    int result[4];
    result[0] = 0;
    ProcessMenuRequest(first, second, result);
}

typedef struct {
    char pad0[8];
    int f08;
    char pad1[8];
    int f14;
    int f18;
    int f1C;
    char pad2[0xF4 - 0x20];
    int fF4;
    int fF8;
    int fFC;
    int f100;
    int f104;
} Func002D5B58Root;
extern int D_001A7424 __attribute__((sda));
extern char D_001A7BB4 __attribute__((sda));
extern int D_001C1220[];
extern int D_001F29A0;
extern void *D_0026CD60[];
extern void func_00287EA8(void);
extern void func_00285828(int, int, int, int);
extern void func_00285788(int, int);
extern void func_002DF190(int, int);

/* Handles a request by type (0 and 1 do nothing): the others set a state code and its parameters in
   the block at D_001F2840, change the flags of D_001A7424 or call the helpers. Types 6 to 11 store 0
   through `result` and return 1 (type 7 falls through into type 8). The dispatch reads the table
   retail already has at D_0026CD60 (fourteen code addresses, one per type; types 0 and 1 go to the
   common return); `cases` only keeps the labels alive. */
int func_002D5B58(int type, int value, int *result)
{
    static void *cases[12] = {&&L3, &&L4, &&L5, &&L6, &&L7, &&L8, &&L10, &&L11, &&L9, &&L2, &&L12, &&L13};
    int ret = 0;

    if ((unsigned)type >= 14)
        goto done;
    goto *D_0026CD60[type];
L3:
    ((Func002D5B58Root *)gPauseMenuState)->f18 = value;
    goto done;
L4:
    PlaySoundFromGlobalBank(4, 0, 0);
    ClearConfirmPending();
    gSaveMenuFlags = (gSaveMenuFlags | 2) & ~4;
    D_001F29A0 = 0;
    BeginSlotRequest(4, 1, 1, value, 0);
    goto done;
L5:
    PlaySoundFromGlobalBank(4, 0, 0);
    gSaveMenuFlags = (gSaveMenuFlags | 4) & ~2;
    BeginSlotRequest(4, 1, 1, value, 0);
    D_001F29A0 = 1;
    goto done;
L6: {
    Func002D5B58Root *root;
    int index = value >> 16;
    if (index != 0) {
        Func002D5B58Root *first = (Func002D5B58Root *)gPauseMenuState;
        first->fFC = D_001C1220[index];
    }
    root = (Func002D5B58Root *)gPauseMenuState;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 5;
    root->fF4 = value & 0xFFFF;
    ret = 1;
    PlayMenuSoundIfEnabled(0, 0x11);
    *result = 0;
    goto done;
}
L7: {
    Func002D5B58Root *root = (Func002D5B58Root *)gPauseMenuState;
    root->fF4 = value;
    root->f100 = root->f14;
    root->f1C = 3;
    root->f104 = root->f08;
    PlayMenuSoundIfEnabled(0, 0x11);
    *result = 0;
}
L8: {
    Func002D5B58Root *root = (Func002D5B58Root *)gPauseMenuState;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 4;
    root->fF4 = value;
    ret = 1;
    PlayMenuSoundIfEnabled(0, 0x11);
    *result = 0;
    goto done;
}
L10: {
    Func002D5B58Root *root = (Func002D5B58Root *)gPauseMenuState;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 6;
    root->fF4 = value;
    ret = 1;
    PlayMenuSoundIfEnabled(0, 0x11);
    *result = 0;
    goto done;
}
L11: {
    Func002D5B58Root *root = (Func002D5B58Root *)gPauseMenuState;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 7;
    ret = 1;
    PlayMenuSoundIfEnabled(0, 0x11);
    *result = 0;
    goto done;
}
L9:
    D_001A7BB4 = value;
    ret = 1;
    *result = 0;
    goto done;
L2:
    PlayMenuSoundIfEnabled(2, 0x11);
    goto done;
L12:
    PlaySoundFromGlobalBank(4, 0, 0);
    StoreFourSettings(0, 0, 0, 0);
    SetMenuSizeLimits(0, 0);
    BeginSlotRequest(4, 1, 9, ((Func002D5B58Root *)gPauseMenuState)->f14, 0);
    goto done;
L13:
    BeginSlotRequest(4, 1, 11, ((Func002D5B58Root *)gPauseMenuState)->f14, 0);
done:
    return ret;
}

/* Runs the request for the currently highlighted row of a menu. */
int func_002D5E38(char *object, int arg, int *result)
{
    typedef struct { int first, value, third; } Func002D5E38Row;
    Func002D5E38Row *rows = *(Func002D5E38Row **)(object + 0x34);
    int index = *(int *)(object + 0x40);
    return ProcessMenuRequest(arg, rows[index].value, result);
}

/* Runs the request stored in one menu entry. */
void func_002D5E70(char *object, int *result) {
    ProcessMenuRequest(*(short *)(object + 2), *(int *)(object + 4), result);
}
