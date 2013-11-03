# SIMDx86 Compliance Test
# Runs a few tests to make sure correct results are computed

all: vector/vector_compliance matrix/matrix_compliance polygon/polygon_compliance quaternion/quaternion_compliance math/math_compliance

clean:
	make clean -C vector/
	make clean -C quaternion/
	make clean -C matrix/
	make clean -C polygon/
	make clean -C math/

vector/vector_compliance:
	make -C vector/

polygon/polygon:
	make -C polygon/

quaternion/quaternion_compliance:
	make -C quaternion/

matrix/matrix_compliance:
	make -C matrix/

math/math_compliance:
	make -C math/
