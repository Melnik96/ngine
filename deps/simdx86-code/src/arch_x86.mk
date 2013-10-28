# arch_x86.mk
# x86 Architecture Rules

ARCH_SRC = \
	main/emms.asm \
	main/getisa_x86.asm \
	main/overlay_x86.c \
	math/math_3dnow.asm \
	math/math_387.asm \
	math/math_buffer.asm \
	math/math_sse.asm \
	math/math_sse2.asm \
	vector/vector_sse.asm \
	vector/vector_sse3.asm \
	vector/vector_3dnow.asm \
	vector/vector_buffer.asm \
	sphere/sphere_sse.asm \
	sphere/sphere_buffer.asm \
	polygon/polygon_buffer.asm \
	polygon/polygon_sse.asm
