extern char D_L00_001BD2C0[];
extern int D_L00_001A8FB4;
extern char *D_L00_001A904C;
extern int D_L00_001AEA7C __attribute__((sda));
extern int D_L00_001AEA80 __attribute__((sda));
extern void func_0027AB40(void);
extern unsigned int func_0034CA68(void *);
extern void func_0034E2E0(void *, int, int, int);
extern void func_0034E218(void *);
extern void func_0034DB98(void *);
extern void func_00338F58(void *);
extern void func_0029CB80(void);
void func_0034E4F8(char *object)
{
    float saved;
    char *camera;
    char *state = D_L00_001BD2C0;
    saved = *(float *)(state + 0xB0);
    *(float *)(state + 0xB0) = 0.62f;
    func_0027AB40();
    if (D_L00_001A8FB4 == 0)
        func_0034E2E0(object, D_L00_001AEA7C, D_L00_001AEA80, func_0034CA68(object + 0x7A0) >> 24);
    func_0034E218(object);
    func_0034DB98(object + 0x7A0);
    camera = D_L00_001A904C + 0x38000;
    *(int *)(camera + 0x7354) = 0;
    *(int *)(camera + 0x7358) = 0;
    func_00338F58(object + 0x1FBC);
    func_0029CB80();
    *(float *)(state + 0xB0) = saved;
    func_0027AB40();
}

extern char *D_001B23CC[] __attribute__((sda));
extern int ref_L00_0034F690_00 __attribute__((sda));
typedef int (*CleanupCallback)(void);
extern int func_001339B0(void);
extern void func_00124B88(int);
extern void func_003505A8(void *);
extern void func_00351E40(void *);
extern void func_0011AA70(int);
extern void func_0011AA30(int);
extern void func_0011B658(int);
extern void func_0011A950(int, int);
extern CleanupCallback func_00126DC0(CleanupCallback);
extern int func_00351890(void *);
extern int func_0034F898(void *);
extern int func_003506A8(void *);

void func_0034F690(void)
{
    func_00124B88(0);
    func_003505A8(D_001B23CC[0]);
    func_00351E40(D_001B23CC[0] + 0xd9168);
    func_0011AA70(ref_L00_0034F690_00);
    func_0011AA30(ref_L00_0034F690_00);
    func_0011B658(2);
    func_0011A950(2, *(int *)(D_001B23CC[0] + 0xd8000 + 0x10f8));
    func_00126DC0(func_001339B0);
    func_00351890(D_001B23CC[0] + 0xd9048);
    func_0034F898(D_001B23CC[0] + 0xd9100);
    func_003506A8(D_001B23CC[0] + 0xd9040);
    func_00124B88(0);
    *(volatile unsigned int *)0x1000e000 &= ~2u;
}

extern char *ref_L00_0034EF58_01[] __attribute__((sda));
extern char ref_L00_0034EF58_00[];
extern void func_0026FEB8(void *, ...);
extern void func_00284088(int, int);
extern int func_0011AB10(void);
extern void func_0011AAB0(int, int);
extern int func_0034F408(void *, void *, int);
extern int func_0034F048(void *, void *, void *);

int func_0034EF58(void *first, void *second, char *pool, char *state, int mode, int volume)
{
    int result = 0;
    ref_L00_0034EF58_01[0] = pool;
    D_001B23CC[0] = state;
    func_0026FEB8(ref_L00_0034EF58_00, 0x38cac0);
    func_00284088(volume, volume);
    func_0011AAB0(func_0011AB10(), 1);
    if (func_0034F408(first, second, mode)) {
        result = func_0034F048(D_001B23CC[0] + 0xd9048, D_001B23CC[0], D_001B23CC[0] + 0xd9040);
    }
    func_0034F690();
    ref_L00_0034EF58_01[0] = 0;
    D_001B23CC[0] = 0;
    return result;
}

typedef unsigned long long u64;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned char u8;

extern int D_001A72DC;
extern int D_001B23C8;
extern void func_002B6480(void *, int);

/* FMV GS packet builder: one 0x40-byte header record, then a 0x60-byte record per
   (row, column), then the closing A_B word pair at the end of the run. */
void func_0034FE18(void *a0, int a1, int a2, int a3, int t0)
{
    u8 *p = (u8 *)a0;
    int rows = a2 >> 4;
    int cols = a3 >> 4;
    int i, j;
    u64 c00, c10, c18, c28, c38, c40;
    u32 off, addr;

    *(u64 *)(p + 0x00) = 0x10000003;
    *(u64 *)(p + 0x08) = 0;
    *(u64 *)(p + 0x10) = 0x1000000000000002ULL;
    *(u64 *)(p + 0x18) = 0xE;
    *(u64 *)(p + 0x20) = ((ll)D_001A72DC >> 8) << 32 | 0x8000000000000LL;
    *(u64 *)(p + 0x28) = 0x50;
    *(u64 *)(p + 0x30) = 0x1000000010ULL;
    *(u64 *)(p + 0x38) = 0x52;

    p += 0x40;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c00 = 0x10000004;
            c10 = 0x1000000000000002ULL;
            c18 = 0xE;
            c28 = 0x51;
            c38 = 0x53;
            c40 = 0x0800000000000040ULL;
            *(u64 *)(p + 0x00) = c00;
            *(u64 *)(p + 0x08) = 0;
            *(u64 *)(p + 0x10) = c10;
            *(u64 *)(p + 0x18) = c18;
            *(u64 *)(p + 0x20) = (((u64)(i << 4)) << 32) | (((u64)(j << 4)) << 48);
            *(u64 *)(p + 0x28) = c28;
            *(u64 *)(p + 0x30) = 0;
            *(u64 *)(p + 0x38) = c38;
            *(u64 *)(p + 0x40) = c40;
            *(u64 *)(p + 0x48) = 0;
            *(u32 *)(p + 0x50) = 0x30000040;
            *(u32 *)(p + 0x54) = a1 & 0x0FFFFFFF;
            *(u64 *)(p + 0x58) = 0;
            a1 += 0x400;
            p += 0x60;
        }
    }

    *(u32 *)(p + 0x00) = 0x20000000;
    off = (t0 << 14) + 0x1C81C0;
    addr = D_001B23C8 + off;
    *(u32 *)(p + 0x0C) = 0;
    *(u32 *)(p + 0x08) = 0;
    *(u32 *)(p + 0x04) = addr;
    func_002B6480((void *)(u32)(D_001B23C8 + off), 1);
}

extern char D_001AE830[];
extern void func_00351848(unsigned char *, int *, int *, int *, int *);
extern int func_003518F0(char *, unsigned long long, unsigned long long, int, int);
extern void func_00351868(char *, int);
extern void func_0034F780(int);
extern int func_00350460(u32, int, u32, int, u32, int, int, int);

int func_00350240(u8 *unused, char *src, char *dst)
{
    int first_address, first_count, second_address, second_count;
    int used = *(int *)(src + 8);
    int remain = *(int *)(src + 0xC);
    int size;
    int second;
    int result;

    size = (int)dst + *(int *)(dst + 0x50008);
    size -= used;
    if (remain < size)
        size = remain;
    second = remain - size;
    func_00351848((unsigned char *)(D_001B23CC[0] + 0xD9048),
                  &first_address, &first_count, &second_address, &second_count);
    result = func_00350460((first_address & 0x0FFFFFFF) | 0x20000000, first_count,
                           (second_address & 0x0FFFFFFF) | 0x20000000, second_count,
                           used, size, (int)dst, second);
    if (result > 0) {
        if (func_003518F0(D_001B23CC[0] + 0xD9048,
                          *(unsigned long long *)(src + 0x10),
                          *(unsigned long long *)(src + 0x18),
                          first_address, result) == 0)
            func_0034F780((int)D_001AE830);
    }
    func_00351868(D_001B23CC[0] + 0xD9048, result);
    return result > 0;
}
