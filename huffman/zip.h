#include "structshuffman.h"

//struct para compactacao
struct tree
{
    void *byte;
    long frequency;
    TREE *next, *left, *right;
};


/**
* Cria um no tipo TREE e retorna ele.
*
* A função new_tree_node() recebe um byte e sua frequencia para alocar memoria para um no
* novo e o byte, isso para que não haja o risco da variavel i alterar todos os bytes apos ser mudada.
* por fim ela retorna o endereco do no criado.
*
* @param        i       Um ponteiro para void.
* @param    frequency   Um long para para a frequencia.
* @return               Um no da arvore de huffman, ou o endereco do no criado, ou um ponteiro para TREE.
*/
TREE* new_tree_node(void *i, long frequency)
{
    TREE *new_node = (TREE*)malloc(sizeof(TREE));
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
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->next = NULL;
    new_node->right = NULL;

    return new_node;
}


/**
* Enfileira os bytes de acordo com a frequencia.
*
* A função enqueue() recebe a cabeca da fila de prioridade e o novo no da arvore que sera enfileirado
* de acordo com a sua frequencia. Enfileira do menor para o maior, nos com mesma frequencia sao enfileirados
* antes do de frequencia parecida.
*
* @param    tree_node   Um ponteiro duplo para a cabeça da lista.
* @param      node      Um ponteiro para o no a ser enfileirado.
*/
void enqueue(TREE **tree_node, TREE *node)
{
    TREE *new_queue_node = node;

    if((*tree_node) == NULL || (*tree_node)->frequency >= new_queue_node->frequency)
    {
        new_queue_node->next = *tree_node;
        *tree_node = new_queue_node;
    }
    else
    {
        TREE *current = *tree_node;
        while(current->next != NULL)
        {
            if(current->next->frequency >= new_queue_node->frequency)
            {
                break;
            }
            current = current->next;
        }   
        new_queue_node->next = current->next;
        current->next = new_queue_node;
    }
    return;
}


/**
* Retira um elemento da fila de priorirade e retorna o ponteiro para ele.
*
* A função dequeue() recebe a cabeca da fila de prioridade e remove ele, aponta o next da fila para NULL
* e retorna o endereco do no.
*
* @param    queue   Um ponteiro duplo para a cabeça da fila.
* @return           Retorna o endereco do no removido da fila. 
*/
TREE* dequeue(TREE **queue)
{
    if(queue == NULL)
    {
        return NULL;
    }
    TREE *dequeued = *queue;
    *queue = dequeued->next;
    dequeued->next = NULL;
    return dequeued;
}


/**
* Cria uma nova subarvore da arvore de huffman.
*
* A função new_huffman_node() recebe os nos que ficaram a esquerda e direita, respectivamente, e o simbolo
* que escolhemos para fazer parte da raiz, em nosso caso foi o *, aloca memoria para a razi e o simbolo
* e cria uma sub arvore da nossa arvore de huffman.
*
* @param    left    Um ponteiro para o no que vai ficar a esquerda da raiz da sub arvore.
* @param    right   Um ponteiro para o no que vai ficar a direita da raiz da sub arvore.
* @param    byte    Um ponteiro para void com o simbolo a ser inserido na raiz da sub arvore.
* @return           Retorna o endereco da raiz da subarvore. 
*/
TREE* new_huffman_node(TREE *left, TREE *right, void *byte)
{
    TREE *root = (TREE*)malloc(sizeof(TREE));
    if(root == NULL)
    {
        printf("\nError allocating root\n");
        exit(1);
    }
    root->byte = (void*)malloc(1);
    if(root->byte == NULL)
    {
        printf("\nError allocating byte to root\n");
        exit(1);
    }
    memcpy(root->byte, byte, 1);
    root->frequency = (left->frequency) + (right->frequency);
    root->left = left;
    root->right = right;

    return root;
}


/**
* Cria uma arvore de huffman.
*
* A função insert_huffman_tree() recebe a fila de prioridade e a raiz da arvore retirando no a no
* da fila e enviando para a funcao new_huffman_node() criando varias subarvores e inserindo na fila novamente.
* e encerrada quado a fila esta com apenas um no que e a raiz da arvore de huffman.
*
* @param        queue       Um ponteiro duplo a cabeca da fila de prioridade.
* @param    huffman_tree    Um ponteiro duplo para a raiz da arvore de huffman. 
*/
void insert_huffman_tree(TREE **queue, TREE **huffman_tree)
{
    uint8_t byte = '*';
    //montando a arvore de huffman
    while((*queue)->next != NULL)
    {
        TREE *left = dequeue(&*queue), *right = dequeue(&*queue), *root;
        root = new_huffman_node(left, right, &byte);
        enqueue(&*queue, root);
    }

    *huffman_tree = dequeue(&*queue);
    return;
}


/**
* Acha a altura da arvore de huffman.
*
* A função height() recebe a raiz da arvore de huffman e vizita no a no para determinar a altura maximo
* da arvore retornando essa altura.
*
* @param     tree_node    Um ponteiro para a raiz da arvore de huffman.
* @return                 A altura da arvore de huffman. 
*/
long height(TREE *tree_node)
{
    int left, right;
    if(tree_node == NULL)
    {
        return -1;
    }
    else
    {
        left = height(tree_node->left) + 1;
        right = height(tree_node->right) + 1;
        if(left > right)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}


/**
* Acha a altura da arvore de huffman.
*
* A função tree_size() recebe o no da arvore de huffman e visita no a no contabilizando quantos nos tem para
* determianr o seu tamanho, ao finalizar ela retorna o tamanho da arvore
*
* @param     tree_node    Um ponteiro para a raiz da arvore de huffman.
* @return                 O tamano da arvore de huffman. 
*/
long tree_size(TREE *tree_node)
{
    if(tree_node == NULL)
    {
        return 0;
    }
    return 1 + ((tree_node->left == NULL && tree_node->right == NULL) && (*(unsigned char*)tree_node->byte == '*' || *(unsigned char*)tree_node->byte == '\\')) + tree_size(tree_node->left) + tree_size(tree_node->right);
}


/**
* Cria o dicionario.
*
* A função create_dicionary() recebe a altura da arvore + 1 e cria um dicionario em forma de matriz para criarmos uma nova tabela de bits.
* Ao finalizar a criacao ela retorna o endereco desse dicionario
*
* @param     tree_size     A altura da arvore + 1.
* @return                  Um ponteiro para o endereco do dicionario criado
*/
uint8_t** create_dicionary(int tree_size)
{
    int i;
    uint8_t **new_dicionary = (uint8_t**)malloc(sizeof(uint8_t*) * Max_table);
    if(new_dicionary == NULL)
    {
        printf("\nError allocating dictionary\n");
        exit(1);
    }
    for(i = 0; i < Max_table; i++)
    {
        new_dicionary[i] = (uint8_t*)malloc(sizeof(uint8_t) * tree_size);
        if(new_dicionary[i] == NULL)
        {
            printf("\nError allocating rest of dictionary\n");
            exit(1);
        }
        new_dicionary[i][0] = '\0';
    }

    return new_dicionary;
}


/**
* Preenche o dicionario.
*
* A função generate_codes() recebe o dicionario, a arvore, a profundidade atual e um vetor de auxilio.
* Com a ajuda do vetor de auxilio percorremos a arvore de huffman com um DFS atribuindo 0's e 1's ao vetor auxiliar.
* Ao chegar em uma folha nos adicionamos tudo que estiver no vetor auxiliar ao dicionario na linha que represente o byte
* gerando uma nova tabela para os bits.
*
* @param     dicionary    Um ponteiro duplo para o dicionario.
* @param        root      Um ponteiro para a raiz da arvore.
* @param       depth      A profundidade atual da arvore.
* @param        aux       Um ponteiro para um vetor que auxilie no preenchimento do dicionario.
*/
void generate_codes(uint8_t **dicionary, TREE *root, long depth, uint8_t *aux)
{
    if(root->left == NULL && root->right == NULL)
    {
        uint8_t byte = *(uint8_t*)root->byte;
        for(int i = 0; i < depth; i++)
        {
            dicionary[byte][i] = aux[i];
        }
        dicionary[byte][depth] = '\0';
        return;
    }

    aux[depth] = '0';
    generate_codes(dicionary, root->left, depth + 1, aux);

    aux[depth] = '1';
    generate_codes(dicionary, root->right, depth + 1, aux);
}


/**
* Pega o lixo de bits gerados.
*
* A função trash() recebe o dicionario e a tabela de frequencias fazendo a contabilizacao de bits lixo
*
* @param     dicionary    Um ponteiro duplo para o dicionario.
* @param       freq       Um ponteiro para a tabela de frequencias.
* @return                 A quantidade de bits de lixo presentes na compactacao.
*/
int trash(uint8_t **dicionary, long *freq){
    long bits_before = 0;
    long bits_after = 0;
    for(int i = 0; i < Max_table; i++){
        if (freq[i] != 0)
        {
            bits_before += freq[i] * 8;
            bits_after += freq[i] * strlen(dicionary[i]);
        }
    }

    printf("\nbits before: %ld bits_after: %ld\n", bits_before, bits_after);

    return (bits_before - bits_after) % 8;
}


/**
* Escreve a arvore de huffman no arquivo compactado.
*
* A função write_tree_in_header() recebe um ponteiro para o arquivo comprimido e a arvore de compactacao, em seguida ele escreve
* a arvore no a no no arquivo compactado.
*
* @param     compressed_file    Um ponteiro para o arquivo de compactacao.
* @param          tree          Um ponteiro para a raiz da arvore de huffman.
*/
void write_tree_in_header(FILE *compressed_file, TREE *tree)
{
    if(tree == NULL)
    {
        return;
    }
    if((tree->left == NULL && tree->right == NULL) && (*(uint8_t*)tree->byte == '*' || *(uint8_t*)tree->byte == '\\'))
    {
        uint8_t scape = (uint8_t)'\\';
        fwrite(&scape, sizeof(uint8_t), 1, compressed_file);
    }
    uint8_t byte = *(uint8_t*)tree->byte;
    fwrite(&byte, sizeof(uint8_t), 1, compressed_file);
    write_tree_in_header(compressed_file, tree->left);
    write_tree_in_header(compressed_file, tree->right);
}


/**
* Escreve o cabeçalho no arquivo compactado.
*
* A função write_header_in_file() recebe um ponteiro para o arquivo de compactacao, os bits de lixo, o tamanho da arvore e um ponteiro para a raiz
* da arvore. Em seguida escreve os bits de lixo e o tamanho da arvore no arquivo, depois passa para a funcao write_tree_in_header() o trabalho de
* escrever a arvore em pre-ordem no arquivo compactado.
*
* @param     compressed_file      Um para o arquivo de compactacao.
* @param        bits_trash        Quantidade de bits que temos de lixo.
* @param        tree_size         Tamanho da arvore.
* @param          tree            Um ponteiro para a raiz da arvore.
*/
void write_header_in_file(FILE *compressed_file, int bits_trash, long tree_sizee, TREE *tree)
{
    //calculando o num de bits de lixo no ultimo byte
    uint8_t byte;

    byte = bits_trash << 5;
    byte |= ((uint8_t)(tree_sizee >> 8));

    uint8_t segundo_byte = (uint8_t)tree_sizee;

    fwrite(&byte, sizeof(uint8_t), 1, compressed_file);
    fwrite(&segundo_byte, sizeof(uint8_t), 1, compressed_file);
    
    //gravando a arvore
    write_tree_in_header(compressed_file, tree);
}


/**
* Escreve os bytes compactados.
*
* A função write_compressed_bytes() recebe um ponteiro para o arquivo de compactacao, um ponteiro para o vetor que guarda todos os
* dados do arquivo de compactacao, um ponteiro duplo para o dicionario e o tamanho do arquivo a ser compactado. Em seguida, para cada
* byte no vetor data ele checa sua nova representacao em bits no dicionario e atribui a um byte generico. Quando o byte generico completa
* 8 bits ele escreve esse byte no arquivo.
*
* @param     compressed_file      Um para o arquivo de compactacao.
* @param          data            Um ponteiro para o vetor de dados ou de bytes do arquivo a ser compactado.
* @param        dicionary         Um ponteiro duplo para o dicionario.
* @param        file_size         O tamanho do arquivo.
*/
void write_compressed_bytes(FILE *compressed_file, uint8_t *data, uint8_t **dicionary, long file_size)
{
    long i, j, bit_index = 7;
    uint8_t byte = 0;
    int new_byte;
    for(i = 0; i < file_size; i++)
    {
        for(j = 0; dicionary[data[i]][j] != '\0'; j++)
        {
            if(dicionary[data[i]][j] == '1')
            {
                byte |= 1 << bit_index;
            }
            bit_index--;
            if(bit_index < 0)
            {
                fwrite(&byte, sizeof(unsigned char), 1, compressed_file);
                bit_index = 7;
                byte = 0;
            }
        }
    }
    if(bit_index != 7)
    {
        fwrite(&byte, sizeof(unsigned char), 1, compressed_file);
    }

    return;
}


/**
* Limpa a memoria alocada para o dicionario.
*
* A função free_dicionary() recebe um ponteiro duplo para o dicionario e libera toda memoria alocada para ele.
*
* @param        dicionary         Um ponteiro duplo para o dicionario.
*/
void free_dicionary(uint8_t **dicionary)
{
    int i;
    for(i = 0; i < 256; i++)
    {
        free(dicionary[i]);
    }
    free(dicionary);
    return;
}


/**
* Limpa a memoria alocada para a arvore de huffman.
*
* A função free_huffman_tree() recebe um ponteiro para a raiz da arvore de huffman e libera toda memoria alocada para os nos
* e para o byte no a no.
*
* @param        root         Um ponteiro para a raiz da arvore de huffman.
*/
void free_huffman_tree(TREE *root)
{
    if(root == NULL)
    {
        return;
    }
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root->byte);
    free(root);
    return;
}


/**
* Comprime o arquivo.
*
* A função compress() recebe o nome do arquivo a ser compactado e faz toda a sequencia de compactacao: leitura do arquivo, criacao de lista de
* frequencias, criacao da fila de prioridade, criacao da arvore de huffman a partir da lista de prioridade, criacao da tabela para compactacao (dicionario),
* escrita de cabecalho no arquivo e escrita do arquivo compactado. Ela também faz a mudanca do nome do arquivo para .huff, exemplo: arquivo.png fica
* arquivo.png.huff. Ao final de tudo ela libera toda a memoria que foi alocada durante o processo.
*
* @param        archive_name         Um ponteiro para a raiz da arvore de huffman.
*/
void compress(char *archive_name)
{
    //criando variáveis
    //cria a fila de prioridade
    TREE *queue = NULL;
    //criando arvore de huffman
    TREE *hft = NULL;
    //criando a variavel do dicionario
    uint8_t **dicionary; 
    //criando a variavel que auxilia a preencher o dicionario
    uint8_t *aux;

    //abrindo o arquivo
    FILE *file = fopen(archive_name, "rb"), *compressed_file;
    if(file == NULL)
    {
        printf("\nCould not find .huff file\n");
        exit(1);
    }

    //criando a variavel que vai manter todos os bytes
    uint8_t *data;
    //criando a tabela de frequencia
    long frequency[Max_table], i;

    //lendo os bytes do arquivo
    printf("\nReading bytes from the file\n");
    //procura o fim do arquivo
    fseek(file, 0, SEEK_END);
    //pega o tamanho do arquivo
    long file_size = ftell(file);
    //volta o ponteiro para o inicio do arquivo
    fseek(file, 0, SEEK_SET);
    //aloca memoria para a variavel data que usaremos para pegar todos os bytes do arquivo
    data = malloc(file_size);
    if(data == NULL)
    {
        printf("\nCould not allocate memory for vector files\n");
        exit(1);
    }
    //setando os bytes para 0
    memset(data, 0, file_size);
    //pegando todos os bytes do arquivo
    fread(data, 1, file_size, file);
    //fechando o arquivo
    fclose(file);

    //iniciando as frequencias como 0
    memset(frequency, 0, Max_table*sizeof(long));

    //obtendo frequencias dos bytes
    printf("\nSetting up the frequency table\n");
    for(i = 0; i < file_size; i++)
    {
        //pegando a frequencia de cada byte
        frequency[data[i]]++;
    }
    
    //montando a fila de prioridade
    printf("\nSetting up the priority queue\n");
    for(i = 0; i < Max_table; i++)
    {
        //avaliando se a frequencia e igual a 0 para nao pegarmos o byte que nao tem no arquivo
        if(frequency[i] != 0)
        {
            //fazendo o cast da variavel i para do tipo unsigned char
            (uint8_t)i;
            //insere na fila de frequencia de maneira organizada
            enqueue(&queue, new_tree_node(&i, frequency[i]));
        }
    }

    //criando a arvore de huffman
    printf("\nSetting up the huffman tree for compression\n");
    insert_huffman_tree(&queue, &hft);

    //pegando a altura da arvore
    long tree_height = height(hft);
    //pegando o tamanho da arvore
    long tree_sizee = tree_size(hft);

    
    //criando o dicionário
    printf("\nCreating the dictionary with new bits\n");
    dicionary = create_dicionary(tree_height + 1);

    //criando o vetor auxiliar para preencher o dicionario
    printf("\nCreating auxiliary vector\n");
    aux = (uint8_t*)malloc(sizeof(uint8_t) * (tree_height + 1));
    if(aux == NULL)
    {
        printf("\nCould not allocate memory for auxiliary array\n");
        exit(1);
    }
    
    //preenchendo o dicionario
    printf("\nFilling the dictionary with the new representation of the old bytes\n");
    generate_codes(dicionary, hft, 0, aux);
    
    //calculo do lixo de bits
    printf("\nFinding the Trash Bits\n");
    int bits_trash = trash(dicionary, frequency);
    //mudanca do nome, exemplo: arquivo.txt vira arquivo.txt.huff
    printf("\nChanging the file name to .huff\n");
    for(i = 0; i != 106; i++)
    {
        if(archive_name[i] == '\0' && i + 6 <= 106)
        {
            archive_name[i] = '.';
            archive_name[i + 1] = 'h';
            archive_name[i + 2] = 'u';
            archive_name[i + 3] = 'f';
            archive_name[i + 4] = 'f';
            archive_name[i + 5] = '\0';
            break;
        }
    }

    //escrevendo o arquivo comprimido
    compressed_file = fopen(archive_name,"wb");
    if(compressed_file == NULL)
    {
        printf("\nUnable to open output file\n");
        exit(1);
    }
    //escrevendo o cabecalho
    printf("\nWriting header data\n");
    write_header_in_file(compressed_file, bits_trash, tree_sizee, hft);
    //escrevendo os bytes compactados
    printf("\nWriting the compressed bytes to the file\n");
    write_compressed_bytes(compressed_file, data, dicionary, file_size);
    //fechando o arquivo
    fclose(compressed_file);

    //liberando a memoria alocada
    printf("\nClearing all allocated memory\n");
    //libera a memoria do dicionario
    free_dicionary(dicionary);
    //libera a memoria da arvore
    free_huffman_tree(hft);
    //libera a memoria do vetor auxiliar
    free(aux);
    //libera a memoria alocada para o vetor data
    free(data);
    aux = NULL;
    dicionary = NULL;
    hft = NULL;
    data = NULL;
    
    printf("\nSuccessfully compressed file!!\n\n");
    return;
}
