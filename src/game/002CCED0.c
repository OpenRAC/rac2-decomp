#include "include_asm.h"
#include "names.h"

typedef struct { unsigned char value; } ResidentFlag;
extern ResidentFlag D_001A7BC9;
extern ResidentFlag D_001A7BCA;
extern ResidentFlag D_001A7BCB;
extern ResidentFlag D_001A7BCC;
extern ResidentFlag D_001A7BCE;
extern short D_L00_001AA8C2;
extern short D_L00_001AA8DA;
extern short D_L00_001AA8F2;
extern short D_L00_001AA90A;
extern short D_L00_001AA922;

/* Updates five menu icon values from five unlock flags: each becomes 3 when unlocked and 0 when not. */
void menu_refresh_unlock_icon_states(void)
{
    D_L00_001AA8C2 = D_001A7BC9.value ? 3 : 0;
    D_L00_001AA8DA = D_001A7BCA.value ? 3 : 0;
    D_L00_001AA8F2 = D_001A7BCB.value ? 3 : 0;
    D_L00_001AA90A = D_001A7BCC.value ? 3 : 0;
    D_L00_001AA922 = D_001A7BCE.value ? 3 : 0;
}
