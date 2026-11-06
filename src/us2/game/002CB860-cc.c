/* func_US2_002CB860, the USA v2.00 copy of func_002CA8A8: the same C, where rename func_002DDEC8 becomes func_US2_002DECE0; rename func_002CAB00 becomes func_US2_002CBAB8; rename func_002CA5D0 becomes func_US2_002CB560. */
#include "common.h"

extern int D_001B1598 MACRO_ADDR __attribute__((sda));
extern int D_001A7344 MACRO_ADDR __attribute__((sda));
/* Frozen Batch A A15-struct-pad-20; acknowledged claim 6d4515f9ca5619f8d02349c6c2ad116dc989f5a4c317c4d31105f9a9271aa080. */
typedef unsigned char BatchA_A15_u8;

extern BatchA_A15_u8 D_L15_001FF640[];

/* Frozen Batch A A10-twin-base-32; acknowledged claim b588059f8808a6607867ee41ec367b24cfb85d2f4cc33273a4392842e34233d5. */
typedef unsigned char BatchA_A10_u8;

extern BatchA_A10_u8 D_L03_001FF8C0[];

extern BatchA_A10_u8 D_L03_001FFAC0[];

typedef int BatchA_A12_s32;

typedef struct { BatchA_A12_s32 a; BatchA_A12_s32 b; } BatchA_A12_BatchA24;

extern BatchA_A12_BatchA24 D_L08_001FF980;

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

/* External functions declared with exact aliases from task.externals */

/* func_002C7E28 is defined in 002C7E28-qcopy.c. */

/* func_002C7F78 is defined in 002C7F78.c. */

extern char D_001F2840[];

/* func_002C9C60 is matched in 002C9C60.c (built with -g). */

/* Uploads the saved screen image back to VRAM in 0x4000-byte strips (0x600 bytes per
   line of the current height), from the start buffer or, when a0 is set, ending at
   0x3FB000, after setting the restore mode (2 with a0, else 1) and bumping the frame
   counter. */
/* func_US2_002CBAB8 is defined in 002CAB00-g8.c. */

extern int func_002B49E0(int, int, int, int, void *);
extern short D_0018A000[];
/* The menu entries are 0x50 apart; D_001B1680 holds the selection and D_001A8B84
 * whether it is enabled. Both scalars and the enable flags are small data: the
 * -G0 compiler addresses them absolutely, and $gp-relative only in delay slots. */
typedef struct { unsigned char value; } ResidentFlag_2CCF68;
extern ResidentFlag_2CCF68 D_001A7BC9 __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCA __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCB __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCC __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCE __attribute__((sda));

extern int func_002CB7D0(int);

typedef struct {
    char reserved00[0x44];
    int state;
    char reserved48[0x8];
    int handle;
    int last;
    int current;
} MenuObject_2CD4E0;

typedef struct {
    char reserved00[0x10];
    int flags;
} ToggleState_2CD4E0;

extern MenuObject_2CD4E0 D_00259C78;
extern ToggleState_2CD4E0 *D_00259C44;
/* func_002C7748 is defined in 002C7748-create-g8.c. */

/* func_002C7BB8 is defined in 002C7BB8.c. */

/* func_002C8610 is in 002C8610.c. */

/* func_002C8A38 is defined in 002C8A38.c. */

/* Like func_002C8A38 with a second vector at +0x30 scaled into the motion. Its
 * address e is an integer: retail loads that vector's last two words only after
 * the first vector is stored, the order alias analysis gives an untraced base. */
/* func_002C9218 is defined in 002C9218.c. */

/* func_002C94C8 is defined in 002C94C8.c. */

/* A15-struct-pad-20 freshly exact-verified under family reservation */
/* A10-twin-base-32 freshly exact-verified under family reservation */
/* reads two object fields, forms centre plus and minus half of a third, and issues two five-argument draw calls taking an id-derived value and a fixed 64-bit attribute */
/* func_US2_002CB560 is defined in 002C7748-g8.c. */

/* func_002CA790 is defined in 002CA790.c. */

/* Pause-menu state at D_001F2840 (RAC1 update_menu_system: update_count, timer, ...). */
typedef struct {
    int mode;
    char pad04[0x10];
    int arg;
    char pad18[4];
    int pending;
    char pad20[0x100];
    int update_count;
    char pad124[0x34];
    int timer;
    char pad15C[8];
    int card_error_frames;
    int clear;
} PauseState;
/* Memory-card state: state and error code (RAC1 memory_card_state). */
typedef struct {
    char pad[0x15C];
    int state;
    int pad160;
    int err;
} PauseCardState;
extern PauseCardState D_001393E0;
extern int D_001A7424 __attribute__((sda));
extern int D_001B1684 __attribute__((sda));
extern s32 D_001B18A4[] __attribute__((sda));
extern void func_US2_002DECE0(void);
extern void func_002CAA58(void);
extern void func_002CAA88(void);
extern void func_002CAAA0(void);
extern void func_US2_002CBAB8(void);
extern void func_002CADB0(void);
extern int func_002E4AC8(void);
extern void func_002B6658(void);
extern void func_US2_002CB560(void);

void func_US2_002CB860(void)
{
    ((PauseState *)D_001F2840)->update_count = ((PauseState *)D_001F2840)->update_count > 31999 ? 32000 : ((PauseState *)D_001F2840)->update_count + 1;
    ((PauseState *)D_001F2840)->clear = 0;
    if (((PauseState *)D_001F2840)->timer) --((PauseState *)D_001F2840)->timer;
    if (D_001393E0.state < 3 && D_001393E0.err < 0) ++((PauseState *)D_001F2840)->card_error_frames;
    else ((PauseState *)D_001F2840)->card_error_frames = 0;
    func_US2_002DECE0();
    if ((D_001A7424 & 1) && ((PauseState *)D_001F2840)->mode == 4 && D_001B1684 >= 8) {
        if (!func_002B49E0(4, 1, 1, ((PauseState *)D_001F2840)->arg, 0)) return;
    }
    switch (((PauseState *)D_001F2840)->mode) {
    case 1: func_002CAA58(); break;
    case 2: func_002CAA88(); break;
    case 3: func_002CAAA0(); break;
    case 4: func_US2_002CBAB8(); break;
    case 5:
        func_002CADB0();
        func_002E4AC8();
        D_0018A000[0] = 10;
        D_001B18A4[1] = 0;
        return;
    }
    func_002B6658();
    func_002E4AC8();
    if (((PauseState *)D_001F2840)->pending) func_US2_002CB560();
}

void func_002CAA58(void);

/* A12-struct-2field-24 freshly exact-verified under family reservation */
void func_002CAA88(void);

void func_002CAAA0(void);

void func_002CADB0(void);

/* func_002CB820 reads $gp slots: it is defined in 002C7748-g8.c. */

/* func_002CB510 is defined in 002CB510.c. */

/* func_002CB648 is defined in 002CB648-g8.c. */

int func_002CB7D0(int mode);

/* func_002CBAE0 is defined in 002C7748-g8.c. */

/* func_002CC528 lives in 002CC528-g8.c. */

/* Near miss: nonmatching/game/func_002CC550.c (316/316 bytes; the two address
   materialisations in the loop preheader keep a separate %hi temporary). */

/* func_002CD3C0 is defined in 002CD3C0.c. */

