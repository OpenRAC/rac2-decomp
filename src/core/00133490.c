#include "include_asm.h"

typedef int s32;

extern s32 func_00133490(s32);

extern int func_00132C48(int, int, void *);

/* lot15 -- two twins of the first call-bearing body (same form, 32 bytes).
   The matched wrappers use a `nop` delay slot and return 1; the slot alone does not establish the callee parameter list. */
extern void func_001338C8();

extern s32 func_00133930(s32, s32);

/* Sends sound command 0x36 with one int and returns its result. */
int func_00133490(int value)
{
    int payload[4];
    payload[0] = value;
    return func_00132C48(0x36, 4, payload);
}

/* func_001334B8 is matched in src/core/001334B8-g8.c. */

/* func_00133580 is matched in src/core/00133580-g8.c. */


/* func_001336C0 is matched in its own unit, src/core/001336C0.c (-O2 -G8 -ffunction-sections). */


extern int func_00132DF0(int, int, void *, int, int);

/* Queues sound command 81 with two ints and returns the result of func_00132DF0. */
int func_00133750(int first, int second) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    return func_00132DF0(81, 8, payload, 0, 0);
}

extern int func_00132DF0(int, int, void *, int, int);

/* Queues sound command 16 with four ints and returns the result of func_00132DF0. */
int func_00133788(int first, int second, int third, int fourth) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    payload[2] = third;
    payload[3] = fourth;
    return func_00132DF0(16, 16, payload, 0, 0);
}




/* Sends sound command 61 with no payload and returns its result. */
int func_00133890(void) {
    return func_00132C48(61, 0, 0);
}


/* Sends sound command 0x3C with no payload. */
void func_001338C8(void)
{
  func_00132C48(0x3c, 0, 0);
}

/* Sends sound command 62 with five ints and returns its result. */
int func_001338F0(int first, int second, int third, int fourth, int fifth) {
    int payload[8];
    payload[0] = first;
    payload[1] = second;
    payload[2] = third;
    payload[3] = fourth;
    payload[4] = fifth;
    return func_00132C48(62, 20, payload);
}


/* Sends sound command 0x5A with two ints and returns its result. */
int func_00133930(int first, int second)
{
    struct {
        unsigned int first;
        unsigned int second;
        unsigned int pad[2];
    } payload;
    payload.first = first;
    payload.second = second;
    return func_00132C48(0x5a, 8, &payload.first);
}

/* Sends sound command 91 with no payload and returns its result. */
int func_00133960(void) {
    return func_00132C48(91, 0, 0);
}
