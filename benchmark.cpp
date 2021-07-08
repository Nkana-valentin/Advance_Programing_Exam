#include "bst.hpp"
#include <cstdlib> // rand
#include <iostream>
#include <ctime>
#include <chrono>
#include <map>

int main(int argc, char **argv)
{

    try
    {

        std::srand(std::time(nullptr));
        // std::srand(3)

        if (argc != 2)
            throw std::runtime_error("Check the number of arguments");
        int number_nodes = std::atoi(argv[1]);

        bst<int, int> tree{}; // empty constructor
        std::map<int, int> map{};

        for (auto i = 0; i < number_nodes; ++i)
        {
            int k = std::rand();
            tree.insert({k, k});
            map.insert({k, k});
        }

        for (int i = 0; i < 11; i += 1)
        {

            auto t_i = std::chrono::high_resolution_clock::now();
            tree.find(i);
            auto t_e = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_e - t_i);
            std::cout << elapsed.count() << std::endl;
        }

        std::cout << std::endl;

        tree.balance();

        for (int i = 0; i < 11; i += 1)
        {

            auto t_i = std::chrono::high_resolution_clock::now();
            tree.find(i);
            auto t_e = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_e - t_i);
            std::cout << elapsed.count() << std::endl;
        }

        std::cout << std::endl;

        std::map<int, int>::iterator it;

        for (auto i = 0; i < 11; i += 1)
        {

            auto t_i = std::chrono::high_resolution_clock::now();
            it = map.find(i);
            auto t_e = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_e - t_i);
            if (it != map.end())
                std::cout << "found it" << std::endl;
            std::cout << elapsed.count() << std::endl;
        }
        return 0;
    }

    catch (const std::exception &e)
    {

        std::cerr << e.what() << '\n';
        return 1;
    }

    catch (...)
    {

        std::cerr << "Unknown exception occurred" << '\n';
    }
}