#include "names.h"
extern float D_L00_001BD2C0[];
extern void func_0027AB40(void);
extern void func_00338AD8(char *);
extern void func_00338F50(char *);

/* Draws a text panel with the screen scale set slightly smaller, unless it is hidden. */
void func_00338F58(char *panel)
{
    float savedScale;
    if (*(float *)*(int *)(panel + 4) == 0.0f)
        return;
    savedScale = D_L00_001BD2C0[44];
    D_L00_001BD2C0[44] = 0.62f;
    UpdateViewContext();
    switch (*(int *)(panel + 0x1C8)) {
    case 0: DrawTextPanel(panel); break;
    case 2: DoNothing00338F50(panel); break;
    }
    D_L00_001BD2C0[44] = savedScale;
    UpdateViewContext();
}
