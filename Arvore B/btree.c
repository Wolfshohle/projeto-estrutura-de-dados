#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3

typedef struct btree BTREE;

struct btree
{
  int number_keys;
  int is_leaf;
  int amount_pontier;
  int keys[T];
  BTREE *childs[T+1];
};

//cria um novo no da arvore b
BTREE* create_btree_node()
{
  BTREE *new_btree = (BTREE*)malloc(sizeof(BTREE));
  new_btree->number_keys = 0;
  new_btree->amount_pontier = 0;
  new_btree->is_leaf = 1;
  for(int i = 0; i < T; i++)
  {
    new_btree->childs[i] = NULL;
  }

  return new_btree;
}

//faz a quebra da pagina da arvore B
BTREE* split_node(BTREE *parent, int pos)
{
  BTREE *right_node = create_btree_node();
  BTREE *left_node = parent->childs[pos];
  parent->amount_pontier++;
  int i, j;
  right_node->is_leaf = left_node->is_leaf;

  if(T % 2 == 0)
  {
    j = (T/2);
  }
  else
  {
    j = (T/2) + 1;
  }
  
  for (i = 0, j; i < T-1 && j < T; i++, j++) 
  {
      right_node->keys[i] = left_node->keys[j];
      right_node->number_keys++;
  }

  
  if (!left_node->is_leaf) 
  {
    if(T % 2 == 0)
    {
      j = (T/2);
    }
    else
    {
      j = (T/2) + 1;
    }
    for (i = 0, j; i < T-1 && j < T+1; i++, j++) 
    {
        right_node->childs[i] = left_node->childs[j];
    }
  }

  // Atualiza o número de chaves em left_node
  if(T % 2 == 0)
  {
    left_node->number_keys = (T / 2) - 1;
  }
  else
  {
    left_node->number_keys = (T / 2);
  }

  if(pos + 1 < T && parent->childs[pos + 1] != NULL)
  {
    for (i = T-1; i >= pos + 1; i--) 
    {
      parent->childs[i] = parent->childs[i-1];
    }

    parent->childs[pos+1] = right_node;

    for (i = T-1; i >= pos + 1; i--) 
    {
      parent->keys[i] = parent->keys[i-1];
        
    }
    if(T % 2 == 0)
    {
      j = (T/2) - 1;
    }
    else
    {
      j = (T/2);
    }
    parent->keys[pos] = left_node->keys[j];
    parent->number_keys++;
  }
  else
  {
    if(T % 2 == 0)
    {
      j = (T/2) - 1;
    }
    else
    {
      j = (T/2);
    }
    if(parent->number_keys == 0)
    {
      parent->keys[pos] = left_node->keys[j];
    }
    else
    {
      parent->keys[pos] = left_node->keys[j];
    }
    parent->number_keys++;
    parent->childs[pos+1] = right_node;
  }

  return parent;
}

// Função auxiliar para inserir uma chave em um nó que não está cheio
void tree_insert_non_full(BTREE *node, int key)
{
    int i = node->number_keys - 1;
    BTREE *new_node;
    if (node->is_leaf) 
    {
      //insere a chave em ordem
      while (i >= 0 && node->keys[i] > key) 
      {
          node->keys[i+1] = node->keys[i];
          i--;
      }
      node->keys[i+1] = key;
      node->number_keys++;
    }
    else
    {
      while (i >= 0 && node->keys[i] > key) 
      {
        i--;
      }
      i++;
      if(node->childs[i]->number_keys == T-1)
      {
        tree_insert_non_full(node->childs[i], key);
        if(node->childs[i]->number_keys == T)
        {
          node = split_node(node, i);
        }
        return;
      }
      
      tree_insert_non_full(node->childs[i], key);
    }
}


//insere uma chave na arvore b
BTREE* tree_insert(BTREE *root, int key)
{
  if(root == NULL)
  {
    root = create_btree_node();
    root->keys[0] = key;
    root->number_keys++;
    
    return root;
  }
  else
  {
    if(root->number_keys == T - 1)
    {
      tree_insert_non_full(root, key);
      if(root->number_keys == T)
      {
        BTREE *new_root = create_btree_node();
        new_root->is_leaf = 0;
        new_root->childs[0] = root;
        new_root->amount_pontier = 1;
        root = split_node(new_root, 0);
      }
    }
    else
    {
      tree_insert_non_full(root, key);
    }
  }


  return root;
}

//faz a busca em uma arvore B
int search_key(BTREE *root, int key)
{
  int i = 0;
  while(i < root->number_keys && root->keys[i] < key)
  {
    i++;
  }
  if(root->keys[i] == key)
  {
    return 1;
  }
  else if(root->childs[i] != NULL)
  {
    return search_key(root->childs[i], key);
  }
  else
  {
    return 0;
  }
}

int find_index(BTREE *root, int key)
{
  int idx = 0;
  while (idx < root->number_keys && key > root->keys[idx]) 
  {
      idx++;
  }
  return idx;
}

BTREE* remove_key(BTREE *root, int key)
{
  if(root == NULL)
  {
    return root;
  }

  int index = find_index(root, key);
  printf("%d\n", index);
  if(root->keys[index] == key && index <= root->number_keys - 1)
  {
    if(root->is_leaf)
    {
      for (int i = index; i < root->number_keys - 1; i++) 
      {
        root->keys[i] = root->keys[i + 1];
      }
      root->number_keys--;
      if(root->number_keys < 1)
      {
        free(root->childs[index]);
        root->amount_pontier--;
      }
    }
    else
    {

    }
  }
  else
  {
    if(root->is_leaf)
    {
      return root;
    }
    root->childs[index] = remove_key(root->childs[index], key);
  }
}


//printa a arvore B
void printBTreeTree(BTREE *root, int nivel) {
    if (root != NULL) {
        int i, j;
        for (i = 0; i < root->number_keys; i++) {
            printBTreeTree(root->childs[i], nivel + 1);
            printf("\n");
            for (j = 0; j < nivel; j++) {
                printf("   ");
            }
            printf("%d", root->keys[i]);
        }
        printBTreeTree(root->childs[i], nivel + 1);
    }
}


int main()
{
  BTREE *root = NULL;
  root = tree_insert(root, 4);
  root = tree_insert(root, 1);
  root = tree_insert(root, 7);
  /*root = tree_insert(root, 22);
  root = tree_insert(root, 10);
  root = tree_insert(root, 45);
  root = tree_insert(root, 4);
  root = tree_insert(root, 16);
  root = tree_insert(root, 36);
  root = tree_insert(root, 54);
  root = tree_insert(root, 1);
  root = tree_insert(root, 7);
  root = tree_insert(root, 13);
  root = tree_insert(root, 19);
  root = tree_insert(root, 28);
  root = tree_insert(root, 39);
  root = tree_insert(root, 48);
  root = tree_insert(root, 57);
  root = tree_insert(root, 25);
  root = tree_insert(root, 33);
  root = tree_insert(root, 42);
  root = tree_insert(root, 51);
  root = tree_insert(root, 60);*/
  printBTreeTree(root, 0);
  printf("\n\n");
  root = remove_key(root, 3);
  printBTreeTree(root, 0);
  printf("\n");
  return 0;
}