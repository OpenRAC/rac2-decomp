/* functional: high. snd_BankLoadAsync. Same reads, writes and calls in retail order; the $gp-relative globals are reached absolutely here (same addresses), which changes no behaviour. The two messages have no conversions, and func_00133580 takes one argument: what retail leaves in $a1-$a3 at those calls is not passed. */
extern int D_001A74C8;
extern int D_001A7488;
extern int D_001A74F8;
extern int D_001A71C0;
extern int D_001A74D0;
extern long D_001A74D8;
extern int D_001A71C4;
extern int D_001A7180;
extern char D_001A7140[];
extern char D_001A7578[];
extern char D_001A7600[];
extern char D_001A7630[];

extern void func_00115D48(char *msg);
extern int func_00133580(int a);
extern int func_0011D810(char *p);
extern void func_00132028(void);
extern void func_0011AEA0(int a);
extern int func_0011D620(char *client, int rpc, int mode, void *send_buf, int send_size, void *recv_buf, int recv_size, int a7, int a8);

void func_00132498(int a0, int a1, int a2, long a3)
{
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7600);
        return;
    }
    if (func_00133580(1) == 1) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7630);
        return;
    }
    D_001A71C0 = a0;
    D_001A71C4 = a1;
    D_001A7180 = -1;
    D_001A74D0 = a2;
    D_001A74D8 = a3;
    while (func_0011D810(D_001A7140) != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7578);
        func_00132028();
        func_0011AEA0(0);
    }
    D_001A74C8 = 1;
    func_0011D620(D_001A7140, 3, 1, &D_001A71C0, 8, &D_001A7180, 4, 0, 0);
}
