#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

/* Level data: the first is read $gp-relative, the second absolutely (an incomplete
   array type keeps it out of the small-data area even under -G8). */
extern s32 g_space_ship_owner_moby __attribute__((sda));
extern u8 g_counter_limit_value[];

/* Tells whether a stored counter is below a limit read from the owner object. */
s32 moby_is_counter_below_limit(void) {
    s32 owner = g_space_ship_owner_moby;
    s32 limit = *(s32 *)g_counter_limit_value;

    return limit < *(s16 *)(*(u32 *)(owner + 0x68) + 0x324);
}
