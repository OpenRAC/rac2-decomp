

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout;


extern Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030EB78(void)
{
    LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE01 &= ~0x20;
    if (LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00.mode_08 != 2)
        return;
    if (LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00.selector_10 == 0) {
        LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE02 = 9;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00.selector_10 == -1) {
        LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00.selector_10 = 0;
        LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE02 = 9;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE00.selector_10 == -2)
        LVL_22_DOBBO_ORBIT_F8172b0f0a91a7cba_AT0030EB78_ROLE02 = 5;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout;


extern Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE02;
extern int LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE00;
extern int LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE03;
extern int LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE01;

void LVL_22_DOBBO_ORBIT_FUN_0030EBE8(void)
{
    if (LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE02.selector_10 != -2) {
        LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE03 = 3;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE01 != 0 || (LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE00 & 2) != 0)
        LVL_22_DOBBO_ORBIT_Fb09e58bdde03cd06_AT0030EBE8_ROLE03 = 6;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout;


extern Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE02;
extern unsigned int LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE03;
extern int LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE01;

void LVL_22_DOBBO_ORBIT_FUN_0030EC38(void)
{
    if (LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE02.selector_10 != -2) {
        LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE03 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE00 & 0x20u) != 0) {
        LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE00 ^= 0x20u;
        if (LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE01 != 0)
            LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE03 = 23;
        else
            LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE03 = 5;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE00 & 0x8u) != 0) {
        LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE00 ^= 0x8u;
        LVL_22_DOBBO_ORBIT_F584c3844a02fd1eb_AT0030EC38_ROLE03 = 7;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_a661193cb7db1192_SDataAccessorRootReset44Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
    unsigned char unknown_14[0x150];
    int selected_164;
    int value_168;
} Rac2Native_a661193cb7db1192_SDataAccessorRootReset44Layout;


extern Rac2Native_a661193cb7db1192_SDataAccessorRootReset44Layout LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE00;
extern int LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE01;

void LVL_22_DOBBO_ORBIT_FUN_0030ECB8(void)
{
    LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE00.selector_10 = 0;
    if (LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE00.selected_164 < 0) {
        LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE00.value_168 = 0;
        LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE00.selected_164 = 3;
    }
    LVL_22_DOBBO_ORBIT_Fa661193cb7db1192_AT0030ECB8_ROLE01 = 8;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_1716667661d8e672_SDataMoreGuard96Layout {
    unsigned char unknown_00[0x15c];
    int mode_15c;
    unsigned char unknown_160[0x4];
    int selected_164;
    unsigned char unknown_168[0x4];
    int extra_16c;
} Rac2Native_1716667661d8e672_SDataMoreGuard96Layout;


extern Rac2Native_1716667661d8e672_SDataMoreGuard96Layout LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE00;
extern unsigned int LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030ECE8(void)
{
    if (LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE00.mode_15c != 2 || LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE00.selected_164 >= 0)
        return;
    if (LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE00.extra_16c != 0) {
        LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE02 = 17;
        LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE01 |= 0x40u;
        return;
    }
    LVL_22_DOBBO_ORBIT_F1716667661d8e672_AT0030ECE8_ROLE02 = 14;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout;


extern Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE01;
extern unsigned int LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030ED48(void)
{
    if (LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE01.selector_10 != 0) {
        LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE02 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE00 & 6u) != 0) {
        LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE02 = 10;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE00 & 0x200u) != 0)
        LVL_22_DOBBO_ORBIT_F715e9b46a377ec8c_AT0030ED48_ROLE02 = 25;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_99b76d48da369e8d_SDataMoreThreshold156Layout {
    unsigned char unknown_00[0xc];
    int value_0c;
    int selector_10;
    unsigned char unknown_14[0x4];
    short phase_18;
    unsigned char unknown_1a[0x6];
    int value_20;
    unsigned char unknown_24[0x138];
    int mode_15c;
    unsigned char unknown_160[0x4];
    int selected_164;
    unsigned char unknown_168[0x4];
    int extra_16c;
} Rac2Native_99b76d48da369e8d_SDataMoreThreshold156Layout;


extern Rac2Native_99b76d48da369e8d_SDataMoreThreshold156Layout LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01;

void LVL_22_DOBBO_ORBIT_FUN_0030EDD8(void)
{
    short phase;
    if (LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.mode_15c != 2 || LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.selected_164 >= 0)
        return;
    if (LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.extra_16c != 0) {
        LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01 = 12;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.selector_10 < -1) {
        LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01 = 3;
        return;
    }
    phase = LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.phase_18;
    if (phase == -2) {
        if (LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.value_0c + LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE00.value_20 < 475)
            LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01 = 19;
        else
            LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01 = 12;
        return;
    }
    if (phase >= -1)
        LVL_22_DOBBO_ORBIT_F99b76d48da369e8d_AT0030EDD8_ROLE01 = 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout;


extern Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE01;
extern int LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE00;
extern int LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030EE78(void)
{
    if (LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE01.selector_10 != 0) {
        LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE02 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE00 & 2) != 0)
        LVL_22_DOBBO_ORBIT_Fa0e246aa2dc0b8e7_AT0030EE78_ROLE02 = 13;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout;


extern Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE02;
extern unsigned int LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE03;
extern int LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE01;

void LVL_22_DOBBO_ORBIT_FUN_0030EEB0(void)
{
    if (LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE02.selector_10 != 0) {
        LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE03 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE00 & 0x20u) != 0) {
        LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE00 ^= 0x20u;
        if (LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE01 != 0)
            LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE03 = 24;
        else
            LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE03 = 12;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE00 & 0x10u) != 0) {
        LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE00 ^= 0x10u;
        LVL_22_DOBBO_ORBIT_F998ff33d7f808dbf_AT0030EEB0_ROLE03 = 14;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout {
    unsigned char unknown_00[0x10];
    int selector_10;
    unsigned char unknown_14[0x168];
    int value_17c;
} Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout;


extern Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030EFE0(void)
{
    if ((LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 & 4) != 0)
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 &= ~4;
    if ((LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 & 2) != 0)
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 &= ~2;
    if ((LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 & 0x80) != 0) {
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE02 = 21;
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 = (LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 ^ 0x80) | 0x40;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 & 0x100) != 0) {
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE02 = 20;
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 = (LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE01 ^ 0x100) | 0x40;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE00.selector_10 != 0) {
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE02 = 3;
        return;
    }
    if (LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE00.value_17c != 0)
        LVL_22_DOBBO_ORBIT_F60904fd170c92806_AT0030EFE0_ROLE02 = 1;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout {
    unsigned char unknown_00[0x24];
    int word_24;
    unsigned char unknown_28[0x134];
    int mode_15c;
    unsigned char unknown_160[0x4];
    int selected_164;
    unsigned char unknown_168[0x4];
    int extra_16c;
    unsigned char unknown_170[0xc];
    int value_17c;
} Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout;


extern Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00;
extern unsigned int LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030F158(void)
{
    if (LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.mode_15c != 2 || LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.selected_164 >= 0)
        return;
    if (LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.extra_16c != 0 || LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.word_24 != 0) {
        LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.value_17c = 0;
        LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE02 = 21;
        LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE01 |= 0x440u;
        return;
    }
    LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE00.value_17c = 1;
    LVL_22_DOBBO_ORBIT_F8391b53329533f81_AT0030F158_ROLE02 = 1;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout;


extern Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030F2D0(void)
{
    if (LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE01.selector_10 != -2) {
        LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE02 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE00 & 0x20) != 0) {
        LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE00 ^= 0x20;
        LVL_22_DOBBO_ORBIT_F83cf4a65b6159c6c_AT0030F2D0_ROLE02 = 5;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_25b7bae55e05d925_SDataRootClear68Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_25b7bae55e05d925_SDataRootClear68Layout;


extern Rac2Native_25b7bae55e05d925_SDataRootClear68Layout LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE01;
extern int LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE00;
extern int LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE02;

void LVL_22_DOBBO_ORBIT_FUN_0030F318(void)
{
    if (LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE01.selector_10 != 0) {
        LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE02 = 3;
        return;
    }
    if ((LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE00 & 0x20) != 0) {
        LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE00 ^= 0x20;
        LVL_22_DOBBO_ORBIT_F25b7bae55e05d925_AT0030F318_ROLE02 = 12;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    unsigned char reserved_00[0x18];
    unsigned char enabled;
    unsigned char count;
    unsigned char kind;
    unsigned char reserved_1b[0x65];
    unsigned char payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;

typedef unsigned long Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags;


extern int LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE02;
extern void LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE03(void *owner, void *payload, int count);
extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE01(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);
extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE00(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);

Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_22_DOBBO_ORBIT_FUN_0032C208(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context)
{
    Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags result = 0;
    if (context->enabled == 1 && context->count != 0)
        LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE03(owner, context->payload, context->count);
    switch (context->kind) {
    case 0:
    case 1:
    case 2:
        if (LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE02 == 0)
            result = LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE01(owner, context);
        else
            result = LVL_22_DOBBO_ORBIT_Fbf55aa2a4d0dd351_AT0032C208_ROLE00(owner, context);
        break;
    default:
        break;
    }
    if ((result & 2) != 0) context->enabled = 0;
    return result;
}


extern int LVL_22_DOBBO_ORBIT_F4ccf861671c28be2_AT002A7A00_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_002A7A00(void)
{
    return LVL_22_DOBBO_ORBIT_F4ccf861671c28be2_AT002A7A00_ROLE00;
}


extern float LVL_22_DOBBO_ORBIT_Fb4ab5917cc7e0e71_AT002DDB90_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002DDB90(float value)
{
    LVL_22_DOBBO_ORBIT_Fb4ab5917cc7e0e71_AT002DDB90_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_967caba148c0b35c_u32;


extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE00;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE01;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE04;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE05;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE06;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE07;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE08;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE09;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE10;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE11;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE02;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE03;
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE12 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE13 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE14 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE15;

void LVL_22_DOBBO_ORBIT_FUN_002EB880(void)
{
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE00 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE01 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE04 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE05 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE06 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE07 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE08 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE09 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE12 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE13 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE14 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE10 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE11 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE02 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE03 = 0;
    LVL_22_DOBBO_ORBIT_F967caba148c0b35c_AT002EB880_ROLE15 = 0;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_a33fc77309a5e461_u32;


extern Rac2Native_a33fc77309a5e461_u32 LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01;
extern Rac2Native_a33fc77309a5e461_u32 LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F5F48(void)
{
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01 + 0) = 0x30000009u;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01 + 4) =
        (LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE00 + 0xc0u) & 0x0fffffffu;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01 + 8) = 0;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01 + 12) = 0x50000009u;
    LVL_22_DOBBO_ORBIT_Fa33fc77309a5e461_AT002F5F48_ROLE01 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_73f23b7222fbc541_u32;

typedef unsigned char Rac2Native_73f23b7222fbc541_u8;


extern Rac2Native_73f23b7222fbc541_u32 LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00;
extern Rac2Native_73f23b7222fbc541_u8 LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_002F6260(void)
{
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00 + 0) = 0x30000026u;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00 + 4) = (Rac2Native_73f23b7222fbc541_u32)LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE01;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00 + 8) = 0;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00 + 12) = 0x50000026u;
    LVL_22_DOBBO_ORBIT_F73f23b7222fbc541_AT002F6260_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_571a3580c10e935f_u32;

typedef unsigned char Rac2Native_571a3580c10e935f_u8;


extern Rac2Native_571a3580c10e935f_u32 LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00;
extern Rac2Native_571a3580c10e935f_u8 LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_002F62C0(void)
{
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00 + 0) = 0x30000029u;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00 + 4) = (Rac2Native_571a3580c10e935f_u32)LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE01;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00 + 8) = 0;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00 + 12) = 0x50000029u;
    LVL_22_DOBBO_ORBIT_F571a3580c10e935f_AT002F62C0_ROLE00 += 16;
}


extern int LVL_22_DOBBO_ORBIT_Fce2e52e5b0780004_AT002F6738_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_002F6738(void)
{
    return LVL_22_DOBBO_ORBIT_Fce2e52e5b0780004_AT002F6738_ROLE00;
}


extern int LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE00 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE01 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE02 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE03;

void LVL_22_DOBBO_ORBIT_FUN_002F67B0(int first, int second, int third, int fourth)
{
    LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE00 = first;
    LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE01 = second;
    LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE02 = third;
    LVL_22_DOBBO_ORBIT_F53dbeb99ca77d218_AT002F67B0_ROLE03 = fourth;
}


extern int LVL_22_DOBBO_ORBIT_F94af54270be5f5c3_AT002F8DE8_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F8DE8(void)
{
    LVL_22_DOBBO_ORBIT_F94af54270be5f5c3_AT002F8DE8_ROLE00 = 3;
}


extern int LVL_22_DOBBO_ORBIT_Fde7724c328f7c2d0_AT002F8E18_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_002F8E18(void)
{
    return LVL_22_DOBBO_ORBIT_Fde7724c328f7c2d0_AT002F8E18_ROLE00;
}


extern int LVL_22_DOBBO_ORBIT_F61acb1f304b382c7_AT002F8E20_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F8E20(void)
{
    LVL_22_DOBBO_ORBIT_F61acb1f304b382c7_AT002F8E20_ROLE00 = 1;
}


extern int LVL_22_DOBBO_ORBIT_Ff0259c87ab6a3193_AT002F8E30_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F8E30(void)
{
    LVL_22_DOBBO_ORBIT_Ff0259c87ab6a3193_AT002F8E30_ROLE00 = 0;
}


extern int LVL_22_DOBBO_ORBIT_F4a91c582a7608c02_AT002F9D28_ROLE00 __attribute__((sda));

int LVL_22_DOBBO_ORBIT_FUN_002F9D28(void)
{
    return LVL_22_DOBBO_ORBIT_F4a91c582a7608c02_AT002F9D28_ROLE00 != 0;
}


extern int LVL_22_DOBBO_ORBIT_F3abdbc5b6ec93b02_AT002F9D70_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F9D70(void)
{
    LVL_22_DOBBO_ORBIT_F3abdbc5b6ec93b02_AT002F9D70_ROLE00 = 0;
}


extern int LVL_22_DOBBO_ORBIT_F4bf2f2e615420e28_AT002F9D78_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_002F9D78(void)
{
    LVL_22_DOBBO_ORBIT_F4bf2f2e615420e28_AT002F9D78_ROLE00 = 1;
}


extern int LVL_22_DOBBO_ORBIT_Fa14de9886d500a76_AT002F9D88_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_002F9D88(void)
{
    return LVL_22_DOBBO_ORBIT_Fa14de9886d500a76_AT002F9D88_ROLE00;
}


extern unsigned int LVL_22_DOBBO_ORBIT_F2f9bdf3d0ed77d09_AT002FF6C0_ROLE00 __attribute__((sda));

void LVL_22_DOBBO_ORBIT_FUN_002FF6C0(void)
{
    if (LVL_22_DOBBO_ORBIT_F2f9bdf3d0ed77d09_AT002FF6C0_ROLE00 != 0)
        --LVL_22_DOBBO_ORBIT_F2f9bdf3d0ed77d09_AT002FF6C0_ROLE00;
}


extern int LVL_22_DOBBO_ORBIT_F6fc8969f33895bc4_AT003018F0_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_003018F0(void)
{
    LVL_22_DOBBO_ORBIT_F6fc8969f33895bc4_AT003018F0_ROLE00 = 1;
}


extern int LVL_22_DOBBO_ORBIT_Fef45f15dfb57feb2_AT00301998_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_00301998(void)
{
    LVL_22_DOBBO_ORBIT_Fef45f15dfb57feb2_AT00301998_ROLE00 = 1;
}


extern int LVL_22_DOBBO_ORBIT_Fd010ae7fd1640d51_AT003019A8_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_003019A8(void)
{
    return LVL_22_DOBBO_ORBIT_Fd010ae7fd1640d51_AT003019A8_ROLE00;
}


extern int LVL_22_DOBBO_ORBIT_Fa91295fd1429c8b1_AT003019B0_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_003019B0(void)
{
    LVL_22_DOBBO_ORBIT_Fa91295fd1429c8b1_AT003019B0_ROLE00 = 0;
}


extern int LVL_22_DOBBO_ORBIT_F30af8d5282429011_AT003019B8_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_003019B8(void)
{
    LVL_22_DOBBO_ORBIT_F30af8d5282429011_AT003019B8_ROLE00 = 0;
}


extern int LVL_22_DOBBO_ORBIT_F25c092d72a2ed8c8_AT003019C0_ROLE00 __attribute__((sda));

void LVL_22_DOBBO_ORBIT_FUN_003019C0(void)
{
    if (LVL_22_DOBBO_ORBIT_F25c092d72a2ed8c8_AT003019C0_ROLE00 == 0)
        LVL_22_DOBBO_ORBIT_F25c092d72a2ed8c8_AT003019C0_ROLE00 = 1;
}


extern int LVL_22_DOBBO_ORBIT_Fb0b88cda64ac44b6_AT003019D8_ROLE00 __attribute__((sda));

int LVL_22_DOBBO_ORBIT_FUN_003019D8(void)
{
    return LVL_22_DOBBO_ORBIT_Fb0b88cda64ac44b6_AT003019D8_ROLE00 == 3;
}


extern int LVL_22_DOBBO_ORBIT_F407105421407f332_AT00312350_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_00312350(void)
{
    LVL_22_DOBBO_ORBIT_F407105421407f332_AT00312350_ROLE00 = -1;
}


extern int LVL_22_DOBBO_ORBIT_Fa077d83e809ad7db_AT00317610_ROLE01;
extern unsigned char LVL_22_DOBBO_ORBIT_Fa077d83e809ad7db_AT00317610_ROLE00[];

void LVL_22_DOBBO_ORBIT_FUN_00317610(unsigned int index)
{
    if (index != 255u)
        LVL_22_DOBBO_ORBIT_Fa077d83e809ad7db_AT00317610_ROLE00[index + (unsigned int)LVL_22_DOBBO_ORBIT_Fa077d83e809ad7db_AT00317610_ROLE01 * 16u] |= 0x80u;
}


extern int LVL_22_DOBBO_ORBIT_Fe44fc83bd69b4f14_AT0032EB98_ROLE00 __attribute__((sda));

int LVL_22_DOBBO_ORBIT_FUN_0032EB98(void)
{
    return LVL_22_DOBBO_ORBIT_Fe44fc83bd69b4f14_AT0032EB98_ROLE00 > 0;
}


extern int LVL_22_DOBBO_ORBIT_F36a7237a316225ca_AT0032EBA8_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_0032EBA8(int value)
{
    LVL_22_DOBBO_ORBIT_F36a7237a316225ca_AT0032EBA8_ROLE00 = value;
}


extern int LVL_22_DOBBO_ORBIT_Fcbf196edf2a6cc29_AT0032EBB0_ROLE00 __attribute__((sda));

void LVL_22_DOBBO_ORBIT_FUN_0032EBB0(void)
{
    int value = (int)((unsigned int)LVL_22_DOBBO_ORBIT_Fcbf196edf2a6cc29_AT0032EBB0_ROLE00 - 1u);
    LVL_22_DOBBO_ORBIT_Fcbf196edf2a6cc29_AT0032EBB0_ROLE00 = value;
    if (value < 0)
        LVL_22_DOBBO_ORBIT_Fcbf196edf2a6cc29_AT0032EBB0_ROLE00 = 0;
}


extern int LVL_22_DOBBO_ORBIT_Fe6fa55215bad26dd_AT0032EBD0_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_0032EBD0(int value)
{
    LVL_22_DOBBO_ORBIT_Fe6fa55215bad26dd_AT0032EBD0_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_4e44694cc39e7084_u32;


extern Rac2Native_4e44694cc39e7084_u32 LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_0037EB38(Rac2Native_4e44694cc39e7084_u32 data_address, Rac2Native_4e44694cc39e7084_u32 tag_bits)
{
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00 + 0) = tag_bits | 0x30000000u;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00 + 4) = data_address;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00 + 8) = 0;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00 + 12) = 0;
    LVL_22_DOBBO_ORBIT_F4e44694cc39e7084_AT0037EB38_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ae24050903bcaa08_u32;


extern Rac2Native_ae24050903bcaa08_u32 LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_0037EC40(Rac2Native_ae24050903bcaa08_u32 final_word)
{
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00 + 0) = 0x10000000u;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00 + 4) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00 + 8) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00 + 12) = final_word;
    LVL_22_DOBBO_ORBIT_Fae24050903bcaa08_AT0037EC40_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_9da4b6b15b3cf4a0_RecordWord180;

typedef unsigned long long Rac2Native_9da4b6b15b3cf4a0_RecordValue180;


extern Rac2Native_9da4b6b15b3cf4a0_RecordWord180 LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00;

void LVL_22_DOBBO_ORBIT_FUN_0037EC88(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 final_word, Rac2Native_9da4b6b15b3cf4a0_RecordValue180 value)
{
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 0) = 0x10000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 4) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 8) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 12) = 0x50000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 16) = 0x8001u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 20) = 0x10000000u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 24) = 0x0eu;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 28) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordValue180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 32) = value;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 40) = final_word;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 + 44) = 0;
    LVL_22_DOBBO_ORBIT_F9da4b6b15b3cf4a0_AT0037EC88_ROLE00 += 48;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_54e735f08c731074_u32;

typedef unsigned char Rac2Native_54e735f08c731074_u8;


extern Rac2Native_54e735f08c731074_u32 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_0037EE70(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00 + 12) = 0x50000003u;
    LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EE70_ROLE00 += 16;
}


extern Rac2Native_54e735f08c731074_u32 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_0037EED0(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00 + 12) = 0x50000003u;
    LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EED0_ROLE00 += 16;
}


extern Rac2Native_54e735f08c731074_u32 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_0037EF30(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00 + 12) = 0x50000003u;
    LVL_22_DOBBO_ORBIT_F54e735f08c731074_AT0037EF30_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_3646a0ca5397f72d_u32;

typedef unsigned char Rac2Native_3646a0ca5397f72d_u8;


extern Rac2Native_3646a0ca5397f72d_u32 LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00;
extern Rac2Native_3646a0ca5397f72d_u8 LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE01[];

void LVL_22_DOBBO_ORBIT_FUN_0037EF98(void)
{
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00 + 0) = 0x3000000bu;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00 + 4) = (Rac2Native_3646a0ca5397f72d_u32)LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE01;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00 + 8) = 0;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00 + 12) = 0x5000000bu;
    LVL_22_DOBBO_ORBIT_F3646a0ca5397f72d_AT0037EF98_ROLE00 += 16;
}


extern int LVL_22_DOBBO_ORBIT_F57a827053efbe0c1_AT0042D218_ROLE00;

int LVL_22_DOBBO_ORBIT_FUN_0042D218(void)
{
    return LVL_22_DOBBO_ORBIT_F57a827053efbe0c1_AT0042D218_ROLE00;
}


/* Measured partial C views; original types and object ownership are unknown. */
typedef struct {
    unsigned char prefix[0x188];
    unsigned char wrapped;
    unsigned char value;
} QwenRecovery_538934d89776_WrapperCollectState132;



extern unsigned char LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE001[3];
extern int LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE000;
extern QwenRecovery_538934d89776_WrapperCollectState132 LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE003;
extern int LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE002(int words[2]);

void LVL_22_DOBBO_ORBIT_FUN_002DD2C8(void)
{
    int words[4];
    LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE002(words);
    if (LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE001[2] != 0) {
        LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE000 += words[0];
        if (LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE000 >= 256) {
            LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE003.wrapped = 1;
            LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE000 -= 255;
        } else {
            LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE003.wrapped = 0;
        }
        LVL_22_DOBBO_ORBIT_QWEN_538934d89776_AT002DD2C8_ROLE003.value = ((unsigned char *)words)[4];
    } else {
        words[0] = 0;
        words[1] = 0;
    }
}



/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned long QwenRecovery_339fe89f21bc_WrapperWaitMaskU64;



extern int LVL_22_DOBBO_ORBIT_QWEN_339fe89f21bc_AT0037EAE8_ROLE001 __attribute__((sda));
extern void LVL_22_DOBBO_ORBIT_QWEN_339fe89f21bc_AT0037EAE8_ROLE000(int ticks);

void LVL_22_DOBBO_ORBIT_FUN_0037EAE8(QwenRecovery_339fe89f21bc_WrapperWaitMaskU64 mask)
{
    while (LVL_22_DOBBO_ORBIT_QWEN_339fe89f21bc_AT0037EAE8_ROLE001 & mask)
        LVL_22_DOBBO_ORBIT_QWEN_339fe89f21bc_AT0037EAE8_ROLE000(0x400);
}

#ifndef RAC2_T_VEC_F6BF9CE42
#define RAC2_T_VEC_F6BF9CE42
typedef struct { float x; float y; } VEC_F6bf9ce42;
#endif


extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE478 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE47C;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE480;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE484;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE488 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE48C;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7340;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7344;
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_FUN_00321E90(int a, int b, int c, int d, int e);
extern int LVL_22_DOBBO_ORBIT_F6bf9ce42_FUN_002F64D0(int a, int b, int c, int d, int e, int f, int g);

void LVL_22_DOBBO_ORBIT_FUN_00439398(VEC_F6bf9ce42 **pobj)
{
    int s0, s1, s2, s3;
    int r;


    VEC_F6bf9ce42 *v;
    v = *pobj;
    s0 = (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE478 + v->x - (float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE488);
    s1 = (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE47C + v->y - (float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE48C);
    s3 = (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE480 + v->x + (float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE488);
    s2 = (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE484 + v->y + (float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE48C);

    r = LVL_22_DOBBO_ORBIT_F6bf9ce42_FUN_00321E90(0x60241700, 0x55F0C070, 20, 0, 0);
    LVL_22_DOBBO_ORBIT_F6bf9ce42_FUN_002F64D0(s0, s1, s3, s2, LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7340, LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7344, r);

    v = *pobj;
    LVL_22_DOBBO_ORBIT_F6bf9ce42_FUN_002F64D0((int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE478 + v->x), (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE47C + v->y),
            (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE480 + v->x), (int)((float)LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001AE484 + v->y),
            LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7340, LVL_22_DOBBO_ORBIT_F6bf9ce42_D_001A7344, 0x60241700);

}
extern char LVL_22_DOBBO_ORBIT_F9c1eb693_D_00189E20[];
extern float LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7FA4 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7F9C __attribute__((sda));

int LVL_22_DOBBO_ORBIT_FUN_002DC7A8(float *a0, float *a1, float *a2)
{
    char *p = LVL_22_DOBBO_ORBIT_F9c1eb693_D_00189E20;
    int v = *(int *)(p + 8852);

    if (v >= 98 && v <= 100) {
        if (a0) *a0 = *(float *)(p + 6316);
        if (a1) *a1 = LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7FA4 * 4.8481374506081920117140e-06f;
        if (a2) *a2 = LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7F9C * 2.9088824521750211715698e-04f;
        return 1;
    }
    if (v == 17) {
        if (a0) *a0 = *(float *)(p + 152);
        if (a1) *a1 = LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7FA4 * 1.4544411897077225148678e-05f;
        if (a2) *a2 = LVL_22_DOBBO_ORBIT_F9c1eb693_D_001A7F9C * 8.7266473565250635147095e-04f;
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_U32_FE8672EA5
#define RAC2_T_U32_FE8672EA5
typedef unsigned int u32_Fe8672ea5;
#endif


extern u32_Fe8672ea5 LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001B2730[];
extern u32_Fe8672ea5 LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001AC18C __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001AC190 __attribute__((sda));

extern void LVL_22_DOBBO_ORBIT_Fe8672ea5_FUN_002F3A48(void *target);

void LVL_22_DOBBO_ORBIT_FUN_0036A878(u32_Fe8672ea5 object)
{
    u32_Fe8672ea5 cursor = object + 40952;
    int i;

    LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001AC18C = object;
    for (i = 511; i >= 0; i--) {
        *(u32_Fe8672ea5 *)cursor = 0;
        cursor -= 80;
    }
    LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001AC190 = 1.0f;
    LVL_22_DOBBO_ORBIT_Fe8672ea5_FUN_002F3A48(LVL_22_DOBBO_ORBIT_Fe8672ea5_D_001B2730);
}
/* Family 8c659bbcffcd2ad3 -- 324 bytes, 27 level placements. */

#ifndef RAC2_T_BLOCK48_F8C659BBC
#define RAC2_T_BLOCK48_F8C659BBC
typedef struct { char pad[48]; } Block48_F8c659bbc;
#endif

#ifndef RAC2_T_BLOCK16_F8C659BBC
#define RAC2_T_BLOCK16_F8C659BBC
typedef struct { char pad[16]; } Block16_F8c659bbc;
#endif


extern char LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B1D90[] __attribute__((sda));
extern char LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9C80[];
extern char LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9EB0[];
extern char LVL_22_DOBBO_ORBIT_F8c659bbc_D_001A8E30 __attribute__((sda));

extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3AB0(char *a, char *b, char *c);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3D60(char *a, char *b, float f);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F42E0(char *a, char *b);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4628(char *a, char *b, char *c);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3BB0(char *a, char *b, char *c);
extern float LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3BC8(char *a);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00325B08(char *a, char *b, float f);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00323710(char *a, float f1, float f2, float f3, float f4);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00325B08(char *a, char *b, float f);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4848(char *a, char *b);
extern void LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4628(char *a, char *b, char *c);

void LVL_22_DOBBO_ORBIT_FUN_002F8B60(char *arg0, int arg1)
{
    Block48_F8c659bbc a;
    Block48_F8c659bbc b;
    Block48_F8c659bbc c;
    Block16_F8c659bbc d;
    Block16_F8c659bbc e;
    float v;

    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3AB0((char *)&e, LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9C80, LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B1D90);
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3D60((char *)&e, (char *)&e, 1.0f);
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F42E0((char *)&c, (char *)&LVL_22_DOBBO_ORBIT_F8c659bbc_D_001A8E30);
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4628((char *)&b, LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9C80 + 560, (char *)&c);
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3BB0((char *)&d, (char *)&b, (char *)&e);
    v = LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F3BC8((char *)&d) * 0.5f;
    if (arg1 != 0) {
        LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00325B08((char *)&d, (char *)&d, -v);
    } else {
        LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00323710(arg0, v, 5.8177649043500423431396e-04f,
                5.8177649043500423431396e-04f,
                5.2359886467456817626953e-02f);
        LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_00325B08((char *)&d, (char *)&d, -*(float *)arg0);
    }
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4848((char *)&d, (char *)&a);
    LVL_22_DOBBO_ORBIT_F8c659bbc_FUN_002F4628(LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9EB0, (char *)&a, LVL_22_DOBBO_ORBIT_F8c659bbc_D_001B9EB0);
}
#ifndef RAC2_T_F32_F7036EF03
#define RAC2_T_F32_F7036EF03
typedef float f32_F7036ef03;
#endif


extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4A8 __attribute__((sda));
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B0 __attribute__((sda));
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B8 __attribute__((sda));
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C0 __attribute__((sda));
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C8 __attribute__((sda));
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4AC;
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B4;
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4BC;
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C4;
extern f32_F7036ef03 LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4CC;

extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00439370(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00439968(void *a0);
extern void LVL_22_DOBBO_ORBIT_F7036ef03_FUN_004398F8(void *a0);
extern int LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00438CA8(void *a0, int a1);

void LVL_22_DOBBO_ORBIT_FUN_00439AC8(char *self, int arg)
{
    f32_F7036ef03 *v;
    char *sub = self + 664;

    v = *(f32_F7036ef03 **)(self + 648);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(self, LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4A8 + v[0], LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4AC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(self + 76, LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B0 + v[0], LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(self + 152, LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4B8 + v[0], LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4BC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_0042C160(self + 576, LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C0 + v[0], LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00439370(sub, LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4C8 + v[0], LVL_22_DOBBO_ORBIT_F7036ef03_D_001AE4CC + v[1]);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00439968(self);
    LVL_22_DOBBO_ORBIT_F7036ef03_FUN_004398F8(self);
    *(int *)(self + 416) = LVL_22_DOBBO_ORBIT_F7036ef03_FUN_00438CA8(sub, arg);
}
extern int LVL_22_DOBBO_ORBIT_F27b8017b_D_001ADC6C __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F27b8017b_D_001ADC70 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F27b8017b_FUN_002FF808(int a, int b);
extern int LVL_22_DOBBO_ORBIT_F27b8017b_FUN_002FFCD8(int a, int b, int c, int d, int e, int *p);

void LVL_22_DOBBO_ORBIT_FUN_0042CB50(int *obj)
{
    int tmp[4];
    float f;

    f = *(float *)obj[4];
    if (f == 0.0f)
        return;
    if (LVL_22_DOBBO_ORBIT_F27b8017b_D_001ADC6C != 0)
        *(int *)obj[3] = (*(int *)obj[3] & 0xff000000) | (LVL_22_DOBBO_ORBIT_F27b8017b_D_001ADC70 & 0x00ffffff);
    tmp[0] = *(int *)obj[3];
    tmp[1] = *(int *)obj[3];
    tmp[2] = *(int *)obj[3];
    tmp[3] = *(int *)obj[3];
    LVL_22_DOBBO_ORBIT_F27b8017b_FUN_002FFCD8(LVL_22_DOBBO_ORBIT_F27b8017b_FUN_002FF808((int)((float *)obj[13])[0], (int)((float *)obj[13])[1]),
             (int)((float *)obj[0])[0], (int)((float *)obj[0])[1],
             (int)((float *)obj[1])[0], (int)((float *)obj[1])[1], tmp);
}
extern void LVL_22_DOBBO_ORBIT_F67cf9b36_FUN_0042C160(char *p, float x, float y, float zero, float zero2);

extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E0 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E8 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F0 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F8 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E4;
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1EC;
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F4;
extern float LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1FC;

struct pos {
    float x;
    float y;
};

void LVL_22_DOBBO_ORBIT_FUN_00434FC8(char *self)
{
    float zero = 0.0f;

    LVL_22_DOBBO_ORBIT_F67cf9b36_FUN_0042C160(self + 1256, LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F8 + (*(struct pos **)(self + 680))->x,
            LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1FC + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F67cf9b36_FUN_0042C160(self + 1040, LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E0 + (*(struct pos **)(self + 680))->x,
            LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E4 + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F67cf9b36_FUN_0042C160(self + 1112, LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1E8 + (*(struct pos **)(self + 680))->x,
            LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1EC + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F67cf9b36_FUN_0042C160(self + 1184, LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F0 + (*(struct pos **)(self + 680))->x,
            LVL_22_DOBBO_ORBIT_F67cf9b36_D_001AE1F4 + (*(struct pos **)(self + 680))->y, zero, zero);
}
extern float LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE440 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE444;
extern float LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE448 __attribute__((sda));
extern void LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042C160(void *, float, float, float, float);
extern void LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042CC48(void *, int, int);
extern void LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042CB50(void *);

void LVL_22_DOBBO_ORBIT_FUN_00438998(int *p)
{
    int i;

    for (i = 0; i < p[95]; i++) {
        float *q = (float *)p[96];
        int v;

        LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042C160(p + 76, q[0] + LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE440,
                (q[1] + LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE444) + LVL_22_DOBBO_ORBIT_Ff0e326aa_D_001AE448 * (float)i, 0.0f, 0.0f);
        if (i == 3)
            v = 0xEA9E;
        else
            v = 0xEAA6;
        p[93] = v;
        LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042CC48(p + 76, v, ((int *)p[94])[i]);
        LVL_22_DOBBO_ORBIT_Ff0e326aa_FUN_0042CB50(p + 76);
    }
}
#ifndef RAC2_T_F32_FE833F09F
#define RAC2_T_F32_FE833F09F
typedef float f32_Fe833f09f;
#endif


extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE378 __attribute__((sda));
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE388 __attribute__((sda));
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE380 __attribute__((sda));
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE390 __attribute__((sda));
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE398 __attribute__((sda));
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE37C;
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE38C;
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE384;
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE394;
extern f32_Fe833f09f LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE39C;

extern void LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(void *a0, f32_Fe833f09f a1, f32_Fe833f09f a2, f32_Fe833f09f a3, f32_Fe833f09f a4);
extern void *LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C148(void *a0);
extern int LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00321E90(int a0, int a1, int a2, int a3, int a4);
extern void LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437B00(void *a0, int a1);
extern void LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437A90(void *a0);
extern void LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437AF8(void *a0);

int LVL_22_DOBBO_ORBIT_FUN_00437BF0(char *self, int arg1)
{
    f32_Fe833f09f *v;

    v = *(f32_Fe833f09f **)(self + 536);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(self, LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE378 + v[0], LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE37C + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(self + 152, LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE388 + v[0], LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE38C + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(self + 76, LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE380 + v[0], LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE384 + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(self + 228, LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE390 + v[0], LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE394 + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C160(self + 464, LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE398 + v[0], LVL_22_DOBBO_ORBIT_Fe833f09f_D_001AE39C + v[1], 0.0f, 0.0f);

    *(int *)LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_0042C148(self + 304) = LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00321E90(0x60442D00, 0x70FFFEED, 20, 0, 0);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437B00(self, arg1);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437A90(self);
    LVL_22_DOBBO_ORBIT_Fe833f09f_FUN_00437AF8(self);
    return *(int *)(self + (*(int *)(self + 764) << 2) + 440);
}
#ifndef RAC2_T_S32_FEE27D7BC
#define RAC2_T_S32_FEE27D7BC
typedef int s32_Fee27d7bc;
#endif

#ifndef RAC2_T_F32_FEE27D7BC
#define RAC2_T_F32_FEE27D7BC
typedef float f32_Fee27d7bc;
#endif


extern s32_Fee27d7bc LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042D168 (s32_Fee27d7bc, s32_Fee27d7bc);
extern s32_Fee27d7bc LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042D0D0 (s32_Fee27d7bc, s32_Fee27d7bc);
extern void LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_00430F08 (s32_Fee27d7bc, s32_Fee27d7bc, const void *);
extern void LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_00431360 (s32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc);
extern void LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C508 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern s32_Fee27d7bc LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C148 (s32_Fee27d7bc);
extern void LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C6B8 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern void LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042FAC8 (s32_Fee27d7bc);

extern char LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001ADF08[];
extern s32_Fee27d7bc LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001A904C;
extern s32_Fee27d7bc LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001ADEF8 __attribute__ ((sda));

void LVL_22_DOBBO_ORBIT_FUN_0042F960 (s32_Fee27d7bc self, s32_Fee27d7bc arg)
{
  s32_Fee27d7bc p;
  *(s32_Fee27d7bc *) self = arg;
  if (arg != 0)
    {
      p = LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042D0D0 (16, LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042D168 (arg, arg));
      *(s32_Fee27d7bc *) (self + 756) = p;
      ((s32_Fee27d7bc *) p)[1] = 0;
      ((s32_Fee27d7bc *) p)[2] = 0;
      ((s32_Fee27d7bc *) p)[3] = 0;
      ((s32_Fee27d7bc *) p)[0] = 0;
    }
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 756))[0] = 256.0f;
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 756))[1] = 212.0f;
  *(s32_Fee27d7bc *) (self + 760) = 0;
  LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_00430F08 (self + 8, arg, &LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001ADEF8);
  LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_00431360 (self + 8, 64.0f, -164.0f, 10.0f, 136.0f, 10.0f, 99.0f);
  LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C508 (self + 680, LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001ADF08, arg);
  p = LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C148 (self + 680);
  *(s32_Fee27d7bc *) p = 0x70FFFEED;
  LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042C6B8 (self + 680, LVL_22_DOBBO_ORBIT_Fee27d7bc_D_001A904C + 0x8710, 214);
  LVL_22_DOBBO_ORBIT_Fee27d7bc_FUN_0042FAC8 (self);
  *(s32_Fee27d7bc *) (self + 768) = 0;
}
#ifndef RAC2_T_S32_F09F721E0
#define RAC2_T_S32_F09F721E0
typedef int s32_F09f721e0;
#endif

#ifndef RAC2_T_F32_F09F721E0
#define RAC2_T_F32_F09F721E0
typedef float f32_F09f721e0;
#endif


extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_FUN_0042D168 (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_FUN_0042D0D0 (s32_F09f721e0, s32_F09f721e0);
extern void LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00430F08 (s32_F09f721e0, s32_F09f721e0, const void *);
extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (s32_F09f721e0);
extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (s32_F09f721e0);
extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (s32_F09f721e0);
extern void LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00431380 (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);
extern void LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00431360 (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);
extern void LVL_22_DOBBO_ORBIT_F09f721e0_FUN_004313D8 (s32_F09f721e0, f32_F09f721e0);
extern void LVL_22_DOBBO_ORBIT_F09f721e0_FUN_004321C8 (s32_F09f721e0, s32_F09f721e0);

extern s32_F09f721e0 LVL_22_DOBBO_ORBIT_F09f721e0_D_001AE040 __attribute__ ((sda));

void LVL_22_DOBBO_ORBIT_FUN_004320A0 (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 q;
  s32_F09f721e0 p;
  s32_F09f721e0 a, b;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      p = LVL_22_DOBBO_ORBIT_F09f721e0_FUN_0042D0D0 (16, LVL_22_DOBBO_ORBIT_F09f721e0_FUN_0042D168 (arg, arg));
      *(s32_F09f721e0 *) (self + 684) = p;
      ((s32_F09f721e0 *) p)[1] = 0;
      ((s32_F09f721e0 *) p)[2] = 0;
      ((s32_F09f721e0 *) p)[3] = 0;
      ((s32_F09f721e0 *) p)[0] = 0;
    }
  q = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[1] = 195.0f;
  LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00430F08 (q, arg, &LVL_22_DOBBO_ORBIT_F09f721e0_D_001AE040);
  a = LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (12773);
  b = LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (11598);
  LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00431380 (q, a, b, LVL_22_DOBBO_ORBIT_F09f721e0_FUN_002F9FF8 (11599));
  LVL_22_DOBBO_ORBIT_F09f721e0_FUN_00431360 (q, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
  LVL_22_DOBBO_ORBIT_F09f721e0_FUN_004313D8 (q, 0.65f);
  *(s32_F09f721e0 *) (self + 680) = 0;
  *(s32_F09f721e0 *) (q + 668) = 0;
  LVL_22_DOBBO_ORBIT_F09f721e0_FUN_004321C8 (self, 0);
}
#ifndef RAC2_T_U8_FE9770B1E
#define RAC2_T_U8_FE9770B1E
typedef unsigned char u8_Fe9770b1e;
#endif

#ifndef RAC2_T_S32_FE9770B1E
#define RAC2_T_S32_FE9770B1E
typedef int s32_Fe9770b1e;
#endif

#ifndef RAC2_T_F32_FE9770B1E
#define RAC2_T_F32_FE9770B1E
typedef float f32_Fe9770b1e;
#endif


/* Resident shared table reached through $gp (small-data symbol). */
extern f32_Fe9770b1e LVL_22_DOBBO_ORBIT_Fe9770b1e_D_001AE0B8[2] __attribute__((sda));

extern void *LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_0042D168(void *);
extern void *LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_0042D0D0(s32_Fe9770b1e, void *);
extern void LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00430F08(u8_Fe9770b1e *, void *, f32_Fe9770b1e *);
extern void *LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_002F9FF8(s32_Fe9770b1e);
extern void LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00431380(u8_Fe9770b1e *, void *, void *, void *);
extern void LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00431360(u8_Fe9770b1e *, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e);
extern void LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_004313D8(u8_Fe9770b1e *, f32_Fe9770b1e);
extern void LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00432E48(u8_Fe9770b1e *, s32_Fe9770b1e);

void LVL_22_DOBBO_ORBIT_FUN_00432D20(u8_Fe9770b1e *self, void *arg) {
    u8_Fe9770b1e *sub;
    void *first, *second, *third;
    *(void **)self = arg;
    if (arg != 0) {
        void *t = LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_0042D168(arg);
        void *p = LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_0042D0D0(16, t);
        *(void **)(self + 684) = p;
        ((s32_Fe9770b1e *)p)[1] = 0;
        ((s32_Fe9770b1e *)p)[2] = 0;
        ((s32_Fe9770b1e *)p)[3] = 0;
        ((s32_Fe9770b1e *)p)[0] = 0;
    }
    sub = self + 8;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[1] = 195.0f;
    LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00430F08(sub, arg, LVL_22_DOBBO_ORBIT_Fe9770b1e_D_001AE0B8);
    first = LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_002F9FF8(11667);
    second = LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_002F9FF8(11598);
    third = LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_002F9FF8(11599);
    LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00431380(sub, first, second, third);
    LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00431360(sub, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_004313D8(sub, 0.2f);
    *(s32_Fe9770b1e *)(self + 680) = 0;
    LVL_22_DOBBO_ORBIT_Fe9770b1e_FUN_00432E48(self, 0);
}
#ifndef RAC2_T_U8_FF4EB83C9
#define RAC2_T_U8_FF4EB83C9
typedef unsigned char u8_Ff4eb83c9;
#endif

#ifndef RAC2_T_S32_FF4EB83C9
#define RAC2_T_S32_FF4EB83C9
typedef int s32_Ff4eb83c9;
#endif

#ifndef RAC2_T_F32_FF4EB83C9
#define RAC2_T_F32_FF4EB83C9
typedef float f32_Ff4eb83c9;
#endif


/* Resident shared table reached through $gp (small-data symbol). */
extern f32_Ff4eb83c9 LVL_22_DOBBO_ORBIT_Ff4eb83c9_D_001AE070[2] __attribute__((sda));

extern void *LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_0042D168(void *);
extern void *LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_0042D0D0(s32_Ff4eb83c9, void *);
extern void LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00430F08(u8_Ff4eb83c9 *, void *, f32_Ff4eb83c9 *);
extern void *LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_002F9FF8(s32_Ff4eb83c9);
extern void LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00431380(u8_Ff4eb83c9 *, void *, void *, void *);
extern void LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00431360(u8_Ff4eb83c9 *, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9);
extern void LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_004313D8(u8_Ff4eb83c9 *, f32_Ff4eb83c9);
extern void LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_004328C0(u8_Ff4eb83c9 *, s32_Ff4eb83c9);

void LVL_22_DOBBO_ORBIT_FUN_00432798(u8_Ff4eb83c9 *self, void *arg) {
    u8_Ff4eb83c9 *sub;
    void *first, *second, *third;
    *(void **)self = arg;
    if (arg != 0) {
        void *t = LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_0042D168(arg);
        void *p = LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_0042D0D0(16, t);
        *(void **)(self + 684) = p;
        ((s32_Ff4eb83c9 *)p)[1] = 0;
        ((s32_Ff4eb83c9 *)p)[2] = 0;
        ((s32_Ff4eb83c9 *)p)[3] = 0;
        ((s32_Ff4eb83c9 *)p)[0] = 0;
    }
    sub = self + 8;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[1] = 195.0f;
    LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00430F08(sub, arg, LVL_22_DOBBO_ORBIT_Ff4eb83c9_D_001AE070);
    first = LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_002F9FF8(11672);
    second = LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_002F9FF8(11598);
    third = LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_002F9FF8(11599);
    LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00431380(sub, first, second, third);
    LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_00431360(sub, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_004313D8(sub, 0.65f);
    *(s32_Ff4eb83c9 *)(self + 680) = 0;
    LVL_22_DOBBO_ORBIT_Ff4eb83c9_FUN_004328C0(self, 0);
}
extern void LVL_22_DOBBO_ORBIT_F54dfe946_FUN_0042C160(char *p, float x, float y, float zero, float zero2);

extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE540 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE548 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE550 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE558 __attribute__((sda));
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE544;
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE54C;
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE554;
extern float LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE55C;

struct pos54dfe946 {
    float x;
    float y;
};

void LVL_22_DOBBO_ORBIT_FUN_0043AB78(char *self)
{
    float zero = 0.0f;

    LVL_22_DOBBO_ORBIT_F54dfe946_FUN_0042C160(self + 808, LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE540 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE544 + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F54dfe946_FUN_0042C160(self + 880, LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE548 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE54C + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F54dfe946_FUN_0042C160(self + 952, LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE550 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE554 + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_22_DOBBO_ORBIT_F54dfe946_FUN_0042C160(self + 736, LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE558 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_22_DOBBO_ORBIT_F54dfe946_D_001AE55C + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
}
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_D_00138344[4];
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF14[4] __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF10 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF18 __attribute__((sda));

extern void LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00431348(char *, float, float);
extern void LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00431158(char *);
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00321E90(int, int, int, int, int);
extern void *LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_0042C148(char *);
extern int LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00321E90(int, int, int, int, int);
extern void LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_0042C160(char *, float, float, float, float);

int LVL_22_DOBBO_ORBIT_FUN_0042FBD8(char *p)
{
    char *a = p + 8;
    char *b;
    void *r;
    float x;
    float y;

    LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00431348(a, ((float *)(*(int *)(p + 756)))[0], ((float *)(*(int *)(p + 756)))[1]);
    LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00431158(a);
    if (LVL_22_DOBBO_ORBIT_Fa769c0f9_D_00138344[0] & 0x5000)
        LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00321E90(0, 0, 1, 0, 1);
    b = p + 680;
    r = LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_0042C148(b);
    *(int *)r = LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_00321E90(0x60442D00, 0x70FFFEED, 20, 0, 0);
    x = ((float *)(*(int *)(p + 756)))[0] + (float)LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF10;
    y = ((float *)(*(int *)(p + 756)))[1]
        + (float)(*(int *)(p + 760) * LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF18);
    y = y + (float)LVL_22_DOBBO_ORBIT_Fa769c0f9_D_001ADF14[0];
    LVL_22_DOBBO_ORBIT_Fa769c0f9_FUN_0042C160(b, x, y, 0.0f, 0.0f);
    return 0;
}
extern unsigned char LVL_22_DOBBO_ORBIT_F65feeb52_D_001A7A0A;
extern int LVL_22_DOBBO_ORBIT_F65feeb52_D_001A79F0 __attribute__((sda));
extern int LVL_22_DOBBO_ORBIT_F65feeb52_FUN_002E9CE8(int, int);

int LVL_22_DOBBO_ORBIT_FUN_002E9D90(int x)
{
    int b = LVL_22_DOBBO_ORBIT_F65feeb52_D_001A7A0A;
    int q;
    int v;

    if (b == 0) {
        q = LVL_22_DOBBO_ORBIT_F65feeb52_FUN_002E9CE8(LVL_22_DOBBO_ORBIT_F65feeb52_D_001A79F0, x) / 100;
        v = 3 - q;
        return b < v ? v : 1;
    }
    return 3;
}
