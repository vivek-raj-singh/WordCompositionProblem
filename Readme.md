# ***Word composition Problem (C++)***

## *Introduction*

This C++ program is developed to identify the longest and second longest compound words from an alphabetically sorted list of words in an input file. A compound word is defined as a word that can be formed by concatenating shorter words found within the same input file.

The program achieves this by employing a trie data structure for efficient storage and retrieval of words. Additionally, it utilizes a recursive approach to ascertain whether a given word is compounded. The program also includes functionality to measure the time taken for processing the input files.

## *Requirements*
- A C++ compiler (e.g., g++)
- Input text files (Input_01.txt and Input_02.txt) containing alphabetically sorted words, with one word per line. The input files should be present in the current working directory.

## *Steps to Execute the code*
1. Clone or download the source code from the provided GitHub URL.
2. Compile the C++ program using your C++ compiler:
    ```bash
    g++ solution.cpp -o solution
    ```
3. Run the program with the following command:
    ```bash
    ./solution
    ```
4. The program will require you to choose either 'Input_01.txt' or 'Input_02.txt' for processing. Please adhere to the on-screen instructions to make your selection.

5. Following the execution, the program will showcase the longest compounded word, the second longest compounded word, and the duration taken to process the input file.

## *Used Methodlogy*
1. Read and Arrange:
    - Extract words from the input file, store them in a vector, and arrange the vector based on word length.
2. Trie for Optimization:
    - Develop a trie for efficient organization and searching of words.

3. Identify Longest Compound Word:
   - Initiate from the end of the sorted list and iterate through words.
   - For each word:
        * Remove it from the trie.
        * Verify if it constitutes a compounded word.
        * Reinsert it into the trie.
        * Record it as the longest compounded word and exit the loop if it's a compounded word.
4. Find Second Longest Compound Word:
    - Continue the iteration to identify the second longest compounded word.
    - The word should be shorter than the length of the longest compound word but longer than other words.
5. Record Time:
    - Log the execution time for performance evaluation.
6. Showcase Results:
    - Present the outcomes, encompassing details such as the longest and second longest compounded words, and the time taken for processing the input files.