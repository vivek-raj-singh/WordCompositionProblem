#include <bits/stdc++.h>
using namespace std;
//defining the numbers of alphabets i.e. a6 because our input only conatsins lowercase letters
#define ALPHABETS 26
//defining trie nodes
class TrieNode
{
public:
    TrieNode *childrens[ALPHABETS];
    bool isValidWord;

    TrieNode()
    {   //pointing all childrens to null
        for (int i = 0; i < ALPHABETS; ++i)
        {
            childrens[i] = NULL;
        }

        
        isValidWord = false;//any word that is not ending at this node
    }
};


//difining trie
class Trie
{
private:
    TrieNode *root;

    inline int charToInt(char ch)
    {
        return ch - 'a';
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insertStr(string &str)
    {
        //head is pointing to the rood of trie
        TrieNode *head = root;
        for (auto i : str)
        {
            int index = charToInt(i);
            if (head->childrens[index] == NULL)
            {
                head->childrens[index] = new TrieNode();
            }
            head = head->childrens[index];
        }
        head->isValidWord = true;
    }

    void deleteStr(string &str)
    {
        TrieNode *head = root;
        for (auto i : str)
        {
            int index = charToInt(i);
            // Check if the current character has a corresponding child node
            if (head->childrens[index] == NULL)
            {
                // If not, the word is not present in the trie, so return 
                return;
            }
            head = head->childrens[index];
        }
        // Mark the last node (corresponding to the last character of the input string) as not the end of a valid word
        head->isValidWord = false;
    }

    bool searchStr(string &str)
    {
        TrieNode *head = root;
        for (auto i : str)
        {
            int index = charToInt(i);
            // Check if the current character has a corresponding child node
            if (head->childrens[index] == NULL)
            {
                // If not, the word is not present in the trie, so return false
                return false;
            }
            head = head->childrens[index];
        }
        // The loop has traversed the entire word in the trie, so check if the last node represents the end of a valid word
        return head->isValidWord;
    }
};

void readFile(vector<string> &inputList, clock_t &startTime)
{
    int choice;
    string fileName;
    //select input fille
    cout << "Input file should be present in the current working directory\n";
    cout << "Press 1 to select 'Input_01.txt' and press 2 to select 'Input_02.txt': ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        fileName = "input_01.txt";
        break;
    case 2:
        fileName = "input_02.txt";
        break;
    default:
        cout << "Invalid choice";
        return;
    }
    //storing the starting time of execution
    startTime = clock();
    //reading file
    ifstream inputFile(fileName);
    string line;
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(inputFile, line))
    {
        inputList.push_back(line);
    }
    //closing the file
    inputFile.close();
}

bool compareLength(string &a, string &b)
{   
    return a.length() > b.length();
}

bool checkCompoundRecursive(Trie &myTrie, string str, bool originalWord)
{
    // Base condition
    if (str.length() == 0)
        return true;

    string prefix = "";
    for (int i = 0; i < str.length(); i++)
    {
        prefix.push_back(str[i]);
        // Checking if the current prefix is present in the trie
        if (myTrie.searchStr(prefix))
        {
            // If the current prefix is found, recursively check the remaining part of the string
            if (checkCompoundRecursive(myTrie, str.substr(i + 1, str.length() - 1), false))
            {
                // If the remaining part is also a compound word, return true
                return true;
            }
        }
    }

    // If no compound word is found, return false
    return false && !originalWord;
}

int main()
{
    //storing input string
    vector<string> inputList;

    //storing time
    clock_t startTime, endTime;
    // calling function to read words from input file and inserting them in vector
    readFile(inputList, startTime);

    if (inputList.size() == 0)
    {
        // if size is 0 then it means file is empty
        return 0;
    }
    // sorting vector on basis of string length as we need to find largest and second largest compound word

    sort(inputList.begin(), inputList.end(), compareLength);
    // creating Trie for given input
    Trie myTrie;
    for (auto &i : inputList)
    {
        myTrie.insertStr(i);
    }
    // creating variables to store largest and second largest compound word
    string largest = "";
    string secondLargest = "";
    int i = 0; // we use i to point elements as we need to skip elements which are processed during finding largest element while finding second largest

    for (; i < inputList.size(); ++i)
    {
        // removing current element from trie
        myTrie.deleteStr(inputList[i]);
        // check if it is compound
        if (checkCompoundRecursive(myTrie, inputList[i], true))
        {
            // adding current element to trie
            myTrie.insertStr(inputList[i]);
            // updating largest element
            largest = inputList[i]; // as current element is largest so it can not be second largest so increasing i by 1
            ++i;
            break;
        }
        // // adding current element to trie as we earlier removed it
        myTrie.insertStr(inputList[i]);
    }
    // finding second largest compound word
    for (; i < inputList.size(); ++i)
    {
        // if length of current word is same as length of largest compound word, then this can not be second largest compound word
        if (inputList[i].length() >= largest.length())
        {
            continue;
        }
        // remove current element from trie
        myTrie.deleteStr(inputList[i]);
        // checking if it is a compound word
        if (checkCompoundRecursive(myTrie, inputList[i], true))
        {
            // adding current element to trie
            myTrie.insertStr(inputList[i]);
            // updating largest element
            secondLargest = inputList[i];
            break;
        }
        // adding current element to trie as we earlier removed it
        myTrie.insertStr(inputList[i]);
    }
    // storing end time
    endTime = clock();
    clock_t timeTaken = endTime - startTime;

    //OUTPUT

    cout << endl;
    cout << "Longest Compound Word: " << largest << endl;
    cout << "Second Largest Compound Word: " << secondLargest << endl;
    cout << "Time taken to process input file: " << timeTaken << " milliseconds" << endl;
    cout << endl;

    return 0;
}
