#ifdef ARCH_ARM
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
#elif ARCH_AARCH64
OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
#endif

SECTIONS
{
    . = ENTRY_POINT;

    .text   ALIGN(4096) : { *(.text)   }
    .data   ALIGN(4096) : { *(.data)   }
    .bss    ALIGN(4096) : { *(.bss)    }
    .rodata ALIGN(4096) : { *(.rodata) }

    text_end = ALIGN(8);
}
