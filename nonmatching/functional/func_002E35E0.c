/* functional: high. Same calls, frame writes and order as retail; the retail loop is a branch chain on the counter, written here as a switch. Case 0 and 1 are identical (retail's case 0 also stores a dead value to frame[2] that func_00283B98's result overwrites). */
typedef float f32;

extern f32 D_001ABDD4 __attribute__((sda));
extern short *D_001B20C0;
extern int D_001B20D0[4];
extern int D_001B2120[4];
extern int D_001B20F0[];
extern int D_001A72E0;

extern void func_002E37B0(void);
extern void func_00283388(void *);
extern void func_00282C88(void *);
extern f32 func_00283B98(f32, f32);
extern void func_00283430(void *, void *);
extern void func_002E3940(int);
extern void func_002E3820(void);
extern void func_002FC560(int, long);

void func_002E35E0(void)
{
    f32 frame[4];
    int i;

    i = 0;
    func_002E37B0();
    D_001B20C0[2] = 0;
    func_00283388(D_001B20F0);
    func_00282C88(frame);
    if (D_001B20C0[3] > 0) {
        do {
            f32 b = 0.0f;
            switch (i) {
            case 0:
            case 1:
                frame[1] = 0.0f;
                break;
            case 2:
                b = -0.15f;
                frame[1] = -0.075f;
                break;
            case 3:
                frame[0] = -0.06f;
                b = 0.125f;
                frame[1] = 0.05f;
                break;
            }
            frame[2] = func_00283B98(D_001ABDD4, b);
            func_00283430(D_001B20F0, frame);
            D_001B2120[0] = D_001B20D0[0];
            D_001B2120[1] = D_001B20D0[1];
            D_001B2120[2] = D_001B20D0[2];
            D_001B2120[3] = D_001B20D0[3];
            func_002E3940(i);
            i++;
        } while (i < D_001B20C0[3]);
    }
    func_002E3820();
    func_002FC560(0x47, 0x5360B);
    func_002FC560(0x4E, 0x1000000 | (D_001A72E0 >> 13));
}
