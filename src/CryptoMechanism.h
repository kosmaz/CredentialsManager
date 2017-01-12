#ifndef CRYPTOMECHANISM_H
#define CRYPTOMECHAMISM_H


#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>

const int limit=100;
typedef char array_t[limit];

const int tmax=95;

class CryptoMechanism
{
	public:
		CryptoMechanism(int change=0);			
		void Decrypt(array_t& msg);
		void MakeRTable();
        void Encrypt(array_t& msg); 
        
    private:
        //data members
        char fTable[tmax]; 
        char fRTable[tmax];
        int fStart;
        int fIncreament;
};

#endif //CRYPTOMECHANISM_H
