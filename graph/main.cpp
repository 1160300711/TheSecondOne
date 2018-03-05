#include <iostream>
#include <cstdio>
#include <cstring>
#define MaxSize 100
using namespace std;
typedef char VertexData;
typedef char VertexType;
typedef int EdgeData;
typedef int InfoType;
typedef enum {unvisited,visited} VisitIf;
typedef struct MTGraph{
    VertexData vertex[MaxSize];
    EdgeData edge[MaxSize][MaxSize];
    int n,e;
    MTGraph(){
    n=0;e=0;
    int i,j;
    for(i=0;i<MaxSize;i++)
        for(j=0;j<MaxSize;j++)
            edge[i][j]=MaxSize;
    }
}MTgraph;
typedef struct node{
    int adjvex;
    EdgeData cost;
    struct node* next;
    EdgeNode(){next=0;}
}EdgeNode;
typedef struct VertexNode{
    VertexData vertex;
    EdgeNode* firstedge;
    VertexNode(){firstedge=0;}
}VertexNode;
typedef struct AdjGraph{
    VertexNode vexlist[MaxSize];
    int n,e;
}AdjGraph;
typedef struct ArcBox{
    int tailvex,headvex;
    struct ArcBox *hlink,*tlink;
    InfoType info;
    ArcBox(){hlink=0;tlink=0;}
}ArcBox;
typedef struct VexNode{
    VertexType data;
    ArcBox *firstin,*firstout;
    int indegree[MaxSize];
    int in;
    VexNode(){firstin=0;firstout=0;memset(indegree,0,MaxSize);in=0;}
}VexNode;
typedef struct OLGraph{
    VexNode xlist[MaxSize];
    int vexnum,arcnum;
}OLGraph;
typedef struct EBox{
   // VisitIf mark;
    int ivex,jvex;
    EBox *ilink,*jlink;
    EBox(){ilink=0;jlink=0;}
    InfoType info;
}EBox;
typedef struct VexBox{
    VertexType data;
    EBox *firstedge;
    VexBox(){firstedge=0;}
}VexBox;
typedef struct AMLGraph{
    VexBox adjmulist[MaxSize];
    int vexnum,edgenum;
}AMLGraph;
MTGraph* CreateMGraph(){
    FILE *fp;
    fp=fopen("1111.txt","r");
    int B,N;
    int x=0,y=0,w=0;
    int step;
    int i=-1;
    MTGraph* G=new MTGraph;
    fscanf(fp,"%d %d",&B,&N);
    //cin>>B>>N;
    G->n=N;
    for(step=0;step<N;step++){
            G->vertex[step]=(65+step);
        }
    fscanf(fp,"%d %d %d",&x,&y,&w);
    //cin>>x>>y>>w;
    while(x!=-1&&y!=-1&&w!=-1){
        if(B==1){
            G->edge[x][y]=w;
        }
        if(B==0){
            G->edge[x][y]=w;
            G->edge[y][x]=w;
        }
        G->e++;
        fscanf(fp,"%d %d %d",&x,&y,&w);
    }
    fclose(fp);
    return G;
}
AdjGraph* CreateGraph(MTGraph *graph){
    AdjGraph* adj = new AdjGraph;
    EdgeNode *p=0,*q=0;
    int i,j;
    for(i=0;i<graph->n;i++){
        adj->vexlist[i].vertex=graph->vertex[i];
        for(j=0;j<graph->n;j++){
            if(graph->edge[i][j]!=MaxSize){
                if(p==0){
                    p=new EdgeNode;
                    p->next=0;
                    p->adjvex=j;
                    p->cost=graph->edge[i][j];
                    adj->vexlist[i].firstedge=p;
                }
                else{
                    q=new EdgeNode;
                    q->next=0;
                    q->adjvex=j;
                    q->cost=graph->edge[i][j];
                    p->next=q;
                    p=q;
                }
            }
        }
        p=0;
    }
    adj->n=graph->n;
    adj->e=graph->e;
    return adj;
}
OLGraph* CreateDG(MTGraph *graph){
    OLGraph *ol=new OLGraph;
    int i,j;
    ArcBox *p;
    ol->vexnum=graph->n;
    ol->arcnum=graph->e;
    for(i=0;i<graph->n;i++){
            ol->xlist[i].data=graph->vertex[i];
        for(j=0;j<graph->n;j++){
            if(graph->edge[i][j]!=MaxSize){
                p=new ArcBox;
                p->headvex=j;
                p->tailvex=i;
                p->info=graph->edge[i][j];
                ol->xlist[j].indegree[i]=1;
                ol->xlist[j].in++;
                p->tlink=ol->xlist[i].firstout;
                p->hlink=ol->xlist[j].firstin;
                ol->xlist[i].firstout=p;
                ol->xlist[j].firstin=p;

            }
        }
    }
    return ol;
}
AMLGraph* CreateUDG_AML(MTGraph* graph){
    AMLGraph* aml = new AMLGraph;
    int i,j;
    aml->edgenum=graph->e;
    aml->vexnum=graph->n;
    for(i=0;i<graph->n;i++){
        aml->adjmulist[i].data=graph->vertex[i];
        for(j=i+1;j<graph->n;j++){
            if(graph->edge[i][j]!=MaxSize){
                EBox *p=new EBox;
                p->ilink=0;
                p->jlink=0;
                p->ivex=j;
                p->jvex=i;
                p->info=graph->edge[i][j];
                p->ilink=aml->adjmulist[i].firstedge;
                p->jlink=aml->adjmulist[j].firstedge;
                aml->adjmulist[i].firstedge=p;
                aml->adjmulist[j].firstedge=p;
            }
        }
    }
    return aml;
}
void DFS_next(AdjGraph* G,bool s[],int i){
    EdgeNode *p;
    //VertexData a[MaxSize];
    cout<<G->vexlist[i].vertex;
    s[i]=true;
    p=G->vexlist[i].firstedge;
    if(p!=0&&s[p->adjvex]==false){
        DFS_next(G,s,p->adjvex);
        p=p->next;
    }

}
void DFS1(AdjGraph *G){
    int i,j;
    bool s[MaxSize]={false};
    for(i=0;i<G->n;i++){
        if(s[i]==false)
            DFS_next(G,s,i);
    }
}
void BFS1(MTGraph *G){
    int visit[MaxSize]={0};
    int i,j;
    for(i=0;i<G->n;i++){
        if(visit[i]==0){
            cout<<G->vertex[i]<<" ";
            visit[i]=1;
        }
        for(j=0;j<G->n;j++){
            if(G->edge[i][j]!=MaxSize&&visit[j]==0){
                cout<<G->vertex[j]<<" ";
                visit[j]=1;
            }
        }
    }

}
void prim(MTGraph G){
    int LOWCOST[MaxSize];
    bool visited[MaxSize]={0};
    int i,j,k,MIN;
    VertexData CLOSSET[MaxSize];
    for(i=1;i<G.n;i++){
        CLOSSET[i]=0;
        LOWCOST[i]=G.edge[0][i];
    }
    cout<<G.vertex[0];
    for(i=1;i<G.n;i++){
        MIN=LOWCOST[1];
        k=1;
        for(j=1;j<G.n;j++){
            if(LOWCOST[j]<MIN){
                MIN=LOWCOST[j];
                k=j;
            }
        }
        cout<<"("<<LOWCOST[k]<<","<<G.vertex[k]<<")"<<endl;
        LOWCOST[k]=MaxSize;
        visited[k]=1;
        for(j=1;j<G.n;j++){
            if(G.edge[k][j]<LOWCOST[j]&&visited[j]!=1){
            LOWCOST[j]=G.edge[k][j];
            CLOSSET[j]=k;
            }
        }
    }
}
int mincost(int D[],bool s[],MTGraph G){
    int temp=MaxSize;
    int w,i;
    for(i=1;i<G.n;i++){
        if(!s[i]&&D[i]<temp){
            temp=D[i];
            w=i;
        }
    }
    return w;
}
void Dijkstra(MTGraph G){
    int D[MaxSize];
    int p[MaxSize];
    bool s[MaxSize]={false};
    int i,j;
    int w,sum;
    for(i=0;i<G.n;i++){
        D[i]=G.edge[0][i];
        p[i]=0;
    }
    s[0]=true;
    for(i=0;i<G.n;i++){
        w=mincost(D,s,G);
        s[w]=true;
        for(j=1;j<G.n;j++){
            if(s[j]!=true){
                sum=D[w]+G.edge[w][j];
                if(sum<D[j]){
                    D[j]=sum;
                    p[j]=w;
                }
            }
        }
    }
    for(i=1;i<G.n;i++){cout<<"  "<<D[i];}
}
void print(MTGraph *G){
    int i,j;
    for(i=0;i<G->n;i++){
            cout<<endl;
        for(j=0;j<G->n;j++){
            cout.width(4);
            cout<<G->edge[i][j];
        }
    }
}
void print_adj(AdjGraph *G){
    int i;
    EdgeNode *p;
    for(i=0;i<G->n;i++){
        cout<<G->vexlist[i].vertex<<" : ";
        p=G->vexlist[i].firstedge;
        while(p!=0){
            cout<<p->adjvex<<"  ";
            p=p->next;
        }
        cout<<endl;
    }
}
void print_ol(OLGraph *G){
    int i;
    ArcBox *p;
    for(i=0;i<G->vexnum;i++){
        cout<<G->xlist[i].data<<" : ";
        p=G->xlist[i].firstout;
        while(p!=0){
            cout<<p->headvex<<"  ";
            p=p->tlink;
        }
       cout<<endl;
    }
    for(i=0;i<G->vexnum;i++){
        cout<<G->xlist[i].data<<" : ";
        p=G->xlist[i].firstin;
        while(p!=0){
            cout<<p->tailvex<<"  ";
            p=p->hlink;
        }
       cout<<endl;
    }

}
int in_order[MaxSize];
int num=-1;
void or_DFS(OLGraph* G,int v,bool visited[]){
    ArcBox *p;
//    int num=-1;
//    bool visited[MaxSize]={false};
    visited[v]=true;
    for(p=G->xlist[v].firstout;p!=0;p=p->tlink){
        if(!visited[p->headvex])
            or_DFS(G,p->headvex,visited);
    }
    in_order[++num]=v;
}
void Rev_DFS(OLGraph* G,int v,bool visited[]){
    ArcBox *p;
 //   bool visited[MaxSize]={false};
    visited[v]=true;
    cout<<v<<" ";
    for(p=G->xlist[v].firstin;p!=0;p=p->hlink){
        if(!visited[p->tailvex])
            Rev_DFS(G,p->tailvex,visited);
    }
}
void Strongly_Connected_Component(OLGraph* G){
    int k=1,v,j;
    bool visited[MaxSize]={false};
    for(v=0;v<G->vexnum;v++)
        if(!visited[v])
            or_DFS(G,v,visited);
    for(v=0;v<G->vexnum;v++)
        visited[v]=false;
    for(j=G->vexnum-1;j>=0;j--){
        v=in_order[j];
        if(!visited[v]){
            cout<<endl<<"第"<<k<<"个联通分量";
            k++;
            Rev_DFS(G,v,visited);
        }
    }
}
void Topologicalsort(OLGraph G){
    int Q[MaxSize]={0};
    int FRONT=0,REAR=-1;
    int v,nodes=0,i,j;
    int visited[MaxSize]={0};
    ArcBox *p;
    for(v=0;v<G.vexnum;v++){
        if(G.xlist[v].firstin==0){
            Q[++REAR]=v;
            visited[v]=1;
        }
    }
    while(REAR>=FRONT){
        v=Q[FRONT];
        FRONT++;
        cout<<G.xlist[v].data;
        nodes++;
        for(i=0;i<G.vexnum;i++){
            if(G.xlist[i].indegree[v]==1)
                G.xlist[i].in--;
        }

        for(i=0;i<G.vexnum;i++){
            if(visited[i]==0&&G.xlist[i].in==0){
                Q[++REAR]=i;
                visited[i]=1;

            }
        }
    }
    if(nodes<G.vexnum)
        cout<<"图中有环路";
}
void print_aml(AMLGraph *G){
    int i;
    EBox *p;
    for(i=0;i<G->vexnum;i++){
        cout<<G->adjmulist[i].data<<" : ";
        p=G->adjmulist[i].firstedge;
        while(p!=0){
            cout<<" ("<<p->ivex<<","<<p->jvex<<") ";
            p=p->ilink;
        }
       cout<<endl;
    }
    for(i=0;i<G->vexnum;i++){
        cout<<G->adjmulist[i].data<<" : ";
        p=G->adjmulist[i].firstedge;
        while(p!=0){
            cout<<" ("<<p->ivex<<","<<p->jvex<<") ";
            p=p->jlink;
        }
       cout<<endl;
    }
}
int main()
{
    MTGraph *graph;
    AdjGraph *adj_graph;
    OLGraph *ol;
    AMLGraph *aml;
    graph=CreateMGraph();
    cout<<"******邻接矩阵如下所示******* ";
    print(graph);
    cout<<endl;
    adj_graph=CreateGraph(graph);
    cout<<"******邻接链表如下所示******* "<<endl;
    print_adj(adj_graph);
    cout<<endl;
    ol=CreateDG(graph);
    cout<<"******十字链表如下所示******* "<<endl;
    print_ol(ol);
    cout<<endl;
    cout<<"******多重邻接表如下所示******* "<<endl;
    aml=CreateUDG_AML(graph);
    print_aml(aml);
    cout<<endl;
    cout<<"******DFS算法如下所示******* "<<endl;
    DFS1(adj_graph);
    cout<<endl;
    cout<<"******BFS算法如下所示******* "<<endl;
    BFS1(graph);
    cout<<endl;
    cout<<"******最小生成树算法如下所示******* "<<endl;
    prim(*graph);
    cout<<endl;
    cout<<"******单源路径最短算法如下所示******* "<<endl;
    Dijkstra(*graph);
    cout<<endl;
    cout<<"******强连通分量算法如下所示******* "<<endl;
    Strongly_Connected_Component(ol);
    cout<<endl;
    cout<<"******拓扑排序算法如下所示******* "<<endl;
    Topologicalsort(*ol);
    return 0;
}
