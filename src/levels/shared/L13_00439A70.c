#include "names.h"
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;

typedef struct {
    u8 pad[0x1C];
    s32 *data;
} Entry;

typedef struct {
    u8 pad[0x10];
    s32 value;
    u8 pad2[0xC];
} Slot;

typedef struct {
    u8 pad[0x7E];
    s16 state;
    u8 pad2[4];
    s16 index;
    s16 owner;
} Object;

extern char g_hero_state[];
extern Entry *D_L13_001B22C4 MACRO_ADDR;
extern Slot *D_L13_001B2140 __attribute__((sda));

/* Switches the object to state 3 unless the player owns it and meets its condition. */
void moby_switch_state_unless_owned(Object *obj) {
    s32 k;
    s32 *data = D_L13_001B22C4[obj->index].data;

    if (((Hero *)g_hero_state)->i[0x24A0 / 4] == obj->owner) {
        k = data[0x24 / 4];
        if (k < 0) {
            return;
        }
        if (((Hero *)g_hero_state)->i[0x630 / 4] == D_L13_001B2140[k].value) {
            if (((Hero *)g_hero_state)->i[0x640 / 4] == 0) {
                return;
            }
        }
    }
    obj->state = 3;
}
