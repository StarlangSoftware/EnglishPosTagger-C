cmake_minimum_required(VERSION 3.23)
project(PosTagger)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(corpus_c REQUIRED)
find_package(hmm_c REQUIRED)

add_library(PosTagger PosTaggedWord.c PosTaggedWord.h PosTaggedCorpus.c PosTaggedCorpus.h DummyPosTagger.c DummyPosTagger.h NaivePosTagger.c NaivePosTagger.h HmmPosTagger.c HmmPosTagger.h)
target_link_libraries(PosTagger corpus_c::corpus_c hmm_c::hmm_c)
