#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern void weapon_menu_init_slots(void);

/* Sets up a pop-up menu panel with its size and starting values (PAL: slide-in value 25). */
/* authored C for independently verified level-native body */
void menu_init_panel_layout_pal(u8 *panel) {
 weapon_menu_init_slots();
 *(s32 *)(panel+0x58)=210;*(s32 *)(panel+0x5c)=200;
 *(s32 *)(panel+0x74)=-2;*(s32 *)(panel+0x78)=25;
 *(u16 *)(panel+0x48)=0;*(u16 *)(panel+0x4a)=0;*(s32 *)(panel+0x70)=0;
}






