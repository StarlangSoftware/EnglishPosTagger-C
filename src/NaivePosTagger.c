//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include "NaivePosTagger.h"

/**
 * Train method for the Naive pos tagger. The algorithm gets all possible tag list. Then counts all
 * possible tags (with its counts) for each possible word.
 *
 * @param corpus Training data for the tagger.
 */
void *train_naive_pos_tagger(Pos_tagged_corpus_ptr corpus) {
    Counter_hash_map_ptr counter_hash_map;
    Hash_map_ptr max_map = create_string_hash_map();
    Hash_map_ptr map = create_string_hash_map();
    for (int i = 0; i < corpus->sentences->size; i++){
        Sentence_ptr s = array_list_get(corpus->sentences, i);
        for (int j = 0; j < sentence_word_count(s); j++){
            Pos_tagged_word_ptr word = array_list_get(s->words, j);
            if (hash_map_contains(map, word->name)){
                counter_hash_map = hash_map_get(map, word->name);
                put_counter_hash_map(counter_hash_map, word->tag);
            } else {
                counter_hash_map = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                           (int (*)(const void *, const void *)) compare_string);
                put_counter_hash_map(counter_hash_map, word->tag);
                hash_map_insert(map, word->name, counter_hash_map);
            }
        }
    }
    Array_list_ptr list = key_list(map);
    for (int i = 0; i < list->size; i++){
        char* name = array_list_get(list, i);
        counter_hash_map = hash_map_get(map, name);
        char* tag = max_counter_hash_map(counter_hash_map);
        hash_map_insert(max_map, name, tag);
    }
    free_array_list(list, NULL);
    free_hash_map(map, (void (*)(void *)) free_counter_hash_map);
    return max_map;
}

/**
 * Test method for the Naive pos tagger. For each word, the method chooses the maximum a posterior tag from all
 * possible tag list for that word.
 *
 * @param sentence Sentence to be tagged.
 * @return Annotated (tagged) sentence.
 */
Sentence_ptr pos_tag_naive(Sentence_ptr sentence, void *model) {
    Hash_map_ptr max_map = model;
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence_word_count(sentence); i++){
        char* name = sentence_get_word(sentence, i);
        char* tag = hash_map_get(max_map, name);
        sentence_add_word2(result, create_pos_tagged_word(name, tag));
    }
    return result;
}
