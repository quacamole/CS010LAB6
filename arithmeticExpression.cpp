#include "arithmeticExpression.h"
#include<iostream>
#include <fstream>
#include<sstream>
using namespace std;

//added constructor -Kera
arithmeticExpression::arithmeticExpression(const string& _infix)
{
    infixExpression = _infix;
    root = nullptr;
}

//optional destructor maybe later
//arithmeticExpression::~arithmeticExpression()
//{ //maybe later}

void arithmeticExpression::buildTree()
{

}

void arithmeticExpression::infix() {
    if (root != nullptr)
    {
        infix(root);
    }
}
void arithmeticExpression::prefix() {
    if (root != nullptr)
    {
        prefix(root);
    }
}
void arithmeticExpression::postfix() {
    if (root != nullptr)
    {
        postfix(root);
    }
}

int arithmeticExpression::priority(char op) {
    int priority = 0;
    if (op == '(') {
        priority = 3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for (unsigned i = 0; i < infixExpression.size(); ++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if (c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while (s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else {
                while (!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else { //c is an operand
            oss << c;
        }
    }
    while (!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

//helper function versions of in, pre and postfix (performs preorder traversal) [Left, Root, Right]
void arithmeticExpression::infix(TreeNode* _root) {
    //Prints Left
    if (_root->left != nullptr)
    {
        cout << "(";
        infix(_root->left);
    }
    else
    {
        cout << _root->data;
        return;
    }

    //Prints Root
    cout << _root->data;

    //Prints Right
    if (_root->right != nullptr)
    {
        infix(_root->right);
        cout << ")";
    }

    return;
}
//[Root, Left, Right]
void arithmeticExpression::prefix(TreeNode* _root) {
    //Prints Root
    cout << _root->data;

    //Moves Left
    if (_root->left != nullptr)
    {
        infix(_root->left);
    }

    //Moves Right
    if (_root->right != nullptr)
    {
        infix(_root->right);
    }

    return;
}
//[Left, Right, Root]
void arithmeticExpression::postfix(TreeNode* _root) {
    //Moves Left
    if (_root->left != nullptr)
    {
        infix(_root->left);
    }

    //Moves Right
    if (_root->right != nullptr)
    {
        infix(_root->right);
    }

    //Prints Root
    cout << _root->data;

    return;
}

void arithmeticExpression::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error opening " << outputFilename << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

//helper for visualizeTree(string); recursive [preorder looks best]; examples below

/*
digraph G1 {
  // nodes and edges    
key12->key8;
key12->key16;
key8->key1;
key8->key11;
key16->key13;
key16->key25;
}
*/
//expected from first test
/*
digraph G {
"+" -> "a";
"+" -> "*";
"*" -> "b";
"*" -> "c";
}
*/

void arithmeticExpression::visualizeTree(ofstream& outFS, TreeNode* _root){
    //Prints Root
    outFS << "\"" << _root->data << "\";" << endl;
    if (_root->left != nullptr)
    {
        outFS << "\"" << _root->data << "\" -> \"" << _root->left->data << "\";" << endl;
    }
    if (_root->right != nullptr)
    {
        outFS << "\"" << _root->data << "\" -> \"" << _root->right->data << "\";" << endl;
    }

    //Prints Left
    if (_root->left != nullptr)
    {
        visualizeTree(outFS, _root->left);
    }

    //Prints Right
    if (_root->right != nullptr)
    {
        visualizeTree(outFS, _root->right);
    }

    return;
}
