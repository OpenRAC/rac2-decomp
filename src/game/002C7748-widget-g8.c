#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001AB7A8[1] __attribute__((sda));
extern int D_001AB7D0[1] __attribute__((sda));
extern int D_001AB7F0[1] __attribute__((sda));
extern int D_001AB808[1] __attribute__((sda));
extern int D_001AB820[1] __attribute__((sda));
extern int D_001AB830[1] __attribute__((sda));
extern int D_001AB838[1] __attribute__((sda));
extern int D_001AB850[1] __attribute__((sda));
extern int D_001AB890[1] __attribute__((sda));
extern int D_001AB8D0[1] __attribute__((sda));
extern int D_002614E8[];
extern unsigned char D_00189E20[];
extern int func_0026F7C0(void), func_0026F7C8(void), func_0026F7D0(void), func_0026F7D8(void), func_0026F7E0(void), func_0026F7E8(void), func_0026F7F0(void), func_002DF1B8(void);
extern void func_00348570(char *, int), func_00348578(char *, int), func_00348580(char *, int *), func_00348630(char *, int, int), func_00348640(char *, int, int *), func_003489E8(char *, int);
#define MENU (D_001A8CFC[0] + 0x39140)
/* Sets up the choices shown in the menu list, depending on what the game is doing. */
void func_002CAF18(void)
{
    if (!D_001A8CFC[0]) return;
    if (EmptyStubF7E0()) {
        SetMenuField0x44C(MENU, 1);
        SetMenuIconCountAndIcons(MENU, 5, D_001AB7F0);
        LoadMenuSpritesFromValues(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB850;
        SetMenuField0x448(p, 0);
        }
        SetMenuTableSlot(MENU, 0, 1);
        SetMenuTableSlot(MENU, 2, 1);
        SetMenuTableSlot(MENU, 3, 1);
        SetMenuTableSlot(MENU, 1, 1);
        SetMenuTableSlot(MENU, 4, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (EmptyStubF7C8() && EmptyStubF7D0()) {
        SetMenuField0x44C(MENU, 1);
        SetMenuIconCountAndIcons(MENU, 5, D_001AB808);
        LoadMenuSpritesFromValues(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB890;
        SetMenuTableSlot(p, 0, 1);
        }
        SetMenuTableSlot(MENU, 1, EmptyStubF7C0() ^ 1);
        SetMenuTableSlot(MENU, 2, EmptyStubF7C0() ^ 1);
        SetMenuTableSlot(MENU, 3, 1);
        SetMenuTableSlot(MENU, 4, EmptyStubF7C0() ^ 1);
        SetMenuField0x448(MENU, 0);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (EmptyStubF7D8()) {
        SetMenuField0x44C(MENU, 1);
        SetMenuIconCountAndIcons(MENU, 3, D_001AB820);
        LoadMenuSpritesFromValues(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB8D0;
        SetMenuField0x448(p, 0);
        }
        SetMenuTableSlot(MENU, 0, 1);
        SetMenuTableSlot(MENU, 1, 1);
        SetMenuTableSlot(MENU, 2, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (EmptyStubF7F0() == 0x31 || EmptyStubF7E8() || EmptyStubF7F0() == 0x1C) {
        SetMenuField0x44C(MENU, 1);
        SetMenuIconCountAndIcons(MENU, 2, D_001AB830);
        LoadMenuSpritesFromValues(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB838;
        SetMenuField0x448(p, 0);
        }
        SetMenuTableSlot(MENU, 0, 1);
        SetMenuTableSlot(MENU, 1, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else {
        SetMenuField0x44C(MENU, 1);
        SetMenuIconCountAndIcons(MENU, 7, D_001AB7D0);
        LoadMenuSpritesFromValues(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_002614E8;
        if (gHeroState[0x22B4] == 1) {
            SetMenuTableSlot(p, 0, 0);
            SetMenuTableSlot(MENU, 1, 0);
            SetMenuTableSlot(MENU, 2, 0);
        } else {
            SetMenuTableSlot(p, 0, 1);
            SetMenuTableSlot(MENU, 1, 1);
            SetMenuTableSlot(MENU, 2, 1);
        }
        }
        SetMenuTableSlot(MENU, 3, 1);
        SetMenuTableSlot(MENU, 4, 1);
        SetMenuTableSlot(MENU, 5, 1);
        if (AlwaysReturnTrue()) {
            SetMenuField0x448(MENU, 1);
            SetMenuTableSlot(MENU, 6, 1);
        } else {
            SetMenuField0x448(MENU, 0);
            SetMenuTableSlot(MENU, 6, 0);
        }
        if (gHeroState[0x22B4] == 1) { char *p = MENU; *(int *)(p + 0x43C) = 3; }
        else { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    }
    UpdateMenuChoiceListWidgets(MENU, 0);
}
