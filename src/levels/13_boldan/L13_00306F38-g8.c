#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct Node {
    u8 pad0[0x28];
    struct Node *next;
    u8 pad2[0x34 - 0x2C];
    u16 flags;
    u8 pad3[0x98 - 0x36];
    u32 f98;
    u8 pad4[0xAA - 0x9C];
    s16 fAA;
} Node;

extern int g_level_progress_state __attribute__((sda));
extern int g_level_state_word __attribute__((nosda));
extern Node *g_flag_node_list_head[1] __attribute__((sda));

/* state 0 starts the effect, state 1 flags every live node of four ids */
/* Starts an effect, then in state 1 marks every live object of four kinds with a flag while the level is in a special mode. */
void flag_nodes_effect_update(u8 *moby) {
    Node *node;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        moby[0x20] = 1;
        break;
    case 1:
        if (g_level_progress_state == 2 && g_level_state_word == 3) {
            for (node = g_flag_node_list_head[0]; node != 0; node = node->next) {
                s16 class_id = node->fAA;

                if (class_id == 0x1F4 || class_id == 0xEA3 || class_id == 0xEA4 || class_id == 0x11EB) {
                    node->f98 = 0;
                    node->flags = (node->flags | 0x41) & 0xEFFF;
                }
            }
        }
        break;
    }
}
