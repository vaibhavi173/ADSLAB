#include<iostream>
#include<bits/stdc++.h>

using namespace std;

struct Node
{
  int key;
  Node **forward;
  Node(int key,int lvl)
  {
    this->key = key;
    forward = new Node*[lvl+1];
    memset(forward,0,sizeof(Node*)*(lvl+1));

  }
};

class skiplist
{
  int maxlvl;
  float p;
  int level;
  Node *header;

  public:
    skiplist(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    void deleteElement(int);
    void searchElement(int);
    void displayList();
};

skiplist::skiplist(int maxlvl,float p)
{
  this->maxlvl = maxlvl;
  this->p = p;
  level=0;
  header = new Node(-1,maxlvl);
}

int skiplist::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while(r < p && lvl < maxlvl)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};

Node* skiplist::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
}

void skiplist::insertElement(int key)
{
  Node* current = header;
        Node* update[maxlvl+1];
        memset(update, 0, sizeof(Node*)*(maxlvl+1));
      
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

void skiplist::deleteElement(int key)
{
  Node *current = header;
  Node *update[maxlvl+1];
  memset(update, 0, sizeof(Node*)*(maxlvl+1));
  
  
  for(int i=level; i>=0; i--)
  {
    while(current->forward[i] != NULL  && current->forward[i]->key < key)
     current = current->forward[i];
     update[i] = current;
  }
  
  current = current->forward[0];
  
  if(current != NULL and current->key == key)
  {
    for(int i=0;i<=level;i++)
    {
      if(update[i]->forward[i] != current)
      break;
      
      update[i]->forward[i] = current->forward[i];
      }
  
    while(level>0 &&header->forward[level] == 0)
    level--;
    cout<<"Successfully deleted key element "<<key<<"\n";
  }
  cout<<"Element not in the skiplist "<<key<<"\n";
};
  

void skiplist::searchElement(int key)
{
    Node *current = header;
    
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
  
    }
    current = current->forward[0];
  
    if(current and current->key == key) 
        cout<<"Found Element: "<<key<<"\n";
};
  

void skiplist::displayList()
{
    cout<<"\n*****Skip List*****"<<"\n";
    for(int i=0;i<=level;i++)
    {
        Node *node = header->forward[i];
        cout<<"Level "<<i<<": ";
        while(node != NULL)
        {
            cout<<node->key<<" ";
            node = node->forward[i];
        }
        cout<<"\n";
    }
};
/*
int main()
{
    // Seed random number generator
    srand((unsigned)time(0));
  
    // create SkipList object with MAXLVL and P 
    skiplist lst(2, 0.5);
  
    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
    lst.insertElement(9);
    lst.displayList();
}
*/

//DRIVER CODE
int main()
{ 
  srand((unsigned)time(0));
  skiplist lst(3, 0.5);
  int n;
  int k;
  cout<<"1:createlist 2:deletelistelement 3:searchlist 4:displaylist"<<endl;
  cout<<"Enter your choice : ";
  cin>>n;
  switch(n)
  {
    case 1:cout<<"Enter the key : ";
           cin>>k;
           lst.insertElement(k);
           break;
    
    case 2:cout<<"Enter the key : ";
           cin>>k;
           lst.deleteElement(k);
           break;
    
    case 3:cout<<"Enter the key : ";
           cin>>k;
           lst.searchElement(k);
           break;
    
    case 4: lst.displayList();

  }
 
}
