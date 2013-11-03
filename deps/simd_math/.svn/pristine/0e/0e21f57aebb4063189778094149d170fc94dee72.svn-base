# SIMDx86
# GNU Makefile (requires gmake) for UNIX-like operating systems 

# Find OS name and hardware platform
OS = $(shell uname)

#Cygwin
ifneq (,$(findstring CYGWIN, $(OS)))
	OS = win32
	ARCH = i386
endif

# Linux
ifeq ($(OS), Linux)
    ARCH = $(shell uname -m)
endif

# Solaris
ifeq ($(OS), SunOS)
	OS = Solaris
	ARCH = $(shell uname -p)
endif

# IRIX
ifeq ($(OS), IRIX)
	ARCH = mips
endif
ifeq ($(OS), IRIX64)
	OS = IRIX
	ARCH = mips
	#ARCH = mips64 
endif


FULL_MAKEFILE = Makefile.$(OS).$(ARCH)

all: libSIMDx86.a

clean:
	@cd src; $(MAKE) -f $(FULL_MAKEFILE) clean
	-rm -f libSIMDx86.a

libSIMDx86.a: force_look
	@cd src; $(MAKE) -f $(FULL_MAKEFILE) libSIMDx86.a

force_look:
	@true
