#include "structshuffman.h"

//struct para arvore de descompactacao
struct descompressed_tree
{
    void *byte;
    TREE_D *left, *right;
};


/**
* Verifica se o bit esta setado.
*
* A is_bit_i_set() recebe o no da arvore de huffman e visita no a no contabilizando quantos nos tem para
* determianr o seu tamanho, ao finalizar ela retorna o tamanho da arvore.
*
* @param      c     O byte a ser testado.
* @param      i     Qual bit vai ser testado.
* @return           Se o bit testado e 0 ou 1. 
*/
int is_bit_i_set(uint8_t c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

/**
* Pega os bits referentes aos bits lixo e ao tamanho da arvore de huffman no arquivo compactado.
*
* A trash_bits_and_tree_size_bits() recebe um ponteiro para a variavel de bits lixo, um para a do tamanho da arvore e um ponteiro
* para o vetor de dados do arquivo a ser descompactado. Em seguida retira do vetor de dados a quantidade de bits lixo e o tamanho
* da arvore.
*
* @param          trahs          Um ponteiro para a variavel de bits lixo.
* @param        tree_size        Um ponteiro para o vetor de dados do arquivo ou bytes.
* @param          data           O tamanho do arquivo compactado.
*/
void trash_bits_and_tree_size_bits(int *trash, long *tree_size, uint8_t *data)
{
    int i, j, k, bit;
    uint8_t mask;
    //primeiro pegamos os bits referente ao lixo
    for(i = 7, j = 2; i >= 5; i--, j--)
    {
        bit = is_bit_i_set(data[0], i); 
        if(bit)
        {
            *trash |= 1 << j;
        }
    }
    
    //pegando os bits do tamanho da arvore
    for(i = 4, j = 12, k = 0; j >= 0; j--)
    {
        bit = is_bit_i_set(data[k], i); 
        if(bit)
        {
            *tree_size |= 1 << j;
        }
        i--;
        if(i < 0)
        {
            i = 7;
            k++;
        }
    }

    return;
}


/**
* Cria um novo no da arvore de huffman para a descompactacao.
*
* A new_tree_node_D() recebe o byte que vamos armazenar no no da arovre em forma de ponteiro para void. Aloca
* memoria para o no e o byte e em seguida retorna um ponteiro para o endereco do no.
*
* @param     i     Um ponteiro para void com o endereco do byte.
* @return          Um ponteiro para o endereco do novo no. 
*/
TREE_D* new_tree_node_D(void *i)
{
    TREE_D *new_node = (TREE_D*)malloc(sizeof(TREE_D));
    if(new_node == NULL)
    {
        printf("\nError allocating node from tree\n");
        exit(1);
    }
    new_node->byte = (void*)malloc(1);
    if(new_node->byte == NULL)
    {
        printf("\nError allocating byte\n");
        exit(1);
    }
    memcpy(new_node->byte, i, 1);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}


/**
* Monta a arvore de huffman.
*
* A unzipping_tree() recebe a raiz da arvore de huffman, o vetor de dados do arquivo, a posicao atual do vetor e o tamanho da 
* arvore + 2. Em seguida ela monta a arvore de huffman para a descompactacao retornando um ponteiro pra a raiz da arvore.
*
* @param         root           Um ponteiro para a raiz da arvore de huffman.
* @param         data           Um ponteiro para o vetor de dados do arquivo ou bytes.
* @param           i            Um ponteiro para a posicao atual no vetor de dados do arquivo ou bytes.
* @param       tree_size        O tamanho da arvore + 2.
* @return                       Um ponteiro para o endereco da raiz da arvore de huffman. 
*/
TREE_D* unzipping_tree(TREE_D *root, uint8_t *data, int *i, long tree_size)
{
    if(*i == tree_size)
    {
        //testar outra hora com os caracteres de escape pra ver se vai dar pau
        return NULL;
    }
    else
    {
        if(data[*i] == '\\')
        {
            (*i)++;
            root = new_tree_node_D(&data[*i]);
            (*i)++;
            return root;
        }
        else if(data[*i] == '*')
        {
            root = new_tree_node_D(&data[*i]);
            (*i)++;
            root->left = unzipping_tree(root->left, data, i, tree_size);
            root->right = unzipping_tree(root->right, data, i, tree_size);
        }
        else
        {
            root = new_tree_node_D(&data[*i]);
            (*i)++;
            return root;
        }
    }

    return root;
}


/**
* Escreve no arquivo descompactado.
*
* A write_file() recebe um ponteiro para o arquivo de descompactacao, um ponteiro para o vetor de dados do arquivo a ser
* descompactado, o tamanho do arquivo, um ponteiro para o no raiz da arvore de descompactacao e a quantidade de lixo no byte
* final. Em seguida ela escreve os dados descompactados no arquivo de descompactacao.
*
* @param       file_descompressed          Um ponteiro para o arquivo de descompactacao.
* @param            data                   Um ponteiro para o vetor de dados do arquivo ou bytes.
* @param          file_size                O tamanho do arquivo compactado.
* @param             i                     A posicao atual no vetor de dados do arquivo ou bytes.
* @param            tree                   Um ponteiro para a raiz da arvore de huffman.
* @param            trash                  A quantidade de bits de lixo no ultimo byte.
*/
void write_file(FILE* descompressed_file, uint8_t* data, long filesize, long i, TREE_D* tree, int trash)
{
    TREE_D* aux = tree;

    while(i < filesize)
    {
        uint8_t byte = data[i];

        for(int j = 7; j >= 0; j--)
        {
            if(i == filesize - 1 && j < trash) return;

            aux = is_bit_i_set(byte, j) ? aux->right : aux->left;

            if(!aux->right && !aux->left)
            {
                fwrite(&(*(uint8_t *)aux->byte), sizeof(uint8_t), 1, descompressed_file);
                aux = tree;
            }
        }
        i++;
    }
}

/**
* Limpa a memoria alocada para a arvore de huffman.
*
* A free_huffman_tree_D() recebe um ponteiro para a raiz da arvore e libera toda a memoria alocada para cada no e byte
* no a no.
*
* @param       root       Um ponteiro para o no raiz da arvore.
*/
void free_huffman_tree_D(TREE_D *root)
{
    if(root == NULL)
    {
        return;
    }
    free_huffman_tree_D(root->left);
    free_huffman_tree_D(root->right);
    free(root->byte);
    free(root);

    return;
}


/**
* Descomprime o arquivo.
*
* A função descompressed() recebe o nome do arquivo a ser descompactado e faz toda a sequencia de descompactacao: le o arquivo,
* pega os bits lixo e o tamanho da arvore do cabecalho, constroi a arvore de huffman para a descompactacao e escreve todos os bytes do arquivo
* original. Vale ressaltar que ela so trabalha com arquivos .huff e faz a mudanca do nome do arquivo para o nome e o tipo original, esemplo:
* arquivo.png.huff vira arquivo.png. Ao final de tudo ela desaloca toda a memoria alocada durante o processo.
*
* @param        archive_name         Um ponteiro para a raiz da arvore de huffman.
*/
void descompressed(char *archive_name)
{
    //abrindo o arquivo de leitura e escrita da descompactacao
    FILE *compressed_file, *descompressed_file;
    TREE_D *hft_descompressed = NULL;
    compressed_file = fopen(archive_name, "rb");
    uint8_t *data;
    int bits_trash = 0, i; 
    long tree_size = 0;
    if(compressed_file == NULL)
    {
        printf("\nCould not find the file\n");
        exit(1);
    }
    //buscando o final do arquivo
    printf("\nReading bytes from the file\n");
    fseek(compressed_file, 0, SEEK_END);
    //pegando o tamanho do arquivo
    long file_size = ftell(compressed_file);
    //voltando para o inicio do arquivo
    fseek(compressed_file, 0, SEEK_SET);
    //alocando memoria para a variavel data
    data = malloc(file_size);
    if(data == NULL)
    {
        printf("\nCould not allocate memory for vector files\n");
        exit(1);
    }
    //setando 0 em todas as posicos de data
    memset(data, 0, file_size);
    //pegando todos os bytes do arquivo
    fread(data, 1, file_size, compressed_file);
    //fechando o arquivo
    fclose(compressed_file);

    //pegando a quantidade de bits de lixo que temos e o tamanho da arvore
    printf("\nGetting garbage bits and huffman tree size, for unpacking, from header\n");
    trash_bits_and_tree_size_bits(&bits_trash, &tree_size, data);
    //montando a arvore de huffman
    printf("\nSetting up the huffman tree for unpacking\n");
    i = 2;
    hft_descompressed = unzipping_tree(hft_descompressed, data, &i, tree_size + 2);

    //mudando o nome do arquivo
    printf("\nchanging the file name\n");
    int archive_name_size = strlen(archive_name);
    archive_name[archive_name_size - 5] = '\0';
    descompressed_file = fopen(archive_name, "wb");
    
    //escrevendo arquivo descompactado
    printf("\nWriting uncompressed bytes to file\n");
    if(descompressed_file == NULL)
    {
        printf("Could not create output file\n");
        exit(1);
    }
    write_file(descompressed_file, data, file_size, i, hft_descompressed, bits_trash);

    //liberando o espaço
    printf("\nClearing all allocated memory\n");
    free(data);
    free_huffman_tree_D(hft_descompressed);
    hft_descompressed = NULL;
    data = NULL;

    printf("\nSuccessfully descompressed file!!\n\n");
    return;
}