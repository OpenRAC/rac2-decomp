#include "include_asm.h"

extern char D_001F2840[];
extern int D_001AB7A4 __attribute__((sda));
extern char D_0025A190[];
extern char D_00259198[];
extern void func_002D7AC8(int, int);
extern int func_US2_002CCAA0(void);
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

void func_US2_002CBAB8(void)
{
    Widget_2CAB00 **widgets = (Widget_2CAB00 **)(((State_2CAB00 *)D_001F2840)->source + 0xEC);
    Widget_2CAB00 *w;
    int i, openIndex, closeIndex;
    if (D_001AB7A4) {
        if (!((State_2CAB00 *)D_001F2840)->count && ((State_2CAB00 *)D_001F2840)->source == D_0025A190) func_002D7AC8(0, 0);
        if (func_US2_002CCAA0()) {
            if (!((State_2CAB00 *)D_001F2840)->count) ((State_2CAB00 *)D_001F2840)->count = 1;
            return;
        }
    }
    if (!((State_2CAB00 *)D_001F2840)->count) {
        for (openIndex = 0; openIndex < 14; openIndex++) {
            w = ((Source_2CAB00 *)((State_2CAB00 *)D_001F2840)->source)->widgets[openIndex];
            if (w && w->open) w->open(w, 0);
        }
        (((State_2CAB00 *)D_001F2840)->count)++;
    }
    for (i = 0; i < 14; i++) {
        if (widgets && widgets[i] && widgets[i]->update) {
            if ((char *)widgets[i] == D_00259198) func_002CCED0();
            if (widgets[i]->update(widgets[i])) ((State_2CAB00 *)D_001F2840)->status = ((State_2CAB00 *)D_001F2840)->value == 4 ? 2 : 1;
        }
    }
    if (((State_2CAB00 *)D_001F2840)->source && *(int *)(((State_2CAB00 *)D_001F2840)->source + 0x128)) {
        w = *(Widget_2CAB00 **)(((State_2CAB00 *)D_001F2840)->source + 0xE8);
        if (w->close) w->close(w, 1);
        *(int *)(((State_2CAB00 *)D_001F2840)->source + 0xE8) = *(int *)(((State_2CAB00 *)D_001F2840)->source + 0x128);
        *(int *)(((State_2CAB00 *)D_001F2840)->source + 0x128) = 0;
        w = *(Widget_2CAB00 **)(((State_2CAB00 *)D_001F2840)->source + 0xE8);
        if (w->open) w->open(w, 1);
    }
    if (((State_2CAB00 *)D_001F2840)->destination) {
        if (((State_2CAB00 *)D_001F2840)->source == ((State_2CAB00 *)D_001F2840)->destination) func_002E5E58(17, 0, 0);
        else func_002E5E58(18, 0, 0);
        for (closeIndex = 0; closeIndex < 14; closeIndex++) {
            w = ((Source_2CAB00 *)((State_2CAB00 *)D_001F2840)->source)->widgets[closeIndex];
            if (w && w->close) w->close(w, 0);
        }
        ((State_2CAB00 *)D_001F2840)->mode = 3;
        ((State_2CAB00 *)D_001F2840)->previous = ((State_2CAB00 *)D_001F2840)->source;
        ((State_2CAB00 *)D_001F2840)->source = 0;
        ((State_2CAB00 *)D_001F2840)->count = 0;
    }
}
