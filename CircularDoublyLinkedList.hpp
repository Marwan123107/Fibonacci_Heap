#include <iostream>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value){
        data = value;
        next = this;
        prev = this;
    }

};
class CircularDoublyLinkedList{
private:
    Node* head;

public:
    CircularDoublyLinkedList(){
        head = nullptr;
    }

    bool isEmpty(){
        return head == nullptr;
    }

    void insertFirst(int value){
        Node*newNode = new Node(value);

        if(isEmpty()){
            head = newNode;
        }else{
            Node* tail = head->prev;

            newNode->next = head;
            newNode->prev = tail;

            tail->next = newNode;
            head->prev = newNode;

            head = newNode;
        }
    }

    void insertLast(int value){
        if(isEmpty()){
            insertFirst(value);
            return;
        }

        Node* newNode = new Node (value);
        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;
    }

    void deleteValue(int value){
        if(isEmpty()){
            cout<<"List is empty.";
            return;
        }

        Node* current = head;

        do{
            if(current->data == value){

                if(current->next == current){
                    delete current;
                    head = nullptr;
                    return;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;

                if(current == head){
                    head = current->next;

                }

                delete current;
                return;
            }
            current = current->next;
        }while(current != head);

    }


    int size(){
        if(isEmpty()) return 0;

        int count = 0;
        Node* temp = head;
        do{
            count++;
            temp=temp->next;
        }while (temp != head);
        
        return count;
    }

    void insertAtIndex(int index, int value){
        int n = size();

        if(index<0 || index > n){
            cout<<"Invalid index"<<endl;
            return;
        }

        Node* newNode = new Node(value);

        if(isEmpty()){
            head = newNode;
            return;
        }

        if(index == 0){
            Node* tail = head->prev;

            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;

            head = newNode;
            return;
        }

        Node* current = head;
        for(int i = 0; i < index-1; i++){
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }


    void deleteAtIndex(int index){

         if(isEmpty()){
            cout<<"List is empty"<<endl;
            return;
        }
         int n = size();

        if(index<0 || index >= n){
            cout<<"Invalid index"<<endl;
            return;
        }

        Node* current = head;

        if(n==1){
            delete head;
            head = nullptr;
            return;
        }

        if(index == 0){
            Node* tail = head->prev;
            
            Node* toDelete = head;
            head = head->next;

            tail->next = head;
            head->prev = tail;

            delete toDelete;
            return;
        }

        for(int i = 0; i<index; i++){
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
    }


    // Display Forward
    /*void displayForward() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(HEAD)\n";
    }

    // Display backward
    void displayBackward() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }

        Node* temp = head->prev;
        Node* tail = temp;

        do {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        } while (temp != tail);

        cout << "(TAIL)\n";
    }*/





};