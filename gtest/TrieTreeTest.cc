#include <gtest/gtest.h>

#include <memory>
#include "../src/Trie.h"

using namespace TrieTree;

struct TrieTreeTest : ::testing::Test {
       
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

};

TEST_F(TrieTreeTest, SimpleTest) 
{
    TrieTree::Trie<std::string>* trie = new TrieTree::Trie<std::string>();
    trie->insert("60", "Malaysia");
    trie->insert("603", "Kuala Lumpur");
    trie->insert("6012", "Maxis Mobile");
    trie->insert("65", "Singapore");
    trie->insert("44", "United Kingdom");
    trie->insert("1300", "Hotline");
    trie->insert("123", "Free");

    trie->print();

    std::cout << trie->get("60122250110") << std::endl;  
    std::cout << trie->get("60377811234") << std::endl; 
    std::cout << trie->get("65334556123") << std::endl; 
    std::cout << trie->get("1300882525")  << std::endl; 
}
