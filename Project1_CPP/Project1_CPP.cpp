/*
Project 1 C++
Linked List Implementation of Stack and Queue
*/

#include<iostream>
using namespace std;

//node
class listNode
{
public:
	int data;
	listNode* next;

	//constructor
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
};

//stack
class LLStack
{
private:
	listNode* top;
public:
	//constructor
	LLStack() 
	{
		top = NULL;
	}

	//pop
	listNode pop()
	{
		listNode* temp = new listNode();
		temp = top;
		if(isEmpty())
		{
			cout << "Stack is empty!";
		}
		else
		{
			cout << "Deleted element is: " << top->data;
			
			top = top->next;
			delete temp;
		}
	}
	//push
	void push(int s)
	{
		listNode* newNode = new listNode(s);
		
		if(isEmpty())
		{
			top = newNode;
		}
		else
		{
			newNode->next = top;
			top = newNode;
		}

	}
	//isempty
	bool isEmpty()
	{
		return top == NULL;
	}
	//print
	void print()
	{
		listNode* q = new listNode();
		q = top;
		if(isEmpty())
		{
			cout << "Stack is empty!";
		}
		else
		{
			while(q!=NULL)
			{
				cout << q->data << " ";
				q = q->next;
			}
		}
	}
};

//queue
class LLQueue
{

private:
	listNode* head;
	listNode* tail;
	listNode* dummy;
public:
	//constructor
	LLQueue()
	{
		dummy = new listNode(9999);
		head = dummy;
		tail = dummy;
	}
	//addQ
	void addQ(int q)
	{		
		listNode* temp = new listNode(q);
		temp->next = dummy;
				
		if(tail == dummy)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}

	}
	//deleteQ
	listNode deletQ()
	{
		listNode* temp = new listNode;
		temp = head;
		if(isEmpty())
		{
			cout << "Queue is empty!";
		}
		else
		{
			cout << "Deleted element is: " << temp->data << endl;
			temp = temp->next;
			delete temp;
		}
	}
	//isEmpty
	bool isEmpty()
	{
		return head == NULL;
	}
	//printQ
	void printQ()
	{	
			
		listNode* n = new listNode;
		n = head;
		if(isEmpty())
		{
			cout <<  "Queue is empty!";
		}
		else
		{
			while(n!=NULL)
			{
				cout << n->data << "<-";
				n = n->next;
			}
			//cout << "dummy(" << dummy->data << ")";
		}
	}	
};


//main
int main(int argc, char**argv)
{
	char in1;
	//STEP 1

	cout << "Choose S - for stack or Q - for queue: ";
	cin >> in1;
	
	char yn;
	int num;
	bool answer = true;
	//s selected
	if(in1 == 's' || in1 == 'S')
	{
		char s_in;	
		//STEP 2	
		cout << "----Stack class chosen----" << endl;

		LLStack sptr;
		while(answer)
		{
			//STEP 3
			cout << "Choose I - for insertion or D - for deletion: ";
			cin >> s_in;
			if(s_in == 'i' || s_in == 'I')
			{
				//STEP 4
				cout << "----Stack insertion chosen----" << endl;
				
				//STEP 5.1
				cout << "Enter integer for insertion: ";
				cin >> num;

				//STEP 5.2
				cout << "Inserting " << num << endl;
				
				//STEP 6.1
				
				//STEP 6.2
				sptr.push(num);
				//STEP 7
				cout << "The Stack list is: ";
				sptr.print();
				cout << endl;
				//STEP 8
				cout << "Would you like to perform another operation? (y - for yes or n - for no): ";
				cin >> yn;
				
				if(yn == 'Y' || yn == 'y')
				{
					//STEP 9
					cout << "Another operation chosen" << endl;
					//REPEAT STEP 3 - 10
					continue;
				}
				//STEP 10
				else if(yn == 'N' || yn == 'n')
				{
					cout << "Exiting program" << endl;
					answer = false;
				}
				else
				{
					cout << "Not an option." << endl;
					break;
				}
								
			}
			else if(s_in == 'd' || s_in == 'D')
			{
				//STEP 4
				cout << "----Stack deletion chosen----" << endl;
				
				//STEP 5.1 (NA)
				//STEP 5.2 (NA)
				//STEP 6.1
				
				//STEP 6.2
				sptr.pop();
				cout << endl;
				//STEP 7
				cout << "The Stack List is: ";
				sptr.print();
				cout << endl;
				
				//STEP 8
				cout << "Would you like to perform another operation? (y - for yes or n - for no): ";
				cin >> yn;
				
				if(yn == 'Y' || yn == 'y')
				{
					//STEP 9
					cout << "Another operation chosen" << endl;
					//REPEAT STEP 3 - 10
					continue;
				}
				//STEP 10
				else if(yn == 'N' || yn == 'n')
				{
					cout << "Exiting program" << endl;
					answer = false;
				}
				else
				{
					cout << "Not an option." << endl;
					break;
				}
				
			}
			else
				cout << "Invalid character, try again" << endl;
		}
	}
	
	
	//q selected
	else if(in1 == 'q' || in1 == 'Q')
	{
		char q_in;
		//STEP 2
		cout << "----Queue class chosen----" << endl;
		
		LLQueue qptr;
		
		while(answer)
		{
			
			//STEP 3
			cout << "Choose I - for insertion or D - for deletion: ";
			cin >> q_in;
			if(q_in == 'i' || q_in == 'I')
			{
				//STEP 4
				cout << "----Queue insertion chosen----" << endl;
				
				//STEP 5.1
				cout << "Enter integer for insertion: ";
				cin >> num;
				
				//STEP 5.2
				cout << "Inserting " << num << endl;
				
				//STEP 6.1
				//STEP 6.2
				qptr.addQ(num);
				
				//STEP 7
				cout << "The Queue list is: ";
				qptr.printQ();
				cout << endl;
				//STEP 8
				cout << "Would you like to perform another operation? (y - for yes or n - for no): ";
				cin >> yn;
				
				if(yn == 'Y' || yn == 'y')
				{
					//STEP 9
					cout << "Another operation chosen" << endl;
					//REPEAT STEP 3 - 10
					continue;
				}
				//STEP 10
				else if(yn == 'N' || yn == 'n')
				{
					cout << "Exiting program" << endl;
					answer = false;
				}
				else
				{
					cout << "No such option." << endl;
					break;
				}
				
			}
			else if(q_in == 'd' || q_in == 'D')
			{
				//STEP 4
				cout << "----Queue deletion chosen----" << endl;
				
				//STEP 5.1 (NA)
				//STEP 5.2 (NA)
				//STEP 6.1
				//STEP 6.2
				qptr.deletQ();
				//cout << endl;
				
				//STEP 7
				cout << "The Queue List is: ";
				qptr.printQ();
				cout << endl;
				
				//STEP 8
				cout << "Would you like to perform another operation? (y - for yes or n - for no): ";
				cin >> yn;
				
				if(yn == 'Y' || yn == 'y')
				{
					//STEP 9
					cout << "Another operation chosen" << endl;
					//REPEAT STEP 3 - 10
					continue;
				}
				//STEP 10
				else if(yn == 'N' || yn == 'n')
				{
					cout << "Exiting program" << endl;
					answer = false;
				}
				else
				{
					cout << "No such option." << endl;
					break;
				}
			}
			else
				cout << "Invalid character, try again" << endl;
			
		}
	}
	//invalid character
	else
		cout << "Invalid character, exiting program" << endl;
	
	return 0;
}
