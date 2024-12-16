#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
const int width = 960, height = 600; // 窗口画幅大小
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
int XL = 0, XR = 0, YB = 0, YT = 0;//裁剪窗口的边界
struct node{
   int x,y;
};
vector<node>wPoints(2); //记录窗口的对角点，用以绘制裁剪窗口
vector<node>lPoints;       //记录线段的两端点，用以绘制线段
char flag='1';              //模式标志位
int index=0;                //修改端点在数组中的索引
void update_XL_XR_YB_YT(){
   XL=min(wPoints[0].x,wPoints[1].x);
   XR=max(wPoints[0].x,wPoints[1].x);
   YB=min(wPoints[0].y,wPoints[1].y);
   YT=max(wPoints[0].y,wPoints[1].y);
}
void DrawWindow(){
   update_XL_XR_YB_YT();//更新边界参数
   glColor3f(0.8, 0, 250.8); // 点颜色
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   glLineWidth(3.f);
   glBegin(GL_LINES);
   //底
   glVertex2i(XL, YB);
   glVertex2i(XR, YB);
   //顶
   glVertex2i(XL, YT);
   glVertex2i(XR, YT);
   //左
   glVertex2i(XL, YB);
   glVertex2i(XL, YT);
   //右
   glVertex2i(XR, YB);
   glVertex2i(XR, YT);
   glEnd();
}
void setPoints(){
   glColor3f(255.f, 0.f, 0.f);
   glPointSize(3.0f); // 设置点的大小
   glBegin(GL_POINTS);
   for(auto &it:lPoints){
       glVertex2i(it.x, it.y);
   }
   glEnd();
}
void DrawLine1(int x0,int y0,int x1,int y1){
   glColor3f(0.f, 250.5f, 0.5f);
   glBegin(GL_LINE_STRIP);
   glVertex2i(x0, y0);
   glVertex2i(x1, y1);
   glEnd();
}
void DrawLine2(float x0,float y0,float x1,float y1){
   glColor3f(255.f, 0.f, 0.f);
   glBegin(GL_LINE_STRIP);
   glVertex2f(x0, y0);
   glVertex2f(x1, y1);
   glFlush();
   glEnd();

}

int ClipT(float p, float q,float *u1,float *u2){
   float r=0;
   if(p<0){
       r=q/p;
       if(r>(*u2))
           return false;
       if(r>(*u1))
           (*u1)=r;
   }
   else if(p>0){
       r=q/p;
       if(r<(*u1))
           return false;
       if(r<(*u2))
           (*u2)=r;
   }
   else return(q>=0);
   return true;
}
//并没有实现一个自由裁剪的功能
void LB_LineClip(float x1, float y1,float x2,  float y2){
   float dx,dy,u1,u2;
   dx=x2-x1;
   dy=y2-y1;
   u1=0,u2=1;
   if(ClipT(-dx,x1-XL,&u1,&u2))
       if(ClipT(dx,XR-x1,&u1,&u2))
           if(ClipT(-dy,y1-YB,&u1,&u2))
               if(ClipT(dy,YT-y1,&u1,&u2)) {
                   DrawLine2(x1 + u1 * dx, y1 + u1 * dy, x1 + u2 * dx, y1 + u2 * dy);
               }
}
void display(){
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   DrawWindow();
   int n=lPoints.size();
   if(n>=2&&n%2==0){
       int i=1;
       while(i<n){
           int x1=lPoints[i-1].x,y1=lPoints[i-1].y,x2=lPoints[i].x,y2=lPoints[i].y;
           DrawLine1(x1,y1,x2,y2);
           LB_LineClip(x1, y1, x2, y2);
           i+=2;
       }
   }
   else if(n>=2&&n%2!=0) {
       int i=1;
       while(i<n-1){
           int x1=lPoints[i-1].x,y1=lPoints[i-1].y,x2=lPoints[i].x,y2=lPoints[i].y;
           DrawLine1(x1,y1,x2,y2);
           LB_LineClip(x1, y1, x2, y2);
           i+=2;
       }
   }
   setPoints();
   glFlush();
}
void dragMouse(int x,int y){
   if(flag=='1'){//绘制窗口模式
       wPoints[1].x = x;
       wPoints[1].y = y;
       DrawWindow();
   }
   if(flag=='2'){//绘制直线模式
       lPoints.back().x=x;
       lPoints.back().y=y;
       setPoints();
       display();
   }
   if(flag=='3'|flag=='5'){//修改直线模式
       lPoints[index].x=x;
       lPoints[index].y=y;
       setPoints();
       display();
   }
   glFlush();
}
// 鼠标监听，画点
void myMouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
       int n = lPoints.size();
       if(flag=='1'){//绘制窗口模式
           wPoints[1].x = x;
           wPoints[1].y = y;
           DrawWindow();
       }
       if(flag=='2'){//绘制直线模式
           lPoints.back().x=x;
           lPoints.back().y=y;
           setPoints();
           display();
       }
       if(flag=='3'){//修改直线模式
           lPoints[index].x=x;
           lPoints[index].y=y;
           setPoints();
           display();
       }
       if(flag=='5'){//删除直线模式
           if(index%2==0){
               if(n>2){
                   for(int i=index;i<n-2;i++){
                       lPoints[i]=lPoints[i+2];
                   }
                   lPoints.resize(n-2);
               }
               else{
                   lPoints.clear();
               }
           }
           else{
               if(n>2){
                   for(int i=index-1;i<n-2;i++){
                       lPoints[i]=lPoints[i+2];
                   }
                   lPoints.resize(n-2);
               }
               else{
                   lPoints.clear();
               }
           }
           setPoints();
           display();
       }
       printf("%d %d\n", x,y); // 把两个坐标打印出来
       glFlush();
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       if(flag=='1'){//绘制窗口模式
           wPoints[0].x=x;
           wPoints[0].y=y;
       }
       if(flag=='2') {//绘制直线模式
           lPoints.push_back({x, y});
           setPoints();
           display();
           lPoints.resize(lPoints.size() + 1);
       }
       if(flag=='3'|flag=='4'|flag=='5') {//修改直线模式
           int dis = INT_MAX;
           int n = lPoints.size();
           index = 0;
           for (int i = 0; i < n; i++) {
               int d = sqrt((x - lPoints[i].x) * (x - lPoints[i].x) + (y - lPoints[i].y) * (y - lPoints[i].y));
               if (dis > d) {
                   dis = d;
                   index = i;
               }
           }
           setPoints();
           display();
       }
       printf("%d %d\n", x,y); // 把两个坐标打印出来
       glFlush();
   }
   if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
       flag= flag=='1'?'2':'1';
       glFlush();
   }
}
//键盘监听
void keyboard(unsigned char key, int a, int b){
   int n=lPoints.size();
   switch(key){
       case 27:
           exit(0);
       case ' ':
           lPoints.clear();//清空线条
           display();
           break;
       case '1':
           flag='1';
           break;
       case '2':
           flag='2';
           break;
       case '3':
           flag='3';
           break;
       case '4':
           flag='4';
           break;
       case '5':
           flag='5';
           break;
       case 'a':
           if(flag=='4') {
               if (n >= 2) {
                   if (index % 2 == 0) {
                       lPoints[index].x -= 10;
                       lPoints[index + 1].x -= 10;
                   } else {
                       lPoints[index].x -= 10;
                       lPoints[index - 1].x -= 10;
                   }
               }
               display();
           }
           break;
       case 'w':
           if(flag=='4') {
               if (n >= 2) {
                   if (index % 2 == 0) {
                       lPoints[index].y -= 10;
                       lPoints[index + 1].y -= 10;
                   } else {
                       lPoints[index].y -= 10;
                       lPoints[index - 1].y -= 10;
                   }
               }
               display();
           }
           break;
       case 'd':
           if(flag=='4') {
               if (n >= 2) {
                   if (index % 2 == 0) {
                       lPoints[index].x += 10;
                       lPoints[index + 1].x += 10;
                   } else {
                       lPoints[index].x += 10;
                       lPoints[index - 1].x += 10;
                   }
               }
               display();
           }
           break;
       case 's':
           if(flag=='4') {
               if (n >= 2) {
                   if (index % 2 == 0) {
                       lPoints[index].y += 10;
                       lPoints[index + 1].y += 10;
                   } else {
                       lPoints[index].y += 10;
                       lPoints[index - 1].y += 10;
                   }
               }
               display();
           }
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
   glutDisplayFunc(display);
   glutDisplayFunc(DrawWindow); // 绘制回调函数,glut机制，它觉得需要重新绘制的时候就会执行
   glutMouseFunc(myMouse); // 键盘监听回调函数
   glutKeyboardFunc(keyboard);// 键盘监听回调函数
   glutMotionFunc(dragMouse); // 鼠标拖动
   glutMainLoop();
}