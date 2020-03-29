#include<iostream>
#include<string>
#include<queue>
#include<set>
#include<stack>
using namespace std;

class Data
{
public:
	int m, n, t;
	string* states, * actions;
	string startState;
	string endState;
	int** taransitionTable;
};

class Node
{
public:
	Node* parent;
	int state;
	int action;
	int pathCost;

	Node(Node* parent = nullptr, int state = -1, int action = -1, int pathCost = 0)
	{
		this->parent = parent;
		this->state = state;
		this->action = action;
		this->pathCost = pathCost;
	}
};

bool findInSet(set<Node*>& explored, Node* node)
{
	bool find = false;
	set <Node*> ::iterator itr;

	for (itr = explored.begin(); itr != explored.end(); ++itr)
	{
		if ((*itr)->state == node->state)
		{
			find = true;
			break;
		}
	}
	return find;
}

bool findInQueue(queue<Node*>& frontier, Node* node)
{
	bool find = false;
	queue<Node*> temp;
	while (!frontier.empty())
	{
		if ((*frontier.front()).state == (*node).state)
		{
			find = true;
		}
		temp.push(frontier.front());
		frontier.pop();
	}

	while (!temp.empty())
	{
		frontier.push(temp.front());
		temp.pop();
	}
	return find;
}

void input(Data& input)
{
	cin >> input.m >> input.n >> input.t;

	input.states = new string[input.m];
	input.actions = new string[input.n];
	input.taransitionTable = new int* [input.m];

	for (int i = 0; i < input.m; i++)
		input.taransitionTable[i] = new int[input.n];

	getchar();

	for (int i = 0; i < input.m; i++)
	{
		if (i == 0)
			cin.ignore();
		getline(cin, input.states[i]);
	}

	getchar();

	for (int i = 0; i < input.n; i++)
		getline(cin, input.actions[i]);

	getchar();

	for (int i = 0; i < input.m; i++)
		cin >> input.taransitionTable[i][0] >> input.taransitionTable[i][1] >> input.taransitionTable[i][2];

	getchar();
	getchar();
}

bool searchPath(Data data,int startState,int endState, set<Node*>explored)
{
	Node* startNode = new Node(nullptr, startState, -1, 0);

	queue<Node*> frontier;

	frontier.push(startNode);

	Node* node = nullptr;

	while (!frontier.empty())
	{
		node = frontier.front();
		frontier.pop();

		if ((*node).state == endState)
		{
			stack<int> recordAction;

			while (node->action != -1)
			{
				recordAction.push(node->action);
				node = node->parent;
			}

			while (!recordAction.empty())
			{
				switch (recordAction.top())
				{
				case 0:
					cout << "Clean";
					break;
				case 1:
					cout << "MoveToRoom1";
					break;
				case 2:
					cout << "MoveToRoom2";
					break;
				default:
					break;
				}
				recordAction.pop();
				if (!recordAction.empty())
					cout << "->";
				else
					cout << endl;
			}

			return true;
		}
		else
		{
			explored.insert(node);

			for (int i = 0; i < data.n; i++)
			{
				Node* tempNode = new Node(node, data.taransitionTable[(*node).state][i], i, ((*node).pathCost) + 1);

				if (!findInSet(explored, tempNode))
				{
					if (!findInQueue(frontier, tempNode))
					{
						frontier.push(tempNode);
					}
				}

			}
		}
	}
	return false;
}

int main()
{
	freopen("input.txt", "r", stdin);

	string startAndEndState;
	Data data;
	input(data);
	

	for (int i = 0; i < data.t; i++)
	{
		set<Node*>explored;
		bool flag = false;
		getline(cin, startAndEndState);

		data.startState = startAndEndState.substr(0, (startAndEndState.find("\t")));

		data.endState = startAndEndState.substr((startAndEndState.find("\t")) + 1);

		int startStateInt = 0;

		int endStateInt = 0;

		for (int j = 0; j < data.m; j++)
		{
			if (!data.startState.compare(data.states[j]))
				break;
			startStateInt++;
		}

		for (int j = 0; j < data.m; j++)
		{
			if (!data.endState.compare(data.states[j]))
				break;
			endStateInt++;
		}

		if (!searchPath(data, startStateInt, endStateInt, explored))
			cout << "Path NOT Find" << endl;
		
	}
	return 0;
}