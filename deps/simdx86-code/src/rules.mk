# Assembly language source code to object code (NASM [Intel] and AS [AT&T] syntax)
%.o: %.asm
	$(NASM) $*.asm -o $*.o
%.o: %.S
	$(AS) $*.S -o $*.o

# C language source code to object code
%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o
