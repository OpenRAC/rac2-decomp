#include "common.h"

/* func_L03_003D20F8 (src/levels/03_endako/L03_00399230.c) in USA v2.00: the six resident
   bytes it sets sit 8 bytes further on, written at their constant addresses (retail's
   lui $at,0x1A; sb form). */
extern void func_2B8510(s32 a0);
extern void func_313378(s32 a0);
extern void func_2BEE78(char *a0, char *a1, s32 a2, s32 a3);
extern void func_311758(void *a0);
extern void func_32F140(s32 a0, s32 a1);
extern void func_359FD0(char *a0, char *a1);
extern void func_30D710(s32 a0, s32 a1);
extern char D_00189E20_11[];
extern u8   g_remote_view_done_flag;
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

void console_remote_view_cleanup_us2(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2;
    void *p;

    func_2B8510(0);
    s2 = D_00189E20_11;
    *(u16 *)(s2 + 0x24FC) = 0;
    func_313378(*(u8 *)(s0 + 0xB0));
    g_remote_view_done_flag = 1;
    *(u8 *)0x001A7B3A = 1;
    *(u8 *)0x001A7B03 = 1;
    *(u8 *)0x001A7B3B = 1;
    *(u8 *)0x001A7B04 = 1;
    *(u8 *)0x001A7B3C = 1;
    *(u8 *)0x001A7B02 = 1;
    func_2BEE78(s0 + 0x10, s0 + 0xF0, 0, 1);
    p = *(void **)(s1 + 0x2C);
    if (p != 0) {
        func_311758(p);
    }
    func_311758(D_L03_001B2A1C_tbl[0] + (*(s32 *)s1 << 8));
    *(s32 *)(s0 + 0x78) = 0x80468CDC;
    func_32F140(*(s32 *)(s1 + 0x24), -1);
    func_359FD0(s2 + 0x80, s2 + 0x90);
    func_30D710(0, -1);
}
