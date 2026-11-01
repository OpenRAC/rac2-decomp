#include "include_asm.h"

#include "common.h"
typedef struct { int item, kind, c, d, e, special; } PurchaseRow;
typedef struct {
    char pad0[0x28]; void *moby;
    char pad2C[0x3C]; int last;
    char pad6C[0xC]; int handle, unused, index, state;
    char pad88[0xB8]; PurchaseRow rows[64]; int count;
} PurchaseState;
typedef struct { char pad0[0x88]; unsigned short price; char pad8A[4]; unsigned short capacity; char pad90[0x50]; } PurchaseItem;
extern PurchaseState D_0021F240;
extern PurchaseItem D_00239BA0[];
extern unsigned char D_00139568[];
extern int D_00139688[];
extern int D_001A79F8 __attribute__((sda));
extern int D_001B2248 __attribute__((sda));
extern int D_001B223C __attribute__((sda));
extern int D_001B2240 __attribute__((sda));
extern int D_001B2244 __attribute__((sda));
typedef struct { char pad[0x1C4]; int buttons; } PurchaseInput;
extern volatile PurchaseInput D_00138180;
extern int func_002F6510(void);
extern void func_002F6608(int);
extern int func_002E5CF8(int, int, void *);
extern int func_0026F748(int, int);
extern int func_00288FB8(int);
extern void func_002F88D8(int);
extern void func_00288308(int);
extern int func_00288870(void *, int, int);
extern void func_002AD860(int);
extern void func_002887B0(int);
extern void func_0028A130(int);
extern void func_0028B6C8(int, int);
extern void func_0029B6D0(int, int);
extern void func_US2_002FC008(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)


