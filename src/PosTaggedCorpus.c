//
// Created by Olcay Taner YILDIZ on 27.09.2023.
//

#include <FileUtils.h>
#include <string.h>
#include <StringUtils.h>
#include <Sentence.h>
#include <Memory/Memory.h>
#include "PosTaggedCorpus.h"
#include "PosTaggedWord.h"

/**
 * Another constructor of PosTaggedCorpus which takes a fileName of the corpus as an input, reads the
 * corpus from that file.
 *
 * @param fileName Name of the corpus file.
 */
Pos_tagged_corpus_ptr create_pos_tagged_corpus(const char *file_name) {
    Sentence_ptr new_sentence = create_sentence();
    Pos_tagged_corpus_ptr result = create_pos_tagged_corpus2();
    Array_list_ptr lines = read_lines(file_name);
    for (int j = 0; j < lines->size; j++){
        char* line = array_list_get(lines, j);
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
                            free_array_list(short_tag_list2, free_);
                        } else {
                            short_tag = str_copy(short_tag, candidate);
                        }
                        free_array_list(short_tag_list, free_);
                    } else {
                        if (strchr(tag, '+') != NULL){
                            Array_list_ptr short_tag_list = str_split(tag, '+');
                            short_tag = str_copy(short_tag, array_list_get(short_tag_list, 0));
                            free_array_list(short_tag_list, free_);
                        } else {
                            short_tag = str_copy(short_tag, tag);
                        }
                    }
                    put_counter_hash_map(result->tag_list, short_tag);
                    Pos_tagged_word_ptr new_word = create_pos_tagged_word(name, short_tag);
                    if (count_counter_hash_map(result->tag_list, short_tag) > 1){
                        free_(short_tag);
                    }
                    sentence_add_word2(new_sentence, new_word);
                    if (strcmp(tag, ".") == 0){
                        corpus_add_sentence2(result, new_sentence);
                        new_sentence = create_sentence();
                    }
                }
                free_array_list(items, free_);
            }
        }
        free_array_list(tokens, free_);
    }
    free_array_list(lines, free_);
    if (sentence_word_count(new_sentence) > 0){
        corpus_add_sentence2(result, new_sentence);
    } else {
        free_sentence(new_sentence);
    }
    return result;
}

/**
 * A constructor of PosTaggedCorpus which initializes the sentences of the corpus, the word list of
 * the corpus, and all possible tags.
 */
Pos_tagged_corpus_ptr create_pos_tagged_corpus2() {
    Pos_tagged_corpus_ptr result = malloc_(sizeof(Pos_tagged_corpus), "create_pos_tagged_corpus2");
    result->sentences = create_array_list();
    result->word_list = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                (int (*)(const void *, const void *)) compare_string);
    result->tag_list = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                               (int (*)(const void *, const void *)) compare_string);
    return result;
}

/**
 * Adds a new sentence to pos tagged corpus.
 * @param corpus Pos tagged corpus to add a sentence.
 * @param sentence Sentence to add.
 */
void corpus_add_sentence2(Pos_tagged_corpus_ptr corpus, Sentence_ptr sentence) {
    array_list_add(corpus->sentences, sentence);
    for (int i = 0; i < sentence->words->size; i++) {
        Pos_tagged_word_ptr pos_tagged_word = array_list_get(sentence->words, i);
        put_counter_hash_map(corpus->word_list, pos_tagged_word->name);
    }
}

/**
 * Adds a new word to a sentence
 * @param sentence Sentence to which a new word will be added
 * @param word Word to be added
 */
void sentence_add_word2(Sentence_ptr sentence, Pos_tagged_word_ptr word) {
    array_list_add(sentence->words, word);
}

/**
 * Returns the pos tag list used for tagging.
 * @param corpus Corpus from which tag list was created.
 * @return Pos tag list used to tag the words in the corpus
 */
Array_list_ptr get_tag_list(Pos_tagged_corpus_ptr corpus) {
    return key_list(corpus->tag_list->map);
}

/**
 * Returns the sentence at position index in the given corpus
 * @param corpus Corpus
 * @param index Position of the sentence
 * @return Sentence at position index in the given corpus
 */
Sentence_ptr corpus_get_sentence3(Pos_tagged_corpus_ptr corpus, int index) {
    return array_list_get(corpus->sentences, index);
}

/**
 * Frees memory allocated for the corpus. Deallocates memory for sentences array list, word_list and tag_list
 * hash maps.
 * @param corpus Corpus to be deallocated.
 */
void free_pos_tagged_corpus(Pos_tagged_corpus_ptr corpus) {
    free_array_list(corpus->sentences, (void (*)(void *)) free_pos_tagged_sentence);
    free_counter_hash_map(corpus->word_list);
    free_counter_hash_map2(corpus->tag_list, free_);
    free_(corpus);
}

/**
 * Returns the pos tagged words in the given sentence.
 * @param sentence Sentence containing the pos tagged words.
 * @return Array list of pos tagged words in the sentence.
 */
Array_list_ptr get_word_list2(Sentence_ptr sentence) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < sentence->words->size; i++){
        Pos_tagged_word_ptr word = array_list_get(sentence->words, i);
        array_list_add(result, word->name);
    }
    return result;
}

/**
 * Frees memory allocated for the sentence. Deallocates memory for words list.
 * @param sentence Sentence to be deallocated.
 */
void free_pos_tagged_sentence(Sentence_ptr sentence) {
    free_array_list(sentence->words, (void (*)(void *)) free_pos_tagged_word);
    free_(sentence);
}
