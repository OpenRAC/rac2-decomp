#include "common.h"
/* Starts state 6, scales the object, and builds the affine basis used by the
 * level effect. The two tables use 32-byte slots and 256-byte model records. */
typedef unsigned int Quadword __attribute__((mode(TI)));
extern int D_L05_001B1B20 __attribute__((sda));
extern int D_L05_001B1ADC __attribute__((sda));
extern int D_L05_001B1B24 __attribute__((sda));
extern int D_L05_001B1F60 MACRO_ADDR, D_L05_001B1F64 MACRO_ADDR;
typedef struct { char pad[0x20]; int model; } Entry;
typedef struct { char pad[0x1C]; Entry *entry; } ModelSlot;
typedef struct { char data[256]; } ModelRecord;
extern ModelSlot *D_L05_001B1EC4 MACRO_ADDR;
extern ModelRecord *D_L05_001B251C MACRO_ADDR;
extern char D_L05_001B3620[] __attribute__((aligned(16))) MACRO_ADDR;
extern char D_L05_001B3610[] __attribute__((aligned(16))) MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern void func_L05_003D1E60(void *,int,int);
extern void func_L05_004424B8(void *,float);
extern void func_002AB6D8(void *,void *);
/* Starts the ship's crash recovery. It remembers where the ship was and sets up the countdown before the ship is reset. */
void func_L05_00442398(char *obj)
{
    Quadword matrix[4];
    Entry *entry;
    float scale;
    if (gShipState != 6) {
        ModelSlot *slots = D_L05_001B1EC4;
        ModelRecord *models = D_L05_001B251C;
        {
            int index = *(short *)(obj + 0x84);

            gShipState = 6;
            entry = slots[index].entry;
        }
        D_L05_001B1F60 = 0;
        {
            int index = entry->model;

            D_L05_001B1F64 = 0;
            func_L05_003D1E60(models[index].data + 0x10, 0, 1);
        }
        qcopy(D_L05_001B3620, obj + 0x30);
        scale = 1.0f;
        if (gCurrentMapIndex == 20) scale = 2.0f;
        UpdateShipRecordTransform(obj, scale);
        gShipTransitionTimer = D_L05_001B1ADC;
        qcopy(&matrix[0], obj);
        qcopy(&matrix[1], obj + 0x10);
        qcopy(&matrix[2], obj + 0x20);
        qzero(&matrix[3]);
        ((float *)matrix)[3] = ((float *)matrix)[7] = ((float *)matrix)[11] = 0.0f;
        ((float *)matrix)[15] = 1.0f;
        GetEulerAnglesFromMatrix(matrix, D_L05_001B3610);
    }
}
