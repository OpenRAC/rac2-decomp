#include "include_asm.h"

#include "common.h"
typedef int L14_TI128 __attribute__((mode(TI)));
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int path_build_route_nodes(char *, int, void *, int);
extern int math_random_int_below(int);
extern void moby_set_state(char *, int, int);
typedef struct {
    unsigned char pad00[0x20];
    float f20;
    unsigned short h24;
    unsigned char pad26[0x28 - 0x26];
    unsigned char b28;
    unsigned char pad29[0x70 - 0x29];
    unsigned char b70;
    unsigned char b71;
    unsigned char b72;
    unsigned char pad73[0x76 - 0x73];
    unsigned char b76;
    unsigned char b77;
    unsigned char pad78[0x7C - 0x78];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    unsigned char pad98[0x9C - 0x98];
    float f9C;
    unsigned char padA0[0xA8 - 0xA0];
    int iA8;
    unsigned char padAC[0xCC - 0xAC];
    unsigned char bCC;
    unsigned char bCD;
    unsigned char bCE;
    unsigned char bCF;
    unsigned char padD0[0xD2 - 0xD0];
    unsigned char bD2;
    unsigned char bD3;
    unsigned char padD4[0x110 - 0xD4];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    unsigned char pad124[0x13C - 0x124];
    float f13C;
    float f140;
    float f144;
    unsigned char pad148[0x14C - 0x148];
    int i14C;
    unsigned char pad150[0x158 - 0x150];
    char *p158;
    char *p15C;
    unsigned char pad160[0x200 - 0x160];
    char area200[0x400];
    char area600[0x80];
    char area680[0x90];
    L14_TI128 vec710;
    unsigned char pad720[0x730 - 0x720];
    int i730;
    unsigned char unknown734[4];
    int i738;
    int i73C;
    float f740;
    unsigned char pad744[0x750 - 0x744];
    int i750;
    unsigned char pad754[0x774 - 0x754];
    short h774;
    unsigned char pad776[0x77C - 0x776];
    short h77C;
} L14State_423000;

void actor_init_pal(char *moby)
{
    L14State_423000 *vars = *(L14State_423000 **)(moby + 0x68);
    short start_state;

    vars->b70 = 8;
    vars->iA8 = 4;
    vars->f80 = 0.080000006f;
    vars->b71 = 0x11;
    vars->f7C = 0.120000005f;
    vars->f84 = 0.006f;
    vars->f90 = 0.5f;
    vars->f94 = 0.5f;
    vars->f9C = 0.4f;
    vars->bCC = 3;
    vars->bCD = 6;
    vars->bCE = 3;
    vars->b76 = 0x12;
    vars->f88 = 0.012f;
    vars->f20 = 16.0f;
    vars->b72 = 0x11;
    vars->b77 = 0x13;
    vars->f8C = 0.006f;
    vars->bCF = 6;
    vars->bD2 = 0xD;
    vars->bD3 = 0x1A;
    vars->h24 = 0x10;
    vars->b28 = 3;
    *(unsigned char *)(moby + 0x30) = 0xC8;
    *(unsigned short *)(moby + 0x32) = 0xC8;
    vars->f144 = 0.25f;
    vars->f110 = 0.4f;
    vars->f114 = 0.5f;
    vars->f118 = 0.5f;
    vars->f11C = 0.5f;
    vars->f140 = 0.2617994248867035f;
    vars->f13C = 0.008f;
    vars->i14C = -1;
    vars->f120 = 3.141590118408203f;
    moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f,
                0.005026549f, 0.25132746f);

    vars->f740 = vars->f740 * 0.01745329424738884f;
    vars->p158 = vars->area680;
    vars->p15C = vars->area600;
    if (vars->i738 != -1)
        vars->i14C = vars->i738;
    vars->i750 = path_build_route_nodes(moby, vars->i73C, vars->area200, 0x20);
    vars->h77C = math_random_int_below(2);

    vars->vec710 = *(L14_TI128 *)(moby + 0x10);

    start_state = vars->h774;
    if (start_state > 0 && (start_state != 3 || vars->i730 != -1))
        moby_set_state(moby, start_state, 1);
    else
        moby_set_state(moby, 1, 1);
}
