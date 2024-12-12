//
//  main.cpp
//  valeria class homework p2
//
//  Created by Valeria  Bukova on 12.12.2024.
//

#include <iostream>
using namespace std;


const int MAX_WORDS = 1000;
const int MAX_WORD_LENGTH = 50;


char toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}


bool isAlnum(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}


void preprocessWord(const char* word, char* cleanWord) {
    int j = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (isAlnum(word[i])) {
            cleanWord[j++] = toLowerCase(word[i]);
        }
    }
    cleanWord[j] = '\0';
}


bool areStringsEqual(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}


void copyString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


void buildWordFrequency(const char* inputFileName, char words[MAX_WORDS][MAX_WORD_LENGTH], int frequencies[MAX_WORDS], int& wordCount) {
    FILE* file = fopen(inputFileName, "r");
    if (!file) {
        cerr << "Ошибка: Не удалось открыть файл " << inputFileName << endl;
        return;
    }

    char buffer[1024];
    char cleanWord[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", buffer) != EOF) {
        preprocessWord(buffer, cleanWord);
        if (stringLength(cleanWord) == 0) continue;

        bool found = false;
        for (int i = 0; i < wordCount; ++i) {
            if (areStringsEqual(words[i], cleanWord)) {
                frequencies[i]++;
                found = true;
                break;
            }
        }

        if (!found && wordCount < MAX_WORDS) {
            copyString(words[wordCount], cleanWord);
            frequencies[wordCount] = 1;
            wordCount++;
        }
    }

    fclose(file);
}


void printWordFrequency(char words[MAX_WORDS][MAX_WORD_LENGTH], int frequencies[MAX_WORDS], int wordCount) {
    for (int i = 0; i < wordCount; ++i) {
        cout << words[i] << ": " << frequencies[i] << endl;
    }
}


void findMostFrequentWord(char words[MAX_WORDS][MAX_WORD_LENGTH], int frequencies[MAX_WORDS], int wordCount, char* mostFrequentWord, int& maxFrequency) {
    maxFrequency = 0;
    mostFrequentWord[0] = '\0';

    for (int i = 0; i < wordCount; ++i) {
        if (frequencies[i] > maxFrequency) {
            maxFrequency = frequencies[i];
            copyString(mostFrequentWord, words[i]);
        }
    }
}


void writeWordFrequencyToFile(const char* outputFileName, char words[MAX_WORDS][MAX_WORD_LENGTH], int frequencies[MAX_WORDS], int wordCount) {
    FILE* file = fopen(outputFileName, "w");
    if (!file) {
        cerr << "Ошибка: Не удалось открыть файл " << outputFileName << endl;
        return;
    }

    for (int i = 0; i < wordCount; ++i) {
        fprintf(file, "%s: %d\n", words[i], frequencies[i]);
    }

    fclose(file);
}

int main() {
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";

    char words[MAX_WORDS][MAX_WORD_LENGTH] = {};
    int frequencies[MAX_WORDS] = {};
    int wordCount = 0;

    
    buildWordFrequency(inputFileName, words, frequencies, wordCount);

    
    cout << "Частотный словарь слов:" << endl;
    printWordFrequency(words, frequencies, wordCount);

    
    char mostFrequentWord[MAX_WORD_LENGTH];
    int maxFrequency;
    findMostFrequentWord(words, frequencies, wordCount, mostFrequentWord, maxFrequency);
    if (stringLength(mostFrequentWord) > 0) {
        cout << "Наиболее часто встречающееся слово: " << mostFrequentWord
             << " (встречается " << maxFrequency << " раз)" << endl;
    }

    
    writeWordFrequencyToFile(outputFileName, words, frequencies, wordCount);

    cout << "Результаты записаны в файл: " << outputFileName << endl;

    return 0;
}

