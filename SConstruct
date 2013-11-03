#!/usr/bin/env python

release_cflags = "-O3"
debug_cflags = "-g"

env = Environment(
    CPATH = 'external/mongoose',
    CFLAGS = '-O2',
)

ngine_sources = [Glob('source/*.c'),
		 Glob('source/math/*.c'),
		 Glob('source/cntr/*.c')]

ngine = env.SharedLibrary(ngine_sources)
env.Program(Glob('main.c') + [ngine], LIBS=['dl', 'pthread', 'GL', 'GLEW', 'glfw'])