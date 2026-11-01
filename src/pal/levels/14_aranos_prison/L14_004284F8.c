#include "include_asm.h"

extern void func_423000();
extern void func_423240();
extern void func_423358();
extern void func_423B30();
extern void func_423BD8();

void func_PAL_L14_004284F8(char *a0)
{
    if (*(unsigned char *)(a0 + 0x20) == 0) {
        func_423000(a0);
    } else {
        func_423240(a0);
        func_423358(a0);
        func_423B30(a0);
        func_423BD8(a0);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L14_004288B0);

extern void func_002B5278(char *object, float factor);
extern void func_002B5258(char *object);
extern void func_002B50E0(char *object, char *bone, float factor);
extern void func_002B4FF0(char *object, char *bone, float factor);
extern void *jtbl_002AA360[];

/* Dispatches on the owner's animation step and plays the matching bone animation. */
void func_PAL_L14_004290A8(char *object)
{
    static void * volatile tab[] = { &&cA, &&cC };
    char *state;
    unsigned int sel;

    sel = *(unsigned char *)(object + 0x42) - 1;
    state = *(char **)(object + 0x68);
    if (sel < 19) {
        goto *jtbl_002AA360[sel];
    }
    goto end;
cA:
    if (*(short *)(state + 0x776) != 0) {
        func_002B5278(object, *(float *)(state + 0x744));
    } else {
        func_002B5258(object);
    }
    goto out;
cC:
    if (*(short *)(state + 0x77A) != 0) {
        func_002B50E0(object, state + 0x700, *(float *)(state + 0x768));
    } else {
        func_002B4FF0(object, state + 0x700, *(float *)(state + 0x740));
    }
out:
end:
    return;
}

#include "common.h"
extern char D_L14_001B9500[];
extern char D_L14_001B9500[];
extern void func_PAL_002AC3C0(char *a0, void *a1);
extern void func_002AEC48(char *a0, void *a1, int a2, float a3, float a4);
extern float func_00282E48(char *a0, void *a1);
extern void func_002A93B0(char *a0);

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
void func_PAL_L14_00429150(char *a0)
{
    char *s1;
    float f20;
    float f21;

    s1 = *(char **)(a0 + 0x68);
    f21 = 0.0432f;
    f20 = 0.43200004f;
    func_PAL_002AC3C0(a0, s1 + 0x50);
    func_002AEC48(a0, s1 + 0x680, 1, f21, f20);
    func_002AEC48(a0, s1 + 0x600, 0, f21, f20);
    if (*(unsigned short *)(a0 + 0x96) <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = *(unsigned short *)(a0 + 0x96) + 1;
    *(unsigned short *)(s1 + 0x776) = 0;
    *(unsigned short *)(s1 + 0x778) = 0;
    *(unsigned short *)(s1 + 0x77A) = 0;
    if (*(unsigned char *)(a0 + 0x31) != 0) {
        if (func_00282E48(a0 + 0x10, D_L14_001B9500) < 24.0f) {
            func_002A93B0(a0);
            *(unsigned char *)(a0 + 0x6F) = 0x16;
        }
    }
}

