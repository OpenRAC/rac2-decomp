#include "common.h"

extern void func_L05_00418200(void *);
extern void func_00282C88(char *);
extern unsigned int D_001A7AF0 MACRO_ADDR;
/* A pointer table whose slot 0 holds the active object (L30_003B3F70-g8.c also reads it as an array). */
extern void *D_0018B650[] __attribute__((nosda));
extern char D_L05_001B34F0[] MACRO_ADDR;
extern char D_L05_001B3510[] MACRO_ADDR;
extern float D_L05_001B3500;
/* Model ids per equipment selector, one 4-entry table per D_001A7AF0 bit field. */
extern short D_L05_001A8F70[] MACRO_ADDR;
extern short D_L05_001A8F78[] MACRO_ADDR;
extern short D_L05_001A8F80[] MACRO_ADDR;
extern short D_L05_001A8F88[] MACRO_ADDR;
extern short D_L05_001A8F90[] MACRO_ADDR;
extern short D_L05_001A8F98[] MACRO_ADDR;
extern short D_L05_001A8FA0[] MACRO_ADDR;
extern char *func_L05_0041C708(void *, float, int, int);
extern char *func_L05_00432080(void *, float);
extern int func_002ED8A0(int);
extern int func_L05_0037AC00(void);
extern int func_L05_0037AC40(void);
extern int func_00282948(char *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L05_00418288(void *);
extern void func_L00_004450C0(void *);

typedef struct {
    int f0;
    int f4;
    short f8;
    short fA;
    char padC[0x8];
    int f14;
    int f18;
    int f1C;
    char pad20[0x10];
    int f30;
    int f34;
    int f38;
    int f3C;
    char * f40;
    char * f44;
    char * f48;
    char * f4C;
    char * f50;
    int f54;
    int f58;
    int f5C;
    char pad60[0x40];
    int fA0;
    char padA4[0x8];
    char * fAC;
    char padB0[0x140];
    char * f1F0;
    char * f1F4;
    char * f1F8;
    char * f1FC;
    char * f200;
    char * f204;
    char * f208;
    int f20C;
    int f210;
    char pad214[0x4C];
    int f260;
    int f264;
    int f268;
    int f26C;
    int f270;
    char * f274;
    char * f278;
    int f27C;
} State_L05_00417D48;

typedef struct {
    char pad0[0x10];
    char pos[0x10];
    unsigned char state;
    char pad21[0x13];
    unsigned short modeBits;
    char pad36[0x32];
    State_L05_00417D48 *pVar;
} Obj_L05_00417D48;

/* State 0 spawns the equipment parts chosen by the D_001A7AF0 selector bits; state 1 updates timers and the
 * position copy. */
void func_L05_00417D48(Obj_L05_00417D48 *o)
{
    State_L05_00417D48 *st = o->pVar;
    int mode = o->state;
    int id;
    unsigned int flags;

    switch (mode) {
    case 0:
        st->f30 = -1;
        st->f270 = -1;
        st->f260 = 1;
        st->f264 = 0x3840;
        st->f0 = 0;
        st->f4 = 0;
        st->f8 = 0;
        st->fA = 0;
        st->f20C = 0;
        st->f210 = 0;
        st->f14 = 0;
        st->f18 = 0;
        st->f1C = 0;
        st->f34 = 0;
        st->f38 = 0;
        st->f3C = 0;
        st->f268 = 0;
        st->f26C = 0;
        st->f27C = 0;
        o->state = 1;
        o->modeBits |= 0x100;
        func_L05_00418200(o);
        func_00282C88(D_L05_001B34F0);
        D_0018B650[0] = o;
        flags = D_001A7AF0 & 3;
        D_L05_001B3500 = 0;
        o->modeBits |= 0x41;
        st->f40 = func_L05_0041C708(o, 0.05f, 0, D_L05_001A8F70[flags]);
        if (st->f40) *(int *)(st->f40 + 0x98) = 0;
        flags = (D_001A7AF0 >> 2) & 3;
        id = D_L05_001A8F78[flags];
        st->f44 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f48 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f44) *(int *)(st->f44 + 0x98) = 0;
        if (st->f48) *(int *)(st->f48 + 0x98) = 0;
        flags = (D_001A7AF0 >> 4) & 3;
        st->f4C = func_L05_0041C708(o, 0.05f, 0, D_L05_001A8F80[flags]);
        if (st->f4C) *(int *)(st->f4C + 0x98) = 0;
        st->f50 = func_L05_00432080(o, 0.05f);
        flags = (D_001A7AF0 >> 6) & 1;
        id = D_L05_001A8F88[flags];
        st->fAC = func_L05_0041C708(o, 0.05f, 0, id);
        st->f1F0 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->fAC) *(int *)(st->fAC + 0x98) = 0;
        if (st->f1F0) *(int *)(st->f1F0 + 0x98) = 0;
        flags = (D_001A7AF0 >> 9) & 1;
        id = D_L05_001A8F98[flags];
        st->f1F4 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f1F8 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f1F4) *(int *)(st->f1F4 + 0x98) = 0;
        if (st->f1F8) *(int *)(st->f1F8 + 0x98) = 0;
        if (func_002ED8A0(3)) {
            flags = (D_001A7AF0 >> 7) & 3;
            id = D_L05_001A8F90[flags];
            if (id) {
                st->f1FC = func_L05_0041C708(o, 0.05f, 0, id);
                st->f200 = func_L05_0041C708(o, 0.05f, 1, id);
                if (st->f1FC) *(int *)(st->f1FC + 0x98) = 0;
                if (st->f200) *(int *)(st->f200 + 0x98) = 0;
            }
        }
        flags = (D_001A7AF0 >> 10) & 3;
        id = D_L05_001A8FA0[flags];
        st->f204 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f208 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f204) *(int *)(st->f204 + 0x98) = 0;
        if (st->f208) *(int *)(st->f208 + 0x98) = 0;
        if (func_002ED8A0(4) != -1) {
            st->f274 = func_L05_0041C708(o, 0.05f, 0, 0x10E2);
            if (st->f274) *(int *)(st->f274 + 0x98) = 0;
        }
        if (func_002ED8A0(5) != -1) {
            st->f278 = func_L05_0041C708(o, 0.05f, 0, 0x10E4);
            if (st->f278) *(int *)(st->f278 + 0x98) = 0;
        }
        st->f58 = 70;
        st->f54 = 60;
        st->f5C = 0;
        st->fA0 = 0;
        break;
    case 1:
        if (func_L05_0037AC00() < func_L05_0037AC40()) st->f260 = mode;
        if (st->f260) {
            if (func_00282948((char *)&st->f264)) st->f268 = mode;
        }
        if (!func_002E59B0(o, st->f30)) st->f30 = func_002E5CF8(0, 4, o);
        func_L05_00418288(o);
        qcopy(D_L05_001B3510, o->pos);
        func_L00_004450C0(o);
        break;
    }
}
