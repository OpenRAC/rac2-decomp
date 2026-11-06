/* functional: medium. Same calls, arguments, writes and order as retail; the frame is a variable-length array sized as retail does (count masked to 29 bits, rounded up to 16), so only its stack placement differs. */
typedef short s16;
typedef unsigned char u8;

extern int *D_001B22A8;
extern int D_001ABDD8[2] __attribute__((sda));
extern int D_001ABDE0 __attribute__((sda));
extern int D_001A72E0;

extern void func_002E4388(void *, int, void *);
extern int func_002E3E54(int, int, int, int);
extern void func_002E3FA0(int, int, int, int);
extern void func_0029CF58(int, int, int);
extern void func_0029CF78(void);
extern void func_002FC560(int, long);

#define REC(o, k) ((char *)(o) + ((k) << 5))
#define H(o, k, off) (*(s16 *)(REC(o, k) + (off)))
#define W20(o, k) (*(int *)(REC(o, k) + 0x20))

void func_002E3BD8(char *object)
{
    int count = *(int *)object;
    unsigned n = (unsigned)count & 0x1FFFFFFF;
    u8 frame[(n + 15) >> 4 << 4];
    int s0, s3;

    if (count == 0)
        return;
    func_002E4388(object + 0x10, count, frame);
    D_001B22A8[0] = 0x30000007;
    D_001B22A8[1] = 0x139300;
    D_001B22A8[2] = 0;
    D_001B22A8[3] = 0x50000007;
    D_001B22A8 = D_001B22A8 + 4;
    D_001ABDE0 = 1 - D_001ABDE0;
    if (frame[0] == 1)
        func_0029CF58(W20(object, 0), H(object, 0, 0x2E) >> 4, D_001ABDD8[D_001ABDE0]);
    if (*(int *)object > 0) {
        s0 = 0;
        do {
            if (frame[s0] == 1)
                func_0029CF78();
            D_001ABDE0 = 1 - D_001ABDE0;
            s3 = s0 + 1;
            if (s3 < *(int *)object) {
                if (frame[s3] == 1)
                    func_0029CF58(W20(object, s3), H(object, s3, 0x2E) >> 4, D_001ABDD8[D_001ABDE0]);
            }
            if (frame[s0] == 1) {
                int base = D_001ABDD8[1 - D_001ABDE0];
                int a = base + H(object, s0, 0x2C);
                int b = base + H(object, s0, 0x2A);
                if (func_002E3E54(base + H(object, s0, 0x28), 0x70002000,
                                  H(object, s0, 0x24), H(object, s0, 0x2C)) == 0)
                    func_002E3FA0(H(object, s0, 0x26), a, b, 0x70002000);
            }
            s0 = s3;
        } while (s0 < *(int *)object);
    }
    func_002FC560(0x47, 0x3180B);
    func_002FC560(0x4E, (long)(D_001A72E0 >> 13) | 0x1000000 | 0x100000000L);
}
