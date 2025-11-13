#pragma once

#include <iostream>
#include <functional>
#include <queue>

template<typename T>
class BSTree {
    struct Node{
        T value;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root = nullptr;

    public:
        ~BSTree(){
            destroy(root);
        }

        void insert(const T& value){
            root = insert(root, value);
        } 
        
        bool contains(const T& value) {
            return contains(root, value);
        }

        void remove(const T& value){
            root = remove(root, value);
        }

        void each(std::function<void(T)> callback) {
            in_order_traversal(root, callback);
        }

        std::vector<std::vector<T>> show(){
            return level_order_traversal(root);
        }
       
    private:
        Node* insert(Node* node, T value){
            if (!node) {
                return new Node{value};
            }
            if (value < node->value) {
                node->left = insert(node->left, value);
            } else if (node->value < value){
                node->right = insert(node->right, value);
            }
            return node;
        }

        void destroy(Node* node){
            if (!node){
                return;
            }
            destroy(node->left);
            destroy(node->right);
            delete node;
        }

        bool contains(Node* node, const T& value) const{
            if (!node) {
                return false;
            }
            if (value < node->value) {
                return contains(node->left, value);
            } else if (node->value < value) {
                return contains(node->right, value);
            } else {
                return true;
            }
        }

        Node* remove(Node* node, T& value){
            if (!node) {
                return nullptr;
            }

            if (value < node->value) {
                node->left = remove(value, node->left);
            } else if (node->value < value) {
                node->right = remove(value, node->right);        
            } else {
                Node* result = node;
                if (node->left && node->right){
                    node->right->left = move_node(node->left, node->right);
                    result = node->right;
                } else if (node->left) {
                    result = node->left;
                } else {
                    result = node->right;
                }
                delete node;
                return result;
            }
            return node;
        }

        Node* move_node(Node* node, Node* to){
            if (!to) {
                return node;
            }
            if (node->value < to->value) {
                to->left = move_node(node, to->left);
            } else if (to->value < node->value) {
                to->right = move_node(node, to->right);
            }
            return to;
        }

        //TREE TRAVERSALS 
        void in_order_traversal(Node* node, std::function<void(T)> callback) {
            if (!node) {
                return;
            }
            in_order_traversal(node->left, callback);
            callback(node->value);
            in_order_traversal(node->right, callback);
        }

        void pre_order_traversal(Node* node, std::function<void(T)> callback) {
            if (!node) {
                return;
            }
            callback(node->value);
            pre_order_traversal(node->left, callback);
            pre_order_traversal(node->right, callback);
        }

        void post_order_traversal(Node* node, std::function<void(Node*)> callback) {
            if (!node) {
                return;
            }
            post_order_traversal(node->left, callback);
            post_order_traversal(node->right, callback);
            callback(node->value);
        }

        std::vector<std::vector<T>> level_order_traversal(Node* node) {
            std::vector<std::vector<T>> result;
            if (!node) {
                return result;
            }
            std::queue<Node*> q;
            q.push(node);

            while (!q.empty()){
                std::vector<T> level = {};
                std::size_t level_size = q.size(); 
                for (std::size_t i = 0; i < level_size; ++i) {
                    Node* front = q.front();
                    q.pop();
                    if (front->left) {
                        q.push(front->left);
                    }
                    if (front->right) {
                        q.push(front->right);
                    }

                    level.push_back(front->value);
                }
                result.push_back(level);
            }
            return result;
        }
};

