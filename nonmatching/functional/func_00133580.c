/* functional: medium. Same flow as retail (flag clear: tail into func_00124B88(arg0); else poll func_0011B500 until D_001A7100 reads non-zero, pumping func_00132028, publishing the status to D_001A7498). Not byte-identical: register allocation differs. */
extern int D_001A748C __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern unsigned int D_001A7100;
extern char D_001A713F;
extern void func_0011B500(void *, void *);
extern int func_00124B88(int);
extern int func_00132028(void);

int func_00133580(int arg0) {
    int busy;

    if (D_001A748C == 0)
        return func_00124B88(arg0);

    func_0011B500(&D_001A7100, &D_001A713F);
    busy = D_001A7100 < 1;
    D_001A7498 = busy;
    if (busy == 1)
        return 0;
    if (arg0 == 1)
        return 1;
    do {
        func_00132028();
        func_0011B500(&D_001A7100, &D_001A713F);
        busy = D_001A7100 < 1;
        D_001A7498 = busy;
    } while (busy == 0);
    return 0;
}
