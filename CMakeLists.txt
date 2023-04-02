cmake_minimum_required(VERSION 3.23)
project(IDSH C)

set(CMAKE_C_STANDARD 23)

add_executable(IDSH main.c DataStructers/vector.h shellprinting.h DataStructers/linkedList.h DataStructers/trie.h shellCore.h DataStructers/str.h DataStructers/iter.h tokenizer.h)
