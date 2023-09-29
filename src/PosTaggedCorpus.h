//
// Created by Olcay Taner YILDIZ on 27.09.2023.
//

#ifndef POSTAGGER_POSTAGGEDCORPUS_H
#define POSTAGGER_POSTAGGEDCORPUS_H

#include <ArrayList.h>
#include <CounterHashMap.h>
#include <HashMap/HashSet.h>
#include <Sentence.h>
#include "PosTaggedWord.h"

struct pos_tagged_corpus{
    Array_list_ptr sentences;
    Counter_hash_map_ptr word_list;
    Counter_hash_map_ptr tag_list;
};

typedef struct pos_tagged_corpus Pos_tagged_corpus;

typedef Pos_tagged_corpus *Pos_tagged_corpus_ptr;

Pos_tagged_corpus_ptr create_pos_tagged_corpus(const char* file_name);

Pos_tagged_corpus_ptr create_pos_tagged_corpus2();

void free_pos_tagged_corpus(Pos_tagged_corpus_ptr corpus);

void sentence_add_word2(Sentence_ptr sentence, Pos_tagged_word_ptr word);

void corpus_add_sentence2(Pos_tagged_corpus_ptr corpus, Sentence_ptr sentence);

Array_list_ptr get_tag_list(Pos_tagged_corpus_ptr corpus);

Sentence_ptr corpus_get_sentence3(Pos_tagged_corpus_ptr corpus, int index);

Array_list_ptr get_word_list2(Sentence_ptr sentence);

#endif //POSTAGGER_POSTAGGEDCORPUS_H
