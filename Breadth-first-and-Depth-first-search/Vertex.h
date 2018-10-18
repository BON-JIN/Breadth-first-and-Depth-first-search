#if !defined VERTX_H
#define VERTX_H

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>

#include"QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArray.h"
using CSC2110::ListArray;

#include "ReadFile.h"
using CSC2110::ReadFile;

#include "Text.h"
using CSC2110::String;

using namespace std;

class Vertex
{
   private:
      string vertex;
      int visited;
   public:
      Vertex(string vertex);
      ~Vertex();

      void visit();
      void noVisit();
      int isVisited();

      static ListArray<Vertex>* readVertices(const char* file_name);

      void displayVertex();
      string getKey();
      int compareVertices(Vertex* vertex_compare);
};

Vertex::Vertex(string vertex)
{
   this->vertex = vertex;
   this->visited = -1;
}

int Vertex::isVisited()
{
   return this->visited;
}
void Vertex::noVisit()
{
   this->visited = -1;
}

void Vertex::visit()
{
   this->visited = 0;
}

Vertex::~Vertex()
{
   delete &vertex;
}
 
int Vertex::compareVertices(Vertex* vertex_compare)
{
   string vertex1 = this->getKey();
   string vertex2 = vertex_compare->getKey();
   return vertex1.compare(vertex2);
}

string Vertex::getKey()
{
   return vertex;
}

void Vertex::displayVertex()
{
   cout << vertex << endl;
}

#endif
