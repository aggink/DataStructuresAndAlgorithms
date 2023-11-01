#pragma once
#include <iostream>

using namespace std;

/// <summary>
/// ������� ������
/// </summary>
/// <typeparam name="T">��� ��������</typeparam>
template <class T>
struct Element {
    /// <summary>
    /// ��������
    /// </summary>
    T data;

    /// <summary>
    /// ��������� �� ��������� ������� ������
    /// </summary>
    Element* next;
};

/// <summary>
/// ����������� ������
/// </summary>
/// <typeparam name="T">��� ������</typeparam>
template <typename T>
class OneList {
private:
    /// <summary>
    /// ��������� �� ������ ������
    /// </summary>
    Element<T>* begin;

    /// <summary>
    /// ��������� �� ����� ������
    /// </summary>
    Element<T>* end;

    /// <summary>
    /// ���������� ��������� � ������
    /// </summary>
    unsigned long int count;

    /// <summary>
    /// ������� ������� � ������
    /// </summary>
    unsigned long int pos;

    /// <summary>
    /// ���������� �������, ������� ������������ �� ��������� �������, ������������ � ���������� �������
    /// </summary>
    /// <param name="index">������</param>
    /// <returns>������� ������</returns>
    Element<T>* move(int index)
    {
        if (count > 0)
        {
            Element<T>* t = begin;
            for (int i = 0; i < index; i++)
                t = t->next;
            return t;
        }
        return nullptr;
    }

    /// <summary>
    /// �������� ����� ������� � ����� ������
    /// </summary>
    /// <param name="_data">������</param>
    void add(T _data)
    {
        Element<T>* elem = new Element<T>;
        elem->data = _data;
        elem->next = nullptr;

        if (begin == nullptr)
        {
            begin = end = elem;
        }
        else
        {
            end->next = elem;
            end = elem;
        }

        count++;
    }

    /// <summary>
    /// ������� ������� � ������� index, ������� ���������� � 0
    /// </summary>
    /// <param name="index">������</param>
    void del(int index)
    {
        if (count == 0)
            return;

        if ((index < 0) || (index >= count))
            return;

        if (index == 0)
        {
            Element<T>* t = begin;
            begin = begin->next;
            delete t;

            if (count == 1) {
                end = nullptr;
            }
        }
        else
        {
            Element<T>* t = move(index - 1);
            Element<T>* t2 = t->next;

            t->next = t2->next;
            delete t2;

            if (index == count - 1) {
                end = t;
            }
        }

        count--;
    }

    /// <summary>
    /// �����, ������� ������ ����� �� ������
    /// </summary>
    void copy(const OneList& obj)
    {
        clear();

        Element<T>* t = obj.begin;

        for (int i = 0; i < obj.count; i++)
        {
            Add(t->data);
            t = t->next;
        }

        count = obj.count;
    }

public:

    /// <summary>
    /// �����������
    /// </summary>
    OneList()
    {
        begin = end = nullptr;
        count = 0;
        pos = 0;
    }

    /// <summary>
    /// ����������� �����������
    /// </summary>
    /// <param name="obj">������ ��� �����������</param>
    OneList(const OneList& obj)
    {
        copy(obj);
    }

    /// <summary>
    /// ����������
    /// </summary>
    ~OneList() {
        clear();
    }

    /// <summary>
    /// �����, ������� ��������� ������� � ������ ������
    /// </summary>
    /// <param name="_data">��������</param>
    void push_front(T data) {
        insert(0, data);
    }

    /// <summary>
    /// �����, ������� ��������� ������� � ����� ������
    /// </summary>
    /// <param name="_data">��������</param>
    void push_back(T _data) {
        add(_data);
    }

    /// <summary>
    /// ������� �������� item � �������� ������� index. ������� index ���������� � 0.
    /// </summary>
    /// <param name="index">������</param>
    /// <param name="item">��������</param>
    void insert(int index, T item)
    {
        if ((count != 0) && ((index < 0) || (index >= count)))
            return;

        Element<T>* t = move(index);

        if (t == nullptr)
        {
            add(item);
        }
        else
        {
            Element<T>* t2 = new Element<T>;
            t2->data = item;

            if (index == 0)
            {
                t2->next = begin;
                begin = t2;
            }
            else
            {
                t = move(index - 1);
                t2->next = t->next;
                t->next = t2;
            }

            count++;
        }
    }

    /// <summary>
    /// �����, ������� ������� ������� ������ ������
    /// </summary>
    void pop_front() {
        del(0);
    }

    /// <summary>
    /// �����, ������� ������� ������� � ����� ������
    /// </summary>
    void pop_back() {
        del(count - 1);
    }

    /// <summary>
    /// �����, ������� ������� �� ������ ����������� � ��������� ��������
    /// </summary>
    /// <param name="_data">��������</param>
    void remove(T data) {
        if (count == 0)
            return;

        Element<T>* current = begin;
        Element<T>* previous = nullptr;

        while (current != nullptr) {
            if (current->data == data) {
                if (previous == nullptr) {
                    begin = current->next;
                    delete current;
                    current = begin;
                }
                else {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                }
                count--;
            }
            else {
                previous = current;
                current = current->next;
            }
        }

        // Update the end if necessary
        if (count == 0) {
            end = nullptr;
        }
        else if (previous != nullptr && previous->next == nullptr) {
            end = previous;
        }
    }

    /// <summary>
    /// �����, ������� ������� ��� ��������
    /// </summary>
    void clear()
    {
        while (begin != nullptr)
            del(0);
    }

    /// <summary>
    /// �����, ������� ���������� ������ �������� ������� ��������� ������
    /// </summary>
    /// <returns>�������� ������� �������� ������</returns>
    T front() {
        if (begin == nullptr)
            throw "The list is empty";

        return begin->data;
    };

    /// <summary>
    /// �����, ������� ���������� �������� ���������� ��������� ������
    /// </summary>
    /// <returns>�������� ���������� �������� ������</returns>
    T back() {
        if (begin == nullptr)
            throw "The list is empty";

        return end->data;
    };

    /// <summary>
    /// �����, ���������� ���������� ��������� � ������
    /// </summary>
    /// <returns>���������� ���������� � ������</returns>
    int size() {
        return count;
    }

    /// <summary>
    /// �������� �������������� ������ ��� �������
    /// </summary>
    /// <param name="index">������</param>
    /// <returns>��������</returns>
    T& operator[](int index)
    {
        if ((index < 0) || (index > count - 1))
            throw out_of_range("Incorrect index");

        Element<T>* t = move(index);
        return t->data;
    }

    T operator++() {
        if (this->pos < this->count) {
            this->pos++;
        }

        return move(pos)->data;
    };

    T operator++(int) {
        if (this->pos < this->count) {
            this->pos++;
        }

        return move(pos)->data;
    };

    T operator--() {
        if (pos > 0) {
            pos--;
        }

        return move(pos)->data;
    }
};