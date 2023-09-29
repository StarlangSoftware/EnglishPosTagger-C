//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include <stdlib.h>
#include <Hmm1.h>
#include "HmmPosTagger.h"

/**
 * Train method for the Hmm pos tagger. The algorithm trains an Hmm from the corpus, where corpus constitutes
 * as an observation array.
 *
 * @param corpus Traning data for the tagger.
 */
void *train_hmm_pos_tagger(Pos_tagged_corpus_ptr corpus) {
    int sentence_count = corpus->sentences->size;
    Array_list_ptr* emitted_symbols = malloc(sentence_count * sizeof(Array_list_ptr));
    Array_list_ptr* all_words = malloc(sentence_count * sizeof(Array_list_ptr));
    for (int i = 0; i < sentence_count; i++){
        emitted_symbols[i] = create_array_list();
        all_words[i] = create_array_list();
        Sentence_ptr sentence = array_list_get(corpus->sentences, i);
        for (int j = 0; j < sentence->words->size; j++){
            Pos_tagged_word_ptr word = array_list_get(sentence->words, j);
            array_list_add(all_words[i], word->name);
            array_list_add(emitted_symbols[i], word->tag);
        }
    }
    return create_hmm1(create_hash_set_of_string2(get_tag_list(corpus)),
                               sentence_count,
                               emitted_symbols,
                               all_words,
                               (unsigned int (*)(const void *, int)) hash_function_string,
                               (int (*)(const void *, const void *)) compare_string,
                               (unsigned int (*)(const void *, int)) hash_function_string,
                               (int (*)(const void *, const void *)) compare_string);
}

/**
 * Test method for the Hmm pos tagger. For each sentence, the method uses the viterbi algorithm to produce the
 * most possible state sequence for the given sentence.
 *
 * @param sentence Sentence to be tagged.
 * @return Annotated (tagged) sentence.
 */
Sentence_ptr pos_tag_hmm(Sentence_ptr sentence, void *model) {
    Hmm1_ptr hmm = model;
    Array_list_ptr tag_list = viterbi_hmm1(hmm, get_word_list2(sentence));
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence_word_count(sentence); i++){
        char* name = sentence_get_word(sentence, i)->name;
        char* tag = array_list_get(tag_list, i);
        sentence_add_word2(result, create_pos_tagged_word(name, tag));
    }
    free_array_list(tag_list, NULL);
    return result;
}
