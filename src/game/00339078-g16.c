#include "names.h"
extern int func_00336E40(void *);
extern float *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_003369A8(void *, void *, void *);
extern void func_00336A30(void *, int);
extern unsigned int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00336A38(void *, void *);
extern void *func_00288FB8(int);
extern int func_00339320(void *, int);
extern char *ref_L00_0042E9A8_00;
extern char ref_L00_0042E9A8_01[];
extern char ref_L00_0042E9A8_02[];
extern char ref_L00_0042E9A8_03[];
extern char ref_L00_0042E9A8_04[];
extern char ref_L00_0042E9A8_05[];
extern char ref_L00_0042E9A8_06[];
extern char ref_L00_0042E9A8_07[];
extern char ref_L00_0042E9A8_08[];
extern char ref_L00_0042E9A8_09[15] __attribute__((sda));

/* Creates the mission screen's panels and labels, then applies its layout. */
void func_00339078(char *screen, void *parent)
{
    char *title;
    char *city;
    char *planet;
    char *mission;
    char *name;
    char *description;
    char *details;
    float *position;
    *(void **)screen = parent;
    *(int *)(screen + 0x298) = 1;
    if (parent) {
        position = ReturnSecondArgument(16, AllocPoolCell(parent));
        *(float **)(screen + 4) = position;
        position[1] = 0.0f;
        position[2] = 0.0f;
        position[3] = 0.0f;
        position[0] = 0.0f;
    }
    (*(float **)(screen + 4))[0] = 256.0f;
    (*(float **)(screen + 4))[1] = 198.0f;
    name = screen + 0x138;
    title = screen + 8;
    city = screen + 0x54;
    planet = screen + 0xa0;
    mission = screen + 0xec;
    description = screen + 0x180;
    details = screen + 0x1c8;
    InitDerivedArrays(title, ref_L00_0042E9A8_01, parent);
    InitDerivedArrays(city, ref_L00_0042E9A8_02, parent);
    InitDerivedArrays(planet, ref_L00_0042E9A8_03, parent);
    InitDerivedArrays(mission, ref_L00_0042E9A8_04, parent);
    InitWidgetDefaults(name, ref_L00_0042E9A8_05, parent);
    InitWidgetDefaults(description, ref_L00_0042E9A8_06, parent);
    InitWidgetDefaults(details, ref_L00_0042E9A8_07, parent);
    InitWidgetDefaults(screen + 0x210, ref_L00_0042E9A8_08, parent);
    SetWidgetField44(details, 1);
    *GetFieldC(title) = 0x60442d00;
    *GetFieldC(city) = 0x60241700;
    *GetFieldC(planet) = 0x55f0c070;
    *GetFieldC(mission) = 0x55f0c070;
    *GetFieldC(name) = 0x80f0f0f0;
    *GetFieldC(description) = 0x80f0f0f0;
    *GetFieldC(details) = 0x80f0f0f0;
    SetFieldAt40(title, ref_L00_0042E9A8_00 + 0x8710, 0x6b);
    SetFieldAt40(city, ref_L00_0042E9A8_00 + 0x8710, 0x6c);
    SetFieldAt40(planet, ref_L00_0042E9A8_00 + 0x8710, 0x6d);
    SetFieldAt40(mission, ref_L00_0042E9A8_00 + 0x8710, 0x6e);
    SetWidgetField40(name, ref_L00_0042E9A8_09);
    SetWidgetField40(description, GetLocalizedString(0x2d4f));
    SetWidgetField40(details, screen + 0x258);
    PlaceMissionScreenPartsAndUpdateStats(screen, 0);
}
