#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;

/* multiplies the index by 20 and adds it to a base; byte-identical across all 27 levels. */
s32 list_menu_get_selected_record_us2(u8 *a0) { return *(s32 *)(a0 + 0x260) + *(s32 *)(a0 + 0x16C) * 20; }

