/* func_PAL_00353D08, the PAL copy of func_00351B20: the same C, where rename func_0034FE18 becomes func_PAL_00352000; rename func_0012F950 becomes func_0012F948. */

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 func_0011AC60(s32);

extern s32 func_0011AC40(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 func_0011AC60(s32 a0);

extern s32 func_0011AC40(s32 a0);

typedef unsigned int u32;

extern int func_00351E58(unsigned char *);

/* func_00351578 is matched in 00351578.c. */

typedef struct { unsigned long long first, second; int offset, count; } Transfer_3518F0;

extern int func_00351310(void *, Transfer_3518F0 *);

/* a % b as a helper: once inlined, its zero-divisor check is tested against $0 */

/* func_00351310 : walks the transfer ring, trimming one message out of the slots */
int func_00351310(void *owner, Transfer_3518F0 *message);

int func_00351468(void *owner, Transfer_3518F0 *message, int unused);

/* func_00351720 is matched in 00351720.c. */

/* Forwards the byte count to the object's transfer buffer. */
/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
s32 func_003518D8(u8 *a0);

extern char *D_001B23CC[] __attribute__((sda));
extern int func_00351468(void *, Transfer_3518F0 *, int);

/* func_00351960 : builds a 16-byte packet (a 4-byte header copied from D_001AE860 and a
   12-byte body), asks the object for the two memory ranges it holds, and moves them into
   the packet.  The two addresses are turned into 32-bit engine addresses. */
typedef struct { char tag[4]; } Header_351960;

extern Header_351960 D_001AE860;

/* These wrappers have different targets in the level programs. */
extern void func_00351E48(u8 *);
extern int func_PAL_00353D08(void *);
extern void func_0026FEB8();
extern char D_001AE868[];
extern char D_001AE880[];
extern int func_0012F9A8(void *);
extern void func_0012F9C8(void *);
extern int func_0012F948(void *, void *, int);
extern void func_0034F3B8(void);
extern void func_0034F780(char *);
extern void *func_00351EE8(char *);
extern void func_00351E70(u8 *);
extern void func_PAL_00352000(void *, void *, int, int, int);

int func_PAL_00353D08(void *p)
{
    int *object = p;
    int result = 1;
    void *packet;
    int i;

    while (func_0012F9A8(object) == 0) {
        if (func_003518D8((u8 *)object) == 1) {
            result = -1;
            func_0026FEB8(D_001AE868);
            break;
        }
        while ((packet = func_00351EE8(D_001B23CC[0] + 0xD9168)) == 0)
            func_0034F3B8();
        if (func_0012F948(object, packet, 0x340) < 0)
            func_0034F780(D_001AE880);
        if (object[2] == 0) {
            int a = object[0];
            int b = object[1];
            for (i = 0; i < *(int *)(D_001B23CC[0] + 0xD9178); i++)
                func_PAL_00352000(*(char **)(D_001B23CC[0] + 0xD916C) + i * 0x138C0 + 0x40,
                              *(char **)(D_001B23CC[0] + 0xD9168) + i * 0xD0000, a, b, i);
        }
        func_00351E70((u8 *)(D_001B23CC[0] + 0xD9168));
        func_0034F3B8();
    }
    func_0012F9C8(object);
    return result;
}

extern void func_0026FEB8(void *, int);

extern char *D_001B23CC[] __attribute__((sda));
extern char *D_001B23CC[] __attribute__((sda));
extern char *D_001B23CC[] __attribute__((sda));
void func_00351E48(u8 *a0);

/* lot13 -- measured bodies with sizes recorded in the catalogue. */
s32 func_00351E58(u8 *a0);

void func_00351E70(u8 *a0);
