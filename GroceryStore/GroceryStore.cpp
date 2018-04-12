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
	char removeFirst()
	{
		Customer *pTemp = pFirst;
		if (pFirst->pNext != NULL)
		{
			pLast = NULL;
		}
		pFirst = pFirst->pNext;
		delete pTemp;

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
	// Accepts an integer.
	// Initial customer adding is 4, each subsequent calling is 1.
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
		return;


	}
	// -----------End addCust----------------

	// Helper method to remove customer from the CashierNode's queue.
	void removeCust()
	{

	}
	// -----------End removeCust----------------

	// Helper method to get the number of customers for each cashier
	int getNumCustomers()
	{

	}
	// -----------End getNumCustomers----------------

	// Method to search the list of Cashiers to find the shortest queue.
	// Returns cashierNum that indicates the cashier with the shortest queue.
	int locateShortestQueue()
	{

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
	c->displayListCustomers();

	//chrono::milliseconds interval(500); // Clear screen every 50ms
	//c->displayListCustomers();
	//system("CLS");
	//
	//while (true)
	//{

	//}










	return 0;
}
