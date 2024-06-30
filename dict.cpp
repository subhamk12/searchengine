#include "dict.h"

Dict::Node::Node()
{
    heightNode = 0;
    count = 0;
}
Dict::Node::Node(string text)
{
    word = text;
    heightNode = 0;
    count = 1;
}

int Dict::Node::height(Node *node)
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->heightNode;
}

int Dict::Node::balanceFactor(Node *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
Dict::Node *Dict::Node::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T = x->right;
    x->right = y;
    y->left = T;
    x->heightNode = 1 + std::max(height(x->left), height(x->right));
    y->heightNode = 1 + std::max(height(y->left), height(y->right));
    return x;
}
Dict::Node *Dict::Node::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T = y->left;
    y->left = x;
    x->right = T;
    x->heightNode = 1 + std::max(height(x->left), height(x->right));
    y->heightNode = 1 + std::max(height(y->left), height(y->right));
    return y;
}
Dict::Node *Dict::Node::balance(Node *node)
{
    int bf = balanceFactor(node);
    if (bf > 1)
    {
        if (balanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (bf < -1)
    {
        if (balanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Dict::Node *Dict::Node::insert(Node *node, std::string word)
{
    if (node == nullptr)
    {
        Node *newNode = new Node(word);
        return newNode;
    }

    if (word < node->word)
    {
        node->left = insert(node->left, word);
    }
    else if (word > node->word)
    {
        node->right = insert(node->right, word);
    }
    else
    {
        node->count++;
        return node;
    }

    node->heightNode = 1 + std::max(height(node->left), height(node->right));
    return balance(node);
}

int Dict::Node::getWordCount(Node *node, std::string word)
{
    if (node == nullptr)
        return 0;

    if (word < node->word)
    {
        return getWordCount(node->left, word);
    }
    else if (word > node->word)
    {
        return getWordCount(node->right, word);
    }
    else
    {
        return node->count;
    }
}
void Dict::Node::dumpToFile(Node *node, std::ofstream &outputFile)
{
    if (node == nullptr)
        return;

    dumpToFile(node->left, outputFile);
    outputFile << node->word << ", " << node->count << std::endl;
    dumpToFile(node->right, outputFile);
}
void Dict::Node::deleteTree(Node *node)
{
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

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

Dict::Dict()
{
    root = nullptr;
    size = 0;
}

Dict::~Dict()
{
    root->Dict::Node::deleteTree(root);
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, std::string sentence)
{
    std::string word = "";
    std::string seperators = " .,-:!\'\"()?[];@";
    //{'.', ' ', ',', '-', ':', '!', '\"', '\'', '(', ')', '?', ';', '@', '[', ']'};

    bool match;
    for (int i = 0; i < sentence.size(); i++)
    {
        match = false;
        for (int x = 0; x < seperators.size(); x++)
        {
            if (sentence[i] == seperators[x])
            {
                processText(word);
                if (size == 0)
                {
                    if (word != "")
                    {
                        root = new Node(word);
                        size += 1;
                    }
                }
                else
                {
                    if (word != "")
                    {
                        root = root->Node::insert(root, word);
                        size += 1;
                    }
                }
                word = "";
                match = true;
                break;
            }
        }
        if (match)
        {
            continue;
        }
        else
        {
            word += sentence[i];
        }
    }
    if (word != "")
    {
        processText(word);
        if (size == 0)
        {
            root = new Node(word);
            size += 1;
        }
        else
        {
            root = root->Node::insert(root, word);
            size += 1;
        }
    }
    return;
}
int Dict::get_word_count(std::string word)
{
    processText(word);
    return root->Node::getWordCount(root, word);
}

void Dict::dump_dictionary(std::string filename)
{
    std::ofstream outputFile(filename);
    root->Node::dumpToFile(root, outputFile);
    outputFile.close();
}

// int main()
// {
//     Dict d;

//     d.insert_sentence(0, 0, 0, 0, "AND");

//     cout << d.get_word_count("and");
// }