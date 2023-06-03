#pragma once

void* getAllStructsFromFile(char *filename, int sizeOfStruct, int *amountOfStructs);

void* getStructByIndexFromFile(char *filename, int index, int sizeOfStruct);

void* getLastStructFromFile(char *filename, int sizeOfStruct);

int appendStructToFile(char *filename, void *value, int sizeOfValue);

void updateStructByIndexInFile(char *filename, void *structPointer, int index, int sizeOfStruct);