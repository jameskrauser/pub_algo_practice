//jameskrauser 
//Breadth-First- Search on array of link list undirected graph 
 
#include <iostream>
using namespace std;
#include <queue>
#include <cmath>
#include <iomanip>

enum Color{WHITE,GRAY,BLACK};
struct Node{
	long id;
	Node *next;
};

void createAdjList(Node **Adj,long numberOfNodes);
void generateANode(Node *newNode,long numberOfNodes,long i);
bool duplicate(Node **Adj,Node *newNode,long i);
void tailOnTo(Node **Adj,Node *newNode,Node **tail,long i);
void createOppositeNode(Node **Adj,Node *newNode,Node **tail,long i);
void deleteAdjList(Node **Adj,long numberOfNodes);
void BFS(Node **Adj,long numberOfNodes,long s);
void printAdjList(Node **Adj,long numberOfNodes);
void main(){

	long numberOfNodes=0;
//	do{
		cout<<"How many nodes? (>10)";
		cin>>numberOfNodes;
//	}while(numberOfNodes<=10);

	Node **Adj = new Node*[numberOfNodes+1];
	createAdjList(Adj,numberOfNodes);
	printAdjList(Adj,numberOfNodes);
	BFS(Adj,numberOfNodes,1);
	deleteAdjList(Adj,numberOfNodes);
	
	system("pause");
}//main
void createAdjList(Node **Adj,long numberOfNodes){
		long degreeUpperBound = static_cast<long>(sqrt(double(numberOfNodes)));
		Node **tail = new Node*[numberOfNodes+1];
		long *degree = new long [numberOfNodes+1];
		long *realDegree = new long [numberOfNodes+1];//因為是無向圖所以當A連到B時,B的EDGES數也要加1
		long numberOfEdges=0;
		long i;
		for(i=1;i<=numberOfNodes;i++){//
				degree[i] = rand() % degreeUpperBound+1;//隨機建立EDGES數目
				realDegree[i] = degree[i];//複制EDGES數目
				numberOfEdges+=degree[i];//EDGES數目加總
		}//for

		for(i=1;i<=numberOfNodes;i++){
			Adj[i] = NULL;
		}
	
		Node *newNode;
		for(i=1;i<=numberOfNodes;i++){//for1 從第一個NODE開始SEARCH
			if(realDegree[i] < numberOfNodes)
				for(long j=1;j <=degree[i]; j++){//for2 依照每個NODE的EDGES數目.建立NODE
					newNode = new Node;
					do{
						generateANode(newNode,numberOfNodes,i);//建立NODE
					}while(duplicate(Adj,newNode,i));//檢查有無重複生NODE ID
					newNode->next = NULL;
					tailOnTo(Adj,newNode,tail,i);//移到ARRAY i的LINK LIST的最後方
					createOppositeNode(Adj,newNode,tail,i);//因為無向圖.所以新的NODE也要連接回去NODE i
					realDegree[newNode->id]++;
					
				}//for2
				tail[i]->next = NULL;
		}//for1
		delete [] realDegree;
		delete [] degree;
		delete [] tail;

}//createAdjList
void generateANode(Node *newNode,long numberOfNodes,long i){
	do{
			newNode->id = rand() % numberOfNodes+1;
	}while(newNode->id == i);//ARRAY 3 連出去的NODＥ　ＩＤ　不可是３
}//generateANode

bool duplicate(Node **Adj,Node *newNode,long i){
	
	Node *newnext = Adj[i];//
	while(newnext != NULL){
		if(newnext->id == newNode->id ) return true;//若新建的NODE ID和ARRAY中的NODE ID一樣.
													//表newNode被newnext連接二次了
		newnext = newnext->next;//移向下一個NODE//move to next node
	}
	return false;
}//duplicate

void tailOnTo(Node **Adj,Node *newNode,Node **tail,long i){//把新建立的NODE,連接在array of link list 最後方
	
	if(Adj[i] == NULL){	//一開始ADJ[]全是ＮＵＬＬ
		Adj[i] = newNode;
		tail[i] = newNode;
	}else{
		tail[i]->next = newNode;//把新NODE放到最後方
		tail[i]= tail[i]->next;//把指標移到最後方
	}

}//tailOnTo

//因為無向圖.所以新的NODE也要連接回去NODE i
void createOppositeNode(Node **Adj,Node *newNode,Node **tail,long i){
	Node *oppositenode = new Node;
	oppositenode->id = i;
	oppositenode->next = NULL;
	tailOnTo(Adj,oppositenode,tail,newNode->id);//把oppositenode連接到newNODE的LINK LIST 最後方

}//createOppositeNode

void printAdjList(Node **Adj,long numberOfNodes){
	Node *newnext;
	for(long i=1;i <=numberOfNodes;i++){
		newnext = Adj[i];
		cout<<setw(3)<<i;
		while(newnext !=NULL){
			cout<<" -> "<<newnext->id;
			newnext = newnext->next;
		}//while
		cout<<endl;
	}//for
  cout<<endl;
}//printAdjList

void deleteAdjList(Node **Adj,long numberOfNodes){
	for(long i =1; i<= numberOfNodes;i++){
		delete [] Adj[i];
	}
	delete [] Adj;
}//deleteAdjList

void BFS(Node **Adj,long numberOfNodes,long s){
	long u;
	queue<long> q;
	Node *newnext;
	Color *color = new Color[numberOfNodes+1];//初始化顏色
	long *parent = new long[numberOfNodes+1];//初始化父母
	long *distance = new long[numberOfNodes+1];//初始化距離

	for(u =1;u <=numberOfNodes;u++){
		//set s = 1 , so node1 no need to initial data
		//設定s為1.所以NODE 1不必設定
		if( u == s) continue;
		color[u] = WHITE;
		distance[u] = -1;
		parent[u] = 0;
	}

	color[s] = GRAY;//NODE1為灰色//node1 set go grey
	distance[s] = 0;//NODE1距離為0//node1 set distance to zero
	parent[s] =0;
	q.push(s);//把NODE1放入QUEUE中//put node1 to queue

	while(! q.empty()){//queue not empty
		u = q.front();
		q.pop();
		newnext = Adj[u];

		while(newnext != NULL){
			//when NewNode's edge Node Color was white , keep put in queue 
			//當NEWNODE連出去的NODE顏色為白色.就可再放入QUEUE中
			if(color[newnext->id] == WHITE)
			{
					color[newnext->id]=GRAY;
					distance[newnext->id] = distance[u] +1;
					parent[newnext->id]=u;
					q.push(newnext->id);
			}
			//指向array NODE1用linklist所指出去的NODE
			//cheage node to newnode
			newnext = newnext->next;
		}//WHILE
		
		//當NODE u指出去的NODE都沒有白色.則node u 為黑色
		//set node u to black , when node u's connect node all was not white color
		color[u] = BLACK;
	}

	//result of BFS
	cout<<"\n -----Result of BFS ------------- \n"<<endl;
	cout<<"tree edges "<<endl<<endl;
	cout<<"(node u's parent,node u)"<<endl;
	for(u=2;u<=numberOfNodes;u++){
		if(parent[u] == 0)continue;
		cout<<"("<<parent[u]<<","<<u<<")"<<endl;
	}
	cout<<endl;
	for(u=1;u<=numberOfNodes;u++){
		cout<<"d["<<u<<"]= "<<setw(2)<<distance[u]<<endl;
	}
	cout<<endl;
}//BFS


