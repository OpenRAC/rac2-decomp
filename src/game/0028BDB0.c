#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef int s32;

extern void func_0028BCE8(void);

/* authored C for independently verified level-native body */
/* Sets up a pop-up menu panel with its size and starting values. */
void func_0028BDB0(u8 *panel) {
 InitWeaponMenuSlots();
 *(s32 *)(panel+0x58)=210;*(s32 *)(panel+0x5c)=200;
 *(s32 *)(panel+0x74)=-2;*(s32 *)(panel+0x78)=30;
 *(u16 *)(panel+0x48)=0;*(u16 *)(panel+0x4a)=0;*(s32 *)(panel+0x70)=0;
}

/* func_0028C6D0 is defined in 0028BDB0-wheel-g8.c. */


/* func_0028CCE0 is defined in 0028BDB0-radial-g8.c. */

/* func_0028D1E8 is defined in 0028D1E8-radial-g8.c. */

extern int func_0028B740(void *, int *, int *);
extern void func_0028B7A8(void *, int *, int *, int, int);
extern int func_0028E588(int, int);
extern void func_0028ECD8(int,int,int,int,int,int);
extern void func_0028E868(int,int,int,int,int,int);
extern short D_0018B69A;
/* Draws a progress bar panel whose fill width follows how far along the value is. */
int func_0028DDD8(char *panel) {
 int x=*(int *)(panel+0x50), y=*(int *)(panel+0x54);
 int fillWidth;
 *(int *)(panel+0x58)=256; *(int *)(panel+0x5c)=64;
 hud_screen_position(panel,&x,&y);
 OffsetHudElementForSlide(panel,&x,&y,*(int *)(panel+0x6c),0);
 fillWidth=*(int *)(panel+0x74)*221 / *(int *)(panel+8)+27;
 DrawHudSpriteSizedTexture(GetIconFrame(0x7558,1),x,y,fillWidth,64,128);
 DrawHudSprite(GetIconFrame(0x7558,0),x,y,256,64,128);
 DrawHudSprite(GetIconFrame(0x7558,2),x,y,32,32,D_0018B69A?128:0);
 return *(int *)(panel+0x58);
}

/* Sets up a small menu panel with its size and timer. */
void func_0028DF38(char *panel) { extern void InitHudCounterValues(u8 *); *(int *)(panel + 0x58) = 0x20; *(int *)(panel + 0x7C) = 0x96; *(int *)(panel + 0x5C) = 0x20; InitHudCounterValues((u8 *)panel); }

/* Does nothing and returns zero. */
int func_0028DF68(void) {
    return 0;
}



/* The map's thirteen records, 0x90 bytes each: +0x04 flags, +0x14 handler,
   +0x68 busy, +0x6C position, +0x7C timer. */
extern char D_00255330[];

/* The retail loads this one through a lui/lw pair of its own. */
extern int D_001B1874 __attribute__((sda));

extern void func_0028B4D8(char *);

extern void func_0028E2A8(void);

/* Walks the records, caps their timers, moves their positions on, and lets a
   record run its own handler. */
/* Counts down the timers of the thirteen HUD records and runs each record's own handler when asked. */
int func_0028E138(int runHandlers)
{
    char *record;
    char *recordsEnd;
    int count = 0;

    UpdateWeaponMenuEntry();
    record = (char *)gHudElements;
    recordsEnd = (char *)gHudElements + 0x750;
    do {
        int timer;

        if ((*(int *)(record + 4) & 0x10) || D_001B1874) {
            timer = *(int *)(record + 0x7C);
            if (timer < 10) {
                *(int *)(record + 0x7C) = 10;
            }
            timer = *(int *)(record + 0x7C);
        } else {
            timer = *(int *)(record + 0x7C);
        }

        if (timer > 0) {
            timer = timer - 1;
            *(int *)(record + 0x7C) = timer;
            if (timer > 0) {
                count++;
                if (*(int *)(record + 0x6C) < 30) {
                    *(int *)(record + 0x6C) = *(int *)(record + 0x6C) + 1;
                }
            } else if (*(int *)(record + 0x6C) >= -5) {
                *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
            }
        } else if (*(int *)(record + 0x6C) >= -5) {
            *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
        }

        if (*(int *)(record + 0x68) != 0) {
            if (*(int *)(record + 0x6C) == -6) {
                FinishHudElementSetup(record);
            }
        }

        if (runHandlers != 0) {
            void (*handler)(char *) = *(void (**)(char *))(record + 0x14);
            if (handler) {
                handler(record);
            }
        }
        record += 0x90;
    } while ((int)record < (int)recordsEnd);
    return count;
}

typedef struct { char reserved00[0x1248]; int selected; char reserved124C[0x1068]; unsigned char blocked; } MapSelection;
typedef struct { char reserved00[0x88]; unsigned short valid; char reserved8A[0x56]; } MapRecord;
extern MapSelection D_00189E20;
extern unsigned char D_00139568[];
extern MapRecord ref_L00_0028E260_00[];
/* Gives the selected weapon, or zero when it cannot be used right now. */
int func_0028E260(void)
{
    int selected = gHeroState.selected;
    int blocked = gHeroState.blocked;
    unsigned int index = gItemSlotToRecord[selected];
    if (((MapRecord *)(index * 0xE0 + (unsigned int)ref_L00_0028E260_00))->valid == 0) selected = 0;
    if (blocked) selected = 0;
    return selected;
}

/* func_0028E2A8 is defined in 0028BDB0-menu-g8.c. */
