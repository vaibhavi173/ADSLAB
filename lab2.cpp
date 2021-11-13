#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Node{
    public:
    int key;
    Node **forward;
    Node(int key,int level)
    {
        this->key = key;
        forward = new Node*[level+1];
        
  
        memset(forward, 0, sizeof(Node*)*(level+1));
       
    }
};

class SkipList
{
    
    int max;
    float P;
    int level;
  
    
    Node *header;
public:
    SkipList(int max, float P)
    {
      this->max = max;
      this->P = P;
      level = 0;
      header = new Node(-1,max);
        
    }
    int randomLevel()
    {
     float r = (float)rand()/RAND_MAX;
     int lvl = 0;
     while (r < P && lvl < max)
     {
        lvl++;
        r = (float)rand()/RAND_MAX;
     }
     return lvl;
     }
    Node* createNode( int key, int level)
    {
        Node* n = new Node(key,level);
        return n;
    }
    void insertElement(int key)
    {
        Node* current = header;
        Node* update[max+1];
        memset(update, 0, sizeof(Node*)*(max+1));
        for(int i=0;i<max+1;i++)
        cout<<update[i]<<endl;
        cout<<"new insertion"<<endl;
        
    for(int i = level; i >= 0; i--)
    {
       
        while (current->forward[i] != NULL &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
        cout<<update[i]<<endl;
    }
      current = current->forward[0];
      
    if (current == NULL || current->key != key)
    {

        int rlevel = randomLevel();
  
        
        if (rlevel > level)
        {
            for (int i=level+1;i<rlevel+1;i++)
                update[i] = header;
  
            
            level = rlevel;
        }
  
        
        Node* n = createNode(key, rlevel);
  
       
        for (int i=0;i<=rlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;

        }
        cout << " succesfully inserted"<<n->key;
        cout<<endl;
     }
    }

    void displayList()
    {
       for (int i=0;i<=level;i++)
     {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key<<" ";
            node = node->forward[i];

        }
        cout<<endl;
        
     }

    }
};

int main()
{
    // Seed random number generator
    srand((unsigned)time(0));
  
    // create SkipList object with MAXLVL and P 
    SkipList lst(2, 0.5);
  
    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
  
    lst.displayList();
}  
