#include "common.h"

extern char *D_001B23CC[] __attribute__((sda));
extern int D_001A7BB8 __attribute__((sda));
extern int D_001B23C8[] __attribute__((sda));
/* The observed packet-builder interface includes its mode argument. */
extern void func_002B6480(void *, int);
extern int func_00126F38(int);
extern int func_001244B8(int, int);
/* The catalogue retains the legacy name; its measured entry is 00127220. */
extern void func_00127218(int *, int) __asm__("func_00127220");
extern int func_00351F38(volatile int *);
extern volatile int D_001AE7D0[] __attribute__((sda));
extern volatile int D_001AE7D4[] __attribute__((sda));
extern volatile int D_001AE7D8[] __attribute__((sda));
extern volatile int D_001AE7DC[] __attribute__((sda));
extern volatile int D_001AE7E0[] __attribute__((sda));

/* Submit a ready movie frame on the active GS field, then restore EE interrupts.
 * The 0xD9168 and 0x1C81C0 values are offsets inside decoder allocations. */
int func_PAL_003521A8(void) {
    int *h = (int *)func_00126F38(2);
    int *buf;

    D_001AE7DC[0] = D_001A7BB8 ? D_001AE7DC[0] ^ 1 : (int)((*(volatile unsigned long long *)0x12001000 >> 13) & 1);
    if (D_001AE7D0[0] != 0) {
        D_001AE7D4[0] = D_001AE7D4[0] + 1;
        D_001AE7E0[0] = func_001244B8(1, 0);
        if (D_001AE7E0[0] == 0) {
            buf = (int *)func_00351F38((volatile int *)(D_001B23CC[0] + 0xD9168));
            if (buf == 0) {
                CpuSync();
                CpuEnableInt();
                return 0;
            }
            if (D_001AE7DC[0] == 0 && buf[0] == 2) {
                int off;
                func_001244B8(0, 0);
                off = (buf[1] << 14) + 0x1C81C0;
                func_002B6480((void *)(D_001B23C8[0] + off), 0);
                func_00127218(h, (int)buf + 0x40);
                buf[0] = 1;
            } else if (D_001AE7DC[0] == 1) {
                int st = buf[0];
                if (st == 1) {
                    int off;
                    func_001244B8(0, 0);
                    off = (buf[1] << 14) + 0x1C81C0;
                    func_002B6480((void *)(D_001B23C8[0] + off), 0);
                    func_00127218(h, (int)buf + 0x13880);
                    buf[0] = 0;
                    D_001AE7D8[0] = st;
                }
            }
        }
    }
    CpuSync();
    CpuEnableInt();
    return 0;
}