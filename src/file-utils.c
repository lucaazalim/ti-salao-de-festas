#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *filename, char *mode)
{

    FILE *file = fopen(filename, mode);

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo: %s\n", filename);
    }

    return file;
}

void* getAllStructsFromFile(char *filename, int sizeOfStruct, int *amountOfStructs)
{

    FILE *file = fopen(filename, "a+");

    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    int fileSize = ftell(file);

    *amountOfStructs = fileSize / sizeOfStruct;

    void *structs = malloc(fileSize);

    fseek(file, 0, SEEK_SET);
    fread(structs, fileSize, 1, file);
    fclose(file);

    return structs;

}

void *getStructByIndexFromFile(char *filename, int index, int sizeOfStruct)
{

    FILE *file = openFile(filename, "a+");

    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, index * sizeOfStruct, SEEK_SET);

    void *structPointer = malloc(sizeOfStruct);

    if (fread(structPointer, sizeOfStruct, 1, file) != 1)
    {
        free(structPointer);
        structPointer = NULL;
    }

    fclose(file);

    return structPointer;
}

void *getLastStructFromFile(char *filename, int sizeOfStruct)
{

    FILE *file = openFile(filename, "a+");

    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, -sizeOfStruct, SEEK_END);

    void *structPointer = malloc(sizeOfStruct);

    fread(structPointer, sizeOfStruct, 1, file);

    fclose(file);

    return structPointer;
}

int appendStructToFile(char *filename, void *structPointer, int sizeOfStruct)
{

    FILE *file = fopen(filename, "ab");

    if (file == NULL)
    {

        printf("Criando arquivo: %s\n", filename);

        file = openFile(filename, "wb");

        if (file == NULL)
        {
            return 0;
        }
    }

    int result = fwrite(structPointer, sizeOfStruct, 1, file);

    fclose(file);

    return result;
}

void updateStructByIndexInFile(char *filename, void *structPointer, int index, int sizeOfStruct)
{

    FILE *file = openFile(filename, "rb+");

    if (file == NULL)
    {
        return;
    }

    fseek(file, index * sizeOfStruct, SEEK_SET);

    fwrite(structPointer, sizeOfStruct, 1, file);

    fclose(file);
}
