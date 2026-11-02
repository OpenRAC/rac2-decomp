/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, v0801: 192/192 bytes, 0/27 places; five instruction words differ.
 * Default -G8 profile. section(".sdata") on the two zero-store aliases gives
 * retail absolute $at stores while retaining split addresses on D_L00_001BF200.
 * The third block is exact. The second block retains its base in $a1 from
 * the start, while retail first uses $v1 and copies to $a1 after the guard.
 * Unsigned integer base and separate count-pointer forms tie. Declarations below. */
typedef unsigned char u8;

typedef unsigned int u32;

typedef signed int s32;

extern u32 D_L00_001BF200[4];

extern u32 D_L00_001B1AC0 __attribute__((section(".sdata")));

extern u32 D_L00_001B1AC0_1 __attribute__((sda));

extern u32 D_L00_001B1AC4 __attribute__((section(".sdata")));

extern u32 D_L00_001B1AC4_1 __attribute__((sda));

void func_L00_00300378(u8 *a0)
{
    if (*(int *)(a0 + 0) != 0)
        D_L00_001BF200[0] = (u32)(a0 + *(int *)(a0 + 0));
    if (*(int *)(a0 + 4) != 0) {
        u8 *p = a0 + *(int *)(a0 + 4);
        int count = *(int *)p;
        int i = 0;
        D_L00_001B1AC0_1 = (u32)p;
        if(count > 0) {
            int *q = (int *)(p + 0x1c);
            do { *q = (int)p + *q; q += 4; i++; } while(i < *(int *)p);
        }
    } else D_L00_001B1AC0 = 0;
    if (*(int *)(a0 + 8) != 0) {
        u8 *p = a0 + *(int *)(a0 + 8);
        int count = *(int *)p;
        int i = 0;
        D_L00_001B1AC4_1 = (u32)p;
        if(count > 0) {
            int *q = (int *)(p + 0x1c);
            do { *q = (int)p + *q; q += 4; i++; } while(i < *(int *)p);
        }
    } else D_L00_001B1AC4 = 0;
}
