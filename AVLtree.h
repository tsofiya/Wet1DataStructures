//
// Created by tsofi on 23/04/2019.
//

#ifndef WET1DATASTRUCTURES_AVLTREE_H
#define WET1DATASTRUCTURES_AVLTREE_H

#include <iostream>


template<class T, class K>
class AVLtree {
private:
    typedef struct Node_t {
        Node_t *rightSon;
        Node_t *leftSon;
        int height;
        K key;
        T data;
    } Node;
    Node *root;

public:
    AVLtree() {
        root = NULL;
    }


    ~AVLtree(){
        deleteTree(root);
    }

    void insert(const K &key, const T &data) {
        if (!root) {
            root = new Node{NULL, NULL, 0, K(key), T(data)};
            return;
        }

        Node *n = new Node{NULL, NULL, 0, K(key), T(data)};
        recInsert(n, root);

    }

    void remove(const K& key){
        recRemoval(root, key);
    }

    void preOrder() {
        preOrder(root);
        std::cout <<std::endl;
    }

private:
    void preOrder(Node *root) {
        if (root != NULL) {
            std::cout << root->key << " ";
            preOrder(root->leftSon);
            preOrder(root->rightSon);
        }

    }

    void recRemoval(Node*n, const K& key){
        if (n==NULL)
            return;
        if (n->key<key)
            recRemoval(n->rightSon, key);
        else if (n->key>key)
            recRemoval(n->leftSon, key);
        else if (n->leftSon==NULL && n->rightSon==NULL){
            delete(n);
            return;
        }
        else if (n->leftSon==NULL){
            Node* temp= n->rightSon;
            n->rightSon=temp->rightSon;
            n->leftSon= temp->leftSon;
            n->key= K(temp->key);
            n->data= T(temp->data);
            delete(temp);
        }
        else if (n->rightSon==NULL){
            Node* temp= n->leftSon;
            n->rightSon=temp->rightSon;
            n->leftSon= temp->leftSon;
            n->key= temp->key;
            n->data= temp->data;
            delete(temp);
        }
        else{
            Node* temp= n->rightSon;
            while (temp->leftSon!=NULL)
                temp=temp->leftSon;
            n->key= temp->key;
            n->data= temp->data;
            n->height= calcHeight(n);
            temp->key= key;
            recRemoval(n, key);
        }

        n->height= calcHeight(n);
        preformRotation(n);
    }

    void deleteTree(Node* n){
        if (n==NULL)
            return;
        deleteTree(n->leftSon);
        deleteTree(n->rightSon);
        delete(n);
    }

    void recInsert(Node *in, Node *curr) {
        if (in->key < curr->key) {
            if (curr->leftSon == NULL) {
                curr->leftSon = in;
            } else
                recInsert(in, curr->leftSon);
        } else {
            if (curr->rightSon == NULL) {
                curr->rightSon = in;
            } else
                recInsert(in, curr->rightSon);
        }

        curr->height = calcHeight(curr);
        preformRotation(curr);
    }

    //Decides if a rotation is required and preforms a rotation if necessary.
    void preformRotation(Node *curr) {
        int balance = getNodeBalance(curr);
        if (balance == 2) {
            if (getNodeBalance(curr->leftSon) == -1)
                lrRotation(curr);
            else if (getNodeBalance(curr->leftSon) >= 0)
                llRotation(curr);
        }
        if (balance == -2) {
            if (getNodeBalance(curr->rightSon) == 1)
                rlRotation(curr);
            else if (getNodeBalance(curr->leftSon) <= 0)
                rrRotation(curr);
        }
    }


    // Get Balance factor of a specific node
    int getNodeBalance(Node *N) {
        if (N == NULL)
            return 0;
        if (N->rightSon == NULL && N->leftSon == NULL)
            return 0;
        if (N->rightSon == NULL)
            return N->leftSon->height+1;
        if (N->leftSon == NULL)
            return -1-N->rightSon->height;
        return (N->leftSon->height) - (N->rightSon->height);
    }

    int calcHeight(Node *n) {
        if (n->rightSon == NULL && n->leftSon == NULL)
            return 0;
        if (n->rightSon == NULL)
            return 1 + n->leftSon->height;
        if (n->leftSon == NULL)
            return 1 + n->rightSon->height;
        return 1 + max(n->leftSon->height, n->rightSon->height);
    }

    //preform LL rotation
    void llRotation(Node *a) {
        Node * b= a->leftSon;
        Node* moveA= new Node;
        moveA->data = T(a->data);
        moveA->key = K(a->key);
        moveA->rightSon = a->rightSon;
        moveA->leftSon = b->rightSon;
        moveA->height = calcHeight(moveA);
        a->data= T(b->data);
        a->key= K(b->key);
        a->leftSon= b->leftSon;
        a->rightSon= moveA;
        delete(b);
    }

    //preform LR rotation
    void lrRotation(Node *a) {
        Node *b = a->leftSon;
        Node *c = b->rightSon;
        Node *moveA = new Node;
        moveA->data = T(a->data);
        moveA->key = K(a->key);
        moveA->rightSon = a->rightSon;
        moveA->leftSon = c->rightSon;
        moveA->height = calcHeight(moveA);
        a->rightSon = moveA;
        a->key = K(c->key);
        a->data = T(c->data);
        b->rightSon = c->leftSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);
    }

    //preform RR rotation
    //TODO: check correctness
    void rrRotation(Node *a) {
        Node *b = a->rightSon;
        Node *moveA = new Node;
        moveA->data = T(a->data);
        moveA->key = K(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = b->leftSon;
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->data = T(b->data);
        a->key = K(b->key);
        a->rightSon = b->rightSon;
        a->height = calcHeight(a);
        delete (b);
    }

    //preform RL rotation
    void rlRotation(Node *a) {
        Node *b = a->rightSon;
        Node *c = b->leftSon;
        Node *moveA = new Node;
        moveA->data = T(a->data);
        moveA->key = T(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = c->leftSon;
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->data = T(c->data);
        a->key = T(c->key);
        b->leftSon = c->rightSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);

    }

    int max(int a, int b) {
        return a < b ? b : a;
    }


};

#endif //WET1DATASTRUCTURES_AVLTREE_H
