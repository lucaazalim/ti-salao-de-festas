#pragma once

/**
 * @brief reads all structs from a file
 * @param filename the path for the file to be read
 * @param sizeOfStruct the size of the struct (sizeof)
 * @param amountOfStructs outputs the amount of structs that were found
 * @return a vector with all the structs found
 */
void* getAllStructsFromFile(char *filename, int sizeOfStruct, int *amountOfStructs);

/**
 * @brief read a specific struct from a file using the index
 * @param filename the path for the file to be read
 * @param index the index of the struct to be read
 * @param sizeOfStruct the size of the struct (sizeof)
 * @return the struct found
 */
void* getStructByIndexFromFile(char *filename, int index, int sizeOfStruct);

/**
 * @brief read the last struct from a file
 * @param filename the path for the file to be read
 * @param sizeOfStruct the size of the struct (sizeof)
 * @return the struct found
 */
void* getLastStructFromFile(char *filename, int sizeOfStruct);

/**
 * @brief append a struct to a file
 * @param filename the path for the file to be read
 * @param value the struct to be appended
 * @param sizeOfValue the size of the struct (sizeof)
 * @return 0 if success and something else if not
 */
int appendStructToFile(char *filename, void *value, int sizeOfValue);

/**
 * @brief update a struct in a file using the index
 * @param filename the path for the file to be read
 * @param structPointer the struct to be updated
 * @param index the index of the struct to be updated
 * @param sizeOfStruct the size of the struct (sizeof)
 */
void updateStructByIndexInFile(char *filename, void *structPointer, int index, int sizeOfStruct);