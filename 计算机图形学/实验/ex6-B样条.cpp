#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
const int width = 960, height = 600; // 窗口画幅大小
struct vertex{
   float x,y;
};
vector<vertex>lPoints;        //记录线段的两端点，用以绘制线段
vector<vertex>Pt;             //记录曲线上的点
char flag='w';                //模式标志位
int index=0;                  //修改端点在数组中的索引
int k=3;                      //B样条阶数，初始设为3阶
//De Boor递推算法实现
void DeBoor(){
   int n=lPoints.size();   //控制点的个数
   Pt.clear();             //清理曲线点数组
   Pt.resize(0);   //重设Pt数组大小
   double t[n+k];        //参数
   vertex Pri[n][n];       //存递推各项的值
   for(int i=0;i<=k-1;i++){
       t[i] = 0;
   }
   for(int i=k;i<n;i++){
       t[i]=t[i-1]+1.0/(n-k+1);
   }
   for(int i=n;i<n+k;i++){
       t[i]=1;
   }
   for(int j=k-1;j<n;j++) {
       for(double T=t[j];T<=t[j+1];T+=0.001/n){
           for(int i=j-k+1;i<=j;i++){
               Pri[0][i].x=lPoints[i].x;
               Pri[0][i].y=lPoints[i].y;
           }
           for (int r = 1; r <= k-1; r++) {
               for(int  i =j-k+r+1 ;i <= j; i++){
                   double a=T-t[i],b=t[i+k-r]-t[i],c=t[i+k-r]-T;
                   double U = b!=0 ? a / b:0, V =  b!=0 ? c / b:0;
                   Pri[r][i].x=U*Pri[r-1][i].x+V*Pri[r-1][i-1].x;
                   Pri[r][i].y=U*Pri[r-1][i].y+V*Pri[r-1][i-1].y;
               }
           }
           Pt.push_back({Pri[k-1][j].x,Pri[k-1][j].y});
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
   DeBoor();
   DrawLine1();
   DrawLine2();
   setPoints();
   glFlush();
}
void dragMouse(int x,int y){
   if(flag=='w'){//绘制模式
       lPoints.back().x = x;
       lPoints.back().y = y;
   }
   if(flag=='s'|flag=='a'|flag=='d'){//修改或修改模式
       lPoints[index].x = x;
       lPoints[index].y = y;
   }
   display();
   glFlush();
}
// 鼠标监听，画点
void myMouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
       if(flag=='w'){//绘制模式
           lPoints.back().x = x;
           lPoints.back().y = y;
       }
       if(flag=='s'|flag=='a'){//修改或修改模式
           lPoints[index].x = x;
           lPoints[index].y = y;
       }
       if(flag=='d'){//删点模式
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
       if(flag=='w'){//绘制模式
           lPoints.push_back({(float)x,(float)y});
       }
       if(flag=='a'){//插点模式
           int n = lPoints.size();
           lPoints.resize(n+1);
           for(int i=n;i>index;i--){
               lPoints[i]=lPoints[i-1];
           }
           lPoints[index].x = x;
           lPoints[index].y = y;
       }
       setPoints();
       printf("%d %d\n", x,y); // 把两个坐标打印出来
       glFlush();
   }
}
//键盘监听
void keyboard(unsigned char key, int a, int b){
   int n=lPoints.size();
   switch(key){
       case 27:
           exit(0);
       case '2':
           k=2;
           printf("k=%d\n",k);
           break;
       case '3':
           k=3;
           printf("k=%d\n",k);
           break;
       case '4':
           k=4;
           printf("k=%d\n",k);
           break;
       case '5':
           k=5;
           printf("k=%d\n",k);
           break;
       case '6':
           k=6;
           printf("k=%d\n",k);
           break;
       case '7':
           k=7;
           printf("k=%d\n",k);
           break;
       case '8':
           k=8;
           printf("k=%d\n",k);
           break;
       case '9':
           k=9;
           printf("k=%d\n",k);
           break;
       case 'e'://升阶
           if(k<n+1)k++;
           printf("k=%d\n",k);
           break;
       case 'q'://降阶
           if(k>1)k--;
           printf("k=%d\n",k);
           break;
       case 'w'://绘制模式
           flag='w';
           printf("绘制模式\n");
           break;
       case 's'://修改模式
           flag='s';
           printf("修改模式\n");
           break;
       case 'a'://插点模式
           flag='a';
           printf("插点模式\n");
           break;
       case 'd'://删点模式
           flag='d';
           printf("删点模式\n");
           break;
       case ' '://清空
           Pt.clear();
           lPoints.clear();//清空线条
           break;
   }
   display();
   glFlush();
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