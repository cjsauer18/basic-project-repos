#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

//Desc: Internal method to test if a positive integer is a prime number.
//Pre: Integer must be supplied.
//Post: Returns true if number is prime, false otherwise.
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

//Desc: Internal method to return a prime number at least as large as n.
//Pre: Integer parameter must be passed
//Post: Returns first prime number closest to n.
int nextPrime( int n )
{
    if( n <= 0 )
        n = 3;

    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

//Desc: Hash routine for string objects.
//Pre: A key must be supplied
//Post: Returns hashed value
int hash1( const string & key )
{
    int hashVal = 0;

    for(unsigned int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

//Desc: Hash routine for integer keys
//Pre: Key must be supplied
//Post: Returns hashed value
int hash1( int key )
{
    return key;
}
