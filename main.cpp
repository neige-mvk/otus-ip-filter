#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <sstream>

union B
{
    in_addr_t i;
    uint8_t byte[4];
} itoch;

struct Address {
    std::string s;
    uint32_t i;

    Address(std::string string_form, uint32_t number_form)
        : s(string_form), i(number_form){};
};

uint32_t addressNumberForm(const std::string& ip) {
    struct in_addr addr;
    if (inet_aton(ip.c_str(), &addr) == 0) {
        std::cout << "Invalid address" << std::endl;
        exit(EXIT_FAILURE);
    }

    itoch.i = addr.s_addr;
    itoch.i = (itoch.byte[3]<<0) | (itoch.byte[2]<<8) | (itoch.byte[1]<<16) | (itoch.byte[0]<<24);

    return itoch.i;
}

void filter(short first_byte, const std::vector<Address>& ip_pool) {
    for(const auto& ip : ip_pool) {
        itoch.i = ip.i;
        if (itoch.byte[3] == first_byte)
            std::cout << ip.s << std::endl;
    }
}

void filter(short first_byte, short second_byte, const std::vector<Address>& ip_pool) {
    for(const auto& ip : ip_pool) {
        itoch.i = ip.i;
        if (itoch.byte[3] == first_byte && itoch.byte[2] == second_byte)
            std::cout << ip.s << std::endl;
    }
}

void filter_any(short any_byte, const std::vector<Address>& ip_pool) {
    for(const auto& ip : ip_pool) {
        itoch.i = ip.i;
        if (itoch.byte[3] == any_byte 
        || itoch.byte[2] == any_byte 
        || itoch.byte[1] == any_byte 
        || itoch.byte[0] == any_byte)
            std::cout << ip.s << std::endl;
    }
}

int main(int, char**)
{
    try
    {
        std::vector<Address> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::stringstream linestream(line);
            std::string data;
            std::getline(linestream, data, '\t');
            ip_pool.push_back(Address(data, addressNumberForm(data)));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin( ), ip_pool.end( ), [ ]( const auto& lhs, const auto& rhs )
        {
            return lhs.i > rhs.i;
        });

        for(const auto& ip : ip_pool) {
            std::cout << ip.s << std::endl;
        }

        filter(1, ip_pool);

        filter(46, 70, ip_pool);

        filter_any(46, ip_pool);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
