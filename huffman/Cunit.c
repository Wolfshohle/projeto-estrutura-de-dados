#include <CUnit/CUnit.h>
#include <CUnit/Basic.h> 
#include <stdbool.h>
#include "zip.h"
#include "unzip.h"


//insere na fila de prioridade
bool insert_in_queue(TREE **queue, uint8_t byte, long freq)
{
    enqueue(&*queue, new_tree_node(&byte, freq));
    if(*(uint8_t*)(*queue)->byte == byte)
    {
        return true;
    }
    return false;
}

//remove da fila de prioridade
bool remove_from_queue(TREE **queue, uint8_t byte)
{
    TREE *dequeued = dequeue(&*queue);
    if(*(uint8_t*)dequeued->byte == byte)
    {
        return true;
    }
    return false;
}

//monta a arvore
bool huffman_tree_compressed_test(TREE **queue, uint8_t left_byte, uint8_t right_byte)
{
    TREE *huffman_tree = NULL;
    insert_huffman_tree(&*queue, &huffman_tree);
    uint8_t huffman_left = *(uint8_t*)huffman_tree->left->byte, huffman_right = *(uint8_t*)huffman_tree->right->byte;
    if(huffman_left == left_byte && huffman_right == right_byte)
    {
        return true;
    }
    return false;
}

//testa algumas funções de compactação
void test_compress_function()
{
    TREE *queue = NULL;
    CU_ASSERT(insert_in_queue(&queue, 'A', 8) == true);
    CU_ASSERT(insert_in_queue(&queue, 'B', 7) == true);
    CU_ASSERT(insert_in_queue(&queue, 'C', 6) == true);
    CU_ASSERT(insert_in_queue(&queue, 'Q', 5) == true);
    CU_ASSERT(insert_in_queue(&queue, 'G', 9) == false);

    CU_ASSERT(remove_from_queue(&queue, 'Q') == true);
    CU_ASSERT(remove_from_queue(&queue, 'C') == true);
    CU_ASSERT(remove_from_queue(&queue, 'G') == false);

    CU_ASSERT(huffman_tree_compressed_test(&queue, 'A', 'G') == true);
}

//testa montagem da arvore de huffman para a descompactacao
bool huffman_tree_descompressed_test(TREE_D **hft, uint8_t *data, long tree_size, uint8_t test_byte)
{
    int i = 0;
    *hft = unzipping_tree(*hft, data, &i, tree_size);
    if(*(uint8_t*)(*hft)->right->byte == test_byte)
    {
        return true;
    }
    return false;
}

//testa algumas funções de descompactação
void test_descompressed_function()
{
    uint8_t data[5] = {'*', '*', 'A', 'B', 'C'};
    TREE_D *hft = NULL;

    CU_ASSERT(huffman_tree_descompressed_test(&hft, data, 5, 'C') == true);
    CU_ASSERT(is_bit_i_set(1, 0) == 1);

}

int main()
{
    CU_initialize_registry();
    
    //testa a fila de prioridade e a arvore de huffman para compactacao
    CU_pSuite suite_compress_function = CU_add_suite("Test Compress Function", 0, 0);
    CU_add_test(suite_compress_function, "test_compress_function", test_compress_function);

    //testa a arvore de huffman
    CU_pSuite suite_descompressed_function = CU_add_suite("Descompressed Function", 0, 0);
    CU_add_test(suite_descompressed_function, "test_descompressed_function", test_descompressed_function);

    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();

    CU_cleanup_registry();
}