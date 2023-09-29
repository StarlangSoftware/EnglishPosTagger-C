//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#ifndef POSTAGGER_DUMMYPOSTAGGER_H
#define POSTAGGER_DUMMYPOSTAGGER_H

#include <Sentence.h>
#include "PosTaggedCorpus.h"

void* train_dummy_pos_tagger(Pos_tagged_corpus_ptr corpus);

Sentence_ptr pos_tag_dummy(Sentence_ptr sentence, void* model);

#endif //POSTAGGER_DUMMYPOSTAGGER_H
