#include "names.h"
extern float D_L00_001BD2C0[];
extern void UpdateViewContext(void);
extern void text_panel_draw(char *);
extern void ui_nop_d(char *);

/* Draws a text panel with the screen scale set slightly smaller, unless it is hidden. */
void text_panel_draw_scaled(char *panel)
{
    float savedScale;
    if (*(float *)*(int *)(panel + 4) == 0.0f)
        return;
    savedScale = D_L00_001BD2C0[44];
    D_L00_001BD2C0[44] = 0.62f;
    UpdateViewContext();
    switch (*(int *)(panel + 0x1C8)) {
    case 0: text_panel_draw(panel); break;
    case 2: ui_nop_d(panel); break;
    }
    D_L00_001BD2C0[44] = savedScale;
    UpdateViewContext();
}
