/*
* ʹ��nuget��װnupengl
* �ο���https://www.cnblogs.com/steamedbun/p/11259376.html
* ����packages�ļ�����
* 
* ʹ��GLUT��
* Computer Graphics with OpenGL ���İ� ʹ��GLUT
*/

#include<gl/GLUT.H>

void display();
int testGLUT(int, char**);

//int main(int argc, char** argv)
//{
//    return testGLUT(argc, argv);
//}

int testGLUT(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // ������ʾģʽ��RGB��ɫģ�ͺ͵�����
    glutInitWindowPosition(100, 100); // ���ڵĳ�ʼλ�ã���Ļ���Ͻ�Ϊԭ��
    glutInitWindowSize(400, 400); // ���ڵĴ�С
    glutCreateWindow("test"); // ���ڱ�����
    glutDisplayFunc(&display); // ע�ᵱǰ���ڵ���ʾ�ص�����

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ����ð�ɫ

    glMatrixMode(GL_PROJECTION); // ͶӰ�任
    gluOrtho2D(0.0, 200, 0.0, 150.0); // ʹ����ͶӰ��һ��x������0~200��y����0~150��Χ�ڵľ�����������ͶӰ����ʾ������

    glutMainLoop(); // ��Ⱦѭ��

    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // ���

    // ����һ�����Ͻ��ڣ�50��100�������½��ڣ�150��50���ĺ�ɫ����
    glColor3f(0.0f, 0.0f, 0.0f); 
    glRectf(50.0f, 100.0f, 150.0f, 50.0f); 

    glFlush(); // ���OpenGL�������
}

