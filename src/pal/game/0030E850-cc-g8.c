/* func_PAL_0030E850, the PAL copy of func_0030D430: the same C, where wrap D_001AF000 (({e}) * 1.2f). */

/* Scrolls the sky layer's texture offset (wrapping it by 8) and draws its two layers
   with the current colours, the planet-specific colour pair and light set for planet
   20 in mode 2; planet 1 in mode 2 takes its own light set as well. Its own -G8 unit:
   the sky globals are $gp scalars. */
typedef struct {
    char pad0[0x38];
    short tex;
} SkyVars30D430;
typedef struct {
    char pad0[0x68];
    SkyVars30D430 *vars;
} SkyMoby30D430;
extern int D_001A79F0;
extern int D_001A8BB0;
extern SkyVars30D430 D_001C1490;
extern SkyVars30D430 D_001C14E0;
extern float D_001AEFFC __attribute__((sda));
extern float D_001AF000 __attribute__((sda));
extern int D_001AEFE4 __attribute__((sda));
extern int D_001AEFEC __attribute__((sda));
extern int D_001AF008 __attribute__((sda));
extern int D_001AF00C __attribute__((sda));
extern float D_001AF018 __attribute__((sda));
extern float D_001AF01C __attribute__((sda));
extern float D_001AF04C __attribute__((sda));
extern float D_001AF028 __attribute__((sda));
extern float D_001AF02C __attribute__((sda));
extern float D_001AF050 __attribute__((sda));
extern char D_00229710[];
extern void func_0030D5B8(void *, int, int, int, float, float, float);
extern void func_0030DB88(SkyMoby30D430 *);

void func_PAL_0030E850(SkyMoby30D430 *moby)
{
    SkyVars30D430 *vars = moby->vars;
    float offset;
    int top;
    int bottom;
    int colour0;
    int colour1;

    if (D_001A79F0 == 1 && D_001A8BB0 == 2)
        vars = &D_001C1490;
    if (D_001A79F0 == 20 && D_001A8BB0 == 2)
        vars = &D_001C14E0;
    offset = D_001AEFFC - ((D_001AF000) * 1.2f);
    D_001AEFFC = offset;
    if (offset <= -8.0f)
        D_001AEFFC = offset + 8.0f;
    top = D_001AEFE4 << 24;
    bottom = D_001AEFEC << 24;
    colour0 = top | D_001AF008;
    colour1 = bottom | D_001AF00C;
    if (D_001A79F0 == 20 && D_001A8BB0 == 2) {
        colour0 = top | 0xEFCD12;
        colour1 = bottom | 0xEF3212;
    }
    func_0030D5B8(D_00229710, colour0, colour1, vars->tex, D_001AF018, D_001AF01C, D_001AF04C);
    func_0030D5B8(D_00229710 + 0x140, colour0, colour1, vars->tex, D_001AF028, D_001AF02C, D_001AF050);
    func_0030DB88(moby);
}
