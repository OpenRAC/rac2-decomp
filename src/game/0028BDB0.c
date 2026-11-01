#include "include_asm.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef int s32;

extern void func_0028BCE8(void);

/* authored C for independently verified level-native body */
void func_0028BDB0(u8 *object) {
 func_0028BCE8();
 *(s32 *)(object+0x58)=210;*(s32 *)(object+0x5c)=200;
 *(s32 *)(object+0x74)=-2;*(s32 *)(object+0x78)=30;
 *(u16 *)(object+0x48)=0;*(u16 *)(object+0x4a)=0;*(s32 *)(object+0x70)=0;
}

/* func_0028C6D0 is defined in 0028BDB0-wheel-g8.c. */


INCLUDE_ASM("asm/game", func_0028CCE0);

INCLUDE_ASM("asm/game", func_0028D1E8);

extern int func_0028B740(void *, int *, int *);
extern void func_0028B7A8(void *, int *, int *, int, int);
extern int func_0028E588(int, int);
extern void func_0028ECD8(int,int,int,int,int,int);
extern void func_0028E868(int,int,int,int,int,int);
extern short D_0018B69A;
int func_0028DDD8(char *o) {
 int x=*(int *)(o+0x50), y=*(int *)(o+0x54);
 int w;
 *(int *)(o+0x58)=256; *(int *)(o+0x5c)=64;
 func_0028B740(o,&x,&y);
 func_0028B7A8(o,&x,&y,*(int *)(o+0x6c),0);
 w=*(int *)(o+0x74)*221 / *(int *)(o+8)+27;
 func_0028ECD8(func_0028E588(0x7558,1),x,y,w,64,128);
 func_0028E868(func_0028E588(0x7558,0),x,y,256,64,128);
 func_0028E868(func_0028E588(0x7558,2),x,y,32,32,D_0018B69A?128:0);
 return *(int *)(o+0x58);
}

void func_0028DF38(char *object) { extern void func_0028B950(u8 *); *(int *)(object + 0x58) = 0x20; *(int *)(object + 0x7C) = 0x96; *(int *)(object + 0x5C) = 0x20; func_0028B950((u8 *)object); }

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
int func_0028E138(int arg)
{
    char *rec;
    char *end;
    int count = 0;

    func_0028E2A8();
    rec = (char *)D_00255330;
    end = (char *)D_00255330 + 0x750;
    do {
        int v;

        if ((*(int *)(rec + 4) & 0x10) || D_001B1874) {
            v = *(int *)(rec + 0x7C);
            if (v < 10) {
                *(int *)(rec + 0x7C) = 10;
            }
            v = *(int *)(rec + 0x7C);
        } else {
            v = *(int *)(rec + 0x7C);
        }

        if (v > 0) {
            v = v - 1;
            *(int *)(rec + 0x7C) = v;
            if (v > 0) {
                count++;
                if (*(int *)(rec + 0x6C) < 30) {
                    *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) + 1;
                }
            } else if (*(int *)(rec + 0x6C) >= -5) {
                *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) - 1;
            }
        } else if (*(int *)(rec + 0x6C) >= -5) {
            *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) - 1;
        }

        if (*(int *)(rec + 0x68) != 0) {
            if (*(int *)(rec + 0x6C) == -6) {
                func_0028B4D8(rec);
            }
        }

        if (arg != 0) {
            void (*handler)(char *) = *(void (**)(char *))(rec + 0x14);
            if (handler) {
                handler(rec);
            }
        }
        rec += 0x90;
    } while ((int)rec < (int)end);
    return count;
}

typedef struct { char reserved00[0x1248]; int selected; char reserved124C[0x1068]; unsigned char blocked; } MapSelection;
typedef struct { char reserved00[0x88]; unsigned short valid; char reserved8A[0x56]; } MapRecord;
extern MapSelection D_00189E20;
extern unsigned char D_00139568[];
extern MapRecord ref_L00_0028E260_00[];
int func_0028E260(void)
{
    int selected = D_00189E20.selected;
    int blocked = D_00189E20.blocked;
    unsigned int index = D_00139568[selected];
    if (((MapRecord *)(index * 0xE0 + (unsigned int)ref_L00_0028E260_00))->valid == 0) selected = 0;
    if (blocked) selected = 0;
    return selected;
}

INCLUDE_ASM("asm/game", func_0028E2A8);
