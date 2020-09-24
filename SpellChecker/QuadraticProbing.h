#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime( int n );
int hash1( const string & key );
int hash1( int key );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
   
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      {
          makeEmpty( );
      }
    //Desc: Contains method, returns boolean if location of object is active.
    //Pre: Object must be supplied
    //Post: Returns true if index position is active, false otherwise.
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }
    
    //Desc: makeEmpty method, clears array and resets the table property to empty
    //Pre: Practical use if table is not empty.
    //Post: Table is cleared of contents.
    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
        
        numberOfObjectsInTable = 0;
    }
    //Desc: Insert method, takes in a hashed object and calls the find position method that locates an open slot based on hashed value. Sets returned position to the parameter object.
    //Pre: Object must be supplied into the table, table must not be full.
    //Post: Returns true if object was hashed and inserted successfully, false otherwise.
    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPosInsert( x );
        if( isActive( currentPos ) ){//shouldnt happen unless array is full?
            return false;
        }
        array[ currentPos ] = HashEntry( x, ACTIVE );
        numberOfObjectsInTable++;
            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );
        
        return true;
    }
    //Desc: Remove method, takes in a hashed object and find's its location in the table by checking if the location is active. If not, table location is marked as deleted, and is removed from the table.
    //Pre: Object must be passed in and location must be supplied by findPos
    //Post: Returns true if object is found and deleted, false otherwise.
    bool remove( const HashedObj & x ) 
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        numberOfObjectsInTable--;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };//status types
    //statistic methods
    //Desc: Method gets collision data via a vector and finds the average of all collisions.
    //Pre: collision vector should be filled with data to report on
    //Post: Returns the average of the collisions.
     double getCollisionLengthAverage(){
            double sum = 0;
            double size = collisionAverage.size();
            for(int i = 0; i < collisionAverage.size(); ++ i){
                sum += collisionAverage[i];
            }
            return sum/size;
        }
    //Desc: Funtion returns the largest element in the collision vector (longest collision chain)
    //Pre: Requires collision vector to be filled with data
    //Post: Returns the longest collision chain count
    int getLongestCollision(){
        auto biggest = max_element(collisionAverage.begin(), collisionAverage.end());
        return *biggest;
    }
    //Desc: Function returns the total amount of collisions in the table.
    //Pre: Collision vector must be initialized.
    //Post: Returns number of collisions that occurred from the hash table insertions.
    int getTotalCollisions(){
        int number = 0;
        for(int i = 0; i < collisionAverage.size(); ++i){
            if(collisionAverage[i] > 1){
                number++;
                }
        }
        return number;//or numberOfCollisionInsertions
    }
    //Desc: Function calculates the load factor, and returns as a double.
    //Pre: Array should be filled with data
    //Post: Returns double of value.
    double getLoadFactor(){
        double temp = array.size();
        return numberOfObjectsInTable/temp;
    }
    //Desc: size of array getter method.
    //Pre: Array must be initialized
    //Post: Returns array size
    int getArraySize(){
        return array.size();
    }
    //Desc: function returns counter to the number of elements inside the hash table.
    //Pre: Hash table/array should be initialized
    //Post: Returns object counter as int
    int getNumberOfObjectsInTable(){
        return numberOfObjectsInTable;
    }
    
    
  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) {
          }
    };
    
    vector<HashEntry> array;
    int currentSize;
    //Desc: Function returns a boolean that checks if a position in the table is occupied or not.
    //Pre: Hash table/array must be initilaized
    //Post: Returns true if location is active, false otherwise.
    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }
    
    //Desc: Non const auxiliary find position method that is called by insert. Records insertion data while finding valid insertion locations for objects.
    //Pre: Requires object to be passed and hashed by another function.
    //Post: Returns location of object to be placed in hash table, along with recording collision statistics (if any).
    int findPosInsert( const HashedObj & x )
    {
        int offset = 1;
        int currentPos = myhash( x );

        collisionCount = 1;//if no collision, count is at least 1
          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
        while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
        {
            if(collisionCount == 1){
                numberOfCollisionInsertions++;//increments once
            }
            collisionCount++;
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }
        if(collisionCount > longestCollision){
            longestCollision = collisionCount;
        }
        collisionAverage.push_back(collisionCount);
        return currentPos;
    }
    //Desc: Const auxiliary find position function. Called by any other methods that are not from insert(). Returns first available index location of object to be hashed.
    //Pre: Requires object to be passed and hashed by another function.
    //Post: Returns position of element in hash table.
   int findPos( const HashedObj & x ) const
      {
          int offset = 1;
          int currentPos = myhash( x );
          
            // Assuming table is half-empty, and table length is prime,
            // this loop terminates
          while( array[ currentPos ].info != EMPTY &&
                  array[ currentPos ].element != x )
          {
            
              currentPos += offset;  // Compute ith probe
              offset += 2;
              if( currentPos >= array.size( ) )
                  currentPos -= array.size( );
          }
          return currentPos;
      }
    //Desc: Rehash function. Table size is doubled if capacity is exceeded.
    //Pre: Requires array to reach maximum capacity.
    //Post: Old table is copied over to a new array of double the size.
    void rehash( )
    {
       
        if(collisionCount > longestCollision){
            longestCollision = collisionCount;
        }
        collisionCount = 0; //reinitialize
        numberOfCollisionInsertions = 0;//reinitialize
        vector<HashEntry> oldArray = array;
        
            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );
    }
    //Desc: Hash function. Takes in an element, and returns its hashed value.
    //Pre: Object must be passed in, auxiliary hash methods must be supplied.
    //Post: Returns value as a key
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash1( x );

        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );

        return hashVal;
    }
    int longestCollision = 0;
    int numberOfObjectsInTable = 0;
    int collisionCount = 1;
    int numberOfCollisionInsertions = 0;
    vector<int> collisionAverage;
};

#endif
