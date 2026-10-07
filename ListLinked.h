#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked;

template <typename T>
std::ostream& operator<<(std::ostream& out, ListLinked<T>& list);


template <typename T>
class ListLinked : public List<T>
{
private:
    Node<T>* first;
    int n;

public:
    ListLinked();
    ~ListLinked() override;

    void insert(int pos, T e) override;
    void append(T e) override;
    void prepend(T e) override;
    T remove(int pos) override;
    T get(int pos) override;
    int search(T e) override;
    bool empty() override;
    int size() override;

    T operator[](int pos);

    friend std::ostream& operator<< <T>(
        std::ostream& out,
        ListLinked<T>& list
    );
};


template <typename T>
ListLinked<T>::ListLinked()
{
    first = nullptr;
    n = 0;
}


template <typename T>
ListLinked<T>::~ListLinked()
{
    while (first != nullptr)
    {
        Node<T>* aux = first->next;

        delete first;

        first = aux;
    }

    n = 0;
}


template <typename T>
void ListLinked<T>::insert(int pos, T e)
{
    if (pos < 0 || pos > n)
    {
        throw std::out_of_range("Posición inválida!");
    }

    if (pos == 0)
    {
        first = new Node<T>(e, first);
    }
    else
    {
        Node<T>* current = first;

        for (int i = 0; i < pos - 1; i++)
        {
            current = current->next;
        }

        current->next = new Node<T>(e, current->next);
    }

    n++;
}


template <typename T>
void ListLinked<T>::append(T e)
{
    insert(n, e);
}


template <typename T>
void ListLinked<T>::prepend(T e)
{
    insert(0, e);
}


template <typename T>
T ListLinked<T>::remove(int pos)
{
    if (pos < 0 || pos >= n)
    {
        throw std::out_of_range("Posición inválida!");
    }

    Node<T>* aux;
    T e;

    if (pos == 0)
    {
        aux = first;
        first = first->next;
    }
    else
    {
        Node<T>* current = first;

        for (int i = 0; i < pos - 1; i++)
        {
            current = current->next;
        }

        aux = current->next;
        current->next = aux->next;
    }

    e = aux->data;

    delete aux;

    n--;

    return e;
}


template <typename T>
T ListLinked<T>::get(int pos)
{
    if (pos < 0 || pos >= n)
    {
        throw std::out_of_range("Posición inválida!");
    }

    Node<T>* current = first;

    for (int i = 0; i < pos; i++)
    {
        current = current->next;
    }

    return current->data;
}


template <typename T>
int ListLinked<T>::search(T e)
{
    Node<T>* current = first;

    for (int i = 0; i < n; i++)
    {
        if (current->data == e)
        {
            return i;
        }

        current = current->next;
    }

    return -1;
}


template <typename T>
bool ListLinked<T>::empty()
{
    return n == 0;
}


template <typename T>
int ListLinked<T>::size()
{
    return n;
}


template <typename T>
T ListLinked<T>::operator[](int pos)
{
    return get(pos);
}


template <typename T>
std::ostream& operator<<(std::ostream& out, ListLinked<T>& list)
{
    out << "List => [" << std::endl;

    Node<T>* current = list.first;

    while (current != nullptr)
    {
        out << "  " << current->data << std::endl;

        current = current->next;
    }

    out << "]";

    return out;
}


#endif
