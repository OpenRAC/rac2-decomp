#include "common.h"

typedef unsigned int QuadDE990 __attribute__((mode(TI)));
typedef union RecordDE990 {
    QuadDE990 data[14];
    struct {
        char pad0[4];
        unsigned char kind;
        char pad5[0x67];
        int value;
        char pad70[0x1e];
        unsigned short cost;
    } f;
} RecordDE990;
typedef struct StateDE990 {
    int f0[4];
    short f10;
    unsigned char f12;
    unsigned char f13;
    int f14;
    int f18, f1c;
    short f20, f22;
    int f24;
    char f28[0x12];
    unsigned char f3a, f3b;
    int f3c;
} StateDE990;
extern StateDE990 D_001A79F8 MACRO_ADDR;
extern int D_001A7AF0 MACRO_ADDR;
extern int D_001A7AF0_gp SDATA(D_001A7AF0);
extern unsigned char D_0018C958[];
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_00139868[];
extern RecordDE990 D_00239BA0[];
extern unsigned char D_00139568[];
extern int D_00139688[];
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char D_0019B278[];
extern unsigned char D_001395B8[];
extern int D_001A73B8[] MACRO_ADDR;
extern unsigned char D_001A7B94[] MACRO_ADDR;
extern unsigned char D_001A7B08 MACRO_ADDR;
extern unsigned char D_00189E20[];
extern unsigned char D_001393E0[];
extern char D_001F2A40[];
extern void func_00282AB0(void *, void *, int);
extern void func_00282A60(void *, int, int);
extern void func_00298E08(void);
extern int func_00287FF8(int, int);
extern int func_00288870(RecordDE990 *, int, int);
extern void func_0029ADA0(char *);

void func_002DE990(int selected)
{
    struct {
        int flags[56];
        int words[56];
        int slots[56];
        RecordDE990 records[56];
    } saved;
    int saved32[32];
    unsigned char saved56[56];
    int saved12[12];
    StateDE990 savedState;
    unsigned char savedBlock[112];
    RecordDE990 first, second;
    int resident, hadCard, i, j, k;
    unsigned char control;
    StateDE990 *gameState;
    unsigned char *card, *block, *slots;
    int *words;
    unsigned char *state, *hud;
    card = D_0018C958;
    D_001A79F8.f12++;
    D_001A79F8.f3a = 1;
    D_001A79F8.f3b = 0;
    resident = D_001A7AF0;
    hadCard = *(unsigned short *)(card + 0x84);
    gameState = &D_001A79F8;
    savedState = *gameState;
    for (j = 0; j < 56; j++) {
        saved.flags[j] = D_001A7AF8[j];
        saved.words[j] = D_00139868[j];
        *(saved.records + j) = D_00239BA0[j];
        saved.slots[j] = D_00139568[j];
    }
    for (i = 0; i < 32; i++) saved32[i] = D_001A7A60[i];
    for (i = 0; i < 12; i++) saved12[i] = D_001A7A40[i];
    saved.flags[51] = 0;
    saved.flags[36] = 0;
    saved.flags[20] = 0;
    saved.flags[13] = 0;
    saved.flags[38] = 0;
    saved.flags[39] = 0;
    saved.flags[46] = 0;
    saved.flags[48] = 0;
    saved.flags[55] = 0;
    saved.flags[21] = 0;
    saved.flags[2] = 0;
    saved.flags[3] = 0;
    saved.flags[4] = 0;
    saved.flags[19] = 0;
    saved.flags[8] = 0;
    func_00282AB0(savedBlock, D_0019B278, 112);
    block = D_001395B8;
    control = block[0x90];
    for (i = 0; i < 56; i++) saved56[i] = D_001A7A80[i];
    func_00298E08();
    func_00282AB0(D_0019B278, savedBlock, 112);
    block = D_001395B8;
    block[0x90] = control;
    func_00282A60(D_001A7AB8, 0, 56);
    for (i = 0; i < 56; i++) D_001A7A80[i] = saved56[i];
    { int m; for (m = 7; m >= 0; m--) D_001A73B8[m] = 0; }
    D_001A79F8 = savedState;
    D_001A73B8[0] = 30;
    D_001A73B8[1] = 42;
    D_001A79F8.f22 = 0;
    D_001A79F8.f24 = 0;
    D_001A79F8.f18 = 0;
    D_001A79F8.f1c = 0;
    D_001A7B94[0] = 0;
    D_001A7B94[1] = 0;
    if (hadCard) {
        card = D_0018C958;
        if (*(unsigned short *)(card + 0x84) == 0)
            *(unsigned short *)(card + 0x84) = 1;
    }
    for (k = 0; k < 56; k++) {
        D_001A7AF8[k] = saved.flags[k];
        D_00139868[k] = saved.words[k];
        D_00239BA0[k] = *(saved.records + k);
        D_00139568[k] = saved.slots[k];
        D_00139688[k] = D_00239BA0[D_00139568[k]].f.cost;
    }
    for (i = 0; i < 32; i++) D_001A7A60[i] = saved32[i];
    for (i = 0; i < 12; i++) D_001A7A40[i] = saved12[i];
    D_001A7B94[1] = 0;
    D_001A7B94[0] = 0;
    func_00287FF8(10, 3);
    if (D_001A7B08) {
        if (D_00239BA0[D_00139568[0x10]].f.kind == 0)
            func_00287FF8(16, 2);
        else
            func_00287FF8(16, 3);
        if (D_00239BA0[D_00139568[0x10]].f.kind == 0) {
            func_00288870(&first, 16, 2);
            func_00288870(&second, 16, 0);
            words = D_00139868;
            words[16] = (float)first.f.value * (float)words[16] / (float)second.f.value;
        }
    }
    hud = D_00189E20;
    *(short *)(hud + 0x24fc) = 1;
    D_001A7AF0_gp = resident;
    if (selected >= 0) {
        state = D_001393E0;
        *(short *)(state + 0x18) = selected;
        *(int *)(state + selected * 28 + 0x30) = 0;
        func_0029ADA0(D_001F2A40);
        *(char **)(state + 0x174) = D_001F2A40;
        *(int *)(state + 0x148) = 0;
        if (*(int *)(state + 0x164) < 0) {
            *(int *)(state + 0x168) = 0;
            *(int *)(state + 0x164) = 19;
        }
    }
}
