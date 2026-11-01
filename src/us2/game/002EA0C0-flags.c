#include "include_asm.h"

#include "common.h"
#define scene (&D_001B8840)
#define state (&D_00152C00)
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define UH(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad00[0xC];
    unsigned char count;
    char pad0D[0x3B];
    int slots[1];
} PlaybackClass;
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char status;
    char pad21[3];
    PlaybackClass *classData;
    char pad28[0xA];
    short drawDistance;
    unsigned short flags;
    char pad36[2];
    unsigned long long colorData;
    unsigned char frame, nextFrame;
    char pad42[2];
    float animTime;
    char pad48[0x10];
    char *joints, *previousJoints;
    unsigned char pad60, animId, opacity, mobyState;
    char pad64[4];
    char *keys;
    char pad6C[3];
    unsigned char shadowRange;
    char pad70[8];
    unsigned int color;
    char pad7C[0x19];
    unsigned char effectOpacity;
    char pad96[2];
    int updateState;
    char pad9C[0xE];
    short classId;
    char padAC[6];
    short partFlags;
    char padB4[8];
    unsigned char effectScale;
    char padBD[3];
    float matrix[12];
    float rotation[4];
} PlaybackMoby;
typedef struct {
    PlaybackMoby *object;
    char pad04[4];
    PlaybackMoby *extra;
    char pad0C[4];
    PlaybackMoby *hero;
    PlaybackMoby *companion;
    char pad18[8];
    short mode, frame;
    short unused24, skip;
    char pad28[0x18];
    int curveIndex, cameraStart, cameraEnd;
    float progress, speed, length, cameraBlend, cameraVelocity;
    char pad60[0xC];
    int fadeStart;
    char pad70[0x20];
    float startPosition[4], endPosition[4], startRotation[4], endRotation[4];
} PlaybackState;
typedef struct {
    char pad00[0x30];
    int selected, frame, streamFrame, chunk;
    short endFrame, unused42, objectCount;
    char pad46[0x22];
    char *keys;
    char pad6C[0x120];
    PlaybackMoby *objects[0];
} PlaybackScene;
extern PlaybackState D_00152C00;
extern PlaybackScene D_001B8840;
typedef struct { char pad[0x1A4]; unsigned int pressed; } PlaybackController;
extern PlaybackController D_00138180;
typedef struct {
    char pad00[0x24];
    int requestedFrame, requestFlags;
    char pad2C[0x40];
    short streamPosition;
    char pad6E[4];
    short mode;
} PlaybackStream;
extern PlaybackStream D_001A63A8;
typedef struct { char pad[0xB0]; float fieldOfView; } PlaybackScreen;
extern PlaybackScreen D_001B9040;
typedef struct {
    char pad00[0x140];
    float position[4], rotation[4];
    char pad160[0x210];
    float forward[4], right[4], up[4];
} PlaybackCamera;
extern PlaybackCamera D_001B5200;
extern char D_001B4580[], D_00189E20[];
extern char D_00261FE0[], D_001CE4EA[];
extern char D_001A8C30[] __attribute__((sda));
extern char *D_001B1B60[] __attribute__((sda));
extern char *D_001B2148;
extern char *D_001B1C4C[] __attribute__((sda));
extern PlaybackMoby *D_00214920[];
typedef struct { float x, y, z, w; } PlaybackPoint;
typedef struct { int count; char pad04[0xC]; PlaybackPoint points[1]; } PlaybackCurve;
typedef struct { char pad00[0x10]; unsigned char n10; char pad11[2]; unsigned char n13; char pad14[8]; int a1C[1]; } PlaybackBones;
extern PlaybackCurve *D_001F1700[];
extern float D_001B15A0 __attribute__((sda));
extern float D_001B15A4 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001B1694 __attribute__((sda));
extern int D_001A8B84 __attribute__((sda));
extern int D_001A8BB0 __attribute__((sda));
extern unsigned int D_001A7AF0[] __attribute__((sda));
extern short D_0018C31C;
extern float D_001AC1B0[] SDATA(D_001AC1B0);
extern float D_001AC1C0[] SDATA(D_001AC1C0);
extern void func_002F5220(void), func_002B6658(void), func_002E5F60(void);
extern void func_0026F720(void), func_002B9390(void), func_002FC138(void);
extern void func_00294070(int), func_0027D330(int), func_0027AB40(void);
extern void func_0029F338(void *), func_0029F390(void *), func_002A0F48(void *);
extern int func_002B49E0(int,int,int,int,int);
extern void func_002B4B70(int,int);
extern void func_002AB6D8(void *,void *), func_00283410(void *,void *);
extern float func_002A89A8(void *,int,float);
extern void func_002830C0(void *,void *,void *), func_00282CC0(void *,void *,void *);
extern float func_00283B98(float,float), func_00283CE0(int), func_00283BE0(float,float);
extern void func_00129178(void *), func_001292C0(void *,void *,float);
extern void func_00129368(void *,void *,float), func_00129218(void *,void *,float);
extern void func_00282D30(void *,void *,float), func_002A9548(void *);
extern void func_0026F798(void *), func_0026F790(void *,int), func_US2_002E72D8(void *);
extern void func_0027CFD0(void *,void *), func_0027CDC8(void *,void *);
extern void func_002ECB70(void), func_002E6B78(void), func_002E7338(void);
extern float func_00283180(float);
extern void func_002B72E8(int), func_002E4AC8(void);
extern short func_002B7CE0(int);
extern int func_001261F0(int);
extern void func_002B6D28(void);
extern PlaybackMoby *func_0029EFD0(int);
extern void func_00335438(void *,void *,int,int,int);
extern float func_00283248(float,float), func_00282C48(float);
extern float func_00282E48(void *,void *), func_00282E80(void *,void *);
extern void func_002AA548(void *,void *,float,float,float,float);
extern void func_00282D08(void *,void *,void *,float), func_00282C88(void *);
extern void func_00335370(void *), func_003353C8(void *);
extern void func_00283678(void *,void *), func_002A10E8(void *);
extern void func_002E8F80(void *,float), func_002E9110(void *);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_002A1130(void *,int,void *,int);
extern void func_002E7B48(void *), func_US2_00272378(void), func_002914B8(void);
extern void func_0029FFB8(void), func_002F52B8(void);
extern int func_US2_002E91C0(void);

INCLUDE_ASM("asm/us2/game", func_US2_002EA0C0);

