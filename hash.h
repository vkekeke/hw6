#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        if(k.empty() ){
            return 0;
        }
        unsigned long long w[5] = {0,0,0,0,0};
        int tracker = k.length() -1;
        for (int j=4; j>=0; --j){
            HASH_INDEX_T digitNum[6] = {0,0,0,0,0,0};
            size_t temp = 0;
            while(tracker >=0 && temp <6){
                digitNum[temp] = letterDigitToNumber(k[tracker]);
                tracker--;
                temp++;
            }
            w[j] = convertToBase10(digitNum); 
        }
        return rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4];

    }

    // converting base-36 to decimal
    unsigned long long convertToBase10(HASH_INDEX_T* w) const
    {
        int r = 36;
        return (((((w[5]*r + w[4])*r + w[3])*r + w[2])*r + w[1])*r + w[0]);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'a' && letter <= 'z'){
            return static_cast<HASH_INDEX_T>(letter - 'a');
        }
        else if(letter >= 'A' && letter <= 'Z'){
            return static_cast<HASH_INDEX_T>(letter - 'A');
        }
        else if(letter >= '0' && letter <= '9'){
            return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        }
        else {
            throw std::invalid_argument("Invalid character in string");
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
