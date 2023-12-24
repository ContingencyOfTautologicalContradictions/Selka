# Selka

A transpiler from modern C++ to the different programming languages: HLSL, GLSL, MSL and WGSL.


## Usage

Selka requires a C++23 capable compiler.

To use Selka, first generate from your C++ shader file, the Clang AST dump file in a JSON format with the inclusion of ``Include/Selka.hpp`` color diagnostics and the stdlib. Please remember to generate a dump file per C++ shader file, Clang won't generate a JSON array from multiple C++ shader files and the transpilation will fail.

An example:

```sh
clang++ File1.cc -nostdlib -std=c++23 -Xclang -ast-dump=json -fno-color-diagnostics -fsyntax-only -I ../Include > File1.selka
clang++ File2.cc -nostdlib -std=c++23 -Xclang -ast-dump=json -fno-color-diagnostics -fsyntax-only -I ../Include > File2.selka
```

Later, execute the Selka binary by giving it the path of the directory that will be used as an input to scan for valid Clang AST sources in a JSON format, as the former argument. For it to be a valid Selka file, must terminate with the file extension ``.selka``.

Then, pass the output directory as the second argument. This output directory will be used to place the produced shader file.

As the third argument, you have to pass the shading language you want to produce, which must be described with one of the following values: 

- ``hlsl``
- ``glsl``
- ``msl``
- ``wgsl``

An optional fourth argument can be given in the form of a natural number, symbolizing the number of threads that Selka will use to process in parallel your provided files. By default, this value is settle to the number of CPU's physical threads.

A valid example to generate Metal shader files (assuming the Selka binary is at the PATH variable as ``selka``, and your ``.selka`` files are at the Source folder):

```sh
mkdir Output
selka ./Source ./Output msl
```

Another valid example to generate Metal shader files (assuming the Selka binary is at the PATH variable as ``selka``, and your ``.selka`` files are at the Source folder) with a limited thread pool of 4 threads:

```sh
mkdir Output
selka ./Source ./Output MSL 4
```

Yet another valid example to generate HLSL shader files (assuming the Selka binary is at the PATH variable as ``selka``, and your ``.selka`` files are at the Source folder) with a limited thread pool of 4 threads:

```sh
mkdir Output
selka ./Source ./Output HLSL 4
```

## Progress

| Version      | Status      |
|--------------|-------------|
| C++11        | In-progress |
| C++14        | Unfinished  |
| C++17        | Unfinished  |
| C++20        | Unfinished  |
| C++23        | Unfinished  |
| C++26        | Unfinished  |