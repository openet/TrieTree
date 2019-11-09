cmake_minimum_required(VERSION 3.11)

project(trie_tree)

set(Source_Dir ${PROJECT_SOURCE_DIR}/src)

add_library(trie_trie ${Source_Dir}/Trie.cc)

add_subdirectory(gtest)
