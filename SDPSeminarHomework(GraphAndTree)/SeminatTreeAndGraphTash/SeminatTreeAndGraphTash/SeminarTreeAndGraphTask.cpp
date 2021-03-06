// SeminarTreeAndGraphTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinTree.h"
#include "LList.h"
#include <vector>
#include <unordered_map>
#include <iostream>

//Checks if an int  value is in a vector 
bool inVector(std::vector<int> vec, int value) {
	for (int i = 0; i < vec.size(); ++i) {
		if (value == vec[i]) {
			return true;
		}
	}
	return false;
}



//An algorithm that takes a list and checks if the sequence of elements in it can be traveresd in the adjacent matrix
//the algorithm stores the valuse in a vector and after that checks for each combination of values that have been hashed if it
//is possiable to make it to the next vertex.
bool listEqualToVector(std::vector<std::vector<bool>> adjacentMatrix, LList<char> lst, std::unordered_map<int, char> map) {
	
	lst.iterStart();
	bool isLetterEvenInHash = false;
	bool foundAMatch=false;
	std::vector<int> currRow;
	std::vector<int> currCol;
	Node<char>* tmp = lst.iterNext();
	
	while(tmp){
		for (int i = 0; i < adjacentMatrix.size(); ++i) {
			if (map[i] == tmp->data) {
				currRow.push_back(i);
				isLetterEvenInHash = true;
			}
		}
		tmp = tmp->next;
		if (!isLetterEvenInHash) return false;
		//If the pointer is null we already gone through all of the vertex from the list
		if (tmp == nullptr) return true;
		isLetterEvenInHash = false;
		
		for (int j = 0; j < adjacentMatrix.size(); ++j) {
			if (map[j] == tmp->data) {
				currCol.push_back(j);
				isLetterEvenInHash = true;
			}
		}
		if (!isLetterEvenInHash) return false;

		for (int i = 0; i < currRow.size();++i) {
			for (int j = 0; j < currCol.size(); ++j) {
				if (adjacentMatrix[currRow[i]][currCol[j]]) {
					foundAMatch = true;
					break;
				}
			}
			if (foundAMatch) break;
		}
		
		if (!foundAMatch) return false;
		//Reseting the flags and the index keeping vectors
		isLetterEvenInHash = false;
		foundAMatch = false;
		currCol.clear();
		currRow.clear();
}
	return true;

}

//----------------------------GRAPH RERESENTATION AS ADJACENT MATRIX-------------------------------------------------------------------
//The basic idea is we go throught our hashtable,if we find more than one duplicate we ask the user to pick one of the vertex index 
//by showing him the connections the vertex has for better orientation,if there aren't any duplicates we return the index of the only occurence of the
//vertex
int checkForDuplicates(std::unordered_map<int, char> &hashedGraph, char value, std::vector<std::vector<bool>> adjacentMatrix) {
	int duplicates = -1;
	std::vector<int> duplicatesIndexer;
	for (int i = 0; i < adjacentMatrix.size(); ++i) {
		if (hashedGraph[i] == value) {
			duplicates++;
			duplicatesIndexer.push_back(i);
		}

	}
	if (duplicates > 0) {
		std::cout << "There are duplicated values chose which one you intend:";
		std::cout << std::endl;
		for (int i = 0; i < duplicatesIndexer.size(); ++i) {
			std::cout << "Vertex conections at index " << duplicatesIndexer[i] << ":";
			for (int j = 0; j < adjacentMatrix[duplicatesIndexer[i]].size(); ++j) {
				std::cout << adjacentMatrix[duplicatesIndexer[i]][j] << " ";
			}
			std::cout << std::endl;
		}
		int pickedVertex;
		do {
			std::cout << "Pick a valid index:";
			std::cin >> pickedVertex;
			std::cout << std::endl;
		}while (inVector(duplicatesIndexer, pickedVertex));
		return pickedVertex;
	}
	return duplicatesIndexer[0];
}

void creatingAGraphWithHashing(std::vector<std::vector<bool>> &adjacentMatrix, std::unordered_map<int, char> &hashedGraph) {
	char input,vertex;
	int indexer = 0;
	//Ading vertecies to the graph and hashing them to a numeric value so 
	//if even there are duplicates they will have diffrent numeric values
	do {
		std::cout << "Enter vertex char value:";
		std::cin >> vertex;
		std::cout << std::endl;
		hashedGraph[indexer] = vertex;
		++indexer;
		std::cout << "Enter more?(y/n):";
		std::cin >> input;
		std::cout << std::endl;
	} while (input == 'y');
	//Creating a new matrix with the size of the edges (indexer x indexer) and making our adjacent matrix equal to it
	adjacentMatrix.clear();
	std::vector<std::vector<bool>> newAdjacentMatrix(indexer);
	for (int i = 0; i < indexer; ++i) {
		newAdjacentMatrix[i].resize(indexer);
	}
	adjacentMatrix = newAdjacentMatrix;
	//Here we add the edges and in case of a duplicate we ask the user to pick one of the nodes;
	char vertex1, vertex2;
	do {
		std::cout << "Enter edge vertex 1:";
		std::cin >> vertex1;
		std::cout << std::endl;
		std::cout << "Enter edge vertex 2:";
		std::cin >> vertex2;
		std::cout << std::endl;
		int i=checkForDuplicates(hashedGraph, vertex1, adjacentMatrix);
		int j=checkForDuplicates(hashedGraph, vertex2, adjacentMatrix);
		adjacentMatrix[i][j] = 1;
		std::cout << "Enter more?(y/n):";
		std::cin >> input;
		std::cout << std::endl;
	} while (input == 'y');

}

//Function that removes the last element of a list
template <typename T>
void removeLast(LList<T> &l) {
	l.iterStart();
	Node<T>* tmpNode = l.iterNext();
	while (tmpNode->next) {
		tmpNode = l.iterNext();
	}
	T x;
	l.deleteElem(tmpNode, x);
}

//---------------STORING ALL THE PATHS FROM THE ROOT TO THE LEAVES IN A VECTOR OF LISTS-----------
void allPathsOfTree(BinTree<char> root, LList<char>& currPath,std::vector<LList<char>> &allPaths) {
	if (root.getRootPtr() == nullptr) {
		return;
	}
	if (root.getLeftTree().getRootPtr() == nullptr&&root.getRightTree().getRootPtr()==nullptr) {
		currPath.insertToEnd(root.getRootData());
		allPaths.push_back(currPath);
		removeLast(currPath);
		return;
	}
	currPath.insertToEnd(root.getRootData());
	allPathsOfTree(root.getLeftTree(),currPath,allPaths);
	allPathsOfTree(root.getRightTree(),currPath,allPaths);
	removeLast(currPath);
}
//------------------------------------MAIN FUNCTION THAT PRINTS THE NEEDED RESULTS----------------------------------------
void printingAllWithRepititions(BinTree<char> tree, std::vector<std::vector<bool>> &graph,std::unordered_map<int,char> map) {
	std::vector<LList<char>> allPaths;
	LList<char> currPath;
	allPathsOfTree(tree, currPath, allPaths);
		for (int j = 0; j < allPaths.size(); ++j) {
				if (listEqualToVector(graph, allPaths[j], map)) {
					allPaths[j].print();
				}
			}
	}



int main()
{
	//Въвеждането се извършва то функции,но поради изискването ще изглежда малко по-грубо на ръка :D

	//Това по-долу е конкретен пример ако дадените върхове се има впредвид че са въведени в следния ред:
	//l,a,b,f,g,c,e,a,n
	//следователно и в този ред ще бъдат хеширани според моята функция!

	std::vector<std::vector<bool>> graph = {	{ 0,1,0,0,0,0,0,0,0 },
												{ 0,0,1,0,0,0,1,0,0 },
												{ 0,0,0,1,0,1,0,0,0 },
												{ 0,0,0,0,1,0,0,0,0 },
												{ 0,0,0,0,0,0,0,0,0 },
												{ 0,0,0,0,0,0,0,0,0 },
												{ 0,0,0,0,1,0,0,0,0 },
												{ 0,0,0,0,0,0,1,0,0 },
												{ 0,0,0,0,0,0,0,1,0 }, };
	//Хешираните стойности											
	std::unordered_map<int, char> map;
	map[0] = 'l';
	map[1] = 'a';
	map[2] = 'b';
	map[3] = 'f';
	map[4] = 'g';
	map[5] = 'c';
	map[6] = 'e';
	map[7] = 'a';
	map[8] = 'n';
	
	
	
	TNode<char> *leaf1=new TNode<char>('n');
	TNode<char> *leaf2=new TNode<char>('h');
	TNode<char> *leaf3=new TNode<char>('g');
	TNode<char> *leaf4=new TNode<char>('c');
	TNode<char> *leaf5 = new TNode<char>('l');
	TNode<char> *nodeLvl11 = new TNode<char>('f', leaf1);
	TNode<char> *nodeLvl12 = new TNode<char>('d', leaf2);
	TNode<char> *nodeLvl21 = new TNode<char>('b', leaf4,nodeLvl11);
	TNode<char> *nodeLvl22 = new TNode<char>('e', nodeLvl12,leaf3);
	TNode<char> *NodeLvl31 = new TNode<char>('a', nodeLvl21, nodeLvl22);
	TNode<char> *root = new TNode<char>('l', NodeLvl31);
	//Направих конструктора на BinTree да приема и указател(а да не е само дефаутен) 
	//за да е по-лесно правенето на дърво на ръка
	BinTree<char> tree(root);

	//Примеррът е доста сходен на дадения в условето но в моят над 'a' дървото а има още един връх 'l',който е корен
	//и в графа има освен дадените ребра също така и реброто -> (а(горно),e)

	printingAllWithRepititions(tree, graph, map);

	
    return 0;
}

