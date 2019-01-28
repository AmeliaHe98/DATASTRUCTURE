#include "chain.h"
#include "chain_given.cpp"
#include <algorithm>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
    clear();
}

/**
 * Inserts a new node in position one of the Chain,
 * after the sentinel node.
 * This function **SHOULD** create a new Node.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertFront(const Block & ndata){
    Node* temp = new Node(ndata);
    temp->next = head_->next;
    head_->next->prev = temp;
    head_->next = temp;
    temp->prev = head_;
    length_++;
}

/**
 * Inserts a new node at the back of the Chain,
 * but before the tail sentinel node.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
    Node* insert = new Node(ndata);
    insert->next =  tail_;
    insert->prev = tail_->prev;
    tail_->prev->next = insert;
    tail_->prev = insert;
    length_++;
}

/**
 * Modifies the Chain by moving a contiguous subset of Nodes to
 * the end of the chain. The subset of len nodes from (and
 * including) startPos are moved so that they
 * occupy the last len positions of the
 * chain (maintaining the sentinel at the end). Their order is
 * not changed in the move.
 */
void Chain::moveToBack(int startPos, int len){
    Node* curr = head_;
    Node* start = walk(curr,startPos);
    Node* end = walk(start,len-1);
    
    start->prev->next=end->next;
    end->next->prev=start->prev;
    
    end->next = tail_;
    start->prev=tail_->prev;
    
    tail_->prev->next=start;
    tail_->prev = end;
}

/**
 * Rotates the current Chain by k nodes: removes the first
 * k nodes from the Chain and attaches them, in order, at
 * the end of the chain (maintaining the sentinel at the end).
 */
void Chain::rotate(int k) {
    if (k > 0 && k <= length_) {
        Node* nodeStart = head_->next;
        Node* nodeEnd = walk(head_, k + 1);
        Node* nodeEndNext = walk(head_, k + 1);
        Node* nodeTailPre = tail_->prev;
        
        head_->next = nodeEndNext;
        nodeEndNext->prev = head_;
        
        nodeStart->prev = nodeTailPre;
        nodeTailPre->next = nodeStart;
        
        nodeEnd->next = tail_;
        tail_->prev = nodeEnd;
        
    }
    
}

/**
 * Modifies the current chain by swapping the Node at pos1
 * with the Node at pos2. the positions are **1-based.
 */
void Chain::swap(int pos1, int pos2){
    if((pos1<0)||(pos2<0)||(pos2>length_)||(pos1>length_))
        return;
    Node* posi1 = walk(head_,pos1);
    Node* posi1Back = posi1->next;
    Node* posi1Front = posi1->prev;
    
    Node* posi2 = walk(head_,pos2);
    Node* posi2Back = posi2->next;
    Node* posi2Front = posi2->prev;
    
    //not next to each other
    if((posi2Back!=posi1)||(posi2Front!=posi1)){
        posi1Front->next=posi2;
        posi1Back->prev=posi2;
        posi2->next=posi1Back;
        posi2->prev=posi1Front;
        
        posi2Front->next=posi1;
        posi2Back->prev=posi1;
        posi1->next=posi2Back;
        posi1->prev=posi2Front;
    }
    //posi1, posi2
    if(posi1Back == posi2){
        posi1Front->next=posi2;
        posi2->prev=posi1Front;
        posi2->next=posi1;
        posi1->prev=posi2;
        posi1->next=posi2Back;
        posi2Back->prev=posi1;
    }
    //posi2, posi1
    if(posi1Front == posi2){
        posi2Front->next=posi1;
        posi1->prev=posi2Front;
        posi1->next=posi2;
        posi2->prev=posi1;
        posi2->next=posi1Back;
        posi1Back->prev=posi2;
    }
return;}

/*
 *  Modifies both the current and input chains by trading
 * nodes in even positions between the chains. Length
 * of each chain should stay the same. If the block dimensions
 * are NOT the same, the funtion has no effect and a simple
 * error message is output: cout << "Block sizes differ." << endl;
 */

void Chain::twist(Chain & other){
  if(size()!=other.size()){
    cout << "Block sizes differ." << endl;
    return ;
  }
  else{
  Node* curr=head_->next;
  Node* other_=other.head_->next;
  int n = 0;
  while(n < size()){
    Node* temp1 = other_->next;
    Node* temp2 = curr->next;
    curr->next=temp1;
    other_->next=temp2;
    
    temp1->prev=curr;
    temp2->prev=other_;
    
    curr=temp1;
    other_=temp2;
    n++;
  }}
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
    Node* current = head_;
    while(current)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
        temp=NULL;
    }
    head_=NULL;
    tail_=NULL;
    length_=0;
    width_=0;
    height_=0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  if(other.empty()){
    return;
  }
  
  head_= new Node();
  tail_= new Node();
  head_->next=tail_;
  tail_->prev=head_;
  
  width_=other.width_;
  height_=other.height_;
  length_=other.length_;
  
  Node* curr = head_;
  Node* other_ = other.head_->next;
  
  for(int n=0; n<size();n++){
    
    Node* temp = new Node(other_->data);
    temp->next=tail_;
    tail_->prev=temp;
    
    curr->next=temp;
    temp->prev=curr;
    
    curr=curr->next;
    other_=other_->next;
    
  }
}


