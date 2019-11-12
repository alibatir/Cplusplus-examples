//minimum spanning tree using Prim's algorithm 
//Download graphViz from http://www.graphviz.org/Download.php  to see the graph visually

#include <iostream>
#include <cstdlib> /* rand, srand */
#include <cstdio> /*for NULL*/
#include <list> /* list (adjacency list)*/
#include <climits> /* for MAX_INT */
#include <fstream> /* input/output file operations*/
#include <ctime> /* time */
#include <vector> /* vector */

using namespace std; /* cout,cin */

class AdjListNode{
public:
	int v; //node value
	int w; //weight
public:
	AdjListNode(int lv, int lw){
		v=lv;
		w=lw;
	}
	int getV(){
		return v;
	}
	int getWeight(){
		return w;
	}
};
class Node{
public:
	bool known;
	int parent;
	int dist;
public:
	Node(){
		known=false;
		parent=-1;
		dist=INT_MAX;
	}
	//Copy constructor
	Node(const Node &v){
		known=v.known;
		parent=v.parent;
		dist=v.dist;
	}
	//Overloaded assignment operator
	Node& operator=(const Node &v){
		// avoid self copy:
		if(this!=&v){
			//copy v:
			known=v.known;
			parent=v.parent;
			dist=v.dist;
		}
		return *this;
	}
	//Destructor
	~Node(){

	}
};
class Graph{
public:
	int numNodes;
	list<AdjListNode> *adj; //adjacency list
	Node* nodeSet;
	int source;
	int ** child; //child matrix
	int * numChildren; //number of children array
public:
	Graph(int numOfNodes){
		this->numNodes=numOfNodes;
		adj=new list<AdjListNode> [numNodes];
		nodeSet=new Node [numNodes];
		child=new int * [numNodes];
		for(int i=0;i<numNodes;i++){
			child[i]=new int [numNodes];
		}
		numChildren=new int [numNodes];
	}
	//add edge of u,v with weight into the adjacency list
	void addEdge(int u, int v, int weight){
		AdjListNode nod(v,weight);
		adj[u].push_back(nod);
	}
	//find the node which gives the minimum distance edge
	int min_dist(){
		int min=INT_MAX;
		int min_index;
		for(int i=0;i<numNodes;i++){
			if(nodeSet[i].known==false && nodeSet[i].dist<=min){
				min=nodeSet[i].dist;
				min_index=i;
			}
		}
		return min_index;
	}
	//prim's algorithm for minimum spanning tree
	void prim(){
		source= rand() % numNodes;
		nodeSet[source].dist=0; //distance of the chosen node is 0
		int u; //node to be added to the minimum spanning tree
		int v; //node value
		int w; //weight
		while(!allNodesVisited()){
			for(int i=0;i<numNodes;i++){
				u=min_dist();
				nodeSet[u].known=true;
				list<AdjListNode>::iterator it;
				for(it=adj[u].begin();it!=adj[u].end();it++){
					v=it->getV();
					w=it->getWeight();
					if(nodeSet[v].known==false && w< nodeSet[v].dist){
						nodeSet[v].parent=u;
						nodeSet[v].dist=w;
					}
				}
			}
		}
		printTree();

	}
	//prints tree in console and gives a graphViz file
	void printTree(){
		int v;
		for(int i=0;i<numNodes;i++){
			v=nodeSet[i].parent;
			if(v!=-1){
				child[v][numChildren[v]]=i;
				numChildren[v]++;
			}
		}
		drawGraph(); //see minSpanTree.dot file in the directory
		for(int i=0;i<numNodes;i++){
			if(nodeSet[i].parent!=-1){
				cout<<nodeSet[i].parent<<"-"<<i<<endl;
			}
		}
	}
	//Draws the tree in GraphViz and shows the minimum spanning tree
	void drawGraph(){

		ofstream fout("minSpanTree.dot",ofstream::out);
		fout<<"digraph G {\n";
		fout<<"edge [arrowhead=none]\n";
		for(int i=0; i<numNodes; i++){
			for(int j=0;j<numChildren[i];j++ ){
				fout<<i<<"->"<<child[i][j]<<"[label="<<abs(nodeSet[child[i][j]].dist-nodeSet[i].dist)<<"];";
				fout<<endl;
			}
		}
		fout<<"}";
		fout.close();
	}
	//Check if all nodes are visited
	bool allNodesVisited(){
		for(int i=0;i<numNodes;i++){
			if(nodeSet[i].known==false){
				return false;
			}
		}
		return true;
	}
	//Destructor
	~Graph(){
		for(int i=0;i<numNodes;i++){
			delete[] child[i];
		}
		delete[] numChildren;
	}
};
int main() {

	/* Vectors
	 *
	 * Remove the comments in this part to see how it works
	 * */

//			vector<int> myVector;
//			int myint=5;
//			myVector.push_back(5); /* Add myint to the back of the vector */
//			myVector.pop_back(); /* Remove myint from the back of the vector */
//			vector<int>::iterator it; /* it is the iterator to navigate within the vector */
//			vector<int>::iterator it2;
//			it=myVector.begin(); 	/* it points to the beginning of the vector */
//			it=myVector.insert(it,200); /* it points to 200 */
//			for(it2=myVector.begin();it2<myVector.end();it2++){
//				cout<<' '<<*it2;
//			}
//			it=myVector.begin();  /* it points to the first element*/
//			it=myVector.begin()+1; /* it points to the second element*/
//			it=myVector.begin()+(myVector.size()-1); /* it points to the last element*/
//			cout<<endl;
//			it=myVector.insert(it,300);
//			/* insert 300 before the position pointed by it
//			* (before 200) and update the it to position of 300 (points to 300)*/
//			/* print the vector*/
//			for(it2=myVector.begin();it2<myVector.end();it2++){
//				cout<<' '<<*it2;
//			}
//			cout<<endl;
//			myVector.insert(it+1,400);
//			/* insert 400 before 200, because it+1 points to the position after 300, which is at 200*/
//			for(it=myVector.begin();it<myVector.end();it++){
//				cout<<' '<<*it;
//			}

	/* Prim's algorithm */

	srand (time(NULL)); // initialize random seed
	Graph g(9);

	/*add edges*/
	g.addEdge(0,1,4);
	g.addEdge(1,0,4);
	g.addEdge(3,7,8);
	g.addEdge(7,3,8);
	g.addEdge(1,2,2);
	g.addEdge(2,1,2);
	g.addEdge(1,5,15);
	g.addEdge(5,1,15);
	g.addEdge(2,3,7);
	g.addEdge(3,2,7);
	g.addEdge(4,8,2);
	g.addEdge(8,4,2);
	g.addEdge(2,5,4);
	g.addEdge(5,2,4);
	g.addEdge(3,4,9);
	g.addEdge(4,3,9);
	g.addEdge(3,5,14);
	g.addEdge(5,3,14);
	g.addEdge(4,5,10);
	g.addEdge(5,4,10);
	g.addEdge(5,6,2);
	g.addEdge(6,5,2);
	g.addEdge(7,6,1);
	g.addEdge(6,7,1);
	g.addEdge(6,8,6);
	g.addEdge(8,6,6);
	g.addEdge(7,8,7);
	g.addEdge(8,7,7);

	g.prim();

	return 0;
}
