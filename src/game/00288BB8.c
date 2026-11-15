#include "include_asm.h"
#include "names.h"

void req_mark_queued_in_flag_table(int);

void req_reset_owner_queue(void*);

typedef unsigned char u8;

typedef int s32;

typedef unsigned int u32;

/* Ordinary integer controller and queue-launch algorithm; static proposals. */
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

/* Marks every request in the queue as used, clears its first word and resets the queue. */
void req_flush_queue(void *queue)
{
  req_mark_queued_in_flag_table((int)queue);
  *(unsigned int *)queue = 0;
  req_reset_owner_queue(queue);
}
extern s32 req_launch_queued(BarlowUtilityQueueView *queue);