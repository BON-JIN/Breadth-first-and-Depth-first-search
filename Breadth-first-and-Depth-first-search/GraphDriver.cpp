#include <iostream>


#include "Graph.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Edge.h"
#include "AdjacencyList.h"

#include "ListArray.h"
using CSC2110::ListArray;

#include"QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include"QueueLinked.h"
using CSC2110::QueueLinked;

using namespace std;

int main(int argc, char *argv[])
{
	// Insert every city into the list array

	cout << endl << "Begining" << endl;
	Graph* graph = new Graph(0);
	
	
	graph->readVertices(argv[1]);
	graph->readEdges(argv[2]);

	
	QueueLinked<Vertex>* dfs = graph->DFS();
	QueueLinked<Vertex>* topo = graph->topological_sort();
	
	cout << endl << "DFS" << endl;
	cout << "------------------------------" << endl;
	while(!(dfs->isEmpty()))
	{
		Vertex* vertex = dfs->dequeue();
		vertex->displayVertex();
	}
	
	cout << endl << "TOPOLOGICAL SORT" << endl;
	cout << "------------------------------" << endl;
	while(!(topo->isEmpty()))
	{
		Vertex* vertex = topo->dequeue();
		vertex->displayVertex();
	}

	cout << endl << "BFS" << endl;
	cout << "------------------------------" << endl;
	QueueLinked<Vertex>* bfs = graph->BFS();	

	while(!(bfs->isEmpty()))
	{
		Vertex* vertex = bfs->dequeue();
		vertex->displayVertex();
	}
	

	cout << endl << "Thank you!" << endl;

	return 0;
}
