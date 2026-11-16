#include "include_asm.h"

#include "common.h"
extern int scePad2GetState(int socket);
extern int pad_read_button_mask(int socket, void *profile);
extern int pad_send_command(int socket, void *profile);
extern int pad_read_record(int socket, void *data);
extern int sceVibSetActParam(int socket, int profile_size, void *profile, int data_size, void *data);
extern void ClearPadInput(void *pad);
extern void pad_decode_reading_pal(void *pad, void *data, int size);
extern int g_pad_device_idle_flag;
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
extern PadPollState g_pad_state;

/* Polls one controller: reads its state, identifies the device and its vibration support, sends vibration and decodes the button reading (PAL). */
void poll_pad_device_state_pal(void *device)
{
    PadPollState *pad = device;
    unsigned char buf[64];
    short vibration;
    int status, count, i;

    pad->held = 0;
    pad->prev_held = pad->latched_held;
    pad->prev_raw_held = pad->raw_held;
    pad->raw_held = 0;
    status = scePad2GetState(pad->socket);
    pad->device_state = status;
    if (status == 1) {
        switch (pad->profile_state) {
        case 0: {
            int count;

            count = pad_read_button_mask(pad->socket, buf);
            if (*(unsigned int *)buf == 0xFFFFFFFF)
                pad->profile_mask = 0x79;
            else
                pad->profile_mask = 0;
            if (count < 5) {
                for (i = 0; i < count; i++)
                    pad->profile[i] = buf[i];
                pad->profile_state = 1;
            } else {
                pad->profile_state = 2;
                count = 0;
            }
            for (i = count; i < 4; i++)
                pad->profile[i] = buf[i];
            count = pad_send_command(pad->socket, buf);
            if (count < 5) {
                for (i = 0; i < count; i++)
                    pad->act[i] = buf[i];
            } else {
                count = 0;
            }
            for (i = count; i < 4; i++)
                pad->act[i] = buf[i];
            ClearPadInput(pad);
            break;
        }
        case 1:
            count = pad_read_record(pad->socket, buf);
            vibration = 0;
            if (pad->act[0] & 2)
                vibration = pad->vibration1;
            if (pad->act[0] & 1) {
                short shifted = vibration << 1;

                vibration = shifted | (pad->vibration0 & 1);
            }
            sceVibSetActParam(pad->socket, 1, pad->act, 2, &vibration);
            pad_decode_reading_pal(pad, buf, count);
            break;
        case 2:
            ClearPadInput(pad);
            break;
        }
    } else {
        ClearPadInput(pad);
        pad->profile_state = 0;
    }
    pad->vibration0 = 0;
    pad->vibration1 = 0;
    g_pad_device_idle_flag = g_pad_state.device_state == 0;
}
