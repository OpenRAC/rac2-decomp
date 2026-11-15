extern unsigned char D_L30_001B3D30[] __attribute__((sda));
extern void *D_L30_00260E30[];
extern char *D_L30_00260EB0[];
extern int D_L30_00260F30[][2];

/* Adds an entry to the tuning menu: the first free slot of the four parallel 32-entry tables
   gets the value pointer, label, type and value range, and the menu's entry count goes up.
   The byte table lies in the GP window (GP + 0x4D40 in USA v1.01). Declared sda, its address
   is one macro instruction instead of a high/low pair, which gives retail's setup order and
   registers. */
void func_L30_00413528(char *menu, void *value, char *label, int type, int low, int high) {
    int *vars = *(int **)(menu + 0x68);
    int i;
    for (i = 0; i < 32; i++) {
        if (D_L30_00260E30[i] == 0) {
            D_L30_00260E30[i] = value;
            D_L30_00260EB0[i] = label;
            D_L30_001B3D30[i] = type;
            D_L30_00260F30[i][0] = low;
            D_L30_00260F30[i][1] = high;
            vars[1]++;
            return;
        }
    }
}
