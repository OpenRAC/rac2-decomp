#include "common.h"
#include "structs.h"

/* rac1-decomp src/core/00118A40.c: func_001191C0 */
/* Always returns 1. */
int menu_always_return_true(void) {
    return 1;
}


extern void *g_active_menu_object;
extern char g_menu_page_known_screen[];

/* Returns true when the current menu screen is the one at D_00259458. */
int menu_is_known_screen_active(void) {
    return g_active_menu_object == g_menu_page_known_screen;
}



/* func_002DF3F8 is in 002DF1B8-capture.c. */


/* func_002DF7A8 is matched in 002DF1B8-g8.c (-G8 small data). */

/* func_002DF838 is in 002DF1B8-packet.c. */

/* func_002DF9E0 is in 002DF1B8-clear.c. */

/* func_002DFBB0 is in 002DF1B8-render-g8.c. */

ASM_FUNC("asm/game", func_002DFD88);

ASM_FUNC("asm/game", func_002E0088);

ASM_FUNC("asm/game", func_002E0408);

ASM_FUNC("asm/game", func_002E0558);

/* Original assembly: lqc2/sqc2/vdiv VU0 ops and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002E0BA8);

ASM_FUNC("asm/game", func_002E0C40);

/* func_002E0F98 is in 002DF1B8-g8.c. */
