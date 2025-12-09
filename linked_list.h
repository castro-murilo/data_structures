#pragma once

template<typename T>
class LinkedList{
    struct Node {
        T element;
        Node* previous = nullptr;
        Node* next = nullptr;

        void place_between(Node* n1, Node n2) {
            connect(n1, this);
            connect(this, n2);
        }
    };

    Node* aux_node;

    public:
        LinkedList(){
            connect(&aux_node, &aux_node);
        }

        ~LinkedList(){
        }

        void push_front(T element){
            Node* node = new Node{element};
            node->place_between(&aux_node, first());
        }

        void push_back(T element){
            Node* node = new Node{element};
            node->place_between(last(), &aux_node);
        }

        void remove_first(){
            remove(first());
        }

        void remove_last(){
            remove(last());
        }

        
    private:
        static void connect(Node* n1, Node* n2) {
            n1->next = n2;
            n2->previous = n1;
        }

        Node* first() const {
            return aux_node.next;
        } 

        Node* last() const {
            return aux_node.previous;
        }

        static void remove(Node* node){
            connect(node->previous, node->next);
            delete node;
        } 
    };