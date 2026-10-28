/* functional: high. Reserves a qword of the frame DMA chain, writes an open DMA tag (0x20000000 NEXT) into it, links the moby segment tag to the new cursor, calls func_002A4AD8 and func_002FC748, then closes the segment by chaining the two tags again; same reads, writes and calls in the same order as retail, only codegen differs. */
extern int D_001B22A8 __attribute__((sda));
extern int D_001B1B50 __attribute__((sda));
extern int D_001A72D0 __attribute__((sda));
extern void func_002A4AD8(int a);
extern void func_002FC748(void);

void func_0029FDF0(void) {
    int *first = (int *)D_001B22A8;
    int *t;
    D_001B22A8 = (int)first + 0x10;
    t = (int *)D_001B1B50;
    t[0] = 0x20000000;
    t = (int *)D_001B1B50;
    t[1] = D_001B22A8;
    t = (int *)D_001B1B50;
    t[2] = 0;
    t = (int *)D_001B1B50;
    t[3] = 0;
    func_002A4AD8(D_001A72D0);
    func_002FC748();
    t = (int *)D_001B22A8;
    t[0] = 0x20000000;
    t = (int *)D_001B22A8;
    t[1] = D_001B1B50 + 0x10;
    t = (int *)D_001B22A8;
    t[2] = 0;
    t = (int *)D_001B22A8;
    t[3] = 0;
    D_001B22A8 = D_001B22A8 + 0x10;
    first[0] = 0x20000000;
    first[3] = 0;
    first[1] = D_001B22A8;
    first[2] = 0;
}
