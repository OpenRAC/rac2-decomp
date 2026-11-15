#include "names.h"
/* Standalone declarations recovered from src/levels/shared/L02_00410450.c. */
typedef unsigned char u8;

extern void func_0032B890(int, int, int);

/* Shows one of several on-screen messages, chosen by a number kept in the object. */
void hud_show_message_for_state(u8 *object) {
    int selector = *(int *)(*(void **)(object + 0x68) + 0x10);
    int message_id;

    switch (selector) {
    case 1:
        message_id = 0x27B9;
        break;
    case 3:
        message_id = 0x27E9;
        break;
    case 4:
        message_id = 0x27F6;
        break;
    case 5:
        message_id = 0x27EB;
        break;
    case 6:
        message_id = 0x27F2;
        break;
    case 7:
        message_id = 0x27F3;
        break;
    case 8:
        message_id = 0x27F4;
        break;
    case 9:
        message_id = 0x27F5;
        break;
    case 0:
    case 2:
    default:
        message_id = 0x2793;
        break;
    }
    func_0032B890(0xB, message_id, 1);
}
