#pragma once
#include "Node.h"
#include "LList.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "User.h"

//DISCLAIMER:Знам че с матрици излиза дългичко,но ми беше интересно да го направя я теоремата за броя маршрути :D

//In case of an edge we add 1 to the matrix (we consider that every vertex has and edge to itself)
void inputMatirx(std::vector<std::vector<int> > &friendsMatrix,Graph<User> &friendsGraph,std::unordered_map<int,User> mapOfUsers) {
	for (int i = 0; i < friendsMatrix.size(); ++i) {
		for (int j = 0; j < friendsMatrix.size(); ++j) {
			if (friendsGraph.hasEdge(mapOfUsers[i],mapOfUsers[j])||(mapOfUsers[i] == mapOfUsers[j])) {
				friendsMatrix[i][j] = 1;
			}
		}
		std::cout<<std::endl;
	}
}
//Printing the adjacnet matrix
void printMatrix(std::vector<std::vector<int> > friendsMatrix) {
	
	for (int i = 0; i < friendsMatrix.size(); ++i) {
		for (int j = 0; j < friendsMatrix.size(); ++j) {
			std::cout << friendsMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
//Multiply matrix so we can see the number of paths with lenght 'k' where k is the power of the matrix
void multiplyMatrixByItself(std::vector<std::vector<int> > mat1, std::vector<std::vector<int> > mat2, std::vector<std::vector<int> > &res)
{
	int i, j, k;
	for (i = 0; i < mat1.size(); i++)
	{
		for (j = 0; j < mat1.size(); j++)
		{
			int startValue = res[i][j];
			for (k = 0; k < mat1.size(); k++) {
				res[i][j] += mat1[i][k] * mat2[k][j];
			}
			res[i][j] -= startValue;
		}

	}
}
//Checking if member of list 
bool member(const User& x, LList<User>& l) {
	l.iterStart();
	Node<User>* currEl = l.iterNext();
	while (currEl&&currEl->data != x) currEl = currEl->next;
	return currEl != nullptr;
}




//We create the unordered map by indexing it as we BFS the Graph depending on our starting vertex(User)
void makingUnorderedMap(const User& user, Graph<User>& friendshipGraph, std::unordered_map<int, User> &mapedUsers, LList<User> &l) {
	int currIndex = 0;
	std::queue<User> q;
	q.push(user);
	l.insertToEnd(user);
	while (!q.empty()) {
		User parentUser = q.front();
		mapedUsers[currIndex] = parentUser;
		++currIndex;
		q.pop();
		Node<User>* currUser = friendshipGraph.getVertexPointer(parentUser);
		currUser = currUser->next;
		while (currUser) {
			if (!member(currUser->data, l)) {
				q.push(currUser->data);
				l.insertToEnd(currUser->data);
			}
			currUser = currUser->next;
		}
	}
}




//We multiply the matrix so we get diffrent levels of friendship and we print our from higest to lowest valuse of 
//the row of the matrix we want the user to be checked,we also add the already printed users to a list so we dont print them again
void suggestFriends(Graph<User> &frinedGraph,User &user,int numberOfSuggestions) {
	std::unordered_map<int, User> mapedUserToIndexes;
	LList<User> tmpList;
	makingUnorderedMap(user, frinedGraph, mapedUserToIndexes, tmpList);
	
	int numberOfuserInNetwork = frinedGraph.getVertices().length();
	std::vector<std::vector<int> > matrixOfAdjacent(numberOfuserInNetwork);
	
	for (int i = 0; i < numberOfuserInNetwork; i++) {
		matrixOfAdjacent[i].resize(numberOfuserInNetwork);
	}
	inputMatirx(matrixOfAdjacent,frinedGraph,mapedUserToIndexes);
	//Now we will find the row of the user we need to suggest friends
	int neededRow;
	LList<User> alreadyCheckedVertices;
	for (int i = 0; i < numberOfuserInNetwork; ++i) {
		if (mapedUserToIndexes[i] == user) {
			neededRow = i;
			break;
		}
	}
	//We add the users with value 1 to the list as they are dirrect friends to our user
	for (int i = 0; i < numberOfuserInNetwork; ++i) {
		if (matrixOfAdjacent[neededRow][i] == 1) {
			alreadyCheckedVertices.insertToEnd(mapedUserToIndexes[i]);
		}
	}
	int currNumberOfSuggestions = 0,currentMax=0;
	std::vector<std::vector<int> > resultMatrix(numberOfuserInNetwork);
	for (int i = 0; i < numberOfuserInNetwork; i++) {
		resultMatrix[i].resize(numberOfuserInNetwork);
	}
	resultMatrix = matrixOfAdjacent;
	//We go in the cycle until we reach the number of user we need
	while (currNumberOfSuggestions < numberOfSuggestions) {
		//Вдигаме степента на матрицата с 1 
		multiplyMatrixByItself(resultMatrix, matrixOfAdjacent, matrixOfAdjacent);

		for (int i = 0; i < numberOfuserInNetwork; ++i) {
			if (currNumberOfSuggestions == numberOfSuggestions) break;
			int currMaxIndex;
			for (int j = 0; j < numberOfuserInNetwork; ++j) {
				if ((matrixOfAdjacent[neededRow][j] > currentMax)&&(!member(mapedUserToIndexes[j],alreadyCheckedVertices))) {
					currentMax =matrixOfAdjacent[neededRow][j];
					currMaxIndex = j;
				}
			}
			if (currentMax != 0) {
				std::cout << mapedUserToIndexes[currMaxIndex].getName() << " ";
				++currNumberOfSuggestions;
				if (currNumberOfSuggestions == numberOfSuggestions) break;
				alreadyCheckedVertices.insertToEnd(mapedUserToIndexes[currMaxIndex]);
				currentMax = 0;
			}
		}
	}



}


