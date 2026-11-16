#include "include_asm.h"
#include "names.h"

extern char g_loader_memory[];
extern int g_pad_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char *g_resident_data_base __attribute__((sda));
extern void *memset(void *, int, int);
extern void func_0029CD20(int);
extern int *ui_return_second_arg(int, int);
extern char *menu_system_init_pal(int *, int);
extern void func_0029C0D0(void);
extern void menu_draw_hud_bolt_pal(void);
extern void menu_draw_hud_subsystems_pal(void);
extern void func_0029CD18(void);
typedef struct { char pad[0x7A84]; void *cb1; void *cb2; } SubBf;

/* Sets up the level object: clears its memory block and global table, then picks which pair of callbacks it uses for this level (PAL). */
void level_init_callbacks_pal(void)
{
    char *state = g_loader_memory;
    char *obj;

    memset(*(void **)(state + 0x80), 0xCD, 0x40000);
    g_pad_state[104] = 0;
    g_pad_state[105] = 0;
    g_pad_state[106] = 0;
    g_pad_state[107] = 0;
    g_pad_state[108] = 0;
    g_pad_state[109] = 0;
    g_pad_state[110] = 0;
    g_pad_state[111] = 0;
    g_pad_state[112] = 0;
    g_pad_state[113] = 0;
    g_pad_state[114] = 0;
    g_pad_state[115] = 0;
    func_0029CD20(g_is_pal_video[0]);
    obj = menu_system_init_pal(ui_return_second_arg(0x3FBD0, *(int *)(state + 0x80)), 0x40000);
    g_resident_data_base = obj;
    if (g_current_map_index == 0x1F5) {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C0D0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029CD18;
    } else {
        ((SubBf *)(obj + 0x38000))->cb1 = menu_draw_hud_bolt_pal;
        ((SubBf *)(obj + 0x38000))->cb2 = menu_draw_hud_subsystems_pal;
    }
}


