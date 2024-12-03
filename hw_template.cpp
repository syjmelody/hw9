#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status; /* 函数结果状态代码,如OK等 */
#define INFINITY INT_MAX /* 用整型最大值代替∞ */
#define MAX_VERTEX_NUM 50 /* 最大顶点个数 */
typedef int VRType;
typedef char InfoType;
typedef int VertexType;
typedef VRType QElemType; /* 队列类型 */
typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct {
    VRType adj; /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
    /* 对带权图，c则为权值类型 */
    InfoType *info; /* 该弧相关信息的指针(可无) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM]; /* 顶点向量 */
    AdjMatrix arcs; /* 邻接矩阵 */
    int vexnum,arcnum; /* 图的当前顶点数和弧数 */
    GraphKind kind; /* 图的种类标志 */
}MGraph;
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
  
typedef struct
{
    QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;
  
Status CreateUDG(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G */
    int i,j;
    scanf("%d",&(*G).vexnum);
    for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
        (*G).vexs[i] = i;
    for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
        for(j=0;j<(*G).vexnum;++j)
        {
            scanf("%d",&(*G).arcs[i][j].adj); /* 图 */
            (*G).arcs[i][j].info=NULL; /* 没有相关信息 */
        }
    (*G).kind=AG;
    return OK;
}
  
int LocateVex(MGraph G,VertexType u)
{ /* 初始条件:图G存在,u和G中顶点有相同特征 */
    /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
    int i;
    for(i=0;i<G.vexnum;++i)
        if(u == G.vexs[i])
            return i;
    return -1;
}
  
int FirstAdjVex(MGraph G,VertexType v)
{ /* 初始条件: 图G存在,v是G中某个顶点 */
/*TODO 1: finish this func*/
}
  
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{ 
/* TODO2: finish this func */
}
  
Status InitQueue(LinkQueue *Q)
{ /* 构造一个空队列Q */
    (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front)
    exit(OVERFLOW);
    (*Q).front->next=NULL;
    return OK;
}
Status QueueEmpty(LinkQueue Q)
{ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
    if(Q.front==Q.rear)
    return TRUE;
    else
    return FALSE;
}
Status DeQueue(LinkQueue *Q,QElemType *e)
{ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    QueuePtr p;
    if((*Q).front==(*Q).rear)
    return ERROR;
    p=(*Q).front->next;
    *e=p->data;
    (*Q).front->next=p->next;
    if((*Q).rear==p)
    (*Q).rear=(*Q).front;
    free(p);
    return OK;
}
Status EnQueue(LinkQueue *Q,QElemType e)
{ /* 插入元素e为Q的新的队尾元素 */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* 存储分配失败 */
    exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    (*Q).rear->next=p;
    (*Q).rear=p;
    return OK;
}
  
bool visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
Status(*VisitFunc)(VertexType); /* 函数变量 */
void BFSTraverse(MGraph G,Status(*Visit)(VertexType))
{ /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
    /* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
    /*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
    /*           使用辅助队列Q和访问标志数组visited */
    int v,u,w;
    LinkQueue Q;
    for(v=0;v<G.vexnum;v++)
    visited[v]=FALSE; /* 置初值 */
    InitQueue(&Q); /* 置空的辅助队列Q */
    for(v=0;v<G.vexnum;v++)
    if(!visited[v]) /* v尚未访问 */
    {
        visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
        Visit(G.vexs[v]);
        EnQueue(&Q,v); /* v入队列 */
        while(!QueueEmpty(Q)) /* 队列不空 */
        {
            DeQueue(&Q,&u); /* 队头元素出队并置为u */
            for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))
                if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
                {
                    visited[w]=TRUE;
                    Visit(G.vexs[w]);
                    EnQueue(&Q,w);
                }
        }
    }
    printf("\n");
}
  
Status visit(VertexType i)
{
    printf("%d ",i);
    return OK;
}
  
int main() {
    MGraph g;
    CreateUDG(&g);
    BFSTraverse(g,visit);
    return 0;
}
 
