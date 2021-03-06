// pa2.cpp

// COMP2011 (Fall 2020)
// Assignment 2: Subtring Pattern Matching
//
// Name: LI Bingxuan
// Student ID: 20677251
// Email: blibb@connect.ust.hk

#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

// C string termination character
const char NULL_CHAR = '\0';

// The "not found" flag
const int NOT_FOUND = -1;

// Single character wildcard
const char DOT = '.';

// Zero or single character wildcard
const char QMARK = '?';

// Zero or more character wildcard
const char PERCENT = '%';

// Matches the beginning of a string
const char CARET = '^';

int matchSub(const char str[], const char pattern[], int &length, int start);
int matchSubWithDot(const char str[], const char pattern[], int &length, int start);
int matchSubWithQmark(const char str[], const char pattern[], int &length, int start);
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start);
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos, int patPos);
int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos, int patPos);
int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos, int patPos);

// Declare additional helper functions below when necessary


// Helper for Task 0.
// Returns the length of the substring in `str` located at `strPos` that
// matches `pattern`.
// If `pattern` is not found, returns the value `NOT_FOUND`.
// The `pattern` may contain the single character wildcard (`.`).
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    if (pattern[patPos] == PERCENT)
        return findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos);
    if (pattern[patPos] == QMARK)
        return findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos);
    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR) // the substring is shorter than the pattern to match
        return NOT_FOUND;
    if (pattern[patPos] == DOT || pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithDot(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
}


// Task 0 (0 point)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the length of the substring matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the single character wildcard (`.`).
int matchSubWithDot(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithDot(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithDot(str, pattern, length, start + 1);
}
// Helper function for Task 1
int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    if (pattern[patPos] == DOT)
        return findSubLenAtStrPosWithDot(str, pattern, strPos, patPos);
    if (pattern[patPos] == PERCENT)
        return findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos);

    if (pattern[patPos]!= NULL_CHAR && str[strPos] == NULL_CHAR && pattern[patPos] != QMARK) //pattern?????????
        return NOT_FOUND;

    if (pattern[patPos] == NULL_CHAR && str[strPos] == NULL_CHAR)
        return 0;

    if (pattern[patPos] == QMARK && str[strPos] == NULL_CHAR)
        return findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos+1);

    if (pattern[patPos] == QMARK && str[strPos] != NULL_CHAR) //pattern????????? ???????
    {
        if (pattern[patPos+1] == NULL_CHAR)
            return 1;
        int result_when_qmark_count = findSubLenAtStrPosWithQmark(str, pattern, strPos+1, patPos+1);
        int result_when_qmark_not_count = findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos+1);

        if (result_when_qmark_count != NOT_FOUND)
            return result_when_qmark_count+1;
        if (result_when_qmark_not_count != NOT_FOUND)
            return result_when_qmark_not_count;
        
    } 
    
    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos+1] == NULL_CHAR)
            return 1;
        int result_when_same = findSubLenAtStrPosWithQmark(str, pattern, strPos+1, patPos+1);
        if (result_when_same != NOT_FOUND)
            return 1 +result_when_same;
    }
    return NOT_FOUND;
}



// Task 1 (40 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or single character wildcard (`?`).


int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithQmark(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
    
}

// Helper function for Task 2
int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    if (pattern[patPos] == DOT)
        return findSubLenAtStrPosWithDot(str, pattern, strPos, patPos);

    if (pattern[patPos] == QMARK)
        return findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos);       

    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR && pattern[patPos] != PERCENT ) //pattern?????????
        return NOT_FOUND;

    if (pattern[patPos] == NULL_CHAR && str[strPos] == NULL_CHAR)
        return 0;

    if (pattern[patPos] == PERCENT)  //pattern????????? ???%???
    {
        if(str[strPos] == NULL_CHAR)
            return findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos+1);

        if(str[strPos] != NULL_CHAR)
        {
            if (pattern[patPos+1] == NULL_CHAR && str[strPos+1] != NULL_CHAR)
            {
                int result_when_percent_count_lots = findSubLenAtStrPosWithPercent(str, pattern, strPos+1, patPos);

                if (result_when_percent_count_lots != NOT_FOUND)
                    return 1+result_when_percent_count_lots;
            } 
            if (pattern[patPos+1] == NULL_CHAR)
                return 1;   

            int result_when_percent_count_lots = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos); // % is not empty and is multiple char
            if (result_when_percent_count_lots != NOT_FOUND)
                return 1 + result_when_percent_count_lots;

            int result_when_percent_count = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos + 1); // % is not empty and counted -----------------------case 1
            if (result_when_percent_count != NOT_FOUND)
                return 1 + result_when_percent_count;

            int result_when_percent_not_count = findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos + 1); // % is empty and not counted --------------------------case 2
            if (result_when_percent_not_count != NOT_FOUND)
                return result_when_percent_not_count;         
        }
    }    

    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos+1] == NULL_CHAR)
            return 1;
        int result_when_same = findSubLenAtStrPosWithPercent(str, pattern, strPos+1, patPos+1);
        if (result_when_same != NOT_FOUND)
            return result_when_same+1;
    }
    return NOT_FOUND;
}

// Task 2 (35 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or more character wildcard (`%`).
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithPercent(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1);
}

// Task 3 (25 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the '^', '.', '?', and '%' wildcards.
int matchSub(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength;

    if (pattern[0] == CARET)
    {
        if (pattern[1] != PERCENT && pattern[1] != QMARK && pattern[1] != DOT && pattern[1] != str[0])
            return NOT_FOUND;
        else 
        {
            testLength = findSubLenAtStrPosWithDot(str, pattern, start, 1);
            if (testLength != NOT_FOUND) 
                {
                    length = testLength;
                    return start;
                }
        }    
    }
    else
    {
        testLength = findSubLenAtStrPosWithDot(str, pattern, start, 0);
            if (testLength != NOT_FOUND) 
            {
                length = testLength;
                return start;
            }
    }
    return matchSub(str, pattern, length, start+1);
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

// Given `str`, prints the substring that begins at `start` with length `length`.
// Raises an assertion error when an attempt is made to print beyond the available length.
// You are not allowed to use loops in your solution, though we use them here.
void printString(const char str[], const int start, const int length)
{
    for (int i = start; i < start + length; i++)
        assert(str[i] != NULL_CHAR);
    for (int i = start; i < start + length; i++)
        cout << str[i];
}

// A driver program for testing your solution.
int main()
{
    const int MAX_LENGTH = 1000;
    char pattern[MAX_LENGTH];
    char str[MAX_LENGTH];
    int option, pos, length;

    while (true)
    {
        cout << "Task No. (-1 to exit): "; cin >> option;
        if (cin.fail())
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (option == -1)
            break;
        if (option < 0 || option > 3)
            continue;
        cout << endl;
        cout << "Enter the string to match: "; cin >> str;
        cout << "Enter the pattern to match: "; cin >> pattern;
        length = 0;
        switch (option)
        {
            case 0:
                pos = matchSubWithDot(str, pattern, length);
                break;
            case 1:
                pos = matchSubWithQmark(str, pattern, length);
                break;
            case 2:
                pos = matchSubWithPercent(str, pattern, length);
                break;
            case 3:
                pos = matchSub(str, pattern, length);
                break;
        }
        cout << endl;
        if (pos == NOT_FOUND)
        {
            cout << "Pattern is not found." << endl;
        }
        else
        {
            cout << "Pattern's first occurence is at " << pos << ", with longest possible length = " << length << "." << endl;
            cout << "Matched substring is '"; printString(str, pos, length); cout << "'." << endl;
        }
        cout << "---------------------------------------------------------------------" << endl;
    }
    cout << "bye" << endl;
}
