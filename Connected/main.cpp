#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
	string name;
	vector<Node*> connectedTo;
	bool visited;

public:
	Node(string n)
	{
		name = string(n);
		visited = false;
	}

	string getName()
	{
		return name;
	}
	void addDest(Node* dest)
	{
		connectedTo.push_back(dest);
	}
	bool getVisited()
	{
		return visited;
	}
	int numConnectedTo()
	{
		return connectedTo.size();
	}
	Node* connectedAt(int i)
	{
		if(i < numConnectedTo() && i >= 0)
		{
			return connectedTo[i];
		}else
		{
			return connectedTo.back();
		}
	}
	bool compareTo(Node* cmp)
	{
		return (name == cmp->getName());
	}
	void visit()
	{
		visited = true;
	}
	void leave()
	{
		visited = false;
	}
};

class Graph
{
	vector<Node*> cities;

public:
	Graph(){};

	bool addNode(string nde, string dest)
	{
		bool nExist = false, dExist = false;
		int nIndex, dIndex;
		
		cout << cities.size() << endl;
		
		if(!cities.empty())
			for(int i = 0; i < cities.size() || (nExist && dExist); i++)
			{
				if(!nExist && !cities[i]->getName().compare(nde))
				{
					nExist = true;
					nIndex = i;
				}

				if(!dExist && !cities[i]->getName().compare(dest))
				{
					dExist = true;
					dIndex = i;
				}
			}
		
		if(nExist && dExist)
		{
			cities[nIndex]->addDest(cities[dIndex]);
		}else if(nExist && !dExist)
		{
			cities.push_back((new Node(dest)));
			cities[nIndex]->addDest(cities.back());
		}else if(!nExist && dExist)
		{
			cities.push_back((new Node(nde)));
			cities.back()->addDest(cities[dIndex]);
		}else
		{
			cities.push_back((new Node(nde)));
			cities.back()->addDest((new Node(dest)));
			cities.push_back(cities.back()->connectedAt(-1));
		}

		return true;
	}

	bool canTravelTo(string start, string dest)
	{
		bool nExist, dExist, ret;
		int nIndex, dIndex;

		for(int i = 0, nExist = false, dExist = false; i < cities.size() || (nExist && dExist); i++)
		{
			if(!nExist && !cities[i]->getName().compare(start))
			{
				nExist = true;
				nIndex = i;
			}

			if(!dExist && !cities[i]->getName().compare(dest))
			{
				dExist = true;
				dIndex = i;
			}
		}

		if(nExist && dExist)
		{
			ret = canTravelTo(cities[nIndex], cities[dIndex]);
		}else
		{
			ret = false;
		}

		for(int i = 0; i < cities.size(); i++)
		{
			cities[i]->leave();
		}

		return ret;
	}

	bool canTravelTo(Node* start, Node* dest)
	{
		bool ret;
		
		if(start->getVisited())
		{
			return false;
		}

		for(int i = 0, ret = false; i < start->numConnectedTo() && !ret; i++)
		{
			start->connectedAt(i)->visit();

			if(start->connectedAt(i)->compareTo(dest))
			{
				ret = true;
			}else
			{
				ret = canTravelTo(start->connectedAt(i), dest);
			}
		}

		return ret;
	}

	string getCities()
	{
		string ret = "";

		for(int i = 0; i < cities.size(); )
		{
			ret += cities[i]->getName();

			if(++i == cities.size())
			{
				ret += ".";
			}else
			{
				ret += ", ";
			}
		}

		return ret;
	}
};

int main(int argc, char** argv)
{
	Graph roadMap = Graph();

	roadMap.addNode("Whoop", "Swoop");
	roadMap.addNode("Whoop", "Doop");
	roadMap.addNode("Whoop", "Poop");
	roadMap.addNode("Coop", "Doop");
	roadMap.addNode("Loop", "Snoop");

	cout << roadMap.getCities() << endl;

	cin.ignore();

	return 0;
}