#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
ifstream fin("date.in");

bool isOK;

class Automata {
	int noOfNodes;
	int initialState, noOfFinalStates, noOfEdges;
	int* finalStates;
	vector< pair< list<int>, list<int> > > states;
public:
	int getInitialState() {
		return initialState;
	}
	Automata() {
		fin >> noOfNodes;
		fin >> initialState;
		fin >> noOfFinalStates;
		finalStates = new int[noOfFinalStates];
		for (int i = 0; i < noOfFinalStates; i++)
			fin >> finalStates[i];
		fin >> noOfEdges;
		states = vector< pair< list<int>, list<int> > >(noOfNodes);
		for (int i = 0; i < noOfEdges; i++) {
			int a, b;
			char c;
			fin >> a >> b >> c;
			if (c == 'a') {
				states[a].first.push_back(b);
			}
			else {
				states[a].second.push_back(b);
			}
		}
	}
	bool isFinalState(int state) {
		for (int i = 0; i < noOfFinalStates; i++)
			if (finalStates[i] == state)
				return true;
		return false;
	}
	bool checkIfLambda(string word) {
		if (word == "lambda")
			return true;
		return false;
	}
	void checkInput(string word, int index, int currentState){
		
		if (index == word.length() - 1){
			if (this->isFinalState(currentState))
				isOK = true;
			else
				isOK = false;
		}
		else {
			if (word[index] == 'a') {
				for (auto nextState : states[currentState].first)
					if(!isOK)
						this->checkInput(word, index + 1, nextState);
			}
			else {
				for (auto nextState : states[currentState].second)
					if(!isOK)
						this->checkInput(word, index + 1, nextState);
			}
		}
	}
};

int main()
{
	Automata a;
	int noOfWords;
	fin >> noOfWords;
	for (int i = 0; i < noOfWords; i++) {
		string str;
		fin >> str;
		if (a.checkIfLambda(str))
			cout << "OK\n";
		else {
			isOK = false;
			a.checkInput(str, 0, a.getInitialState());
			if(isOK)
				cout << "OK";
			else
				cout << "NOT OK";
			cout << endl;
		}
	}
	
}


