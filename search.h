// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine
{
private:
    // You can add attributes/helper functions here
    struct SentenceNode
    {
        int book_code;
        int page;
        int paragraph;
        int sentence_no;
        std::string sentence;

        // Constructor
        SentenceNode(int code, int p, int para, int s_no, const std::string &s)
            : book_code(code), page(p), paragraph(para), sentence_no(s_no), sentence(s) {}
    };
    std::vector<SentenceNode> sentenceNodes;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
    int searchCount;
    int foundCount;
};