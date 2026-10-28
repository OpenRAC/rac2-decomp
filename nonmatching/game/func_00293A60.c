/* func_00293A60 - 576 bytes.  Worker attempt, 27 October 2026 (draft below).

   dropped: 576B function with a 6-way jump-table switch (table at 0x26C900)
   whose case bodies (sizes of 0x152xxx records, func_002B7C10, 002B6828,
   00132828 paths) I only partly decoded; draft covers the head and one case,
   292B vs 576B, 40 diff lines. */

extern int D_001A7280[] __attribute__((sda));
extern int D_001A7284[] __attribute__((sda));
extern int D_001A7434[] __attribute__((sda));
extern int D_001A7900[] __attribute__((sda));
extern int D_001A3B30 __attribute__((sda));
extern int D_001A2160 __attribute__((sda));
extern int D_001A1B40 __attribute__((sda));
extern int D_001A2910 __attribute__((sda));
extern void func_00133230(void);
extern void func_00132028(void);
extern int func_00133580(int);
extern int func_00125588(void);
extern void func_00133640(void);
extern void func_002B6788(void);
extern void func_002E4A68(void);

int func_00293A60(void)
{
    func_00133230();
    func_00132028();
    if (func_00133580(1) != 0) {
        D_001A3B30++;
        if (D_001A7900[0] != 1)
            return 0;
        if (D_001A3B30 < 0x2D1)
            return 0;
        D_001A7434[0] = D_001A7900[0];
        D_001A2910 = 0;
        if (D_001A7280[0] >= 3)
            D_001A7280[0] = D_001A7280[0] - 1;
        func_00133640();
        return 0;
    }
    if (func_00125588() != 0 && D_001A3B30 == 0) {
        D_001A7434[0] = 1;
        D_001A2910 = 0;
        if (D_001A2160 >= 3)
            D_001A7280[0] = D_001A2160 - 1;
    }
    switch (D_001A7280[0]) {
    case 3:
        if (D_001A7284[0] != 0)
            return 0;
        func_002E4A68();
        func_002B6788();
        D_001A2160 = D_001A7280[0] + 1;
        return 0;
    default:
        return 0;
    }
}
