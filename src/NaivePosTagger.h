//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#ifndef POSTAGGER_NAIVEPOSTAGGER_H
#define POSTAGGER_NAIVEPOSTAGGER_H

#include <Sentence.h>
#include "PosTaggedCorpus.h"

void* train_naive_pos_tagger(Pos_tagged_corpus_ptr corpus);

Sentence_ptr pos_tag_naive(Sentence_ptr sentence, void* model);

#endif //POSTAGGER_NAIVEPOSTAGGER_H
