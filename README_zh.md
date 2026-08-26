![logo](logo.png)

\|[English](README.md)\|中文|

---

**LPCRAFT** 是一个第三方的 **Minecraft PE 0.14.3** 客户端。

这是 **LPCRAFT** 的逆向修改部分，不包含 **assets** 资源。此项目仅用于生成面向 **armeabi-v7a** 架构的 **liblpteam.so** 库文件，该库最终会被游戏加载，并在 **JNI_OnLoad** 函数中执行一系列操作以达到预期目的。

> 当前项目仅支持在 **Arm64 架构的 Linux 系统** 上进行编译。

你可以使用项目根目录下的 **`build.sh`** 脚本来便捷地管理构建流程。使用前，请先将项目所需的 NDK 工具链安装到 **`/opt`** 目录下。

[点击此处下载项目所需的 NDK 工具链](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/android-ndk-aide_arm64.tar.xz)

**`build.sh`** 脚本支持以下命令：

| 参数         | 说明                                                                                                                             |
|:-----------:|---------------------------------------------------------------------------------------------------------------------------------|
| `--init`    | 若 **`.build`** 目录存在则删除，重新创建后，以 Release 模式初始化 CMake。                                                         |
| `--b`       | 构建项目。若尚未初始化，会先提示进行初始化；编译成功时，将在 **`out`** 目录下生成 **`liblpteam.so`**。                                  |
| `--command` | 生成并链接项目根目录下的 **`compile_command.json`** 以供 **clangd** 使用，同时无需重新初始化 CMake 即可更新 **GLOB**。建议每次新增 C++ 源文件后执行此命令。 |
| `--clean`   | 删除 **`.build`** 目录。                                                                                                        |
| `--help`    | 查看 **`build.sh`** 的帮助信息（目前仅提供中文）。                                                                                 |

---

如果你需要分析游戏反编译得到的汇编代码和 C++ 代码，可在此处下载：

[可分析内容下载](https://github.com/LPTEAM-G/LPCRAFT-BLACK-Cpp-Source-Code/releases/download/project-dependencies/lpcraft-black-project-analytical.zip)

> 压缩包内包含已导出的符号表和虚表。

请注意，游戏 SO 文件使用的汇编指令集为 **ARM Thumb**。这意味着，若你通过以下方式获取可调用的函数指针：
```

SO 在内存中的基址 + 函数在 SO 文件中的 vaddr

```
请务必记得 **加上 `+1`** 以指明 Thumb 模式，例如：
```cpp
void(*func)() = (void(*)())(base + offset + 1);
```