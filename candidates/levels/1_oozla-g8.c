

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout;


extern Rac2Native_8172b0f0a91a7cba_SDataClearMode112Layout LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00;
extern int LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE01;
extern int LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE02;

void LVL_1_OOZLA_FUN_002FEFF8(void)
{
    LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE01 &= ~0x20;
    if (LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00.mode_08 != 2)
        return;
    if (LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00.selector_10 == 0) {
        LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE02 = 9;
        return;
    }
    if (LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00.selector_10 == -1) {
        LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00.selector_10 = 0;
        LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE02 = 9;
        return;
    }
    if (LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE00.selector_10 == -2)
        LVL_1_OOZLA_F8172b0f0a91a7cba_AT002FEFF8_ROLE02 = 5;
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


extern Rac2Native_a661193cb7db1192_SDataAccessorRootReset44Layout LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE00;
extern int LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE01;

void LVL_1_OOZLA_FUN_002FF138(void)
{
    LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE00.selector_10 = 0;
    if (LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE00.selected_164 < 0) {
        LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE00.value_168 = 0;
        LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE00.selected_164 = 3;
    }
    LVL_1_OOZLA_Fa661193cb7db1192_AT002FF138_ROLE01 = 8;
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


extern Rac2Native_1716667661d8e672_SDataMoreGuard96Layout LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE00;
extern unsigned int LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE01;
extern int LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE02;

void LVL_1_OOZLA_FUN_002FF168(void)
{
    if (LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE00.mode_15c != 2 || LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE00.selected_164 >= 0)
        return;
    if (LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE00.extra_16c != 0) {
        LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE02 = 17;
        LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE01 |= 0x40u;
        return;
    }
    LVL_1_OOZLA_F1716667661d8e672_AT002FF168_ROLE02 = 14;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout;


extern Rac2Native_715e9b46a377ec8c_SDataMoreBits76RootLayout LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE01;
extern unsigned int LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE00;
extern int LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE02;

void LVL_1_OOZLA_FUN_002FF1C8(void)
{
    if (LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE01.selector_10 != 0) {
        LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE02 = 3;
        return;
    }
    if ((LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE00 & 6u) != 0) {
        LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE02 = 10;
        return;
    }
    if ((LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE00 & 0x200u) != 0)
        LVL_1_OOZLA_F715e9b46a377ec8c_AT002FF1C8_ROLE02 = 25;
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


extern Rac2Native_99b76d48da369e8d_SDataMoreThreshold156Layout LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00;
extern int LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01;

void LVL_1_OOZLA_FUN_002FF258(void)
{
    short phase;
    if (LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.mode_15c != 2 || LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.selected_164 >= 0)
        return;
    if (LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.extra_16c != 0) {
        LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01 = 12;
        return;
    }
    if (LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.selector_10 < -1) {
        LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01 = 3;
        return;
    }
    phase = LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.phase_18;
    if (phase == -2) {
        if (LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.value_0c + LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE00.value_20 < 475)
            LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01 = 19;
        else
            LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01 = 12;
        return;
    }
    if (phase >= -1)
        LVL_1_OOZLA_F99b76d48da369e8d_AT002FF258_ROLE01 = 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout;


extern Rac2Native_a0e246aa2dc0b8e7_SDataAccessorRoot56Layout LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE01;
extern int LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE00;
extern int LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE02;

void LVL_1_OOZLA_FUN_002FF2F8(void)
{
    if (LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE01.selector_10 != 0) {
        LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE02 = 3;
        return;
    }
    if ((LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE00 & 2) != 0)
        LVL_1_OOZLA_Fa0e246aa2dc0b8e7_AT002FF2F8_ROLE02 = 13;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout {
    unsigned char unknown_00[0x10];
    int selector_10;
    unsigned char unknown_14[0x168];
    int value_17c;
} Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout;


extern Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE00;
extern int LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01;
extern int LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE02;

void LVL_1_OOZLA_FUN_002FF460(void)
{
    if ((LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 & 4) != 0)
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 &= ~4;
    if ((LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 & 2) != 0)
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 &= ~2;
    if ((LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 & 0x80) != 0) {
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE02 = 21;
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 = (LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 ^ 0x80) | 0x40;
        return;
    }
    if ((LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 & 0x100) != 0) {
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE02 = 20;
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 = (LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE01 ^ 0x100) | 0x40;
        return;
    }
    if (LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE00.selector_10 != 0) {
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE02 = 3;
        return;
    }
    if (LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE00.value_17c != 0)
        LVL_1_OOZLA_F60904fd170c92806_AT002FF460_ROLE02 = 1;
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


extern Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00;
extern unsigned int LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE01;
extern int LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE02;

void LVL_1_OOZLA_FUN_002FF5D8(void)
{
    if (LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.mode_15c != 2 || LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.selected_164 >= 0)
        return;
    if (LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.extra_16c != 0 || LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.word_24 != 0) {
        LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.value_17c = 0;
        LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE02 = 21;
        LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE01 |= 0x440u;
        return;
    }
    LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE00.value_17c = 1;
    LVL_1_OOZLA_F8391b53329533f81_AT002FF5D8_ROLE02 = 1;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout;


extern Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE01;
extern int LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE00;
extern int LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE02;

void LVL_1_OOZLA_FUN_002FF750(void)
{
    if (LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE01.selector_10 != -2) {
        LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE02 = 3;
        return;
    }
    if ((LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE00 & 0x20) != 0) {
        LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE00 ^= 0x20;
        LVL_1_OOZLA_F83cf4a65b6159c6c_AT002FF750_ROLE02 = 5;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_25b7bae55e05d925_SDataRootClear68Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_25b7bae55e05d925_SDataRootClear68Layout;


extern Rac2Native_25b7bae55e05d925_SDataRootClear68Layout LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE01;
extern int LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE00;
extern int LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE02;

void LVL_1_OOZLA_FUN_002FF798(void)
{
    if (LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE01.selector_10 != 0) {
        LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE02 = 3;
        return;
    }
    if ((LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE00 & 0x20) != 0) {
        LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE00 ^= 0x20;
        LVL_1_OOZLA_F25b7bae55e05d925_AT002FF798_ROLE02 = 12;
    }
}


extern int LVL_1_OOZLA_F4ccf861671c28be2_AT002A5F80_ROLE00;

int LVL_1_OOZLA_FUN_002A5F80(void)
{
    return LVL_1_OOZLA_F4ccf861671c28be2_AT002A5F80_ROLE00;
}


extern float LVL_1_OOZLA_Fb4ab5917cc7e0e71_AT002CD108_ROLE00;

void LVL_1_OOZLA_FUN_002CD108(float value)
{
    LVL_1_OOZLA_Fb4ab5917cc7e0e71_AT002CD108_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_967caba148c0b35c_u32;


extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE00;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE01;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE04;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE05;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE06;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE07;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE08;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE09;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE10;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE11;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE02;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE03;
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE12 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE13 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE14 __attribute__((sda));
extern Rac2Native_967caba148c0b35c_u32 LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE15;

void LVL_1_OOZLA_FUN_002DADF8(void)
{
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE00 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE01 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE04 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE05 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE06 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE07 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE08 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE09 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE12 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE13 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE14 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE10 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE11 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE02 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE03 = 0;
    LVL_1_OOZLA_F967caba148c0b35c_AT002DADF8_ROLE15 = 0;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_a33fc77309a5e461_u32;


extern Rac2Native_a33fc77309a5e461_u32 LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01;
extern Rac2Native_a33fc77309a5e461_u32 LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE00;

void LVL_1_OOZLA_FUN_002E5920(void)
{
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01 + 0) = 0x30000009u;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01 + 4) =
        (LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE00 + 0xc0u) & 0x0fffffffu;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01 + 8) = 0;
    *(Rac2Native_a33fc77309a5e461_u32 *)(LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01 + 12) = 0x50000009u;
    LVL_1_OOZLA_Fa33fc77309a5e461_AT002E5920_ROLE01 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_73f23b7222fbc541_u32;

typedef unsigned char Rac2Native_73f23b7222fbc541_u8;


extern Rac2Native_73f23b7222fbc541_u32 LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00;
extern Rac2Native_73f23b7222fbc541_u8 LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE01[];

void LVL_1_OOZLA_FUN_002E5C38(void)
{
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00 + 0) = 0x30000026u;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00 + 4) = (Rac2Native_73f23b7222fbc541_u32)LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE01;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00 + 8) = 0;
    *(Rac2Native_73f23b7222fbc541_u32 *)(LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00 + 12) = 0x50000026u;
    LVL_1_OOZLA_F73f23b7222fbc541_AT002E5C38_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_571a3580c10e935f_u32;

typedef unsigned char Rac2Native_571a3580c10e935f_u8;


extern Rac2Native_571a3580c10e935f_u32 LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00;
extern Rac2Native_571a3580c10e935f_u8 LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE01[];

void LVL_1_OOZLA_FUN_002E5C98(void)
{
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00 + 0) = 0x30000029u;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00 + 4) = (Rac2Native_571a3580c10e935f_u32)LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE01;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00 + 8) = 0;
    *(Rac2Native_571a3580c10e935f_u32 *)(LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00 + 12) = 0x50000029u;
    LVL_1_OOZLA_F571a3580c10e935f_AT002E5C98_ROLE00 += 16;
}


extern int LVL_1_OOZLA_Fce2e52e5b0780004_AT002E6110_ROLE00;

int LVL_1_OOZLA_FUN_002E6110(void)
{
    return LVL_1_OOZLA_Fce2e52e5b0780004_AT002E6110_ROLE00;
}


extern int LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE00 __attribute__((sda));
extern int LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE01 __attribute__((sda));
extern int LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE02 __attribute__((sda));
extern int LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE03;

void LVL_1_OOZLA_FUN_002E6188(int first, int second, int third, int fourth)
{
    LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE00 = first;
    LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE01 = second;
    LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE02 = third;
    LVL_1_OOZLA_F53dbeb99ca77d218_AT002E6188_ROLE03 = fourth;
}


extern int LVL_1_OOZLA_F94af54270be5f5c3_AT002E87C0_ROLE00;

void LVL_1_OOZLA_FUN_002E87C0(void)
{
    LVL_1_OOZLA_F94af54270be5f5c3_AT002E87C0_ROLE00 = 3;
}


extern int LVL_1_OOZLA_Fde7724c328f7c2d0_AT002E87F0_ROLE00;

int LVL_1_OOZLA_FUN_002E87F0(void)
{
    return LVL_1_OOZLA_Fde7724c328f7c2d0_AT002E87F0_ROLE00;
}


extern int LVL_1_OOZLA_F61acb1f304b382c7_AT002E87F8_ROLE00;

void LVL_1_OOZLA_FUN_002E87F8(void)
{
    LVL_1_OOZLA_F61acb1f304b382c7_AT002E87F8_ROLE00 = 1;
}


extern int LVL_1_OOZLA_Ff0259c87ab6a3193_AT002E8808_ROLE00;

void LVL_1_OOZLA_FUN_002E8808(void)
{
    LVL_1_OOZLA_Ff0259c87ab6a3193_AT002E8808_ROLE00 = 0;
}


extern int LVL_1_OOZLA_F3abdbc5b6ec93b02_AT002E9748_ROLE00;

void LVL_1_OOZLA_FUN_002E9748(void)
{
    LVL_1_OOZLA_F3abdbc5b6ec93b02_AT002E9748_ROLE00 = 0;
}


extern int LVL_1_OOZLA_F4bf2f2e615420e28_AT002E9750_ROLE00;

void LVL_1_OOZLA_FUN_002E9750(void)
{
    LVL_1_OOZLA_F4bf2f2e615420e28_AT002E9750_ROLE00 = 1;
}


extern int LVL_1_OOZLA_Fa14de9886d500a76_AT002E9760_ROLE00;

int LVL_1_OOZLA_FUN_002E9760(void)
{
    return LVL_1_OOZLA_Fa14de9886d500a76_AT002E9760_ROLE00;
}


extern int LVL_1_OOZLA_F0e62d1a3c6e50a8e_AT003027D0_ROLE00;

void LVL_1_OOZLA_FUN_003027D0(void)
{
    LVL_1_OOZLA_F0e62d1a3c6e50a8e_AT003027D0_ROLE00 = -1;
}


extern int LVL_1_OOZLA_Fa077d83e809ad7db_AT00307E70_ROLE01;
extern unsigned char LVL_1_OOZLA_Fa077d83e809ad7db_AT00307E70_ROLE00[];

void LVL_1_OOZLA_FUN_00307E70(unsigned int index)
{
    if (index != 255u)
        LVL_1_OOZLA_Fa077d83e809ad7db_AT00307E70_ROLE00[index + (unsigned int)LVL_1_OOZLA_Fa077d83e809ad7db_AT00307E70_ROLE01 * 16u] |= 0x80u;
}


extern int LVL_1_OOZLA_Fcd2479c5d433222d_AT00320AE8_ROLE00 __attribute__((sda));

int LVL_1_OOZLA_FUN_00320AE8(void)
{
    return LVL_1_OOZLA_Fcd2479c5d433222d_AT00320AE8_ROLE00 > 0;
}


extern int LVL_1_OOZLA_Ffb9b02e5623c7428_AT00320AF8_ROLE00;

void LVL_1_OOZLA_FUN_00320AF8(int value)
{
    LVL_1_OOZLA_Ffb9b02e5623c7428_AT00320AF8_ROLE00 = value;
}


extern int LVL_1_OOZLA_Faf0fba3892cd725e_AT00320B20_ROLE00;

void LVL_1_OOZLA_FUN_00320B20(int value)
{
    LVL_1_OOZLA_Faf0fba3892cd725e_AT00320B20_ROLE00 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_4e44694cc39e7084_u32;


extern Rac2Native_4e44694cc39e7084_u32 LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00;

void LVL_1_OOZLA_FUN_00371678(Rac2Native_4e44694cc39e7084_u32 data_address, Rac2Native_4e44694cc39e7084_u32 tag_bits)
{
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00 + 0) = tag_bits | 0x30000000u;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00 + 4) = data_address;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00 + 8) = 0;
    *(Rac2Native_4e44694cc39e7084_u32 *)(LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00 + 12) = 0;
    LVL_1_OOZLA_F4e44694cc39e7084_AT00371678_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ae24050903bcaa08_u32;


extern Rac2Native_ae24050903bcaa08_u32 LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00;

void LVL_1_OOZLA_FUN_00371780(Rac2Native_ae24050903bcaa08_u32 final_word)
{
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00 + 0) = 0x10000000u;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00 + 4) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00 + 8) = 0;
    *(Rac2Native_ae24050903bcaa08_u32 *)(LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00 + 12) = final_word;
    LVL_1_OOZLA_Fae24050903bcaa08_AT00371780_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_9da4b6b15b3cf4a0_RecordWord180;

typedef unsigned long long Rac2Native_9da4b6b15b3cf4a0_RecordValue180;


extern Rac2Native_9da4b6b15b3cf4a0_RecordWord180 LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00;

void LVL_1_OOZLA_FUN_003717C8(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 final_word, Rac2Native_9da4b6b15b3cf4a0_RecordValue180 value)
{
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 0) = 0x10000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 4) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 8) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 12) = 0x50000002u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 16) = 0x8001u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 20) = 0x10000000u;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 24) = 0x0eu;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 28) = 0;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordValue180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 32) = value;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 40) = final_word;
    *(Rac2Native_9da4b6b15b3cf4a0_RecordWord180 *)(LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 + 44) = 0;
    LVL_1_OOZLA_F9da4b6b15b3cf4a0_AT003717C8_ROLE00 += 48;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ff971bf89acc2217_u32;

typedef unsigned char Rac2Native_ff971bf89acc2217_u8;


extern Rac2Native_ff971bf89acc2217_u32 LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00;
extern Rac2Native_ff971bf89acc2217_u8 LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE01[];

void LVL_1_OOZLA_FUN_003719B0(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00 + 4) = (Rac2Native_ff971bf89acc2217_u32)LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00 + 12) = 0x50000003u;
    LVL_1_OOZLA_Fff971bf89acc2217_AT003719B0_ROLE00 += 16;
}


extern Rac2Native_ff971bf89acc2217_u32 LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00;
extern Rac2Native_ff971bf89acc2217_u8 LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE01[];

void LVL_1_OOZLA_FUN_00371A10(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00 + 4) = (Rac2Native_ff971bf89acc2217_u32)LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00 + 12) = 0x50000003u;
    LVL_1_OOZLA_Fff971bf89acc2217_AT00371A10_ROLE00 += 16;
}


extern Rac2Native_ff971bf89acc2217_u32 LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00;
extern Rac2Native_ff971bf89acc2217_u8 LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE01[];

void LVL_1_OOZLA_FUN_00371A70(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00 + 4) = (Rac2Native_ff971bf89acc2217_u32)LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00 + 12) = 0x50000003u;
    LVL_1_OOZLA_Fff971bf89acc2217_AT00371A70_ROLE00 += 16;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_3646a0ca5397f72d_u32;

typedef unsigned char Rac2Native_3646a0ca5397f72d_u8;


extern Rac2Native_3646a0ca5397f72d_u32 LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00;
extern Rac2Native_3646a0ca5397f72d_u8 LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE01[];

void LVL_1_OOZLA_FUN_00371AD8(void)
{
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00 + 0) = 0x3000000bu;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00 + 4) = (Rac2Native_3646a0ca5397f72d_u32)LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE01;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00 + 8) = 0;
    *(Rac2Native_3646a0ca5397f72d_u32 *)(LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00 + 12) = 0x5000000bu;
    LVL_1_OOZLA_F3646a0ca5397f72d_AT00371AD8_ROLE00 += 16;
}


extern int LVL_1_OOZLA_Fb61be26e24a4cd6c_AT0042F820_ROLE00;

int LVL_1_OOZLA_FUN_0042F820(void)
{
    return LVL_1_OOZLA_Fb61be26e24a4cd6c_AT0042F820_ROLE00;
}


/* Measured partial C views; original types and object ownership are unknown. */
typedef struct {
    unsigned char prefix[0x188];
    unsigned char wrapped;
    unsigned char value;
} QwenRecovery_538934d89776_WrapperCollectState132;



extern unsigned char LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE001[3];
extern int LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE000;
extern QwenRecovery_538934d89776_WrapperCollectState132 LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE003;
extern int LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE002(int words[2]);

void LVL_1_OOZLA_FUN_002CC7A8(void)
{
    int words[4];
    LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE002(words);
    if (LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE001[2] != 0) {
        LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE000 += words[0];
        if (LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE000 >= 256) {
            LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE003.wrapped = 1;
            LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE000 -= 255;
        } else {
            LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE003.wrapped = 0;
        }
        LVL_1_OOZLA_QWEN_538934d89776_AT002CC7A8_ROLE003.value = ((unsigned char *)words)[4];
    } else {
        words[0] = 0;
        words[1] = 0;
    }
}



/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned long QwenRecovery_339fe89f21bc_WrapperWaitMaskU64;



extern int LVL_1_OOZLA_QWEN_339fe89f21bc_AT00371628_ROLE001 __attribute__((sda));
extern void LVL_1_OOZLA_QWEN_339fe89f21bc_AT00371628_ROLE000(int ticks);

void LVL_1_OOZLA_FUN_00371628(QwenRecovery_339fe89f21bc_WrapperWaitMaskU64 mask)
{
    while (LVL_1_OOZLA_QWEN_339fe89f21bc_AT00371628_ROLE001 & mask)
        LVL_1_OOZLA_QWEN_339fe89f21bc_AT00371628_ROLE000(0x400);
}

extern char LVL_1_OOZLA_F9c1eb693_D_00189E20[];
extern float LVL_1_OOZLA_F9c1eb693_D_001A7FA4 __attribute__((sda));
extern float LVL_1_OOZLA_F9c1eb693_D_001A7F9C __attribute__((sda));

int LVL_1_OOZLA_FUN_002CBC88(float *a0, float *a1, float *a2)
{
    char *p = LVL_1_OOZLA_F9c1eb693_D_00189E20;
    int v = *(int *)(p + 8852);

    if (v >= 98 && v <= 100) {
        if (a0) *a0 = *(float *)(p + 6316);
        if (a1) *a1 = LVL_1_OOZLA_F9c1eb693_D_001A7FA4 * 4.8481374506081920117140e-06f;
        if (a2) *a2 = LVL_1_OOZLA_F9c1eb693_D_001A7F9C * 2.9088824521750211715698e-04f;
        return 1;
    }
    if (v == 17) {
        if (a0) *a0 = *(float *)(p + 152);
        if (a1) *a1 = LVL_1_OOZLA_F9c1eb693_D_001A7FA4 * 1.4544411897077225148678e-05f;
        if (a2) *a2 = LVL_1_OOZLA_F9c1eb693_D_001A7F9C * 8.7266473565250635147095e-04f;
        return 1;
    }
    return 0;
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


extern char LVL_1_OOZLA_F8c659bbc_D_001B21D0[] __attribute__((sda));
extern char LVL_1_OOZLA_F8c659bbc_D_001B94C0[];
extern char LVL_1_OOZLA_F8c659bbc_D_001B96F0[];
extern char LVL_1_OOZLA_F8c659bbc_D_001A8E30 __attribute__((sda));

extern void LVL_1_OOZLA_F8c659bbc_FUN_002E34A0(char *a, char *b, char *c);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E3738(char *a, char *b, float f);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E3CB8(char *a, char *b);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E4000(char *a, char *b, char *c);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E3588(char *a, char *b, char *c);
extern float LVL_1_OOZLA_F8c659bbc_FUN_002E35A0(char *a);
extern void LVL_1_OOZLA_F8c659bbc_FUN_003167D8(char *a, char *b, float f);
extern void LVL_1_OOZLA_F8c659bbc_FUN_00314330(char *a, float f1, float f2, float f3, float f4);
extern void LVL_1_OOZLA_F8c659bbc_FUN_003167D8(char *a, char *b, float f);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E4220(char *a, char *b);
extern void LVL_1_OOZLA_F8c659bbc_FUN_002E4000(char *a, char *b, char *c);

void LVL_1_OOZLA_FUN_002E8538(char *arg0, int arg1)
{
    Block48_F8c659bbc a;
    Block48_F8c659bbc b;
    Block48_F8c659bbc c;
    Block16_F8c659bbc d;
    Block16_F8c659bbc e;
    float v;

    LVL_1_OOZLA_F8c659bbc_FUN_002E34A0((char *)&e, LVL_1_OOZLA_F8c659bbc_D_001B94C0, LVL_1_OOZLA_F8c659bbc_D_001B21D0);
    LVL_1_OOZLA_F8c659bbc_FUN_002E3738((char *)&e, (char *)&e, 1.0f);
    LVL_1_OOZLA_F8c659bbc_FUN_002E3CB8((char *)&c, (char *)&LVL_1_OOZLA_F8c659bbc_D_001A8E30);
    LVL_1_OOZLA_F8c659bbc_FUN_002E4000((char *)&b, LVL_1_OOZLA_F8c659bbc_D_001B94C0 + 560, (char *)&c);
    LVL_1_OOZLA_F8c659bbc_FUN_002E3588((char *)&d, (char *)&b, (char *)&e);
    v = LVL_1_OOZLA_F8c659bbc_FUN_002E35A0((char *)&d) * 0.5f;
    if (arg1 != 0) {
        LVL_1_OOZLA_F8c659bbc_FUN_003167D8((char *)&d, (char *)&d, -v);
    } else {
        LVL_1_OOZLA_F8c659bbc_FUN_00314330(arg0, v, 5.8177649043500423431396e-04f,
                5.8177649043500423431396e-04f,
                5.2359886467456817626953e-02f);
        LVL_1_OOZLA_F8c659bbc_FUN_003167D8((char *)&d, (char *)&d, -*(float *)arg0);
    }
    LVL_1_OOZLA_F8c659bbc_FUN_002E4220((char *)&d, (char *)&a);
    LVL_1_OOZLA_F8c659bbc_FUN_002E4000(LVL_1_OOZLA_F8c659bbc_D_001B96F0, (char *)&a, LVL_1_OOZLA_F8c659bbc_D_001B96F0);
}
extern void LVL_1_OOZLA_F332a1d80_FUN_0042E768(void *, float, float, float, float);
extern void LVL_1_OOZLA_F332a1d80_FUN_0042F250(void *, int, int);
extern void LVL_1_OOZLA_F332a1d80_FUN_0042F250(void *, int, int);
extern void LVL_1_OOZLA_F332a1d80_FUN_0042F250(void *, int, int);
extern void LVL_1_OOZLA_F332a1d80_FUN_0042F250(void *, int, int);
extern int *LVL_1_OOZLA_F332a1d80_FUN_0042E750(void *);
extern void LVL_1_OOZLA_F332a1d80_FUN_0042F158(void *);

extern float LVL_1_OOZLA_F332a1d80_D_001AE420 __attribute__((sda));
extern float LVL_1_OOZLA_F332a1d80_D_001AE424;
extern float LVL_1_OOZLA_F332a1d80_D_001AE428 __attribute__((sda));

struct Obj {
    char pad[380];
    int h380;
    char pad2[56];
    int tbl440[3];
    int a452;
    int *p456;
    int count460;
    char pad3[72];
    float *fp536;
    char pad4[224];
    int mode764;
};

void LVL_1_OOZLA_FUN_0043A3C0(struct Obj *o)
{
    int i;

    for (i = 0; i < o->count460; i++) {
        LVL_1_OOZLA_F332a1d80_FUN_0042E768(&o->h380, o->fp536[0] + LVL_1_OOZLA_F332a1d80_D_001AE420,
                o->fp536[1] + LVL_1_OOZLA_F332a1d80_D_001AE424 + LVL_1_OOZLA_F332a1d80_D_001AE428 * (float)i, 0.0f, 0.0f);
        if (o->mode764 == 2) {
            int v = o->p456[i];

            if (v == 5)
                LVL_1_OOZLA_F332a1d80_FUN_0042F250(&o->h380, 60062, 5);
            else
                LVL_1_OOZLA_F332a1d80_FUN_0042F250(&o->h380, v, 0);
        } else if (o->mode764 == 0) {
            int w = o->p456[i];

            if (w == 6)
                LVL_1_OOZLA_F332a1d80_FUN_0042F250(&o->h380, 60055, 0);
            else
                LVL_1_OOZLA_F332a1d80_FUN_0042F250(&o->h380, o->a452, w);
        } else {
            LVL_1_OOZLA_F332a1d80_FUN_0042F250(&o->h380, o->a452, o->p456[i]);
        }
        {
            int *r = LVL_1_OOZLA_F332a1d80_FUN_0042E750(&o->h380);
            int t = o->tbl440[o->mode764] ^ i;
            int alt = 0x70FFFEED;

            *r = t ? 0x60F0F0B0 : alt;
        }
        LVL_1_OOZLA_F332a1d80_FUN_0042F158(&o->h380);
    }
}
#ifndef RAC2_T_F32_FD368ADD8
#define RAC2_T_F32_FD368ADD8
typedef float f32_Fd368add8;
#endif


extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE3F8 __attribute__((sda));
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE408 __attribute__((sda));
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE400 __attribute__((sda));
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE410 __attribute__((sda));
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE418 __attribute__((sda));
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE3FC;
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE40C;
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE404;
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE414;
extern f32_Fd368add8 LVL_1_OOZLA_Fd368add8_D_001AE41C;

extern void LVL_1_OOZLA_Fd368add8_FUN_0042E768(void *a0, f32_Fd368add8 a1, f32_Fd368add8 a2, f32_Fd368add8 a3, f32_Fd368add8 a4);
extern void *LVL_1_OOZLA_Fd368add8_FUN_0042E750(void *a0);
extern int LVL_1_OOZLA_Fd368add8_FUN_00312AB0(int a0, int a1, int a2, int a3, int a4);
extern void LVL_1_OOZLA_Fd368add8_FUN_0043A108(void *a0, int a1);
extern void LVL_1_OOZLA_Fd368add8_FUN_0043A098(void *a0);
extern void LVL_1_OOZLA_Fd368add8_FUN_0043A100(void *a0);

int LVL_1_OOZLA_FUN_0043A1F8(char *self, int arg1)
{
    f32_Fd368add8 *v;

    v = *(f32_Fd368add8 **)(self + 536);
    LVL_1_OOZLA_Fd368add8_FUN_0042E768(self, LVL_1_OOZLA_Fd368add8_D_001AE3F8 + v[0], LVL_1_OOZLA_Fd368add8_D_001AE3FC + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    LVL_1_OOZLA_Fd368add8_FUN_0042E768(self + 152, LVL_1_OOZLA_Fd368add8_D_001AE408 + v[0], LVL_1_OOZLA_Fd368add8_D_001AE40C + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    LVL_1_OOZLA_Fd368add8_FUN_0042E768(self + 76, LVL_1_OOZLA_Fd368add8_D_001AE400 + v[0], LVL_1_OOZLA_Fd368add8_D_001AE404 + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    LVL_1_OOZLA_Fd368add8_FUN_0042E768(self + 228, LVL_1_OOZLA_Fd368add8_D_001AE410 + v[0], LVL_1_OOZLA_Fd368add8_D_001AE414 + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 536);
    LVL_1_OOZLA_Fd368add8_FUN_0042E768(self + 464, LVL_1_OOZLA_Fd368add8_D_001AE418 + v[0], LVL_1_OOZLA_Fd368add8_D_001AE41C + v[1], 0.0f, 0.0f);

    *(int *)LVL_1_OOZLA_Fd368add8_FUN_0042E750(self + 304) = LVL_1_OOZLA_Fd368add8_FUN_00312AB0(0x60442D00, 0x70FFFEED, 20, 0, 0);
    LVL_1_OOZLA_Fd368add8_FUN_0043A108(self, arg1);
    LVL_1_OOZLA_Fd368add8_FUN_0043A098(self);
    LVL_1_OOZLA_Fd368add8_FUN_0043A100(self);
    return *(int *)(self + (*(int *)(self + 764) << 2) + 440);
}
extern unsigned char LVL_1_OOZLA_F65feeb52_D_001A7A0A;
extern int LVL_1_OOZLA_F65feeb52_D_001A79F0 __attribute__((sda));
extern int LVL_1_OOZLA_F65feeb52_FUN_002D9260(int, int);

int LVL_1_OOZLA_FUN_002D9308(int x)
{
    int b = LVL_1_OOZLA_F65feeb52_D_001A7A0A;
    int q;
    int v;

    if (b == 0) {
        q = LVL_1_OOZLA_F65feeb52_FUN_002D9260(LVL_1_OOZLA_F65feeb52_D_001A79F0, x) / 100;
        v = 3 - q;
        return b < v ? v : 1;
    }
    return 3;
}
