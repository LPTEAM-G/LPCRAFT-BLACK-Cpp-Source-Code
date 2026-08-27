![logo](logo.png)

![Standard](https://img.shields.io/static/v1?label=Standard&message=C%2B%2B11&labelColor=blue&color=lightgrey)
![Arch](https://img.shields.io/static/v1?label=Arch&message=Arm%20Thumb&labelColor=yellow&color=lightgrey)
![Platform](https://img.shields.io/static/v1?label=Platform&message=Android&labelColor=green&color=lightgrey)

\|English\|[中文](README_zh.md)\|

---

**LPCRAFT** is a third-party client for **Minecraft PE 0.14.3**.

This is the reverse-engineered modification part of **LPCRAFT**, and does **not** include the **APK itself**. This project is only used to generate the **liblpteam.so** library for the **armeabi-v7a** architecture. The library is eventually loaded by the game and executes in the **JNI_OnLoad** function, or is invoked through **Java-layer Native function calls**, along with a series of other operations to achieve the intended purposes. This project is not intended to develop **cheats** that break the game balance; rather, it focuses more on **visual enhancements** to the game itself, or some **auxiliary features** that do not disrupt game balance.

> This project currently supports compilation only on **Arm64 Linux systems**.

You can use the **`build.sh`** script in the project root directory to conveniently manage the build process. Before using it, please install the required NDK toolchain into the **`/opt`** directory.

[Click here to download the required NDK toolchain](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/android-ndk-aide_arm64.tar.xz)

The **`build.sh`** script supports the following commands:

|Parameter|Description|
|:---:|---|
|`--init`|If the `.build` directory exists, delete it, then recreate it and initialize CMake in Release mode.|
|`--b`|Build the project. If not yet initialized, it will prompt you to initialize first; upon successful compilation, it will generate `liblpteam.so` in the `out` directory.|
|`--command`|Generate and link the `compile_command.json` in the project root directory for use with **clangd**, while also updating **GLOB_RECURSE** without re‑initializing CMake. It is recommended to run this command after adding new C++ source files.|
|`--clean`|Delete the `.build` directory.|
|`--help`|Display the help information for `build.sh`.|

---

If you need to analyze the disassembled assembly code and C++ code from the game, you can download it here:

[Downloadable analysis content](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/lpcraft-black-project-analytical.zip)

> The archive contains assembly code, the C++ files obtained from disassembly, and exported symbol tables and v-tables.

Please note that the game SO uses the **ARM Thumb** instruction set. This means that if you obtain a callable function pointer by:
```

base address of the SO in memory + vaddr of the function in the SO file

```
be sure to **add `+1`** to indicate Thumb mode, for example:
```cpp
void(*func)() = (void(*)())(base + offset + 1);
```