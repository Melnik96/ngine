Nutty Engine
===========

3D game engine write in C.

Function Naming
------------
ngine_<obj_name>_<action>(type _arg, ...);

Features
--------
- scene management
-   tree-based scene graph

Architecture
------------
|----------------------|--------|---------------|
||gui		      |||      |||nodes|	|
|----------------------|--------|---------------|
||graphics	      |||audio |||logic|	|
|----------------------|--------|---------------|
||OpenGL ES||OpenGL 3x|||FMOD  |||c scripting|	|
|----------------------|------------------------|



Renderer
- lighting (point, shape lighting)
- teselation displaysment

Matrix mul order: pers_proj * (cam_rot * cam_trans) * (trans * rot * scale)

Scene graph pipeline
obj:
- (vec3)position
- (vec4)rotatation qaut
- (vec3)scale

pso = pos*scale*rot
world_pso = pso+child_pso
cam_space_world_pso = world_pso+(-cam_pso)
perspective_cswp = get_perspective(cam_space_world_pso, tan(fov/2))

TODO camera_pso

Resources(Asets)
- models
- materials
- textures
- shader programs
- scripts
- sounds

TODO
----
- core
-   network
-     cluster system support
-     remote console control
-   module system
-     C dynamic linking
-   multi-threaded
-     ^binary thread priority(поток виконується один раз на кожні n\\2 фрейми,
-       але рендер виконується в кожному фреймі)
-   data structure serialization
-   SIMD math
-   costom memory alocators
-   fixed fps
-   scons build system
-   use own input system insted of glfw
-     remote input
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
- sound(FMOD)
-   virtually unlimited number of 3D sound sources
-   zone sound effects
- physics(bullet3d or ODE based)
-   aircraft simulation
- logic
-   C scripting using tcc
-   interactive C console
- animation
- tools
-   blender3d plugin
-     in blender render window
-   costom asset file format
- weather system
- Wayland display protocol support
- voxel
