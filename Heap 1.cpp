#include <iostream>
#include "Heap.hpp"
#include "CircularDoublyLinkedList.hpp"
using namespace std;

int main() {
	// Just a test to create a node
	node a(10,"Sample Task");
	cout << "Node created with key: " << a.key << " and Taskname: " << a.Taskname << endl << a.left << endl <<a.right<< endl<<a.children << endl<< a.degree << endl;
	return 0;
}

<<<<<<< HEAD



node* FibonacciHeap::insert(int key, const string &taskName){
=======
node* FibonacciHeap::insert(node* newNode){
>>>>>>> 7d319953bf23d970f054d26acf734483763ff033
	/*function insert(key, taskName):
	// 1. Create a new Node object
	newNode = new Node(key, taskName)

	// 2. Initialize the node properties
	newNode.degree = 0
	newNode.mark = false
	newNode.parent = nil
	newNode.child = nil

	// 3. Add newNode to the root list
	// The root list is a circular, doubly linked list.
	if rootList is empty:
		rootList = newNode
		newNode.left = newNode
		newNode.right = newNode
	else:
		// Insert newNode next to rootList's current head (minNode)
		minNode = findMin()
		newNode.right = minNode.right
		newNode.left = minNode
		minNode.right.left = newNode
		minNode.right = newNode

	// 4. Update the pointer to the minimum node (minNode)
	if newNode.key < minNode.key:
		minNode = newNode

	// 5. Increment the number of nodes (n) in the heap
	n = n + 1

	// 6. Return the new node handle
	return newNode
	*/

<<<<<<< HEAD

	


=======
	//add newNode to root list
	if(rootlist->isEmpty()){
		rootlist->insertFirst(newNode);
		newNode->left = newNode;
		newNode->right = newNode;
	}else{
		node* minNode = findMin();

		newNode->right = minNode->right;
		newNode->left = minNode;

		minNode->right->left = newNode;
		minNode->right = newNode;
	}

	// update min pointer
	if (min == nullptr || newNode->key < min->key){
		min=newNode;
	}

	return newNode;
>>>>>>> 7d319953bf23d970f054d26acf734483763ff033
}

//DONE
node* FibonacciHeap::findMin() const{
	return min;
}

//DONE
node* FibonacciHeap::extractMin(){
	/*function extractMin():
 	 z = findMin()

  if z is not nil:
    // 1. Move all children of z to the root list
    for each child x of z:
      // Remove x from its child list
      x.parent = nil
      // Add x to the root list (similar to insert's root list update)
      // ... insertion into root list logic ...

    // 2. Remove z from the root list
    if z == z.right:
      rootList = nil  // Heap becomes empty
    else:
      z.left.right = z.right
      z.right.left = z.left
      rootList = z.right // Set a new arbitrary root list start
      
    // 3. Update minNode and Consolidate
    if rootList is not nil:
      minNode = rootList // Start with an arbitrary node
      CONSOLIDATE()

    // 4. Decrement node count
    n = n - 1

  	return z   */

	node* min = findMin();
	if (min != NULL){
		Node<node>* current = min->children->head;
		for (int i = 0; i < min->degree; i++){
			current->data.parent = NULL;
			insert(current->data.left);
			current = current->next;
		}
	}

	rootlist->deleteValue(min);

	if (rootlist != NULL){
		Consolidate();
	}

	return min;
}

//DONE
void FibonacciHeap::decreaseKey(node* handle, int newKey){
	/*function decreaseKey(handle, newKey):
	// 1. Validate the new key
	if newKey > handle.key:
		error "New key is greater than current key"

	// 2. Update the key
	handle.key = newKey

	y = handle.parent
	// 3. Check for heap property violation
	if y is not nil and handle.key < y.key:
		CUT(handle, y)
		CASCADING_CUT(y)

	// 4. Update minNode if necessary
	if handle.key < minNode.key:
		minNode = handle*/

		// 1. Validate the new key
		if (newKey > handle->key) {
			cout << "Error: new key is greater than current key" << endl;
			return;
		}

		// 2. Update the key
		handle->key = newKey;
		node* parent = handle->parent;

		// 3. Check for heap property violation

		if (parent != nullptr && handle->key < parent->key) {
			Cut(handle, parent);
			cascading_cut(parent);
		}


		// 4. Update minNode if necessary
		if (min == nullptr || handle->key < min->key) {
			min = handle;
		}	
}	

//DONE
void FibonacciHeap::deleteNode(node* handle){
	decreaseKey(handle, INT_MIN);
	extractMin();
}

void FibonacciHeap::Consolidate(){
	// --- Helper Function for CONSOLIDATION ---
    /*//function CONSOLIDATE():
	// 1. Create an auxiliary array A[0...D_n] where D_n is the max degree
	initialize array A to all nil pointers

	for each node w in the root list:
		x = w
		d = x.degree
		while A[d] is not nil:
		y = A[d]
		if x.key > y.key:
			// Swap x and y if x has the larger key
			temp = x; x = y; y = temp
		
		// y becomes a child of x (Link step)
		LINK(y, x)
		A[d] = nil
		d = d + 1

		A[d] = x

		// 2. Rebuild the root list from the array A and find the new minNode
		minNode = nil
		for each non-nil entry A[i] in array A:
		// Add A[i] to the root list (clearing previous root list)
		// ... root list rebuild logic ...

		// Update minNode
		if minNode is nil or A[i].key < minNode.key:
		minNode = A[i]*/
	const int MAX_DEGREE = 64; // A safe upper bound for degrees
	node* A[MAX_DEGREE];
	for (int i = 0; i < MAX_DEGREE; i++){
		A[i] = nullptr;
	}
	// Traverse root list
	Node<node>* current = rootlist->head;
	int rootSize = rootlist->size();
	for (int i = 0; i < rootSize; i++){
		node* x = &current->data;
		int d = x->degree;

		while (A[d] != nullptr){
			node* y = A[d];
			if (x->key > y->key){
				node* temp = x; 
				x = y; 
				y = temp;
			}
			Link(x, y);
			A[d] = nullptr;
			d++;
		}
		A[d] = x;
		Node<node>* next = current->next;

		current = next;
	}
	// Rebuild root list and find new min
	min = nullptr;
	delete rootlist;
	rootlist = new CircularDoublyLinkedList<node>();
	for (int i = 0; i < MAX_DEGREE; i++){
		if (A[i] != nullptr){
			rootlist->insertLast(A[i]);
			if (min == nullptr || A[i]->key < min->key){
				min = A[i];
			}
		}
	}



}	

//DONE
void FibonacciHeap::Link(node* x, node*y){
// --- Helper Function for LINKING ---
	/*function LINK(y, x):
	// Make y a child of x (x is the new parent)
	// 1. Remove y from the root list
	y.left.right = y.right
	y.right.left = y.left

	// 2. Make y a child of x
	y.parent = x
	if x.child is nil:
		x.child = y
		y.left = y
		y.right = y
	else:
		// Insert y into the circular child list of x
		// ... insertion into child list logic ...

	// 3. Increment x's degree
	x.degree = x.degree + 1
	// 4. Clear y's mark
	y.mark = false*/
	
	rootlist->deleteValue(y);
	x->children->insertLast(y);
	y->parent = x;
	x->degree++;
	y->mark = false;
}

void FibonacciHeap::Cut(node* x, node*y){
	// --- Helper Function for CUT ---
	/*function CUT(x, y):
	// Remove x from the child list of y
	// ... removal from circular list logic ...

	y.degree = y.degree - 1
	
	// Add x to the root list
	// ... insertion into root list logic ...

	x.parent = nil
	x.mark = false*/
	y->children->deleteValue(x);
	y->degree--;
	insert(x);
	x->parent = nullptr;
	x->mark = false;
}

void FibonacciHeap::cascading_cut(node* y){
	// --- Helper Function for CASCADING CUT ---
	/*function CASCADING_CUT(y):
	z = y.parent
	if z is not nil:
		if y.mark == false:
		y.mark = true
		else:
		CUT(y, z)
		CASCADING_CUT(z)*/
	node* z = y->parent;
	if (z != nullptr){
		if (y->mark == false){
			y->mark = true;
		}else{
			Cut(y, z);
			cascading_cut(z);
		}
	}
}		