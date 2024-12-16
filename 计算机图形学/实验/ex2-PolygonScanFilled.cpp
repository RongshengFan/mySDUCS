#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
int width = 960, height = 600; // 窗口画幅大小
int preX = 0, preY = 0, curX = 0, curY = 0; // 起始与终点位置
//边表
typedef struct ET{
   float x;
   float dx;
   float yMax;
   ET* next;
}pAET,pNET;
//点表
struct node{
   int x,y;
};
vector<node>points;//点集
void setPoints(){
   glColor3f(255.f, 0.f, 0.f);
   glPointSize(3.0f); // 设置点的大小
   glBegin(GL_POINTS);
   for(auto &it:points){
       glVertex2i(it.x, it.y);
   }
   glEnd();
}
void drawLine(){
   glClear(GL_COLOR_BUFFER_BIT); // 清除窗口内容
   int n=points.size();
   if(n>=2){
       glColor3f(255.f, 0.f, 0.f);
       glLineWidth(3.f);
       glBegin(GL_LINES);
       for (int i = 0; i < n; i++) {
           int x1=points[i%n].x, y1=points[i%n].y, x2=points[(i + 1)%n].x, y2=points[(i + 1)%n].y;
           glVertex2f(x1, y1);
           glVertex2f(x2, y2);
       }
   }
   glEnd();
   glFlush();
}
void PolygonScan(){
   //找出maxY
   int maxY=0;
   int size=points.size();
   for(int i=0;i<size;i++){
       maxY=max(points[i].y,maxY);
   }

   //AET表
   pAET *AET=new pAET;
   AET->next=NULL;
   //NET表
   pNET *NET[maxY+1];
   for(int i=0;i<=maxY;i++){
       NET[i]=new pNET;
       NET[i]->next=NULL;
   }
   //glClear(GL_COLOR_BUFFER_BIT);        //赋值的窗口显示.
   glColor3f(0.f,250.5f,0.5f); //设置直线的颜色
   glBegin(GL_POINTS); //画点

   for(int i=0;i<=maxY;i++){
       for(int j=0;j<size;j++){
           if(points[j].y==i){
               int left= (j - 1 + size) % size;//前一个点
               int right = (j + 1 + size) % size;//后一个点
               if(points[left].y > points[j].y){
                   pNET *p=new pNET;
                   p->x=(float)points[j].x;
                   p->yMax=(float)points[left].y;
                   p->dx=(float)(points[left].x-points[j].x)/(float)(points[left].y-points[j].y);
                   p->next=NET[i]->next;
                   NET[i]->next=p;
               }
               if(points[right].y>points[j].y){
                   pNET *p=new pNET;
                   p->x=(float)points[j].x;
                   p->yMax=(float)points[right].y;
                   p->dx=(float)(points[right].x-points[j].x)/(float)(points[right].y-points[j].y);
                   p->next=NET[i]->next;
                   NET[i]->next=p;
               }
           }
       }
   }
   for(int i=0;i<=maxY;i++){
       pAET *p=AET->next;
       //更新活边新交点
       while(p){
           p->x+=p->dx;
           p=p->next;
       }
       //对AET按照x递增顺序排序
       pAET *tq=AET;
       p=AET->next;
       tq->next=NULL;
       while(p)
       {
           while(tq->next && p->x >= tq->next->x)
               tq=tq->next;
           pNET *t=p->next;
           p->next=tq->next;
           tq->next=p;
           p=t;
           tq=AET;
       }
       //删去AET中yMax=i的节点
       pAET *q=AET;
       p=q->next;
       while(p){
           if(p->yMax==i){
               q->next=p->next;
               delete p;
               p=q->next;
           }
           else {
               p=p->next;
               q=q->next;
           }
       }
       //使用插入排序法将NET[i]的边节点插入AET
       p=NET[i]->next;
       q=AET;
       while(p){
           while(q->next && p->x >= q->next->x)q=q->next;
           pNET *t=p->next;
           p->next=q->next;
           q->next=p;
           p=t;
           q=AET;
       }
       //把配对交点区间上的像素改写，即画点填充
       p=AET->next;
       while(p&&p->next){
           for(float j=p->x; j<=p->next->x; j++)
               glVertex2i(static_cast<int>(j),i);
           p=p->next->next;//考虑端点情况
       }
   }
   glEnd();
   glFlush();
}
void display(){
   PolygonScan();
}
void dragMouse(int x,int y){
   points.back().x=x;
   points.back().y=y;
   drawLine();
   glFlush();
}
// 鼠标监听，画点
void myMouse(int button, int state, int x, int y) {
   if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
       points.back().x=x;
       points.back().y=y;
       drawLine();

       printf("%d %d\n", x,y); // 把两个坐标打印出来
       glFlush();
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       points.push_back({x,y});//压点入集
       printf("%d %d\n", x,y); // 把两个坐标打印出来
       setPoints();//画点
       glFlush();
   }
   if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
       display();
       points.clear();
       glFlush();
   }
}
void keyboard(unsigned char key, int a, int b){
   switch(key){
       case ' ':
           points.clear();
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
   glPointSize(1.0f); // 设置点的大小

   glMatrixMode(GL_PROJECTION); /* 设置为投影类型模式和其他观察参数 */
   glLoadIdentity(); /* 设置为投影类型模式和其他观察参数 */
   gluOrtho2D(0, width, height, 0);
}

int main(int argc, char** argv){
   init(argc, argv);
   glutDisplayFunc( setPoints);// 绘制回调函数,glut机制，它觉得需要重新绘制的时候就会执行
   glutMouseFunc(myMouse); // 键盘监听回调函数
   glutKeyboardFunc(keyboard);// 键盘监听回调函数
   glutMotionFunc(dragMouse); // 鼠标拖动
   glutMainLoop();
}