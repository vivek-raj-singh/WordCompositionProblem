#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

#define ALPHABETS 26

class TrieNode
{
public:
    TrieNode *children[ALPHABETS];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false)
    {
        fill(children, children + ALPHABETS, nullptr);
    }
};

class Trie
{
private:
    TrieNode *root;

    int charToInt(char ch) const
    {
        return ch - 'a';
    }

public:
    Trie() : root(new TrieNode()) {}

    void insert(const string &word)
    {
        TrieNode *current = root;
        for (char ch : word)
        {
            int index = charToInt(ch);
            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    void remove(const string &word)
    {
        TrieNode *current = root;
        for (char ch : word)
        {
            int index = charToInt(ch);
            if (current->children[index] == nullptr)
            {
                return;
            }
            current = current->children[index];
        }
        current->isEndOfWord = false;
    }

    bool search(const string &word) const
    {
        TrieNode *current = root;
        for (char ch : word)
        {
            int index = charToInt(ch);
            if (current->children[index] == nullptr)
            {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    bool isCompoundWord(const string &word) const
    {
        if (word.empty())
        {
            return true;
        }

        TrieNode *current = root;
        for (char ch : word)
        {
            int index = charToInt(ch);
            if (current->children[index] == nullptr)
            {
                return false;
            }
            current = current->children[index];
            if (current->isEndOfWord)
            {
                if (isCompoundWord(word.substr(ch + 1)))
                {
                    return true;
                }
            }
        }

        return false;
    }
};

void readInputFile(vector<string> &words, clock_t &start_time)
{
    int choice;
    string file_name;

    cout << "Input file should be present in the current working directory.\n";
    cout << "Press 1 to select 'Input_01.txt' and press 2 to select 'Input_02.txt' : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        file_name = "input_01.txt";
        break;
    case 2:
        file_name = "input_02.txt";
        break;
    default:
        cout << "Invalid choice";
        return;
    }

    start_time = clock();

    ifstream inputFile(file_name);
    string line;
    while (getline(inputFile, line))
    {
        words.push_back(line);
    }
    inputFile.close();
}

bool compareLength(const string &a, const string &b)
{
    return a.length() > b.length();
}

void findLargestAndSecondLargestCompoundWords(const vector<string> &words, Trie &trie, string &largest, string &second_largest)
{
    for (const string &word : words)
    {
        trie.remove(word);

        if (trie.isCompoundWord(word))
        {
            if (word.length() > largest.length())
            {
                second_largest = largest;
                largest = word;
            }
            else if (word.length() > second_largest.length() && word != largest)
            {
                second_largest = word;
            }
        }

        trie.insert(word);
    }
}

int main()
{
    vector<string> words;
    clock_t start_time, end_time;

    readInputFile(words, start_time);

    if (words.empty())
    {
        cout << "File is empty.\n";
        return 0;
    }

    sort(words.begin(), words.end(), compareLength);

    Trie trie;
    string largest = "";
    string second_largest = "";

    findLargestAndSecondLargestCompoundWords(words, trie, largest, second_largest);

    end_time = clock();
    clock_t time_taken = end_time - start_time;

    cout << "\nLongest Compound Word: " << largest << endl;
    cout << "Second Largest Compound Word: " << second_largest << endl;
    cout << "Time taken to process input file: " << time_taken << " milliseconds\n\n";

    return 0;
}
