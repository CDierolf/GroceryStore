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
	Customer *pNext;
	Customer() : pNext(NULL) { }

};
///*******END Customer Class********/

/*******BEGIN CUSTOMERLIST Class********/
// A Queued Linked List of Customer Objects to be embedded within a 
// CashierNode. 
// Parameters: int numCust -- Keeps track of the number of customers 
//                            in each cashier queue.
/////////////
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

/*******BEGIN CustomerQueue Class********/
// Handles the queue specifications for the Customer
// List class. 
// PARAMETERS: int maxCust -- The maximum combined customers
//                            within the program.
////////////

class CustomerQueue {
private:
	CustomerList custList;
	int maxCust = 180;
public:
	// Helper method for the CustomerList qIsEmpty() method.
	bool isEmpty()
	{
		return custList.qIsEmpty();
	}
	//---------------END isEmpty--------------------

	// Helper method for the CustomerList insertLast() method.
	void insert()
	{
		Customer *c = new Customer;
		custList.insertLast(c);
	}
	//---------------END insert--------------------

	// Helper method for the CustomerLIst removeFirst() method.
	void remove()
	{
		custList.removeFirst();
	}
	//---------------END remove--------------------

	// Method to return the maximum total customers for the program.
	int getMaxCust()
	{
		return maxCust;
	}
	//---------------END getMaxCust--------------------

	// Method to set the maxCust parameter.
	void setMaxCust(int numCust)
	{
		maxCust = numCust;
	}
	//---------------END setMaxCust--------------------


};

/*******BEGIN CASHIERNODE Class********/
// A node for cashiers.
// PARAMETERS: int cashierNum -- the cashier node identifier.
//             int numCustomers -- the number of customers in the cashiers
//								  CustomerQueue.
////////////
class CashierNode {					// Each node represents a cashier object
public:
	int cashierNum;
	int numCustomers = 0;			// Keeps track of the number of customers in each Cashiers queue.
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
			if (cn->cashierNum == cashier && cn->numCustomers < cq.getMaxCust()) // verify maxCust
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

		int queueNum = 20;
		int cashier = 0;
		while (pCurrent != NULL)
		{
			if (pCurrent->numCustomers < queueNum)
			{
				queueNum = pCurrent->numCustomers;
				cashier = pCurrent->cashierNum;
			}
			pCurrent = pCurrent->pNext;
		}
		return cashier;
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

	int getTotalCustomers()
	{
		CashierNode *pCurrent = pHead;
		int totCust = 0;
		while (pCurrent != NULL)
		{
			totCust += pCurrent->numCustomers;
			pCurrent = pCurrent->pNext;
		}
		return totCust;
	}
};
/*******END CashierList Class********/

// Function Prototypes
void inOutRandom(CashierList *, int);

//---------------MAIN------------------//
int main()
{
	int maximumCustomers, cashiers;
	cout << "This program simulates the checkout lines of a\n";
	cout << "retail store on black friday.\n\n";
	cout << "Enter the maximum total customers to be reached\n";
	cout << "before armeggedon breaks out: ";
	cin >> maximumCustomers;
	cout << "\n\nEnter the number of cashiers on staff for black friday: ";
	cin >> cashiers;

	// Build a list of cashier nodes.
	CashierList *c;
	c = new CashierList;
	c->createCashierNode(cashiers);
	cout << c->getTotalCustomers();
	while (c->getTotalCustomers() < maximumCustomers) // loop FOR-EV-VERR
	{
		chrono::milliseconds interval(50); // Clear screen every 50ms
		while (true)
		{
			chrono::seconds addCustInterval(rand() % 2); // Clear screen every 50ms
			inOutRandom(c, cashiers);
			c->displayListCustomers();
			this_thread::sleep_for(addCustInterval);
			system("CLS");
		}
		this_thread::sleep_for(interval);
	}
	return 0;
}

// Method to insert and remove customers.
// Inserts based on the shortest queue.
void inOutRandom(CashierList *c, int numCashier)
{

	int shortestQueue = c->locateShortestQueue();
	cout << "\nShortest Queue: Cashier #: " << shortestQueue << endl;
	cout << "Total Customers: " << c->getTotalCustomers() << endl << endl;
	int randRemove = (rand() % numCashier + 5); // Make modulus slightly higher so that
												// a customer isn't removed at every pass.

	c->addCust(1, shortestQueue);
	c->removeCust(randRemove);
}
// -----------End inOutRandom--------------

