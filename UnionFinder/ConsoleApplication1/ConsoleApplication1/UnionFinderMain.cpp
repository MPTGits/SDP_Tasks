// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "UnionFinder.h"

using namespace std;

int creatingSocialConnections(int numPeople, int numConnections, fstream &SocialNetworkFile) {
	UnionFinder SocialNetwork(numPeople);
	//Starting a timer when the netowrk is created
	clock_t timeOfFileCreation = clock();
	int personOne, personTwo,timeOfFullConectivity=-1,currConnectivityTime;
	bool flag = true;
	//Loop that makes all the connection betwen people and writes them to the file 
	for (int i = 0; i < numConnections; ++i) {
		cout << "Enter number of person one:";
		cin >> personOne;
		SocialNetworkFile << personOne;
		cout << endl;
		cout << "Enter number of person to connect to:";
		cin >> personTwo;
		SocialNetworkFile <<" "<< personTwo;
		clock_t currTime = clock();
		//Calculates the timem that has passed since the network was created and writes the time of connections to the file
		currConnectivityTime = (currTime - timeOfFileCreation) / 1000;
		cout << "Connection successful!";
		SocialNetworkFile<< "=>Connection successful at time:"<<currConnectivityTime<<'\n';
		cout << endl;
		SocialNetwork.connect(personOne, personTwo);
		//Check if all the users are connected already and if they are stores the time at which this occured 
		for (int i = 0; i < numPeople&&flag == true; ++i) {
			if (!SocialNetwork.checkConnection(0, i)) {
				break;
			}
			if ((i + 1) == numPeople) {
				timeOfFullConectivity = currConnectivityTime;
				flag = false;
			}
		}
	}
	return timeOfFullConectivity;
}


int main()
{
	/* TESTS
	UnionFinder uf(6);
	std::cout << uf << std::endl;
	uf.connect(0, 5);
	uf.connect(4, 5);
	uf.connect(4, 2);
	uf.connect(0, -3);
	uf.connect(3, 1);
	std::cout << uf.getRoot(4) << std::endl;
	std::cout << uf << std::endl;
	std::cout << uf.getRoot(2) << std::endl;
	std::cout << uf.checkConnection(5, 4) << std::endl;
	*/
	/*Имаме социална мрежа, в която между всеки двама души може да се установи двупосочна връзка. Нека също така имаме група от хора, които са част от тази социална мрежа и имаме информация за това кога връзките между тях са били създадени (в брой часове от създаването на социалната мрежа).

Нека имаме файл с последователен достъп, в който са записани на отделни редове първо броя на хората, които ще разглеждаме, после броя на връзките, които са създадени между хората в групата, както и информация кога е създадена всяка една връзка спрямо създаването на социалната мрежа.

Напишете програма, която пресмята дали и в кой момент всички хора от групата са били свързани или директно, или чрез друг човек, с всички останали в групата.

Примерен файл:

5
7
7: 0 4
9: 4 2
10: 3 1
15: 2 0
17: 1 4
20: 2 3
31: 2 4

Изход: 17
*/

	fstream SocialNetworkFile;
	SocialNetworkFile.open("PeopleInfo.txt", ios::in | ios::out);
	int numPeople, numConnections;
	cout << "Input the number of people in the social network:";
	cin >> numPeople;
	SocialNetworkFile << numPeople << '\n';
	cout << endl;
	cout << "Enter the number of current connections:";
	cin >> numConnections;
	SocialNetworkFile << numConnections << '\n';
	cout << endl;
	//Function that creates the connections and the time they were made(returns the time that full connectivity was achived)! 
	int fullConnectionTime=creatingSocialConnections(numPeople,numConnections,SocialNetworkFile);
	SocialNetworkFile << "Full connectivity time is:" << fullConnectionTime;
	SocialNetworkFile.close();
	



    return 0;
}
