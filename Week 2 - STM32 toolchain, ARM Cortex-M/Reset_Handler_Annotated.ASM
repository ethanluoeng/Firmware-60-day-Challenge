

/* SIMPLE RESET_HANDLER EXAMPLE*/

void Reset_Handler(void)
{
    /* Given: 
    _etext as the address the init values are stored at
    _sdata as the address the static variables live at
    _edata as the end of the static variables memory*/
    uint32_t *init_values_ptr = &_etext;                        // Set a pointer to _etext                             
    uint32_t *data_ptr = &_sdata;                               // Set a pointer to _sdata

    /* Copy init values for text to data */
    if (init_values_ptr != data_ptr) {
        for (; data_ptr < &_edata;) {                           // When the data address is less than the end of the memory
            *data_ptr++ = *init_values_ptr++;                   // Copy it over and increment
        }
    }

    /* Initialize the BSS variable to 0 */
    for (uint32_t *bss_ptr = &_sbss; bss_ptr < &_ebss;) {       // Given _sbss and _ebss as start and end addresses
        *bss_ptr++ = 0;                                         // Set to 0 and increment
    }

    /* Overwriting the default value of the NVMCTRL.CTRLB.MANW bit (errata reference 13134) */
    NVMCTRL->CTRLB.bit.MANW = 1;

    /* Branch to main function */
    main();

    /* Infinite loop in case main function returns*/
    while (1);
}