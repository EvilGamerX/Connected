#include <iostream>
#include <fstream>
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
		//cout << "Adding " << dest->getName() << " to " << this->getName()<< endl;
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
		//cout << this->getName() << " | " << cmp->getName() << endl;
		return !(this->getName().compare(cmp->getName()));
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
		int nIndex = -1, dIndex = -1;
		
		if(!cities.empty())
		{
			for(int i = 0; i < cities.size() && !(nExist && dExist); i++)
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
		}

		//cout << nIndex << " | " << dIndex << " | " << nExist << " | " << dExist << endl;

		if(nExist && dExist)
		{
			//cout << cities[nIndex]->getName() << " | " << cities[dIndex]->getName() << endl;
			cities[nIndex]->addDest(cities[dIndex]);
			cities[dIndex]->addDest(cities[nIndex]);

			//cout << endl << cities[nIndex]->numConnectedTo() << " | "  << cities[dIndex]->numConnectedTo() << endl;
		}else if(nExist && !dExist)
		{
			cities.push_back((new Node(dest)));
			
			addNode(cities[nIndex]->getName(), cities.back()->getName());
		}else if(!nExist && dExist)
		{
			cities.push_back((new Node(nde)));

			addNode(cities.back()->getName(), cities[dIndex]->getName());
		}else
		{
			cities.push_back((new Node(nde)));
			dIndex = cities.size();
			cities.push_back(new Node(dest));
			
			addNode(cities[dIndex - 1]->getName(), cities[dIndex]->getName());
		}

		return true;
	}

	bool canTravelTo(string start, string dest)
	{
		bool nExist = false, dExist = false, ret = false;
		int nIndex, dIndex;

		for(int i = 0; i < cities.size() && !(nExist && dExist); i++)
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
			//cout << nIndex << " | " << dIndex << " | " << cities[nIndex]->getName() << endl;
			//cout << endl << cities[nIndex]->numConnectedTo() << " | "  << cities[dIndex]->numConnectedTo() << endl;
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
		bool ret = false;

		//cout << start->getName() << " | " << dest->getName() << endl;
		//cout << endl << start->getName() << "=" << start->numConnectedTo() << " | "  << dest->getName() << "=" << dest->numConnectedTo() << endl;

		if(!(start) || !(dest))
		{
			return false;
		}

		if(start->getVisited())
		{
			return false;
		}

		//cout << "NOT VISITED" << endl;
		start->visit();
		//cout << "VISITED" << endl;

		for(int i = 0; i < start->numConnectedTo() && !ret; i++)
		{
			//cout << i << " | " << start->numConnectedTo() << endl;

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

	if(argc != 4)
	{
		cout << "Please use the proper format" << endl;
		cin.ignore();
		exit(0);
	}


	ifstream file(argv[1]);

	if(!file.is_open())
	{
		cout << "ERR: Could not open file.  Please try again." << endl;
		cin.ignore();
		exit(0);
	}

	string buff;
	string c1;
	string c2;
	int pos;

	while(file.good())
	{
		getline(file, buff);

		pos = buff.find(", ");
		c1 = buff.substr(0, pos);
		c2 = buff.substr(pos + string(", ").length(), buff.length());

		roadMap.addNode(c1, c2);
	}

	if(roadMap.canTravelTo(argv[2], argv[3]))
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	cin.ignore();

	return 0;
}