// Do NOT add any other includes
#include "search.h"

void processText(std::string &input)
{
    std::string lowercaseWord;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = tolower(input[i]);
        }
    }
    return;
}

SearchEngine::SearchEngine()
{
    // Implement your function here
    searchCount = 0;
    foundCount = 0;
    sentenceNodes = {};
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
    // for(int i=0;i<sentenceNodes.size();i++){
    //     sentenceNodes[i];
    // }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    processText(sentence);
    SentenceNode newNode(book_code, page, paragraph, sentence_no, sentence);
    sentenceNodes.push_back(newNode);
    return;
}

std::vector<int> computeLPSArray(const std::string &pattern)
{
    int patternLength = pattern.length();
    std::vector<int> lps(patternLength, 0);
    int len = 0;
    int i = 1;

    while (i < patternLength)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMPSearch(const std::string &text, const std::string &pattern)
{
    vector<int> offsetlist;
    int textLength = text.length();
    int patternLength = pattern.length();
    std::vector<int> lps = computeLPSArray(pattern);
    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]
    bool found = false;
    while (i < textLength)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == patternLength)
        {
            // Pattern found in the text starting at index i - j
            offsetlist.push_back(i - j);
            if (!found)
            {
                found = true;
            }
            // j = 0;
            // i++;
        }
        if (i < textLength && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    // Pattern not found in the text
    if (!found)
    {
        offsetlist.push_back(-1);
    }
    return offsetlist;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    vector<int> offsetlist;
    int val;
    Node *head = nullptr;
    Node *current;
    processText(pattern);
    for (int i = 0; i < sentenceNodes.size(); i++)
    {
        offsetlist = KMPSearch(sentenceNodes[i].sentence, pattern);
        if (offsetlist[0] != -1)
        {
            int number = offsetlist.size();
            for (int off = 0; off < number; off++)
            {
                Node *newFound = new Node(sentenceNodes[i].book_code, sentenceNodes[i].page, sentenceNodes[i].paragraph, sentenceNodes[i].sentence_no, offsetlist[off]);
                if (foundCount == 0)
                {
                    head = newFound;
                    current = newFound;
                }
                else
                {
                    current->right = newFound;
                    newFound->left = current;
                    current = newFound;
                }
                SearchEngine::foundCount += 1;
            }
        }
        searchCount += 1;
    }
    n_matches = foundCount;
    return head;
}

// int main()
// {
//     // std::string text = "naa";
//     // std::string pattern = "na";
//     // vector<int> v = KMPSearch(text, pattern);
//     // if (v[0] != -1)
//     // {
//     //     std::cout<<v.size()<<std::endl;
//     //     std::cout << v[0] << std::endl;
//     //     std::cout << v[1] << std::endl;
//     //     std::cout << v[2] << std::endl;
//     //     std::cout << v[3] << std::endl;
//     //     std::cout << v[4] << std::endl;
//     // }
//     // else
//     // {
//     //     std::cout << "Pattern not found in the text." << std::endl;
//     // }

//     // return 0;
//     SearchEngine se;
//     se.insert_sentence(1, 1, 1, 1, "Big buddy did me wrona=][3r1r-0]2';Dg but what.");
//     se.insert_sentence(1, 1, 1, 2, "didasfknafwlqnv'p -0]2';Dg bufwefw031-02[ml't whdiddsdw");
//     int nmat = 0;
//     Node *npt = se.search("did", nmat);
//     while (npt)
//     {
//         std::cout << npt->sentence_no << " - " << npt->offset << std::endl;
//         npt = npt->right;
//     }
// }
