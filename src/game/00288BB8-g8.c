#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct {
    u8 prefix[0x30];
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3c;
    s32 field40;
    s32 field44;
} BarlowUtilityQueueView;

extern s32 D_L04_001A8F00 __attribute__((sda));
extern s32 req_pop_queue(BarlowUtilityQueueView *, s32 *, s32 *);
extern s32 request_begin_slot(s32, s32, u32, u32, u8 *);
extern void level_init_owner_object(BarlowUtilityQueueView *);

/* launches one queued request using mode-dependent word arguments and resets the queue after a negative submission status */
s32 req_launch_queued(BarlowUtilityQueueView *queue) {
    if (queue->field38 != 0) {
        s32 request[2];
        s32 status;
        s32 mode;
        queue->field3c = 0;
        queue->field44 = 1;
        request[0] = 0;
        request[1] = 0;
        req_pop_queue(queue, &request[0], &request[1]);
        status = 0;
        mode = 1;
        if ((u32)(D_L04_001A8F00 - 1) < 2) mode = 2;
        queue->field40 = mode;
        if (request[1] == 0)
            status = request_begin_slot(1, mode, 0, request[0], 0);
        else if (request[1] == 1)
            status = request_begin_slot(2, mode, request[0], 0, 0);
        if (status < 0) level_init_owner_object(queue);
        return status == 0;
    }
    return 0;
}

/* The retail unit reaches its small-data words through $gp, so it is built -G8.  The two
   control words at the top of the small-data area are declared sda; the resident word and
   the mode word below are plain externs, whose .extern line the single-pass assembler only
   sees after the body, so it expands them to the absolute lui/%lo form the retail shows. */
typedef struct {
    u8 pad00[0x18];
    short field18;
    u8 pad1A[0x17C - 0x1A];
    s32 field17C;
} BootData001393E0;

extern BootData001393E0 g_memcard_state;
extern s32 D_001A8B84 __attribute__((sda));
extern s32 D_001B1680 __attribute__((sda));
extern s32 g_save_menu_flags;
extern s32 D_001B1680_1;
extern void flag_clear_word(void);
extern int MemcardSave(s32, s32);

/* Stores a new value in the small data words and, when asked, resets the related state. */
void data_set_small_value_and_refresh(int newValue, int refresh)
{
    D_001A8B84 = 1;
    D_001B1680 = newValue;
    if (newValue == -1) {
        if (g_memcard_state.field17C != 0) {
            g_memcard_state.field17C = 0;
        }
        if (g_memcard_state.field18 >= 0) {
            g_memcard_state.field18 = (short)newValue;
        }
        g_save_menu_flags &= ~0x200;
    }
    if (refresh != 0) {
        flag_clear_word();
        MemcardSave(0, D_001B1680_1);
    }
}