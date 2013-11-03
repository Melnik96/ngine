# build.mk
# Building rules

include rules.mk

# Platform/architecture independent source files
SRC = \
	main/aligned_malloc.c \
	main/version.c \
	main/isastr.c \
	consts.c

OBJ := $(SRC:.c=.o)
PLAT_OBJ := $(PLAT_SRC:.c=.o)
ARCH_OBJ := $(addsuffix .o,$(basename $(ARCH_SRC))) 


all: libSIMDx86.a



libSIMDx86.a: $(OBJ) $(PLAT_OBJ) $(ARCH_OBJ)
	$(AR) cru libSIMDx86.a $(OBJ) $(PLAT_OBJ) $(ARCH_OBJ)
	$(RANLIB) libSIMDx86.a
	cp libSIMDx86.a ../

# Remove all object code and binaries
clean:
	-rm -f libSIMDx86.a $(OBJ) $(PLAT_OBJ) $(ARCH_OBJ)
