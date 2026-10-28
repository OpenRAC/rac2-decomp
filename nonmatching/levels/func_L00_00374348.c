/* func_L00_00374348 - 432 bytes.  Worker attempt, 27 October 2026 (draft below).

   416 B vs 432 (level 00). Logic fully decoded (shop buy state machine states
   1/2/3). Diffs: retail rebuilds the pad word address twice (lui v1,0x14;
   daddu a0,v1; addiu v1,v1,-0x7E80; lw 0x1C4(v1) ... second check addiu
   v1,a0,-0x7E80; lw 0x1C4(v1)) i.e. reads D_00138180+0x1C4 twice via
   lui+addiu, not folded into the lw; mine folds the low part into lw and
   (with section .sdata attr) CSEs the load. Retail also derives the shop base
   again as addiu a0,s1,-0x840 for the state=3 store (matched in mine only
   partly). Tried: pointer vs struct cast, locals for index/state/price at top
   (needed), MACRO_ADDR-style sdata attribute. */

/* append to src/levels/shared/L00_00358D98-g8.c, remove INCLUDE_ASM from L00_00358D98.c and the extern func_L00_00374348(int*,int*) decl at the top of the g8 file; D_L00_0022F7C0 is extern int[] there. Only level 00 compiled. */
typedef struct {
    char pad00[0x28];
    int field28;
    char pad2C[0x4C - 0x2C];
    int field4C;
    char pad50[0x80 - 0x50];
    int index;
    int state;
    char pad88[0x144 - 0x88];
    struct { int price; int pad4[2]; int item; int pad10[2]; } rows[1];
    char pad160[0x740 - 0x144 - 28];
    int limit;
} Shop374348;

extern char D_00138180[];
extern int D_001B25A4 __attribute__((sda));
extern int D_001A79FC;
extern int D_001A7AF0;
extern char D_L00_0028B380c[];
extern void func_0035F3A8(int, int, int);
extern void func_003722E0(void);
extern void func_003794D0(void);

void func_L00_00374348(int *out, int *unused)
{
#define SHOP ((Shop374348 *)D_L00_0022F7C0)
    int index = SHOP->index;
    int state = SHOP->state;
    int price = SHOP->rows[index].price;

    if (state == 1) {
        *out = 0;
        if (D_001A79FC < price)
            func_0035F3A8(2, 0x11, SHOP->field28);
        SHOP->state = 2;
    } else if (state == 2) {
        if ((*(int *)(D_00138180 + 0x1C4) & 0x10) && !(D_001B25A4 & 0x10)) {
            *out = 0;
            SHOP->state = 3;
        } else if ((*(int *)(D_00138180 + 0x1C4) & 0x40) && !(D_001B25A4 & 0x40)) {
            *out = 1;
            SHOP->state = 3;
        }
    } else if (state == 3) {
        if (*out != 0 && D_001A79FC >= price) {
            int cash = D_001A79FC;
            D_001A79FC = cash - price;
            D_001A7AF0 = SHOP->field4C;
            *(int *)(D_L00_0028B380c + SHOP->rows[index].item * 40 + 0x18) = 1;
            func_003722E0();
            if (SHOP->limit < SHOP->index)
                SHOP->index = SHOP->limit;
            func_0035F3A8(7, 0x11, SHOP->field28);
        } else {
            func_0035F3A8(0, 0x11, SHOP->field28);
        }
        SHOP->state = 0;
        func_003794D0();
    }
#undef SHOP
}
