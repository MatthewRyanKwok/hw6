#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        unsigned long long w[5] = {0,0,0,0,0}; //w array

        int len = k.length();
        int g = 4; //starts from w[4] -> w[3] etc
        int i = len - 1;

        while (i >= 0 && g >= 0) {
            unsigned long long val = 0;
            unsigned long long pow = 1;
            //builds the num for this group, up to 6 chars
            for (int j = 0; j < 6 && i >= 0; ++j, --i) {//increment j, decrement i at same time
                HASH_INDEX_T num = letterDigitToNumber(k[i]);
                val += num * pow;
                pow *= 36;
            }
            w[g] = val;
            --g;
        }
        unsigned long long hash = 0;
        for (int i = 0; i < 5; i++) { //final hash
            hash += rValues[i] * w[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'A' && letter <= 'Z') {
            letter = letter - 'A' + 'a'; //lowercase
        }
        if (letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
        }
        return 0;
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
