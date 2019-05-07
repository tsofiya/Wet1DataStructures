//
// Created by tsofi on 23/04/2019.
//

#ifndef WET1DATASTRUCTURES_AVLTREE_H
#define WET1DATASTRUCTURES_AVLTREE_H

#include "Wet1Exceptions.h"

using namespace Wet1Utils;

#include <iostream>


template<class K, class T>
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
    int size;

public:
    AVLtree() : size(0) {
        root = NULL;
    }


    ~AVLtree() {
        deleteTree(root);
    }

    void insert(const K &key, const T &data) {
        if (!root) {
            root = new Node{NULL, NULL, 0, K(key), T(data)};
            size++;
            return;
        }

        Node *n = new Node{NULL, NULL, 0, K(key), T(data)};
        recInsert(n, root);
        size++;

    }

    void remove(const K &key) {
        recRemoval(root, NULL, key);
        size--;
    }

    //Return the data for a certain key. If the key does not exist, throws KeyNotExist();
    T &getByKey(const K &key) {
        return recGetByKey(root, key);
    }

    void addTreeToTree(AVLtree& tree){
        if (tree.root==NULL) return;
        addTreeToTreeRec(tree.root);
    }

    void preOrderPrint() {
        preOrder(root);
        std::cout << std::endl;
    }


    T* getAllData() {
        if (size == 0) {
            return NULL;
        }
        T* dataArray = new T[size];
        int *pos = new int;
        *pos = -1;
        recGetAllData(root, dataArray, pos);
        delete (pos);
        return dataArray;
    }

    int getTreeSize(){
        return size;
    }

    bool elementExistsByKey(const K& key){
        return recElementExistsByKey(root, key);
    }

    void ChangeKey(K& lastK, K& newK){
        T d= getByKey(lastK);
        remove(lastK);
        insert(newK, d);
    }


private:
    void preOrder(Node *root) {
        if (root != NULL) {
            std::cout << "("<<root->key << ", "<<root->data<<") ";
            preOrder(root->leftSon);
            preOrder(root->rightSon);
        }

    }

    void addTreeToTreeRec(Node*n){
        if (n->rightSon!=NULL)
            addTreeToTreeRec(n->rightSon);
        if (n->leftSon!=NULL)
            addTreeToTreeRec(n->leftSon);
        insert(n->key, n->data);
    }

//this can throw an exception, but it shouldnt...
    bool recElementExistsByKey(Node*n, const K& key){
        if (n==NULL) {
            return false;
        }
        if (n->key==key) {
            return true;
        }
        else {
            if (key < n->key) {
                return recElementExistsByKey(n->leftSon, key);
            }
            else {
                return recElementExistsByKey(n->rightSon, key);
            }
        }
    }

    void recGetAllData(Node *curr, T *dataArray, int *pos){
        if (curr == NULL)
            return;
        (*pos)++;
        dataArray[*pos] = T(curr->data);
        recGetAllData(curr->leftSon, dataArray, pos);
        recGetAllData(curr->rightSon, dataArray, pos);
    }


    T &recGetByKey(Node *n, const K &key) {
        if (n == NULL)
            throw KeyNotExist();
        if (n->key == key) {
            return n->data;
        } else {
            if (key < n->key) {
                return recGetByKey(n->leftSon, key);
            } else {
                return recGetByKey(n->rightSon, key);
            }
        }
    }

    void recRemoval(Node *n, Node *f, const K &key) {
        if (n == NULL)
            return;
        if (n->key < key)
            recRemoval(n->rightSon, n, key);
        else if (n->key > key)
            recRemoval(n->leftSon, n, key);
        else if (n->leftSon == NULL && n->rightSon == NULL) {
            if (f != NULL) {
                if (f->leftSon == n) {
                    f->leftSon = NULL;
                } else if (f->rightSon == n) {
                    f->rightSon = NULL;
                }
                delete (n);
                return;
            } else {

                delete (n);
                root = NULL;
                return;
            }
        } else if (n->leftSon == NULL) {
            Node *temp = n->rightSon;
            n->rightSon = temp->rightSon;
            n->leftSon = temp->leftSon;
            n->key = K(temp->key);
            n->data = T(temp->data);
            delete (temp);
        } else if (n->rightSon == NULL) {
            Node *temp = n->leftSon;
            n->rightSon = temp->rightSon;
            n->leftSon = temp->leftSon;
            n->key = temp->key;
            n->data = temp->data;
            delete (temp);
        } else {
            Node *temp = n->rightSon;
            while (temp->leftSon != NULL)
                temp = temp->leftSon;
            n->key = temp->key;
            n->data = temp->data;
            n->height = calcHeight(n);
            temp->key = key;
            recRemoval(n, f, key);
        }

        n->height = calcHeight(n);
        preformRotation(n);
    }

    void deleteTree(Node *n) {
        if (n == NULL)
            return;
        deleteTree(n->leftSon);
        deleteTree(n->rightSon);
        delete (n);
    }

    //Todo: this is the problematic function causing a segmentation fault
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
            return N->leftSon->height + 1;
        if (N->leftSon == NULL)
            return -1 - N->rightSon->height;
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
        Node *b = a->leftSon;
        Node *moveA = new Node;
        moveA->data = T(a->data);
        moveA->key = K(a->key);
        moveA->rightSon = a->rightSon;
        moveA->leftSon = b->rightSon;
        moveA->height = calcHeight(moveA);
        a->data = T(b->data);
        a->key = K(b->key);
        a->leftSon = b->leftSon;
        a->rightSon = moveA;
        delete (b);
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
        moveA->key = K(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = c->leftSon;
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->data = T(c->data);
        a->key = K(c->key);
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
