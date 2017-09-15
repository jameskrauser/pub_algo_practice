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
		long *realDegree = new long [numberOfNodes+1];//�]���O�L�V�ϩҥH��A�s��B��,B��EDGES�Ƥ]�n�[1
		long numberOfEdges=0;
		long i;
		for(i=1;i<=numberOfNodes;i++){//
				degree[i] = rand() % degreeUpperBound+1;//�H���إ�EDGES�ƥ�
				realDegree[i] = degree[i];//�ƨ�EDGES�ƥ�
				numberOfEdges+=degree[i];//EDGES�ƥإ[�`
		}//for

		for(i=1;i<=numberOfNodes;i++){
			Adj[i] = NULL;
		}
	
		Node *newNode;
		for(i=1;i<=numberOfNodes;i++){//for1 �q�Ĥ@��NODE�}�lSEARCH
			if(realDegree[i] < numberOfNodes)
				for(long j=1;j <=degree[i]; j++){//for2 �̷ӨC��NODE��EDGES�ƥ�.�إ�NODE
					newNode = new Node;
					do{
						generateANode(newNode,numberOfNodes,i);//�إ�NODE
					}while(duplicate(Adj,newNode,i));//�ˬd���L���ƥ�NODE ID
					newNode->next = NULL;
					tailOnTo(Adj,newNode,tail,i);//����ARRAY i��LINK LIST���̫��
					createOppositeNode(Adj,newNode,tail,i);//�]���L�V��.�ҥH�s��NODE�]�n�s���^�hNODE i
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
	}while(newNode->id == i);//ARRAY 3 �s�X�h��NOD�ӡ@�עҡ@���i�O��
}//generateANode

bool duplicate(Node **Adj,Node *newNode,long i){
	
	Node *newnext = Adj[i];//
	while(newnext != NULL){
		if(newnext->id == newNode->id ) return true;//�Y�s�ت�NODE ID�MARRAY����NODE ID�@��.
													//��newNode�Qnewnext�s���G���F
		newnext = newnext->next;//���V�U�@��NODE//move to next node
	}
	return false;
}//duplicate

void tailOnTo(Node **Adj,Node *newNode,Node **tail,long i){//��s�إߪ�NODE,�s���barray of link list �̫��
	
	if(Adj[i] == NULL){	//�@�}�lADJ[]���O�ܢ�ڢ�
		Adj[i] = newNode;
		tail[i] = newNode;
	}else{
		tail[i]->next = newNode;//��sNODE���̫��
		tail[i]= tail[i]->next;//����в���̫��
	}

}//tailOnTo

//�]���L�V��.�ҥH�s��NODE�]�n�s���^�hNODE i
void createOppositeNode(Node **Adj,Node *newNode,Node **tail,long i){
	Node *oppositenode = new Node;
	oppositenode->id = i;
	oppositenode->next = NULL;
	tailOnTo(Adj,oppositenode,tail,newNode->id);//��oppositenode�s����newNODE��LINK LIST �̫��

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
	Color *color = new Color[numberOfNodes+1];//��l���C��
	long *parent = new long[numberOfNodes+1];//��l�Ƥ���
	long *distance = new long[numberOfNodes+1];//��l�ƶZ��

	for(u =1;u <=numberOfNodes;u++){
		//set s = 1 , so node1 no need to initial data
		//�]�ws��1.�ҥHNODE 1�����]�w
		if( u == s) continue;
		color[u] = WHITE;
		distance[u] = -1;
		parent[u] = 0;
	}

	color[s] = GRAY;//NODE1���Ǧ�//node1 set go grey
	distance[s] = 0;//NODE1�Z����0//node1 set distance to zero
	parent[s] =0;
	q.push(s);//��NODE1��JQUEUE��//put node1 to queue

	while(! q.empty()){//queue not empty
		u = q.front();
		q.pop();
		newnext = Adj[u];

		while(newnext != NULL){
			//when NewNode's edge Node Color was white , keep put in queue 
			//��NEWNODE�s�X�h��NODE�C�⬰�զ�.�N�i�A��JQUEUE��
			if(color[newnext->id] == WHITE)
			{
					color[newnext->id]=GRAY;
					distance[newnext->id] = distance[u] +1;
					parent[newnext->id]=u;
					q.push(newnext->id);
			}
			//���Varray NODE1��linklist�ҫ��X�h��NODE
			//cheage node to newnode
			newnext = newnext->next;
		}//WHILE
		
		//��NODE u���X�h��NODE���S���զ�.�hnode u ���¦�
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


