#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	Graph map;
	
	return 0;
}

class Node
{
	string name;
	vector<Node*> connectedTo;
	bool visited;

public:
	Node(string n)
	{
		name = n;
	}

	string getName()
	{
		return name;
	}

	bool addDest(string dest)
	{

	}

	bool addDest(Node* dest)
	{

	}
};

class Graph
{
	vector<Node> cities;

public:
	Graph(){};

	bool addNode(string nde, string dest)
	{
		bool nExist, dExist;
		int nIndex, dIndex;

		for(int i = 0, nExist = false, dExist = false; i < cities.size() || (nExist && dExist); i++)
		{
			if(!nExist && !nde.compare(cities[i].getName()))
			{
				nExist = true;
				nIndex = i;
			}

			if(!dExist && !dest.compare(cities[j].getName()))
			{
				dExist = true;
				dIndex = i;
			}
		}

		cities[nIndex].addDest(&cities[dIndex]);
	}
};