/* One measured small-data body. The retail writes the ring header fields and
   then advances the resident pointer itself, which the pinned -G0 profile
   cannot express: the last store addresses the global through $gp. This unit
   is compiled with the qualified small-data profile instead, so the body stays
   ordinary C and no byte is patched. */
extern int *D_1B3188;
extern int D_1A742C;

void LVL_19_GRELBIN_FUN_002EDDF0(void)
{
    *(int *)D_1B3188 = 0x30000009;
    *(int *)((char *)D_1B3188 + 4) = (D_1A742C + 192) & 0x0FFFFFFF;
    *(int *)((char *)D_1B3188 + 8) = 0;
    *(int *)((char *)D_1B3188 + 12) = 0x50000009;
    D_1B3188 = (int *)((char *)D_1B3188 + 16);
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout;


extern Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00;
extern int LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE01;
extern int LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE02;

void LVL_19_GRELBIN_FUN_00307128(void)
{
    LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE01 &= ~0x20;
    if (LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00.mode_08 != 2)
        return;
    if (LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00.selector_10 == 0) {
        LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE02 = 9;
        return;
    }
    if (LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00.selector_10 == -1) {
        LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00.selector_10 = 0;
        LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE02 = 9;
        return;
    }
    if (LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE00.selector_10 == -2)
        LVL_19_GRELBIN_F8172b0f0a91a7cba_AT00307128_ROLE02 = 5;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout;


extern Rac2Native_b09e58bdde03cd06_SDataRootMarker76Layout LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE02;
extern int LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE00;
extern int LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE03;
extern int LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE01;

void LVL_19_GRELBIN_FUN_00307198(void)
{
    if (LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE02.selector_10 != -2) {
        LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE03 = 3;
        return;
    }
    if (LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE01 != 0 || (LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE00 & 2) != 0)
        LVL_19_GRELBIN_Fb09e58bdde03cd06_AT00307198_ROLE03 = 6;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout;


extern Rac2Native_584c3844a02fd1eb_SDataBranch124RootLayout LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE02;
extern unsigned int LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE00;
extern int LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE03;
extern int LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE01;

void LVL_19_GRELBIN_FUN_003071E8(void)
{
    if (LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE02.selector_10 != -2) {
        LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE03 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE00 & 0x20u) != 0) {
        LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE00 ^= 0x20u;
        if (LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE01 != 0)
            LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE03 = 23;
        else
            LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE03 = 5;
        return;
    }
    if ((LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE00 & 0x8u) != 0) {
        LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE00 ^= 0x8u;
        LVL_19_GRELBIN_F584c3844a02fd1eb_AT003071E8_ROLE03 = 7;
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


extern Rac2Native_a661193cb7db1192_SDataAccessorRootReset44Layout LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE00;
extern int LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE01;

void LVL_19_GRELBIN_FUN_00307268(void)
{
    LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE00.selector_10 = 0;
    if (LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE00.selected_164 < 0) {
        LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE00.value_168 = 0;
        LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE00.selected_164 = 3;
    }
    LVL_19_GRELBIN_Fa661193cb7db1192_AT00307268_ROLE01 = 8;
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


extern Rac2Native_1716667661d8e672_SDataMoreGuard96Layout LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE00;
extern unsigned int LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE01;
extern int LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE02;

void LVL_19_GRELBIN_FUN_00307298(void)
{
    if (LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE00.mode_15c != 2 || LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE00.selected_164 >= 0)
        return;
    if (LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE00.extra_16c != 0) {
        LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE02 = 17;
        LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE01 |= 0x40u;
        return;
    }
    LVL_19_GRELBIN_F1716667661d8e672_AT00307298_ROLE02 = 14;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout;


extern Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE01;
extern unsigned int LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE00;
extern int LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE02;

void LVL_19_GRELBIN_FUN_003072F8(void)
{
    if (LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE01.selector_10 != 0) {
        LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE02 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE00 & 6u) != 0) {
        LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE02 = 10;
        return;
    }
    if ((LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE00 & 0x200u) != 0)
        LVL_19_GRELBIN_F715e9b46a377ec8c_AT003072F8_ROLE02 = 25;
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


extern Rac2Native_99b76d48da369e8d_SDataMoreThreshold156Layout LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00;
extern int LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01;

void LVL_19_GRELBIN_FUN_00307388(void)
{
    short phase;
    if (LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.mode_15c != 2 || LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.selected_164 >= 0)
        return;
    if (LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.extra_16c != 0) {
        LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01 = 12;
        return;
    }
    if (LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.selector_10 < -1) {
        LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01 = 3;
        return;
    }
    phase = LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.phase_18;
    if (phase == -2) {
        if (LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.value_0c + LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE00.value_20 < 475)
            LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01 = 19;
        else
            LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01 = 12;
        return;
    }
    if (phase >= -1)
        LVL_19_GRELBIN_F99b76d48da369e8d_AT00307388_ROLE01 = 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout;


extern Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE01;
extern int LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE00;
extern int LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE02;

void LVL_19_GRELBIN_FUN_00307428(void)
{
    if (LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE01.selector_10 != 0) {
        LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE02 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE00 & 2) != 0)
        LVL_19_GRELBIN_Fa0e246aa2dc0b8e7_AT00307428_ROLE02 = 13;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout;


extern Rac2Native_998ff33d7f808dbf_SDataBranch120RootLayout LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE02;
extern unsigned int LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE00;
extern int LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE03;
extern int LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE01;

void LVL_19_GRELBIN_FUN_00307460(void)
{
    if (LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE02.selector_10 != 0) {
        LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE03 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE00 & 0x20u) != 0) {
        LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE00 ^= 0x20u;
        if (LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE01 != 0)
            LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE03 = 24;
        else
            LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE03 = 12;
        return;
    }
    if ((LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE00 & 0x10u) != 0) {
        LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE00 ^= 0x10u;
        LVL_19_GRELBIN_F998ff33d7f808dbf_AT00307460_ROLE03 = 14;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout {
    unsigned char unknown_00[0x10];
    int selector_10;
    unsigned char unknown_14[0x168];
    int value_17c;
} Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout;


extern Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE00;
extern int LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01;
extern int LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE02;

void LVL_19_GRELBIN_FUN_00307590(void)
{
    if ((LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 & 4) != 0)
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 &= ~4;
    if ((LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 & 2) != 0)
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 &= ~2;
    if ((LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 & 0x80) != 0) {
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE02 = 21;
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 = (LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 ^ 0x80) | 0x40;
        return;
    }
    if ((LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 & 0x100) != 0) {
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE02 = 20;
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 = (LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE01 ^ 0x100) | 0x40;
        return;
    }
    if (LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE00.selector_10 != 0) {
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE02 = 3;
        return;
    }
    if (LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE00.value_17c != 0)
        LVL_19_GRELBIN_F60904fd170c92806_AT00307590_ROLE02 = 1;
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


extern Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00;
extern unsigned int LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE01;
extern int LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE02;

void LVL_19_GRELBIN_FUN_00307708(void)
{
    if (LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.mode_15c != 2 || LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.selected_164 >= 0)
        return;
    if (LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.extra_16c != 0 || LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.word_24 != 0) {
        LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.value_17c = 0;
        LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE02 = 21;
        LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE01 |= 0x440u;
        return;
    }
    LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE00.value_17c = 1;
    LVL_19_GRELBIN_F8391b53329533f81_AT00307708_ROLE02 = 1;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout;


extern Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE01;
extern int LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE00;
extern int LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE02;

void LVL_19_GRELBIN_FUN_00307880(void)
{
    if (LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE01.selector_10 != -2) {
        LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE02 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE00 & 0x20) != 0) {
        LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE00 ^= 0x20;
        LVL_19_GRELBIN_F83cf4a65b6159c6c_AT00307880_ROLE02 = 5;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_25b7bae55e05d925_SDataRootClear68Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_25b7bae55e05d925_SDataRootClear68Layout;


extern Rac2Native_25b7bae55e05d925_SDataRootClear68Layout LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE01;
extern int LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE00;
extern int LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE02;

void LVL_19_GRELBIN_FUN_003078C8(void)
{
    if (LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE01.selector_10 != 0) {
        LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE02 = 3;
        return;
    }
    if ((LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE00 & 0x20) != 0) {
        LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE00 ^= 0x20;
        LVL_19_GRELBIN_F25b7bae55e05d925_AT003078C8_ROLE02 = 12;
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


extern int LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE02;
extern void LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE03(void *owner, void *payload, int count);
extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE01(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);
extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE00(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);

Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags LVL_19_GRELBIN_FUN_00324CF0(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context)
{
    Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags result = 0;
    if (context->enabled == 1 && context->count != 0)
        LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE03(owner, context->payload, context->count);
    switch (context->kind) {
    case 0:
    case 1:
    case 2:
        if (LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE02 == 0)
            result = LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE01(owner, context);
        else
            result = LVL_19_GRELBIN_Fbf55aa2a4d0dd351_AT00324CF0_ROLE00(owner, context);
        break;
    default:
        break;
    }
    if ((result & 2) != 0) context->enabled = 0;
    return result;
}


extern int LVL_19_GRELBIN_F4ccf861671c28be2_AT002A7600_ROLE00;

int LVL_19_GRELBIN_FUN_002A7600(void)
{
    return LVL_19_GRELBIN_F4ccf861671c28be2_AT002A7600_ROLE00;
}


extern float LVL_19_GRELBIN_Fb4ab5917cc7e0e71_AT002D53E0_ROLE00;

void LVL_19_GRELBIN_FUN_002D53E0(float value)
{
    LVL_19_GRELBIN_Fb4ab5917cc7e0e71_AT002D53E0_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_967caba148c0b35c_u32;


extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE00;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE01;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE04;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE05;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE06;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE07;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE08;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE09;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE10;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE11;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE02;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE03;
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE12 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE13 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE14 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE15;

void LVL_19_GRELBIN_FUN_002E30D0(void)
{
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE00 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE01 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE04 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE05 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE06 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE07 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE08 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE09 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE12 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE13 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE14 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE10 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE11 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE02 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE03 = 0;
    LVL_19_GRELBIN_F967caba148c0b35c_AT002E30D0_ROLE15 = 0;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_73f23b7222fbc541_u32;

typedef unsigned char Rac2Native_73f23b7222fbc541_u8;


extern Rac2Native_73f23b7222fbc541_u32 LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00;
extern Rac2Native_73f23b7222fbc541_u8 LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE01[];

void LVL_19_GRELBIN_FUN_002EE108(void)
{
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00 + 0) = 0x30000026u;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00 + 4) = (Rac2Native_73f23b7222fbc541_u32)LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE01;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00 + 8) = 0;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00 + 12) = 0x50000026u;
    LVL_19_GRELBIN_F73f23b7222fbc541_AT002EE108_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_571a3580c10e935f_u32;

typedef unsigned char Rac2Native_571a3580c10e935f_u8;


extern Rac2Native_571a3580c10e935f_u32 LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00;
extern Rac2Native_571a3580c10e935f_u8 LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE01[];

void LVL_19_GRELBIN_FUN_002EE168(void)
{
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00 + 0) = 0x30000029u;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00 + 4) = (Rac2Native_571a3580c10e935f_u32)LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE01;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00 + 8) = 0;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00 + 12) = 0x50000029u;
    LVL_19_GRELBIN_F571a3580c10e935f_AT002EE168_ROLE00 += 16;
}


extern int LVL_19_GRELBIN_Fce2e52e5b0780004_AT002EE5E0_ROLE00;

int LVL_19_GRELBIN_FUN_002EE5E0(void)
{
    return LVL_19_GRELBIN_Fce2e52e5b0780004_AT002EE5E0_ROLE00;
}


extern int LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE00 __attribute__((sda));
extern int LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE01 __attribute__((sda));
extern int LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE02 __attribute__((sda));
extern int LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE03;

void LVL_19_GRELBIN_FUN_002EE658(int first, int second, int third, int fourth)
{
    LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE00 = first;
    LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE01 = second;
    LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE02 = third;
    LVL_19_GRELBIN_F53dbeb99ca77d218_AT002EE658_ROLE03 = fourth;
}


extern int LVL_19_GRELBIN_F94af54270be5f5c3_AT002F0C90_ROLE00;

void LVL_19_GRELBIN_FUN_002F0C90(void)
{
    LVL_19_GRELBIN_F94af54270be5f5c3_AT002F0C90_ROLE00 = 3;
}


extern int LVL_19_GRELBIN_Fde7724c328f7c2d0_AT002F0CC0_ROLE00;

int LVL_19_GRELBIN_FUN_002F0CC0(void)
{
    return LVL_19_GRELBIN_Fde7724c328f7c2d0_AT002F0CC0_ROLE00;
}


extern int LVL_19_GRELBIN_F61acb1f304b382c7_AT002F0CC8_ROLE00;

void LVL_19_GRELBIN_FUN_002F0CC8(void)
{
    LVL_19_GRELBIN_F61acb1f304b382c7_AT002F0CC8_ROLE00 = 1;
}


extern int LVL_19_GRELBIN_Ff0259c87ab6a3193_AT002F0CD8_ROLE00;

void LVL_19_GRELBIN_FUN_002F0CD8(void)
{
    LVL_19_GRELBIN_Ff0259c87ab6a3193_AT002F0CD8_ROLE00 = 0;
}


extern int LVL_19_GRELBIN_F4a91c582a7608c02_AT002F1BD0_ROLE00 __attribute__((sda));

int LVL_19_GRELBIN_FUN_002F1BD0(void)
{
    return LVL_19_GRELBIN_F4a91c582a7608c02_AT002F1BD0_ROLE00 != 0;
}


extern int LVL_19_GRELBIN_F3abdbc5b6ec93b02_AT002F1CA0_ROLE00;

void LVL_19_GRELBIN_FUN_002F1CA0(void)
{
    LVL_19_GRELBIN_F3abdbc5b6ec93b02_AT002F1CA0_ROLE00 = 0;
}


extern int LVL_19_GRELBIN_F4bf2f2e615420e28_AT002F1CA8_ROLE00;

void LVL_19_GRELBIN_FUN_002F1CA8(void)
{
    LVL_19_GRELBIN_F4bf2f2e615420e28_AT002F1CA8_ROLE00 = 1;
}


extern int LVL_19_GRELBIN_Fa14de9886d500a76_AT002F1CB8_ROLE00;

int LVL_19_GRELBIN_FUN_002F1CB8(void)
{
    return LVL_19_GRELBIN_Fa14de9886d500a76_AT002F1CB8_ROLE00;
}


extern unsigned int LVL_19_GRELBIN_F2f9bdf3d0ed77d09_AT002F75F0_ROLE00 __attribute__((sda));

void LVL_19_GRELBIN_FUN_002F75F0(void)
{
    if (LVL_19_GRELBIN_F2f9bdf3d0ed77d09_AT002F75F0_ROLE00 != 0)
        --LVL_19_GRELBIN_F2f9bdf3d0ed77d09_AT002F75F0_ROLE00;
}


extern int LVL_19_GRELBIN_F6fc8969f33895bc4_AT002F9820_ROLE00;

void LVL_19_GRELBIN_FUN_002F9820(void)
{
    LVL_19_GRELBIN_F6fc8969f33895bc4_AT002F9820_ROLE00 = 1;
}


extern int LVL_19_GRELBIN_Fef45f15dfb57feb2_AT002F98C8_ROLE00;

void LVL_19_GRELBIN_FUN_002F98C8(void)
{
    LVL_19_GRELBIN_Fef45f15dfb57feb2_AT002F98C8_ROLE00 = 1;
}


extern int LVL_19_GRELBIN_Fd010ae7fd1640d51_AT002F98D8_ROLE00;

int LVL_19_GRELBIN_FUN_002F98D8(void)
{
    return LVL_19_GRELBIN_Fd010ae7fd1640d51_AT002F98D8_ROLE00;
}


extern int LVL_19_GRELBIN_Fa91295fd1429c8b1_AT002F98E0_ROLE00;

void LVL_19_GRELBIN_FUN_002F98E0(void)
{
    LVL_19_GRELBIN_Fa91295fd1429c8b1_AT002F98E0_ROLE00 = 0;
}


extern int LVL_19_GRELBIN_F30af8d5282429011_AT002F98E8_ROLE00;

void LVL_19_GRELBIN_FUN_002F98E8(void)
{
    LVL_19_GRELBIN_F30af8d5282429011_AT002F98E8_ROLE00 = 0;
}


extern int LVL_19_GRELBIN_F25c092d72a2ed8c8_AT002F98F0_ROLE00 __attribute__((sda));

void LVL_19_GRELBIN_FUN_002F98F0(void)
{
    if (LVL_19_GRELBIN_F25c092d72a2ed8c8_AT002F98F0_ROLE00 == 0)
        LVL_19_GRELBIN_F25c092d72a2ed8c8_AT002F98F0_ROLE00 = 1;
}


extern int LVL_19_GRELBIN_Fb0b88cda64ac44b6_AT002F9908_ROLE00 __attribute__((sda));

int LVL_19_GRELBIN_FUN_002F9908(void)
{
    return LVL_19_GRELBIN_Fb0b88cda64ac44b6_AT002F9908_ROLE00 == 3;
}


extern int LVL_19_GRELBIN_F407105421407f332_AT0030A948_ROLE00;

void LVL_19_GRELBIN_FUN_0030A948(void)
{
    LVL_19_GRELBIN_F407105421407f332_AT0030A948_ROLE00 = -1;
}


extern int LVL_19_GRELBIN_Fa077d83e809ad7db_AT0030FC48_ROLE01;
extern unsigned char LVL_19_GRELBIN_Fa077d83e809ad7db_AT0030FC48_ROLE00[];

void LVL_19_GRELBIN_FUN_0030FC48(unsigned int index)
{
    if (index != 255u)
        LVL_19_GRELBIN_Fa077d83e809ad7db_AT0030FC48_ROLE00[index + (unsigned int)LVL_19_GRELBIN_Fa077d83e809ad7db_AT0030FC48_ROLE01 * 16u] |= 0x80u;
}


extern int LVL_19_GRELBIN_Fe44fc83bd69b4f14_AT00328068_ROLE00 __attribute__((sda));

int LVL_19_GRELBIN_FUN_00328068(void)
{
    return LVL_19_GRELBIN_Fe44fc83bd69b4f14_AT00328068_ROLE00 > 0;
}


extern int LVL_19_GRELBIN_F36a7237a316225ca_AT00328078_ROLE00;

void LVL_19_GRELBIN_FUN_00328078(int value)
{
    LVL_19_GRELBIN_F36a7237a316225ca_AT00328078_ROLE00 = value;
}


extern int LVL_19_GRELBIN_Fcbf196edf2a6cc29_AT00328080_ROLE00 __attribute__((sda));

void LVL_19_GRELBIN_FUN_00328080(void)
{
    int value = (int)((unsigned int)LVL_19_GRELBIN_Fcbf196edf2a6cc29_AT00328080_ROLE00 - 1u);
    LVL_19_GRELBIN_Fcbf196edf2a6cc29_AT00328080_ROLE00 = value;
    if (value < 0)
        LVL_19_GRELBIN_Fcbf196edf2a6cc29_AT00328080_ROLE00 = 0;
}


extern int LVL_19_GRELBIN_Fe6fa55215bad26dd_AT003280A0_ROLE00;

void LVL_19_GRELBIN_FUN_003280A0(int value)
{
    LVL_19_GRELBIN_Fe6fa55215bad26dd_AT003280A0_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_4e44694cc39e7084_u32;


extern Rac2Native_4e44694cc39e7084_u32 LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00;

void LVL_19_GRELBIN_FUN_00379408(Rac2Native_4e44694cc39e7084_u32 data_address, Rac2Native_4e44694cc39e7084_u32 tag_bits)
{
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00 + 0) = tag_bits | 0x30000000u;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00 + 4) = data_address;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00 + 8) = 0;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00 + 12) = 0;
    LVL_19_GRELBIN_F4e44694cc39e7084_AT00379408_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ae24050903bcaa08_u32;


extern Rac2Native_ae24050903bcaa08_u32 LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00;

void LVL_19_GRELBIN_FUN_00379510(Rac2Native_ae24050903bcaa08_u32 final_word)
{
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00 + 0) = 0x10000000u;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00 + 4) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00 + 8) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00 + 12) = final_word;
    LVL_19_GRELBIN_Fae24050903bcaa08_AT00379510_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_9da4b6b15b3cf4a0_RecordWord180;

typedef unsigned long long Rac2Native_9da4b6b15b3cf4a0_RecordValue180;


extern Rac2Native_9da4b6b15b3cf4a0_RecordWord180 LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00;

void LVL_19_GRELBIN_FUN_00379558(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 final_word, Rac2Native_9da4b6b15b3cf4a0_RecordValue180 value)
{
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 0) = 0x10000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 4) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 8) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 12) = 0x50000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 16) = 0x8001u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 20) = 0x10000000u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 24) = 0x0eu;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 28) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordValue180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 32) = value;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 40) = final_word;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 + 44) = 0;
    LVL_19_GRELBIN_F9da4b6b15b3cf4a0_AT00379558_ROLE00 += 48;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_54e735f08c731074_u32;

typedef unsigned char Rac2Native_54e735f08c731074_u8;


extern Rac2Native_54e735f08c731074_u32 LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE01[];

void LVL_19_GRELBIN_FUN_00379848(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00 + 12) = 0x50000003u;
    LVL_19_GRELBIN_F54e735f08c731074_AT00379848_ROLE00 += 16;
}


extern Rac2Native_54e735f08c731074_u32 LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE01[];

void LVL_19_GRELBIN_FUN_003798A8(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00 + 12) = 0x50000003u;
    LVL_19_GRELBIN_F54e735f08c731074_AT003798A8_ROLE00 += 16;
}


extern Rac2Native_54e735f08c731074_u32 LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00;
extern Rac2Native_54e735f08c731074_u8 LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE01[];

void LVL_19_GRELBIN_FUN_00379908(void)
{
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00 + 4) = (Rac2Native_54e735f08c731074_u32)LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE01;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00 + 8) = 0;
    *(Rac2Native_54e735f08c731074_u32 *)(LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00 + 12) = 0x50000003u;
    LVL_19_GRELBIN_F54e735f08c731074_AT00379908_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_3646a0ca5397f72d_u32;

typedef unsigned char Rac2Native_3646a0ca5397f72d_u8;


extern Rac2Native_3646a0ca5397f72d_u32 LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00;
extern Rac2Native_3646a0ca5397f72d_u8 LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE01[];

void LVL_19_GRELBIN_FUN_00379970(void)
{
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00 + 0) = 0x3000000bu;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00 + 4) = (Rac2Native_3646a0ca5397f72d_u32)LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE01;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00 + 8) = 0;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00 + 12) = 0x5000000bu;
    LVL_19_GRELBIN_F3646a0ca5397f72d_AT00379970_ROLE00 += 16;
}


extern float LVL_19_GRELBIN_F4b98cfe0dd4b2c6f_AT0037C7C0_ROLE00;

float LVL_19_GRELBIN_FUN_0037C7C0(void)
{
    return LVL_19_GRELBIN_F4b98cfe0dd4b2c6f_AT0037C7C0_ROLE00;
}


extern int LVL_19_GRELBIN_F57a827053efbe0c1_AT0043DBC0_ROLE00;

int LVL_19_GRELBIN_FUN_0043DBC0(void)
{
    return LVL_19_GRELBIN_F57a827053efbe0c1_AT0043DBC0_ROLE00;
}


/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned long QwenRecovery_339fe89f21bc_WrapperWaitMaskU64;



extern int LVL_19_GRELBIN_QWEN_339fe89f21bc_AT003793B8_ROLE001 __attribute__((sda));
extern void LVL_19_GRELBIN_QWEN_339fe89f21bc_AT003793B8_ROLE000(int ticks);

void LVL_19_GRELBIN_FUN_003793B8(QwenRecovery_339fe89f21bc_WrapperWaitMaskU64 mask)
{
    while (LVL_19_GRELBIN_QWEN_339fe89f21bc_AT003793B8_ROLE001 & mask)
        LVL_19_GRELBIN_QWEN_339fe89f21bc_AT003793B8_ROLE000(0x400);
}

#ifndef RAC2_T_VEC_F6BF9CE42
#define RAC2_T_VEC_F6BF9CE42
typedef struct { float x; float y; } VEC_F6bf9ce42;
#endif


extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE478 __attribute__((sda));
extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE47C;
extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE480;
extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE484;
extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE488 __attribute__((sda));
extern int LVL_19_GRELBIN_F6bf9ce42_D_001AE48C;
extern int LVL_19_GRELBIN_F6bf9ce42_D_001A7340;
extern int LVL_19_GRELBIN_F6bf9ce42_D_001A7344;
extern int LVL_19_GRELBIN_F6bf9ce42_FUN_0031A810(int a, int b, int c, int d, int e);
extern int LVL_19_GRELBIN_F6bf9ce42_FUN_002EE378(int a, int b, int c, int d, int e, int f, int g);

void LVL_19_GRELBIN_FUN_00449D40(VEC_F6bf9ce42 **pobj)
{
    int s0, s1, s2, s3;
    int r;


    VEC_F6bf9ce42 *v;
    v = *pobj;
    s0 = (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE478 + v->x - (float)LVL_19_GRELBIN_F6bf9ce42_D_001AE488);
    s1 = (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE47C + v->y - (float)LVL_19_GRELBIN_F6bf9ce42_D_001AE48C);
    s3 = (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE480 + v->x + (float)LVL_19_GRELBIN_F6bf9ce42_D_001AE488);
    s2 = (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE484 + v->y + (float)LVL_19_GRELBIN_F6bf9ce42_D_001AE48C);

    r = LVL_19_GRELBIN_F6bf9ce42_FUN_0031A810(0x60241700, 0x55F0C070, 20, 0, 0);
    LVL_19_GRELBIN_F6bf9ce42_FUN_002EE378(s0, s1, s3, s2, LVL_19_GRELBIN_F6bf9ce42_D_001A7340, LVL_19_GRELBIN_F6bf9ce42_D_001A7344, r);

    v = *pobj;
    LVL_19_GRELBIN_F6bf9ce42_FUN_002EE378((int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE478 + v->x), (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE47C + v->y),
            (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE480 + v->x), (int)((float)LVL_19_GRELBIN_F6bf9ce42_D_001AE484 + v->y),
            LVL_19_GRELBIN_F6bf9ce42_D_001A7340, LVL_19_GRELBIN_F6bf9ce42_D_001A7344, 0x60241700);

}
extern char LVL_19_GRELBIN_F9c1eb693_D_00189E20[];
extern float LVL_19_GRELBIN_F9c1eb693_D_001A7FA4 __attribute__((sda));
extern float LVL_19_GRELBIN_F9c1eb693_D_001A7F9C __attribute__((sda));

int LVL_19_GRELBIN_FUN_002D3F38(float *a0, float *a1, float *a2)
{
    char *p = LVL_19_GRELBIN_F9c1eb693_D_00189E20;
    int v = *(int *)(p + 8852);

    if (v >= 98 && v <= 100) {
        if (a0) *a0 = *(float *)(p + 6316);
        if (a1) *a1 = LVL_19_GRELBIN_F9c1eb693_D_001A7FA4 * 4.8481374506081920117140e-06f;
        if (a2) *a2 = LVL_19_GRELBIN_F9c1eb693_D_001A7F9C * 2.9088824521750211715698e-04f;
        return 1;
    }
    if (v == 17) {
        if (a0) *a0 = *(float *)(p + 152);
        if (a1) *a1 = LVL_19_GRELBIN_F9c1eb693_D_001A7FA4 * 1.4544411897077225148678e-05f;
        if (a2) *a2 = LVL_19_GRELBIN_F9c1eb693_D_001A7F9C * 8.7266473565250635147095e-04f;
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_U32_FE8672EA5
#define RAC2_T_U32_FE8672EA5
typedef unsigned int u32_Fe8672ea5;
#endif


extern u32_Fe8672ea5 LVL_19_GRELBIN_Fe8672ea5_D_001B3030[];
extern u32_Fe8672ea5 LVL_19_GRELBIN_Fe8672ea5_D_001AC18C __attribute__((sda));
extern float LVL_19_GRELBIN_Fe8672ea5_D_001AC190 __attribute__((sda));

extern void LVL_19_GRELBIN_Fe8672ea5_FUN_002EB8E8(void *target);

void LVL_19_GRELBIN_FUN_00365098(u32_Fe8672ea5 object)
{
    u32_Fe8672ea5 cursor = object + 40952;
    int i;

    LVL_19_GRELBIN_Fe8672ea5_D_001AC18C = object;
    for (i = 511; i >= 0; i--) {
        *(u32_Fe8672ea5 *)cursor = 0;
        cursor -= 80;
    }
    LVL_19_GRELBIN_Fe8672ea5_D_001AC190 = 1.0f;
    LVL_19_GRELBIN_Fe8672ea5_FUN_002EB8E8(LVL_19_GRELBIN_Fe8672ea5_D_001B3030);
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


extern char LVL_19_GRELBIN_F8c659bbc_D_001B2650[] __attribute__((sda));
extern char LVL_19_GRELBIN_F8c659bbc_D_001B9A40[];
extern char LVL_19_GRELBIN_F8c659bbc_D_001B9C70[];
extern char LVL_19_GRELBIN_F8c659bbc_D_001A8E30 __attribute__((sda));

extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EB950(char *a, char *b, char *c);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EBC08(char *a, char *b, float f);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EC188(char *a, char *b);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EC4D0(char *a, char *b, char *c);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EBA38(char *a, char *b, char *c);
extern float LVL_19_GRELBIN_F8c659bbc_FUN_002EBA50(char *a);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_0031E4E0(char *a, char *b, float f);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_0031C090(char *a, float f1, float f2, float f3, float f4);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_0031E4E0(char *a, char *b, float f);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EC6F0(char *a, char *b);
extern void LVL_19_GRELBIN_F8c659bbc_FUN_002EC4D0(char *a, char *b, char *c);

void LVL_19_GRELBIN_FUN_002F0A08(char *arg0, int arg1)
{
    Block48_F8c659bbc a;
    Block48_F8c659bbc b;
    Block48_F8c659bbc c;
    Block16_F8c659bbc d;
    Block16_F8c659bbc e;
    float v;

    LVL_19_GRELBIN_F8c659bbc_FUN_002EB950((char *)&e, LVL_19_GRELBIN_F8c659bbc_D_001B9A40, LVL_19_GRELBIN_F8c659bbc_D_001B2650);
    LVL_19_GRELBIN_F8c659bbc_FUN_002EBC08((char *)&e, (char *)&e, 1.0f);
    LVL_19_GRELBIN_F8c659bbc_FUN_002EC188((char *)&c, (char *)&LVL_19_GRELBIN_F8c659bbc_D_001A8E30);
    LVL_19_GRELBIN_F8c659bbc_FUN_002EC4D0((char *)&b, LVL_19_GRELBIN_F8c659bbc_D_001B9A40 + 560, (char *)&c);
    LVL_19_GRELBIN_F8c659bbc_FUN_002EBA38((char *)&d, (char *)&b, (char *)&e);
    v = LVL_19_GRELBIN_F8c659bbc_FUN_002EBA50((char *)&d) * 0.5f;
    if (arg1 != 0) {
        LVL_19_GRELBIN_F8c659bbc_FUN_0031E4E0((char *)&d, (char *)&d, -v);
    } else {
        LVL_19_GRELBIN_F8c659bbc_FUN_0031C090(arg0, v, 5.8177649043500423431396e-04f,
                5.8177649043500423431396e-04f,
                5.2359886467456817626953e-02f);
        LVL_19_GRELBIN_F8c659bbc_FUN_0031E4E0((char *)&d, (char *)&d, -*(float *)arg0);
    }
    LVL_19_GRELBIN_F8c659bbc_FUN_002EC6F0((char *)&d, (char *)&a);
    LVL_19_GRELBIN_F8c659bbc_FUN_002EC4D0(LVL_19_GRELBIN_F8c659bbc_D_001B9C70, (char *)&a, LVL_19_GRELBIN_F8c659bbc_D_001B9C70);
}
#ifndef RAC2_T_F32_F7036EF03
#define RAC2_T_F32_F7036EF03
typedef float f32_F7036ef03;
#endif


extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4A8 __attribute__((sda));
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4B0 __attribute__((sda));
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4B8 __attribute__((sda));
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4C0 __attribute__((sda));
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4C8 __attribute__((sda));
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4AC;
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4B4;
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4BC;
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4C4;
extern f32_F7036ef03 LVL_19_GRELBIN_F7036ef03_D_001AE4CC;

extern void LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void LVL_19_GRELBIN_F7036ef03_FUN_00449D18(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);
extern void LVL_19_GRELBIN_F7036ef03_FUN_0044A310(void *a0);
extern void LVL_19_GRELBIN_F7036ef03_FUN_0044A2A0(void *a0);
extern int LVL_19_GRELBIN_F7036ef03_FUN_00449650(void *a0, int a1);

void LVL_19_GRELBIN_FUN_0044A470(char *self, int arg)
{
    f32_F7036ef03 *v;
    char *sub = self + 664;

    v = *(f32_F7036ef03 **)(self + 648);
    LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(self, LVL_19_GRELBIN_F7036ef03_D_001AE4A8 + v[0], LVL_19_GRELBIN_F7036ef03_D_001AE4AC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(self + 76, LVL_19_GRELBIN_F7036ef03_D_001AE4B0 + v[0], LVL_19_GRELBIN_F7036ef03_D_001AE4B4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(self + 152, LVL_19_GRELBIN_F7036ef03_D_001AE4B8 + v[0], LVL_19_GRELBIN_F7036ef03_D_001AE4BC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_19_GRELBIN_F7036ef03_FUN_0043CB08(self + 576, LVL_19_GRELBIN_F7036ef03_D_001AE4C0 + v[0], LVL_19_GRELBIN_F7036ef03_D_001AE4C4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 648);
    LVL_19_GRELBIN_F7036ef03_FUN_00449D18(sub, LVL_19_GRELBIN_F7036ef03_D_001AE4C8 + v[0], LVL_19_GRELBIN_F7036ef03_D_001AE4CC + v[1]);
    LVL_19_GRELBIN_F7036ef03_FUN_0044A310(self);
    LVL_19_GRELBIN_F7036ef03_FUN_0044A2A0(self);
    *(int *)(self + 416) = LVL_19_GRELBIN_F7036ef03_FUN_00449650(sub, arg);
}
extern int LVL_19_GRELBIN_F27b8017b_D_001ADC6C __attribute__((sda));
extern int LVL_19_GRELBIN_F27b8017b_D_001ADC70 __attribute__((sda));
extern int LVL_19_GRELBIN_F27b8017b_FUN_002F7738(int a, int b);
extern int LVL_19_GRELBIN_F27b8017b_FUN_002F7C08(int a, int b, int c, int d, int e, int *p);

void LVL_19_GRELBIN_FUN_0043D4F8(int *obj)
{
    int tmp[4];
    float f;

    f = *(float *)obj[4];
    if (f == 0.0f)
        return;
    if (LVL_19_GRELBIN_F27b8017b_D_001ADC6C != 0)
        *(int *)obj[3] = (*(int *)obj[3] & 0xff000000) | (LVL_19_GRELBIN_F27b8017b_D_001ADC70 & 0x00ffffff);
    tmp[0] = *(int *)obj[3];
    tmp[1] = *(int *)obj[3];
    tmp[2] = *(int *)obj[3];
    tmp[3] = *(int *)obj[3];
    LVL_19_GRELBIN_F27b8017b_FUN_002F7C08(LVL_19_GRELBIN_F27b8017b_FUN_002F7738((int)((float *)obj[13])[0], (int)((float *)obj[13])[1]),
             (int)((float *)obj[0])[0], (int)((float *)obj[0])[1],
             (int)((float *)obj[1])[0], (int)((float *)obj[1])[1], tmp);
}
extern void LVL_19_GRELBIN_F67cf9b36_FUN_0043CB08(char *p, float x, float y, float zero, float zero2);

extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1E0 __attribute__((sda));
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1E8 __attribute__((sda));
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1F0 __attribute__((sda));
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1F8 __attribute__((sda));
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1E4;
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1EC;
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1F4;
extern float LVL_19_GRELBIN_F67cf9b36_D_001AE1FC;

struct pos {
    float x;
    float y;
};

void LVL_19_GRELBIN_FUN_00445970(char *self)
{
    float zero = 0.0f;

    LVL_19_GRELBIN_F67cf9b36_FUN_0043CB08(self + 1256, LVL_19_GRELBIN_F67cf9b36_D_001AE1F8 + (*(struct pos **)(self + 680))->x,
            LVL_19_GRELBIN_F67cf9b36_D_001AE1FC + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_19_GRELBIN_F67cf9b36_FUN_0043CB08(self + 1040, LVL_19_GRELBIN_F67cf9b36_D_001AE1E0 + (*(struct pos **)(self + 680))->x,
            LVL_19_GRELBIN_F67cf9b36_D_001AE1E4 + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_19_GRELBIN_F67cf9b36_FUN_0043CB08(self + 1112, LVL_19_GRELBIN_F67cf9b36_D_001AE1E8 + (*(struct pos **)(self + 680))->x,
            LVL_19_GRELBIN_F67cf9b36_D_001AE1EC + (*(struct pos **)(self + 680))->y, zero, zero);
    LVL_19_GRELBIN_F67cf9b36_FUN_0043CB08(self + 1184, LVL_19_GRELBIN_F67cf9b36_D_001AE1F0 + (*(struct pos **)(self + 680))->x,
            LVL_19_GRELBIN_F67cf9b36_D_001AE1F4 + (*(struct pos **)(self + 680))->y, zero, zero);
}
extern float LVL_19_GRELBIN_Ff0e326aa_D_001AE440 __attribute__((sda));
extern float LVL_19_GRELBIN_Ff0e326aa_D_001AE444;
extern float LVL_19_GRELBIN_Ff0e326aa_D_001AE448 __attribute__((sda));
extern void LVL_19_GRELBIN_Ff0e326aa_FUN_0043CB08(void *, float, float, float, float);
extern void LVL_19_GRELBIN_Ff0e326aa_FUN_0043D5F0(void *, int, int);
extern void LVL_19_GRELBIN_Ff0e326aa_FUN_0043D4F8(void *);

void LVL_19_GRELBIN_FUN_00449340(int *p)
{
    int i;

    for (i = 0; i < p[95]; i++) {
        float *q = (float *)p[96];
        int v;

        LVL_19_GRELBIN_Ff0e326aa_FUN_0043CB08(p + 76, q[0] + LVL_19_GRELBIN_Ff0e326aa_D_001AE440,
                (q[1] + LVL_19_GRELBIN_Ff0e326aa_D_001AE444) + LVL_19_GRELBIN_Ff0e326aa_D_001AE448 * (float)i, 0.0f, 0.0f);
        if (i == 3)
            v = 0xEA9E;
        else
            v = 0xEAA6;
        p[93] = v;
        LVL_19_GRELBIN_Ff0e326aa_FUN_0043D5F0(p + 76, v, ((int *)p[94])[i]);
        LVL_19_GRELBIN_Ff0e326aa_FUN_0043D4F8(p + 76);
    }
}
#ifndef RAC2_T_F32_FE833F09F
#define RAC2_T_F32_FE833F09F
typedef float f32_Fe833f09f;
#endif


extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE378 __attribute__((sda));
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE388 __attribute__((sda));
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE380 __attribute__((sda));
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE390 __attribute__((sda));
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE398 __attribute__((sda));
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE37C;
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE38C;
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE384;
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE394;
extern f32_Fe833f09f LVL_19_GRELBIN_Fe833f09f_D_001AE39C;

extern void LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(void *a0, f32_Fe833f09f a1, f32_Fe833f09f a2, f32_Fe833f09f a3, f32_Fe833f09f a4);
extern void *LVL_19_GRELBIN_Fe833f09f_FUN_0043CAF0(void *a0);
extern int LVL_19_GRELBIN_Fe833f09f_FUN_0031A810(int a0, int a1, int a2, int a3, int a4);
extern void LVL_19_GRELBIN_Fe833f09f_FUN_004484A8(void *a0, int a1);
extern void LVL_19_GRELBIN_Fe833f09f_FUN_00448438(void *a0);
extern void LVL_19_GRELBIN_Fe833f09f_FUN_004484A0(void *a0);

int LVL_19_GRELBIN_FUN_00448598(char *self, int arg1)
{
    f32_Fe833f09f *v;

    v = *(f32_Fe833f09f **)(self + 536);
    LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(self, LVL_19_GRELBIN_Fe833f09f_D_001AE378 + v[0], LVL_19_GRELBIN_Fe833f09f_D_001AE37C + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(self + 152, LVL_19_GRELBIN_Fe833f09f_D_001AE388 + v[0], LVL_19_GRELBIN_Fe833f09f_D_001AE38C + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(self + 76, LVL_19_GRELBIN_Fe833f09f_D_001AE380 + v[0], LVL_19_GRELBIN_Fe833f09f_D_001AE384 + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(self + 228, LVL_19_GRELBIN_Fe833f09f_D_001AE390 + v[0], LVL_19_GRELBIN_Fe833f09f_D_001AE394 + v[1], 0.0f, 0.0f);
    v = *(f32_Fe833f09f **)(self + 536);
    LVL_19_GRELBIN_Fe833f09f_FUN_0043CB08(self + 464, LVL_19_GRELBIN_Fe833f09f_D_001AE398 + v[0], LVL_19_GRELBIN_Fe833f09f_D_001AE39C + v[1], 0.0f, 0.0f);

    *(int *)LVL_19_GRELBIN_Fe833f09f_FUN_0043CAF0(self + 304) = LVL_19_GRELBIN_Fe833f09f_FUN_0031A810(0x60442D00, 0x70FFFEED, 20, 0, 0);
    LVL_19_GRELBIN_Fe833f09f_FUN_004484A8(self, arg1);
    LVL_19_GRELBIN_Fe833f09f_FUN_00448438(self);
    LVL_19_GRELBIN_Fe833f09f_FUN_004484A0(self);
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


extern s32_Fee27d7bc LVL_19_GRELBIN_Fee27d7bc_FUN_0043DB10 (s32_Fee27d7bc, s32_Fee27d7bc);
extern s32_Fee27d7bc LVL_19_GRELBIN_Fee27d7bc_FUN_0043DA78 (s32_Fee27d7bc, s32_Fee27d7bc);
extern void LVL_19_GRELBIN_Fee27d7bc_FUN_004418B0 (s32_Fee27d7bc, s32_Fee27d7bc, const void *);
extern void LVL_19_GRELBIN_Fee27d7bc_FUN_00441D08 (s32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc);
extern void LVL_19_GRELBIN_Fee27d7bc_FUN_0043CEB0 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern s32_Fee27d7bc LVL_19_GRELBIN_Fee27d7bc_FUN_0043CAF0 (s32_Fee27d7bc);
extern void LVL_19_GRELBIN_Fee27d7bc_FUN_0043D060 (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern void LVL_19_GRELBIN_Fee27d7bc_FUN_00440470 (s32_Fee27d7bc);

extern char LVL_19_GRELBIN_Fee27d7bc_D_001ADF08[];
extern s32_Fee27d7bc LVL_19_GRELBIN_Fee27d7bc_D_001A904C;
extern s32_Fee27d7bc LVL_19_GRELBIN_Fee27d7bc_D_001ADEF8 __attribute__ ((sda));

void LVL_19_GRELBIN_FUN_00440308 (s32_Fee27d7bc self, s32_Fee27d7bc arg)
{
  s32_Fee27d7bc p;
  *(s32_Fee27d7bc *) self = arg;
  if (arg != 0)
    {
      p = LVL_19_GRELBIN_Fee27d7bc_FUN_0043DA78 (16, LVL_19_GRELBIN_Fee27d7bc_FUN_0043DB10 (arg, arg));
      *(s32_Fee27d7bc *) (self + 756) = p;
      ((s32_Fee27d7bc *) p)[1] = 0;
      ((s32_Fee27d7bc *) p)[2] = 0;
      ((s32_Fee27d7bc *) p)[3] = 0;
      ((s32_Fee27d7bc *) p)[0] = 0;
    }
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 756))[0] = 256.0f;
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 756))[1] = 212.0f;
  *(s32_Fee27d7bc *) (self + 760) = 0;
  LVL_19_GRELBIN_Fee27d7bc_FUN_004418B0 (self + 8, arg, &LVL_19_GRELBIN_Fee27d7bc_D_001ADEF8);
  LVL_19_GRELBIN_Fee27d7bc_FUN_00441D08 (self + 8, 64.0f, -164.0f, 10.0f, 136.0f, 10.0f, 99.0f);
  LVL_19_GRELBIN_Fee27d7bc_FUN_0043CEB0 (self + 680, LVL_19_GRELBIN_Fee27d7bc_D_001ADF08, arg);
  p = LVL_19_GRELBIN_Fee27d7bc_FUN_0043CAF0 (self + 680);
  *(s32_Fee27d7bc *) p = 0x70FFFEED;
  LVL_19_GRELBIN_Fee27d7bc_FUN_0043D060 (self + 680, LVL_19_GRELBIN_Fee27d7bc_D_001A904C + 0x8710, 214);
  LVL_19_GRELBIN_Fee27d7bc_FUN_00440470 (self);
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


extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_FUN_0043DB10 (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_FUN_0043DA78 (s32_F09f721e0, s32_F09f721e0);
extern void LVL_19_GRELBIN_F09f721e0_FUN_004418B0 (s32_F09f721e0, s32_F09f721e0, const void *);
extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (s32_F09f721e0);
extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (s32_F09f721e0);
extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (s32_F09f721e0);
extern void LVL_19_GRELBIN_F09f721e0_FUN_00441D28 (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);
extern void LVL_19_GRELBIN_F09f721e0_FUN_00441D08 (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);
extern void LVL_19_GRELBIN_F09f721e0_FUN_00441D80 (s32_F09f721e0, f32_F09f721e0);
extern void LVL_19_GRELBIN_F09f721e0_FUN_00442B70 (s32_F09f721e0, s32_F09f721e0);

extern s32_F09f721e0 LVL_19_GRELBIN_F09f721e0_D_001AE040 __attribute__ ((sda));

void LVL_19_GRELBIN_FUN_00442A48 (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 q;
  s32_F09f721e0 p;
  s32_F09f721e0 a, b;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      p = LVL_19_GRELBIN_F09f721e0_FUN_0043DA78 (16, LVL_19_GRELBIN_F09f721e0_FUN_0043DB10 (arg, arg));
      *(s32_F09f721e0 *) (self + 684) = p;
      ((s32_F09f721e0 *) p)[1] = 0;
      ((s32_F09f721e0 *) p)[2] = 0;
      ((s32_F09f721e0 *) p)[3] = 0;
      ((s32_F09f721e0 *) p)[0] = 0;
    }
  q = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 684))[1] = 195.0f;
  LVL_19_GRELBIN_F09f721e0_FUN_004418B0 (q, arg, &LVL_19_GRELBIN_F09f721e0_D_001AE040);
  a = LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (12773);
  b = LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (11598);
  LVL_19_GRELBIN_F09f721e0_FUN_00441D28 (q, a, b, LVL_19_GRELBIN_F09f721e0_FUN_002F1F28 (11599));
  LVL_19_GRELBIN_F09f721e0_FUN_00441D08 (q, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
  LVL_19_GRELBIN_F09f721e0_FUN_00441D80 (q, 0.65f);
  *(s32_F09f721e0 *) (self + 680) = 0;
  *(s32_F09f721e0 *) (q + 668) = 0;
  LVL_19_GRELBIN_F09f721e0_FUN_00442B70 (self, 0);
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
extern f32_Fe9770b1e LVL_19_GRELBIN_Fe9770b1e_D_001AE0B8[2] __attribute__((sda));

extern void *LVL_19_GRELBIN_Fe9770b1e_FUN_0043DB10(void *);
extern void *LVL_19_GRELBIN_Fe9770b1e_FUN_0043DA78(s32_Fe9770b1e, void *);
extern void LVL_19_GRELBIN_Fe9770b1e_FUN_004418B0(u8_Fe9770b1e *, void *, f32_Fe9770b1e *);
extern void *LVL_19_GRELBIN_Fe9770b1e_FUN_002F1F28(s32_Fe9770b1e);
extern void LVL_19_GRELBIN_Fe9770b1e_FUN_00441D28(u8_Fe9770b1e *, void *, void *, void *);
extern void LVL_19_GRELBIN_Fe9770b1e_FUN_00441D08(u8_Fe9770b1e *, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e);
extern void LVL_19_GRELBIN_Fe9770b1e_FUN_00441D80(u8_Fe9770b1e *, f32_Fe9770b1e);
extern void LVL_19_GRELBIN_Fe9770b1e_FUN_004437F0(u8_Fe9770b1e *, s32_Fe9770b1e);

void LVL_19_GRELBIN_FUN_004436C8(u8_Fe9770b1e *self, void *arg) {
    u8_Fe9770b1e *sub;
    void *first, *second, *third;
    *(void **)self = arg;
    if (arg != 0) {
        void *t = LVL_19_GRELBIN_Fe9770b1e_FUN_0043DB10(arg);
        void *p = LVL_19_GRELBIN_Fe9770b1e_FUN_0043DA78(16, t);
        *(void **)(self + 684) = p;
        ((s32_Fe9770b1e *)p)[1] = 0;
        ((s32_Fe9770b1e *)p)[2] = 0;
        ((s32_Fe9770b1e *)p)[3] = 0;
        ((s32_Fe9770b1e *)p)[0] = 0;
    }
    sub = self + 8;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[1] = 195.0f;
    LVL_19_GRELBIN_Fe9770b1e_FUN_004418B0(sub, arg, LVL_19_GRELBIN_Fe9770b1e_D_001AE0B8);
    first = LVL_19_GRELBIN_Fe9770b1e_FUN_002F1F28(11667);
    second = LVL_19_GRELBIN_Fe9770b1e_FUN_002F1F28(11598);
    third = LVL_19_GRELBIN_Fe9770b1e_FUN_002F1F28(11599);
    LVL_19_GRELBIN_Fe9770b1e_FUN_00441D28(sub, first, second, third);
    LVL_19_GRELBIN_Fe9770b1e_FUN_00441D08(sub, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    LVL_19_GRELBIN_Fe9770b1e_FUN_00441D80(sub, 0.2f);
    *(s32_Fe9770b1e *)(self + 680) = 0;
    LVL_19_GRELBIN_Fe9770b1e_FUN_004437F0(self, 0);
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
extern f32_Ff4eb83c9 LVL_19_GRELBIN_Ff4eb83c9_D_001AE070[2] __attribute__((sda));

extern void *LVL_19_GRELBIN_Ff4eb83c9_FUN_0043DB10(void *);
extern void *LVL_19_GRELBIN_Ff4eb83c9_FUN_0043DA78(s32_Ff4eb83c9, void *);
extern void LVL_19_GRELBIN_Ff4eb83c9_FUN_004418B0(u8_Ff4eb83c9 *, void *, f32_Ff4eb83c9 *);
extern void *LVL_19_GRELBIN_Ff4eb83c9_FUN_002F1F28(s32_Ff4eb83c9);
extern void LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D28(u8_Ff4eb83c9 *, void *, void *, void *);
extern void LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D08(u8_Ff4eb83c9 *, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9, f32_Ff4eb83c9);
extern void LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D80(u8_Ff4eb83c9 *, f32_Ff4eb83c9);
extern void LVL_19_GRELBIN_Ff4eb83c9_FUN_00443268(u8_Ff4eb83c9 *, s32_Ff4eb83c9);

void LVL_19_GRELBIN_FUN_00443140(u8_Ff4eb83c9 *self, void *arg) {
    u8_Ff4eb83c9 *sub;
    void *first, *second, *third;
    *(void **)self = arg;
    if (arg != 0) {
        void *t = LVL_19_GRELBIN_Ff4eb83c9_FUN_0043DB10(arg);
        void *p = LVL_19_GRELBIN_Ff4eb83c9_FUN_0043DA78(16, t);
        *(void **)(self + 684) = p;
        ((s32_Ff4eb83c9 *)p)[1] = 0;
        ((s32_Ff4eb83c9 *)p)[2] = 0;
        ((s32_Ff4eb83c9 *)p)[3] = 0;
        ((s32_Ff4eb83c9 *)p)[0] = 0;
    }
    sub = self + 8;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Ff4eb83c9 *)*(void **)(self + 684))[1] = 195.0f;
    LVL_19_GRELBIN_Ff4eb83c9_FUN_004418B0(sub, arg, LVL_19_GRELBIN_Ff4eb83c9_D_001AE070);
    first = LVL_19_GRELBIN_Ff4eb83c9_FUN_002F1F28(11672);
    second = LVL_19_GRELBIN_Ff4eb83c9_FUN_002F1F28(11598);
    third = LVL_19_GRELBIN_Ff4eb83c9_FUN_002F1F28(11599);
    LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D28(sub, first, second, third);
    LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D08(sub, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    LVL_19_GRELBIN_Ff4eb83c9_FUN_00441D80(sub, 0.65f);
    *(s32_Ff4eb83c9 *)(self + 680) = 0;
    LVL_19_GRELBIN_Ff4eb83c9_FUN_00443268(self, 0);
}
extern void LVL_19_GRELBIN_F54dfe946_FUN_0043CB08(char *p, float x, float y, float zero, float zero2);

extern float LVL_19_GRELBIN_F54dfe946_D_001AE540 __attribute__((sda));
extern float LVL_19_GRELBIN_F54dfe946_D_001AE548 __attribute__((sda));
extern float LVL_19_GRELBIN_F54dfe946_D_001AE550 __attribute__((sda));
extern float LVL_19_GRELBIN_F54dfe946_D_001AE558 __attribute__((sda));
extern float LVL_19_GRELBIN_F54dfe946_D_001AE544;
extern float LVL_19_GRELBIN_F54dfe946_D_001AE54C;
extern float LVL_19_GRELBIN_F54dfe946_D_001AE554;
extern float LVL_19_GRELBIN_F54dfe946_D_001AE55C;

struct pos54dfe946 {
    float x;
    float y;
};

void LVL_19_GRELBIN_FUN_0044B520(char *self)
{
    float zero = 0.0f;

    LVL_19_GRELBIN_F54dfe946_FUN_0043CB08(self + 808, LVL_19_GRELBIN_F54dfe946_D_001AE540 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_19_GRELBIN_F54dfe946_D_001AE544 + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_19_GRELBIN_F54dfe946_FUN_0043CB08(self + 880, LVL_19_GRELBIN_F54dfe946_D_001AE548 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_19_GRELBIN_F54dfe946_D_001AE54C + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_19_GRELBIN_F54dfe946_FUN_0043CB08(self + 952, LVL_19_GRELBIN_F54dfe946_D_001AE550 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_19_GRELBIN_F54dfe946_D_001AE554 + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
    LVL_19_GRELBIN_F54dfe946_FUN_0043CB08(self + 736, LVL_19_GRELBIN_F54dfe946_D_001AE558 + (*(struct pos54dfe946 **)(self + 1072))->x,
            LVL_19_GRELBIN_F54dfe946_D_001AE55C + (*(struct pos54dfe946 **)(self + 1072))->y, zero, zero);
}
extern int LVL_19_GRELBIN_Fa769c0f9_D_00138344[4];
extern int LVL_19_GRELBIN_Fa769c0f9_D_001ADF14[4] __attribute__((sda));
extern int LVL_19_GRELBIN_Fa769c0f9_D_001ADF10 __attribute__((sda));
extern int LVL_19_GRELBIN_Fa769c0f9_D_001ADF18 __attribute__((sda));

extern void LVL_19_GRELBIN_Fa769c0f9_FUN_00441CF0(char *, float, float);
extern void LVL_19_GRELBIN_Fa769c0f9_FUN_00441B00(char *);
extern int LVL_19_GRELBIN_Fa769c0f9_FUN_0031A810(int, int, int, int, int);
extern void *LVL_19_GRELBIN_Fa769c0f9_FUN_0043CAF0(char *);
extern int LVL_19_GRELBIN_Fa769c0f9_FUN_0031A810(int, int, int, int, int);
extern void LVL_19_GRELBIN_Fa769c0f9_FUN_0043CB08(char *, float, float, float, float);

int LVL_19_GRELBIN_FUN_00440580(char *p)
{
    char *a = p + 8;
    char *b;
    void *r;
    float x;
    float y;

    LVL_19_GRELBIN_Fa769c0f9_FUN_00441CF0(a, ((float *)(*(int *)(p + 756)))[0], ((float *)(*(int *)(p + 756)))[1]);
    LVL_19_GRELBIN_Fa769c0f9_FUN_00441B00(a);
    if (LVL_19_GRELBIN_Fa769c0f9_D_00138344[0] & 0x5000)
        LVL_19_GRELBIN_Fa769c0f9_FUN_0031A810(0, 0, 1, 0, 1);
    b = p + 680;
    r = LVL_19_GRELBIN_Fa769c0f9_FUN_0043CAF0(b);
    *(int *)r = LVL_19_GRELBIN_Fa769c0f9_FUN_0031A810(0x60442D00, 0x70FFFEED, 20, 0, 0);
    x = ((float *)(*(int *)(p + 756)))[0] + (float)LVL_19_GRELBIN_Fa769c0f9_D_001ADF10;
    y = ((float *)(*(int *)(p + 756)))[1]
        + (float)(*(int *)(p + 760) * LVL_19_GRELBIN_Fa769c0f9_D_001ADF18);
    y = y + (float)LVL_19_GRELBIN_Fa769c0f9_D_001ADF14[0];
    LVL_19_GRELBIN_Fa769c0f9_FUN_0043CB08(b, x, y, 0.0f, 0.0f);
    return 0;
}
extern unsigned char LVL_19_GRELBIN_F65feeb52_D_001A7A0A;
extern int LVL_19_GRELBIN_F65feeb52_D_001A79F0 __attribute__((sda));
extern int LVL_19_GRELBIN_F65feeb52_FUN_002E1538(int, int);

int LVL_19_GRELBIN_FUN_002E15E0(int x)
{
    int b = LVL_19_GRELBIN_F65feeb52_D_001A7A0A;
    int q;
    int v;

    if (b == 0) {
        q = LVL_19_GRELBIN_F65feeb52_FUN_002E1538(LVL_19_GRELBIN_F65feeb52_D_001A79F0, x) / 100;
        v = 3 - q;
        return b < v ? v : 1;
    }
    return 3;
}
extern int LVL_19_GRELBIN_F64995502_D_001B2488;
extern int LVL_19_GRELBIN_F64995502_D_001B2490;
extern int LVL_19_GRELBIN_F64995502_D_001B2494;
extern int LVL_19_GRELBIN_F64995502_D_001B248C;
extern int LVL_19_GRELBIN_F64995502_D_001B24B8;
extern int LVL_19_GRELBIN_F64995502_D_001B24BC;
extern int LVL_19_GRELBIN_F64995502_D_001A8F00;
extern int LVL_19_GRELBIN_F64995502_D_001A8F08;
extern unsigned char LVL_19_GRELBIN_F64995502_D_0018C0D4[];
extern int LVL_19_GRELBIN_F64995502_D_00138320[];
extern short LVL_19_GRELBIN_F64995502_D_001B271C;
extern short LVL_19_GRELBIN_F64995502_D_001B271E;
extern short LVL_19_GRELBIN_F64995502_D_001B2720;
extern short LVL_19_GRELBIN_F64995502_D_001B2722;
extern short LVL_19_GRELBIN_F64995502_D_001B2724;

void LVL_19_GRELBIN_FUN_0036D290(void)
{
    unsigned char mode;

    LVL_19_GRELBIN_F64995502_D_001B2488 = 0;
    mode = LVL_19_GRELBIN_F64995502_D_0018C0D4[0];
    LVL_19_GRELBIN_F64995502_D_001B2490 = 0;
    LVL_19_GRELBIN_F64995502_D_001B2494 = 0;
    LVL_19_GRELBIN_F64995502_D_001B248C = 0;
    LVL_19_GRELBIN_F64995502_D_001B24B8 = 0;
    LVL_19_GRELBIN_F64995502_D_001B24BC = 0;

    if (mode == 1)
    {
        if ((LVL_19_GRELBIN_F64995502_D_00138320[0] & 0x10) == 0)
        {
            if (LVL_19_GRELBIN_F64995502_D_001A8F00 != 4 && LVL_19_GRELBIN_F64995502_D_001A8F08 != 4)
            {
                LVL_19_GRELBIN_F64995502_D_001B271C = 0;
                LVL_19_GRELBIN_F64995502_D_001B271E = 0;
                LVL_19_GRELBIN_F64995502_D_001B2720 = 0;
                LVL_19_GRELBIN_F64995502_D_001B2722 = 0;
                LVL_19_GRELBIN_F64995502_D_001B2724 = 0;
            }
        }
    }
}
