/*
  Реалізація:
  1 конструктор по замовчуванню:                   + IntList() 
  2 конструктор з параметрами:                     + IntList(int), IntList(string)
  3 копіювання (конструктор копіювання):           + IntList(IntList&)
  4 індексації (перевантаження []):                + operator[](int index)
  5 присваивания (перевантаження =):               + operator=(const IntList& p)
  6 візуалізації:                                  + toString()
  7 збереження (на диск) та відновлення:           +/2 std::ostream& operator <<(std::ostream&, IntList&); +/2 std::istream& operator >>(std::istream&, IntList&);
  8 діалогового керування:                         шоэта?
  9 "розумного доступу" (перевантаження ->):       зачем? +
  10 псевдозмінних (f(x)=const):                   см. выше +
  11 Перевантаження потокового введення/виведення: см. пункт 7
 
  Створення та використання файла бібліотеки (*.LIB): libintlist.dylib
  Повторне використання класів без їх перекомпіляції (ReUse): к libintlist.dylib прилагается intlist.h

  Списки та функціональне програмування. Мови функціонального програмування (Lisp, ML, Haskell та ін.)  
  містять єдину структура даних – список і єдину алгоритмічну структуру – функцію, яка також має вигляд списку. 
  Необхідно скласти програму, яка забезпечує роботу користувача зі списками у стилі функціонального 
  програмування.
  Користувач вводить:
   а) (= x (1 2 3))         - в результаті програма виконує наступні дії у список х заносяться значення 1,2,3. 
   б) (cdr x)                - в результаті на екран виводиться хвіст списку
   г) (= y (append x (-2 -1))) - в результаті список y буде містити наступні значення (1 2 3 -2 -1) 
  Використання псевдозмінних для списку аналогічно використанню псевдозмінних для стека.
 
 */

#include <iostream>
#include <fstream>
#include <map>
#include "intlist.h"

using namespace std;

int main (int argc, char * const argv[]) {
    cout << "running some tests...\n";
    cout << "default constructor:\n";
    IntList list;
    cout << "list.toString() method: "<< list.toString() << endl;
    cout << "list.push:\npush(20)\npush(30)\npush(40)\n"; 
    list.push(20);
    list.push(30);
    list.push(40);
    cout << list.toString() << endl;
    cout << "indexing:\nlist[2] => " << list[2] << endl;
    cout << "list[2] <= 3 : ";
    list[2] = 3;
    cout << list << endl;
    cout << "list.pop():\n";
    cout << "pop():" << list.pop() << endl;
    cout << "pop():" << list.pop() << endl;
    cout << "pop():" << list.pop() << endl;
    cout << "constructor with params (1 25 8):\n";
    IntList list2("(1 25 8)");
    cout << "stream output: list2 = " << list2 << endl;
    cout << "copy-constructor: IntList list3(list2) :";
    IntList list3(list2);
    cout << list3 << endl;
    cout << "pseudo-variables: list3(0,2):"<< list3(0,2) << endl;

    cout << "stream input:"; cin >> list;
    cout << "list = " << list << endl;
    cout << "writing list to file \"list.txt\"";

//    ofstream data("list.txt", ios_base::out||ios_base::trunc);
    ofstream data("list.txt", ios_base::out);
    data << list;
    data.close();
    cout << " ok\n";
    cout << "reading list from file \"list.txt\": ";
    IntList list4;
    ifstream data_in("list.txt", ios_base::in);
    data_in >> list4;
    data_in.close();
    cout << list4 << endl;
    
    cout << "\nstarting program\n";
    map<string, IntList*> lists;
    cout << "hello, Master of the universe, please enter your commands" << endl;
    string input;
    do {
        cout << ">> ";
        getline(cin, input);
        if (input[0] == '(' && input[input.size()-1] == ')') {
            //убираем скобки
            input = input.substr(1, input.size()-2);
            //комманда присваивания
            if (input[0] == '='){
                //убираем равно и пробел после него
                input = input.substr(2, input.size()-2);
                //получем имя списка
                int next_space = input.find_first_of(' ', 0);
                string list_name = input.substr(0, next_space);
                input = input.substr(next_space+1, input.size()-next_space-1);
//                cout << input << endl;
                if (input.substr(0,7) == "(append") {
                    //получается что новый список - какой-то существующий + что допишут
                    input = input.substr(8, input.size()-9);
//                    cout << input << endl;
                    int sp = input.find_first_of(' ', 0);
                    string exist_list_name = input.substr(0, sp);
                    string append_list = input.substr(sp+1,input.size()-sp);
//                    cout << exist_list_name << " - " << list << endl; 
                    if (lists[exist_list_name] == NULL)
                        cout << "there is no list " << exist_list_name << endl;
                    else {
                        IntList *new_list = new IntList(*lists[exist_list_name]);
                        
                        string line = append_list.substr(1, append_list.size()-2);
//                        cout << line << endl;
                        int line_size = line.size();
                        std::string tmp = "";
                        tmp += line[0];
                        for(int i=1; i<line_size; i++){
                            if (line[i] == ' '){
                                int value = atoi(tmp.c_str());
                                //std::cout << "item:" << item << std::endl;
                                new_list->push(value);
                                tmp.clear();
                            }
                            else {
                                tmp += line[i];
                            }
                        }
                        new_list->push(atoi(tmp.c_str()));
                        
                        if (lists[list_name] != NULL) delete lists[list_name];
                        lists[list_name] = new_list;
                        cout << list_name << " = " << *new_list << endl;
                    }
                } else if (input[0]=='(') {
                    //получается что тупо присвоить список
                    //получаем список    
//                    input = input.substr(0, input.size()-1);
//                    std::cout << list_name << " - " << input << std::endl;
                    IntList *list = new IntList(input);
                    //вдруг раньше что-нибудь записано, так удаляем его нах
                    if (lists[list_name] != NULL) delete lists[list_name];
                    lists[list_name] = list;
                    cout << list_name << " = " << *list << endl;
                } 
            }
            //комманда вывода хвоста
            else if (input.substr(0,3) == "cdr") {
                string list_name = input.substr(4,input.size()-4);
                if (lists[list_name] == NULL)
                    cout << "there is no list " << list_name << endl;
                else {
                    cout << lists[list_name]->printTail() << endl;
                }
            }
        }
        else std::cout << "error" << std::endl;
    } while (input != "exit");
    
//    map<string, IntList*> list_map;
//    IntList *one = new IntList("(1 2 3)");
//    IntList *two = new IntList("(4 5 6)");
//    list_map["one"] = one;
//    list_map["two"] = two;
//    std::cout << *list_map["one"] << "\t" << *list_map["two"] << std::endl;
//    delete one;
//    delete two;
    
    return 0;
}
