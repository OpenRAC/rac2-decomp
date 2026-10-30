/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G0 -ffunction-sections -g.
 * us: 09_dobbo: 1448 bytes, expected 1440; us2: 09_dobbo: 1448 bytes, expected 1440; pal: ABSENT.
 * Complete two-layer/six-vertex beam reconstruction with real 0x60-byte vertex rows, 0x40-byte
 * history rows and pointer-return particle helper. Canonical particle velocity is
 * D_L09_001A8F20. All float angles use measured encodings. The debug-padding probe is 1448/1440;
 * loop/FP priority and division scheduling remain.
 * Reopen: Independent loop FP-lifetime and scalar-division scheduling witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
extern int func_L02_002F1658(void),func_002A77E0(int);
extern float func_00282DF0(void *),func_00283CE0(int),func_00283198(float),func_00283180(float);
extern float func_00283B98(float,float),func_00283BE0(float,float),func_002ABB18(float),func_002A78D8(float,float);
extern void func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_002ACB48(void *,float);
extern u8 *func_L08_0034A078(void *,void *,int,void *);
extern u8 *D_L09_00255E90[][2];
extern float D_L09_00255F40[][4][4],D_L09_00256310[][4],D_L09_00256410[][4];
extern float D_L09_00256510[][6][4];
extern int D_L09_001B35E0[],D_L09_001B36E0[],D_L09_001B3720[],D_L09_001B37A0[];
extern float D_L09_001B3620[],D_L09_001B3660[],D_L09_001B36A0[];
extern float D_L09_001A8F20[];

/* Updates the two six-vertex beam layers and occasionally sheds particles at
 * their endpoints. Each global row retains its measured stride and open extent.
 */
void func_L09_003FB9F8(u8 *unused, int index)
{
    float delta[4],start[4],scaled[4],point[4];
    int i,alpha,side,even,odd;
    float length,segment,t,step,modulation,phase,phase2,first,second;
    float (*a)[4],(*b)[4];
    u8 *particle;
    if (!func_L02_002F1658()) return;
    alpha = D_L09_00255E90[index][0][0x23];
    even = index*2; odd = even+1;
    func_00282CF0(delta,D_L09_00256310[index],D_L09_00255F40[index]);
    length = func_00282DF0(delta);
    segment = length / func_00283CE0(5);
    if (D_L09_001B35E0[index] == 2) {
        a = D_L09_00256510[even]; b = D_L09_00256510[odd];
        D_L09_001B35E0[index] = 3;
        for (i=0;i<6;i++) {
            t = segment * func_00283CE0(i);
            a[i][2] = a[i][1] = 0.0f; a[i][3] = 1.0f; a[i][0] = t;
            b[i][0] = t; b[i][2] = b[i][1] = 0.0f; b[i][3] = 1.0f;
        }
    }
    D_L09_001B3620[index] = func_00283B98(D_L09_001B3620[index],0.174532949924469f);
    D_L09_001B3660[index] = func_00283BE0(D_L09_001B3660[index],0.8028515577316284f);
    D_L09_001B36A0[index] = func_00283B98(D_L09_001B36A0[index],0.05235999822616577f);
    qcopy(start,D_L09_00255F40[index]);
    func_00282F20(scaled,delta,segment);
    step = (360.0f / (func_00283CE0(6)*0.5f))*0.017453294f;
    a = D_L09_00256510[even];
    for (i=0;i<6;i++) {
        t = func_00283CE0(i);
        modulation = func_00283198(t/func_00283CE0(5)*3.1415927f) * -0.09f + 0.1f;
        modulation *= func_00283198(func_002ABB18(D_L09_001B3620[index]+t*step));
        a[i][1] = 0.0f; a[i][3] = 1.0f; a[i][2] = modulation; a[i][0] = segment*t;
    }
    qcopy(D_L09_00256410[index],D_L09_00255E90[index][1]+0x10);
    b = D_L09_00256510[odd];
    for (i=0;i<6;i++) {
        t = func_00283CE0(i);
        phase = func_002ABB18(D_L09_001B3660[index]+t*0.994837760925293f);
        phase2 = func_002ABB18(D_L09_001B36A0[index]+t*0.20943999290466309f);
        first = func_00283198(phase2)*0.2f;
        second = func_00283198(phase);
        modulation = func_002A78D8(0.0f,0.2f);
        b[i][2] = a[i][2] + first*second + modulation;
        b[i][1] = func_00283180(phase)*0.1f;
        b[i][3] = 1.0f; b[i][0] = segment*t;
    }
    for (side=0;side<2;side++) {
        if (!func_002A77E0(3)) {
            qcopy(point,D_L09_00255E90[index][side]+0x10);
            func_002ACB48(point,0.1f);
            particle = func_L08_0034A078(point,D_L09_001A8F20,(alpha*127)/100,
                                        D_L09_00255E90[index][side]);
            if (particle) {
                *(u16 *)(particle+0xA)=4;
                *(float *)(particle+0xC)=120000.0f;
                *(float *)(particle+0x30)=1.0f/func_00283CE0(4);
                *(int *)(particle+0x38)=0x7F7F7F;
                if (D_L09_001B37A0[index]==1) *(u16 *)(particle+0x36)=D_L09_001B37A0[index];
            }
        }
    }
    D_L09_001B36E0[index] = -1;
    D_L09_001B3720[index] = -1;
}
