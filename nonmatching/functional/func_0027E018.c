/* functional: high. Hand-written from the assembly (never matched): emits one 0x60-byte GIF packet (header, 16-byte template, A+D rows) at D_001B22A8 in retail's order; stores and arithmetic widths follow retail. */
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int Quad __attribute__((mode(TI)));

extern u32 *D_001B22A8;
extern int D_001A7350[2];
extern Quad D_001AC800;

void func_0027E018(int a0, int a1, int a2, int a3, int t0, int t1, int t2, int t3, u64 arg9, u64 arg10)
{
    u32 *p = D_001B22A8;
    int ox = D_001A7350[0], oy = D_001A7350[1];
    int x0, x1, y0, y1, r0, r1, r2, r3, r4, r5;
    u64 mask, ly0, ly1;
    u64 *d;

    p[0] = 0x10000007;
    D_001B22A8[1] = 0;
    D_001B22A8[2] = 0;
    D_001B22A8[3] = 0x50000007;

    x0 = a0 * 16 + ox - 8;
    x1 = (a0 + a2) * 16 + ox - 8;
    y0 = a1 * 16 + oy - 8;
    y1 = (a1 + a3) * 16 + oy - 8;
    r0 = (t0 + t2) * 16;   /* t2' */
    r1 = t0 * 16;          /* t0' */
    r2 = t1 << 20;         /* t1' */
    r3 = (t1 + t3) << 20;  /* t3' */

    p = D_001B22A8;
    D_001B22A8 = p + 4;
    *(Quad *)(p + 4) = D_001AC800;
    D_001B22A8 = p + 8;

    mask = (u64)(((0xFFFFu << 16) | 0xF000u)) << 24;
    ly0 = (u64)(long long)y0 << 16;
    ly1 = (u64)(long long)y1 << 16;

    d = (u64 *)(p + 8);
    d[0] = arg10;
    d[1] = 0x154;
    d[2] = arg9;
    d[3] = (u64)(long long)(r2 + r1);
    d[4] = ((u64)(long long)x0 | ly0) | mask;
    d[5] = (u64)(long long)(r2 + r0);
    d[6] = ((u64)(long long)x1 | ly0) | mask;
    d[7] = (u64)(long long)(r3 + r1);
    d[8] = ((u64)(long long)x0 | ly1) | mask;
    d[9] = (u64)(long long)(r3 + r0);
    d[10] = ((u64)(long long)x1 | ly1) | mask;
    d[11] = 0;
    D_001B22A8 = D_001B22A8 + 0x18;
}
