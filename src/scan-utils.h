#pragma once

/**
 * @brief clears the input buffer
 */
void clearInputBuffer();

/**
 * @brief removes the new line character from a string
 * @param string 
 */
void removeNewLine(char *string);

/**
 * @brief scans a text from the user
 * @param destination the char pointer for the scanned text
 * @param destinationLength the length of the destination
 */
void scanText(char *destination, int destinationLength);

/**
 * @brief listens to any key pressed by the user
*/
int getch();