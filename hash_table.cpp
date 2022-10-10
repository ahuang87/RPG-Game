/*
 Student Name: Andy Huang
 Date: 3/12/2020

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h" // header file for the hash table 


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
  
  HashTableEntry* Newentry = (HashTableEntry*)malloc(sizeof(HashTableEntry));  // Creates HashTableEntry Pointer, for the HashTable.

  Newentry->key= key;           // Creates the local variable key in the hashtableentry.
  Newentry->value= value;       // Creates the local variable value in the hashtableentry.
  Newentry->next = NULL;        // Creates the local variable next in the hashtableentry.

  return Newentry;              // Returns the pointer to the hash table entry. (We named our pointer Newentry.) 
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
  int index= hashTable->hash(key);                     // Define variable index. Finds where the key is using hash(key)

  HashTableEntry* NewNode = hashTable->buckets[index];   // Since we have the bucket number we have to get inside the bucket using our variable index. 

  while (NewNode) {                     // Implement a while loop to find the input key that matches the key Newnode that we have found. 
    if (NewNode->key == key) {          // If the input key matches, we return the NewNode, and this stops the whileloop. 
      return NewNode;
    }
    NewNode = NewNode->next;            // Since we have not found a matched key we have to look at the next one, so we set the pointer to the next. 
  }
  return NULL;                          // If there is no NewNode, and no match we would return NULL.
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, in it each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }
  return newTable;   // Return the new HashTable struct.
}

void destroyHashTable(HashTable* hashTable) {

  for (int i=0; i <(hashTable->num_buckets); i++){                // Free Node and Value. 
    HashTableEntry* location = hashTable->buckets[i];   // Need to get bucket location to start to destroy every node and value. 
    while(location){
      free(location->value);                        // Free the value. 
      HashTableEntry* next = location->next;
      free(location);
      location = next; 
    }
  }
  free(hashTable->buckets);   // Free the bucket
  free(hashTable);            // Free the hashtable. 
}                             // No memory leaks using valgrind --leak-check=full ./ht_tests 


void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
  HashTableEntry* item = findItem(hashTable, key);   // We find (hashTable, key) and assign it to the pointer item. 
  void *holdvalue;                // Create a variable which is matched with the input of void*. 

  if (item){
    holdvalue = item->value;      // If the item is present then we try to get the value. 
    item->value = value;          // assigned to the value. 
    return holdvalue;             // Return the previous variable holdvalue, which matched with (item->value). 
  }   else{
    int var = hashTable->hash(key);     // Index of the key. 
    //HashTableEntry* location = hashTable->buckets[var];
    HashTableEntry* CreatedNode = createHashTableEntry(key, value);
    if(CreatedNode == NULL){
    return NULL;  // If Malloc fails. 
  }
    CreatedNode->next = hashTable->buckets[var];  // Insert the new node at the heas od the linked list.
    hashTable->buckets[var] = CreatedNode;        // Node at the head of the linked list. 
    return NULL;                // When inserting an item whose key does not already exist in the HT, return NULL.
  }

}

void* getItem(HashTable* hashTable, unsigned int key) {
  HashTableEntry* Node = findItem(hashTable, key);     // Locate the given input in the HashTable and find the bucket location. 

  if (Node){                               // If there is a Node, you get the item from the node. 
    return Node-> value;                   // Return The found value in the node. 
  }
  return NULL;                            // If there isnt a node, then return null. 
}

void* removeItem(HashTable* hashTable, unsigned int key) {

  int var = hashTable->hash(key);                            // Gets the index. 
  HashTableEntry* location = hashTable->buckets[var];        // Gets the bucket index. 

  HashTableEntry* prev = NULL;                             // We set prev to NULL in case there is an edge case that there is no node present. 
  HashTableEntry* current = location;                      // Current is what we a re looking at so we can set it to the bucket index. 
   

  HashTableEntry* Locator = findItem(hashTable, key);
  if(Locator){
    while(current->key != key){
    prev=current;
    current= current->next;
    }

    if (prev){
    prev->next = current->next;
    } else {
    hashTable->buckets[var] = current->next;
    }

    void* foundvalue = current->value;
    free(current);                                         // Free the hash table entry from the heap. 
    return foundvalue;                                     // Return the pointer of the value based on they key when found. 
    } else {
      return NULL;                                         // If there is no found pointer value then we return NULL. 
    }
  }

void deleteItem(HashTable* hashTable, unsigned int key) {
  void* removeditem = removeItem(hashTable,key);  //Find the item in the table based on the key. We can use our function remove item. 
  free(removeditem);                             //Free the value found.  
  return;                                       // Stops the funtion. 
}
