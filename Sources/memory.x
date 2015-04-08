/* ----------------------------------------------------------------------
 * This describes the MCF5213 Eval board memory map.
 * ---------------------------------------------------------------------- */
FLASH_START = 0x00015000;	 /* 256K Internal FLASH start adress */
FLASH_SIZE = 0x0002B000;	 /* 256K Internal FLASH size */
INTERNAL_RAM_START = 0x20002000;	/* 32K  Internal SRAM */
INTERNAL_RAM_SIZE = 0x00006000;	/* 32K  Internal SRAM */

MEMORY {
  rom_flash_program (rx):      ORIGIN = 0x00015000, LENGTH = 0x0002B000 /* 256K Internal FLASH */
  sram_int (rw):   ORIGIN = 0x20002000, LENGTH = 0x00005C00 /* 23K  Internal SRAM (1k pour la pile) */
  sim :        ORIGIN = 0x40000000, LENGTH = 0x40000000 /* 1G   Internal peripheral registers */
}


SECTIONS
{
  RAM_INIT : { 
    libs/crt/crt.o(.text)
    Main.o(.text)
    launch_ITs.o(.text)
    libs/spiUtils/spiUtils.o(.text)
    libs/sensorUtils/sensorUtils.o(.text)
   __DATA_RAM = .;
    *(.data)
    Main.o(.rodata)
    launch_ITs.o(.rodata)
    libs/spiUtils/spiUtils.o(.rodata)
    libs/sensorUtils/sensorUtils.o(.rodata)
    } > sram_int
   __DATA_END = .;
}

SECTIONS
{
  RAM : {
    __BSS_START = .;
    *(.bss) *(COMMON)
    } > sram_int
  __BSS_END = .;
}

SECTIONS
{
	ROM_FLASH :
		{
      *(.text)
			*(.rodata)
			*(.init)
			*(.fini)
			*(.eini)
			. = (. +15) & ~ 15 ;
		} > rom_flash_program
	__DATA_ROM = . ;
	
  }

/*	GROUP : {

    __DATA_RAM = .;
	
    .data (DATA)  LOAD(__DATA_ROM)  :
               {
                 *(.data)
               }

    .sdata (DATA) :
               {
                 *(.sdata)
               }
    __DATA_END = .;


    __BSS_START = .;
    .bss (BSS) :
               {
                 *(.bss)
               }

    .sbss (BSS) :
                {
                  *(.sbss)
                } > sram_int
   __BSS_END = .;


  }
}
*/



SECTIONS	/* Contient les commentaires ajoutes a chaque routine par gcc (stupide) */
{
	/DISCARD/ :	/* Mot clé: la section ne sera pas générée */
	{
		*(.comment)
	}
}

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */

SECTIONS
{
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }  

}
SP_INIT = INTERNAL_RAM_START + INTERNAL_RAM_SIZE -4; /*ADDR(sram_int) + SIZEOF(sram_int);*/
PROVIDE ( __SP_INIT = SP_INIT );
SP_END = SP_INIT - 0x0800+8;
PROVIDE ( __SP_END = SP_END);
HEAP_END = SP_END - 8;


/* Some identifiers for locating special memory map boundaries */
PROVIDE ( __FLASH_START = FLASH_START );	/* = rom_flash_program */
IPSBAR = 0x40000000; /* ADDR( sim ); */
PROVIDE ( __IPSBAR = IPSBAR );
PROVIDE ( __VBR_START = FLASH_START );	/* = rom_flash_program */
RAMBAR = INTERNAL_RAM_START;
PROVIDE ( __RAMBAR = RAMBAR );

