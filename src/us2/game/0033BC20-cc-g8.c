/* func_US2_0033BC20, the USA v2.00 copy of func_0033ABD8: the same C, where rename func_003369A8 becomes func_US2_003377B0; swap locals *record *vel278; swap locals *rec198 *vel280. */

extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_US2_003377B0(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern int func_00288FB8(int);
extern char *D_001A8CFC[] __attribute__((sda));
/* Binds the screen to its owner: allocates the 16-byte position block, initialises the four
   76-byte and nine 72-byte widgets by name ("0".."3", "title", "missions", ...), sets their
   colours, fonts and labels, marks the "  Exit" label with glyph 0x12 and lays them out.
   The block's four zero stores are written 1, 2, 3, 0 for retail's 0, 4, 8, C order. */
/* The X bias lives in small data, so this file is built with -G8. */
extern void func_00335E38(char *, float, float, float, float);

/* Offsets the record position by the two resident biases and hands it to the
   shared spawn helper with no rotation. */
/* The table of four resident ints is reached through $gp and the resident
   pointer through the small-data unit, so this body needs -G8. */
extern char *D_001A8CFC[] __attribute__((sda));
extern char D_001ADC88[];
extern int *func_00335E20(void *);
extern int func_00288FB8(int);
typedef struct { int first, second, color; float angle; short id; short pad; int text; } Entry_0033A6D8;
#define ENTRY_0033A6D8 (*(Entry_0033A6D8 **)self)[i]

/* Draws the selection list: two fixed sprites, then one sprite per entry placed around the stored
   position (the radius at +0x204 scales the cosine and the sine of the entry's angle), and for the
   selected entry the cursor sprite and its label. A mode (the ints from +0x1B8) of 1 gives the
   sprite the tint 0x80808080 instead of the entry's own colour; a mode of 2 clears the flag given
   to func_00335E68 and keeps the cursor from being moved and labelled.
   ENTRY_0033A6D8 is entry i of the array that starts at self + 0. `one` holds the 1 of the mode
   test in a register of its own: written as a bare 1 in the comparison, the constant is not
   hoisted out of the loop. The pointer to the modes is assigned where it is first used, and the
   cursor sprite (self + 4) reaches its virtual call through a variable: these decide which
   induction variable and which register the compiler picks. */
#undef ENTRY_0033A6D8

extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_US2_003377B0(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00115484(void *, int, int);
extern char D_001ADC80[], D_001ADC88[];
extern int D_001ADD40[2] __attribute__((sda));

/* Constructor of a gadget made of five sprite slots (76 bytes each from +0xC, switched on by the
   five shorts of LIST, which are also kept at +0x188) and three 72-byte sprites at +0x198, +0x1E0
   and +0x228, each with an 8-byte offset beside it at +0x278, +0x280 and +0x288.  The blank name
   is D_001ADC88; the slot loop reaches it as D_001ADC80 + 8 and the three sprites through the
   spent list pointer, which keeps the compiler from hoisting it across the loop. */
void func_US2_0033BC20(char *object, char *owner, short *list)
{
    char *vel278, *vel280, *rec1E0, *rec228, *record, *rec198, *vel288;
    short *flags, *p;
    int *color;
    int i;

    *(char **)(object + 8) = owner;
    if (owner) {
        int *allocation = func_00336DA8(16, func_00336E40(owner));
        *(int **)object = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    vel278 = object + 0x2a8;
    rec198 = object + 0x198;
    vel288 = object + 0x2b8;
    rec228 = object + 0x248;
    flags = (short *)(object + 0x188);
    rec1E0 = object + 0x1f0;
    color = D_001ADD40;
    record = object + 0xC;
    vel280 = object + 0x2b0;
    p = list;
    for (i = 4; i >= 0; i--) {
        if (*p != 0) {
            func_003361E0(record, D_001ADC80 + 8, owner);
            *func_00335E20(record) = *color;
            func_00336390(record, D_001A8CFC[0] + 0x8710, *p);
        }
        *flags = *p;
        color++;
        record += 0x4C;
        p++;
        flags++;
    }
    p = (short *)D_001ADC88;
    func_US2_003377B0(rec198, p, owner);
    func_00115484(vel278, 0, 8);
    func_00335E38(rec198, 0.0f, 0.0f, 0.0f, 0.0f);
    *func_00335E20(rec198) = 0x80F0F0F0;
    func_US2_003377B0(rec228, p, owner);
    func_00115484(vel288, 0, 8);
    func_00335E38(rec228, 0.0f, 0.0f, 0.0f, 0.0f);
    *func_00335E20(rec228) = 0x80F0F0F0;
    func_US2_003377B0(rec1E0, p, owner);
    func_00115484(vel280, 0, 8);
    func_00335E38(rec1E0, 0.0f, 0.0f, 0.0f, 0.0f);
    *func_00335E20(rec1E0) = 0x80F0F0F0;
    *(float *)(object + 0x2a4) = 0.0f;
    *(int *)(object + 0x2c0) = 1;
    *(int *)(object + 0x2c4) = 1;
    *(int *)(object + 4) = 0;
    *(int *)(object + 0x2cc) = 1;
}
