#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct btree BTREE;

struct btree
{
  int number_keys;
  int is_leaf;
  int keys[T-1];
  BTREE *childs[T];
};

//cria um novo no da arvore b
BTREE* create_btree()
{
  BTREE *new_btree = (BTREE*)malloc(sizeof(BTREE));
  new_btree->number_keys = 0;
  new_btree->is_leaf = 1;
  for(int i = 0; i < T; i++)
  {
    new_btree->childs[i] = NULL;
  }

  return new_btree;
}

//faz a quebra da pagina
BTREE* split(BTREE *root, int i)
{

}

// Função auxiliar para inserir uma chave em um nó que não está cheio
void insert_non_full(BTREE *node, int key)
{
    int i = node->number_keys - 1;
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
      
    }
}

//insere uma chave na arvore b
BTREE* insert(BTREE *root, int key)
{
  if(root == NULL)
  {
    root = create_btree();
    root->keys[0] = key;
    root->number_keys++;
    
    return root;
  }
  else
  {
    if(root->number_keys == T - 1)
    {
      BTREE *new_root = create_btree();
      new_root->is_leaf = 0;
      new_root = split(new_root, 0);
    }
    else
    {
      insert_non_full(root, key);
    }
  }


  return root;
}

int main()
{
  BTREE *root = NULL;
  root = insert(root, 10);
  root = insert(root, 20);
  printf("%d\n", root->keys[0]);
  printf("%d\n", root->keys[1]);
  printf("%d\n", root->number_keys);
}