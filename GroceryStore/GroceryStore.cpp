#include <iostream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;
/*******BEGIN CUSTOMER Class********/
// A class of customer objects to be inserted into
// a CustomerList, which is a linked list within a CashierNode.
class Customer {
public:
	char cusrIdentifier = 'O';
	Customer *pNext;
	Customer() : pNext(NULL) { }

};
///*******END Customer Class********/

/*******BEGIN CUSTOMERLIST Class********/
// A Queued Linked List of Customer Objects to be embedded within a 
// CashierNode. 
class CustomerList {
private:
	Customer * pFirst, *pLast;
	int numCust = 0;
public:
	// ctor
	CustomerList() : pFirst(NULL), pLast(NULL) { }
	// de-ctor
	~CustomerList()
	{
		Customer *pCurrent = pFirst;
		while (pCurrent != NULL)
		{
			Customer *pTemp = pCurrent;
			pCurrent = pCurrent->pNext;
			delete pTemp;
		}
	}

	// Method to determine if the CustomerList within the CashierNode is Empty.
	bool qIsEmpty()
	{
		return pFirst == NULL;
	}
	//---------------END qIsEmpty--------------------

	// Method to pop the first customer out of the CustomerList for a given CashierNode
	void removeFirst()
	{
		if (pFirst != NULL)
		{
			Customer *temp = pFirst->pNext;
			delete pFirst;
			pFirst = temp;
			--numCust;
		}
	}
	//---------------END removeFirst--------------------

	// Method to insert a new customer to the CustomerList within a given CashierNode
	void insertLast(Customer *c)
	{
		if (qIsEmpty())
		{
			pFirst = c;
		}
		else
		{
			pLast->pNext = c;
		}
		pLast = c;
		numCust++;
	}
	//---------------END removeFirst--------------------

	// Method to get the number of customers in the customer list
	int getNumCustomers()
	{
		Customer *cust = pFirst;
		while (cust != NULL)
		{
			numCust++;
			cust = cust->pNext;
		}
		return numCust;
	}
	//---------------END getNumCustomers-----------------
};
/*******END CustomerList Class********/

class CustomerQueue {
private:
	CustomerList custList;
public:
	bool isEmpty()
	{
		return custList.qIsEmpty();
	}
	void insert()
	{
		Customer *c = new Customer;
		custList.insertLast(c);
	}
	void remove()
	{
		custList.removeFirst();
	}


};

/*******BEGIN CASHIERNODE Class********/
class CashierNode {					// Each node represents a cashier object
public:
	int cashierNum;
	int numCustomers = 0;				// Keeps track of the number of customers in each Cashiers queue.
	CashierNode *pNext;				// A pointer to the next cashier object in the linked list.
};
/*******END CashierNode Class********/

/*******BEGIN CASHIERLIST Class********/
// CashierList Class creates a linked list of CashierNodes
// Within the CashierNodes exists a linked list of customers
// in the form of a queue.
class CashierList {					// A list of cashier objects as a linked list.
private:
	CashierNode * pHead, *pTail;		// Pointers to the head and tail of the linked list.

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
	// -----------End createCashierNode----------------

	// Helper method to add customer to the CashierNode's queue.
	// Accepts an integer for the number of customers to be added,
	// and an integer for the cashier number to insert the customers.
	// Inserts into the shortest queue located by locateShortestQueue.
	void addCust(int num, int cashier)
	{
		CustomerQueue cq;
		CashierNode *cn = pHead;
		while (cn != NULL)
		{
			if (cn->cashierNum == cashier)
			{
				for (int i = 0; i < num; i++)
				{
					cq.insert();
					cn->numCustomers++;
				}
				return;
			}
			else 
			{
				cn = cn->pNext;
			}
		}
		return; // Not found
	}
	// -----------End addCust----------------

	// Helper method to remove customer from the CashierNode's queue.
	void removeCust(int cashier)
	{
		CustomerQueue cq;
		CashierNode *cn = pHead;
		while (cn != NULL)
		{
			if (cn->cashierNum == cashier)
			{
				cq.remove();
				cn->numCustomers--;
				return;
			}
			else
			{
				cn = cn->pNext;
			}

		}
		return; // Not found

	}
	// -----------End removeCust----------------

	// Method to search the list of Cashiers to find the shortest queue.
	// Returns cashierNum that indicates the cashier with the shortest queue.
	int locateShortestQueue()
	{
		CashierNode *pCurrent = pHead;
		int shortestQueue = pHead->numCustomers;
		while (pCurrent != NULL)
		{
			if (pCurrent->numCustomers < shortestQueue)	// Any queue with numCustomers > 0
			{
				return pCurrent->cashierNum;
			}
			if (pCurrent->numCustomers == 0)	// Any queue with numCustomers == 0
			{
				return pCurrent->cashierNum;
			}
			else
			{
				pCurrent = pCurrent->pNext;	// Look for smaller queues.
			}
		}
	}
	// -----------End locateShortestQueue--------------

	// Method to get the number of cashier nodes -- TESTING
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
	// -----------End getCount----------------

	// Method to display the cashiers and the number of customers
	void displayListCustomers()
	{
		CashierNode *pCurrent = pHead;
		while (pCurrent != NULL)
		{
			cout << "Cashier Number " << pCurrent->cashierNum << ": ";
			cout << "Customers: "; 
			// Print a O for every customer to simulate the transition of customers through the queue
			for (int i = 0; i < pCurrent->numCustomers; i++) 
			{
				cout << 'O' << " ";
			}
			cout << endl;
			pCurrent = pCurrent->pNext;
		}
	}
	// -----------End displayListCustomers----------------
};
/*******END CashierList Class********/


//---------------MAIN------------------//
int main()
{
	// Build a list of cashier nodes.
	CashierList *c;
	c = new CashierList;
	c->createCashierNode(9);
	c->addCust(5, 3);
	c->addCust(3, 4);
	c->addCust(2, 1);
	c->addCust(1, 5);
	c->addCust(6, 2);
	c->addCust(7, 6);
	c->addCust(10, 7);
	c->addCust(4, 8);
	c->addCust(8, 9);

	c->removeCust(1);
	c->removeCust(1);
	c->displayListCustomers();
	cout << "\nShortest Queue: " << c->locateShortestQueue() << endl;

	//chrono::milliseconds interval(500); // Clear screen every 50ms
	//c->displayListCustomers();
	//system("CLS");
	//
	//while (true)
	//{

	//}










	return 0;
}
