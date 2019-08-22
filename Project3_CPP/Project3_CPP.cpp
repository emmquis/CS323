/*
Project 3: Radix Sort (String)
*/

#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
using namespace std;

class listNode
{
public:
	string data;
	listNode* next;
	listNode()
	{
		data = "";
		next = NULL;
	}
	
	listNode(string d)
	{
		data = d;
		next = NULL;
	}
	
	string printLN()
	{
		string str = "";
		if(next == NULL)
		{
			str = str + "(" + data + ", NULL)";
		}
		else
		{
			str = str + "(" + data + ", " + next->data + ")";
		}
		return str;
	}
	
};

class LLStack
{
private:
	listNode* top;
public:
	LLStack()
	{
		top = NULL;
	}
	
	listNode* pop(ofstream& os)
	{
		listNode* temp = new listNode();
		if(isEmpty())
		{
			os << "Stack is empty!" << endl;
		}
		temp = top;
		top = top->next;
		temp->next = NULL;
		return temp;
	}
	
	void push(listNode* newNode)
	{
		newNode->next = top;
		top = newNode;
	}
	
	bool isEmpty()
	{
		if(top == NULL)
			return 1;
		return 0;
	}
	
	void printStack(ostream& os)
	{
		listNode* temp = new listNode();
		temp = top;
		os << "***Below is the output of the stack***" << endl;
		os << "Top";
		while(temp!=NULL)
		{
			os << "->" << temp->printLN();
			temp = temp->next;
		}
		os << "->NULL" << endl;
		os << endl;
	}

	
};

class LLQueue
{
private:
	listNode* head;
	listNode* tail;
	listNode* dummy;
public:
	LLQueue()
	{
		dummy = new listNode("9999");
		head = dummy;
		tail = dummy;
	}
	
	bool isEmpty()
	{
		if(head->next == NULL)
			return 1;
		return 0;

	}
	
	void addTail(listNode* newNode)
	{
		tail->next = newNode;
		tail = newNode;

	}
	
	listNode* deleteHead(ofstream& os)
	{
		listNode* temp = new listNode();
		if(isEmpty())
		{
			os << "Queue is empty!" << endl;
		}
		else
		{
			temp = head->next;
			head->next = head->next->next;
			temp->next = NULL;
			if(tail == temp)
				tail = head;
		}
		return temp;
	}
	
	void printQueue(ostream& os)
	{
		listNode* temp = new listNode();
		temp = head;
		while(temp!=NULL)
		{
			os << "->" << temp->printLN();
			temp = temp->next;
		}
		os << "->NULL" << endl;
	}
	
	
};

class RadixSort
{
private:
	int tableSize;
	LLQueue** hashTable;
	int currentTable;
	int previousTable;
	int longestStringLength;
	int currentPosition;
	LLStack stack;
public:
	RadixSort()
	{
		tableSize = 256;
		hashTable = new LLQueue*[2];
		currentTable = 0;
		previousTable = 1;
		longestStringLength = 0;
		currentPosition = 0;
		for(int i=0; i<2; i++)
			hashTable[i] = new LLQueue[tableSize];
		for(int j=0; j<2; j++)
			for(int k=0; k<tableSize; k++)
				hashTable[j][k] = LLQueue();
				
		stack = LLStack();
	}

	int firstReading(ifstream& in)
	{
		string data;
		while(in >> data)
		{
			if(data.length() > longestStringLength)
				longestStringLength = data.length();
		}
	}
	
	void loadStack(ifstream& in, ofstream& os)
	{
		listNode* newNode;
		string data;
		string paddedData;
		while(in >> data)
		{
			paddedData = padString(data);
			newNode = new listNode(paddedData);
			stack.push(newNode);
		}
		stack.printStack(os);
		
		listNode* temp = newNode;
		while(temp!=NULL)
		{
			reverseStr(temp->data);
			temp = temp->next;
		}
		
	}
	
	void radixSort(ofstream& os2)
	{	
		
		dumpStack(os2);
		currentPosition++;
		while(currentPosition < longestStringLength)
		{
			swap1(currentTable, previousTable);
			listNode* node = new listNode();
			for(int i=0; i<tableSize; i++)
			{
				listNode* node = new listNode();
				char chr;
				while(!hashTable[previousTable][i].isEmpty())
				{
					node = hashTable[previousTable][i].deleteHead(os2);
					chr = getChar(node);
					int hashIndex = (int)chr;
					hashTable[currentTable][hashIndex].addTail(node);
				}
			}
			printTable(os2);
			currentPosition++;
		}
		
	}
	
	void swap1(int& ct, int& pt)
	{
		int temp = ct;
		ct = pt;
		pt = temp;
	}
	
	void reverseStr(string& str) 
	{ 
    	for (int i = 0; i < longestStringLength / 2; i++) 
        	swap2(str[i], str[longestStringLength - i - 1]); 
	}
	
	void swap2(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}
	
	void dumpStack(ofstream& os)
	{
		listNode* temp = new listNode();
		while(!stack.isEmpty())
		{
			temp = stack.pop(os);
			char chr = getChar(temp);
			int hashIndex = (int)chr;
			hashTable[currentTable][hashIndex].addTail(temp);
		}
		printTable(os);
	}
	
	char getChar(listNode* node)
	{
		char chr = node->data.at(currentPosition);
		return chr;
	}
	
	string padString(string data)
	{
		while(data.length() < longestStringLength)
		{
			data = data + " ";
		}
		return data;
	}
	
	void printTable(ofstream& os)
	{
		//listNode* temp = new listNode();
			
		os << "***Below is the output of the queue at index with data reversed***" << endl;
		for(int i = 0; i<tableSize; i++)
		{
			if(!hashTable[currentTable][i].isEmpty())
			{
				os << "Table [" << currentTable << "][" << i << "]:";
				hashTable[currentTable][i].printQueue(os);
			}
		}
		os << endl;
		
	}
	
	void sort(ofstream& os)
	{
		os <<"***Below is the Sorted list***" << endl;
		for(int i=0; i<tableSize; i++)
		{
			listNode* temp = new listNode();
			while(!hashTable[currentTable][i].isEmpty())
			{
				temp = hashTable[currentTable][i].deleteHead(os);
				reverseStr(temp->data);
				os << temp->data;
				delete temp;
			}
		}
	}
};

int main(int argc, char** argv)
{
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	RadixSort rsort = RadixSort();
	rsort.firstReading(inFile);
	inFile.close();
	
	inFile.open(argv[1]);
	rsort.loadStack(inFile, outFile2);
	rsort.radixSort(outFile1);
	rsort.sort(outFile2);
	
	inFile.close();
	outFile1.close();
	outFile2.close();
}
