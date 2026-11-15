#include "include_asm.h"
#include "names.h"

typedef struct MovieAdpcmDecoder {
    int mode;           /* 0x0 */
    char pad4[0x14];
    int nch;            /* 0x18 */
    int chunk;          /* 0x1C */
    char pad20[0x14];
    unsigned char *buf; /* 0x34 */
    int rd;             /* 0x38 */
    int cnt;            /* 0x3C */
    int size;           /* 0x40 */
    char pad44[0xC];
    int bytes;          /* 0x50 */
    char pad54[0xC];
    int pos;            /* 0x60 */
} MovieAdpcmDecoder;


extern void func_L00_0042BCF8_1(void *p);

extern void func_0034B070(void *p);

extern void func_L00_0042BFF8_7(void *p);

extern void func_00337BD8(void *p);

extern char *F476e86a4_FUN_00335E10(char *p);

extern void F476e86a4_FUN_003364C8(char *p, int a, int b);

extern void F476e86a4_FUN_00336508(char *p, int a, int b);

extern void F476e86a4_FUN_00336CE0(char *p, int a);

/* Qwen draft (branch qwen/autonomy, 56f9a59b), checked by tools/check.py */
void func_00338A60(int);

/* Qwen draft (branch qwen/autonomy, 576906e6), checked by tools/check.py */
void func_00338F58(int);

extern char F45821cfb_D_001C2740[];

extern void F45821cfb_FUN_00282C88(char *);

extern char F0a76d85b_D_001B5200[];

extern void F0a76d85b_FUN_00283360(char *p);

extern void F0a76d85b_FUN_00279D18(void);

extern void func_0034CEA0(void *);
extern void func_0034E4B8(int);
extern void func_0029CB58(void);

typedef int s32;

/* lot15 -- first CALL-BEARING body: the call family is now open. */
extern void func_0011AAD0(s32);

/* lot15 -- two twins of the first call-bearing body (same form, 32 bytes).
   The matched wrappers use a `nop` delay slot and return 1; the slot alone does not establish the callee parameter list. */
extern void func_001338C8();

typedef unsigned char u8;

extern void func_001338F0(s32, s32, s32, s32, s32);

extern s32 func_00133890(void);

extern s32 func_0011AEA0(s32);

extern s32 func_0011AFE0(s32 *, s32);

extern s32 func_0011AFC0(s32);

extern s32 func_00133930(s32, s32);

extern volatile unsigned int D_L00_001AEB10 __attribute__((sda));

typedef struct { int pos; int used; int size; } Ring;

extern void func_00336DB0(void *);
extern void func_00336CE8(void *);
extern void func_00336DB8(void *, int, void *, int);
extern void func_002B7C80(void *, void *, int);
extern void func_00115484(void *, int, int);
extern char *D_001A8CFC[] __attribute__((sda));
typedef struct { char pad0[0x36C]; int offset; char pad370[0x1348]; char *data; int size; } InitData;
extern InitData D_0014B540;
extern void func_003484C8(void *);
extern void func_00346670(void *);
extern void func_00345400(void *);
extern void func_003439A0(void *);
extern void func_0033F0A0(void *);
extern void func_00339A38(void *);
extern void func_00339008(void *);
extern void func_0033B0B8(void *);
extern void func_0033E640(void *);
extern void func_003411C0(void *);
extern void func_00343200(void *);
extern void func_0033E480(void *);
extern void func_00340D18(void *);
extern void func_00349148(void *);
extern void func_003395F8(void *);
extern void func_0033D708(void *);
extern void func_0033C430(void *);
extern void func_0033C9B8(void *);
extern void func_0033CD80(void *);
extern void func_0033D440(void *);
extern void func_0033BD38(void *);
extern void func_0033C178(void *);
extern void func_00347EA0(void *);
extern void func_003420C8(void *);
extern void func_00341C90(void *);
extern void func_0033DAD0(void *);
extern void func_0033DD80(void *);
extern void func_0033DF78(void *);
extern void func_0033E170(void *);
extern void func_0033A4A0(void *);
extern void func_0034E070(void *, void *, void *);
extern void func_003486A8(void *, void *);
extern void func_00346710(void *, void *);
extern void func_00345490(void *, void *);
extern void func_00343A30(void *, void *);
extern void func_0033F218(void *, void *);
extern void func_00339AD0(void *, void *);
extern void func_00340D68(void *, void *);
extern void func_00339078(void *, void *);
extern void func_00341220(void *, void *);
extern void func_00343260(void *, void *);
extern void func_0033B170(void *, void *);
extern void func_0033E6D0(void *, void *);
extern void func_0033E4C0(void *, void *);
extern void func_00349150(void *);
extern void func_0033A520(void *, void *);
extern void func_0033D740(void *, void *);
extern void func_0033C468(void *, void *);
extern void func_00339630(void *, void *);
extern void func_0033C9F0(void *, void *);
extern void func_0033CDC8(void *, void *);
extern void func_0033D478(void *, void *);
extern void func_0033BD70(void *, void *);
extern void func_0033C1B0(void *, void *);
extern void func_00347EC8(void *, void *);
extern void func_00341CE0(void *, void *);
extern void func_00342118(void *, void *);
extern void func_0033DB08(void *, void *);
extern void func_0033DDB8(void *, void *);
extern void func_0033DFB0(void *, void *);
extern void func_0033E1B0(void *, void *);


/* func_0034CEA0 is defined in 0034CEA0-menu-g8.c. */

/* func_0034DB98 is in 0034CEA0-g8.c. */


/* walks 26 consecutive 72-byte records calling one leaf per record, then calls four more leaves on fixed offsets of the same object and returns the object pointer */
/* Sets up the menu part objects: 26 item records and four extra pieces. */
unsigned char *func_0034DFE0(unsigned char *a0)
{
    unsigned char *p;
    int i;

    for (i = 25, p = a0; i != -1; i--) {
        func_L00_0042BCF8_1(p);
        p += 72;
    }
    func_L00_0042BCF8_1(a0 + 1872);
    ConstructHudObject(a0 + 1952);
    func_L00_0042BFF8_7(a0 + 7472);
    ShutdownTextPanel(a0 + 7532);
    ShutdownTextPanel(a0 + 8124);
    return a0;
}


/* Does nothing. */
void func_0034E218(void)
{
}

/* Moves one radial menu item to a screen position and draws it. */
void func_0034E220(char *a0, int a1, int a2, int a3, int t0)
{
    char *base = a0 + a1 * 72;
    float *p;
    char *vt;

    p = (float *)F476e86a4_FUN_00335E10(base);
    p[0] = (float)a2;
    p = (float *)F476e86a4_FUN_00335E10(base);
    p[1] = (float)a3;
    F476e86a4_FUN_003364C8(base, t0, t0);
    F476e86a4_FUN_00336508(base, t0, t0);
    F476e86a4_FUN_00336CE0(base, t0 << 24);
    vt = *(char **)(base + 48);
    (*(void (**)(char *))(vt + 12))(base + *(short *)(vt + 8));
}




/* Updates a part of the HUD stored inside this object. */
void func_0034E4B8(int param_1)
{
  UpdateTextPanelByMode(param_1 + 0x1d6c);
}

/* Updates another part of the HUD stored inside this object. */
void func_0034E4D8(int param_1)
{
  DrawTextPanelScaled(param_1 + 0x1d6c);
  return;
}



/* Returns the object it was given, unchanged. */
void *func_0034E5B8(void *object) {
    return object;
}

/* Clears the menu memory block and sets up every menu screen inside it. */
char *func_0034E5C0(char *object)
{
    int i;
    int size;
    char *end;
    int *clear = (int *)(object + 4);
    char *root;
    char *part0;
    char *part1;
    char *part2;
    char *part3;
    char *part4;
    char *part5;
    char *part6;
    char *part7;
    char *part8;
    char *part9;
    char *part10;
    char *part11;
    char *part12;
    char *part13;
    char *part14;
    char *part15;
    char *part16;
    char *part17;
    char *part18;
    char *part19;
    char *part20;
    char *part21;
    char *part22;
    char *part23;
    char *part24;
    char *part25;
    char *part26;
    char *part27;
    char *part28;
    char *part29;
    char *part30;
    for (i = 0x86F; i != -1; i--) {
        clear[0] = 0; clear[1] = 0; clear[2] = 0; clear[3] = 0;
        clear += 4;
    }
    root = object + 0x36F10;
    ReturnSelf(root);
    part0 = object + 0x36F28;
    InitLevelPartsA(part0);
    part1 = object + 0x39140;
    InitSevenLabelMenu(part1);
    part2 = object + 0x39590;
    InitLargeMenuScreenParts(part2);
    part3 = object + 0x39A98;
    InitMenuScreenParts(part3);
    part4 = object + 0x39F38;
    InitGridMenuWidgets(part4);
    part5 = object + 0x3A388;
    ConstructRadialMenuParts(part5);
    part6 = object + 0x3ADE8;
    DestroyListScreenWidgets(part6);
    part7 = object + 0x3B1F0;
    InitMissionScreenParts(part7);
    part8 = object + 0x3B490;
    DestroyMapScreenWidgets(part8);
    part9 = object + 0x3B7C0;
    DestroyElevenTextMenuPage(part9);
    part10 = object + 0x3BE08;
    ConstructTabbedMenuParts(part10);
    part11 = object + 0x3C108;
    InitMenuWidgets(part11);
    part12 = object + 0x3C440;
    DestroySimpleListMenuPage(part12);
    part13 = object + 0x3C738;
    ConstructSmallMenuParts(part13);
    part14 = object + 0x3C950;
    ReturnObject(part14);
    part15 = object + 0x3CAA8;
    ShutdownMissionScreen(part15);
    part16 = object + 0x3CDB0;
    DestroySingleToggleOptionMenuB(part16);
    part17 = object + 0x3D060;
    DestroyOnOffOptionMenu(part17);
    part18 = object + 0x3D310;
    DestroyFourOptionMenu(part18);
    part19 = object + 0x3D5C0;
    DestroyTwoToggleOptionMenuA(part19);
    part20 = object + 0x3D900;
    DestroySingleToggleOptionMenuA(part20);
    part21 = object + 0x3DBB0;
    DestroyMapScreenPromptBar(part21);
    part22 = object + 0x3DE60;
    DestroyScreenAdjustMenu(part22);
    part23 = object + 0x3E110;
    PassThroughHandle(part23);
    part24 = object + 0x3E1D8;
    ConstructListMenuParts(part24);
    part25 = object + 0x3E430;
    ConstructSmallListMenuParts(part25);
    part26 = object + 0x3E5A8;
    DestroyTwoToggleOptionMenuB(part26);
    part27 = object + 0x3E858;
    DestroySingleToggleOptionMenuC(part27);
    part28 = object + 0x3EB08;
    DestroySingleToggleOptionMenuD(part28);
    part29 = object + 0x3EDB8;
    DestroyListMenuPage(part29);
    part30 = object + 0x3F138;
    DestroyTitleScreenWidgets(part30);
    size = 0x3F490;
    end = object + size;
    D_001A8CFC[0] = object;
    *(char **)object = (char *)(((int)end + 3) & -4);
    *(int *)(object + 0x3F348) = size;
    ReadDiscWithPause(object + 0x8710, gCopySetupData.data + gCopySetupData.offset, gCopySetupData.size);
    RelocateTableEntryPointers(object + 0x8710);
    InitCellPool(root, 16, object + 4, 0x8700);
    InitRecordsScreen(part0, object, root);
    *(int *)(object + 0x3F34C) = 0;
    *(int *)(object + 0x3F350) = 0;
    *(int *)(object + 0x3F354) = 0;
    *(int *)(object + 0x3F358) = 0;
    ConstructMenuPageWithRows(part1, root);
    InitItemGridMenu(part2, root);
    InitSelectionMenu(part3, root);
    ConstructGridMenu(part4, root);
    InitRadialMenu(part5, root);
    InitListScreen(part6, root);
    InitMenuGrid(part13, root);
    InitMissionScreen(part7, root);
    InitTabbedMenu(part10, root);
    ConstructItemSelectMenu(part11, root);
    InitMapScreen(part8, root);
    InitInfoPanelMenu(part9, root);
    InitSimpleMenuPage(part12, root);
    ClearMenuEntries(part14);
    InitTitleLabelScreen(part30, root);
    InitTwoToggleOptionMenuB(part16, root);
    InitFourOptionMenu(part17, root);
    InitPopupMessageBox(part15, root);
    InitTwoToggleOptionMenuB(part16, root);
    InitFourOptionMenu(part17, root);
    InitPromptBarMenu(part18, root);
    InitAudioOptionsMenu(part19, root);
    InitSingleToggleOptionMenuA(part20, root);
    InitScreenAdjustMenu(part21, root);
    InitOnOffOptionMenu(part22, root);
    InitListMenu_00347EC8(part23, root);
    InitSmallListMenu(part25, root);
    InitListMenu_00342118(part24, root);
    InitSingleToggleOptionMenuC(part26, root);
    InitSingleToggleOptionMenuD(part27, root);
    InitSingleToggleOptionMenuE(part28, root);
    InitListMenuPage(part29, root);
    *(int *)(object + 0x3F364) = 0;
    *(int *)(object + 0x3F368) = 0;
    *(int *)(object + 0x3F36C) = 0;
    memset(object + 0x3F370, 0, 32);
    memset(object + 0x3F390, 0, 256);
    return object;
}

/* The retail caller passes an owner to both setup helpers; these bodies use resident state. */
/* Sets the light directions and colors used by the menus. */
void func_0034EBE0(void *owner)
{
    float *p = (float *)F45821cfb_D_001C2740;

    p[224] = 0.4f;
    p[225] = 0.8f;
    p[226] = 1.2f;
    *(int *)&p[227] = 0;
    p[228] = 0.577f;
    p[229] = 0.577f;
    p[230] = -0.577f;
    *(int *)&p[231] = 0;
    F45821cfb_FUN_00282C88((char *)&p[232]);
    F45821cfb_FUN_00282C88((char *)&p[236]);
}

/* Resets some menu drawing values to zero. */
void func_0034EC70(void *owner)
{
    char *p = F0a76d85b_D_001B5200;

    *(int *)(p + 320) = 0;
    *(int *)(p + 324) = 0;
    *(int *)(p + 328) = 0;
    F0a76d85b_FUN_00283360(p + 880);
    F0a76d85b_FUN_00279D18();
}


/* The two "slot" sub-objects of a level object: each holds an index into the
   entry table, and the entry gives the packet the slot writes to. */
typedef unsigned int u32;

typedef struct {
    u8 pad00[8];
    u8 f08;
    u8 pad09[0x3f];
    u32 *f48[8];
} EntryTable;

typedef struct {
    u8 pad00[0x10];
    u8 f10;
    u8 pad11[2];
    u8 f13;
    u8 pad14[8];
    u32 f1c[8];
} Entry;

typedef struct {
    u8 pad00[0x24];
    EntryTable *f24;
    u8 pad28[0x18];
    u8 f40;
    u8 f41;
    u8 f42;
    u8 f43;
    u8 pad44[0x14];
    char *f58;
    char *f5c;
} SlotObject;

extern void func_0026F788(char *, long long);
extern void func_002A05A8(char *);
extern void func_002A1130(u32 *, u32, long long, u32);
extern void func_002A0F48(char *);

/* Links two menu slots to their picture data so they can be drawn. */
void func_0034ECB0(char *obj)
{
    char *sub = obj + 0xC00;
    SlotObject *s = (SlotObject *)sub;

    EmptyStubF788(sub, 0);
    func_002A05A8(sub);
    if (s->f42 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f42];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f40], (long long)obj, table->f08);
        s->f58 = obj;
    }
    if (s->f43 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f43];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f41], (long long)(obj + 0x600), table->f08);
        s->f5c = obj + 0x600;
    }
    func_002A0F48(sub);
}

extern volatile int D_001A7350 __attribute__((sda));
extern volatile int D_001A7354 __attribute__((sda));
extern char D_L00_001AC820[];
extern char *D_L00_001B2608[] __attribute__((sda));
extern void func_00282B50(void *, void *, int);
extern void func_002A0300(void *, int);
/* Draws a menu sprite twice, first shifted for a shadow, then in place. */
void func_0034EDB0(void *unused, char *object)
{
    char *packet = D_L00_001AC820;
    *(int *)(packet + 0x20) = gScreenOffsetX + *(short *)(object + 0xB4);
    *(int *)(packet + 0x24) = gScreenOffsetY + *(short *)(object + 0xB6);
    FastMemoryHelperC(D_L00_001B2608[0], packet, 48);
    D_L00_001B2608[0] += 48;
    UploadObjectTextures(object, 1);
    *(int *)(packet + 0x20) = gScreenOffsetX;
    *(int *)(packet + 0x24) = gScreenOffsetY;
    FastMemoryHelperC(D_L00_001B2608[0], packet, 48);
    D_L00_001B2608[0] += 48;
}




/* func_0034F048 is in 0034CEA0-read-mpeg.c. */

/* Starts the movie sound transfer. */
void func_0034F3B8(void) {
    RotateThreadReadyQueue(1);
}

extern char *D_001B23CC[] __attribute__((sda));
extern int func_0034FAE8(u8 *);

/* Tells whether the movie sound buffer has filled up enough. */
int func_0034F3D8(void) {
    return IsMovieAudioPrimed((u8 *)(gMoviePlayerState[0] + 0xD9100));
}

/* func_0034F408 is in 0034CEA0-movie-init.c. */

extern char D_001AE820[];
extern void func_0026FEB8(void *, int);

/* Passes a number on to a debug print helper. */
void func_0034F780(int value) {
    STUB_printf(D_001AE820, value);
}

extern char *D_001B23CC[] __attribute__((sda));
extern void func_0034FAF8(int *);

/* Keeps the movie sound playing if it is active. */
void func_0034F7A8(void) {
    UpdateMovieAudioIfActive((int *)(gMoviePlayerState[0] + 0xD9100));
}


/* Resets the movie sound transfer and reports success. */
s32 func_0034F898(void) {
    SendSoundCommand3C();
    return 1;
}


/* Starts playing the movie sound. */
void func_0034F8C0(u8 *decoder) {
    SendSoundCommand3E(*(s32 *)(decoder+0x48), *(s32 *)(decoder+0x4c) / 1024 * 1024,
                *(s32 *)(decoder+0x5c), *(s32 *)(decoder+0x14), *(s32 *)(decoder+0x18));
    *(s32 *)decoder = 2;
}

/* Stops the movie sound and clears its counters. */
void func_0034F918(u8 *decoder) {
    SendSoundCommand3D();
    *(volatile s32 *)(decoder + 0x5c) = 0;
    *(volatile s32 *)(decoder + 0x00) = 0;
    *(volatile s32 *)(decoder + 0x30) = 0;
    *(volatile s32 *)(decoder + 0x38) = 0;
    *(volatile s32 *)(decoder + 0x3c) = 0;
    *(volatile s32 *)(decoder + 0x44) = 0;
    *(volatile s32 *)(decoder + 0x50) = 0;
    *(volatile s32 *)(decoder + 0x58) = 0;
}

/* Works out where new movie sound data can be written in the ring buffer. */
void func_0034F960(s32 *state,s32 *outPtr1,s32 *outLen1,s32 *outPtr2,s32 *outLen2) {
 s32 offset,wanted;
 if(state[0]==0) {
  if(state[1]!=4) {
   *outPtr1=(s32)((u8 *)state+(state[12]+8));
   *outLen1=0x28-state[12]; *outPtr2=state[13]; *outLen2=state[16];
   return;
  }
  *outPtr1=state[13]; *outLen1=state[16];
  clear: *outPtr2=0; *outLen2=0; return;
 }
 wanted=state[16]-state[15];offset=state[14];
 if(state[16]-offset>=wanted) {
  *outPtr1=state[13]+offset; *outLen1=wanted; goto clear;
 }
 *outPtr1=state[13]+offset;
 *outLen1=state[16]-state[14]; *outPtr2=state[13];
 *outLen2=wanted-(state[16]-state[14]);
}

int func_0034FA30(s32 *state,s32 amount) {
    if(state[0]==0) {
        if(state[1]!=4) {
            s32 room=40-state[12];
            s32 taken=amount;
            if(room<amount) taken=room;
            state[12]+=taken;
            if(state[12]>39) state[0]=1;
            amount-=taken;
        } else state[0]=1;
    }
    state[16]=state[16]/1024*1024;
    state[14]=(state[14]+amount)%state[16];
    state[15]+=amount;
    state[17]+=amount;
    return state[17];
}

/* true when the counter has reached 0x1000; byte-identical across all 27 levels. */
s32 func_0034FAE8(u8 *a0) { return *(s32 *)(a0 + 0x50) >= 0x1000; }

extern void func_0034FBC8(void *);

/* Sends movie sound data if the player is running. */
void func_0034FAF8(int *object) {
    if (object[0] != 0)
        SendMovieAudioBlocks(object);
}

/* Sends one block of sound data to the sound chip and waits until it is done. */
void func_0034FB20(u8 *a0, s32 a1, s32 a2, s32 a3) {
    s32 dma[4], id;
    ((void (*)(s32))FlushCache)(0);
    dma[0] = a1; dma[1] = *(s32 *)(a0+0x48); dma[2] = a2; dma[3] = 0;
    do { id = sceSifSetDma(dma,1); } while (id == 0);
    while (sceSifDmaStat(id) >= 0) {}
    SendSoundCommand5A(a2,a3);
}

/* sendADPCM(_AudioDec *) */
extern s32 D_001B23D4 __attribute__((section(".sdata")));
extern s32 func_00133960(void);

/* Feeds the movie sound data to the sound chip in blocks, one per channel. */
void func_0034FBC8(void *object) {
    s32 *o = object;
    s32 t = 0;
    s32 next, i, count;
    u8 *src;
    u8 *dst;

    switch (o[0]) {
    case 1:
        if (o[15] < 0x1000)
            return;
        t = 0x1000 - o[20];
        break;
    case 2:
        t = (SendSoundCommand5B() - o[24]) & 0xFFF;
        break;
    case 3:
        return;
    default:
        break;
    }
    while (t >= 0x400 && o[15] >= o[6] * 1024) {
        next = t - 0x400;
        for (i = 0; i < o[6]; i++) {
            count = 0;
            src = (u8 *)o[13] + (o[14] - o[15] + o[16]) % o[16];
            src += i * o[7];
            dst = (u8 *)D_001B23D4;
            do {
                s32 k;
                for (k = 0; k < o[7]; k++) {
                    *dst++ = *src++;
                    count++;
                }
                src += o[7] * (o[6] - 1);
            } while (count < 0x400);
            if (o[24] + 0x400 == 0x1000)
                ((u8 *)D_001B23D4)[0x3F1] = 3;
            if (o[24] == 0) {
                u8 *p = (u8 *)D_001B23D4;
                p[1] = 6;
                p[0x11] = 2;
            }
            SendAudioBlockToSpu((u8 *)o, D_001B23D4, 0x400, (i << 12) + o[24]);
        }
        t = next;
        o[15] -= o[6] * 1024;
        o[24] = (o[24] + 0x400) % 0x1000;
        o[20] += 0x400;
    }
}

/* func_0034FE18 is in 0034CEA0-g8.c. */

/* func_0034FFC0 is defined in 0034FFC0.c. */

/* func_00350190 is defined in 00350190.c. */

extern int func_001261F0(int);
extern int D_001A7BB8 __attribute__((sda));
extern volatile int D_001AE7D0[] __attribute__((sda));
extern volatile int D_001AE7D4[] __attribute__((sda));

/* Waits for the right screen field, then lets the movie start showing frames. */
void func_003501E0(int value)
{
    while (GetGsCurrentField(0) == value && gWidescreenFlag == 0) {}
    D_001AE7D0[0] = 1;
    D_001AE7D4[0] = 0;
}

/* A19-sda-scalar-store-16 freshly exact-verified under family reservation */
/* Clears a movie flag. */
void func_00350230(void) { D_L00_001AEB10 = 0; }

/* func_00350240 is in 0034CEA0-g8.c. */

extern int func_00350460(char *, int, char *, int, char *, int, char *, int);

/* Copies a chunk of movie sound data into the sound buffer. */
int func_00350378(void *unused, int *packet, char *buf)
{
    char *first_address;
    int first_count;
    char *second_address;
    int second_count;
    Ring *r = (Ring *)(buf + 0x50000);
    char *src = (char *)packet[2] + 4;
    char *end = buf + r->size;
    int len = packet[3] - 4;
    int first, second, result;

    if (src >= end)
        src -= r->size;
    first = end - src;
    if (len < first)
        first = len;
    second = len - first;
    GetAudioBufferWritePointers((s32 *)(gMoviePlayerState[0] + 0xD9100), (s32 *)&first_address, &first_count, (s32 *)&second_address, &second_count);
    result = CopySplitBuffer(first_address, first_count, second_address, second_count, src, first, buf, second);
    audioDecEndPut((s32 *)(gMoviePlayerState[0] + 0xD9100), result);
    return result > 0;
}


/* Sets up an empty read buffer. */
void func_00350590(u8 *ring) {
 ring+=0x50000;
 *(s32 *)(ring+8)=0x50000;
 *(s32 *)ring=0;
 *(s32 *)(ring+4)=0;
}

/* Does nothing. */
void func_003505A8(void)
{
}

s32 func_003505B0(u8 *buf,u8 **outPtr) {
 s32 *ring=(s32 *)(buf+0x50000);
 s32 freeBytes=ring[2]-ring[1];
 if(freeBytes!=0) *outPtr=buf+ring[0];
 return freeBytes;
}

void func_003505E0(char *base, int n) {
    Ring *r = (Ring *)(base + 0x50000);
    int avail = r->size - r->used;
    if (n < avail) avail = n;
    r->pos = (r->pos + avail) % r->size;
    r->used += avail;
}

s32 func_00350628(u8 *buf,s32 *outPtr) {
    u8 *ring=buf+0x50000;
    s32 usedBytes=*(s32 *)(ring+4);
    if(usedBytes!=0) {
        s32 size=*(s32 *)(ring+8);
        *outPtr=(s32)buf+((*(s32 *)ring-usedBytes)+size)%size;
    }
    return *(s32 *)(ring+4);
}

s32 func_00350670(u8 *ring,s32 amount) {
 s32 before,taken;
 ring+=0x50000;
 taken=*(s32 *)(ring+4);before=taken;
 if(amount<taken) taken=amount;
 *(s32 *)(ring+4)=before-taken;
 return taken;
}

/* stores two words and returns 1; byte-identical across all 27 levels. */
s32 func_00350698(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0x4) = a1; *(s32 *)a0 = a2; return 1; }
