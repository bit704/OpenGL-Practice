#version 330 core
layout (location = 0) in vec3 aPos; // λ�ñ���������λ��ֵΪ0
layout (location = 1) in vec3 aColor; // ��ɫ����������λ��ֵΪ 1

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ

void main()
{
	gl_Position = vec4(aPos, 1.0); // ��һ��vec3��Ϊvec4�Ĺ������Ĳ���
	ourColor = aColor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}