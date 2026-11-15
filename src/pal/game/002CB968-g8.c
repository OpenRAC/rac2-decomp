#include "include_asm.h"
#include "names.h"

extern char g_pause_menu_state[];
extern int D_001AB7A4 __attribute__((sda));
extern char D_0025A190[];
extern char D_00259198[];
extern int menu_clear_choice(int, int);
extern int func_PAL_002CC950(void);
extern void menu_refresh_unlock_icon_states(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);
typedef struct Widget_2CAB00 {
    int (*update)(struct Widget_2CAB00 *);
    int unused;
    void (*open)(struct Widget_2CAB00 *, int);
    void (*close)(struct Widget_2CAB00 *, int);
} Widget_2CAB00;
typedef struct {
    char pad00[0xEC];
    Widget_2CAB00 *widgets[14];
} Source_2CAB00;
typedef struct {
    int mode, count, value, padC, pad10;
    char *source;
    char *destination;
    int status;
    char pad20[0xC0];
    char *previous;
} State_2CAB00;

void func_PAL_002CB968(void)
{
    Widget_2CAB00 **widgets = (Widget_2CAB00 **)(((State_2CAB00 *)g_pause_menu_state)->source + 0xEC);
    Widget_2CAB00 *w;
    int i, openIndex, closeIndex;
    if (D_001AB7A4) {
        if (!((State_2CAB00 *)g_pause_menu_state)->count && ((State_2CAB00 *)g_pause_menu_state)->source == D_0025A190) menu_clear_choice(0, 0);
        if (func_PAL_002CC950()) {
            if (!((State_2CAB00 *)g_pause_menu_state)->count) ((State_2CAB00 *)g_pause_menu_state)->count = 1;
            return;
        }
    }
    if (!((State_2CAB00 *)g_pause_menu_state)->count) {
        for (openIndex = 0; openIndex < 14; openIndex++) {
            w = ((Source_2CAB00 *)((State_2CAB00 *)g_pause_menu_state)->source)->widgets[openIndex];
            if (w && w->open) w->open(w, 0);
        }
        (((State_2CAB00 *)g_pause_menu_state)->count)++;
    }
    for (i = 0; i < 14; i++) {
        if (widgets && widgets[i] && widgets[i]->update) {
            if ((char *)widgets[i] == D_00259198) menu_refresh_unlock_icon_states();
            if (widgets[i]->update(widgets[i])) ((State_2CAB00 *)g_pause_menu_state)->status = ((State_2CAB00 *)g_pause_menu_state)->value == 4 ? 2 : 1;
        }
    }
    if (((State_2CAB00 *)g_pause_menu_state)->source && *(int *)(((State_2CAB00 *)g_pause_menu_state)->source + 0x128)) {
        w = *(Widget_2CAB00 **)(((State_2CAB00 *)g_pause_menu_state)->source + 0xE8);
        if (w->close) w->close(w, 1);
        *(int *)(((State_2CAB00 *)g_pause_menu_state)->source + 0xE8) = *(int *)(((State_2CAB00 *)g_pause_menu_state)->source + 0x128);
        *(int *)(((State_2CAB00 *)g_pause_menu_state)->source + 0x128) = 0;
        w = *(Widget_2CAB00 **)(((State_2CAB00 *)g_pause_menu_state)->source + 0xE8);
        if (w->open) w->open(w, 1);
    }
    if (((State_2CAB00 *)g_pause_menu_state)->destination) {
        if (((State_2CAB00 *)g_pause_menu_state)->source == ((State_2CAB00 *)g_pause_menu_state)->destination) snd_play_from_global_bank(17, 0, 0);
        else snd_play_from_global_bank(18, 0, 0);
        for (closeIndex = 0; closeIndex < 14; closeIndex++) {
            w = ((Source_2CAB00 *)((State_2CAB00 *)g_pause_menu_state)->source)->widgets[closeIndex];
            if (w && w->close) w->close(w, 0);
        }
        ((State_2CAB00 *)g_pause_menu_state)->mode = 3;
        ((State_2CAB00 *)g_pause_menu_state)->previous = ((State_2CAB00 *)g_pause_menu_state)->source;
        ((State_2CAB00 *)g_pause_menu_state)->source = 0;
        ((State_2CAB00 *)g_pause_menu_state)->count = 0;
    }
}
