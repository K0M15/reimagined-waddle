# RT File Format Specification

The RT file format is a scene description format designed for ray tracing applications. This format defines 3D scenes containing geometric objects, lighting, camera settings, and material properties using a structured text-based syntax.

## File Structure

RT files use a line-based format where each line defines either a scene element or serves as a comment. The parser supports the following element types:

### Required Elements

Every valid RT scene must contain exactly one camera and one ambient light definition.

### Comment Lines

Lines beginning with `#` are treated as comments and ignored during parsing. Empty lines are also ignored.

## Element Specifications

### Camera (C)
Defines the viewpoint and projection parameters for the scene.

**Syntax:** `C x,y,z vx,vy,vz fov`

- **Position:** `x,y,z` - Camera position coordinates (floating-point)
- **Look Direction:** `vx,vy,vz` - Normalized direction vector (floating-point, range: -1.0 to 1.0)
- **Field of View:** `fov` - Horizontal field of view in degrees (integer, range: 0-180)

**Example:** `C 0,0,0 0,0,-1 90`

### Ambient Light (A)
Sets the global ambient lighting for the scene.

**Syntax:** `A intensity r,g,b`

- **Intensity:** `intensity` - Ambient light ratio (floating-point, range: 0.0-1.0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `A 0.2 255,255,255`

### Point Light (L)
Defines a point light source in the scene.

**Syntax:** `L x,y,z brightness r,g,b`

- **Position:** `x,y,z` - Light source coordinates (floating-point)
- **Brightness:** `brightness` - Light intensity (floating-point, range: 0.0-1.0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `L -3,8,-2 0.7 255,255,255`

## Geometric Objects

### Sphere (sp)
Defines a spherical object.

**Syntax:** `sp x,y,z diameter r,g,b [reflectivity scatter emitting brightness texture bump]`

- **Position:** `x,y,z` - Center coordinates (floating-point)
- **Diameter:** `diameter` - Sphere diameter (floating-point, > 0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `sp 2,2,-4 2.0 255,0,0`

### Plane (pl)
Defines an infinite plane.

**Syntax:** `pl x,y,z nx,ny,nz r,g,b [reflectivity scatter emitting brightness texture bump]`

- **Position:** `x,y,z` - Point on the plane (floating-point)
- **Normal:** `nx,ny,nz` - Normalized surface normal vector (floating-point, range: -1.0 to 1.0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `pl 0,-3,-10 0,1,0 0,255,0`

### Cylinder (cy)
Defines a finite cylinder.

**Syntax:** `cy x,y,z nx,ny,nz diameter height r,g,b [reflectivity scatter emitting brightness texture bump]`

- **Position:** `x,y,z` - Center coordinates (floating-point)
- **Axis:** `nx,ny,nz` - Normalized cylinder axis direction (floating-point, range: -1.0 to 1.0)
- **Diameter:** `diameter` - Cylinder diameter (floating-point, > 0)
- **Height:** `height` - Cylinder height (floating-point, > 0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `cy 0,10,-10 1,0,0 10.0 100.0 10,0,255`

### Cone (co)
Defines a finite cone.

**Syntax:** `co x,y,z nx,ny,nz diameter height r,g,b [reflectivity scatter emitting brightness texture bump]`

- **Position:** `x,y,z` - Base center coordinates (floating-point)
- **Axis:** `nx,ny,nz` - Normalized cone axis direction (floating-point, range: -1.0 to 1.0)
- **Diameter:** `diameter` - Base diameter (floating-point, > 0)
- **Height:** `height` - Cone height (floating-point, > 0)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `co 0,7,5 1,0,0 1.0 10.0 0,255,255`

### Triangle (tr)
Defines a triangular surface.

**Syntax:** `tr x1,y1,z1 x2,y2,z2 x3,y3,z3 r,g,b [reflectivity scatter emitting brightness texture bump]`
Write a description for the file format .rt
you can find the specs inside of src/parser
write out optional arguments and make it sound like a professional description. dont use utf8 characters, only ascii
- **Vertex 1:** `x1,y1,z1` - First vertex coordinates (floating-point)
- **Vertex 2:** `x2,y2,z2` - Second vertex coordinates (floating-point)
- **Vertex 3:** `x3,y3,z3` - Third vertex coordinates (floating-point)
- **Color:** `r,g,b` - RGB color values (integers, range: 0-255)

**Example:** `tr 0,0,0 1,0,0 0,1,0 255,128,0`

## Optional Material Properties

All geometric objects support advanced material properties as optional parameters:

### Material Parameters
- **Reflectivity:** Surface reflectance coefficient (floating-point, range: 0.0-1.0)
- **Scatter:** Surface roughness for diffuse reflection (floating-point, range: 0.0-1.0)
- **Emitting:** Light emission flag (integer, 0 or 1)
- **Brightness:** Emission intensity for emitting materials (floating-point, range: 0.0-1.0)
- **Texture:** Diffuse texture file path (string, use "*" for no texture)
- **Bump:** Normal map texture file path (string, use "*" for no bump map)

### Extended Syntax Example
```
cy 0,10,-10 1,0,0 10.0 100.0 10,0,255 0.4 0.2 0 0.8 ./moss.png ./moss_bump.png
```

## Data Format Conventions

### Coordinates
All spatial coordinates use a comma-separated format: `x,y,z`

### Colors
RGB values use comma-separated integers: `r,g,b` where each component ranges from 0 to 255

### Vectors
Direction and normal vectors use comma-separated floating-point values: `vx,vy,vz` typically normalized to unit length

### File Paths
Texture and bump map paths are specified as strings. Use "*" as a placeholder when no texture is desired.

## Parser Notes

- Elements are processed line by line
- Each element must be complete on a single line
- Whitespace between tokens is flexible
- Invalid lines will cause parsing to fail
- Camera and ambient light definitions are mandatory
- Multiple lights and objects are supported
- Material properties are optional extensions to the base format