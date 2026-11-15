#include "common.h"

/* The object preview's sequencer (func_002FF450), in a unit of its own: it is
   built with -g, whose line label before each division keeps the two padding
   nops retail has in front of div.s, and its jump table is the unit's only
   .rodata. */

/* State of the object preview (PreviewState in 002FC8D0.c), seen whole. It is
   a small-data object: fields past the first halfword are offsets from it
   (two-word macros that never fill a delay slot), while the state halfword is
   a one-word access that the assembler turns into a $gp store in a delay
   slot. */
typedef struct {
    short state;              /* 0x00 */
    short frames;             /* 0x02 */
    float rate;               /* 0x04 */
    short s08;                /* 0x08 */
    char pad0A[0x0D - 0x0A];
    unsigned char b0D;        /* 0x0D */
    short s0E;                /* 0x0E */
    char pad10[0x30 - 0x10];
    char *object;             /* 0x30 */
    unsigned char phase;      /* 0x34 */
    unsigned char spin;       /* 0x35 */
    short alpha;              /* 0x36 */
} PreviewState;

/* The camera (PreviewCameraPrefix in 002FC8D0.c). */
typedef struct {
    char reserved000[0x140];
    float position[4];        /* 0x140 */
    float rotation[4];        /* 0x150 */
    char reserved160[0x370 - 0x160];
    float forward[4];         /* 0x370 */
} PreviewCamera;

/* The subtitle owner (SubtitleOwnerUpdate in 00289178.c). */
typedef struct {
    char pad00[0x6C];
    short id;
    char pad6E[4];
    short state;
} PreviewSubtitleOwner;

extern PreviewState D_001B2310 __attribute__((sda));
extern PreviewCamera D_001B5200;
extern PreviewSubtitleOwner D_001A63A8;
extern int D_001AD7E4 SDATA(D_001AD7E4) __attribute__((sda));
extern int D_001AD7E8 SDATA(D_001AD7E8) __attribute__((sda));
extern int D_001AD7F8 SDATA(D_001AD7F8) __attribute__((sda));
extern int D_001AD7FC SDATA(D_001AD7FC) __attribute__((sda));
extern int D_001AD800 SDATA(D_001AD800) __attribute__((sda));
extern int D_001AD804 SDATA(D_001AD804) __attribute__((sda));
extern float D_001B90F0;
extern short D_0018A000;

extern int func_00282978(short *);
extern int func_002B6D28(void);
extern void func_00283360(float *);
extern void func_0027AB40(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027D098(void (*)(void), int);
extern void func_002FFCF8(void);
extern void func_002FFFE0(void);
extern void func_002FF3F8(void);
extern void func_002FF968(char *);
/* Retail passes the object in $a0; the matched body does not read it. */
extern void func_002FFD78(char *);
extern char *func_002FFB68(char *);
extern void func_00287EB0(int);
extern void func_00288508(int);
extern void func_002AD860(int);
extern int func_002B49E0(int, int, int, int, int);

/* Steps the object preview through its eight states: wait for the subtitle
   owner (at most 181 frames), set up the camera and the object, show it,
   fade, release it and hand control back. */
void func_002FF450(void)
{
    char *object, *current;
    float angle, sine, tangent, zero;

    switch (gObjectPreviewState.state) {
    case 0:
        if (FastDecTimer(&gObjectPreviewState.frames)
            && !(D_001AD7E4 && (gMusicState.state != 3 || gMusicState.id >= 6000)
                 && D_001AD7E8++ < 181)) {
            ResumeMusicStream();
            gActiveCamera.position[0] = 25.0f;
            gActiveCamera.position[2] = 900.0f;
            gActiveCamera.position[1] = 25.0f;
            D_001AD7E4 = 0;
            D_001AD7E8 = 0;
            set_identity_rotation_rows(gActiveCamera.forward);
            object = gObjectPreviewState.object;
            zero = 0.0f;
            gActiveCamera.rotation[2] = zero;
            gActiveCamera.rotation[1] = zero;
            gActiveCamera.rotation[0] = zero;
            gObjectPreviewState.state = 1;
            gObjectPreviewState.frames = D_001AD7FC;
            gObjectPreviewState.s0E = 0;
            qcopy(object + 0xF0, gActiveCamera.rotation);
            if (gObjectPreviewState.spin)
                *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), -1.5707964897155762f);
            angle = 0.5621705651283264f;
            sine = FastSinOrCosB(angle);
            tangent = sine / FastSinOrCosA(angle);
            D_001B90F0 = tangent;
            UpdateViewContext();
            *(unsigned short *)(object + 0x34) &= ~0x41;
        } else {
            RegisterFinalDrawCallback(DrawPreviewFadeOverlay, 0);
        }
        break;
    case 1:
        PlaceObjectBeforeCamera(gObjectPreviewState.object);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.frames = D_001AD800;
            gObjectPreviewState.rate = 1.0f / IntToFloat(gObjectPreviewState.frames);
            gObjectPreviewState.state = 2;
            gObjectPreviewState.phase = 0;
        }
        break;
    case 2:
        current = gObjectPreviewState.object;
        PlaceObjectBeforeCamera(current);
        EmitParticlesBeforeCamera(current);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.frames = 2;
            gObjectPreviewState.state = 3;
            gObjectPreviewState.alpha = 128;
            RegisterFinalDrawCallback(DrawPreviewDimOverlay, 0);
        }
        break;
    case 3:
        current = gObjectPreviewState.object;
        RegisterFinalDrawCallback(DrawPreviewDimOverlay, 0);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.frames = 12;
            gObjectPreviewState.state = 4;
            gObjectPreviewState.object = SpawnModeEffectObject(current);
        }
        break;
    case 4:
        if (gObjectPreviewState.object)
            PlaceObjectBeforeCamera(gObjectPreviewState.object);
        RegisterFinalDrawCallback(DrawPreviewDimOverlay, 0);
        gObjectPreviewState.alpha = FloatToInt(IntToFloat(gObjectPreviewState.frames) * (1.0f / 12.0f) * 128.0f);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.state = 5;
            gObjectPreviewState.frames = D_001AD804;
            gObjectPreviewState.alpha = 0;
        }
        break;
    case 5:
        if (gObjectPreviewState.object)
            PlaceObjectBeforeCamera(gObjectPreviewState.object);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.frames = 3;
            gObjectPreviewState.state = 6;
        }
        break;
    case 6:
        if (gObjectPreviewState.object)
            PlaceObjectBeforeCamera(gObjectPreviewState.object);
        RegisterFinalDrawCallback(DrawPreviewFadeOverlay, 0);
        if (FastDecTimer(&gObjectPreviewState.frames)) {
            gObjectPreviewState.frames = 0;
            gObjectPreviewState.rate = 1.0f / IntToFloat(D_001AD7F8);
            gObjectPreviewState.b0D = gObjectPreviewState.s0E = 1;
            D_0018A000 = D_001AD7F8 + 5;
            SetupPreviewObject();
            gObjectPreviewState.object = 0;
            AdvanceChainEntry(gObjectPreviewState.s08);
            ShowHelpMessageForId(gObjectPreviewState.s08);
            if (gObjectPreviewState.spin)
                HandleRequestSlotState(gObjectPreviewState.s08);
            gObjectPreviewState.state = 7;
        }
        break;
    case 7:
        if (gObjectPreviewState.frames++ >= D_001AD7F8)
            BeginSlotRequest(0, 2, 0, 0, 0);
        else
            RegisterFinalDrawCallback(DrawPreviewFadeOverlay, 0);
        break;
    }
}
