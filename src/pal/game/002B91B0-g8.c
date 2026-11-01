#include "include_asm.h"

#include "common.h"
extern int func_00128C18(int socket);
extern int func_00128B28(int socket, void *profile);
extern int func_00128F48(int socket, void *profile);
extern int func_00128A48(int socket, void *data);
extern void func_00128FD0(int socket, int profile_size, void *profile, int data_size, void *data);
extern void func_002B8888(void *pad);
extern void func_PAL_002B94A8(void *pad, void *data, int size);
extern int D_001A7428;
typedef struct {
    unsigned char pad0[0x180];
    unsigned char profile[4];
    unsigned char act[4];
    unsigned char vibration0;
    unsigned char vibration1;
    unsigned char pad18a[10];
    int socket;
    int profile_state;
    int device_state;
    int held, pressed, released, prev_held;
    int raw_held, raw_pressed, raw_released, prev_raw_held;
    unsigned char pad1c0[0x1C];
    int profile_mask;
    unsigned char pad1e0[0x168];
    int latched_held;
} PadPollState;
extern PadPollState D_00138180;

void func_PAL_002B91B0(void *arg)
{
    PadPollState *p = arg;
    unsigned char buf[64];
    short vibration;
    int status, n, i;

    p->held = 0;
    p->prev_held = p->latched_held;
    p->prev_raw_held = p->raw_held;
    p->raw_held = 0;
    status = func_00128C18(p->socket);
    p->device_state = status;
    if (status == 1) {
        switch (p->profile_state) {
        case 0: {
            int n;

            n = func_00128B28(p->socket, buf);
            if (*(unsigned int *)buf == 0xFFFFFFFF)
                p->profile_mask = 0x79;
            else
                p->profile_mask = 0;
            if (n < 5) {
                for (i = 0; i < n; i++)
                    p->profile[i] = buf[i];
                p->profile_state = 1;
            } else {
                p->profile_state = 2;
                n = 0;
            }
            for (i = n; i < 4; i++)
                p->profile[i] = buf[i];
            n = func_00128F48(p->socket, buf);
            if (n < 5) {
                for (i = 0; i < n; i++)
                    p->act[i] = buf[i];
            } else {
                n = 0;
            }
            for (i = n; i < 4; i++)
                p->act[i] = buf[i];
            func_002B8888(p);
            break;
        }
        case 1:
            n = func_00128A48(p->socket, buf);
            vibration = 0;
            if (p->act[0] & 2)
                vibration = p->vibration1;
            if (p->act[0] & 1) {
                short shifted = vibration << 1;

                vibration = shifted | (p->vibration0 & 1);
            }
            func_00128FD0(p->socket, 1, p->act, 2, &vibration);
            func_PAL_002B94A8(p, buf, n);
            break;
        case 2:
            func_002B8888(p);
            break;
        }
    } else {
        func_002B8888(p);
        p->profile_state = 0;
    }
    p->vibration0 = 0;
    p->vibration1 = 0;
    D_001A7428 = D_00138180.device_state == 0;
}
