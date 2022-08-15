#version 330 core
out vec4 FragColor;
uniform vec4 uniformColor; // ��OpenGL����������趨�������
in vec3 ourColor;

void main()
{
	FragColor = mix(vec4(ourColor, 1.0), uniformColor, 0.5); // ������ɫ��ƽ��
}