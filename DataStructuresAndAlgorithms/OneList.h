#pragma once
#include <iostream>

using namespace std;

/// <summary>
/// Элемент списка
/// </summary>
/// <typeparam name="T">Тип значения</typeparam>
template <class T>
struct Element {
    /// <summary>
    /// Значение
    /// </summary>
    T data;

    /// <summary>
    /// Указатель на следующий элемент списка
    /// </summary>
    Element* next;
};

/// <summary>
/// Односвязный список
/// </summary>
/// <typeparam name="T">Тип списка</typeparam>
template <typename T>
class OneList {
private:
    /// <summary>
    /// Указатель на начало списка
    /// </summary>
    Element<T>* begin;

    /// <summary>
    /// Указатель на конец списка
    /// </summary>
    Element<T>* end;

    /// <summary>
    /// Количество элементов в списке
    /// </summary>
    unsigned long int count;

    /// <summary>
    /// Текущая позиция в списке
    /// </summary>
    unsigned long int pos;

    /// <summary>
    /// Внутренняя функция, которая перематывает на указанную позицию, используется в нескольких методах
    /// </summary>
    /// <param name="index">Индекс</param>
    /// <returns>Элемент списка</returns>
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
    /// Добавить новый элемент в конец списка
    /// </summary>
    /// <param name="_data">Индекс</param>
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
    /// Удалить элемент в позиции index, позиция нумеруется с 0
    /// </summary>
    /// <param name="index">Индекс</param>
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
    /// Метод, который делает копию из списка
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
    /// Конструктор
    /// </summary>
    OneList()
    {
        begin = end = nullptr;
        count = 0;
        pos = 0;
    }

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="obj">Список для копирования</param>
    OneList(const OneList& obj)
    {
        copy(obj);
    }

    /// <summary>
    /// Деструктор
    /// </summary>
    ~OneList() {
        clear();
    }

    /// <summary>
    /// Метод, который добавляет элемент в начало списка
    /// </summary>
    /// <param name="_data">Значение</param>
    void push_front(T data) {
        insert(0, data);
    }

    /// <summary>
    /// Метод, который добавляет элемент в конец списка
    /// </summary>
    /// <param name="_data">Значение</param>
    void push_back(T _data) {
        add(_data);
    }

    /// <summary>
    /// Вставка элемента item в заданную позицию index. Позиция index нумеруется с 0.
    /// </summary>
    /// <param name="index">Индекс</param>
    /// <param name="item">Значение</param>
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
    /// Метод, который удаляет элемент начале списка
    /// </summary>
    void pop_front() {
        del(0);
    }

    /// <summary>
    /// Метод, который удаляет элемент в конце списка
    /// </summary>
    void pop_back() {
        del(count - 1);
    }

    /// <summary>
    /// Метод, который удаляет из списка совпадающие с элементом значения
    /// </summary>
    /// <param name="_data">Значение</param>
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
    /// Метод, который удаляет все элементы
    /// </summary>
    void clear()
    {
        while (begin != nullptr)
            del(0);
    }

    /// <summary>
    /// Метод, который возвращает первый значение первого элекмента списка
    /// </summary>
    /// <returns>Значение первого элемента списка</returns>
    T front() {
        if (begin == nullptr)
            throw "The list is empty";

        return begin->data;
    };

    /// <summary>
    /// Метод, который возвращает значение последнего элекмента списка
    /// </summary>
    /// <returns>Значение последнего элемента списка</returns>
    T back() {
        if (begin == nullptr)
            throw "The list is empty";

        return end->data;
    };

    /// <summary>
    /// Метод, возвращает количество элементов в списке
    /// </summary>
    /// <returns>Количество элекментов в списке</returns>
    int size() {
        return count;
    }

    /// <summary>
    /// Оператор индексирования списка как массива
    /// </summary>
    /// <param name="index">Индекс</param>
    /// <returns>Значение</returns>
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