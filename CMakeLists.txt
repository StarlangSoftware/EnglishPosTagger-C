cmake_minimum_required(VERSION 3.23)
project(PosTagger C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(PosTagger src/PosTaggedWord.c src/PosTaggedWord.h src/PosTaggedCorpus.c src/PosTaggedCorpus.h src/DummyPosTagger.c src/DummyPosTagger.h src/NaivePosTagger.c src/NaivePosTagger.h src/HmmPosTagger.c src/HmmPosTagger.h)
target_link_libraries(PosTagger ${CONAN_LIBS})
add_executable(DummyPosTaggerTest src/PosTaggedWord.c src/PosTaggedWord.h src/PosTaggedCorpus.c src/PosTaggedCorpus.h src/DummyPosTagger.c src/DummyPosTagger.h Test/DummyPosTaggerTest.c)
target_link_libraries(DummyPosTaggerTest ${CONAN_LIBS})
add_executable(NaiveTaggerTest src/PosTaggedWord.c src/PosTaggedWord.h src/PosTaggedCorpus.c src/PosTaggedCorpus.h src/DummyPosTagger.c src/DummyPosTagger.h src/NaivePosTagger.c src/NaivePosTagger.h Test/NaiveTaggerTest.c Test/NaiveTaggerTest.c)
target_link_libraries(NaiveTaggerTest ${CONAN_LIBS})
add_executable(HmmPosTaggerTest src/PosTaggedWord.c src/PosTaggedWord.h src/PosTaggedCorpus.c src/PosTaggedCorpus.h src/DummyPosTagger.c src/DummyPosTagger.h src/NaivePosTagger.c src/NaivePosTagger.h src/HmmPosTagger.c src/HmmPosTagger.h Test/HmmPosTaggerTest.c)
target_link_libraries(HmmPosTaggerTest ${CONAN_LIBS})
