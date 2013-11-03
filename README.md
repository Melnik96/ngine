Nutty Engine
===========

3D game engine write in C.

Features
--------

TODO
----
- core
-   network
-     cluster system support
-     remote console control
-   module system
-     C dynamic linking and python support
-   multi-threaded
-     ^binary thread priority(поток виконується один раз на кожні n\\2 фрейми,
-       але рендер виконується в кожному вреймі)
-   data structure serialization
-   SIMD math
-   costom memory alocators
-   fixed fps
-   scons build system
- scene management
-   tree-based scene graph
- rendering
-   multi-monitor and multi-window output
-   frustum culling
-   material system
-   LOD system
-   lighting
-     per-pixel dynamic lighting
-     real-time global illumination
-     SSAO
-     lightmap
-     scattering
-     shape lighting
-     god rays
-   shadows
-   tessellation with displacement mapping
-   depth of field
-   subsurface scattering
-   HDR rendering
-   dual quaternion skinning
-   stereo 3D
-   ngl(Nutty GUI Library)
- sound(OpenAL)
-   virtually unlimited number of 3D sound sources
-   zone sound effects
- physics(bullet3d or ODE based)
- logic
- animation
- tools
-   blender3d plugin
-     in blender render window
-   costom asset file format
- weather system
- Wayland display protocol support
