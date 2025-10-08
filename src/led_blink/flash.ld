/* RP2350 Bare-Metal Linker Script */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x10000000,  LENGTH = 4M 
  RAM   (rwx) : ORIGIN = 0x20000000,  LENGTH = 520K
}

__heap_size = 8K;

/*Map sections to memory*/
SECTIONS
{
	.boot : {
		KEEP(*(.vector_table))
		KEEP(*(.start_block))
		KEEP(*(.init))
	} > FLASH

	TEXT : {
		*(.text*)
		*(.rodata*)
		__etext = .;
	} > FLASH

	DATA : {
		__data_lma = LOADADDR(DATA);
		__data = .;
		*(.data)
		*(.data*)
		__edata = .;
	} > RAM AT> FLASH

	BSS  : {
		__bss = .;
		*(.bss*)
	} > RAM
	__ebss = .;
	__end = .;

    /* Stack section (grows downward) */
    .stack :
    {
        . = ALIGN(8);
        __stack_bottom__ = .;
        . = . + 4K;  /* 4KB stack, adjust as needed */
        __stack_top = .;
    } > RAM
}