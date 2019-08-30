#ifndef MERSENNE_H
#define MERSENNE_H
#include <cstddef>

class Mersenne{
    private:
        // word size in bits
        static const size_t w = 32;
        // degree of recurrence
        static const size_t n = 624;
        // middle word
        static const size_t m = 397;
        // separation point of one word
        static const size_t r = 31;
        // coefficients of the rational normal form twist matrix
        static const unsigned int a = 0x9908B0DF;
        // tempering bit shifts
        static const size_t s = 7;
        static const size_t t = 15;
        // tempering bit mask
        static const unsigned int b = 0x9D2C5680;
        static const unsigned int c = 0xEFC60000;
        // additional tempering bit shifts/masks
        static const size_t u = 11;
        static const unsigned int d = 0xFFFFFFFF;
        static const size_t l = 18;
        // initialization constant
        static const unsigned int f = 1812433253;
        // Array of length n to store the state of the generator
        unsigned int MT[n];
        int index = n+1;
        // r number of 1s
        const unsigned int lower_mask = (1u << r) - 1;
        const unsigned int upper_mask = 1u << r;
    
        void twist(){
            for(size_t i = 0; i < n; i++){
                unsigned int x = (MT[i] & upper_mask) +
                    (MT[(i+1)%n] & lower_mask);
                unsigned int xA = x >> 1;
                if(x % 2){
                    xA ^= a;
                }
                MT[i] = MT[(i+m) % n] ^ xA;
            }
            index = 0;
        }

    public:
        Mersenne(size_t seed){
            index = n;
            MT[0] = seed;
            for(size_t i = 1; i < n; i++){
                MT[i] = ((1ull << 33) -1) & // lowest w bits of
                    (f * (MT[i-1] ^ (MT[i-1] >> (w - 2))) + i);
            }
        }

        unsigned int operator()(){
            if(index == n){
                twist();
            }

            unsigned int y = MT[index++];
            y = y ^ ((y >> u) & d);
            y = y ^ ((y << s) & b);
            y = y ^ ((y << t) & c);
            y = y ^ (y >> l);

            return ((1ull << 33) -1) & y; // lowest w bits of y
        }
};
#endif
