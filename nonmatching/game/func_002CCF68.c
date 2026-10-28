/* func_002CCF68 - 384 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002CCF68: control flow matches retail (gp/at/delay-slot structure
   close), draft 380 B vs 384, needs own file 002CCF68-g8.c "-O2 -G8
   -ffunction-sections" (NOT_SDA for D_001F2854 gives the lui v0/lw v1 form).
   Open problem: address forms of D_001B1680 (sda gp read/write, absolute `lui
   $at; sw` store via second name D_001B1680_1), D_001B8B84 (tied lui/lw load,
   `lui $at; sw` store) and bytes D_001A7BC9..CE (tied lui/lbu) cannot all be
   had in one -G8 file: MACRO_ADDR gives tied loads but stores become $gp; sda
   arrays become $gp. Also register: retail hi of D_00138180 in a3 and saved
   D_001B1680 in t0 (mine swapped), byte in v0/index in v1 (mine v1/a0). */

typedef struct { char pad[0x1C4]; int flags; } MenuState;

extern char *D_001F2854 NOT_SDA;
extern MenuState D_00138180;
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680 __attribute__((sda));
extern int D_001B1680_1 MACRO_ADDR;
extern int D_001B8B84 MACRO_ADDR;
extern unsigned char D_001A7BC9 MACRO_ADDR;
extern unsigned char D_001A7BCA MACRO_ADDR;
extern unsigned char D_001A7BCB MACRO_ADDR;
extern unsigned char D_001A7BCC MACRO_ADDR;
extern unsigned char D_001A7BCE MACRO_ADDR;
extern char D_00259148[];
extern char D_00259198[];
extern char D_002591E8[];
extern char D_00259238[];
extern char D_00259288[];
extern char D_002592D8[];
extern int func_002D5EC0(char *);

int func_002CCF68(char *x)
{
    int blocked;
    int saved;
    int n;
    int b;

    if (*(char **)(D_001F2854 + 0xE8) == x) {
        if (D_00138180.flags & ~0x40) {
            if (x == D_00259148)
                return 0;
            blocked = D_001A8B84;
        } else {
            blocked = D_001B8B84;
        }
        saved = D_001B1680;
        if (!blocked && *(short *)(*(char **)(x + 0x34) + *(int *)(x + 0x40) * 12 + 2) == 3) {
            if (x == D_00259148) {
                D_001B1680_1 = 1;
                D_001A8B84 = 1;
                return 0;
            }
            if (D_00138180.flags & 0x40) {
                if (x == D_00259198) {
                    b = D_001A7BC9;
                    n = 1;
                } else if (x == D_002591E8) {
                    b = D_001A7BCA;
                    n = 2;
                } else if (x == D_00259238) {
                    b = D_001A7BCB;
                    D_001B1680 = 3;
                    goto done;
                } else if (x == D_00259288) {
                    b = D_001A7BCC;
                    n = 4;
                } else if (x == D_002592D8) {
                    b = D_001A7BCE;
                    n = 6;
                } else {
                    if (D_001A8B84 == 0)
                        D_001B1680 = saved;
                    return 0;
                }
                D_001B1680_1 = n;
done:
                D_001B8B84 = b != 0;
                if (D_001B8B84 == 0)
                    D_001B1680 = saved;
                return 0;
            }
        }
    }
    return func_002D5EC0(x);
}
