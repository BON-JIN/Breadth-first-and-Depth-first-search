#if !defined GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

#include "Vertex.h"
#include "Matrix.h"
#include "Edge.h"
#include "AdjacencyList.h"
#include "StackLinked.h"

#include "ListArray.h"
using CSC2110::ListArray;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include"QueueLinked.h"
using CSC2110::QueueLinked;

class Graph
{
	private:
		int max_num_vertices;
		ListArray<Vertex>* vertices;
		ListArray<Edge>* edges;
		QueueLinked<Vertex>* bfs_queue;
		QueueLinked<Vertex>* dfs_linked;
		StackLinked<Vertex>* stuck_topological;
	public:

		//constructor should accept the maximum number of vertices allowed in the graph
		Graph(int maxNumVertices);
		~Graph();
		//allow items (items are identified by String search keys) to be stored in the Graph vertices
		void addVertex(Vertex* item); 

		//add a directed edge between two vertices
		//void addEdge(String start_vertex_key, String end_vertex_key, double edge_weight);

		//perform a depth first search, adding items to a linked list
		QueueLinked<Vertex>* DFS(); 
		void dfs(int** edges, int count, ListArray<Vertex>* rows);
		//perform a breadth first search, adding items to a linked list
		QueueLinked<Vertex>* BFS();
		void bfs(QueueLinked<Vertex>* visited_queue, int count, AdjacencyList* v);
		//compute a topological sort using depth first search, return null if not a dag
		QueueLinked<Vertex>* topological_sort();

		int size();

		void readVertices(const char* file_name);
		void readEdges(const char* file_name);
		void displayVertices();
		void displayEdges();
		int getIndex(Vertex* vertex);
};

Graph::Graph(int maxNumVertices)
{
	this->max_num_vertices = maxNumVertices;
	this->vertices = new ListArray<Vertex>();
	this->edges = new ListArray<Edge>();
	this->bfs_queue = new QueueLinked<Vertex>();
	this->dfs_linked = new QueueLinked<Vertex>();
	this->stuck_topological = new StackLinked<Vertex>();
}
Graph::~Graph()
{
	delete &max_num_vertices;
	delete vertices;
}

int Graph::size()
{
	return max_num_vertices;
}

void Graph::addVertex(Vertex* item)
{
	vertices->add(max_num_vertices + 1, item);
	max_num_vertices = max_num_vertices + 1;
} 


void Graph::displayVertices()
{
	ListArrayIterator<Vertex>* itr = vertices->iterator();
	while(itr->hasNext())
	{
		Vertex* vertex = itr->next();
		vertex->displayVertex();
	}
}

void Graph::displayEdges()
{
	ListArrayIterator<Edge>* itr = edges->iterator();
	while(itr->hasNext())
	{
		Edge* edge = itr->next();
		edge->displayEdge();
	}
}


QueueLinked<Vertex>* Graph::DFS()
{
	Matrix* matrix = new Matrix(vertices, vertices, max_num_vertices);
 	matrix->displaySize();
	
	ListArray<Vertex>* rows = matrix->getRows();
	matrix->addEdges(this->edges);
	
  	int** edges = matrix->getEdges();
   
   int count = 0;
   dfs(edges, count, rows);

	return dfs_linked;
}
void Graph::dfs(int** edges, int count, ListArray<Vertex>* rows)
{
      Vertex* vertex = rows->get(count + 1);
      dfs_linked->enqueue(vertex);
      
      for(int r = 0; r < this->size(); r++)
      {
          edges[r][count] = 0;
      }

      for(int j = 0; j <this->size(); j++)
      {          
        
        if(edges[count][j] > 0)
        {  
            edges[count][j] = 0;
            edges[j][count] = 0;
            int c = j;
            dfs(edges, c, rows);
        }
      }

      stuck_topological->push(vertex);
}

QueueLinked<Vertex>* Graph::topological_sort()
{
	QueueLinked<Vertex>* topological = new QueueLinked<Vertex>(); 
	while(!stuck_topological->isEmpty())
	{
		Vertex* vertex = stuck_topological->pop();
		topological->enqueue(vertex);
	}
	return topological;
}

int Graph::getIndex(Vertex* vertex)
{
	int index;
	for(int i = 1; i <= this->size(); i++)
	{
			Vertex* compare = vertices->get(i);
			if(vertex->compareVertices(compare) == 0)
			{
				index = i;
				return index;
			}

	}

	return -1;

}


QueueLinked<Vertex>* Graph::BFS()
{
	QueueLinked<Vertex>* visited_queue = new QueueLinked<Vertex>();

	AdjacencyList* adjacency_list = new AdjacencyList(max_num_vertices);
	adjacency_list->addFirstItemsToAdjacency_list(vertices);
	adjacency_list->addToadjacency_list(vertices, edges);
	
	
	for(int i = 0; i < this->size(); i++)
	{
		QueueLinked<Vertex>* vertex = adjacency_list->adjacency_list[i];
		if(!(vertex->isEmpty()))
		{
			Vertex* vertex = adjacency_list->adjacency_list[i]->peek();
			if(vertex->isVisited() != 0)
			{
				bfs(visited_queue, i, adjacency_list);
			}
		}

	}

	return bfs_queue;
}

void Graph::bfs(QueueLinked<Vertex>* visited_queue, int count, AdjacencyList* v)
{	
	while(!(v->adjacency_list[count]->isEmpty()))
	{
		Vertex* vertex = v->adjacency_list[count]->dequeue();
		
		if(vertex->isVisited() != 0)
		{
			vertex->visit();
			visited_queue->enqueue(vertex);
		}
	}

	Vertex* visited_vertex = visited_queue->dequeue();

	bfs_queue->enqueue(visited_vertex);
	
	
	if(!(visited_queue->isEmpty()))
	{	
		visited_vertex = visited_queue->peek();
		count = this->getIndex(visited_vertex);
	}
	else
	{
		count = -1;
	}
	
	if(count > 0)
	{
		bfs(visited_queue, count - 1, v);
	}
	
}


void Graph::readVertices(const char* file_name)
{
    string vertex_name;

    fstream infile; 
    infile.open(file_name); 
    infile >> vertex_name;
 
    Vertex* vertex = new Vertex(vertex_name);
    this->vertices->add(1, vertex);

    int index = 2;
    while (!infile.eof())
    { 
       infile >> vertex_name;    
       Vertex* vertex = new Vertex(vertex_name);
       this->vertices->add(index, vertex);
       index++;
    }
   
   int max = this->vertices->size();
   this->max_num_vertices = max;

   infile.close();
}

void Graph::readEdges(const char* file_name)
{
	fstream infile; 
    infile.open(file_name); 
   
   
    string src;
    string des;
    string w;

    infile >> src;
    int index = 1;
    while (!infile.eof())
    {  
       infile >> des;
       infile >> w;

       Vertex* src_vertex = new Vertex(src);
       Vertex* des_vertex = new Vertex(des);
       int weight = atoi(w.c_str());

       Edge* edge = new Edge(src_vertex, des_vertex, weight);
       this->edges->add(index, edge);

       index++;
       infile >> src;
    }

    infile.close();
}
#endif