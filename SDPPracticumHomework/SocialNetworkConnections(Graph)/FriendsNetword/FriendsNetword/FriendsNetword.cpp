// FriendsNetword.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FriendsRecommandations.h"


int main()
{
	//Примерния граф,който ни е дадаен
	User us0("Ivan0");
	User us1("Ivan1");
	User us2("Ivan2");
	User us3("Ivan3");
	User us4("Ivan4");
	User us5("Ivan5");
	User us6("Ivan6");
	User us7("Ivan7");
	User us8("Ivan8");
	User us9("Ivan9");
	User us10("Ivan10");
	User us11("Ivan11");
	User us12("Ivan12");
	


	Graph<User> g;
	g.addVertex(us0);
	g.addVertex(us1);
	g.addVertex(us2);
	g.addVertex(us3);
	g.addVertex(us4);
	g.addVertex(us5);
	g.addVertex(us6);
	g.addVertex(us7);
	g.addVertex(us8);
	g.addVertex(us9);
	g.addVertex(us10);
	g.addVertex(us11);
	g.addVertex(us12);

	g.addEdge(us0, us1);
	g.addEdge(us0, us2);
	g.addEdge(us0, us12);
	g.addEdge(us1, us2);
	g.addEdge(us1, us4);
	g.addEdge(us1, us3);
	g.addEdge(us1, us5);
	g.addEdge(us1, us0);
	g.addEdge(us2, us0);
	g.addEdge(us2, us5);
	g.addEdge(us2, us4);
	g.addEdge(us2, us1);
	g.addEdge(us12, us0);
	g.addEdge(us12, us5);
	g.addEdge(us12, us6);
	g.addEdge(us3, us7);
	g.addEdge(us3, us1);
	g.addEdge(us4, us1);
	g.addEdge(us4, us2);
	g.addEdge(us4, us8);
	g.addEdge(us5, us1);
	g.addEdge(us5, us2);
	g.addEdge(us5, us12);
	g.addEdge(us5, us6);
	g.addEdge(us5, us8);
	g.addEdge(us5, us9);
	g.addEdge(us5, us10);
	g.addEdge(us5, us11);
	g.addEdge(us6, us5);
	g.addEdge(us6, us12);
	g.addEdge(us7, us3);
	g.addEdge(us8, us3);
	g.addEdge(us8, us4);
	g.addEdge(us8, us5);
	g.addEdge(us9, us5);
	g.addEdge(us10, us5);
	g.addEdge(us11, us5);

	LList<User> l;

	suggestFriends(g, us0, 7);
	
    return 0;
}

