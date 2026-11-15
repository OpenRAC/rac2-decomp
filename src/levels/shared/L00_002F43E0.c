

extern int ref_L00_002F43E0_00;

extern int ref_L00_002F43E8_00;

extern int ref_L00_002F43F8_00;

/* Turns a flag off. */
void func_L00_002F43E0(void)
{
    ref_L00_002F43E0_00 = 0;
}

/* Turns a flag on. */
void func_L00_002F43E8(void)
{
    ref_L00_002F43E8_00 = 1;
}

/* Gets the stored flag value. */
int func_L00_002F43F8(void)
{
    return ref_L00_002F43F8_00;
}
