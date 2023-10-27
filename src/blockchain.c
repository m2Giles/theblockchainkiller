#include <stdio.h>
#include <stdlib.h>
#include "include/block.h"
#include "include/blockchain.h"
#include "include/linked_list.h"
#include "include/return_codes.h"

return_code_t blockchain_create(
    blockchain_t **blockchain,
    size_t num_leading_zero_bytes_required_in_block_hash
) {
    return_code_t return_code = SUCCESS;
    if (NULL == blockchain) {
        return_code = FAILURE_INVALID_INPUT;
        goto end;
    }
    blockchain_t *new_blockchain = malloc(sizeof(blockchain_t));
    if (NULL == new_blockchain) {
        return_code = FAILURE_COULD_NOT_MALLOC;
        goto end;
    }
    linked_list_t *block_list = NULL;
    return_code = linked_list_create(
        &block_list,
        (free_function_t *)block_destroy,
        NULL);
    if (SUCCESS != return_code) {
        free(new_blockchain);
        goto end;
    }
    new_blockchain->block_list = block_list;
    new_blockchain->num_leading_zero_bytes_required_in_block_hash =
        num_leading_zero_bytes_required_in_block_hash;
    *blockchain = new_blockchain;
end:
    return return_code;
}

return_code_t blockchain_destroy(blockchain_t *blockchain) {
    return_code_t return_code = SUCCESS;
    if (NULL == blockchain) {
        return_code = FAILURE_INVALID_INPUT;
        goto end;
    }
    return_code = linked_list_destroy(blockchain->block_list);
    free(blockchain);
end:
    return return_code;
}

return_code_t blockchain_add_block(blockchain_t *blockchain, block_t *block) {
    return_code_t return_code = SUCCESS;
    if (NULL == blockchain || NULL == block) {
        return_code = FAILURE_INVALID_INPUT;
        goto end;
    }
    return_code = linked_list_append(blockchain->block_list, block);
end:
    return return_code;
}

return_code_t blockchain_is_valid_proof_of_work(
    blockchain_t *blockchain,
    block_t *block,
    bool *is_valid_proof_of_work
) {
    return_code_t return_code = SUCCESS;
    if (NULL == blockchain || NULL == block || NULL == is_valid_proof_of_work) {
        return_code = FAILURE_INVALID_INPUT;
        goto end;
    }
    sha_256_t hash = {0};
    return_code = block_hash(block, &hash);
    if (SUCCESS != return_code) {
        goto end;
    }
    bool is_valid = true;
    for (size_t idx = 0;
        idx < blockchain->num_leading_zero_bytes_required_in_block_hash;
        idx++) {
        if (hash.digest[idx] != 0) {
            is_valid = false;
            break;
        }
    }
    *is_valid_proof_of_work = is_valid;
end:
    return return_code;
}

void blockchain_print(blockchain_t *blockchain) {
    if (NULL == blockchain) {
        return;
    }
    for (node_t *node = blockchain->block_list->head;
        NULL != node;
        node = node->next) {
        block_t *block = (block_t *)node->data;
        printf("%d->", block->proof_of_work);
    }
    printf("\n");
}
