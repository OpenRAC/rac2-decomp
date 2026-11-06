/* func_PAL_L15_004366F0, the PAL copy of func_L15_00430B30: the same C, which also deletes the two tracked mobys. */
typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

extern void func_0029F338(void *);
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(s32 a0);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_PAL_L05_0037D9D0(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_PAL_L15_00436118(u8 *a0, s32 a1);

extern s32 D_L15_001B1534 __attribute__((sda));
typedef struct StageState {
    s32 initial;
    s32 pad04[3];
    s32 active;
    s32 pad14[6];
    s32 timer;
} StageState;
extern char *D_L15_001B1584 __attribute__((sda));
extern char *D_L15_001B1588 __attribute__((sda));
extern StageState D_L15_00221E10;
extern s32 D_L15_001B2148;
extern u8 *D_L15_001B2714;

/* Applies both material passes to matching objects once, then advances the stage. */
void func_PAL_L15_004366F0(u8 *arg0) {
    s32 n;
    s32 count;
    u8 **p;

    if (D_L15_001B1534 == 0) {
        D_L15_00221E10.timer = 0;
        D_L15_001B1534 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        p = func_L05_00379EB8();
        count = func_L00_004272A0();
        if (count > 0) {
            n = count;
            do {
                if (*(s16 *)(*p + 0xAA) == 0xF93) {
                    func_PAL_L05_0037D9D0(*p, 1);
                    func_L05_0037CEE0(*p, (u8 *)D_L15_001B2714 + (D_L15_00221E10.initial << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*p, (u8 *)D_L15_001B2714 + (D_L15_00221E10.initial << 7) + 0x30, 64.0f);
                }
                n--;
                p++;
            } while (n);
        }
        if (D_L15_001B1584 != 0) {
            func_0029F338(D_L15_001B1584);
            D_L15_001B1584 = 0;
        }
        if (D_L15_001B1588 != 0) {
            func_0029F338(D_L15_001B1588);
            D_L15_001B1588 = 0;
        }
    }
    if (D_L15_00221E10.active == 0 && D_L15_001B2148 >= 6)
        func_PAL_L15_00436118(arg0, 1);
}
