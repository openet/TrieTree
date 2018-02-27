#include <gtest/gtest.h>

#include <memory>
#include "Trie.h"

using namespace TrieTree;

struct TrieTreeTest : ::testing::Test {
       
    TrieTree::Trie<std::string>* m_trie;

    virtual void SetUp() {
        m_trie = new TrieTree::Trie<std::string>(TrieTree::VectorNode);
    }

    virtual void TearDown() {
        delete m_trie;
    }

    void insert(const std::string& s, const std::string& s2) {
        m_trie->insert(s,s+" "+s2);
    }

};

TEST_F(TrieTreeTest, Test01) 
{
    insert("60", "Malaysia");
    insert("603", "Kuala Lumpur");
    insert("6012", "Maxis Mobile");
    insert("65", "Singapore");
    insert("44", "United Kingdom");
    insert("1300", "Hotline");
    insert("123", "Free");

    m_trie->print();

    EXPECT_STREQ(m_trie->get("60122250110").c_str(),"6012 Maxis Mobile");
    EXPECT_STREQ(m_trie->get("60377811234").c_str(),"603 Kuala Lumpur");
    EXPECT_STREQ(m_trie->get("65334556123").c_str(),"65 Singapore");
    EXPECT_STREQ(m_trie->get("1300882525").c_str(),"1300 Hotline");
}

TEST_F(TrieTreeTest, Test02) 
{
    std::cout << " test 02 " << std::endl;

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
