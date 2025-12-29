# MiniRT

This project has been created as part of the 42 curriculum by **caburges** and **alsuchon**.

## Description

The MiniRT project is a ray tracer implementation exercise in the 42 curriculum that introduces students to computer graphics, 3D rendering, and mathematical foundations of ray tracing. The project involves creating a program that generates photorealistic images by simulating the physical behavior of light rays as they interact with 3D objects.

The challenge is to implement ray-object intersection algorithms, handle light sources, compute shadows, and manage a scene described in a custom file format. This project serves as an introduction to computer graphics fundamentals including vector mathematics, geometric transformations, color theory, and the MiniLibX graphics library.

## Key Features

- Ray tracing engine with camera positioning and orientation
- Support for multiple geometric objects:
  - Spheres with adjustable radius
  - Planes with normal vectors
  - Cylinders with height and diameter
- Ambient, diffuse, and specular lighting
- Shadow computation for realistic lighting
- Scene parsing from .rt configuration files
- Real-time rendering with MiniLibX
- Camera field of view control
- RGB color support for objects and lights
- Anti-aliasing capabilities
- Keyboard controls for interactive navigation
- Fully compliant with 42's norminette coding standards

## Visual Examples

### Scene Renders

![Temple Scene](./temple.png)

_Stone temple lit by warm ambient and point lights._

![Snowman Scene](./snowman.png)

_Snowman with multiple spheres and soft shadows._

![Room Walls](./room_walls.png)

_Interior walls illustrating planes, lighting, and shadow falloff._

![Sphere Shadow](./sphere_shadow.png)

_Sphere casting a defined shadow to validate intersection and shading._


## Instructions

### Prerequisites

- C compiler (cc/gcc)
- Make
- A Unix-based operating system (Linux or macOS)
- MiniLibX library
- X11 development libraries (Linux)
  - `sudo apt-get install libx11-dev libxext-dev` (Debian/Ubuntu)
- Math library (libm)

### Installation

Clone the repository:

```bash
git clone https://github.com/caburges/minirt.git
cd minirt
```

### Compilation

To compile the project, run:

```bash
make
```

This will:
1. Compile the libft library
2. Compile the MiniLibX library
3. Generate a `miniRT` executable

### Usage

Run the program with a scene file:

```bash
./miniRT scene/scene1.rt
```

#### Scene File Format

Scene files (.rt) define the 3D world using the following elements:

**Ambient Lighting:**
```
A 0.2 255,255,255
```
Format: `A [ratio] [R,G,B]`
- ratio: ambient lighting intensity (0.0 to 1.0)
- R,G,B: color values (0-255)

**Camera:**
```
C 0,0,-10 0,0,1 70
```
Format: `C [x,y,z] [nx,ny,nz] [fov]`
- x,y,z: camera position
- nx,ny,nz: orientation vector (normalized)
- fov: field of view in degrees (0-180)

**Light:**
```
L -5,5,-15 0.8 255,255,255
```
Format: `L [x,y,z] [brightness] [R,G,B]`
- x,y,z: light position
- brightness: light intensity (0.0 to 1.0)
- R,G,B: color values (0-255)

**Sphere:**
```
sp 0,0,5 4.0 255,0,0
```
Format: `sp [x,y,z] [diameter] [R,G,B]`
- x,y,z: sphere center position
- diameter: sphere diameter
- R,G,B: color values (0-255)

**Plane:**
```
pl 0,0,0 0,1,0 200,200,200
```
Format: `pl [x,y,z] [nx,ny,nz] [R,G,B]`
- x,y,z: point on the plane
- nx,ny,nz: normal vector (normalized)
- R,G,B: color values (0-255)

**Cylinder:**
```
cy 0,0,0 0,1,0 2.0 5.0 0,255,0
```
Format: `cy [x,y,z] [nx,ny,nz] [diameter] [height] [R,G,B]`
- x,y,z: cylinder center position
- nx,ny,nz: axis orientation (normalized)
- diameter: cylinder diameter
- height: cylinder height
- R,G,B: color values (0-255)

#### Example Scenes

The project includes several example scenes in the `scene/` directory:

```bash
./miniRT scene/sphere_shadow.rt    # Demonstrates shadow rendering
./miniRT scene/cylinder_rainbow.rt # Multiple colored cylinders
./miniRT scene/snowman.rt          # Complex multi-object scene
./miniRT scene/temple.rt           # Architectural scene
./miniRT scene/room_walls.rt       # Indoor scene with walls
```

### Controls

- `ESC` - Exit the program
- `Arrow Keys` - Navigate/rotate camera (if implemented)
- `W/A/S/D` - Move camera (if implemented)
- `X` (close button) - Exit the program

### Available Make Rules

- `make` or `make all` - Compiles the project
- `make clean` - Removes object files
- `make fclean` - Removes object files and executables
- `make re` - Recompiles the entire project
- `make norm` - Checks norminette compliance (if implemented)

## Project Structure

### Core Files

- [main.c](srcs/main.c) - Entry point and main rendering loop
- [Makefile](Makefile) - Build configuration
- [minirt.h](includes/minirt.h) - Main header file with structures and prototypes

### Parsing

Scene file parsing and validation:
- [parsing_file.c](srcs/parsing_file.c) - Scene file reading and parsing
- [parsing_types.c](srcs/parsing_types.c) - Object type parsing
- [check_objs.c](srcs/check_objs.c) - Object validation
- [check_cylinder.c](srcs/check_cylinder.c) - Cylinder-specific validation

### Rendering & Graphics

Window management and rendering:
- [init_mlx.c](srcs/init_mlx.c) - MiniLibX initialization
- [draw.c](srcs/draw.c) - Main drawing and rendering functions
- [camera.c](srcs/camera.c) - Camera setup and ray generation

### Ray Tracing

Core ray tracing algorithms:
- [ray.c](srcs/ray.c) - Ray creation and manipulation
- [intersections.c](srcs/intersections.c) - Ray-object intersection calculations
- [prepare_initial_computations.c](srcs/prepare_initial_computations.c) - Intersection computation preparation

### Geometric Objects

Object-specific implementations:
- [sphere.c](srcs/sphere.c) - Sphere intersection and normal calculation
- [plane.c](srcs/plane.c) - Plane intersection and normal calculation
- [cylinder.c](srcs/cylinder.c) - Cylinder intersection and normal calculation

### Lighting & Shading

Light and color calculations:
- [light.c](srcs/light.c) - Lighting calculations (diffuse, specular)
- [shadow.c](srcs/shadow.c) - Shadow ray casting and computation
- [colour_maths.c](srcs/colour_maths.c) - Color operations and blending

### Mathematics

Vector and matrix operations:
- [maths_utils.c](srcs/maths_utils.c) - General mathematical utilities
- [tuple_utils.c](srcs/tuple_utils.c) - Vector/point operations
- [tuple_utils2.c](srcs/tuple_utils2.c) - Additional vector operations
- [tuple_utils3.c](srcs/tuple_utils3.c) - Extended vector utilities

### User Interaction

Event handling:
- [keyboard.c](srcs/keyboard.c) - Keyboard input handling
- [actions.c](srcs/actions.c) - User action processing

### Utilities

Helper functions:
- [utils.c](srcs/utils.c) - General utility functions
- [utils2.c](srcs/utils2.c) - Additional utilities

## Technical Details

### Ray Tracing Algorithm

The ray tracer uses the following pipeline:

1. **Scene Parsing**: Read and validate the .rt configuration file
2. **Camera Setup**: Configure camera position, orientation, and field of view
3. **Ray Generation**: For each pixel, generate a ray from the camera through the viewport
4. **Intersection Testing**: Test the ray against all objects in the scene
5. **Shading Calculation**: For the closest intersection:
   - Calculate surface normal
   - Compute ambient lighting contribution
   - Cast shadow rays to each light source
   - Calculate diffuse and specular components (Phong reflection model)
6. **Color Accumulation**: Combine all lighting contributions
7. **Pixel Rendering**: Set the pixel color in the image buffer

### Mathematical Foundations

#### Vector Operations
- Dot product for angle calculations and projections
- Cross product for perpendicular vectors
- Vector normalization for direction vectors
- Vector addition/subtraction for position calculations

#### Ray-Object Intersections

**Sphere**: Solved using quadratic equation
```
t² + 2bt + c = 0
where ray = origin + t * direction
```

**Plane**: Solved using dot product
```
t = (plane_point - ray_origin) · plane_normal / (ray_direction · plane_normal)
```

**Cylinder**: Combination of quadratic equation (body) and plane intersection (caps)

### Lighting Model

The project implements the **Phong reflection model**:

- **Ambient**: `I_ambient = k_a * I_a`
- **Diffuse**: `I_diffuse = k_d * (L · N) * I_light`
- **Specular**: `I_specular = k_s * (R · V)^n * I_light`

Where:
- L = light direction
- N = surface normal
- R = reflection vector
- V = view direction
- n = shininess coefficient

### Shadow Computation

For each light source, a shadow ray is cast from the intersection point toward the light. If any object intersects this ray, the point is in shadow and only ambient lighting is applied.

### Color Management

Colors are represented as RGB tuples with values from 0-255. Color operations include:
- Addition and subtraction for light accumulation
- Scalar multiplication for intensity
- Component-wise multiplication for color filtering
- Clamping to ensure values stay within valid range

### Memory Management

The project includes comprehensive memory management:
- Proper allocation and deallocation of scene objects
- Cleanup of MiniLibX resources on exit
- Error handling with appropriate cleanup
- No memory leaks (verified with valgrind)

