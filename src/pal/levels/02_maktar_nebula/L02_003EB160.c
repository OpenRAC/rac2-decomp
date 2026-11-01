#include "include_asm.h"




#include "common.h"
extern void func_002A7750(char *, int, int);
extern void func_002A7750();
extern void func_00282CC0(void *, void *, void *);
extern void func_L02_0031E9E8(float *, float);
extern void func_L01_0031A278(char *, float *, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_00321878(char *, int, int, int, int, int, float);
extern int func_002A68A8(char *, int *);
extern char *func_003202E8(float *, int, int, int);
extern void func_00282D30(char *, char *, float);
extern void func_L02_003A8770(float *, int);
extern void func_0026FEB8(const char *, ...);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002B0A18(int, int);
extern char D_L02_001B09C8[];
extern int D_L02_001AEC78 __attribute__((sda));
extern int D_L02_001A903C __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern void *D_L02_002A52D0[5];
typedef struct {
    char pad0[0xA4];
    int flag;
} State003E77E0;
typedef struct {
    char pad0[0x79];
    u8 once;
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((sda));
extern u8 D_L02_00220730;

/* Re-arms the actor (func_002A7750 with 1), builds a random point near it (a, from
   func_L01_0031A278, plus the offset b from func_L02_0031E9E8) and acts on the mode at +0x5C of
   its state (the one func_L02_003E79F8 rolls), through the level's own jump table. Mode 1 starts
   an effect (func_L00_00321878). Mode 2 sets the word at +0xA4, decrements D_L02_001AEC78 and
   changes the actor's state to 5. Mode 3 scales by 0.35 the state of the object func_003202E8
   makes at the point. Mode 4 calls func_L02_003A8770 and prints D_L02_001B09C8. Mode 5 runs a
   one-shot (the flag at D_001A7A00 + 0x79, func_002E5E58, func_002B0A18 and D_L02_001A903C) and
   adds 300 to D_001A79F8. Modes 1, 3, 4 and 5 call func_002E5CF8 with 2 first, any other mode
   with 3. */
void func_PAL_L02_003EBBD0(char *arg0) {
    static void *tab[] = { &&c1, &&c2, &&c3, &&c4, &&c5 };
    char *state = *(char **)(arg0 + 0x68);
    float a[4];
    float b[4];
    int out;
    char *p;
    unsigned int sel;

    func_002A7750(arg0, 1, -1);
    func_L02_0031E9E8(b, 1.0f);
    func_L01_0031A278(arg0, a, 3.0f, 0.0f, 2.0f);
    func_00282CC0(a, b, a);
    sel = *(int *)(state + 0x5C) - 1;
    if (sel < 5)
        goto *D_L02_002A52D0[sel];
    goto other;
c1:
    func_002E5CF8(2, 0x20, arg0);
    func_L00_00321878(arg0, 0xF, 0x41, 3, -1, 4, 0.0f);
    goto done;
c2:
    ((State003E77E0 *)state)->flag = 1;
    D_L02_001AEC78--;
    func_002A7750(arg0, 5, -1);
    goto done;
c3:
    func_002E5CF8(2, 0x20, arg0);
    func_002A68A8(arg0, &out);
    p = *(char **)(func_003202E8(a, out, -1, 0) + 0x68);
    func_00282D30(p, p, 0.35f);
    goto done;
c4:
    func_002E5CF8(2, 0x20, arg0);
    func_L02_003A8770(a, 0);
    func_0026FEB8(D_L02_001B09C8);
    goto done;
c5:
    func_002E5CF8(2, 0x20, arg0);
    if (D_001A7A00.once == 0) {
        D_001A7A00.once = 1;
        func_002E5E58(1, 0, 0);
        func_002B0A18(0x1233, -1);
        D_L02_001A903C = 1;
    }
    D_001A79F8 += 300;
    goto done;
other:
    func_002E5CF8(3, 0x20, arg0);
done:
    return;
}

