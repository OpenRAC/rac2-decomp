#include "include_asm.h"

extern int D_00134688;

ASM_FUNC("asm/core", func_0011A830);

/* Asks the console to end the running program. */
ASM_FUNC("asm/core", func_0011A840);

ASM_FUNC("asm/core", func_0011A850);

/* Loads another program from disc and starts it. */
ASM_FUNC("asm/core", func_0011A860);

/* Starts another program that is already in memory. */
ASM_FUNC("asm/core", func_0011A870);

ASM_FUNC("asm/core", func_0011A880);

ASM_FUNC("asm/core", func_0011A890);

/* Registers a function to run on a bus interrupt from the IO processor. */
ASM_FUNC("asm/core", func_0011A8A0);

/* Removes a bus interrupt function. */
ASM_FUNC("asm/core", func_0011A8B0);

/* Sends an interrupt signal to the IO processor. */
ASM_FUNC("asm/core", func_0011A8C0);

/* Sets the function that handles memory page-table misses. */
ASM_FUNC("asm/core", func_0011A8D0);

/* Sets the function that handles common CPU exceptions. */
ASM_FUNC("asm/core", func_0011A8E0);

/* Sets the function that handles CPU interrupts. */
ASM_FUNC("asm/core", func_0011A8F0);

/* Registers a function to run on an interrupt. */
ASM_FUNC("asm/core", func_0011A900);

/* Registers a function to run on an interrupt (second version). */
ASM_FUNC("asm/core", func_0011A910);

/* Removes an interrupt handler function. */
ASM_FUNC("asm/core", func_0011A920);

/* Registers a function to run when a data transfer (DMA) ends. */
ASM_FUNC("asm/core", func_0011A930);

/* Registers a function to run when a DMA ends (second version). */
ASM_FUNC("asm/core", func_0011A940);

/* Removes a data transfer (DMA) handler function. */
ASM_FUNC("asm/core", func_0011A950);

/* Turns on an interrupt source. */
ASM_FUNC("asm/core", func_0011A960);

/* Turns off an interrupt source. */
ASM_FUNC("asm/core", func_0011A970);

/* Turns on a data transfer (DMA) channel interrupt. */
ASM_FUNC("asm/core", func_0011A980);

/* Turns off a data transfer (DMA) channel interrupt. */
ASM_FUNC("asm/core", func_0011A990);

/* Starts a timer alarm that calls a function later. */
ASM_FUNC("asm/core", func_0011A9A0);

/* Cancels a timer alarm. */
ASM_FUNC("asm/core", func_0011A9B0);

/* Turns on an interrupt source (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011A9C0);

/* Turns off an interrupt source (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011A9D0);

/* Turns on a DMA channel interrupt (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011A9E0);

/* Turns off a DMA channel interrupt (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011A9F0);

/* Starts a timer alarm (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AA00);

/* Cancels a timer alarm (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AA10);

/* Makes a new thread. */
ASM_FUNC("asm/core", func_0011AA20);

/* Deletes a thread. */
ASM_FUNC("asm/core", func_0011AA30);

/* Starts a thread running. */
ASM_FUNC("asm/core", func_0011AA40);

/* Ends the current thread. */
ASM_FUNC("asm/core", func_0011AA50);

/* Ends the current thread and deletes it. */
ASM_FUNC("asm/core", func_0011AA60);

/* Stops another thread. */
ASM_FUNC("asm/core", func_0011AA70);

/* Stops another thread (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AA80);

/* Stops the system from switching between threads. */
ASM_FUNC("asm/core", func_0011AA90);

/* Lets the system switch between threads again. */
ASM_FUNC("asm/core", func_0011AAA0);

/* Changes how important a thread is. */
ASM_FUNC("asm/core", func_0011AAB0);

/* Changes how important a thread is (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AAC0);

/* Moves the next ready thread of a priority to the front. */
ASM_FUNC("asm/core", func_0011AAD0);

/* Moves the next ready thread of a priority to the front (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AAE0);

/* Wakes a thread that is waiting. */
ASM_FUNC("asm/core", func_0011AAF0);

/* Wakes a waiting thread (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AB00);

/* Gives the ID number of the current thread. */
ASM_FUNC("asm/core", func_0011AB10);

/* Reads the state of a thread. */
ASM_FUNC("asm/core", func_0011AB20);

/* Reads the state of a thread (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AB30);

/* Puts the current thread to sleep until it is woken. */
ASM_FUNC("asm/core", func_0011AB40);

/* Wakes a sleeping thread. */
ASM_FUNC("asm/core", func_0011AB50);

/* Wakes a sleeping thread (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AB60);

/* Cancels a pending wake-up request for a thread. */
ASM_FUNC("asm/core", func_0011AB70);

/* Cancels a pending wake-up request (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AB80);

/* Pauses a thread. */
ASM_FUNC("asm/core", func_0011AB90);

/* Pauses a thread (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011ABA0);

/* Lets a paused thread run again. */
ASM_FUNC("asm/core", func_0011ABB0);

/* Lets a paused thread run again (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011ABC0);

/* Waits for a thread to finish. */
ASM_FUNC("asm/core", func_0011ABD0);

ASM_FUNC("asm/core", func_0011ABE0);

ASM_FUNC("asm/core", func_0011ABF0);

/* Gives the address where the program heap ends. */
ASM_FUNC("asm/core", func_0011AC00);

ASM_FUNC("asm/core", func_0011AC10);

/* Makes a new semaphore (a counter threads use to take turns). */
ASM_FUNC("asm/core", func_0011AC20);

/* Deletes a semaphore. */
ASM_FUNC("asm/core", func_0011AC30);

/* Adds one to a semaphore, which can wake a waiting thread. */
ASM_FUNC("asm/core", func_0011AC40);

/* Adds one to a semaphore (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AC50);

/* Waits until a semaphore is available, then takes it. */
ASM_FUNC("asm/core", func_0011AC60);

/* Takes a semaphore only if it is free right now. */
ASM_FUNC("asm/core", func_0011AC70);

/* Takes a semaphore only if it is free (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AC80);

/* Reads the state of a semaphore. */
ASM_FUNC("asm/core", func_0011AC90);

/* Reads the state of a semaphore (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011ACA0);

ASM_FUNC("asm/core", func_0011ACB0);

/* Saves the console settings (language, time zone and so on). */
ASM_FUNC("asm/core", func_0011ACC0);

/* Reads the console settings (language, time zone and so on). */
ASM_FUNC("asm/core", func_0011ACD0);

/* Reads the horizontal screen settings. */
ASM_FUNC("asm/core", func_0011ACE0);

/* Reads the vertical screen settings. */
ASM_FUNC("asm/core", func_0011ACF0);

/* Sets the horizontal screen settings. */
ASM_FUNC("asm/core", func_0011AD00);

/* Sets the vertical screen settings. */
ASM_FUNC("asm/core", func_0011AD10);

/* Makes a new event flag. */
ASM_FUNC("asm/core", func_0011AD20);

/* Deletes an event flag. */
ASM_FUNC("asm/core", func_0011AD30);

/* Sets event flag bits. */
ASM_FUNC("asm/core", func_0011AD40);

/* Sets event flag bits (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AD50);

/* Clears event flag bits. */
ASM_FUNC("asm/core", func_0011AD60);

/* Waits until event flag bits are set. */
ASM_FUNC("asm/core", func_0011AD70);

/* Checks event flag bits without waiting. */
ASM_FUNC("asm/core", func_0011AD80);

/* Checks event flag bits without waiting (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AD90);

/* Reads the state of an event flag. */
ASM_FUNC("asm/core", func_0011ADA0);

ASM_FUNC("asm/core", func_0011ADB0);

/* Reads the state of an event flag (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011ADC0);

ASM_FUNC("asm/core", func_0011ADD0);

/* Turns on an interrupt handler. */
ASM_FUNC("asm/core", func_0011ADE0);

/* Turns on an interrupt handler (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011ADF0);

/* Turns off an interrupt handler. */
ASM_FUNC("asm/core", func_0011AE00);

/* Turns off an interrupt handler (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AE10);

/* Turns on a DMA handler. */
ASM_FUNC("asm/core", func_0011AE20);

/* Turns on a DMA handler (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AE30);

/* Turns off a DMA handler. */
ASM_FUNC("asm/core", func_0011AE40);

/* Turns off a DMA handler (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AE50);

/* Switches memory mapping to the cached kernel segment. */
ASM_FUNC("asm/core", func_0011AE60);

/* Turns on a CPU cache. */
ASM_FUNC("asm/core", func_0011AE70);

/* Turns off a CPU cache. */
ASM_FUNC("asm/core", func_0011AE80);

/* Reads a CPU control register. */
ASM_FUNC("asm/core", func_0011AE90);

/* Writes cache contents back to memory or clears them. */
ASM_FUNC("asm/core", func_0011AEA0);

/* Changes the CPU configuration. */
ASM_FUNC("asm/core", func_0011AEB0);

/* Reads a CPU control register (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AEC0);

/* Flushes the CPU cache (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AED0);

/* Changes the CPU configuration (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AEE0);

/* Stops a data transfer to the IO processor. */
ASM_FUNC("asm/core", func_0011AEF0);

/* Sets the function that runs when the CPU timer fires. */
ASM_FUNC("asm/core", func_0011AF00);

/* Sets the CPU timer. */
ASM_FUNC("asm/core", func_0011AF10);

/* Saves extra console settings. */
ASM_FUNC("asm/core", func_0011AF20);

/* Reads extra console settings. */
ASM_FUNC("asm/core", func_0011AF30);

/* Reads the graphics chip interrupt mask. */
ASM_FUNC("asm/core", func_0011AF40);

/* Reads the graphics chip interrupt mask (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AF50);

/* Sets the graphics chip interrupt mask. */
ASM_FUNC("asm/core", func_0011AF60);

/* Sets the graphics chip interrupt mask (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AF70);

/* Sets the function that handles the graphics interface interrupt. */
ASM_FUNC("asm/core", func_0011AF80);

/* Sets the flags that the screen refresh (vsync) updates. */
ASM_FUNC("asm/core", func_0011AF90);

ASM_FUNC("asm/core", func_0011AFA0);

/* Prints a debug text message through the console. */
ASM_FUNC("asm/core", func_0011AFB0);

/* Checks whether a data transfer to the IO processor is done. */
ASM_FUNC("asm/core", func_0011AFC0);

/* Checks whether a data transfer is done (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AFD0);

/* Starts a data transfer to the IO processor. */
ASM_FUNC("asm/core", func_0011AFE0);

/* Starts a data transfer to the IO processor (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011AFF0);

/* Turns on chained data transfers to the IO processor. */
ASM_FUNC("asm/core", func_0011B000);

/* Turns on chained data transfers (version for use inside interrupts). */
ASM_FUNC("asm/core", func_0011B010);

/* Writes a communication register shared with the IO processor. */
ASM_FUNC("asm/core", func_0011B020);

/* Reads a communication register shared with the IO processor. */
ASM_FUNC("asm/core", func_0011B030);

/* Starts the console built-in menu program. */
ASM_FUNC("asm/core", func_0011B040);

/* Calls the debug link (DECI2) service. */
ASM_FUNC("asm/core", func_0011B050);

/* Tells which mode the console is in (PS2 or PS1). */
ASM_FUNC("asm/core", func_0011B060);

/* Tells which type of console this is. */
ASM_FUNC("asm/core", func_0011B070);

/* Gives how much memory the console has. */
ASM_FUNC("asm/core", func_0011B080);

/* Resets the memory page table. */
ASM_FUNC("asm/core", func_0011B090);

/* Clears a library flag back to zero. */
void func_0011B0A0(void)
{
    D_00134688 = 0;
}

/* Waits for the start of the screen refresh interval. */
ASM_FUNC("asm/core", func_0011B0B0);
