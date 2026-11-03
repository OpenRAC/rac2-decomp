/* functional: high. Unchecked: every captured call stays in the movie loop past the gate's 40M-instruction budget (NOTHING COMPARED). Read 0x2F5FB8-0x2F6454 in full: same calls, arguments, reads and writes in retail's order; the TEX0 word is built as one 64-bit value (retail's shifts give the same bits); the dead read-back of stream->mode when the decoder does not return 1 is kept. func_0034EF58 is declared as the port's host function (int arguments). */

/* Plays the current FMV (the stream handle D_001B220C, set up by func_002F5E20): if there is none it shows the
 * message D_001AD178 and ends the movie state (D_001BAD40). Otherwise it uploads the movie's two textures
 * (display slot 2 of D_001B9740, images from D_001B1604), sets the slot's 64-bit TEX0 word for the frame
 * size, waits for the sound streams to idle, then decodes frames with func_0034EF58 into the two buffers at
 * D_001BAEC0 +0x0C/+0x14 (64-aligned), loading each frame's audio descriptor (D_001B2210) through
 * func_002B7C80, and advancing either a scripted frame list (D_001BAD40[0] counter, 1..24) or the stream
 * (func_00288A00) until it ends; the next chunk's sector and size come from the table of contents
 * D_0014B540. Finally it restores the texture, clears the slot's TEX0 word and either chains the next
 * scene (func_002B49E0(2, 2, frame, 0, 0)) or returns to the game (func_002B4B70(0, 0)). */

typedef struct {
    unsigned long packet;       /* 0x00: 64-bit TEX0 word */
    unsigned short tex0, tex1;  /* 0x08 */
    short width, height;        /* 0x0C: log2 */
} FmvDisplaySlot;

typedef struct {
    int frame;                  /* 0x00: scripted frame counter */
    short *frames;              /* 0x04 */
    char pad08[0x30];
    int active;                 /* 0x38 */
    int mode;                   /* 0x3C */
} FmvStream;

extern int D_001B2208;          /* the next chunk's sector */
extern int D_001B220C;          /* the stream handle / the next chunk's size */
extern int *D_001B2210;         /* the frame's audio descriptor: sector, size */
extern int D_001B2214;
extern int D_001B2218;
extern char D_001AD178[];
extern int D_001BAD40[];
extern int D_001BAEC0[];
extern FmvDisplaySlot D_001B9740[];
extern char *D_001B1604;
extern int D_001B8840[];
extern int D_001393E0[];
extern int D_0014B540[];
extern char D_001339B0[];

extern void func_0029CC98(void *, int);
extern void func_00288BB8(void *);
extern void func_002B4B70(int, int);
extern void func_002FC3C0(int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(void *, void *);
extern int func_001244B8(int, int);
extern void func_002E5FE0(void);
extern void func_002B7170(void);
extern int func_00133580(int);
extern void func_00298F00(void);
extern int func_002B7C80(char *, int, int);
extern int func_0034EF58(int, int, int, int, int, int);
extern int func_00288A00(void *, int *, int *);
extern int func_002EF010(int);
extern void func_00126DC0(void *);
extern void func_002F0FA0(void);
extern int func_002B49E0(int, int, int, int, int);
extern void func_002FC1D8(void);

void func_002F5FB8(void)
{
    int packet[32] __attribute__((aligned(16)));    /* the GS image-transfer packet (0x60 bytes used) */
    FmvDisplaySlot *display;
    FmvStream *stream = (FmvStream *)D_001BAD40;
    char *destination;
    int first, second;
    int frame, status, done, result, nextFrame;
    unsigned long word;

    if (D_001B220C == 0) {
        func_0029CC98(D_001AD178, -1);
        func_00288BB8(D_001BAD40);
        func_002B4B70(0, 0);
        return;
    }
    second = D_001BAEC0[5];
    first = D_001BAEC0[3];
    destination = (char *)(second + 0xE0000);
    display = &D_001B9740[2];
    func_002FC3C0(1);
    func_00126288(packet, 0x3F70, (short)((1 << display->width) >> 6), 0x13, 0, 0,
                  (short)(1 << display->width), (short)(1 << display->height));
    func_0011AEA0(0);
    func_001265B0(packet, D_001B1604 + display->tex0 * 16);
    func_001244B8(0, 0);
    func_00126288(packet, 0x3F6C, 1, 0, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(packet, D_001B1604 + display->tex1 * 16);
    func_001244B8(0, 0);
    word = ((unsigned long)(long)((1 << display->width) >> 6) << 14) | 0x3F70;
    word |= ((unsigned long)(long)display->width << 26) | 0x1300000;
    word |= (unsigned long)(long)display->height << 30;
    word |= 0x7ED8400000000UL;
    word |= 0x8000000000000000UL;
    display->packet = word;
    func_0011AEA0(0);
    func_002E5FE0();
    func_002B7170();
    func_00133580(0);
    while (D_001393E0[0x15C / 4] >= 3 || D_001393E0[0x164 / 4] >= 0)
        func_00298F00();

    frame = 0;
    status = -1;
    first += 63;
    second += 63;
    done = 0;
    do {
        int *descriptor = D_001B2210;
        if (descriptor != 0 && descriptor[0] != 0) {
            func_002B7C80(destination, descriptor[0] + D_0014B540[1], (descriptor[1] + 2047) / 2048);
            D_001B8840[0x34 / 4] = 0;
            D_001B8840[0x4C / 4] = (int)destination;
        } else {
            D_001B8840[0x4C / 4] = 0;
            D_001B8840[0x34 / 4] = 0;
        }
        result = func_0034EF58(D_001B2208, D_001B220C, first & -64, second & -64, D_001B2214,
                               D_001B2218 != 0);
        if (result == 1)
            stream->mode = 1;
        else
            stream->mode = stream->mode;
        if (result != 0) {
            stream->mode = 1;
            func_00288BB8(stream);
        }
        if (stream->frame != 0) {
            stream->frame = stream->frame + 1;
            if (stream->frame >= 25)
                stream->frame = 1;
            nextFrame = stream->frames[stream->frame];
        } else {
            if (stream->active == 0) {
                done = 1;
                continue;
            }
            func_00288A00(stream, &frame, &status);
            if (status != 0) {
                if (status == 1)
                    done = 1;
                continue;
            }
            nextFrame = frame;
        }
        {
            int offset = (func_002EF010(nextFrame) << 4) | 8;
            int sector = *(int *)((char *)D_0014B540 + 8 + offset);
            int size = *(int *)((char *)D_0014B540 + 12 + offset);
            D_001B2208 = sector + D_0014B540[1];
            D_001B220C = size;
        }
    } while (!done);

    func_00133580(0);
    func_00126DC0(D_001339B0);
    func_001244B8(0, 0);
    display = &D_001B9740[2];
    func_001265B0(packet, D_001B1604 + display->tex1 * 16);
    func_001244B8(0, 0);
    func_002F0FA0();
    display->packet = 0;
    func_002FC1D8();
    if (result == 0 && status == 1)
        func_002B49E0(2, 2, frame, 0, 0);
    else
        func_002B4B70(0, 0);
}
