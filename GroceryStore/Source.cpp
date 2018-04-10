#include <iostream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

class Customer {
public:
	int custNum = 0;					// Customer Number

	// ctor - iterates custNum each time a customer is created.
	Customer() : custNum(custNum++) {}

};
/*******END Customer Class********/

class CashierNode {					// Each node represents a cashier object
public:
	int cashierNum;
	int numCustomers;				// Keeps track of the number of customers in each Cashiers queue.
	int qFront, qRear;				// Front and Rear of the arrCustomerQueue
	int maxCustomers = 5;
	Customer arrCustomerQueue[5];	// Each cashier has a queue array of customer objects.
	CashierNode *pNext;				// A pointer to the next cashier object in the linked list.

	// Method's to add customers to the checkout lines.
	// Accepts the cashierNum from which the method
	// should enqueue or dequeue.
	void enqueueCustomer(int num)
	{
		Customer c;
		for (int i = 0; i < num; i++)
		{
			if (qRear == maxCustomers - 1)
			{
				qRear = -1;
			}
			arrCustomerQueue[++qRear] = c;
			numCustomers++;
			cout << numCustomers;
		}

	}
	// -----------End enqueueCustomer------------------
	void dequeueCustomer()
	{
		Customer c;
		c = arrCustomerQueue[qFront++];
		if (qFront == maxCustomers)
		{
			qFront = 0;
		}
		numCustomers--;
	}
	// -----------End dequeueCustomer----------------

	// Method to determine if the queue is empty or full.
	// isEmpty -- Returns true if empty.
	bool qIsEmpty()
	{
		return qFront == -1;
	}
	// -----------End qIsEmpty-----------------------

	// isFull -- Returns true if full.
	bool qIsFull()
	{
		return qFront == maxCustomers - 1;
	}
	// -----------End qIsFull------------------------
	// Method to return the number of customers current in a node
	// Accepts the cashierNum for which the method returns the
	// number of customers in its queue.
	int getNumCustomers()
	{
		return numCustomers;
	}
	// -----------End getNumCustomers----------------
};

/*******END CashierNode Class********/


class CashierList {					// A list of cashier objects as a linked list.
private:
	CashierNode *pHead, *pTail;		// Pointers to the head and tail of the linked list.

public:
	// ctor
	CashierList() {
		pHead = pTail = NULL;
	}
	// Method to create a new cashier
	void createCashierNode(int numCashiers)
	{
		for (int i = 1; i <= numCashiers; i++)
		{
			CashierNode *pTemp = new CashierNode;
			pTemp->cashierNum = i;
			pTemp->pNext = NULL;
			if (pHead == NULL)			// The list doesn't yet exist...new node is the head and tail.
			{
				pHead = pTemp;
				pTail = pTemp;
				pTemp = NULL;

			}
			else                        // Otherwise, place the new node after the previous tail.
			{
				pTail->pNext = pTemp;
				pTail = pTemp;
			}
		}
	}
	// Helper method to add customer to the CashierNode's queue.
	// Accepts an integer.
	// Initial customer adding is 4, each subsequent calling is 1.
	void addCust(int num)
	{
		CashierNode cn;
		for (int i = 0; i < num; i++)
		{
			cn.enqueueCustomer(num);
		}
	}
	// Helper method to remove customer from the CashierNode's queue.
	void removeCust()
	{
		CashierNode *cn;
		cn->dequeueCustomer();
	}
	// Helper method to get the number of customers for each cashier
	int getNumCustomers()
	{
		CashierNode cn;
		return cn.getNumCustomers();
	}

	// Method to search the list of Cashiers to find the shortest queue.
	// Returns cashierNum that indicates the cashier with the shortest queue.
	int locateShortestQueue()
	{
		CashierNode *pCurrent = pHead;
		int cn, shortestNode;
		shortestNode = pCurrent->numCustomers;
		while (pCurrent != NULL)
		{
			if (pCurrent->numCustomers < shortestNode)
			{
				shortestNode = pCurrent->numCustomers;
				cn = pCurrent->cashierNum;
			}
		}
		return cn;
	}
	// Method to get the number of cashier nodes
	int getCount()
	{
		int count = 0;
		CashierNode *pCurrent = pHead;
		while (pCurrent != NULL)
		{
			count++;
			pCurrent = pCurrent->pNext;
		}
		return count;
	}
};
/*******END CashierList Class********/

// Function Prototypes

// method to build the cashier list
void buildCashiers(int n);
// method to enqueue customers at random intervals.
// method to dequeue customers at random intervals.
// method to display the action. 
int main()
{
	// Build a list of cashier nodes.
	CashierList c;
	c.createCashierNode(9);
	cout << c.getCount();
	
	


	
	//chrono::milliseconds interval(50); // Clear screen every 50ms
	//system("CLS");

		
	

	return 0;
}

void buildCashiers(int n)
{

}