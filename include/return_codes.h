/**
 * @brief Defines return codes for the project.
 */

#ifndef INCLUDE_RETURN_CODES_H_
#define INCLUDE_RETURN_CODES_H_

typedef enum return_code_t {
    SUCCESS,
    FAILURE_COULD_NOT_MALLOC,
    FAILURE_INVALID_INPUT,
    FAILURE_LINKED_LIST_EMPTY,
    FAILURE_LINKED_LIST_NO_COMPARE_FUNCTION,
} return_code_t;

#endif  // INCLUDE_RETURN_CODES_H_
