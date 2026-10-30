/* Historical 624-byte form. The new full-vector/cursor source is retained in
 * src/levels/16_snivelak/L16_0041F360-g8.c. Its local checks pass 1/1 placements
 * in each of USA v1.01, v2.00 and PAL; strict linked checks now pass in all three carrying programs.
 * Distinct counters for the three loops restore the retail register lifetimes.
 * This older reconstruction remains here to preserve its different lowering.
 */
/* Nonmatching reconstruction; game compiler, -O2 -G8 -ffunction-sections.
   us: 16_snivelak: 624 bytes, expected 576.
   us2: 16_snivelak: 624 bytes, expected 576.
   pal: 16_snivelak: 624 bytes, expected 576.
   The 33-point ring, collision passes and two draw passes are reconstructed. Pointer allocation, argument setup and loop scheduling remain different. Reopen with matching ring/collision structure. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef int quad __attribute__((mode(TI)));
extern f32 D_L16_001B2008 __attribute__((sda));
extern u32 D_L16_001B2000 __attribute__((sda));
extern s32 D_L16_001B1FF8 __attribute__((sda));
extern u32 D_L16_001B2004 __attribute__((nosda));
extern s32 D_L16_001B1FFC __attribute__((nosda));
extern f32 D_L16_001B200C __attribute__((nosda));
extern f32 D_L16_001B2010 __attribute__((nosda));
extern f32 D_L16_001B2014 __attribute__((nosda));
extern char D_L16_001A8F20[];
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CC0(char *, char *, char *);
extern void func_002A8C00(char *, char *, s32, char *, f32);
extern s32 func_002761F8(char *, char *, s32, char *, char *);
extern u32 func_00283D38(u32, u32, f32);
extern void func_L00_002EBE88(char *, s32, s32, s32, u32, u32, f32, f32, f32);

/* Constructs and clips the expanding ring, then draws its two surfaces. */
void func_L16_0041F360(char *self) {
    f32 points[33][4];
    char collision[48];
    char *st = *(char **)(self + 0x68);
    f32 angle;
    u32 inner, outer;
    s32 i;
    for (i = 0; i < 32; i++) {
        angle = (f32)(i << 1) * 0.09817477315664291f - 3.141592741012573f;
        points[i][0] = func_00283180(angle) * *(f32 *)(st + 0x2C);
        points[i][1] = func_00283198(angle) * *(f32 *)(st + 0x2C);
        points[i][2] = 0;
        func_00282CC0((char *)points[i], (char *)points[i], self + 0x10);
        points[i][3] = D_L16_001B2008;
    }
    *(quad *)points[32] = *(quad *)points[0];
    for (i = 0; i < 32; i++) {
        func_002A8C00(collision, self, 1, D_L16_001A8F20, *(f32 *)(st + 0x28));
        collision[24] = 0;
        collision[25] = 1;
        *(u16 *)(collision + 26) = *(u16 *)(self + 0xAA);
        func_002761F8((char *)points[i], (char *)points[i + 1], 9, self, collision);
    }
    inner = func_00283D38(D_L16_001B2000 & 0xFFFFFF, D_L16_001B2000, *(f32 *)(st + 0x30));
    outer = func_00283D38(D_L16_001B2004 & 0xFFFFFF, D_L16_001B2004, *(f32 *)(st + 0x30));
    func_L00_002EBE88((char *)points, D_L16_001B1FF8, D_L16_001B1FFC, 33, inner, outer,
                      D_L16_001B2008, D_L16_001B200C, *(f32 *)(st + 0x34));
    for (i = 31; i >= 0; i--) points[i][3] = D_L16_001B2010;
    func_L00_002EBE88((char *)points, D_L16_001B1FF8, D_L16_001B1FFC, 33, inner, outer,
                      D_L16_001B2010, D_L16_001B2014, -*(f32 *)(st + 0x34));
}
