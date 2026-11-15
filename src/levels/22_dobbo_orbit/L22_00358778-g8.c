#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

/* Level data: the first is read $gp-relative, the second absolutely (an incomplete
   array type keeps it out of the small-data area even under -G8). */
extern s32 D_L22_001AF314 __attribute__((sda));
extern u8 D_L22_0018B694[];

/* Tells whether a stored counter is below a limit read from the owner object. */
s32 func_L22_003A6620(void) {
    s32 owner = D_L22_001AF314;
    s32 limit = *(s32 *)D_L22_0018B694;

    return limit < *(s16 *)(*(u32 *)(owner + 0x68) + 0x324);
}
