#include "include_asm.h"

extern void func_0033AB50(char *p);

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_00432D98(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_004331D8(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_00433490(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_00433A18(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

extern void func_0033AE28_2(char *p);
extern void func_L00_00430948_3(char *p, float a, float b);
extern void func_002E5E58_3(int a, int b, int c);
extern volatile unsigned char D_001A7B95 __attribute__((sda));
extern volatile unsigned char D_001A7B94 __attribute__((sda));

/* makes two float-binding calls, then toggles one of two global flag bytes selected by an object field and returns bit 6 of the flag word */
int func_US2_L00_00433B78(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    func_0033AE28_2(p);
    q = *(float **)(a0 + 732);
    func_L00_00430948_3(p, q[0], q[1]);
    if (a1 & 0x1000) {
        func_002E5E58_3(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        func_002E5E58_3(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        func_002E5E58_3(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            D_001A7B95 = D_001A7B95 == 0;
            break;
        case 1:
            D_001A7B94 = D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_004344A0(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

extern void func_US2_0033BE70 (char *object);
extern void func_L00_00430948 (char *object, float x, float y);
extern int func_002E5E58 (int a, int b, int c);

/* resets a sub-object, applies a two-float transform, and when bit 6 of flags is set and an int field is zero calls a mode setter and toggles a global byte */
int func_US2_L00_00434600 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7B9E;
  float *vec;
  int discarded;

  func_US2_0033BE70 (object + 8);
  vec = *(float **) (object + 732);
  func_L00_00430948 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = func_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_US2_L00_00434768(char *object)
{
    func_0033AB50(object + 8);
    return object;
}


extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

int func_US2_L00_004348C8(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    Fc558ca70_FUN_0033AE28(p);
    q = *(float **)(a0 + 732);
    Fc558ca70_FUN_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}


extern void Ffb202470_FUN_0033AB50(char *p);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_L00_00434B38(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

int func_US2_L00_00434C98 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7BBA;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_L00_00434DE8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



int func_US2_L00_00434F48 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7BBA;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_L00_00434FE0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



int func_US2_L00_00435140 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7BBA;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


extern void *func_US2_0033BB98(void *);
extern void *func_00347EA0(void *);

void *func_US2_L00_004351D8(char *object) {
    func_US2_0033BB98(object + 0x8);
    func_00347EA0(object + 0x2E0);
    return object;
}


extern void *func_L00_0042C290(void *);

void *func_US2_L00_004354E8(char *object) {
    func_US2_0033BB98(object + 0x8);
    func_L00_0042C290(object + 0x2E0);
    return object;
}


extern int func_0033AF48(char *p);

int func_US2_L00_00435688(char *p)
{
    return func_0033AF48(p + 8);
}

