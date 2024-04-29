#include<iostream>
#include<string>
#include<string.h>
using namespace std;
#define n 100
#define Max_n 65535
typedef struct Vex
{
    string city;
    int num;
}Vex;
typedef struct graph
{
    double arc[n][n];
    Vex vex[n];
    int vexsnum,arcsnum;
}Graph;
/*�ҳ������ƶ�Ӧ�ı��*/
int Find(Graph &g,string ch)
{
    for(int i=0;i<g.vexsnum;i++)
    {
        if(ch==g.vex[i].city)
        {
            return i;
        }
    }
    cout<<"δ���ҵ���·��"<<endl;
    return -1;
}
/*1.��������·�����ڽӾ���*/
void Creat(Graph &g)
{
    cout<<"��ֱ��������������·������:";
    cin>>g.vexsnum>>g.arcsnum;
    for(int i=0;i<g.vexsnum;i++)//Ϊ�����б��
    {
        g.vex[i].num=i;
    }
    cout<<"����������"<<g.vexsnum<<"����������:"<<endl;
    for(int i=0;i<g.vexsnum;i++)
    {
        cin>>g.vex[i].city;
    }
    //��ʼ���ڽӾ���
    for(int i=0;i<g.vexsnum;i++)
    {
        for(int j=0;j<g.vexsnum;j++)
        {
            if(i==j)
            {
                g.arc[i][j]=0;
            }
            else
                g.arc[i][j]=Max_n;
        }
    }
    //��ӳ��м�·��
    cout<<"������"<<g.arcsnum<<"��·��������ʾ��"<<endl;
    cout<<"������ �յ���� ·��Ȩ��"<<endl;
    string start={0};string destination={0};
    int a,b;
    for(int i=0;i<g.arcsnum;i++)
    {
        cin>>start>>destination;
        a=Find(g,start);//a �����
        b=Find(g,destination);//b �յ���
        cin>>g.arc[a][b];//Ȩ��
        g.arc[b][a]=g.arc[a][b];
    }
    cout<<"������ɣ�"<<endl;
}
/*�˵�����*/
void menue()
{
    cout<<"*****************��ͨ��ѯϵͳ*****************"<<endl;
    cout<<"\t1.�������н�ͨ����ͼ\t"<<endl;
    cout<<"\t2.��ѯ���������м�����·��\t"<<endl;
    cout<<"\t3.��ѯ���ڳ��е��������е����·��\t"<<endl;
    cout<<"\t4.����µĳ���\t"<<endl;
    cout<<"\t5.��ʾ����ӳ��г�ʼ·��\t"<<endl;
    cout<<"\t6.�޸ĳ���·����Ϣ\t"<<endl; 
    cout<<"\t0.�˳�ϵͳ\t"<<endl;
    cout<<"*****************��ӭʹ��*********************"<<endl;
    cout<<"��ѡ������";
}
/*2.��ѯ���������м�����·��*/
void Floyd_path(Graph g)//���ø��������㷨�������������������·������
{
    string city1,city2;
    cout<<"������Ҫ��ѯ���������������Ʒֱ�Ϊ��";
    cin>>city1>>city2;
    int v0=Find(g,city1);
    int vf=Find(g,city2);
    for(int k=0;k<g.vexsnum;k++)
    {
        for(int i=0;i<g.vexsnum;i++)
        {
            for(int j=0;j<g.vexsnum;j++)
            {
                if(g.arc[i][j]>g.arc[i][k]+g.arc[k][j])
                {
                    g.arc[i][j]=g.arc[i][k]+g.arc[k][j];
                }
            }
        }
    }
    cout<<"��������֮������·�����£�"<<endl;
    cout<<"����"<<"\t";
    for(int i=0;i<g.vexsnum;i++)
    {
        cout<<g.vex[i].city<<"\t";
    }
    cout<<endl;
    for(int i=0;i<g.vexsnum;i++)
    {
        for(int j=0;j<g.vexsnum;j++)
        {
            if(j==0)
            {
                cout<<g.vex[i].city<<"\t";
            }
            cout<<g.arc[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"���s�����в�ѯ:";
    char c;cin>>c;
    cout<<city1<<"��"<<city2<<"�����·������Ϊ"<<g.arc[v0][vf]<<endl;
}
void track_path(Graph &g,int p[],int v0,int vf)
{
    if(v0==vf)
    {
        cout<<g.vex[p[vf]].city;
        return;
    }
    track_path(g,p,v0,p[vf]);
    cout<<"->"<<g.vex[p[vf]+1].city;
}
/*3.��ѯ���ڳ��е��������е����·��*/
void Dijkstra_path(Graph g)//���õϽ�˹�����㷨��Դ���·������
{
    string city1={0},city2={0};
    cout<<endl;
    cout<<"�����뵱ǰ�������ƺ�Ŀ�ĵس������ƣ�";
    cin>>city1>>city2;
    int D[n],P[n];//D[n]������Ÿ������·����Ȩֵ�ͣ�P[n]�����洢���·���±�
    int min,w;
    int v0=Find(g,city1);
    int vf=Find(g,city2);
    int final[n];
    //��ʼ������
    for(int v=0;v<g.vexsnum;v++)
    {
        final[v]=0;
        D[v]=g.arc[v0][v];
        if(g.arc[v0][v]==Max_n)
            P[v]=0;
        else
            P[v]=v0;
    }
    //v0��v0����Ҫ��·��
    final[v0]=1;
    //v0��v0·��Ϊ0
    D[v0]=0;
    //��ʼ��ѭ����ÿ�����v0��ĳ�����v�����·��
    for(int v=1;v<g.vexsnum;v++)
    {
        min=Max_n;
        //����v0��������Ķ���
        for(int w=0;w<g.vexsnum;w++)//��v��w
        {
            if(final[w]==0)
            {
                if(D[w]<min)
                {
                    v=w;
                    min=D[w];
                }
            }
        }
        final[v]=1;//��v0�����v����S��
        for(int w=0;w<g.vexsnum;w++)
        {
            if(!final[w]&&(g.arc[v][w]<Max_n)&&(min+g.arc[v][w]<D[w]))
            {   
                D[w]=min+g.arc[v][w];//����·����
                P[w]=v;
            }
        }
    }
    cout<<"���·������Ϊ��"<<D[vf]<<endl;
    track_path(g,P,v0,vf);
}
/*4.����µĳ���*/
void add_city(Graph &g)
{
    string city1;
    string city2;
    string city3;
    cout<<"������Ҫ����³��е����ƣ�"<<endl;
    cin>>city1;
    g.vex[g.vexsnum].city=city1;
    g.vexsnum++;
    cout<<"������Ҫ���·������"<<endl;
    int num;
    cin>>num;
    cout<<"������"<<num<<"��·��������ʾ��"<<endl;
    cout<<"������ �յ���� ·��Ȩ��"<<endl;
    int weight;
    for(int i=0;i<g.vexsnum;i++)
    {
        g.arc[i][g.vexsnum-1]=Max_n;
    }
    for(int i=0;i<num;i++)
    {
        cin>>city2>>city3>>weight;
        int v0=Find(g,city2);
        int vf=Find(g,city3);
        g.arc[v0][vf]=weight;
        g.arc[vf][v0]=g.arc[v0][vf];
    }
    cout<<"��ӳɹ���"<<endl;
}
/*5.��ʾ����ӳ��г�ʼ·��*/
void show_city(Graph g)
{
    cout<<"��������֮������·�����£�"<<endl;
    cout<<"����"<<"\t";
    for(int i=0;i<g.vexsnum;i++)
    {
        cout<<g.vex[i].city<<"\t";
    }
    cout<<endl;
    for(int i=0;i<g.vexsnum;i++)
    {
        for(int j=0;j<g.vexsnum;j++)
        {
            if(j==0)
            {
                cout<<g.vex[i].city<<"\t";
            }
            cout<<g.arc[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"ע�⣺"<<Max_n<<"���������м�û�г�ʼ·��"<<endl;
}
/*6.�޸ĳ���·����Ϣ*/
void modeify_city(Graph &g)
{
    int num;
    cout<<"�޸�·������Ϊ��";
    cin>>num;
    string city1,city2;
    int weight;
    cout<<"������"<<num<<"��Ҫ�޸ĵ�·��������ʾ��"<<endl;
    cout<<"������ �յ���� ·��Ȩ��"<<endl;
    for(int i=0;i<num;i++)
    {
        cin>>city1>>city2>>weight;
        int v0=Find(g,city1);
        int vf=Find(g,city2);
        g.arc[v0][vf]=weight;
        g.arc[vf][v0]=g.arc[v0][vf];
    }
    cout<<"�޸ĳɹ���"<<endl;
}
int main()
{
    Graph g;
    menue();
    int op;
    while(1)
    {
        cout<<"����������";
        cin>>op;
        switch(op)
        {
        case 1:Creat(g);break;
        case 2:Floyd_path(g);break;
        case 3:Dijkstra_path(g);break;
        case 4:add_city(g);break;
        case 5:show_city(g);break;
        case 6:modeify_city(g);break;
        case 0:cout<<"�ѳɹ��˳�ϵͳ����ӭ�´�ʹ�ã�"<<endl;system("pause");return 0;
        default: cout<<"�������,������"<<endl;break;
        }
    }
    system("pause");
    return 0;
}