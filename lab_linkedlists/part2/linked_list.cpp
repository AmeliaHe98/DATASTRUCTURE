// linked_list.cc -- functions for linked_list lab (cs221) 

#include "linked_list.h"


/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: newKey is the value for the key in the new Node 
 * POST: the new Node is now the head of the linked_list
 */ 
void insert(Node*& head, int newKey) {
  Node * curr = new Node;
  //next code modified by Hejian
  curr->key  = newKey;
  if  (head ==NULL){
        //  std::cout<<"It is the first node!"<<std::endl;
 	 curr->next =NULL;
	}
  else {
	curr->next =head;  
	} 
  // end modified
  head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
void print(Node* head) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    std::cout << curr->key;
    if (curr->next != NULL) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/** 
 * Returns the size (number of Nodes) of the linked_list  
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
int size(Node* head){ 
  if (! head) return 0; 
  return 1 + size(head->next); 
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * POST: a new vector<int> containing the keys in the correct order has been returned.  
 */ 
std::vector<int> to_vector(Node* head) {
  std::vector<int> result;
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    result.push_back(curr->key); 
  }
  return result; 
}

/** 
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node*& head){
    Node* curr = head;
    Node* temp=NULL; // Point to the node before the last
	
    if(size(curr)==1){
        delete curr;
        head =NULL;
        return;
    }
    else {
        while(curr->next!=NULL){
	    temp =curr;  // Temp points to the node before the last one. Modified by Hejian
            curr=curr->next; // Curr moves forward. Modified by Hejian
        }
        delete(curr);
        temp->next = NULL; // make sure the node before the last points to nill
    }
    
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list. 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value of the key in the Node to be removed 
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed 
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */ 
void remove(Node*& head, int oldKey) {
    Node* curr = head;
    Node* temp;
    if(size(curr)==0){
        std::cout << "The list is empty, couldn't remove!"<< std::endl;
        return;
    }
    else if((size(curr)==1)&&(curr->key==oldKey)){
        delete(curr);
        head=NULL; // modified by Hejian
        return ;   // modified by Hejian 
    }
    else {
        temp=curr->next;
        while(temp!=NULL){
       	    if(temp->key==oldKey){  // modified by Hejian
                curr->next=temp->next;
                temp=NULL;
		delete temp;
                return;
             }
          else{
                curr=temp; //curr saves the current node; Modified  by Hejian
		temp=temp->next;
          }
        }
    }
    
}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value to look for (in the key of an existing Node)  
 * PRE: newKey is the value of the key in the new Node (that might be inserted) 
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node* head, int oldKey, int newKey){
   Node* curr = head;
    Node* temp;
    Node* n = new Node();
    if(size(curr)==0){
        std::cout << "The list is empty, just return!"<< std::endl;
        return;
    }
    else if((size(curr)==1)&&(curr->key==oldKey)){
        curr->next=n;
        n->key=newKey;
        n->next = NULL;
	return;
    }
    else{
        temp=head;
        if (temp->key ==oldKey){
           n->next = temp->next;
           n->key =newKey;
           temp->next =n;
           return;
        }
	temp= curr->next;
    	while(temp->next!=NULL){
            if(temp->key==oldKey){
	        n->next = temp->next;
        	n->key=newKey;
        	temp->next = n->next;
                return;
	    }
	    else {
                temp= temp->next;  //Coud not find the node where key equals oldkey, just moves forward. Modified by Hejian
	    }
        }
  }
}

/** 
 * Create a new linked_list by merging two existing linked_lists. 
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from 
 * the Nodes in list1 and list2, starting with the key of the first Node of list1, 
 * then the key of the first Node of list2, etc. 
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node* interleave(Node* list1, Node* list2){
  // ******** WRITE YOUR CODE HERE ********
  return NULL;  // ******** DELETE THIS LINE ********

}
