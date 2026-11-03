/* func_L00_002FC980: 616 bytes retail, 612 bytes here; all the control flow, the frame (0xD0),
 * the block-move loops (-O2 -G0 -ffunction-sections, default profile) and the register allocation
 * match except for the address forms, which differ in the four places where retail uses the
 * assembler-macro/unsplit form: the base of D_L00_001BCAC0 at the end (lui t0; addiu v0,t0,lo;
 * lw 0x30(v0)) and the float store to D_L00_001A8FC8 (lui $at; swc1 f0,-0x7038($at)), plus the
 * a2 -> s7 copy of the base. These are what -mno-split-addresses produces; a unit with that flag
 * (config/cflags.txt line, not allowed for the worker) should close it. Untested with that flag.
 * Tried: statement order of the three float stores (all six orders, same size), list pointer
 * (base + 0x18C) kept separate, entry pointer for the stores, sda attribute on the two globals.
 */
#include "include_asm.h"

extern int D_L00_001BCAC0[];
extern void func_0029F978(char *, int, void *);
typedef struct {
    short id;
    short value;
    float amount;
} Row_2FC980;

typedef struct {
    Row_2FC980 row[13];
} Table_2FC980;

typedef struct {
    char pad00[1];
    unsigned char used;
    char pad02[0x1E];
    float f20;
    float f24;
    float f28;
    char pad2C[0x14];
} Slot_2FC980;

typedef struct {
    char pad00[0x30];
    int f30;
    char pad34[0x44 - 0x34];
    short count;
    char pad46[0x18C - 0x46];
    char *objs[1];
} Ctx_2FC980;

extern unsigned char D_001A7A40;
extern int D_001A79F0 __attribute__((sda));
extern Table_2FC980 D_L00_002A0E60;
extern Slot_2FC980 D_L00_0022F600[7];
extern float D_L00_001A8FC8 __attribute__((sda));

void func_L00_002FC980(void)
{
    Table_2FC980 local;
    Ctx_2FC980 *base;
    char **list;
    char *obj;
    int i;
    int j;
    int k;
    float amount;

    if (D_001A7A40) {
        local = D_L00_002A0E60;
        base = (Ctx_2FC980 *)D_L00_001BCAC0;
        list = base->objs;
        for (i = 0; i < base->count; i++) {
            obj = list[i];
            if (*(int *)(obj + 0x54) == 0) {
                for (j = 0; local.row[j].id != 0; j++) {
                    if (*(short *)(obj + 0xAA) == local.row[j].id) {
                        amount = local.row[j].amount;
                        k = 0;
                        while (k < 7 && D_L00_0022F600[k].used != 0) {
                            k++;
                        }
                        if (k < 7) {
                            Slot_2FC980 *e = &D_L00_0022F600[k];

                            func_0029F978(obj, local.row[j].value, e);
                            e->f28 = amount;
                            e->f20 = amount;
                            e->f24 = amount;
                        }
                    }
                }
            }
        }
    }
    if (D_001A79F0 == 6 && ((Ctx_2FC980 *)D_L00_001BCAC0)->f30 == 1) {
        D_L00_001A8FC8 = -0.25f;
    }
}
