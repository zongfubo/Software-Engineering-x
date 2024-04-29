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
/*找城市名称对应的编号*/
int Find(Graph &g,string ch)
{
    for(int i=0;i<g.vexsnum;i++)
    {
        if(ch==g.vex[i].city)
        {
            return i;
        }
    }
    cout<<"未查找到该路径"<<endl;
    return -1;
}
/*1.创建城市路径的邻接矩阵*/
void Creat(Graph &g)
{
    cout<<"请分别输入城市总数和路线总数:";
    cin>>g.vexsnum>>g.arcsnum;
    for(int i=0;i<g.vexsnum;i++)//为结点城市编号
    {
        g.vex[i].num=i;
    }
    cout<<"请依次输入"<<g.vexsnum<<"个城市名称:"<<endl;
    for(int i=0;i<g.vexsnum;i++)
    {
        cin>>g.vex[i].city;
    }
    //初始化邻接矩阵
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
    //添加城市间路径
    cout<<"请输入"<<g.arcsnum<<"条路径如下所示："<<endl;
    cout<<"起点城市 终点城市 路径权重"<<endl;
    string start={0};string destination={0};
    int a,b;
    for(int i=0;i<g.arcsnum;i++)
    {
        cin>>start>>destination;
        a=Find(g,start);//a 起点编号
        b=Find(g,destination);//b 终点编号
        cin>>g.arc[a][b];//权重
        g.arc[b][a]=g.arc[a][b];
    }
    cout<<"创建完成！"<<endl;
}
/*菜单界面*/
void menue()
{
    cout<<"*****************交通咨询系统*****************"<<endl;
    cout<<"\t1.创建城市交通网络图\t"<<endl;
    cout<<"\t2.查询任意两城市间的最短路径\t"<<endl;
    cout<<"\t3.查询所在城市到其它城市的最短路径\t"<<endl;
    cout<<"\t4.添加新的城市\t"<<endl;
    cout<<"\t5.显示已添加城市初始路径\t"<<endl;
    cout<<"\t6.修改城市路线信息\t"<<endl; 
    cout<<"\t0.退出系统\t"<<endl;
    cout<<"*****************欢迎使用*********************"<<endl;
    cout<<"请选择操作项：";
}
/*2.查询任意两城市间的最短路径*/
void Floyd_path(Graph g)//利用弗洛伊德算法求任意两个顶点间的最短路径问题
{
    string city1,city2;
    cout<<"请输入要查询的任意两城市名称分别为：";
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
    cout<<"各个城市之间的最短路径如下："<<endl;
    cout<<"城市"<<"\t";
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
    cout<<"点击s键进行查询:";
    char c;cin>>c;
    cout<<city1<<"到"<<city2<<"的最短路径长度为"<<g.arc[v0][vf]<<endl;
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
/*3.查询所在城市到其他城市的最短路径*/
void Dijkstra_path(Graph g)//利用迪杰斯特拉算法求单源最短路径问题
{
    string city1={0},city2={0};
    cout<<endl;
    cout<<"请输入当前城市名称和目的地城市名称：";
    cin>>city1>>city2;
    int D[n],P[n];//D[n]用来存放各点最短路径的权值和，P[n]用来存储最短路径下标
    int min,w;
    int v0=Find(g,city1);
    int vf=Find(g,city2);
    int final[n];
    //初始化数据
    for(int v=0;v<g.vexsnum;v++)
    {
        final[v]=0;
        D[v]=g.arc[v0][v];
        if(g.arc[v0][v]==Max_n)
            P[v]=0;
        else
            P[v]=v0;
    }
    //v0到v0不需要求路径
    final[v0]=1;
    //v0到v0路径为0
    D[v0]=0;
    //开始主循环，每次求得v0到某个结点v的最短路径
    for(int v=1;v<g.vexsnum;v++)
    {
        min=Max_n;
        //找离v0顶点最近的顶点
        for(int w=0;w<g.vexsnum;w++)//从v到w
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
        final[v]=1;//离v0最近的v加入S集
        for(int w=0;w<g.vexsnum;w++)
        {
            if(!final[w]&&(g.arc[v][w]<Max_n)&&(min+g.arc[v][w]<D[w]))
            {   
                D[w]=min+g.arc[v][w];//更新路径和
                P[w]=v;
            }
        }
    }
    cout<<"最短路径长度为："<<D[vf]<<endl;
    track_path(g,P,v0,vf);
}
/*4.添加新的城市*/
void add_city(Graph &g)
{
    string city1;
    string city2;
    string city3;
    cout<<"请输入要添加新城市的名称："<<endl;
    cin>>city1;
    g.vex[g.vexsnum].city=city1;
    g.vexsnum++;
    cout<<"请输入要添加路径数："<<endl;
    int num;
    cin>>num;
    cout<<"请输入"<<num<<"条路径如下所示："<<endl;
    cout<<"起点城市 终点城市 路径权重"<<endl;
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
    cout<<"添加成功！"<<endl;
}
/*5.显示已添加城市初始路径*/
void show_city(Graph g)
{
    cout<<"各个城市之间的最短路径如下："<<endl;
    cout<<"城市"<<"\t";
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
    cout<<"注意："<<Max_n<<"代表两城市间没有初始路径"<<endl;
}
/*6.修改城市路线信息*/
void modeify_city(Graph &g)
{
    int num;
    cout<<"修改路径条数为：";
    cin>>num;
    string city1,city2;
    int weight;
    cout<<"请输入"<<num<<"条要修改的路径如下所示："<<endl;
    cout<<"起点城市 终点城市 路径权重"<<endl;
    for(int i=0;i<num;i++)
    {
        cin>>city1>>city2>>weight;
        int v0=Find(g,city1);
        int vf=Find(g,city2);
        g.arc[v0][vf]=weight;
        g.arc[vf][v0]=g.arc[v0][vf];
    }
    cout<<"修改成功！"<<endl;
}
int main()
{
    Graph g;
    menue();
    int op;
    while(1)
    {
        cout<<"请输入操作项：";
        cin>>op;
        switch(op)
        {
        case 1:Creat(g);break;
        case 2:Floyd_path(g);break;
        case 3:Dijkstra_path(g);break;
        case 4:add_city(g);break;
        case 5:show_city(g);break;
        case 6:modeify_city(g);break;
        case 0:cout<<"已成功退出系统，欢迎下次使用！"<<endl;system("pause");return 0;
        default: cout<<"输入错误,请重试"<<endl;break;
        }
    }
    system("pause");
    return 0;
}