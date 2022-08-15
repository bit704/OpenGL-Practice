#version 330 core
out vec4 FragColor;
uniform vec4 uniformColor; // 在OpenGL程序代码中设定这个变量
in vec3 ourColor;

void main()
{
	FragColor = mix(vec4(ourColor, 1.0), uniformColor, 0.5); // 两种颜色做平均
}