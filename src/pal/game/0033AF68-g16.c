/* func_PAL_0033AF68, the PAL copy of func_00339078: the same C, where the four labels from object + 0x138
   step 0x58 instead of 0x48, the fields after them move up by 0x40, and both label texts are looked up. */
extern int func_00336E40(void *);
extern float *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
extern void func_00336A30(void *, int);
extern unsigned int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00336A38(void *, void *);
extern void *func_00288FB8(int);
extern int func_PAL_0033B218(void *, int);
extern char *ref_L00_0042E9A8_00;
extern char ref_L00_0042E9A8_01[];
extern char ref_L00_0042E9A8_02[];
extern char ref_L00_0042E9A8_03[];
extern char ref_L00_0042E9A8_04[];
extern char ref_L00_0042E9A8_05[];
extern char ref_L00_0042E9A8_06[];
extern char ref_L00_0042E9A8_07[];
extern char ref_L00_0042E9A8_08[];

/* Creates the mission screen's panels and labels, then applies its layout. */
void func_PAL_0033AF68(char *object, void *parent)
{
    char *title;
    char *city;
    char *planet;
    char *mission;
    char *name;
    char *description;
    char *details;
    float *position;
    *(void **)object = parent;
    *(int *)(object + 0x2d8) = 1;
    if (parent) {
        position = func_00336DA8(16, func_00336E40(parent));
        *(float **)(object + 4) = position;
        position[1] = 0.0f;
        position[2] = 0.0f;
        position[3] = 0.0f;
        position[0] = 0.0f;
    }
    (*(float **)(object + 4))[0] = 256.0f;
    (*(float **)(object + 4))[1] = 198.0f;
    name = object + 0x138;
    title = object + 8;
    city = object + 0x54;
    planet = object + 0xa0;
    mission = object + 0xec;
    description = object + 0x190;
    details = object + 0x1e8;
    func_003361E0(title, ref_L00_0042E9A8_01, parent);
    func_003361E0(city, ref_L00_0042E9A8_02, parent);
    func_003361E0(planet, ref_L00_0042E9A8_03, parent);
    func_003361E0(mission, ref_L00_0042E9A8_04, parent);
    func_PAL_00338688(name, ref_L00_0042E9A8_05, parent);
    func_PAL_00338688(description, ref_L00_0042E9A8_06, parent);
    func_PAL_00338688(details, ref_L00_0042E9A8_07, parent);
    func_PAL_00338688(object + 0x240, ref_L00_0042E9A8_08, parent);
    func_00336A30(details, 1);
    *func_00335E20(title) = 0x60442d00;
    *func_00335E20(city) = 0x60241700;
    *func_00335E20(planet) = 0x55f0c070;
    *func_00335E20(mission) = 0x55f0c070;
    *func_00335E20(name) = 0x80f0f0f0;
    *func_00335E20(description) = 0x80f0f0f0;
    *func_00335E20(details) = 0x80f0f0f0;
    func_00336390(title, ref_L00_0042E9A8_00 + 0x8710, 0x6b);
    func_00336390(city, ref_L00_0042E9A8_00 + 0x8710, 0x6c);
    func_00336390(planet, ref_L00_0042E9A8_00 + 0x8710, 0x6d);
    func_00336390(mission, ref_L00_0042E9A8_00 + 0x8710, 0x6e);
    func_00336A38(name, func_00288FB8(0xbd6));
    func_00336A38(description, func_00288FB8(0xb60));
    func_00336A38(details, object + 0x298);
    func_PAL_0033B218(object, 0);
}
