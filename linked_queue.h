// Copyright 2016 Thomas Machado

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <stdexcept>  // C++ exceptions

namespace structures {

//! Uma classe
    /*!
    Descreve comportamento de uma fila encadeada
*/
template<typename T>
class LinkedQueue {
 public:
    //! Contrutor
    /*!
        Construtor default
    */
    LinkedQueue() {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destrutor default
    */
    ~LinkedQueue() {
        clear();
    }

    //! Um método
    /*!
        Limpa a fila deletando todos os nodes
    */
    void clear() {
        Node* current = head;
        Node* previous;
        while (current != nullptr) {
            previous = current;
            current = current->next();
            delete previous;
        }
        size_ = 0;
        head = nullptr;
        tail = nullptr;
    }

    //! Um método
    /*!
        \param data
        Adiona elemento na fila
    */
    void enqueue(const T& data) {
        Node* newNode = new Node(data, nullptr);
        if (newNode == nullptr) {
            throw std::out_of_range("Full queue");
        } else {
            if (empty()) {
                head = newNode;
            } else {
                tail->next(newNode);
            }
            tail = newNode;
            size_ = size_ + 1;
        }
    }

    //! Um método
    /*!
        \param data
        retira elemento na fila
    */
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Empty queue");
        } else {
            if (size_== 1) {
                T back = head->data();
                delete head;
                head = nullptr;
                tail = nullptr;
                size_ = size_ - 1;
                return back;
            } else {
                Node* previous = head;
                T back = head->data();
                head = head->next();
                delete previous;
                size_ = size_ - 1;
                return back;
            }
        }
    }
    //! Um método
    /*!
        \return T&
        retorna o valor do início da fila
    */
    T& front() {
        if (size_ == 0) {
            throw std::out_of_range("Empty queue");
        } else {
            return head->data();
        }
    }

    //! Um método
    /*!
        \return T&
        retorna o valor do final da fila
    */
    T& back() {
        if (empty()) {
            throw std::out_of_range("Empty queue");
        } else {
            return tail->data();
        }
    }

    //! Um método
    /*!
        \return bool
        Informa se a fila da vazia
    */
    bool empty() const {
        return size_ == 0;
    }

    //! Um método
    /*!
        \return bool
        Informa tamanho da fila
    */
    std::size_t size() const {
        return size_;
    }

 private:
        class Node {  // Elemento
         public:
            explicit Node(const T& data):
                data_{data}
            {}

            Node(const T& data, Node* next):
                data_{data},
                next_{next}
            {}

            T& data() {  // getter: dado
                return data_;
            }

            const T& data() const {  // getter const: dado
                return data_;
            }

            Node* next() {  // getter: próximo
                return next_;
            }

            const Node* next() const {  // getter const: próximo
                return next_;
            }

            void next(Node* node) {  // setter: próximo
                next_ = node;
            }

         private:
            T data_;
            Node* next_{nullptr};
        };
     Node* end() {  // último nodo da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i) {
                it = it->next();
            }
            return it;
        }
    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

#endif
