#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ip_functions.h"

int main(int, char **) {
    try {
        std::vector<std::vector<std::string> > ip_pool;
        std::ifstream file;
        file.open("C:\\Users\\Russell\\Desktop\\OTUS\\Homeworks\\16.03.2025\\ip_filter.tsv");
        
        // Решил прочитать ip адреса из приложеного файла
        std::string line;
        if (file.is_open()) {
            while(getline(file, line)){                 
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(split(v.at(0), '.'));
            }
        } else {
            printf("%s", "File not found!");
        }
        file.close(); 

        // TODO reverse lexicographically sort
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        
        // Ответ:
        //sort_asc(ip_pool); // По возраснанию
        sort_desc(ip_pool); // По убыванию

        // Вывод в консоль
        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
                if (ip_part != ip->cbegin()) { 
                    std::cout << "."; 
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // TODO filter by first byte and output
        // ip = filter(1)
        
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Ответ:
        filter(ip_pool, 1); // При успехе выведет на экран ip адрес
        
        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // Ответ:
        filter(ip_pool, 46, 70); // При успехе выведет на экран ip адрес

        // TODO filter by any byte and output
        // ip = filter_any(46)
        
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

        // Ответ:
        filter_any(ip_pool, 46); // При успехе выведет на экран ip адрес
    }    
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}