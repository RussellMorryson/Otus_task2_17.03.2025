#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>

#include "ip_functions.h"
#include "version.h"

int version() {
	return PROJECT_VERSION_PATCH;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

// Запись ip адреса в отдельный вектор
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

// Сортировка по возрастанию
void sort_asc(std::vector<std::array<int, 4> > &ip_pool) {
    std::array<int, 4> temp; // временная табица
    int size = ip_pool.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (i != j){
                if (ip_pool[i][0] < ip_pool[j][0]) {
                    temp = ip_pool[i];
                    ip_pool[i] = ip_pool[j];
                    ip_pool[j] = temp;                    
                } else if (ip_pool[i][0] == ip_pool[j][0]) {
                    if (ip_pool[i][1] < ip_pool[j][1]) {
                        temp = ip_pool[i];
                        ip_pool[i] = ip_pool[j];
                        ip_pool[j] = temp;                        
                    } else if (ip_pool[i][1] == ip_pool[j][1]) {
                        if (ip_pool[i][2] < ip_pool[j][2]) {
                            temp = ip_pool[i];
                            ip_pool[i] = ip_pool[j];
                            ip_pool[j] = temp;                            
                        } else if (ip_pool[i][2] == ip_pool[j][2]) {
                            if (ip_pool[i][3] < ip_pool[j][3]) {
                                temp = ip_pool[i];
                                ip_pool[i] = ip_pool[j];
                                ip_pool[j] = temp;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Сортировка по убыванию
void sort_desc(std::vector<std::array<int, 4> > &ip_pool) {
    std::array<int, 4> temp; // временная табица
    int size = ip_pool.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (i != j){
                if (ip_pool[i][0] > ip_pool[j][0]) {
                    temp = ip_pool[i];
                    ip_pool[i] = ip_pool[j];
                    ip_pool[j] = temp;                   
                } else if (ip_pool[i][0] == ip_pool[j][0]) {
                    if (ip_pool[i][1] > ip_pool[j][1]) {
                        temp = ip_pool[i];
                        ip_pool[i] = ip_pool[j];
                        ip_pool[j] = temp;                        
                    } else if (ip_pool[i][1] == ip_pool[j][1]) {
                        if (ip_pool[i][2] > ip_pool[j][2]) {
                            temp = ip_pool[i];
                            ip_pool[i] = ip_pool[j];
                            ip_pool[j] = temp;                            
                        } else if (ip_pool[i][2] == ip_pool[j][2]) {
                            if (ip_pool[i][3] > ip_pool[j][3]) {
                                temp = ip_pool[i];
                                ip_pool[i] = ip_pool[j];
                                ip_pool[j] = temp;                                
                            }
                        }
                    }
                }
            }
        }
    }
}

// Вывод на экран ip адреса
void print_ip_v4(std::array<int, 4> &ip_v4, int &num) {
    std::cout << num << ") ";
    int size = ip_v4.size();
    for(int y = 0; y < size; y++) {
        if(y != size-1) {
            std::cout << ip_v4[y] << '.';
        } else {
            std::cout << ip_v4[y] << std::endl;
        }        
    }
}

// Поиск ip адреса по маске
void filter(std::vector<std::array<int, 4> > &ip_pool, int a1, int a2, int a3, int a4) {    
    std::cout << "\n*** FILTER FUNCTION ***\n";
    std::cout << "Find ip of: " << a1 << '.' << a2 << '.' << a3 << '.' << a4 << std::endl;
    int size = ip_pool.size();
    if (a1 != 0 && a2 == 0 && a3 == 0 && a4 == 0) {
        for(int i = 0; i < size; i++) {
            if (ip_pool[i][0] == a1) {
                print_ip_v4(ip_pool[i], i);
            }
        }
    } else if (a1 != 0 && a2 != 0 && a3 == 0 && a4 == 0) {
        for(int i = 0; i < size; i++) {
            if (ip_pool[i][0] == a1 
            && ip_pool[i][1] == a2) {
                print_ip_v4(ip_pool[i], i);
            }
        }  
    } else if (a1 != 0 && a2 != 0 && a3 != 0 && a4 == 0) {
        for(int i = 0; i < size; i++) {
            if (ip_pool[i][0] == a1 
            && ip_pool[i][1] == a2 
            && ip_pool[i][2] == a3) {
                print_ip_v4(ip_pool[i], i);
            }
        }  
    } else if (a1 != 0 && a2 != 0 && a3 != 0 && a4 != 0) {
        for(int i = 0; i < size; i++) {
            if (ip_pool[i][0] == a1 
            && ip_pool[i][1] == a2 
            && ip_pool[i][2] == a3
            && ip_pool[i][3] == a4) {
                print_ip_v4(ip_pool[i], i);
            }
        } 
    }
}

// Поиск ip адреса по числу
void filter_any(std::vector<std::array<int, 4> > &ip_pool, int a) {
    std::cout << "\n*** FILTER FUNCTION ***\n";
    std::cout << "Find in ip of: " << a << std::endl;    
    int size = ip_pool.size();
    for(int i = 0; i < size; i++) {
        if (ip_pool[i][0] == a 
        || ip_pool[i][1] == a 
        || ip_pool[i][2] == a 
        || ip_pool[i][3] == a) {
            print_ip_v4(ip_pool[i], i);
        }
    }
}