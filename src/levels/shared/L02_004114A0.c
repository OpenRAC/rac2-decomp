/* Standalone declarations recovered from src/levels/shared/L02_00410450.c. */
typedef unsigned char u8;

extern void func_0032B890(int, int, int);

/* Shows one of several on-screen messages, chosen by a number kept in the object. */
void func_L02_004114A0(u8 *object) {
    int selector = *(int *)(*(void **)(object + 0x68) + 0x10);
    int messageId;

    switch (selector) {
    case 1:
        messageId = 0x27B9;
        break;
    case 3:
        messageId = 0x27E9;
        break;
    case 4:
        messageId = 0x27F6;
        break;
    case 5:
        messageId = 0x27EB;
        break;
    case 6:
        messageId = 0x27F2;
        break;
    case 7:
        messageId = 0x27F3;
        break;
    case 8:
        messageId = 0x27F4;
        break;
    case 9:
        messageId = 0x27F5;
        break;
    case 0:
    case 2:
    default:
        messageId = 0x2793;
        break;
    }
    func_0032B890(0xB, messageId, 1);
}
