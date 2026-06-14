# Wavefront OBJ Reader

A faithful C++ reader for Wavefront OBJ and MTL files.

This project is designed for graphics tools, asset pipelines, and engine development where preserving the original contents of the file is more important than performing automatic transformations.

This reader is intended as a low-level asset ingestion layer for graphics tools and build pipelines.

## Features
- OBJ file support
- MTL file support
- Vertex (v) parsing
- Texture coordinate (vt) parsing
- Normal (vn) parsing
- Face (f) parsing
- Object (o) support
- Group (g) support
- Material assignment (usemtl) support
- Material library (mtllib) support
- Comment preservation
- Exact index retention
- No automatic triangulation
- No mesh optimization
- No hidden data modification

## Design Goals

The reader follows a simple philosophy:

> Read the file faithfully and preserve its structure.

Many OBJ loaders automatically triangulate faces, reorder data, optimize meshes, or discard hierarchy information. This reader focuses on preserving the original contents of the source file so that higher-level tools can decide how the data should be processed.

## Example
```cpp
Wavefront_OBJ_File obj;

if (obj.Load_File("cube.obj"))
{
    std::cout << "Vertices: "
              << obj.v_count()
              << std::endl;
}
```

---

## Current Status

Under active development.

## Implemented

- OBJ parsing
- MTL parsing
- Object hierarchy
- Group hierarchy
- Material assignment

## Planned

- Additional validation
- Unit tests

## Project Structure

```text
Wavefront_OBJ_File
│
├── OBJ Parser
├── MTL Parser
├── DW_IO
├── DW_String
└── Wavefront_Tools
```

## License

MIT
