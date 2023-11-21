//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include <stdlib.h>
#include "DummyPosTagger.h"

/**
 * Train method for the Dummy pos tagger. The algorithm gets all possible tag list.
 *
 * @param corpus Traning data for the tagger.
 */
void *train_dummy_pos_tagger(Pos_tagged_corpus_ptr corpus) {
    return get_tag_list(corpus);
}

/**
 * Test method for the Dummy pos tagger. For each word, the method chooses randomly a tag from all possible
 * tag list.
 *
 * @param sentence Sentence to be tagged.
 * @return Annotated (tagged) sentence.
 */
Sentence_ptr pos_tag_dummy(Sentence_ptr sentence, void* model) {
    srand(0);
    Array_list_ptr tag_list = (Array_list_ptr) model;
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence_word_count(sentence); i++){
        int index = random() % tag_list->size;
        char* tag = array_list_get(tag_list, index);
        sentence_add_word2(result, create_pos_tagged_word(sentence_get_word(sentence, i), tag));
    }
    return result;
}
