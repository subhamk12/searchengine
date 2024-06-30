// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict
{
private:
    // You can add attributes/helper functions here
    class Node
    {
    public:
        Node();
        Node(string text);
        std::string word;
        int count;
        Node *left = nullptr;
        Node *right = nullptr;
        int heightNode;
        int height(Node *node);
        int balanceFactor(Node *node);
        Node *rightRotate(Node *y);
        Node *leftRotate(Node *x);
        Node *balance(Node *node);
        Node *insert(Node *node, std::string word);
        int getWordCount(Node *node, std::string word);
        void dumpToFile(Node *node, std::ofstream &outputFile);
        void deleteTree(Node *node);
    };

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
    Node *root;
    int size;
};