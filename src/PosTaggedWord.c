//
// Created by Olcay Taner YILDIZ on 27.09.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include "PosTaggedWord.h"

/**
 * A constructor of {@link PosTaggedWord} which takes name and tag as input and sets the corresponding attributes
 * @param name Name of the word
 * @param tag Tag of the word
 */
Pos_tagged_word_ptr create_pos_tagged_word(char *name, char *tag) {
    Pos_tagged_word_ptr result = malloc(sizeof(Pos_tagged_word));
    result->name = str_copy(result->name, name);
    result->tag = str_copy(result->tag, tag);
    return result;
}

void free_pos_tagged_word(Pos_tagged_word_ptr pos_tagged_word) {
    free(pos_tagged_word->name);
    free(pos_tagged_word->tag);
    free(pos_tagged_word);
}
