#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
int width = 960, height = 600; // 窗口画幅大小
struct line{
   int x1,y1,x2,y2;
};
vector<line>Lines;  // 存储线条
int gridSize = 4;   // 网格大小
int pointFlag=false;//画线与修改模式转换标志符
int index,pos;      //修改的端点
void setSquare(GLint x, GLint y, int size) // 画方格
{
   glColor3f(255, 0, 0); // 点颜色
   glPointSize(1.0f);
   glBegin(GL_POINTS);
   int x0= ((float)x / size) * size;
   int y0= ((float)y / size) * size;
   for (float i = x0; i <= x0 + size; i ++)
   {
       for (float j = y0; j <= y0 + size; j ++)
       {
           glVertex2f(i, j);
       }
   }
//    glVertex2f(x0, y0);
//    glVertex2i(x0 + size, y0);
//    glVertex2i(x0 + size, y0 + size);
//    glVertex2i(x0, y0 + size);
   glEnd();
}

void drawGrid() // 绘制网格
{
   for (int i = 0; i <= width; i += gridSize)
   {
       for (int j = 0; j <= height; j += gridSize)
       {
           glColor3f(0.8, 0.85, 0.8); // 网格线颜色
           glLineWidth(0.4);
           glBegin(GL_LINES);
           glVertex2i(i, 0);
           glVertex2i(i, height);
           glVertex2i(0, j);
           glVertex2i(width, j);
           glEnd();
       }
   }
}

void BresenhamLine(int x0, int y0, int x1, int y1)
{
   int dx = abs(x1 - x0);
   int dy = abs(y1 - y0);
   int sx = x0 < x1 ? 1 : -1;
   int sy = y0 < y1 ? 1 : -1;
   int e = (dx > dy ? dx : -dy) / 2;
   int x = x0, y = y0;
   while (true) {
       // 填充方格，而不是绘制点
       setSquare(x, y, gridSize);
       if (x == x1 && y == y1) break;
       int p = e;
       if (p > -dx) { e -= dy; x += sx; }
       if (p < dy) { e += dx; y += sy; }
   }
}

void DrawLine()
{
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口显示内容
   drawGrid(); // 绘制网格
   for(int i=0;i<Lines.size();i++) {
       int x1 = Lines[i].x1, y1 = Lines[i].y1, x2 = Lines[i].x2, y2 = Lines[i].y2;
       BresenhamLine(x1, y1, x2, y2);
   }
   glFlush();
}

// 鼠标拖动
void dragMouse(int x, int y) {
   if(!pointFlag){
       Lines.back().x2=x,Lines.back().y2=y;
   }
   else{
       if(pos==1){
           Lines[index].x1=x,Lines[index].y1=y;
       }
       else{
           Lines[index].x2=x,Lines[index].y2=y;
       }
   }
   DrawLine(); // 画线
   printf("%d %d \n", x,y); // 把两个坐标打印出来
   glFlush();
}

// 鼠标监听，画点
void myMouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
       if(!pointFlag){
           Lines.back().x2=x,Lines.back().y2=y;
       }
       else{
           if(pos==1){
               Lines[index].x1=x,Lines[index].y1=y;
           }
           else{
               Lines[index].x2=x,Lines[index].y2=y;
           }
       }
       DrawLine(); // 画线
       printf("%d %d \n", x,y); // 把两个坐标打印出来
       glFlush();
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       if(!pointFlag){//画线模式
           Lines.push_back({x,y,x,y});
       }
       else{//修改模式
           int dis=INT_MAX;
           for(int i=0;i<Lines.size();i++){
               int d1=sqrt((x-Lines[i].x1)*(x-Lines[i].x1)+(y-Lines[i].y1)*(y-Lines[i].y1));
               if(dis>d1){
                   dis=d1;
                   index=i;
                   pos=1;
               }
               int d2=sqrt((x-Lines[i].x2)*(x-Lines[i].x2)+(y-Lines[i].y2)*(y-Lines[i].y2));
               if(dis>d2){
                   dis=d2;
                   index=i;
                   pos=2;
               }
           }
       }
       printf("%d %d \n", x,y); // 把两个坐标打印出来
   }
   if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
       pointFlag=!pointFlag;
   }
}
void keyboard(unsigned char key, int a, int b){
   switch(key){
       case ' ':
           if(!Lines.empty())Lines.pop_back();
           DrawLine();
           break;
       case '\r':
           Lines.clear();
           glClearColor(1, 1, 1, 1); // 设置绘制窗口颜色为白色
           glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
           glutPostRedisplay(); // 请求OpenGL重新绘制窗口
           glFlush();
           break;
   }
}
int main(int argc, char** argv) {
   glutInit(&argc, argv); // 初始化

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置绘制模式
   glutInitWindowPosition(180, 50); // 设置窗口出现的位置
   glutInitWindowSize(width, height); // 设置窗口大小
   glutCreateWindow("BresenhamLine"); // 创建窗口

   glClearColor(1, 1, 1, 1); // 设置绘制窗口颜色为白色
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   glPointSize(3.0f); // 设置点的大小

   glMatrixMode(GL_PROJECTION); /* 设置为投影类型模式和其他观察参数 */
   glLoadIdentity(); /* 设置为投影类型模式和其他观察参数 */
   gluOrtho2D(0, width, height, 0);

   glutDisplayFunc(DrawLine); // 绘制回调函数,glut机制，它觉得需要重新绘制的时候就会执行
   glutMouseFunc(myMouse);    // 鼠标监听回调函数
   glutMotionFunc(dragMouse); // 鼠标拖动
   glutKeyboardFunc(keyboard);// 键盘监听回调函数
   glutMainLoop();
}