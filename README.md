![logo](logo.png)

\|English\|[中文](README_zh.md)\|

---

**LPCRAFT** is a third-party client for **Minecraft PE 0.14.3**.

This is the reverse-engineered modification part of **LPCRAFT**, excluding the **assets** portion. This project is solely used to generate the **liblpteam.so** file targeted at the **armeabi-v7a** architecture. The resulting library will ultimately be loaded by the game, and it performs a series of operations inside the **JNI_OnLoad** function to achieve its goals.

> This project currently only supports compilation on **Arm64 Linux systems**.

You can use the **`build.sh`** script located in the project root to conveniently manage the build process. Before doing so, you should install the required NDK toolchain in the **`/opt`** directory.

[Download the required NDK toolchain here](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/android-ndk-aide_arm64.tar.xz)

The **`build.sh`** script supports the following commands:

| Argument     | Description                                                                                                                                                                                                 |
|:------------:|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `--init`     | If the **`.build`** directory exists, delete it, then recreate it, and initialize CMake in Release mode.                                                                                                    |
| `--b`        | Build the project. If not initialized, it will first ask you to initialize, and upon success, it will generate **`liblpteam.so`** in the **`out`** directory.                                                |
| `--command`  | Generate and link a **`compile_command.json`** file at the project root for **clangd** to use. This also updates **GLOB** without re-running CMake; it is recommended to run this after adding new C++ source files. |
| `--clean`    | Delete the **`.build`** directory.                                                                                                                                                                          |
| `--help`     | Display help information for **`build.sh`** (currently only available in Chinese).                                                                                                                          |

---

If you need to analyse the disassembled assembly code and C++ code of the game, you can download them here:

[Analytical materials](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/lpcraft-black-project-analytical.zip)

> Includes exported symbol tables and virtual tables.

Please note that the assembly used in the game's SO file is **ARM Thumb**. This means that if you obtain a callable function pointer via:
```

base address of the SO in memory + function's vaddr within the SO

```
do not forget to add **`+1`** to indicate Thumb mode, for example:
```cpp
void(*func)() = (void(*)())(base + offset + 1);
```