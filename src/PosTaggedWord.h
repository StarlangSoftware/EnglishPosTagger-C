//
// Created by Olcay Taner YILDIZ on 27.09.2023.
//

#ifndef POSTAGGER_POSTAGGEDWORD_H
#define POSTAGGER_POSTAGGEDWORD_H

struct pos_tagged_word{
    char* name;
    char* tag;
};

typedef struct pos_tagged_word Pos_tagged_word;

typedef Pos_tagged_word *Pos_tagged_word_ptr;

Pos_tagged_word_ptr create_pos_tagged_word(const char* name, const char* tag);

void free_pos_tagged_word(Pos_tagged_word_ptr pos_tagged_word);

#endif //POSTAGGER_POSTAGGEDWORD_H
