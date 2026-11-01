#include "include_asm.h"

typedef struct {
    char pad00[0x28];
    char *object;
    char pad2c[0x54];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int value; int third; } cells[0];  
} PurchaseModel;
extern PurchaseModel D_L00_0022F7C0;
typedef struct { char pad[0x1C4]; unsigned int pressed; } PurchaseInput;
extern PurchaseInput D_00138180;
extern int D_001A79F8;
extern unsigned int D_L00_001B25A4 __attribute__((sda));
extern int D_L00_001AD500 __attribute__((sda));
extern int D_L00_001AD4F8 __attribute__((sda));
extern int D_L00_001AD4FC __attribute__((sda));
extern int func_002E5CF8(int, int, char *);
extern int func_00288FB8(int);
extern void func_002F88D8(void *);
extern void func_US2_002FA028(void);
extern void func_US2_002FC008(void);

void func_US2_L00_00375068(int *answer, int *unused) {
    PurchaseModel *model = &D_L00_0022F7C0;
    int index = model->index;
    int price = model->cells[index].price;
    int state = D_L00_0022F7C0.state;
    if (state == 1) {
        *answer = 0;
        if (D_001A79F8 < price) func_002E5CF8(2, 17, D_L00_0022F7C0.object);
        D_L00_0022F7C0.state = 2;
    } else if (state == 2) {
        if ((D_00138180.pressed & 0x10) && !(D_L00_001B25A4 & 0x10)) {
            *answer = 0;
            D_L00_0022F7C0.state = 3;
        } else if ((D_00138180.pressed & 0x40) && !(D_L00_001B25A4 & 0x40)) {
            *answer = 1;
            D_L00_0022F7C0.state = 3;
        }
    } else if (state == 3) {
        if (*answer) {
            if (D_001A79F8 >= price && D_L00_001AD500 != 4) {
                D_L00_001AD4F8 = 1;
                D_L00_001AD4FC = model->cells[index].value;
                func_002E5CF8(7, 17, D_L00_0022F7C0.object);
                D_001A79F8 -= price;
                func_002F88D8((void *)func_00288FB8(0x2C61));
                func_002E5CF8(7, 17, D_L00_0022F7C0.object);
                func_US2_002FA028();
            } else if (D_L00_001AD500 == 4) {
                func_002F88D8((void *)func_00288FB8(0x2C62));
                func_002E5CF8(0, 17, D_L00_0022F7C0.object);
            } else {
                func_002F88D8((void *)func_00288FB8(0x2C62));
                func_002E5CF8(0, 17, D_L00_0022F7C0.object);
            }
        } else func_002E5CF8(0, 17, D_L00_0022F7C0.object);
        D_L00_0022F7C0.state = 0;
        func_US2_002FC008();
    }
}
