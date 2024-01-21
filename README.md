# OpenGL-Practice

[代码仓库](https://github.com/bit704/OpenGL-Practice)

使用VS2022。

目录：

- 0-test
  - 0-testGLFW
  - 0-testGLUT
  - 1-triangle
  - 2-rectangle
  - 3-glsl
  - 4-texture
  - 5-transform
  - 6-coordinate-system
  - 7-camera-control
- 1-lighting
  - 0-color
  - 1-basic-lighting
  - 2-material
  - 3-lighting-map
  - 4-light-caster

- 2-model
  - 0-assimp

- 3-advanced
  - 0-depth-testing
  - 1-stencil-testing
  - 2-blending-face-culling
  - 3-framebuffer
  - 4-cubemap
  - 5-geometry-shader
  - 6-instancing
  - 7-anti-aliasing

- 4-advanced-lighting
- 5-PBR
- 6-practice
- 7-guest

注意事项：

1. 各个代码文件首部有详细说明。
2. 通用代码置于tools文件夹下。
3. 将glad、glm、stb_image、assimp库的头文件加入**属性 -> C/C++ -> 附加包含目录**。
4. assimp库直接用[官网](https://assimp.org/)下载的预编译的dll和lib就可以。将assimp库的库文件夹加入**属性 -> 链接器 -> 常规 -> 附加库目录**，库文件名加入**属性 -> 链接器 -> 输入 -> 附加依赖项**。不知道为什么，`assimp-vc143-mt.dll`不能和`assimp-vc143-mt.lib`一样进行上述配置，否则会报错`fatal error LNK1107: 文件无效或损坏: 无法在 0x300 处读取`，应另外将`PATH=dll所在文件夹`加入**属性 -> 调试 -> 环境**。
5. `#include <glad/glad.h>`应放在所有OpenGL头文件前面。`glad.c`应加入源文件中。
6. 只包含宏的`std_image.c`应加入源文件中。
7. 同一项目下只有需要运行的一个main函数未注释，可以自行修改。

参考资料：

[主页 - LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/)

Computer Graphics with OpenGL 第四版 / Donald Hearn etc.
