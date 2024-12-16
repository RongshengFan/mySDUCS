#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
const int width = 960, height = 600; // 窗口画幅大小
struct vertex{
   float x,y;
};
vector<vertex>lPoints;      //记录线段的两端点，用以绘制线段
vector<vertex>Pt;           //记录曲线上的点
vector<int>C;               //存储组合数
char flag='1';              //模式标志位
int index=0;                //修改端点在数组中的索引
//计算组合数Cnk
void getCnk(){
   int n=lPoints.size();
   C.clear();
   C.resize(n);
   int i,j;
   for(j=0;j<n;j++){//循环前先从n!中把i!消掉，注意体会
       C[j]=1;
       for(i=n-1;i>=j+1;i--)
           C[j]=C[j]*i;
       for(i=n-1-j;i>=2;i--)
           C[j]=C[j]/i;
   }
}
void Bezier(){
   int n=lPoints.size();
   int m=3000;        //曲线上点的个数
   Pt.clear();
   Pt.resize(m);
   float Berstein;
   for(int i=0;i<m;i++) {
       float t = (float) i / m;
       for (int j = 0; j < n; j++) {
           Berstein = C[j] * pow(t, j) * pow(1 - t, n - 1 - j);
           Pt[i].x += lPoints[j].x * Berstein;
           Pt[i].y += lPoints[j].y * Berstein;
       }
   }
}
void setPoints(){
   glColor3f(250.5f, 0.f, 0.f);
   glPointSize(3.0f); // 设置点的大小
   glBegin(GL_POINTS);
   for(auto &it:lPoints){
       glVertex2i(it.x, it.y);
   }
   glEnd();
}
//绘制控制点形成的线段
void DrawLine1(){
   int n=lPoints.size();
   glColor3f(0.f, 250.5f, 0.4f);
   glLineWidth(3.0f);
   glBegin(GL_LINE_STRIP);
   for(int i=0;i<n;i++){
       int x=lPoints[i].x,y=lPoints[i].y;
       glVertex2i(x, y);
   }
   glEnd();
}
//绘制曲线
void DrawLine2(){
   int m=Pt.size();
   glColor3f(250.5f, 0.f, 0.f);
   glLineWidth(3.5f);
   glBegin(GL_LINE_STRIP);
   for(int i=0;i<m;i++){
       float x=Pt[i].x,y=Pt[i].y;
       glVertex2f(x, y);
   }
   glEnd();
}
void display(){
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   getCnk();
   Bezier();
   DrawLine1();
   DrawLine2();
   setPoints();
}
void dragMouse(int x,int y){
   if(flag=='1'){//绘制模式
       lPoints.back().x = x;
       lPoints.back().y = y;
   }
   if(flag=='2'|flag=='3'|flag=='4'){//修改或修改模式
       lPoints[index].x = x;
       lPoints[index].y = y;
   }
   display();
   glFlush();
}
// 鼠标监听，画点
void myMouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
       if(flag=='1'){//绘制模式
           lPoints.back().x = x;
           lPoints.back().y = y;
       }
       if(flag=='2'|flag=='3'){//修改或插点模式
           lPoints[index].x = x;
           lPoints[index].y = y;
       }
       if(flag=='4'){//删点模式
           int n = lPoints.size();
           if(n>0){
               for(int i=index;i<n-1;i++){
                   lPoints[i]=lPoints[i+1];
               }
               lPoints.resize(n-1);
           }
       }
       display();
       printf("%d %d\n", x,y); // 把两个坐标打印出来
       glFlush();
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       //获取鼠标位置
       int dis = INT_MAX;
       int n = lPoints.size();
       index = n - 1;
       for (int i = 0; i < n; i++) {
           int d = sqrt((x - lPoints[i].x) * (x - lPoints[i].x) + (y - lPoints[i].y) * (y - lPoints[i].y));
           if (dis > d) {
               dis = d;
               index = i;
           }
       }
       if(flag=='1'){//绘制模式
           lPoints.push_back({(float)x,(float)y});
       }
       if(flag=='3'){//插点模式
           int n = lPoints.size();
           lPoints.resize(n+1);
           for(int i=n;i>index;i--){
               lPoints[i]=lPoints[i-1];
           }
           lPoints[index].x = x;
           lPoints[index].y = y;
       }
   }
}
//键盘监听
void keyboard(unsigned char key, int a, int b){
   int n=lPoints.size();
   switch(key){
       case 27:
           exit(0);
       case '1'://绘制模式
           flag='1';
           break;
       case '2'://修改模式
           flag='2';
           break;
       case '3'://插点模式
           flag='3';
           break;
       case '4'://删点模式
           flag='4';
           break;
       case ' '://清空
           Pt.clear();
           lPoints.clear();//清空线条
           glClearColor(1, 1, 1, 1); // 设置绘制窗口颜色为白色
           glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
           glutPostRedisplay(); // 请求OpenGL重新绘制窗口
           glFlush();
           break;
   }
}
void init(int argc, char** argv){
   glutInit(&argc, argv); // 初始化

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置绘制模式
   glutInitWindowPosition(180, 50); // 设置窗口出现的位置
   glutInitWindowSize(width, height); // 设置窗口大小
   glutCreateWindow("PolygonScanLineFilled"); // 创建窗口

   glClearColor(1, 1, 1, 1); // 设置绘制窗口颜色为白色
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   glPointSize(3.0f); // 设置点的大小

   glMatrixMode(GL_PROJECTION); /* 设置为投影类型模式和其他观察参数 */
   glLoadIdentity(); /* 设置为投影类型模式和其他观察参数 */
   gluOrtho2D(0, width, height, 0);
}

int main(int argc, char** argv){
   init(argc, argv);
   glutDisplayFunc(setPoints);
   glutDisplayFunc(display);// 绘制回调函数,glut机制，它觉得需要重新绘制的时候就会执行
   glutMouseFunc(myMouse); // 键盘监听回调函数
   glutKeyboardFunc(keyboard);// 键盘监听回调函数
   glutMotionFunc(dragMouse); // 鼠标拖动
   glutMainLoop();
}