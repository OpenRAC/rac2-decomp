#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 g_moby_l11_script_data_2[];
extern void func_300150(void *);
extern void func_2F8AD0(void *, void *);
extern void func_31F338(void);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((section(".sdata")));
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table;
extern u8 *g_arena_camera_table __attribute__((sda));
extern u8 g_hero_state[];
extern u8 g_music_state[];

void arena_end_frame_pal(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    u16 *counter = (u16 *)(obj + 0x96);
    if (*counter <= 0xFFFE) {
        *counter = *counter + 1;
    }
    func_300150(state + 0x190);
    func_2F8AD0(g_moby_l11_script_data_2, obj);
    func_31F338();
}

