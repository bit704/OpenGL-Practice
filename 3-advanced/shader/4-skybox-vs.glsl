#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // 将输出位置的z分量等于w分量，这样透视除法后z分量永远等于1.0，让天空盒有着最大的深度值1.0
}  