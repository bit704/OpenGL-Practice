/*
* 使用nuget安装nupengl
* 参考：https://www.cnblogs.com/steamedbun/p/11259376.html
* 包在packages文件夹下
* 
* 使用GLUT库
* Computer Graphics with OpenGL 第四版 使用GLUT
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
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // 窗口显示模式，RGB颜色模型和单缓存
    glutInitWindowPosition(100, 100); // 窗口的初始位置，屏幕左上角为原点
    glutInitWindowSize(400, 400); // 窗口的大小
    glutCreateWindow("test"); // 窗口标题名
    glutDisplayFunc(&display); // 注册当前窗口的显示回调函数

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 清空用白色

    glMatrixMode(GL_PROJECTION); // 投影变换
    gluOrtho2D(0.0, 200, 0.0, 150.0); // 使用正投影将一个x坐标在0~200，y坐标0~150范围内的矩形坐标区域投影到显示器窗口

    glutMainLoop(); // 渲染循环

    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // 清空

    // 绘制一个左上角在（50，100），右下角在（150，50）的黑色矩形
    glColor3f(0.0f, 0.0f, 0.0f); 
    glRectf(50.0f, 100.0f, 150.0f, 50.0f); 

    glFlush(); // 清空OpenGL命令缓冲区
}

