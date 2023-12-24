# Selka

A transpiler from modern C++ to the different programming languages: HLSL, GLSL, MSL and WGSL.


## Usage

To use Selka, first pass to it the path of the directory that will be used as an input to scan for valid clang AST sources in a JSON format, as the former argument. For it to be a valid Selka file, must terminate with the file extension ``.selka``.

Then, pass the output directory as the second argument. This output directory will be used to place the produced shader file.

As the third argument, you have to pass the shading language you want to produce, which must be described with one of the following values: 

- ``hlsl``
- ``glsl``
- ``msl``
- ``wgsl``

An optional fourth argument can be given in the form of a natural number, symbolizing the number of threads that Selka will use to process in parallel your provided files. By default, this value is settle to the number of CPU's physical threads.

Finally, at your C++ shader files, include ``Include/Selka.hpp``.

## Progress

| Version      | Status      |
|--------------|-------------|
| C++11        | In-progress |
| C++14        | Unfinished  |
| C++17        | Unfinished  |
| C++20        | Unfinished  |
| C++23        | Unfinished  |
| C++26        | Unfinished  |