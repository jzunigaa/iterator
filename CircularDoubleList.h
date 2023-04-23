#include <iostream>

using namespace std;

template<class T>
class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(){ 
            next = nullptr;
            prev = nullptr;
        }

        Node(T value){
            data = value;
            next = nullptr;
            prev = nullptr;
        } 
};

template<class T>
class IteratorCircularDoubleList{
    private:
        Node<T> *current;
        T data;
    
    public:
        
        IteratorCircularDoubleList(){
            this->current = new Node<T>();
        }
        
        IteratorCircularDoubleList(Node<T> *index){
            this->current = index;
        }

        bool operator!=(const IteratorCircularDoubleList &other){
            return this->current != other.current;
        }

        IteratorCircularDoubleList operator++(){
            this->current = this->current->next;
            return *this;
        }

        T operator*(){
            return this->current->data;
        }
};

template <class T>
class circularDoubleList {
    private:
        Node<T>* sentinel;
        int nodes;
    
    public:
        typedef IteratorCircularDoubleList<T> iterator;

    public:
        circularDoubleList() {
            this->sentinel = new Node<T>();
            this->nodes = 0;
        }

        ~circularDoubleList(){
         	while (sentinel->next != sentinel){
                 this->pop_front();
            }
            cout<<"Ha terminado"<<endl;
        }

        void push_front(T data){
            Node<T> *nuevo = new Node<T>(data);
            if (nodes == 0){
                nuevo->next = this->sentinel;
                nuevo->prev = this->sentinel;
                this->sentinel->next = nuevo;
                this->sentinel->prev = nuevo;
                this->nodes = this->nodes + 1;
            }else{
                nuevo->next = this->sentinel->next;
                nuevo->prev = this->sentinel;
                this->sentinel->next->prev = nuevo;
                this->sentinel->next = nuevo;
                this->nodes = this->nodes + 1;
            }
        }

        void push_back(T data){
            Node<T> *nuevo = new Node<T>(data);
            if (nodes == 0){
                this->push_front(data);
            }else{
                nuevo->prev = this->sentinel->prev;
                nuevo->next = this->sentinel;
                this->sentinel->prev->next = nuevo;
                this->sentinel->prev = nuevo;
                this->nodes = this->nodes + 1;
            }
        }

        void pop_front(){
            Node<T> *temp = sentinel->next->next;
            delete sentinel->next;
            sentinel->next = temp;
            temp->prev = sentinel;
        }

        void pop_back(){
            throw ("sin definir");
        }

        T& operator[](int pos){
            int _case = this->nodes/2;

            if(pos + 1 > this->nodes){
                cout<<"indice fuera de rango";
                return this->sentinel->data;
            }else {
                if(pos <= _case){
                    Node<T> *temp = this->sentinel->next;
                    for (int i = 0; i < pos; i++){
                    temp = temp->next;
                    }
                    return temp->data;
                }else{
                    Node<T> *temp = this->sentinel->prev;
                    for (int i = 1; i < this->nodes - pos; i++){
                        temp = temp->prev;
                    }
                    return temp->data;
                }
            };
        }

        bool is_empty(){
            return this->nodes == 0;
        }

        int size(){
            return this->nodes;
        }

        void display(){
            Node<T> *temp = this->sentinel->next;
            while (temp != sentinel){
                cout<<temp->data<<endl;
                temp = temp->next;
            }
        }

        IteratorCircularDoubleList<T> begin(){
            return iterator(this->sentinel->next);
        }

        IteratorCircularDoubleList<T> end(){
            return iterator(this->sentinel);
        }
};