#include <bits/stdc++.h>
using namespace std;

// define number of ALPHABETS
// size is considered 26 because our input only contains lowercase words
#define ALPHABETS 26

// define node
class trie_node
{
    public:
        trie_node *childrens[ALPHABETS];
        bool is_valid_word;
        trie_node()//test
        {
            // point all childrens to null
            for (int i = 0; i < ALPHABETS; ++i)
            {
                childrens[i] = NULL;
            }
            // false means any word don't end at this node
            is_valid_word = false;
        }
};

// define trie
class trie
{
    private:
        trie_node *root;
    
        inline int char_to_int(char ch){
            return ch-'a';
        }
    public:
        trie(){
            root = new trie_node();
        }

        void insert_str(string &str){
            // head is temp variable that points to root of trie 
            trie_node *head = root;
            for(auto i : str){
                int index = char_to_int(i);
                if(head->childrens[index] == NULL){
                    head->childrens[index] = new trie_node();
                }
                head = head->childrens[index];
            }
            head->is_valid_word = true;
        }

        void delete_str(string &str){
            trie_node *head = root;
            for(auto i : str){
                int index = char_to_int(i);
                if(head->childrens[index] == NULL){
                    return;
                }
                head = head->childrens[index];
            }
            head->is_valid_word = false;
        }

        bool search_str(string &str){
            trie_node *head = root;
            for(auto i : str){
                int index = char_to_int(i);
                if(head->childrens[index] == NULL){
                    return false;
                }
                head = head->childrens[index];
            }
            return head->is_valid_word;
        }
};

void read_file(vector<string> &input_list, clock_t &start_time){
    int choice;
    string file_name;
    
    // select input file
    cout<<"Input file should be present in current working directory \n";
    cout<<"Press 1 to select 'Input_01.txt' and press 2 to select 'Input_02.txt' : ";
    cin>>choice;
    switch (choice){
        case 1 : file_name = "input_01.txt";
                break;
        case 2 : file_name = "input_02.txt";
                break;
        default: cout<<"Invalid choice";
                return;
    }

    // as execution starts here so store time 
    start_time = clock();

    // read file and push words in vector
    ifstream Input_file(file_name);
    // Use a while loop together with the getline() function to read the file line by line
    string line;
    while(getline(Input_file, line)) {
        input_list.push_back(line);
    }
    // Close the file
    Input_file.close();
}

bool comparator(string &a, string &b)
{
    return a.length()>b.length();
}

bool check_compound(trie my_trie, string str){
    // base conditional
    if(str.length() == 0) return true;

    string prefix = "";
    for (int i = 0; i < str.length(); i++) {
        prefix.push_back(str[i]);
        if(my_trie.search_str(prefix) && check_compound(my_trie, str.substr(i+1, str.length()-1))){
            return true;
        }
    }

    return false;
}

int main()
{
    // vector to store input strings 
    vector<string> input_list;
    // variables to store time 
    clock_t start_time, end_time;

    // call function to read words from input file and insert them in vector
    read_file(input_list, start_time);

    if(input_list.size() == 0){
        // if size is 0 then it means file is empty 
        return 0;
    }

    // sort vector on basis of string length as we need to find largest and second largest compound word 
    sort(input_list.begin(), input_list.end(), comparator);

    // print vector for testing 
    // for(auto i:input_list){
    //     cout<<i <<" => "<<i.length()<<endl;
    // } 

    // create trie for given input 
    trie my_trie;
    for(auto &i : input_list){
        my_trie.insert_str(i);
    }

    // create variables to store largest and second largest compound word 
    string largest = ""; 
    string second_largest = ""; 
    int i = 0;  // i points to elements of input list
    // we use i to point elements as we need to skip elements which are processed during finding largest element while finding second largest

    // find largest compound word 
    for( ; i<input_list.size(); ++i){
        // remove current element from trie
        my_trie.delete_str(input_list[i]);
        // check if it is compound
        if(check_compound(my_trie, input_list[i])){
            // add current element to trie 
            my_trie.insert_str( input_list[i] );
            // update largest element 
            largest = input_list[i];
            // as current element is largest so it can not be second largest so increase i by 1
            ++i;
            break;
        }
        // add current element to trie as we earlier removed it 
        my_trie.insert_str(input_list[i]);
    }
    // find second largest compound word 
    for( ; i<input_list.size(); ++i){
        // if length of current word is same as length of largest compound word, then this can not be second largest compound word
        if(input_list[i].length() >= largest.length()){
            continue;
        }
        // remove current element from trie
        my_trie.delete_str(input_list[i]);
        // check if it is a compound word
        if(check_compound(my_trie, input_list[i])){
            // add current element to trie 
            my_trie.insert_str( input_list[i] );
            // update largest element 
            second_largest = input_list[i];
            break;
        }
        // add current element to trie as we earlier removed it 
        my_trie.insert_str(input_list[i]);
    }
    // store end time  
    end_time = clock();
    clock_t time_taken = end_time-start_time;
    // show output 
    cout<<endl;
    cout<<"Longest Compound Word : "<<largest<<endl;
    cout<<"Second Largest Compound Word : "<<second_largest<<endl;
    cout<<"Time taken to process input file : "<<time_taken<<" milli seconds"<<endl;
    cout<<endl;
    
    return 0;
}