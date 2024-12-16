#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
const int width = 960, height = 600; // ���ڻ�����С
int XL = 0, XR = 0, YB = 0, YT = 0;  //�ü����ڵı߽�
struct node {
   int x,y;
};
struct edge//Edge��
{
   int bx, by, ex, ey;
}LEFT,RIGHT,BOTTOM,TOP;      //�������������߽�
vector<node>wPoints(2);   //��¼���ڵĶԽǵ㣬���Ի��Ʋü�����
vector<node>lPoints;         //��¼�������Ķ��㣬���ڻ��Ƴ�ʼͼ��
vector<node>inPoints;        //��¼����Ķ��㣬���ڸ��£�ÿ�μ���outPoints
vector<node>outPoints;       //��¼����Ķ��㣬���ڻ��Ʋü����ͼ��
bool displayFlag=false;      //չʾ��־λ
char flag='1';               //ģʽ��־λ
int index=0;                 //�޸Ķ˵��������е�����
//���²ü����ڱ߽�
void update_XL_XR_YB_YT(){
   XL=min(wPoints[0].x,wPoints[1].x);
   XR=max(wPoints[0].x,wPoints[1].x);
   YB=min(wPoints[0].y,wPoints[1].y);
   YT=max(wPoints[0].y,wPoints[1].y);
   //˳ʱ������
   LEFT={XL, YT, XL, YB};
   BOTTOM={XL, YB, XR, YB};
   RIGHT={XR, YB, XR,YT };
   TOP={XR, YT, XL, YT};
}
//���Ʋü�����
void DrawWindow(){
   update_XL_XR_YB_YT();//���±߽����
   glClear(GL_COLOR_BUFFER_BIT); // �����������
   glColor3f(0.8, 0, 250.8); // ����ɫ
   glLineWidth(3.f);
   glBegin(GL_LINES);
   //��
   glVertex2i(XL, YB);
   glVertex2i(XR, YB);
   //��
   glVertex2i(XL, YT);
   glVertex2i(XR, YT);
   //��
   glVertex2i(XL, YB);
   glVertex2i(XL, YT);
   //��
   glVertex2i(XR, YB);
   glVertex2i(XR, YT);
   glEnd();
}
//�жϵ��Ƿ�ɼ�
bool inside(node& pt, edge ClipBoundary){
   if (ClipBoundary.ex > ClipBoundary.bx)
   {
       if (pt.y >= ClipBoundary.by)//�ü���Ϊ�����±���
           return true;
   }
   else if (ClipBoundary.ex < ClipBoundary.bx)
   {
       if (pt.y <= ClipBoundary.by)//�ü���Ϊ�����ϱ���
           return true;
   }
   else if (ClipBoundary.ey > ClipBoundary.by)//�ü���Ϊ�����ұ���
   {
       if (pt.x <= ClipBoundary.bx)
           return true;
   }
   else if (ClipBoundary.ey < ClipBoundary.by)//�ü���Ϊ���������
   {
       if (pt.x >= ClipBoundary.bx)
           return true;
   }
   return false;
}
//ֱ�߶�SP�ͱ߽��󽻣����ؽ���
void intersect(node& s, node& p, edge ClipBoundary, node& intersectPt){
   if (ClipBoundary.by == ClipBoundary.ey)//ˮƽ�ü��߽�
   {
       intersectPt.y = ClipBoundary.by;
       //x=���ĺ�����+dy/spб��
       intersectPt.x = s.x + (ClipBoundary.by - s.y) * (p.x - s.x) / (p.y - s.y);
   }
   else//��ֱ�ü��߽�
   {
       intersectPt.x = ClipBoundary.bx;
       intersectPt.y = s.y + (ClipBoundary.bx - s.x) * (p.y - s.y) / (p.x - s.x);
   }
}
void SutherlandHodgmanClip(edge ClipBoundary)
{
   node s, p, ip;
   outPoints.clear();
   int n=inPoints.size();
   s = inPoints[n- 1];//��β

   for (int j = 0; j < n; j++)
   {
       p = inPoints[j];
       if (inside(p, ClipBoundary))//p����
       {
           if (inside(s, ClipBoundary))//sp���ڴ�����
           {
               outPoints.push_back(p);
           }
           else//p������ s����
           {
               intersect(s, p, ClipBoundary, ip);
               outPoints.push_back(ip);
               outPoints.push_back(p);

           }
       }
       else//p������
       {
           if (inside(s, ClipBoundary))//s�ڴ�����p�ڴ�����
           {
               intersect(s, p, ClipBoundary, ip);
               outPoints.push_back(ip);
           }
           //sp���������������
       }
       s = p;
   }
   inPoints = outPoints;//��ε������Ϊ��һ�ε����룬input_vertice��output_vertice��ȫ�ֱ���
}

//����ԭʼͼ�α���
void DrawLine1(){
   int n=lPoints.size();
   if(n>=2){
       glColor3f(0.f, 250.5f, 0.4f);
       glLineWidth(3.0f);
       glBegin(GL_LINE_STRIP);
       for(int i=0;i<=n;i++){
           int x=lPoints[i%n].x,y=lPoints[i%n].y;
           glVertex2i(x, y);
       }
       glEnd();
   }
}
//���Ʊ��ü�ͼ�α���
void DrawLine2(){
   int n=outPoints.size();
   if(n>=2){
       glColor3f(255.f, 0.f, 0.f);
       glLineWidth(3.5f);
       glBegin(GL_LINE_STRIP);
       for(int i=0;i<=n;i++){
           int x=outPoints[i%n].x,y=outPoints[i%n].y;
           glVertex2i(x, y);
       }
       glEnd();
   }
}
void setPoints(){
   glColor3f(255.f, 0.f, 0.f);
   glPointSize(3.0f); // ���õ�Ĵ�С
   glBegin(GL_POINTS);
   for(auto &it:lPoints){
       glVertex2i(it.x, it.y);
   }
   glEnd();
}
void display(){
   //�������£�˳ʱ������
   SutherlandHodgmanClip(LEFT);
   SutherlandHodgmanClip(BOTTOM);
   SutherlandHodgmanClip(RIGHT);
   SutherlandHodgmanClip(TOP);
   DrawLine2();
}
void dragMouse(int x,int y){
   if(flag=='1'){//���ƴ���ģʽ
       wPoints[1].x = x;
       wPoints[1].y = y;
       DrawWindow();
   }
   if(flag=='3'|flag=='4'){//�޸Ļ���ɾ��ģʽ
       if(lPoints.size()>0){
           lPoints[index].x=x;
           lPoints[index].y=y;
           inPoints=lPoints;
           DrawWindow();
           DrawLine1();
           display();
       }
   }
   if(flag=='2'){//���ƶ��������ģʽ
       lPoints.back().x=x;
       lPoints.back().y=y;
       inPoints=lPoints;
       DrawWindow();
       DrawLine1();
       display();
   }
   glFlush();
}
// ������������
void myMouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
       if(flag=='1'){//���ƴ���
           wPoints[1].x=x;
           wPoints[1].y=y;
           DrawWindow();
       }
       if(flag=='2'){//����ͼ��
           lPoints.back().x=x;
           lPoints.back().y=y;
           inPoints=lPoints;
           DrawLine1();
           display();
       }
       if(flag=='3'){//�޸�ģʽ
           if(lPoints.size()>0) {
               lPoints[index].x = x;
               lPoints[index].y = y;
               inPoints = lPoints;
               DrawWindow();
               DrawLine1();
               display();
           }
       }
       if(flag=='4'){//ɾ��ģʽ
           int n=lPoints.size();
           if(n > 1){
               for(int i=index;i<n-1;i++){
                   lPoints[i]=lPoints[i+1];
               }
               lPoints.resize(n-1);
               inPoints=lPoints;
               DrawWindow();
               DrawLine1();
               display();
           }
           else{
               lPoints.clear();
               inPoints.clear();
               DrawWindow();
           }
       }
       setPoints();
       printf("%d %d\n", x,y); // �����������ӡ����
       glFlush();
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       int dis=INT_MAX;
       int n=lPoints.size();
       index=n-1;
       for(int i=0;i<n;i++){
           int d=sqrt((x-lPoints[i].x)*(x-lPoints[i].x)+(y-lPoints[i].y)*(y-lPoints[i].y));
           if(dis>d){
               dis=d;
               index=i;
           }
       }
       if(flag=='1'){//���ƴ���
           wPoints[0].x=x;
           wPoints[0].y=y;
       }
       if(flag=='2'){//����ͼ��
           lPoints.push_back({x, y});
           inPoints=lPoints;
       }
       printf("%d %d\n", x,y); // �����������ӡ����
       glFlush();
   }
   if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){//���ƴ��ڱ�־λת��
       displayFlag=!displayFlag;
       if(flag!='1'){
           if(!displayFlag){
               DrawWindow();
               inPoints=lPoints;
               display();
           }
           else {
               DrawLine1();
           }
       }
       glFlush();
   }
}
//���̼���
void keyboard(unsigned char key, int a, int b){
   int n=inPoints.size();
   switch(key) {
       case 27:
           exit(0);
       case ' '://��ճ��ü���������������
           lPoints.clear();  //�������
           inPoints.clear(); //�������
           outPoints.clear();//�������
           DrawWindow();     //�����Ļ���»��Ʋü�����
           glFlush();
           break;
       case '1'://���ƴ���ģʽ
           flag = '1';
           break;
       case '2'://����ͼ��ģʽ
           flag = '2';
           break;
       case '3'://�޸�ģʽ
           flag = '3';
           break;
       case '4'://ɾ��ģʽ
           flag = '4';
           break;
   }
}
void init(int argc, char** argv){
   glutInit(&argc, argv); // ��ʼ��

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ���û���ģʽ
   glutInitWindowPosition(180, 50); // ���ô��ڳ��ֵ�λ��
   glutInitWindowSize(width, height); // ���ô��ڴ�С
   glutCreateWindow("PolygonClip"); // ��������

   glClearColor(1, 1, 1, 1); // ���û��ƴ�����ɫΪ��ɫ
   glClear(GL_COLOR_BUFFER_BIT); // �����������
   glPointSize(3.0f); // ���õ�Ĵ�С

   glMatrixMode(GL_PROJECTION); /* ����ΪͶӰ����ģʽ�������۲���� */
   glLoadIdentity(); /* ����ΪͶӰ����ģʽ�������۲���� */
   gluOrtho2D(0, width, height, 0);
}

int main(int argc, char** argv){
   init(argc, argv);

   glutDisplayFunc(display);
   glutDisplayFunc(setPoints);
   glutDisplayFunc(DrawLine1);
   glutDisplayFunc(DrawWindow); // ���ƻص�����,glut���ƣ���������Ҫ���»��Ƶ�ʱ��ͻ�ִ��
   glutMouseFunc(myMouse); // ���̼����ص�����
   glutKeyboardFunc(keyboard);// ���̼����ص�����
   glutMotionFunc(dragMouse); // ����϶�
   glutMainLoop();
}