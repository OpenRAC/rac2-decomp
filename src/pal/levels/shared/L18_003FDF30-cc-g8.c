/* func_PAL_L18_003FDF30, the PAL copy of func_L18_003F9E50: the same C, where rename func_L18_002E0070 becomes func_PAL_L18_002E01E0; scale *(s32 *)((char *)&D_L18_001B04E0 + (*(s16 *)(s0 + 0xAE) << 2)). */
typedef short s16;
typedef int s32;

extern s32 D_L18_001B0460 __attribute__((sda));
extern s32 D_L18_001B0480 __attribute__((sda));
extern s32 D_L18_001B04A0 __attribute__((sda));
extern s32 D_L18_001B04C0 __attribute__((sda));
extern s32 D_L18_001B04E0 __attribute__((sda));

extern void func_00335438(char *a0, char *a1, s32 a2, s32 a3, s32 t0);
extern void func_L01_0042A6F0(s32 a0, s32 a1);
extern void func_00335370(char *a0);
extern void func_003353C8(char *a0);
extern s32 func_PAL_L18_002E01E0(s32 a0, s32 a1);

void func_PAL_L18_003FDF30(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);

    func_00335438((char *)&D_L18_001B0460 + (*(s16 *)(s0 + 0xAE) << 4),
                (char *)&D_L18_001B0480 + (*(s16 *)(s0 + 0xAE) << 4), 1, 0, 0);
    func_L01_0042A6F0(2, (((int)(*(s32 *)((char *)&D_L18_001B04E0 + (*(s16 *)(s0 + 0xAE) << 2))) * 5 + 2) / 6));
    func_00335370((char *)&D_L18_001B04A0 + (*(s16 *)(s0 + 0xAE) << 4));
    func_003353C8((char *)&D_L18_001B04C0 + (*(s16 *)(s0 + 0xAE) << 4));
    func_PAL_L18_002E01E0(0x6F, 1);
    *(s16 *)(s0 + 0xAC) = 1;
}
