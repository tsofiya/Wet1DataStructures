//
// Created by tsofi on 21/04/2019.
//

#ifndef WET1DATASTRUCTURES_BIDIRECTIONALLIST_H
#define WET1DATASTRUCTURES_BIDIRECTIONALLIST_H

#include <istream>

using std::ostream;

template <class T>
struct Node {
    T data;
    Node *next;
    Node *previous;
};

template<class T>
class BiDirectionalList {
private:
    Node<T> *head;
    Node<T> *tail;
    friend ListIterator;

public:

    class ListIterator{
    private:
        BiDirectionalList *list;
        Node* current;
    public:
        ListIterator(BiDirectionalList *lst, bool hOrT):list(lst) {
            if (lst==NULL)
                throw NullArgument();
            if (lst->head==NULL)
                current==NULL;
            else if (hOrT){
                current==head;
            } else {
                current == tail;
            }
        }

        ListIterator&operator++(){
            if (current==NULL)
                return *this;
            current=current->next;
            return *this;
        }

        ListIterator&operator--(){
            if (current==NULL)
                return *this;
            current=current->previous;
            return *this;
        }

        T&operator*(){
            return current->data;
        }

    };

    BiDirectionalList(Node<T> *h = NULL, Node<T> *t = NULL) : head(h), tail(t) {}

    Node<T>* push(const T& data){
        Node<T> *n= new Node<T>;
        n->data= data;
        if (head==NULL) {
            tail = n;
            head = n;
            n->next=NULL;
            n->previous =NULL;
        }
        else
        {
            n->next = head;
            n->previous = NULL;
            head->previous =n;
            head = n;
        }
        return n;

    }

    friend ostream &operator<<(ostream &os, BiDirectionalList<T> &list) {
        os << "direction 1: "<<std::endl;
        os << "BEGIN <-> ";
        Node<T> *ptr = list.head;
        while (ptr != NULL) {
            os << ptr->data << " <-> ";
            ptr = ptr->next;
        }
        os << "END";
        return os;
    }

    ~BiDirectionalList() {
            Node<T>* currentPos = head;
            while (currentPos!=NULL)
            {
                Node<T>* nextPos=currentPos->next;
                delete(currentPos);
                currentPos=nextPos;
            }
    }

    ListIterator& beginForward(){
        return ListIterator(this, true);
    }

    ListIterator& beginBackward(){
        return ListIterator(this, false);
    }

    int size(){
        int s= 0;
        Node* ptr=head;
        while (ptr!=NULL) {
            s++;
            ptr=ptr->next;
        }
        return s;
    }

};


#endif //WET1DATASTRUCTURES_BIDIRECTIONALLIST_H
