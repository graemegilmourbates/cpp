/*
  Graeme Bates
  Linked List
*/

#include <iostream>
using namespace std;

template <typename T>
struct node{
  T key;
  node<T>* next;
  node<T>* previous;
};

template <class T>
class linkedList{
  public:
    linkedList();
    ~linkedList();

    void push(T key);
    void pop();
    //Add insert? insert ordered
    T get(int index);

    void print();

    void sort();

  private:
    node<T>* root;
    void push(T key, node<T>* n);
    void pop(node<T>* n);
    void destroy_list();
};

template <class T>
linkedList<T>::linkedList(){
  root=NULL;
}

template <class T>
void linkedList<T>::push(T key, node<T>* n){
  if(n->next!=NULL){
    push(key, n->next);
  } else {
    n->next=new node<T>;
    n->next->key=key;
    n->next->previous=n;
  }
}

template <class T>
void linkedList<T>::push(T key){
  if(root==NULL){
    root=new node<T>;
    root->key=key;
    root->next=NULL;
    root->previous=NULL;
  } else {
    push(key, root);
  }
}

template <class T>
void linkedList<T>::pop(node<T>* n){
  if(n->next!=NULL){
    pop(n->next);
  } else {
    n->previous->next=NULL;
    delete n;
  }
}

template <class T>
void linkedList<T>::pop(){
  if(root!=NULL){
    if(root->next!=NULL){
      pop(root->next);
    } else {
      delete root;
      root=NULL;
    }
  }
}

template <class T>
T linkedList<T>::get(int index){
  int i = 0;
  node<T>* current = root;
  while(i < index){
    current = current->next;
    i++;
  }
  return current->key;
}

template <class T>
void linkedList<T>::print(){
  node<T>* current = root;
  while(current!=NULL){
    cout << current->key << endl;
    current=current->next;
  }
}

template <class T>
void linkedList<T>::sort(){
  //Merge sort implementation?? maybe that should not be a class function
}

template <class T>
void linkedList<T>::destroy_list(){
  while(root!=NULL){
    pop();
  }
}

template <class T>
linkedList<T>::~linkedList(){
  destroy_list();
}

int main(){
  linkedList<int> test = linkedList<int>();
  test.push(1);
  test.push(3);
  test.push(4);
  test.push(4);
  test.push(4);
  test.print();
  return 0;
}
