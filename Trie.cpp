#include<bits/stdc++.h>
using namespace std;

class TrieNode{
    public:
    TrieNode*child[2];
    bool isterminal=false;
    bool containletter(char ch){
        return(this->child[ch-'0']!=NULL);
    }
    void insertletter(char ch){
        this->child[ch-'0']=new TrieNode();
    }
    TrieNode*get(char ch){
        return(this->child[ch-'0']);
    }
    void setend()
    {
        this->isterminal=true;
    }
    bool isend(){
        return(this->isterminal);
    }  
};

class Trie {
private:
TrieNode *root;
public:

    /** Initialize your data structure here. */
    Trie() {
        root=new TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode*node=root;
        for(int i=0;i<word.size();i++)
        {
            if(!node->containletter(word[i])){
                node->insertletter(word[i]);
            }
            node=node->get(word[i]);
        }
        node->setend();
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode*node=root;
        for(int i=0;i<word.size();i++)
        {
            if(!node->containletter(word[i]))return false;
            node=node->get(word[i]);
        }
        return(node->isend());

    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        TrieNode*node=root;
        if(!node->containletter(word[0]))return false;
        for(int i=1;i<word.size();i++)
        {
            if(!node->containletter(word[i]))return true;
            node=node->get(word[i]);
        }
        return true;
    }
};

int main()
{
    int  n; cin>>n;
    Trie T;
    for(int i=0;i<n;i++)
    {
        string s; cin>>s;
        if(T.startsWith(s))cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        T.insert(s);
    }
}