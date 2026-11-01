#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;
typedef struct {
    u8 field00[0x218]; signed short field218; u8 field21A[0x12e];
    signed short field348; u8 field34A[4]; signed short field34E;
    u8 field350[0x1147]; u8 field1497; u8 field1498[2]; u8 field149A;
    u8 field149B[0xdf9]; s32 field2294;
} NativeModeResident;
extern NativeModeResident D_00189E20_8;
extern s32 D_L00_001A8FF0 __attribute__((sda));
extern volatile u8 D_001A7B08[4] __attribute__((sda));
extern s32 D_L00_001A8FF4_1 __attribute__((sda));
extern u8 D_0018A0E0[];

/* resident mode predicate: returns 0, 1 or 2 from the resident state words */
s32 func_PAL_L00_002D3928(void) {
    s32 result = D_00189E20_8.field348;
    if (D_L00_001A8FF0 != 0 && D_L00_001A8FF4_1 == 0) result = 2;
    if (D_L00_001A8FF4_1 != 0 || D_00189E20_8.field2294 == 59 ||
        (D_00189E20_8.field2294 == 110 && D_00189E20_8.field149A == 0) ||
        D_00189E20_8.field2294 == 109 || D_00189E20_8.field218 != 0 ||
        (D_00189E20_8.field1497 != 0 && D_001A7B08[3] != 0 &&
         D_00189E20_8.field2294 == 0 && D_00189E20_8.field34E < 3)) result = 1;
    if (result == 1 && D_00189E20_8.field149A != 0) result = 0;
    return result;
}


