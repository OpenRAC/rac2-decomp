#include "include_asm.h"

typedef struct {
    int id;
    int kind;
    char pad[12];
    int owned;
} VendorSlot;
typedef struct {
    char pad[0x80];
    int index;
    char pad2[0xBC];
    VendorSlot slots[1];
} VendorState;
typedef struct {
    char pad[8];
    int text;
    char pad2[0x7C];
    unsigned short price;
    char pad3[4];
    unsigned short max;
    char pad4[0x50];
} VendorItem;
extern VendorState D_0021F240;
extern unsigned char D_00139568[];
extern int D_00139688[];
extern char D_00239BA0[];
extern char D_001AD3D0[];
extern int D_001A7340;
extern int D_001A79F8;
extern float D_001B2280;
extern char *func_00288FB8(int);
extern char *func_00115690(char *, char *);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern void func_0027FA10(int, int, unsigned long, char *, int);
extern void func_0027F5B8(int, int, unsigned long, char *, int);
extern void func_002F9BC0(char *, int);
extern void func_00288870(void *, int, int);
extern int func_002F6510(void);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, void *);

/* Draws the selected vendor item, its price and the purchase/maximum-ammo prompt. */
void func_US2_002FB718(void)
{
    char text[256];
    char info[224];
    int available = 1;
    VendorState *v;
    int color = 0x80F0F0F0;
    v = &D_0021F240;
    if (v->slots[v->index].kind == available) {
        int id = v->slots[v->index].id;
        char *copied;
        char *fmt = D_001AD3D0;
        if (D_00139688[id] >=
            ((VendorItem *)(D_00239BA0 + D_00139568[id] * 224))->max)
            available = 0;
        copied = func_00115690(text, func_00288FB8(((VendorItem *)(D_00239BA0 + D_00139568[id] * 224))->text));
        func_00115DA8(text, fmt, copied, func_00288FB8(0x2C5F));
        func_0027FB40(D_001A7340 >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, text, -1);
        func_002F9BC0(text, ((VendorItem *)(D_00239BA0 + D_00139568[v->slots[v->index].id] * 224))->price);
        if (D_001A79F8 < ((VendorItem *)(D_00239BA0 + D_00139568[v->slots[v->index].id] * 224))->price)
            color = (int)0x802020F0;
    } else {
        if (D_0021F240.slots[D_0021F240.index].owned) {
            int special = 0;
            switch (D_0021F240.slots[D_0021F240.index].id) {
            case 12:
            case 14:
            case 17:
            case 18:
            case 53:
                special = 1;
            }
            func_00288870(info, D_0021F240.slots[D_0021F240.index].id, special ? 1 : 2);
            func_0027FB40(D_001A7340 >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, func_00288FB8(*(int *)(info + 8)), -1);
        } else {
            func_0027FB40(D_001A7340 >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, func_00288FB8(((VendorItem *)(D_00239BA0 + D_00139568[D_0021F240.slots[D_0021F240.index].id] * 224))->text), -1);
        }
        func_002F9BC0(text, func_002F6510());
        if (D_001A79F8 < func_002F6510())
            color = (int)0x802020F0;
    }
    if (available) {
        int tex;
        func_0027FA10(220, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, func_00288FB8(0x31DA), -1);
        ((int *)info)[0] = 0x60F0F0B0;
        ((int *)info)[1] = 0x60F0F0B0;
        ((int *)info)[2] = 0x60F0F0B0;
        ((int *)info)[3] = 0x60F0F0B0;
        tex = func_0028E588(0x7567, 0);
        func_0028EA58(tex, 236, (int)(D_001B2280 * 210.0f + 0.5f), 16, (int)(D_001B2280 * 16.0f + 0.5f), info);
        func_0027F5B8(256, (int)(D_001B2280 * 210.0f + 0.5f), color, text, -1);
    } else {
        func_0027FB40(259, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, func_00288FB8(0x31B2), -1);
    }
}
