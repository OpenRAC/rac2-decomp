#include "common.h"
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48c]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[216]; } MaterialRecord;
typedef struct { char pad[0x44]; int selected; } EquipmentState;

extern void func_002E5E58(int, int, int);
extern unsigned char D_001A7AF8[] __attribute__((section(".sdata")));
extern unsigned char D_00139568[];
extern MaterialRecord D_00239BA0[];
extern int D_001ADB10 __attribute__((sda));
extern SelectionEntry D_001AA898[];
extern EquipmentState D_001F2840;

#define MATERIAL(id) ((MaterialRecord *)(D_00139568[id]*224 + (char *)D_00239BA0))->material

void func_00345D58(SelectionOwner *o, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next;

        func_002E5E58(3, 0, 0);
        column = o->column;
        next = column - 1;
        o->row = 0;
        o->state = 3;
        if (next < 0)
            next = 0;
        o->column = next;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        o->row = 0;
        o->state = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        column = o->column;
        column--;
        o->column = column;
        if (column < 0)
            o->column = 2;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        column = o->column;
        column++;
        o->column = column;
        if (column >= 3)
            o->column = 0;
    } else if (buttons & 0x40) {
        id = D_001AA898[o->column].v[3];
        if (id != 0 && D_001A7AF8[id] != 0) {
            func_002E5E58(4, 0, 0);
            D_001ADB10 = MATERIAL(o->selected);
            if (D_001F2840.selected == id)
                D_001F2840.selected = 0;
            else
                D_001F2840.selected = id;
        } else {
            func_002E5E58(5, 0, 0);
        }
    }
    {
        int selected = D_001AA898[o->column].v[3];
        o->selected = selected;
        if (selected != 0 && D_001A7AF8[selected] != 0)
            D_001ADB10 = MATERIAL(selected);
    }
}
