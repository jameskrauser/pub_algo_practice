/*
  DFS  array of link list    
  jameskrauser
 
  ask�G	Implement the procedure DFS (in the textbook) on unweighted undirected simple graphs.
  input�G	Number of nodes (at least 10) 
  output�G	1.	The adjacency list of an unweighted undirected simple graph,
	2.	the tree edge (pi[v], v) for every node v, and
	3.	the discovery time d[v] and the finishing time f[v] for every node v.
  detail:
  1.	The adjacency list of the graph should be represented as an array of linked lists, which is dynamically allocated by the instruction new.
  2.	Because there are no loops in the graph, any node cannot belong to the list corresponding to itself.
  3.	Because there are no parallel edges in the graph, the elements in the list corresponding to any node are all distinct.
  4.	If all ��cout�� instructions are deleted and the number of nodes is 1,000,000, then the actual running time of your program should be less than half a minute.

*/
#include <iostream>
using namespace std;
#include <queue>
#include <cmath>
#include <iomanip>
enum Color{WHITE,GRAY,BLACK};
struct Node{
	long id;
	Node *next;
};//node
void createAdjList(Node **Adj,long numberOfNodes);
void generateANode(Node *newNode,long numberOfNodes,long i);
bool duplicate(Node **Adj,Node *newNode,long i);
void tailOnTo(Node **Adj,Node *newNode,Node **tail,long i);
void createOppositeNode(Node **Adj,Node *newNode,Node **tail,long i);
void deleteAdjList(Node **Adj,long numberOfNodes);
void printAdjList(Node **Adj,long numberOfNodes);
void dfs(Node **Adj,long numberOfNodes);
void dfs_visit(long id,Color color[],Node **Adj,long d[],long f[],long parent[]);
long time = 0;
void main(){
	long numberOfNodes=0;
	do{
		cout<<"how many node? (>10) ";
		cin>>numberOfNodes;
	}while(numberOfNodes<=10);
	cout<<endl;
	Node **Adj = new Node*[numberOfNodes+1];
	createAdjList(Adj,numberOfNodes);
	printAdjList(Adj,numberOfNodes);
	dfs(Adj,numberOfNodes);

	system("pause");
};//end main

void dfs(Node **Adj,long numberOfNodes){
		Color *color = new Color[numberOfNodes+1];
		long *parent = new long[numberOfNodes+1];
		long *d = new long[numberOfNodes+1];
		long *f = new long[numberOfNodes+1];
		
		//dfs�|��Ҧ�NODE���]�@��,�N��O�W���I�]�|�],�]�Ҧ�NODE���զ��parent��0
		//dfs will go through all Node onece, event isolated Node, set all Node was White and Parent Node is zero
		for(long index=1;index<=numberOfNodes;++index){
				color[index] = WHITE;//�]�wNODE���զ�//set Node initial color was white
				parent[index] = 0;//�]�wPARENT��0 //set Node initial Parent was zero
		}
		
		//�X�ݩҦ�NODE//visit all node 
		//Visited all Node 
		for(long index2=1;index2<=numberOfNodes;++index2){
			if(color[index2] == WHITE){//only visited Node when Color was White
					dfs_visit(index2,color,Adj,d,f,parent);
			}//NODE is WHITE
		} 
	    //print result of DFS 
		cout<<"tree edges"<<endl;
		cout<<"(w,t)  Node t his parent is Node w"<<endl;
		for(long u=2;u<=numberOfNodes;++u){
			if(parent[u]==0) continue;
			cout<<"("<<parent[u]<<","<<u<<")"<<endl;//parent[2]=3 ��NODE2�����ˬONODE3
		}

		cout<<endl;
		for(long u=1;u<=numberOfNodes;++u){
			cout<<"node"<<u<<"  d["<<d[u]<<"] f["<<f[u]<<"]"<<endl;
		} 
}//dfs

void dfs_visit(long id,Color color[],Node **Adj,long d[],long f[],long parent[]){
			color[id] = GRAY;
			time+=1;
			d[id] = time;
			Node *tempnode = Adj[id];
			
			//�X�ݩҦ�NODE ID�s�X�h��EDGES
			//visited all edge from Node ID
			while(tempnode != NULL){
				if(color[ tempnode->id	] == WHITE){
						parent[tempnode->id] = id;
						dfs_visit(tempnode->id,color,Adj,d,f,parent);
				}
				tempnode = tempnode->next;//����NODE ID���U�@�ӾF�~�I
			} 
			
			//��NODE ID�Ҧ����F�~�I���]�L�F.�~�ܶ¦�
			//when Node_ID's all neighbor Node was vissited , set Node_ID to Black color
			color[id ] = BLACK;
			time+=1;
			f[id] = time;
}//dfs_visit

//�إߵL�V��.array of link list
//create undirected graph. array of link list
void createAdjList(Node **Adj,long numberOfNodes){
	long degreeUpperBound = static_cast<long>(sqrt(double(numberOfNodes)));
	Node **tail = new Node*[numberOfNodes+1];
	long *degree = new long [numberOfNodes+1];
	long *realDegree = new long [numberOfNodes+1];
	long numberOfEdges = 0;
	long i=0;
	for(i=1;i<=numberOfNodes;++i){
			degree[i] = rand()% degreeUpperBound+1;//���I���X�ӳs�X�h��edges , generate edge numbers of Node
			realDegree[i] = degree[i];
			numberOfEdges+= degree[i];
	}
	for(i=1;i<=numberOfNodes;++i){
		Adj[i] = NULL;
	}
	Node *newNode;
	for(i=1;i<=numberOfNodes;++i){
		if(realDegree[i] < numberOfNodes)
			for(long j=1;j<=degree[i];++j){//for2///�C��NODE�i�H�s�X�h��EDGES�ƥ�//loop counts = each Node's edges
				newNode = new Node;
				do{
					generateANode(newNode,numberOfNodes,i);//generate node
				}while(duplicate(Adj,newNode,i));//check duplicate NODE ID
				newNode->next =  NULL;
				tailOnTo(Adj,newNode,tail,i);//����ARRAY I��LINK LIST���̫��
				createOppositeNode(Adj,newNode,tail,i);//�L�V��,�ҥH�sNODE�]�n�s���^�hNODE i//undirected graph , so new node should connect back
				realDegree[newNode->id]++;//�sNODE�]�s�^�h�쥻��NODE.�ҥHedges�n�A�[�@//edge counts add 1 due to connect back				 
			} 	
			tail[i]->next = NULL;
	}
	delete [] realDegree;
	delete [] degree;
	delete [] tail;
}//createAdjList

void generateANode(Node *newNode,long numberOfNodes,long i){
	do{
		newNode->id = rand()%numberOfNodes+1;
	}while(newNode->id == i);//ARRAY node 3�s�X�h��NODE ID���i�O3
}//generateANode
bool duplicate(Node **Adj,Node *newNode,long i){
	Node *newnext = Adj[i];
	while(newnext!=NULL){
		if(newnext->id == newNode->id )
			return true;//�Y�s�ت�NODE ID �MARRAY����NODE ID�@��.��newNode���ƤF//if new Node_ID as same as Old Node_ID , it's duplicate

		newnext = newnext->next;
	}//while;
	return false;
}//duplicate

//��s�ت�NODE,�s���barray of link list���
//set the new Node connect to tail of array of link list
void tailOnTo(Node **Adj,Node *newNode,Node **tail,long i){
	if(Adj[i] == NULL){//�@�}�lADJ[]���ONULL//initial ADJ[] all set to NULL
		Adj[i] = newNode;
		tail[i] = newNode;
	}else{
		tail[i]->next = newNode;//��sNODE��b�̫��//set tail->next to newNode
		tail[i] = tail[i]->next;//����в���̫��//set pointer to tail
	}
}

//�]���L�V��,�ҥH�sNODE�]�n�s���^�hNODE i
//because this is undirected graph , New Node must connect back to Node i
void createOppositeNode(Node **Adj,Node *newNode,Node **tail,long i){
	Node *oppositenode = new Node;
	oppositenode->id = i;
	oppositenode->next =NULL;
	
	//��oppositenode�s��newNode��LINK LIST���̫��
	//set the oppositenode connect back to end of newNode's link list 
	tailOnTo(Adj,oppositenode,tail,newNode->id);
}//crateOppositeNode

void printAdjList(Node **Adj,long numberOfNodes){
	Node *newnext;
	for(long i=1;i<=numberOfNodes;++i){
		newnext = Adj[i];
		cout<<setw(3)<<i;
		while(newnext!=NULL){
			cout<<" -> "<<newnext->id;
			newnext = newnext->next;
		}
		cout<<endl;
	}
	cout<<endl;
}//printAdjList

void deleteAdjList(Node **Adj,long numberOfNodes){
	for(long i=1;i<=numberOfNodes;++i){
			delete [] Adj[i];
	}delete []Adj;
}//deleteAdjList

