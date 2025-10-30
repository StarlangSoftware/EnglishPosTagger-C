//
// Created by Olcay Taner YILDIZ on 29.09.2023.
//

#include <string.h>
#include "../src/PosTaggedCorpus.h"
#include "../src/NaivePosTagger.h"
#include "Memory/Memory.h"

int main(){
    start_large_memory_check();
    Pos_tagged_corpus_ptr pos_tagged_corpus = create_pos_tagged_corpus("brown.txt");
    Hash_map_ptr model = train_naive_pos_tagger(pos_tagged_corpus);
    double correct = 0, incorrect = 0;
    for (int i = 0; i < pos_tagged_corpus->sentences->size; i++){
        Sentence_ptr sentence = corpus_get_sentence3(pos_tagged_corpus, i);
        Sentence_ptr tagged_sentence = pos_tag_naive(sentence, model);
        for (int j = 0; j < sentence_word_count(sentence); j++){
            Pos_tagged_word_ptr real = array_list_get(sentence->words, j);
            Pos_tagged_word_ptr predicted = array_list_get(tagged_sentence->words, j);
            if (strcmp(real->tag, predicted->tag) == 0){
                correct++;
            } else {
                incorrect++;
            }
        }
        free_pos_tagged_sentence(tagged_sentence);
    }
    printf("Accuracy: %.6lf", 100 * correct / (correct + incorrect));
    free_pos_tagged_corpus(pos_tagged_corpus);
    free_hash_map2(model, free_, free_);
    end_memory_check();
}