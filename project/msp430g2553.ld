/* Default linker script for the msp430g2553 device */

OUTPUT_ARCH(msp430)
ENTRY(_start)

MEMORY
{
  TEXT   (rx)  : ORIGIN = 0xC000, LENGTH = 0x3FFF
  DATA   (rw)  : ORIGIN = 0x0200, LENGTH = 0x0200
  INFOMEM (rw) : ORIGIN = 0x1000, LENGTH = 0x0100
}

SECTIONS
{
  .init :
  {
    KEEP(*(.init))
  } > TEXT

  .text :
  {
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    KEEP(*(.ctors))
    KEEP(*(.dtors))
    _etext = .;
  } > TEXT

  .data :
  {
    _data = .;
    *(.data)
    *(.data*)
    _edata = .;
  } > DATA AT> TEXT
 
  .bss :
  {
    _bss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > DATA

  .noinit (NOLOAD):
  {
    *(.noinit*)
  } > DATA

  .infomem :
  {
    *(.infomem)
  } > INFOMEM

  .stack :
  {
    . = ALIGN(2);
    _stack = .;
    *(.stack)
    . = . + 0x0100;
    _estack = .;
  } > DATA

  /DISCARD/ :
  {
    *(.note*)
    *(.comment)
  }
}
