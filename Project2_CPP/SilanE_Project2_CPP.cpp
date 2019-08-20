/*
Emmanuel Silan
CSC 323-35
Project 2: Radix Sort
*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
using namespace std;

class listNode
{
public:
    int data;
    listNode* next;

	listNode()
	{
		data = 0;
		next = NULL;
	}

    listNode(int d)
	{
        data = d;
        next = NULL;
    }

    string printLN()
	{
        string str = "";
        if(next == NULL)
        {
        	str = str + "(" + to_string(data) + ", NULL )";
		}
        else
		{
			str = str + "(" + to_string(data) + ", " + to_string(next->data) + ")";	
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

    listNode* pop()
	{
		listNode* node = new listNode();
		node = top;
        if(isEmpty())
		{
			return NULL;
		} 
        top = top->next;
        node->next = NULL;
        return node;
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
        os << "*** Below is the output of the stack ***" << endl;
        os << "TOP";
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
public:
    LLQueue()
	{
		head = NULL;
		tail = NULL;
    }
    
    void addTail(listNode* newNode)
	{

        if(isEmpty()) 
		{
            tail = newNode;
            head = newNode;
        }
        else 
		{
            tail->next = newNode;
            tail = newNode;
        }
    }

    listNode* deleteHead()
	{
        listNode* temp = new listNode();
		temp = head;
        if(head == tail)
		{ 
			head = NULL;
			tail = NULL;
		}

        else 
			head = head->next;

        temp->next = NULL;
        return temp;

    }

    bool isEmpty()
	{
		if(tail == NULL)
			return 1;
		return 0;
    }

    void printQueue(ostream& os)
	{
		listNode* temp = new listNode();
		temp = head;
		
        os << "Front";
        while(temp!=NULL)
		{
            os << "->" << temp->printLN();
            temp = temp->next;
        }
        os << "->NULL" << endl;
        
        temp = tail;
        os << "Tail";
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
	int maxDigit; 
	int offSet; 
	int currentDigit;
    LLStack stack;  
public:
    RadixSort()
	{
        tableSize = 10;
        hashTable = new LLQueue*[2];
        currentTable = 0;
        previousTable = 1;
        maxDigit = 0;
        offSet = 0;
        currentDigit = 1;

        for(int i =0; i<2; i++) 
			hashTable[i] = new LLQueue[tableSize];
        for(int j =0; j<2; j++)
            for(int k = 0; k <tableSize; k++)
                hashTable[j][k] = LLQueue();
                
		stack = LLStack();
    }

    ~RadixSort()
	{
        for(int i =0; i<2; i++) 
			delete []hashTable[i];
        delete []hashTable;
    }

    void firstReading(ifstream& in)
	{
        int negativeNum = 0;
		int positiveNum = 0; 
		int data;
        while(!in.eof())
		{
            in >> data;
            if(data<negativeNum) 
				negativeNum = data;
            if(data>positiveNum) 
				positiveNum = data;
        }
        offSet = abs(negativeNum);
        positiveNum = positiveNum+offSet;
        maxDigit = getMaxDigits(positiveNum);
    }

    void loadStack(ifstream& in, ofstream& os)
	{
		listNode* newNode;
        int data;
        while(in >> data)
		{
            newNode = new listNode(data+offSet);
            stack.push(newNode);
        }
        stack.printStack(os);
    }

    void radixSort(ofstream& os)
	{
        dumpStack(os);
        currentDigit++;
        while(currentDigit<=maxDigit)
		{
            swap(currentTable, previousTable);

            for(int i =0; i<tableSize; i++)
			{
				listNode* temp = new listNode();
                while(!hashTable[previousTable][i].isEmpty())
				{
                	temp = hashTable[previousTable][i].deleteHead();
                    string str = to_string(temp->data);
                    int digit = str[str.length()-currentDigit] - '0';
                    if(str.length() < currentDigit) 
						digit = 0;
                    hashTable[currentTable][digit].addTail(temp);
                }
            }
            printTable(os);
            currentDigit++;
        }
    }
    
    void swap(int& ct, int& pt)
    {
    	int temp = ct;
    	ct = pt;
    	pt = temp;
	}

    void dumpStack(ofstream& os)
	{
		listNode* temp = new listNode();
        while(!stack.isEmpty())
		{
            temp = stack.pop();
            int digit = temp->data%(currentDigit*10);
            hashTable[currentTable][digit].addTail(temp);
        }
        printTable(os);
    }
    
    int getMaxDigits(int pnum)
	{
		int count = 0;
        while(pnum > 0) 
		{
            pnum = pnum/10;
            count++;
        }
        return count;
	}

    void printTable(ofstream& os)
	{
        os << "***Below is the output of the queue at index***" << endl;
        for(int i = 0; i<tableSize; i++)
		{
            if(!hashTable[currentTable][i].isEmpty())
			{
                os << "Table [" << to_string(currentTable) << "][" << to_string(i) <<"]: ";
                hashTable[currentTable][i].printQueue(os);
            }
        }
        os << endl;
    }

    void sort(ofstream& os)
	{
		os << "***Sorted list***" << endl;
        for(int i = 0; i<tableSize; i++)
		{
			listNode* temp = new listNode();
            while(!hashTable[currentTable][i].isEmpty())
			{
                temp = hashTable[currentTable][i].deleteHead();
                os << temp->data - offSet << " ";
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
    rsort.radixSort(outFile2);
	rsort.sort(outFile1);
	
    inFile.close();
    outFile1.close();
    outFile2.close();

}
