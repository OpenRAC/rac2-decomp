/* func_US2_002DB700, the USA v2.00 copy of func_002DA9A8: the same C. */

/* A row of a choice list: its label, the byte it edits and up to four choice labels. */
/* A menu page: the page the back button opens and the menu taking input. */
/* The menu system D_001F2840: its current page, the page to open next and the flag that
 * keeps the menu from closing. */
extern int D_00138180[];

extern void func_002DF190(int, int);

/* Qwen draft (branch qwen/autonomy, 385de342), checked by tools/check.py */
/* func_002D7AC8: owner ABI/declaration review retained. */
typedef int s32;

/* Qwen draft (branch qwen/autonomy, f0b23b24), checked by tools/check.py */
typedef unsigned long long undefined8;

typedef unsigned int undefined4;

extern undefined4 func_002DE618(undefined4);

#ifndef RAC2_T_TWO_F73AF1964
#define RAC2_T_TWO_F73AF1964
#endif

/* func_002D5EC0 is in 002D5E98-list-g8.c. */

/* func_002D6230 is in 002D5E98-render-g8.c. */

/* func_002D68D8 is in 002D5E98-g8.c. */

typedef struct { char pad[4]; short mode; } Mode2D6E78;
typedef struct { char pad[0x29C]; int flags[5]; int selected; } Map2D6E78;
typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern Mode2D6E78 D_001A63A8;
extern Map2D6E78 D_001C4FA0;
extern State2D6E78 D_001F2840;
extern void func_002B7AD0(void);

typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 D_0025A6E0;
/* D_001A7B90 is the 40-byte saved settings block (func_00298E08 copies it whole). Read as
   fields, its symbol+offset macro loads never fill a delay slot, as in retail. The two
   sliders are numbered by the menu row that edits them. */
typedef struct {
    char pad00[8];
    int mode;
    int slider1;
    int slider0;
    char pad14[0x28 - 0x14];
} Settings2D7B18;
extern Settings2D7B18 D_001A7B90 __attribute__((sda));
/* Sound menu input: back and close, row navigation, volume sliders and the mode toggle. */
/* func_002D7DB8 is in 002D5E98-audio.c. */

typedef struct { char pad0[0x36C]; int offset; char pad370[0x16B0 - 0x370]; int start; int length; } Stream2D81B0;
typedef struct { unsigned int key; unsigned int flags; } Slot2D81B0;
extern Stream2D81B0 D_0014B540;
#define MACRO_ADDR __attribute__((section(".sdata")))
extern Slot2D81B0 D_001B1F50[] MACRO_ADDR;
/* Halves the stream length while it marks the slots whose key is older than the clock and
   (outside the mode) asks for the next block; the result picks state 1 or 3. */
extern void func_002B7AD0(void);
/* The loader object of func_002D81B0: its flags, the entry table it replaced and its state. */
/* Advances the loader: starts the read, then unpacks the loaded block and relocates its entries. */
/* func_002D89D8 is defined in 002D5E98-listbox.c. */

#define NOT_SDA __attribute__((section(".data")))

extern unsigned char r1_D_001414F4 NOT_SDA;

/* A short-returning inline keeps retail's branch: the select happens in
   HImode, which has no movcc pattern, so jump.c cannot turn it into the
   xori/movz a promoted `short` local gets. */

/* rac1-decomp src/game/pause.c: func_0021EDD8 */
/* The select sits in a `static inline short` helper so that it stays a
   branch: jump.c turns an if into movz/movn only when its arm sets a
   full register, and the inline's short return value is a subreg. */
/* Scans the object's 24 effect slots: a slot whose entry flag is clear, whose
   "used" byte is set, and whose table word is zero is skipped.  Slot 7 also
   skips a live, in-range material.  The remaining slots dispatch by slot
   number: most first test the material on the shared record, and every slot
   that is still live is handed to the effect runner with the "run" flag. */
/* func_002D99E8 is built from 002D99E8-g8.c for small-data access. */

/* func_002D9DA0 is in 002D5E98-texture.c. */

/* The screen position the object is drawn at, and the 64-bit packet its draw call carries. */
typedef struct {
    char pad[0x160];
    short x;
    short y;
} ScreenPos_2DA118;

extern ScreenPos_2DA118 D_001A6480;
extern void func_0027E018(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws the object at the screen position in D_001A6480, sized by the object's own width
   and height. The draw's colour is a grey 0x808080 whose top byte comes from the object's
   counter: with the 0x40000 flag set it is the counter itself, scaled and clamped, and
   without it the colour is plain 0x80808080. Returns 0 when the object draws nothing. */
/* Re-initialises a state block: clears field 68, builds two sub-records from the flag word at field 52 masked with 0x200, substitutes a default record for any that came back zero, then clears field 92, sets fields 84 and 80 to -1 and returns 0. */
/* func_002DA328 is in 002D5E98-stream.c. */

/* A menu panel: drawn as a texture rectangle (at its own position with flag 8 of the first
   flags word, else at the screen size in D_001A6480), or for modes 0 and 1 as a message. */
typedef struct {
    char pad0[0x10];
    unsigned int placement;
    char pad14[4];
    int x, y;
    int width, height;
    char pad28[0xC];
    unsigned int flags;
    int u_width, v_height;
    char pad40[4];
    int mode;
    int texture[2];
    int choice[2];
    int active;
} MenuPanel2DA9A8;

/* RAC1's font window (pause.c struct TextRegion). */
typedef struct {
    short top, bottom, left, right;
    short anchor_x, anchor_y;
    short measured_width, rendered_height;
    short line_advance;
    unsigned short flags;
    short subpixel_x, subpixel_y;
} TextWindow2DA9A8;

typedef struct { short pad0[2]; short type; short id; short pad8; } MenuRow2DA9A8;
typedef struct { char pad0[0x48]; MenuRow2DA9A8 *rows; } MenuRows2DA9A8;
typedef struct { char pad0[0xE8]; MenuRows2DA9A8 *rows; } MenuOwner2DA9A8;

typedef struct { char pad0[8]; int state; char padC[0x150]; int stage; char pad160[4]; int status; } Scene2DA9A8;
extern Scene2DA9A8 D_001393E0;

/* D_001F2840 seen through the fields this function reads. */
typedef struct {
    char pad0[0x14];
    MenuOwner2DA9A8 *owner;
    char pad18[0x120];
    int message_override, message;
    char pad140[0x24];
    int age;
} Menu2DA9A8;
#define Menu_2DA9A8 (*(Menu2DA9A8 *)&D_001F2840)

extern unsigned char D_001A7AF8[];
extern unsigned char D_001395B8[];
extern int func_002B49C8(int);
extern unsigned char *func_00288FB8(int);
extern void func_0027C540(int);
extern void func_0027C660(void);
extern void func_00280200(TextWindow2DA9A8 *, long, unsigned char *, int);
extern unsigned long long func_00294C40(int);

/* Draws the menu panel. Modes 0 and 1 print message 0x2E00 (or the menu's override) centred
   in the panel, as a black shadow and then in colour one pixel up and left, and return 2
   (1 when the panel's 0x100 flag is clear). Other modes draw the chosen texture and return 16,
   or 1 when flag 4 is set and the chosen row's entry is not available. */
int func_US2_002DB700(MenuPanel2DA9A8 *menu)
{
    unsigned long long texture;
    unsigned char *text;
    MenuRow2DA9A8 *row;
    int message;

    if (menu->active < 0 || func_002B49C8(6)) return 0;
    if (menu->mode < 2) {
        if (!(menu->flags & 0x100)) return 1;
        if (D_001393E0.state == 2
            && !(D_001393E0.stage < 3 && D_001393E0.status < 0 && Menu_2DA9A8.age > 10)) {
            func_0027C540(0);
            message = 0x2c96;
            if (Menu_2DA9A8.message_override) message = Menu_2DA9A8.message;
            text = func_00288FB8(message);
            {
                TextWindow2DA9A8 window = {1, menu->height + 1, 1, menu->width + 1,
                                           menu->width >> 1, 5, 0, 0, 16, 5};
                func_00280200(&window, 0x80000000L, text, -1);
                window.anchor_y = (menu->height - window.rendered_height) >> 1;
                window.flags ^= 4;
                func_00280200(&window, 0x80000000L, text, -1);
                window.top--;
                window.bottom--;
                window.left--;
                window.right--;
                window.anchor_x--;
                window.anchor_y--;
                func_00280200(&window, 0x80FFA888L, text, -1);
            }
            func_0027C660();
        }
        return 2;
    }
    if (menu->flags & 4) {
        unsigned int selection = (menu->mode < 4) ^ 1;
        row = &Menu_2DA9A8.owner->rows->rows[menu->choice[selection]];
        if (row->type == 0) {
            short id = row->id;
            if (!D_001A7AF8[id]) return 1;
        }
        if (row->type == 1 && !D_001395B8[row->id]) return 1;
    }
    func_0027C540(0);
    if (menu->mode < 4) texture = func_00294C40(menu->texture[0]);
    else texture = func_00294C40(menu->texture[1]);
    if (menu->placement & 8)
        func_0027E018(menu->x, (char *)menu->y, menu->width, menu->height, 0, 0,
                      menu->u_width, menu->v_height, 0x80808080ULL, texture);
    else
        func_0027E018(0, 0, D_001A6480.x, D_001A6480.y, 0, 0,
                      menu->u_width, menu->v_height, 0x80808080ULL, texture);
    func_0027C660();
    return 16;
}

/* The stream block D_0014B540 seen as its two tables of five {start, length} reads,
   picked by D_001A7BB4 modulo 5. */
/* Starts the read of the object's first, then its second stream once D_001A63AC is clear:
   states 0 to 4, or -1 when a read is refused. */
/* func_002DAE90 is in 002D5E98-g8.c. */

/* The map screen's frame: the page and image being shown and the two frame textures. */
extern char *D_001F2854;
/* The frame counter as an incomplete sda array: retail's tied absolute macro load. */
/* Draws the textured frame around the map dialog, scrolling the inner texture. */
/* func_002DB3C0 is in 002DB3C0.c. */

/* Choice list input: close, back, row navigation and cycling the selected row's value. */
/* func_002DB7F0 is in 002DB7F0.c. */

/* func_002DB988 is defined in 002DB988-init-g8.c. */

extern char *D_001F2854;

undefined8 func_002DBB48(int param_1);

typedef struct { char reserved00[0x14]; char *object; int value; char reserved1C[0xC8]; int clear; } SceneState;
extern SceneState ref_L00_002DBB78_00;
/* func_002DBC10 is defined in 002DBC10.c. */

#define MACRO_ADDR __attribute__((section(".sdata")))

/* MACRO_ADDR: lui/lw where retail has them, $gp-relative in a delay slot
   (r1_func_0021F7D0, r1_func_002229B0). */
extern int r1_D_0015EE84 MACRO_ADDR;

/* rac1-decomp src/game/pause.c: func_00222D70 */
/* `r1_D_001D48A8[(unsigned)r1_D_0015EE84 % 19]`; the older near-miss
   predated MACRO_ADDR. */
extern int D_00138180[];
extern int D_001F2974;
extern void func_002DF190(int, int);

extern int D_00138180[];
extern int D_001F2974;
extern void func_002DF190(int, int);

/* Two-branch draw set-up: copies a 2-byte record from one of two tables into a 16-byte local, then issues a draw call with five float arguments (scale, per-instance angle, two constants, colour value) plus a 64-bit attribute word, a geometry handle, a fifth integer argument -1 and a local buffer. */
/* func_002DC720 is matched in its own unit, src/game/002DC720.c (its jump table). */

/* func_002DC900 is built from 002DC900-g8.c for small-data access. */

/* func_002DCAB8 is built from 002D5E98-g8.c for small-data access. */

