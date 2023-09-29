//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#ifndef POSTAGGER_HMMPOSTAGGER_H
#define POSTAGGER_HMMPOSTAGGER_H

#include <Sentence.h>
#include "PosTaggedCorpus.h"

void* train_hmm_pos_tagger(Pos_tagged_corpus_ptr corpus);

Sentence_ptr pos_tag_hmm(Sentence_ptr sentence, void* model);

#endif //POSTAGGER_HMMPOSTAGGER_H
