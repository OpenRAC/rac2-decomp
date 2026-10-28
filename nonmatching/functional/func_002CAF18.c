/* functional: medium. Decoded from the assembly: sets up the widget at (D_001A8CFC + 0x39140) differently per game-state predicate (func_0026F7xx) with the same calls, arguments and order as retail; the shared tails are merged. Table addresses are the sda variables retail passes by address. */
extern char *D_001A8CFC;

extern int func_0026F7E0(void);
extern int func_0026F7C8(void);
extern int func_0026F7D0(void);
extern int func_0026F7D8(void);
extern int func_0026F7F0(void);
extern int func_0026F7E8(void);
extern int func_0026F7C0(void);
extern int func_002DF1B8(void);
extern void func_00348578(void *, int);
extern void func_00348640(void *, int, void *);
extern void func_00348580(void *, void *);
extern void func_00348570(void *, int);
extern void func_00348630(void *, int, int);
extern void func_003489E8(void *, int);

extern char D_001AB7F0[] __attribute__((sda)); /* gp-0x3800 */
extern char D_001AB7A8[] __attribute__((sda)); /* gp-0x3848 */
extern char D_001AB850[] __attribute__((sda)); /* gp-0x37A0 */
extern char D_001AB808[] __attribute__((sda)); /* gp-0x37E8 */
extern char D_001AB890[] __attribute__((sda)); /* gp-0x3760 */
extern char D_001AB820[] __attribute__((sda)); /* gp-0x37D0 */
extern char D_001AB8D0[] __attribute__((sda)); /* gp-0x3720 */
extern char D_001AB830[] __attribute__((sda)); /* gp-0x37C0 */
extern char D_001AB838[] __attribute__((sda)); /* gp-0x37B8 */
extern char D_001AB7D0[] __attribute__((sda)); /* gp-0x3820 */
extern char D_002614E8[];
extern unsigned char D_0018C0D4[];

#define Q ((char *)D_001A8CFC + 0x39140)
#define SETFN(p) (*(int *)(Q + 0x414) = (int)(p))

void func_002CAF18(void)
{
    if (D_001A8CFC == 0)
        return;

    if (func_0026F7E0()) {
        func_00348578(Q, 1);
        func_00348640(Q, 5, D_001AB7F0);
        func_00348580(Q, D_001AB7A8);
        SETFN(D_001AB850);
        func_00348570(Q, 0);
        func_00348630(Q, 0, 1);
        func_00348630(Q, 2, 1);
        func_00348630(Q, 3, 1);
        func_00348630(Q, 1, 1);
        func_00348630(Q, 4, 1);
        *(int *)(Q + 0x43C) = 0;
    } else if (func_0026F7C8() && func_0026F7D0()) {
        func_00348578(Q, 1);
        func_00348640(Q, 5, D_001AB808);
        func_00348580(Q, D_001AB7A8);
        SETFN(D_001AB890);
        func_00348630(Q, 0, 1);
        func_00348630(Q, 1, func_0026F7C0() ^ 1);
        func_00348630(Q, 2, func_0026F7C0() ^ 1);
        func_00348630(Q, 3, 1);
        func_00348630(Q, 4, func_0026F7C0() ^ 1);
        func_00348570(Q, 0);
        *(int *)(Q + 0x43C) = 0;
    } else if (func_0026F7D8()) {
        func_00348578(Q, 1);
        func_00348640(Q, 3, D_001AB820);
        func_00348580(Q, D_001AB7A8);
        SETFN(D_001AB8D0);
        func_00348570(Q, 0);
        func_00348630(Q, 0, 1);
        func_00348630(Q, 1, 1);
        func_00348630(Q, 2, 1);
        *(int *)(Q + 0x43C) = 0;
    } else if (func_0026F7F0() == 0x31 || func_0026F7E8() != 0 || func_0026F7F0() == 0x1C) {
        func_00348578(Q, 1);
        func_00348640(Q, 2, D_001AB830);
        func_00348580(Q, D_001AB7A8);
        SETFN(D_001AB838);
        func_00348570(Q, 0);
        func_00348630(Q, 0, 1);
        func_00348630(Q, 1, 1);
        *(int *)(Q + 0x43C) = 0;
    } else {
        func_00348578(Q, 1);
        func_00348640(Q, 7, D_001AB7D0);
        func_00348580(Q, D_001AB7A8);
        SETFN(D_002614E8);
        if (D_0018C0D4[0] == 1) {
            func_00348630(Q, 0, 0);
            func_00348630(Q, 1, 0);
            func_00348630(Q, 2, 0);
        } else {
            func_00348630(Q, 0, 1);
            func_00348630(Q, 1, 1);
            func_00348630(Q, 2, 1);
        }
        func_00348630(Q, 3, 1);
        func_00348630(Q, 4, 1);
        func_00348630(Q, 5, 1);
        if (func_002DF1B8()) {
            func_00348570(Q, 1);
            func_00348630(Q, 6, 1);
        } else {
            func_00348570(Q, 0);
            func_00348630(Q, 6, 0);
        }
        if (D_0018C0D4[0] == 1)
            *(int *)(Q + 0x43C) = 3;
        else
            *(int *)(Q + 0x43C) = 0;
    }
    func_003489E8(Q, 0);
}
