//
// Created by Olcay Taner YILDIZ on 27.09.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include <StringUtils.h>
#include <Sentence.h>
#include "PosTaggedCorpus.h"
#include "PosTaggedWord.h"

/**
 * Another constructor of PosTaggedCorpus which takes a fileName of the corpus as an input, reads the
 * corpus from that file.
 *
 * @param fileName Name of the corpus file.
 */
Pos_tagged_corpus_ptr create_pos_tagged_corpus(const char *file_name) {
    char line[MAX_LINE_LENGTH];
    Sentence_ptr new_sentence = create_sentence();
    Pos_tagged_corpus_ptr result = create_pos_tagged_corpus2();
    FILE* input_file;
    input_file = fopen(file_name, "r");
    char* input = fgets(line, MAX_LINE_LENGTH, input_file);
    while (input != NULL){
        line[strcspn(line, "\n")] = 0;
        Array_list_ptr tokens = str_split(left_trim(line), ' ');
        for (int i = 0; i < tokens->size; i++){
            char* word = array_list_get(tokens, i);
            if (strlen(word) > 0 && strchr(word, '/') != NULL){
                Array_list_ptr items = str_split(word, '/');
                if (items->size == 2){
                    char* name = array_list_get(items, 0);
                    char* tag = array_list_get(items, 1);
                    char* short_tag = NULL;
                    if (strchr(tag, '-') != NULL && strcmp(tag, "--") != 0){
                        Array_list_ptr short_tag_list = str_split(tag, '-');
                        char* candidate = array_list_get(short_tag_list, 0);
                        if (strchr(candidate, '+') != NULL){
                            Array_list_ptr short_tag_list2 = str_split(candidate, '+');
                            short_tag = str_copy(short_tag, array_list_get(short_tag_list2, 0));
                        } else {
                            short_tag = str_copy(short_tag, candidate);
                        }
                        free_array_list(short_tag_list, free);
                    } else {
                        if (strchr(tag, '+') != NULL){
                            Array_list_ptr short_tag_list = str_split(tag, '+');
                            short_tag = str_copy(short_tag, array_list_get(short_tag_list, 0));
                            free_array_list(short_tag_list, free);
                        } else {
                            short_tag = str_copy(short_tag, tag);
                        }
                    }
                    put_counter_hash_map(result->tag_list, short_tag);
                    Pos_tagged_word_ptr new_word = create_pos_tagged_word(name, short_tag);
                    sentence_add_word2(new_sentence, new_word);
                    if (strcmp(tag, ".") == 0){
                        corpus_add_sentence2(result, new_sentence);
                        new_sentence = create_sentence();
                    }
                }
                free_array_list(items, free);
            }
        }
        free_array_list(tokens, free);
        input = fgets(line, MAX_LINE_LENGTH, input_file);
    }
    if (sentence_word_count(new_sentence) > 0){
        corpus_add_sentence2(result, new_sentence);
    }
    return result;
}

/**
 * A constructor of PosTaggedCorpus which initializes the sentences of the corpus, the word list of
 * the corpus, and all possible tags.
 */
Pos_tagged_corpus_ptr create_pos_tagged_corpus2() {
    Pos_tagged_corpus_ptr result = malloc(sizeof(Pos_tagged_corpus));
    result->sentences = create_array_list();
    result->word_list = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                (int (*)(const void *, const void *)) compare_string);
    result->tag_list = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                               (int (*)(const void *, const void *)) compare_string);
    return result;
}

void corpus_add_sentence2(Pos_tagged_corpus_ptr corpus, Sentence_ptr sentence) {
    array_list_add(corpus->sentences, sentence);
    for (int i = 0; i < sentence->words->size; i++) {
        Pos_tagged_word_ptr pos_tagged_word = array_list_get(sentence->words, i);
        put_counter_hash_map(corpus->word_list, pos_tagged_word->name);
    }
}

void sentence_add_word2(Sentence_ptr sentence, Pos_tagged_word_ptr word) {
    array_list_add(sentence->words, word);
}

Array_list_ptr get_tag_list(Pos_tagged_corpus_ptr corpus) {
    return key_list(corpus->tag_list->map);
}

Sentence_ptr corpus_get_sentence3(Pos_tagged_corpus_ptr corpus, int index) {
    return array_list_get(corpus->sentences, index);
}

void free_pos_tagged_corpus(Pos_tagged_corpus_ptr corpus) {
    free_array_list(corpus->sentences, (void (*)(void *)) free_sentence);
    free_counter_hash_map(corpus->word_list);
    free_counter_hash_map(corpus->tag_list);
    free(corpus);
}

Array_list_ptr get_word_list2(Sentence_ptr sentence) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < sentence->words->size; i++){
        Pos_tagged_word_ptr word = array_list_get(sentence->words, i);
        array_list_add(result, word->name);
    }
    return result;
}
