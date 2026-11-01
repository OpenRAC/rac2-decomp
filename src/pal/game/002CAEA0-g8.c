#include "include_asm.h"

typedef struct {
    char reserved_000[0x1248];
    int value_1248;
    char reserved_124C[0x107C];
    int value_22C8;
} GameState_189E20;
extern GameState_189E20 D_00189E20;
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_2CBAE0;
extern MenuState_2CBAE0 D_001F2840;
typedef struct {
    int state;
    int field4;
    char pad08[0xC];
    char *object;
    char pad18[0xC];
    int mode;
    int value;
    char pad2C[0x14];
    int choices[4];
    char pad50[0xD0];
    int frames;
} MenuState_2CA5D0;
typedef struct { char pad[0x22C8]; int choices[4]; } SavedChoices_2CA5D0;
typedef struct { char pad[0x10]; unsigned int flags; } Flags_2CA5D0;
typedef struct { char pad[0xEC]; char *children[14]; } CallbackGroup_2CA5D0;
typedef struct {
    char pad[0x14];
    int a[8];
    int b[16];
    int c[8];
} GroupTable_2CA5D0;
extern char D_001BAF80[];
extern int D_001A7398[] __attribute__((sda));
extern GroupTable_2CA5D0 *D_001B1888;
extern int D_001A72D4 __attribute__((sda));
extern void func_002FC3C0(int);
extern void func_002FC1D8(void);
extern void func_0028B160(int, int, int);
extern void func_0028AFE8(int);
extern void func_PAL_0029C0B8(int);
extern void func_0029B698(int);
extern void func_002FC280(void);

void func_PAL_002CB410(void)
{
    int i, j;

    if (((MenuState_2CA5D0 *)&D_001F2840)->frames < 10)
        return;
    func_002FC3C0(1);
    func_002FC1D8();
    if (((MenuState_2CA5D0 *)&D_001F2840)->object) {
        for (i = 0; i < 14; i++) {
            char *obj = ((CallbackGroup_2CA5D0 *)((MenuState_2CA5D0 *)&D_001F2840)->object)->children[i];
            if (obj && *(void (**)(char *, int))(obj + 12))
                (*(void (**)(char *, int))(obj + 12))(obj, 0);
        }
        ((MenuState_2CA5D0 *)&D_001F2840)->object = 0;
    }
    for (j = 0; j < 4; j++) {
        int old = D_001A7398[j];
        int selected = ((MenuState_2CA5D0 *)&D_001F2840)->choices[j];
        if (old != selected)
            ((SavedChoices_2CA5D0 *)&D_00189E20)->choices[j] = selected ? selected : 0x77;
    }
    D_001A72D4 = ((MenuState_2CA5D0 *)&D_001F2840)->value;
    func_0028B160(0, D_001B1888->c[0], 0);
    func_0028AFE8(2);
    if (D_001B1888->c[3])
        func_0028AFE8(3);
    if (D_001B1888->c[4])
        func_0028AFE8(4);
    func_PAL_0029C0B8(300);
    func_0029B698(150);
    ((MenuState_2CA5D0 *)&D_001F2840)->state = 5;
    ((MenuState_2CA5D0 *)&D_001F2840)->field4 = 0;
    ((MenuState_2CA5D0 *)&D_001F2840)->mode = 2;
    ((Flags_2CA5D0 *)D_001BAF80)->flags &= 0x7FFFFFFF;
    func_002FC280();
    func_002FC3C0(1);
}
