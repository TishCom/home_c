#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_pool.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static void reset_ptr_block_pool(MemoryPool *pool);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация пула памяти*/
bool initializePool(MemoryPool *pool, uint32_t block_size, uint32_t block_count)
{
    if (pool == NULL || block_count == 0 || block_size < sizeof(void*))
        return false;

    pool->buffer = (void*)malloc(block_count * block_size);
    if (pool->buffer == NULL)
        return false;

    pool->block_count = block_count;
    pool->block_size = block_size;
    pool->used_blocks = 0;
    reset_ptr_block_pool(pool);

    return true;
}

/*проверка, является ли пул памяти пустым*/
bool poolIsEmpty(const MemoryPool *pool)
{
    if (pool == NULL)
        return false;

    return pool->used_blocks == 0;
}

/*проверка, является ли пул памяти полным*/
bool poolIsFull(const MemoryPool *pool)
{
    if (pool == NULL)
        return false;

    return pool->used_blocks == pool->block_count;
}

/*определяет количество занятых блоков в пуле памяти*/
uint32_t poolUsedBlockCount(const MemoryPool *pool)
{
    if (pool == NULL)
        return false;

    return pool->used_blocks;
}

/*определяет количество свободных блоков в пуле памяти*/
uint32_t poolUnusedBlockCount(const MemoryPool *pool)
{
    if (pool == NULL)
        return false;

    return pool->block_count - pool->used_blocks;
}

/*выделение свободного блока памяти для пользователя*/
void* poolAllocBlock(MemoryPool *pool)
{
    if (pool == NULL || pool->buffer == NULL || poolIsFull(pool))
        return NULL;

    void *current_block = pool->free_block;

    pool->free_block = *(void**)pool->free_block;
    pool->used_blocks++;

    return current_block;
}

/*освобождение блока памяти занятого пользователем*/
bool poolFreeBlock(MemoryPool *pool, void *block)
{
    if (pool == NULL || pool->buffer == NULL || poolIsEmpty(pool) || block == NULL)
        return false;

    *(void**)block = pool->free_block;
    pool->free_block = block;
    pool->used_blocks--;

    return true;
}

/*освобождение выделенной памяти если она есть*/
bool emptyThePool(MemoryPool *pool)
{
    if (pool == NULL)
        return false;

    free(pool->buffer);
    pool->block_count = 0;
    pool->block_size = 0;
    pool->free_block = NULL;
    pool->used_blocks = 0;

    return true;
}

/*сброс состояния пула памяти*/
bool resetPool(MemoryPool *pool)
{
    if (pool == NULL || pool->buffer == NULL)
        return false;

    reset_ptr_block_pool(pool);
    pool->used_blocks = 0;

    return true;
}
 
/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/


/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static void reset_ptr_block_pool(MemoryPool *pool)
{
    char *ptr = (char*)pool->buffer;

    for (uint32_t i = 0; i < pool->block_count - 1; i++) 
    {
        /*привидение (void**) необходимо чтобы компилятор понимал,
        что мы начиная с этой ячейки будем записывать не char, а указатель*/
        *(void**)ptr = ptr + pool->block_size;
        ptr += pool->block_size;
    }
    *(void**)ptr = NULL;
    
    pool->free_block = pool->buffer;
}