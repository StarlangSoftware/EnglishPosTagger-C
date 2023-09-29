//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include <Corpus.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "../src/PosTaggedCorpus.h"
#include "../src/DummyPosTagger.h"

int main(){
    Pos_tagged_corpus_ptr pos_tagged_corpus = create_pos_tagged_corpus("brown.txt");
    Array_list_ptr model = train_dummy_pos_tagger(pos_tagged_corpus);
    double correct = 0, incorrect = 0;
    for (int i = 0; i < pos_tagged_corpus->sentences->size; i++){
        Sentence_ptr sentence = corpus_get_sentence3(pos_tagged_corpus, i);
        Sentence_ptr tagged_sentence = pos_tag_dummy(sentence, model);
        for (int j = 0; j < sentence_word_count(sentence); j++){
            Pos_tagged_word_ptr real = array_list_get(sentence->words, j);
            Pos_tagged_word_ptr predicted = array_list_get(tagged_sentence->words, j);
            if (strcmp(real->tag, predicted->tag) == 0){
                correct++;
            } else {
                incorrect++;
            }
        }
        free_sentence(tagged_sentence);
    }
    free_pos_tagged_corpus(pos_tagged_corpus);
    free_array_list(model, free);
    if (fabs(100 * correct / (correct + incorrect) - 0.94) > 0.01){
        printf("Error %.6lf", 100 * correct / (correct + incorrect));
    }
}