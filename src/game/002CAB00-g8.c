#include "include_asm.h"
#include "names.h"

extern char D_001F2840[];
extern int D_001AB7A4 __attribute__((sda));
extern char D_0025A190[];
extern char D_00259198[];
extern void func_002D7AC8(int, int);
extern int func_002CBAE0(void);
extern void func_002CCED0(void);
extern void func_002E5E58(int, unsigned int, void *);
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
/* Updates the widgets of the current pause menu page: opens them when the page starts, runs each one, switches the active widget, and closes them when leaving. */
void func_002CAB00(void)
{
    Widget_2CAB00 **widgets = (Widget_2CAB00 **)(((State_2CAB00 *)gPauseMenuState)->source + 0xEC);
    Widget_2CAB00 *widget;
    int i, openIndex, closeIndex;
    if (D_001AB7A4) {
        if (!((State_2CAB00 *)gPauseMenuState)->count && ((State_2CAB00 *)gPauseMenuState)->source == D_0025A190) ClearSavedSelection(0, 0);
        if (UpdateMenuPageInput()) {
            if (!((State_2CAB00 *)gPauseMenuState)->count) ((State_2CAB00 *)gPauseMenuState)->count = 1;
            return;
        }
    }
    if (!((State_2CAB00 *)gPauseMenuState)->count) {
        for (openIndex = 0; openIndex < 14; openIndex++) {
            widget = ((Source_2CAB00 *)((State_2CAB00 *)gPauseMenuState)->source)->widgets[openIndex];
            if (widget && widget->open) widget->open(widget, 0);
        }
        (((State_2CAB00 *)gPauseMenuState)->count)++;
    }
    for (i = 0; i < 14; i++) {
        if (widgets && widgets[i] && widgets[i]->update) {
            if ((char *)widgets[i] == D_00259198) RefreshUnlockIconStates();
            if (widgets[i]->update(widgets[i])) ((State_2CAB00 *)gPauseMenuState)->status = ((State_2CAB00 *)gPauseMenuState)->value == 4 ? 2 : 1;
        }
    }
    if (((State_2CAB00 *)gPauseMenuState)->source && *(int *)(((State_2CAB00 *)gPauseMenuState)->source + 0x128)) {
        widget = *(Widget_2CAB00 **)(((State_2CAB00 *)gPauseMenuState)->source + 0xE8);
        if (widget->close) widget->close(widget, 1);
        *(int *)(((State_2CAB00 *)gPauseMenuState)->source + 0xE8) = *(int *)(((State_2CAB00 *)gPauseMenuState)->source + 0x128);
        *(int *)(((State_2CAB00 *)gPauseMenuState)->source + 0x128) = 0;
        widget = *(Widget_2CAB00 **)(((State_2CAB00 *)gPauseMenuState)->source + 0xE8);
        if (widget->open) widget->open(widget, 1);
    }
    if (((State_2CAB00 *)gPauseMenuState)->destination) {
        if (((State_2CAB00 *)gPauseMenuState)->source == ((State_2CAB00 *)gPauseMenuState)->destination) PlaySoundFromGlobalBank(17, 0, 0);
        else PlaySoundFromGlobalBank(18, 0, 0);
        for (closeIndex = 0; closeIndex < 14; closeIndex++) {
            widget = ((Source_2CAB00 *)((State_2CAB00 *)gPauseMenuState)->source)->widgets[closeIndex];
            if (widget && widget->close) widget->close(widget, 0);
        }
        ((State_2CAB00 *)gPauseMenuState)->mode = 3;
        ((State_2CAB00 *)gPauseMenuState)->previous = ((State_2CAB00 *)gPauseMenuState)->source;
        ((State_2CAB00 *)gPauseMenuState)->source = 0;
        ((State_2CAB00 *)gPauseMenuState)->count = 0;
    }
}
