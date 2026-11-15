#include "include_asm.h"
#include "names.h"

typedef int s32;

extern s32 snd_send_cmd36(s32);

extern int snd_SendCommandSync(int, int, void *);

/* lot15 -- two twins of the first call-bearing body (same form, 32 bytes).
   The matched wrappers use a `nop` delay slot and return 1; the slot alone does not establish the callee parameter list. */
extern void snd_send_cmd3c();

extern s32 snd_send_cmd5a(s32, s32);

/* Sends sound command 0x36 with one value. */
int snd_send_cmd36(int value)
{
    int payload[4];
    payload[0] = value;
    return snd_SendCommandSync(0x36, 4, payload);
}

/* func_001334B8 is matched in src/core/001334B8-g8.c. */

/* func_00133580 is matched in src/core/00133580-g8.c. */


/* func_001336C0 is matched in its own unit, src/core/001336C0.c (-O2 -G8 -ffunction-sections). */


extern int snd_queue_command(int, int, void *, int, int);

/* Sends sound command 81 with two values. */
int snd_send_cmd51(int first, int second) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    return snd_queue_command(81, 8, payload, 0, 0);
}

extern int snd_queue_command(int, int, void *, int, int);

/* Sends sound command 16 with four values. */
int snd_send_cmd10(int first, int second, int third, int fourth) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    payload[2] = third;
    payload[3] = fourth;
    return snd_queue_command(16, 16, payload, 0, 0);
}




/* Sends sound command 61, which has no data. */
int snd_send_cmd3d(void) {
    return snd_SendCommandSync(61, 0, 0);
}


/* Sends sound command 0x3C, which has no data. */
void snd_send_cmd3c(void)
{
  snd_SendCommandSync(0x3c, 0, 0);
}

/* Sends sound command 62 with five values. */
int snd_send_cmd3e(int first, int second, int third, int fourth, int fifth) {
    int payload[8];
    payload[0] = first;
    payload[1] = second;
    payload[2] = third;
    payload[3] = fourth;
    payload[4] = fifth;
    return snd_SendCommandSync(62, 20, payload);
}


/* Sends sound command 0x5A with two values. */
int snd_send_cmd5a(int first, int second)
{
    struct {
        unsigned int first;
        unsigned int second;
        unsigned int pad[2];
    } payload;
    payload.first = first;
    payload.second = second;
    return snd_SendCommandSync(0x5a, 8, &payload.first);
}

/* Sends sound command 91, which has no data. */
int snd_send_cmd5b(void) {
    return snd_SendCommandSync(91, 0, 0);
}
