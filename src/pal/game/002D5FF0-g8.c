#include "include_asm.h"

extern char *D_001A8CFC;
extern int ref_L00_002D5570_00 __attribute__((sda));
extern int ref_L00_002D5570_01 __attribute__((sda));
extern void func_PAL_0033B6C0(char *);
extern void func_PAL_0033B740(char *);

int func_PAL_002D6148(char *a0)
{
    if (D_001A8CFC != 0) {
        if (a0 == (char *)&ref_L00_002D5570_00)
            func_PAL_0033B6C0(D_001A8CFC + 0x3CF50);
        else if (a0 == (char *)&ref_L00_002D5570_01)
            func_PAL_0033B740(D_001A8CFC + 0x3CF50);
    }
    return 0;
}

extern int D_001A7424;
extern int D_001A7420;
extern int D_00138180[];
extern char D_001F2840[];
extern char *ref_L00_002D55E0_00 __attribute__((sda));
extern int func_PAL_0029D478(int);
extern int func_PAL_00343EC0(char *);
extern void func_PAL_002D6A70(int);

int func_PAL_002D61B8(void)
{
    int result = 0;
    int *state = D_00138180;
    int flags;
    D_001A7424 = (D_001A7424 | 2) & ~4;
    flags = state[0x1c4 / 4];
    if (flags & 0x10) {
        char *root = D_001F2840;
        int value = *(int *)(*(char **)(root + 0x14) + 0xe0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0: status = -1; goto finish;
            default: break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) result = 1;
    else {
        func_PAL_0029D478(flags);
        if ((state[0x1c4 / 4] & 0x40) && ref_L00_002D55E0_00) {
            char *entry = (char *)func_PAL_00343EC0(ref_L00_002D55E0_00 + 0x3EA78);
            struct { short unused; short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            if ((D_001A7420 == 6 || D_001A7420 == 13) && request.id == 5) {
                D_001A7420 = 12;
                D_001A7424 &= ~2;
            }
            func_PAL_002D6A70((int)&request);
        }
    }
    return result;
}

/* func_PAL_002D5FF0, the PAL copy of func_002D53F0: a centred text draw at y = 329 less a word
   reached through $gp (-G8), with text id 0xB60 where USA draws 0x2D4F at a scaled y. */
extern int D_001ABB8C __attribute__((sda));
extern void func_0027C540(long);
extern void func_0027C660(void);
extern void func_PAL_0029CEC8(void);
extern char *func_00288FB8(int);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

int func_PAL_002D5FF0(void)
{
    int y;

    func_0027C540(0);
    func_PAL_0029CEC8();
    y = 329 - D_001ABB8C;
    func_0027F980(0x1C7, y, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0xB60), -1);
    func_0027C660();
    return 0;
}
