//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include <Hmm1.h>
#include <Memory/Memory.h>
#include "HmmPosTagger.h"

/**
 * Train method for the Hmm pos tagger. The algorithm trains an Hmm from the corpus, where corpus constitutes
 * as an observation array.
 *
 * @param corpus Traning data for the tagger.
 */
void *train_hmm_pos_tagger(Pos_tagged_corpus_ptr corpus) {
    int sentence_count = corpus->sentences->size;
    Array_list_ptr* emitted_symbols = malloc_(sentence_count * sizeof(Array_list_ptr), "train_hmm_pos_tagger_1");
    Array_list_ptr* all_words = malloc_(sentence_count * sizeof(Array_list_ptr), "train_hmm_pos_tagger_2");
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
    Array_list_ptr tag_list = get_tag_list(corpus);
    Hash_set_ptr tag_set = create_hash_set_of_string2(tag_list);
    free_array_list(tag_list, NULL);
    Hmm1_ptr hmm = create_hmm1(tag_set,
                               sentence_count,
                               emitted_symbols,
                               all_words,
                               (unsigned int (*)(const void *, int)) hash_function_string,
                               (int (*)(const void *, const void *)) compare_string,
                               (void *(*)(void *)) clone_string,
                               (unsigned int (*)(const void *, int)) hash_function_string,
                               (int (*)(const void *, const void *)) compare_string,
                               (void *(*)(void *)) clone_string);
    free_hash_set(tag_set, NULL);
    for (int i = 0; i < sentence_count; i++){
        free_array_list(emitted_symbols[i], NULL);
        free_array_list(all_words[i], NULL);
    }
    free_(emitted_symbols);
    free_(all_words);
    return hmm;
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
    Array_list_ptr word_list = get_word_list2(sentence);
    Array_list_ptr tag_list = viterbi_hmm1(hmm, word_list);
    free_array_list(word_list, NULL);
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence_word_count(sentence); i++){
        Pos_tagged_word_ptr word = array_list_get(sentence->words, i);
        char* tag = array_list_get(tag_list, i);
        sentence_add_word2(result, create_pos_tagged_word(word->name, tag));
    }
    free_array_list(tag_list, NULL);
    return result;
}
