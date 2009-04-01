/*
 *  intlist.h
 *  lab2
 *
 *  Created by Igor Evsukov on 14.03.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <vector>


struct ListNode {
    int value;
    ListNode *next;
};

class ostream;

class IntList {
protected:
    ListNode *item;
public:
    //конструкторы
    //по-умолчанию голове присваивается 0
    IntList();
    //значение головы - значение параметра
    IntList(int);
    //параметр - строка вида (1 2 3 4 5)
    IntList(std::string);
    //конструктор копирования. Создается deep-копия
    IntList(IntList&);
    //деструктор
    ~IntList();
    //добавляет новый элемент в список
    virtual void push(int);
    //выталкивает последний элемент из списка
    virtual int pop();
    //пустой ли список
    virtual bool isEmpty();
    //возвращает строковое представление списка - (1 2 3 ... 666)
    virtual std::string toString();
    //возвращает представление списка в виде std::vector
    virtual std::vector<int> toVector();
    //возвращает хвост списка в виде строки
    virtual std::string printTail();
    //перегрузка оператора индексирования []
    int& operator[](int);
    
    //IntList& operator[](int);
    //перегрузка оператора присваивания
    IntList& operator=(const IntList&);
    
    IntList& operator->();
    
    IntList& operator()(const int s, const int e);
//    void operator()(const int s, const int e);
};

std::ostream& operator <<(std::ostream&, IntList&);
std::istream& operator >>(std::istream&, IntList&);