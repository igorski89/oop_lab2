/*
 *  intlist.cpp
 *  lab2
 *
 *  Created by Igor Evsukov on 14.03.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "intlist.h"

IntList::IntList(){
    item = NULL;
};

IntList::IntList(int a){
    item = new ListNode;
    item->value = a;
    item->next = NULL;
};

IntList::IntList(std::string line) {
    item = NULL;
    line = line.substr(1,line.size()-2);
    int line_size = line.size();
    std::string tmp = "";
    tmp += line[0];
    for(int i=1; i<line_size; i++){
        if (line[i] == ' '){
            int value = atoi(tmp.c_str());
            //std::cout << "item:" << item << std::endl;
            push(value);
            tmp.clear();
        }
        else {
            tmp += line[i];
        }
    }
    push(atoi(tmp.c_str()));
}

IntList::IntList(IntList& p) {
    item == NULL;
    if (!p.isEmpty()){
        std::vector<int> vec = p.toVector();
        item = new ListNode;
        item->value = vec[0];
        item->next = NULL;
        for(int i=1; i<vec.size(); i++)
            push(vec[i]);
    }
    
//    std::vector<int>::iterator it;
//    for (it = vec.begin(); it < vec.end(); it++) 
//        push(*it);
    
};

IntList::~IntList(){
    ListNode *node = item;
    
    while(node != NULL){
        ListNode *currNode = node;
        node = node->next;
        delete currNode;
    }
    
};

void IntList::push(int p) {
    if (item == NULL) {
        //если список пуст
        item = new ListNode;
        item->value = p;
        item->next = NULL;
    }
    else {
        //в списке уже есть элементы - идем до конца
        
        //находим последний элемент
        ListNode *lastNode = item;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;
        ListNode *newNode = new ListNode;
        newNode->value = p;
        newNode->next = NULL;
        lastNode->next = newNode;
    }
};

int IntList::pop() {
    if (isEmpty())
        return 0;
    else if (item->next == NULL) {
        int ret = item->value;
//        delete item;
        item = NULL;
        return ret;
    }
    else {
        ListNode *preLastNode = item;
        //находим предпоследний элемент
        while(preLastNode->next->next != NULL)
            preLastNode = preLastNode->next;
        ListNode *lastNode = preLastNode->next;
        int ret = lastNode->value;
        preLastNode->next = NULL;
        delete lastNode;
        return ret;
    }
};

bool IntList::isEmpty() {
    //return item ? true : false;
    if (item == NULL) return true;
    else return false;
};

std::string IntList::toString() {
    std::stringstream str_stream;
    str_stream << "(";
    ListNode *node = item;
    while(node != NULL){
        str_stream << node->value << " ";
        node = node->next;
    };
    std::string str = str_stream.str();
    if (!isEmpty()) str = str.substr(0, str.size()-1);
    str += ")";
    return str;
};

std::string IntList::printTail(){
    if (isEmpty()) return "()";
    if (item->next==NULL) return "()";
    std::stringstream str_stream;
    str_stream << "(";
    ListNode *node = item->next;
    while(node != NULL){
        str_stream << node->value << " ";
        node = node->next;
    };
    std::string str = str_stream.str();
    str = str.substr(0, str.size()-1);
    str += ")";
    return str;
};

std::vector<int> IntList::toVector() {
    std::vector<int> ret;
    ListNode *node = item;
    while(node != NULL) {
        ret.push_back(node->value);
        node = node->next;
    }
    return ret;
};

int& IntList::operator[](int index){
    int *zero = new int(0);
    if (index < 0 || isEmpty()) return *zero;
    else {
        ListNode *currNode = item;
        int i = 0;
        while(i != index && currNode != NULL) {
            currNode = currNode->next;
            i++;
        }
        //ну вдруг индекс больше задали чем на самом деле
        if (i < index)
            return *zero;
        else
            return currNode->value;
    }
};

//IntList& IntList::operator[](int ) {
//        
//}

IntList& IntList::operator=(const IntList& p) {
    item = p.item;
    return *this;
};

IntList& IntList::operator->() {
    return *this;
}

IntList& IntList::operator()(const int s, const int e) {
    IntList *ret = new IntList();
    for(int i = s; i < e; i++) 
        ret->push(this->operator[](i));
    
    return *ret;
}


std::ostream& operator << (std::ostream& os, IntList& list) {
    return os << list.toString();
}

std::istream& operator >>(std::istream& is, IntList& list) {
    std::string line;
    std::getline(is, line);
    line = line.substr(1,line.size()-2);
//    std::cout << line << std::endl;
    int line_size = line.size();
    std::string tmp = "";
    tmp += line[0];
    for(int i=1; i<line_size; i++){
        if (line[i] == ' '){
            int item = atoi(tmp.c_str());
//            std::cout << "item:" << item << std::endl;
            list.push(item);
            tmp.clear();
        }
        else {
            tmp += line[i];
        }
    }
    list.push(atoi(tmp.c_str()));
    return is;
}