#include <gtest/gtest.h>

#include <memory>
#include "Trie.h"

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

    EXPECT_EQ(trie->get("60122250110"), "Maxis Mobile");
    EXPECT_EQ(trie->get("60377811234"), "Kuala Lumpur");
    EXPECT_EQ(trie->get("65334556123"), "Singapore");
    EXPECT_EQ(trie->get("1300882525"), "Hotline");
}
