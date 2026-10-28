/* functional: medium. Same flow as retail (flag clear: tail into func_00124B88(arg0); else poll func_0011B500 until D_001A7100 reads non-zero, pumping func_00132028). Not byte-identical: register allocation differs, so the dead $v1 the callee's system call sees may differ. */
extern unsigned int D_001A7100;
extern char D_001A713F;
extern void func_0011B500(void *, void *);
extern int func_00124B88(int);
extern int func_00132028(void);

int func_00133580(int arg0) {
    int busy;

    if (*(int *)0x1A748C == 0)
        return func_00124B88(arg0);

    func_0011B500(&D_001A7100, &D_001A713F);
    busy = D_001A7100 < 1;
    *(int *)0x1A7498 = busy;
    if (busy == 1)
        return 0;
    if (arg0 == 1)
        return 1;
    do {
        func_00132028();
        func_0011B500(&D_001A7100, &D_001A713F);
        busy = D_001A7100 < 1;
        *(int *)0x1A7498 = busy;
    } while (busy == 0);
    return 0;
}
