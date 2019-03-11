#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define MAX_NAME 10
#define MAX_INFO 20
#define OK 1
#define ERROR -1



typedef int Status;
typedef int VRType;
//图的种类  {有向图，有向网，无向图，无向网}
typedef enum{DG,DN,UDG,UDN} GraphKind;


//顶点信息类型
typedef struct VertexType
{
	//顶点名称
	char name[MAX_NAME];
}VertexType;


//弧的信息类型
typedef struct  InfoType
{
	char info[MAX_INFO];
}InfoType;


//弧信息结构
typedef struct ArcCell
{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


//邻接矩阵存储结构
typedef struct MGraph
{
	//顶点向量
	VertexType vexs[MAX_VERTEX_NUM];
	//邻接矩阵
	AdjMatrix arcs;
	int arcnum;
	int vexnum;
	//图的种类
	GraphKind kind;
}MGraph;


void visit(VertexType vex);
void inputVex(VertexType *vex);
void inputArc(InfoType **info);
void outputArc(InfoType info);
void createGraph(MGraph *g);
void createDG(MGraph *g);
void createDN(MGraph *g);
void createUDN(MGraph *g);
void createUDG(MGraph *g);
int locateVex(MGraph g,VertexType v);
VertexType getVex(MGraph g,int v);
Status putVex(MGraph *g,VertexType v,VertexType value);
int firstAdjVex(MGraph g,int v);
int nextAdjVex(MGraph g,int v,int w);
void insertVex(MGraph *g,VertexType v);
Status insertArc(MGraph *g,VertexType v,VertexType w);
Status deleteVex(MGraph *g,VertexType v);
Status deleteArc(MGraph *g,VertexType v,VertexType w);
void destroyGraph(MGraph *g);
void display(MGraph g);



void createGraph(MGraph *g)
{
	switch (g->kind)
	{
	 case DN:createDN(g);
		break;
	 case DG:createDG(g);
		 break;
	 case UDN:createUDN(g);
		 break;
	 case UDG:createUDG(g);
		 break;
	}
}


//创建有向图G
void createDG(MGraph *g)
{
	VertexType v,w;
	int incInfo;
	printf_s("请输入图的顶点数﹑弧数﹑是否有相关信息（0：无 1：有）");
	//%*c吃掉回车键
	scanf_s("%d%d%d%*c",&g->vexnum,&g->arcnum,&incInfo);
	printf_s("请输入%d个顶点的值(名称<%d个字符)：",g->vexnum,MAX_NAME);
	//构造顶点向量
	for (int i = 0; i < g->vexnum; i++)
	{
		//输入顶点信息
		inputVex(&g->vexs[i]);
	}
	//初始化二维矩阵
	for (int i = 0; i < g->vexnum; i++)
	{
		for (int j = 0; j < g->vexnum; j++)
		{
			//有向图，不相邻
			g->arcs[i][j].adj = 0;
			//无相关信息
			g->arcs[i][j].info = NULL;
		}
	}
	printf_s("请输入%d条弧的弧尾﹑弧头：\n",g->arcnum);
	for (int k = 0; k < g->arcnum; k++)
	{
		//%*c吃掉回车符
		scanf_s("%s%s%*c",v.name,w.name);
		int i = locateVex(*g,v);
		int j = locateVex(*g,w);
		//不存在顶点v或w
		if (i < 0 || j < 0)
		{
			continue;
		}
		//有向图，相邻
		g->arcs[i][j].adj = 1;
		//有相关信息
		if (incInfo)
		{
			//动态生成存储空间，存储弧的信息
			inputArc(&g->arcs[i][j].info);
		}
	}
	g->kind = DG;
}


//创建有向网
void createDN(MGraph *g)
{
	VertexType v,w;
	int incInfo;
	printf_s("请输入图的顶点数﹑弧数﹑是否有相关信息（0：无 1：有）");
	scanf_s("%d%d%d%*c",&g->vexnum,&g->arcnum,&incInfo);
	printf_s("请输入%d个顶点的值(名称<%d个字符)：",g->vexnum,MAX_NAME);
	//构造顶点向量
	for (int i = 0; i < g->vexnum; i++)
	{
		//输入顶点信息
		inputVex(&g->vexs[i]);
	}
	//初始化二维矩阵
	for (int i = 0; i < g->vexnum; i++)
	{
		for (int j = 0; j < g->vexnum; j++)
		{
			//有向网，不相邻
			g->arcs[i][j].adj = INFINITY;
			//无相关信息
			g->arcs[i][j].info = NULL;
		}
	}
	printf_s("请输入%d条弧的弧尾﹑弧头﹑权值：",g->arcnum);
	int weight = 0;
	for (int k = 0; k < g->arcnum; k++)
	{
		//%*c吃掉回车符
		scanf_s("%s%s%d%*c",v.name,w.name,&weight);
		int i = locateVex(*g,v);
		int j = locateVex(*g,w);
		//不存在顶点v或w
		if (i < 0 || j < 0)
		{
			continue;
		}
		//有向网，相邻
		g->arcs[i][j].adj = weight;
		//有相关信息
		if (incInfo)
		{
			//动态生成存储空间，存储弧的信息
			inputArc(&g->arcs[i][j].info);
		}
	}
	g->kind = DN;
}


//创建无向网
void createUDN(MGraph *g)
{
	VertexType v,w;
	int incInfo;
	printf_s("请输入图的顶点数﹑弧数﹑是否有相关信息（0：无 1：有）");
	scanf_s("%d%d%d%*c",&g->vexnum,&g->arcnum,&incInfo);
	printf_s("请输入%d个顶点的值(名称<%d个字符)：",g->vexnum,MAX_NAME);
	//构造顶点向量
	for (int i = 0; i < g->vexnum; i++)
	{
		//输入顶点信息
		inputVex(&g->vexs[i]);
	}
	//初始化二维矩阵
	for (int i = 0; i < g->vexnum; i++)
	{
		for (int j = 0; j < g->vexnum; j++)
		{
			//无向网，不相邻
			g->arcs[i][j].adj = INFINITY;
			//无相关信息
			g->arcs[i][j].info = NULL;
		}
	}
	printf_s("请输入%d条弧的弧尾﹑弧头﹑权值：",g->arcnum);
	int weight;
	for (int k = 0; k < g->arcnum; k++)
	{
		//%*c吃掉回车符
		scanf_s("%s%s%d%*c",v.name,w.name,&weight);
		int i = locateVex(*g,v);
		int j = locateVex(*g,w);
		//不存在顶点v或w
		if (i < 0 || j < 0)
		{
			continue;
		}
		//无向网，相邻
		g->arcs[i][j].adj = weight;
		//有相关信息
		if (incInfo)
		{
			//动态生成存储空间，存储弧的信息
			inputArc(&g->arcs[i][j].info);
		}
		//无向，两个元素存储的信息相同
		g->arcs[j][i] = g->arcs[i][j];
	}
	g->kind = UDN;
}


//创建无向图
void createUDG(MGraph *g)
{
	VertexType v,w;
	int incInfo;
	printf_s("请输入图的顶点数﹑弧数﹑是否有相关信息（0：无 1：有）");
	scanf_s("%d%d%d%*c",&g->vexnum,&g->arcnum,&incInfo);
	printf_s("请输入%d个顶点的值(名称<%d个字符)：",g->vexnum,MAX_NAME);
	//构造顶点向量
	for (int i = 0; i < g->vexnum; i++)
	{
		//输入顶点信息
		inputVex(&g->vexs[i]);
	}
	//初始化二维矩阵
	for (int i = 0; i < g->vexnum; i++)
	{
		for (int j = 0; j < g->vexnum; j++)
		{
			//无向图，不相邻
			g->arcs[i][j].adj = 0;
			//无相关信息
			g->arcs[i][j].info = NULL;
		}
	}
	printf_s("请输入%d条弧的弧尾﹑弧头：\n",g->arcnum);
	for (int k = 0; k < g->arcnum; k++)
	{
		//%*c吃掉回车符
		scanf_s("%s%s%*c",v.name,w.name);
		int i = locateVex(*g,v);
		int j = locateVex(*g,w);
		//不存在顶点v或w
		if (i < 0 || j < 0)
		{
			continue;
		}
		//无向图，相邻
		g->arcs[i][j].adj = 1;
		//有相关信息
		if (incInfo)
		{
			//动态生成存储空间，存储弧的信息
			inputArc(&g->arcs[i][j].info);
		}
		//无向，两个元素存储的信息相同
		g->arcs[j][i] = g->arcs[i][j];
	}
	//无向图
	g->kind = UDG;
}



int locateVex(MGraph g,VertexType v)
{
	for (int i = 0; i < g.vexnum; i++)
	{
		if (0 == strcmp(v.name,g.vexs[i].name))
		{
			return i;
		}
	}
	return -1;
}



VertexType getVex(MGraph g,int v)
{
	if (v<0 || v>=g.vexnum)
	{
		VertexType v;
		strcpy_s(v.name,NULL);
		return v;
	}
	return g.vexs[v];
}



Status putVex(MGraph *g,VertexType v,VertexType value)
{
	int i = locateVex(*g,v);
	if (i < 0)
	{
		return ERROR;	
	}
	g->vexs[i] = value;
	return OK;	
}



int firstAdjVex(MGraph g,int v)
{
	VRType j = 0;
	if (g.kind%2)
	{
		j = INFINITY;
	}
	//从第1个顶点开始
	for (int i = 0; i < g.vexnum; i++)
	{
		//第一个邻接点
		if (g.arcs[v][i].adj != j)
		{
			//返回该邻接顶点的序号
			return i;
		}
	}
	return -1;
}



int nextAdjVex(MGraph g,int v,int w)
{
	//顶点关系类型：图
	VRType j = 0;
	//网
	if (g.kind%2)
	{
		j = INFINITY;
	}
	//从第w+1个顶点开始
	for (int i = w+1; i < g.vexnum; i++)
	{
		//从第w+1个顶点开始的第一个邻接点
		if (g.arcs[v][i].adj != j)
		{
			return i;
		}
	}
	return -1;
}



void insertVex(MGraph *g,VertexType v)
{
	if (g->vexnum+1 <= MAX_VERTEX_NUM)
	{
		g->vexs[g->vexnum] = v;
		VRType j = 0;
		if (g->kind%2)
		{
			j = INFINITY;
		}
		for (int i = 0; i <= g->vexnum; i++)
		{
			g->arcs[g->vexnum][i].adj = g->arcs[i][g->vexnum].adj = j;
			g->arcs[g->vexnum][i].info = g->arcs[i][g->vexnum].info = NULL;
		}
		g->vexnum++;
	}
}



Status insertArc(MGraph *g,VertexType v,VertexType w)
{
	int v1 = locateVex(*g,v);
	int w1 = locateVex(*g,w);
	if (v1 < 0 || w1 < 0 || v1 == w1)
	{
		return ERROR;
	}
	//网
	if (g->kind%2)
	{
		printf_s("请输入弧（边）的权值:");
		scanf_s("%d",g->arcs[v1][w1].adj);
	}else
	{
		//图
		g->arcs[v1][w1].adj = 1;
	}
	printf_s("是否有该弧的相关信息0：无 1：有：");
	int i;
	scanf_s("%d%*c",&i);
	if (1 == i)
	{
		inputArc(&g->arcs[v1][w1].info);
	}
	//无向
	if (g->kind>1)
	{
		g->arcs[w1][v1] = g->arcs[v1][w1];
	}
	g->arcnum++;
	return OK;
}


//若图g中存在顶点v，则删除图g中的顶点v
Status deleteVex(MGraph *g,VertexType v)
{
	//待删顶点的序号
	int k = locateVex(*g,v);
	//不存在顶点v
	if (k < 0)
	{
		return ERROR;
	}
	//删除由顶点v发出的所有边（弧）
	for (int i = 0; i < g->vexnum; i++)
	{
		deleteArc(g,v,g->vexs[i]);
	}
	//有向
	if (g->kind < 2)
	{
		//删除发向顶点v的所有弧
		for (int i = 0; i < g->vexnum; i++)
		{
			deleteArc(g,g->vexs[i],v);
		}
	}
	//顶点v后面的顶点往前移
	for (int j = k+1; j < g->vexnum; j++)
	{
		g->vexs[j-1] = g->vexs[j];
	}
	for (int i = 0; i < g->vexnum; i++)
	{
		for (int j = k+1; j < g->vexnum; j++)
		{
			//移动待删除顶点v右边的矩阵元素
			g->arcs[i][j-1] = g->arcs[i][j];
			//移动待删除顶点v下边的矩阵元素
			g->arcs[j-1][i] = g->arcs[j][i];
		}
	}
	//顶点数减1
	g->vexnum--;
	return OK;
}



Status deleteArc(MGraph *g,VertexType v,VertexType w)
{
	int v1 = locateVex(*g,v);
	int w1 = locateVex(*g,w);
	//不存在顶点v1或w1
	if (v1 < 0 || w1 < 0)
	{
		return ERROR;
	}
	VRType j = 0;
	//网
	if (g->kind%2)
	{
		j = INFINITY;
	}
	//存在弧（边）
	if (g->arcs[v1][w1].adj != j)
	{
		//删除弧<w,v>
		g->arcs[v1][w1].adj = j;
		//有弧（边）的信息
		if (g->arcs[v1][w1].info)
		{
			//释放信息指针
			free(g->arcs[v1][w1].info);
			//将信息指针置为空
			g->arcs[v1][w1].info = NULL;
		}
		//无向，删除对称弧（边）<w,v>
		if (g->kind>1)
		{
			g->arcs[w1][v1] = g->arcs[v1][w1];
		}
		g->arcnum--;
		return OK;
	}
	return ERROR;
}



void destroyGraph(MGraph *g)
{
	for (int i = g->vexnum-1; i >= 0; i--)
	{
		deleteVex(g,g->vexs[i]);
	}
}



void inputArc(InfoType **info)
{
	char s[MAX_INFO];
	printf_s("请输入该弧的相关信息(<%d个字符)：",MAX_INFO);
	gets_s(s);
	int m = strlen(s);
	if (m)
	{
		*info = (InfoType *)malloc(MAX_INFO*sizeof(char));
		strcpy_s((**info).info,s);
	}
}



void outputArc(InfoType info)
{
	printf_s("%s",info.info);
}



void visit(VertexType vex)
{
	printf_s("%s",vex.name);
}



void inputVex(VertexType *vex)
{
	scanf_s("%s",vex->name);
}


//输出邻接矩阵存储结构的图G
void display(MGraph g)
{
	char s[7] = "无向网";
	char s1[3] = "边";
	switch (g.kind)
	{
	case DG:strcpy_s(s,"有向图");
			strcpy_s(s1,"弧");
			break;
	case DN:strcpy_s(s,"有向网");
		    strcpy_s(s1,"弧");
		    break;
	case UDG:strcpy_s(s,"无向图");
			break;
	case UDN:;
	}
	printf_s("%d个顶点  %d条%s的%s。顶点依次是：",g.vexnum,g.arcnum,s1,s);
	for (int i = 0; i < g.vexnum; i++)
	{
		//依次访问顶点
		visit(getVex(g,i));
	}
	//输出二维矩阵
	for (int i = 0; i < g.vexnum; i++)
	{
		for (int j = 0; j < g.vexnum; j++)
		{
			if (INFINITY == g.arcs[i][j].adj)
			{
				printf_s("");
			}else
			{
				printf_s("%4d",g.arcs[i][j].adj);
			}
			printf_s("\n");
		}
	}
	printf_s("G.arcs.info:\n");
	//有向
	if (g.kind < 2)
	{
		printf_s("弧尾  弧头  该%s的信息：\n",s1);
	}else
	{
		//无向
		printf_s("顶点1  顶点2  该%s的信息：\n",s1);
	}
	for (int i = 0; i < g.vexnum; i++)
	{
		//有向
		if (g.kind < 2)
		{
			for (int j = 0; j < g.vexnum; j++)
			{
				if (g.arcs[i][j].info)
				{
					printf_s("%5s%5s",g.vexs[i].name,g.vexs[j].name);
					//输出弧的信息
					outputArc(*g.arcs[i][j].info);
				}
			}
		}else
		{
			//无向，输出上三角
			for (int j = i+1; j < g.vexnum; j++)
			{
				if (g.arcs[i][j].info)
				{
					printf_s("%5s%5s",g.vexs[i].name,g.vexs[j].name);
					//输出弧的信息
					outputArc(*g.arcs[i][j].info);
				}
			}
		}
	}
}



