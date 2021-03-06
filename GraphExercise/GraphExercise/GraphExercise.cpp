// GraphExercise.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Graph.h"
#include "LList.h"
#include "Node.h"
//Да се намерят свързаните копоненти на един граф
//template <typename T>
void connectedComponent(int node, LList<int>& l,Graph<int> g,bool * visited) {
	visited[node] = 1;
	l.insertToEnd(node);
	Node<int> * ptr = g.getVertexPointer(node);
	ptr = ptr->next;
	while(ptr) {
		if (!visited[ptr->data]) {
			visited[ptr->data] = 1;
			connectedComponent(ptr->data, l,g, visited);
		}
		ptr = ptr->next;
	}
}


void connectedComponentsOfGraph(Graph<int> &g ,LList<LList<int>> resultList) {
	int length = g.getVertices().length();
	bool * visited = new bool[length]();
	for (int i = 0; i <= length; ++i) {
		if (!visited[i]) {
			LList<int> tmpList;
			connectedComponent(i, tmpList, g , visited);
			tmpList.print();
			resultList.insertToEnd(tmpList);
		}
	}
	delete visited;

}



int main()
{
	Graph<int> g;
	g.addVertex(0);
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);

	g.addEdge(3, 4);
	g.addEdge(4, 2);
	g.addEdge(2, 3);
	g.addEdge(4, 0);
	g.addEdge(0, 1);
	g.addEdge(1, 0);
	g.addEdge(0, 5);
	
	LList<LList<int>> l;
	connectedComponentsOfGraph(g, l);
    return 0;
}

