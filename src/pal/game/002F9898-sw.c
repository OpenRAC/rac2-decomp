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
extern void func_PAL_002FC1D0(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)
extern int ref_PAL_002F9898_00(int, int);

void func_PAL_002F9898(int *cancel, int *confirm)
{
    PurchaseItem result;
    int item, special, used;
    if (D_0021F240.state == 1) {
        {
            PurchaseItem *record = &ITEM;
            if (record->price) D_001B2248 = D_001A79F8 / record->price;
            else D_001B2248 = 0;
        }
        {
            int *ammo = &D_00139688[ROW.item];
            PurchaseItem *record = &ITEM;
            int room = record->capacity - *ammo;
            if (D_001B2248 > room) D_001B2248 = room;
        }
        *cancel = 0;
        *confirm = 0;
        if (ROW.kind == 1 && D_00139688[ROW.item] >= ITEM.capacity) {
            func_002E5CF8(2, 17, D_0021F240.moby);
        } else if (ROW.kind == 1) {
            PurchaseItem *record = &ITEM;
            if (D_001A79F8 < record->price) func_002E5CF8(2, 17, D_0021F240.moby);
            else *confirm = 1;
        } else if (D_001A79F8 < func_002F6510()) {
            func_002E5CF8(2, 0, D_0021F240.moby);
        }
        D_0021F240.state = 2;
    } else if (D_0021F240.state == 2) {
        if (*confirm == 1) {
            if ((BUTTONS & 0x8000) || (D_001B223C >= 16 && !(D_001B223C & 7)) || D_001B223C >= 48) {
                if (D_001B2248 >= 2) {
                    --D_001B2248;
                    if (!(D_001B223C & 3) || D_001B223C < 16)
                        func_002E5CF8(1, 17, D_0021F240.moby);
                }
            }
            if ((BUTTONS & 0x2000) || (D_001B2240 >= 16 && !(D_001B2240 & 7)) || D_001B2240 >= 48) {
                PurchaseItem *record = &ITEM;
                if (record->price) {
                    int max = D_001A79F8 / record->price;
                    int left = record->capacity - D_00139688[ROW.item];
                    if (left < max) max = left;
                    if (D_001B2248 < max) {
                        ++D_001B2248;
                        if (!(D_001B2240 & 3) || D_001B2240 < 16)
                            func_002E5CF8(1, 17, D_0021F240.moby);
                    }
                }
            }
        }
        if ((BUTTONS & 16) && !(D_001B2244 & 16)) {
            *cancel = 0;
            D_0021F240.state = 4;
        } else if ((BUTTONS & 64) && !(D_001B2244 & 64)) {
            *cancel = 1;
            D_0021F240.state = 4;
        }
    } else if (D_0021F240.state == 4) {
        if (*cancel == 1) {
            int cost;
            PurchaseItem *gate;
            if (ROW.kind == 1) {
                PurchaseItem *record = &ITEM;
                cost = record->price * D_001B2248;
            } else cost = func_002F6510();
            if (D_001A79F8 < cost && D_00139688[ROW.item] >= (gate = &ITEM)->capacity) {
                func_002E5CF8(0, 17, D_0021F240.moby);
            } else if (ROW.kind == 1) {
                int *ammo = &D_00139688[ROW.item];
                PurchaseItem *record = &ITEM;
                int total;
                if (*ammo < record->capacity) {
                    total = record->price * D_001B2248;
                    if (D_001A79F8 >= total) {
                        if (*ammo > record->capacity) *ammo = record->capacity;
                        used = D_001B2248;
                        used -= ref_PAL_002F9898_00(ROW.item, used);
                        {
                            PurchaseItem *record = &ITEM;
                            total = record->price * used;
                            D_001A79F8 -= total;
                        }
                        func_002F6608(0);
                        func_002F88D8(func_00288FB8(0xBDC));
                        func_002E5CF8(7, 17, D_0021F240.moby);
                    } else {
                        func_002F88D8(func_00288FB8(0xBDD));
                        func_002E5CF8(0, 17, D_0021F240.moby);
                    }
                } else func_002E5CF8(0, 17, D_0021F240.moby);
            } else {
                int price = func_002F6510();
                if (D_001A79F8 >= price) {
                    item = ROW.item;
                    func_00288308(item);
                    if (ROW.special) {
                        special = 0;
                        switch (ROW.item) {
                        case 12: case 14: case 17: case 18: case 53: special = 1; break;
                        }
                        if (special) {
                            PurchaseState *shop = &D_0021F240;
                            PurchaseRow *rows = shop->rows;
                            if (func_00288870(&result, rows[shop->index].item, 1) && result.price)
                                D_00139688[rows[shop->index].item] = result.capacity;
                        } else {
                            PurchaseState *shop = &D_0021F240;
                            PurchaseRow *rows = shop->rows;
                            if (func_00288870(&result, rows[shop->index].item, 2) && result.price)
                                D_00139688[rows[shop->index].item] = result.capacity;
                        }
                    }
                    if (item != 31 && item != 61) func_002AD860(item);
                    D_0021F240.last = item;
                    if (ROW.special) func_002887B0(ROW.item);
                    func_0028A130(D_0021F240.last);
                    D_001A79F8 -= price;
                    func_002F6608(0);
                    if (D_0021F240.handle != -1) func_0028B6C8(D_0021F240.handle, 0);
                    D_0021F240.handle = -1;
                    if (ROW.kind == 1) func_0029B6D0(ROW.item, 0xE4E1C0);
                    else if (D_0021F240.index > D_0021F240.count - 1) D_0021F240.index = D_0021F240.count - 1;
                    func_002F88D8(func_00288FB8(0xBDC));
                    func_002E5CF8(7, 17, D_0021F240.moby);
                } else {
                    func_002F88D8(func_00288FB8(0xBDD));
                    func_002E5CF8(0, 17, D_0021F240.moby);
                }
            }
        } else func_002E5CF8(0, 17, D_0021F240.moby);
        D_0021F240.state = 0;
        func_PAL_002FC1D0();
    }
}
