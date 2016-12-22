RTOS keeps the memory allocation API in its portable layer. The portable layer is
 outside of the source files that implement the core RTOS functionality, 
 allowing an application specific implementation appropriate for the real time system being developed to be provided. 
 When the RTOS kernel requires RAM, instead of calling malloc(), it instead calls pvPortMalloc().
 When RAM is being freed, instead of calling free(), the RTOS kernel calls vPortFree().



 Following below:

    heap_1 - the very simplest, does not permit memory to be freed
    heap_2 - permits memory to be freed, but not does coalescence adjacent free blocks.
    heap_3 - simply wraps the standard malloc() and free() for thread safety
    heap_4 - coalescences adjacent free blocks to avoid fragmentation. Includes absolute address placement option
    heap_5 - as per heap_4, with the ability to span the heap across multiple non-adjacent memory areas


The xPortGetFreeHeapSize() API function returns the total amount of heap space that remains unallocated when the function is called, 
and the xPortGetMinimumEverFreeHeapSize() API function returns lowest amount of free heap space that has 
existed system the FreeRTOS application booted. 
Neither function provides information on how the unallocated memory is fragmented into smaller blocks.

