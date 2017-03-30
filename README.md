This project demonstrates accessing ARMv7 CP15 registers under GDB and QEMU. It's accomplished by calling helper functions with the necessary code sequence interactively in GDB.

To build the code
* Edit armv7-linaro.env to point to your ARMv7 cross compiler
* Run:
```
$ . armv7-linaro.env
$ make
```

To run the code under the QEMU emulator:
```
$ make qemu
```

In a separate terminal:
```
$ make gdb
```

Try calling the following functions interactively in GDB:
```
(gdb) p/x cr_get()
(gdb) p/x auxcr_get()
(gdb) p/x cpuid_get()
```

See (cp15.h) and (cp15.c) for more details.
