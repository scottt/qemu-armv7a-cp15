file cp15.elf
load
break main
continue

printf "cr_get(): 0x%x\n", cr_get()
printf "Try:\np (cr_get() & CR_W)\n"
