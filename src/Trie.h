#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include "Exception.h"

template <class Key, class Pointer>
class PointerContainer
{
public:
    PointerContainer() {}
    virtual ~PointerContainer() {}
    virtual Pointer* get(const Key& key) const = 0;
    virtual void insert(const Key& key, Pointer* pointer) = 0;
    virtual const size_t size() const = 0;
    virtual Pointer* at(size_t n) = 0;
    virtual void begin() = 0;
    virtual Pointer* next() = 0;
    static const unsigned int null_ptr = 0;
};

namespace TrieTree {

template <class T, class F = unsigned long>
class Filter {
public:
    virtual bool filter(T t, F k) = 0;
    virtual ~Filter() {}
};

template <class T, class F = unsigned long>
class NoFilter : public Filter<T,F> {
public:
    virtual bool filter(T t, F f) { return false; }
    virtual ~NoFilter() {}
};

enum NodeType {
    VectorNode,
    MapNode
};

template <class T, class F = unsigned long>
class Trie
{
private:
    struct Node;

    class VectorContainer : public PointerContainer<char, Node> {
        typedef std::vector<Node*> vector;
        typedef typename vector::iterator iterator;
        typedef typename vector::size_type size_type;
        vector m_v;
        iterator m_it;

        struct Deleter { void operator()(Node* node) {
                delete node;
        }};
    public:
        ~VectorContainer() {
            std::for_each(m_v.begin(), 
                          m_v.end(), 
                          Deleter());
        }
        Node* get(const char& key) const {
            for ( size_t i = 0; i < m_v.size(); i++ ) {
                Node* child = m_v.at(i);
                if ( child->m_key == key ) {
                    return child;
                }
            }
            return NULL;
        }
        void insert(const char& key, Node* node) {
            m_v.push_back(node);
        }
        const size_type size() const { return m_v.size(); }
        Node* at(size_type n) { return m_v.at(n); }

        void begin() { m_it = m_v.begin(); }
        Node* next() {
            return *m_it++;
        }
    };

    class MapContainer : public PointerContainer<char, Node> {
        typedef std::map<char, Node*> map;
        typedef typename map::iterator iterator;
        typedef typename map::const_iterator const_iterator;
        typedef typename map::value_type value_type;
        typedef typename map::size_type size_type;
        map m_map;
        iterator m_it;

        struct Deleter { void operator()(value_type& instance) {
                delete instance.second;
        }};
    public:
        ~MapContainer() {
            std::for_each(m_map.begin(),
                          m_map.end(),
                          Deleter());
        }
        Node* get(const char& key) const {
            const_iterator it = m_map.find(key);
            if (it != m_map.end()) {
                return it->second;
            }
            return NULL;
        }
        void insert(const char& key, Node* node) {
            m_map.insert(std::pair<char,Node*>(key,node));
        }
        const size_type size() const { return m_map.size(); }
        Node* at(size_type n) { return m_map.at(n); } 

        void begin() { m_it = m_map.begin(); }
        Node* next() {
            return m_it++->second;
        }
    };

    struct Node 
    {
        Node * m_parent;
        Filter<T, F> *m_filter;
        NodeType m_type ;
        PointerContainer<char, Node>* m_children;
        std::string m_content;
        T m_value;
        char m_key;

        Node(char c, Node* parent, class Filter<T, F>* filter, NodeType type=VectorNode) : 
            m_key(c),
            m_parent(parent),
            m_filter(filter),
            m_type(type) {
            if (m_type == VectorNode)
                useVector();
            else
                useMap();
        }
        ~Node() {
            delete m_children;
        }

        void useVector() {
            m_children = new VectorContainer;
        }
        void useMap() {
            m_children = new MapContainer;
        }

        Node* addNode(const char c) {
            Node* child = new Node(c,this,m_filter,m_type);
            m_children->insert(c,child);
            return child;
        }

        const T getValue(const F& filterKey) const {
            if (m_content.size() == 0) {
                if (m_parent == NULL) {
                    return NULL;
                }
                return m_parent->getValue(filterKey);
            }
            if (m_filter->filter(m_value, filterKey)) {
                if (m_parent == NULL) {
                    return NULL;
                }
                return m_parent->getValue(filterKey);
            } else {
                return m_value;
            }
        }

        Node* getChildNode(const char c) {
            return m_children->get(c);
        }


        void print(std::map<unsigned int,unsigned int>& m, unsigned int lvl=0) const {
            for (unsigned int j=0; j<lvl; j++ ) {
                char c = m[j]>0?'|':' ';
                std::cout << c <<" ";
            }
            std::cout << "\033[1;32m" << m_key << "\033[0m";
            if (m_content.length())
                std::cout << "\033[1;31m ---" << m_value << "\033[0m";
            std::cout << std::endl;

            lvl++;
            m_children->begin();
            m[lvl] = m_children->size();
            for (size_t i = 0; i < m_children->size(); i++ ) {
                m[lvl]--;
                m_children->next()->print(m, lvl);
            }
        }

    };

private:

    Filter<T, F> *m_filter;
    Node* m_root;
public:
    Trie() {
        m_filter = new NoFilter<T, F>;
        m_root = new Node(0,NULL,m_filter,MapNode);
    }
    Trie(NodeType type) {
        m_filter = new NoFilter<T, F>;
        m_root = new Node(0,NULL,m_filter,type);
    }
    Trie(class Filter<T, F>* filter) {
        m_filter = filter;
        m_root = new Node(0,NULL,m_filter,MapNode);
    }
    Trie(NodeType type, class Filter<T, F>* filter) {
        m_filter = filter;
        m_root = new Node(0,NULL,m_filter,type);
    }
    ~Trie() {
        delete m_root;
        delete m_filter;
    }

    void insert(const std::string& key, const T& value, bool rejectDuplicate=false) {
        Node* cur = m_root;
        for (size_t i=0; i<key.length(); i++) {
            Node* child = cur->getChildNode(key[i]);
            if (!child) {
                child = cur->addNode(key[i]);
            }
            cur = child;
        }
        if (rejectDuplicate && cur->m_content.size() != 0) {
            throw DuplicateRecordException(std::string("Duplicate record '") + key);
        }
        cur->m_content = key;
        cur->m_value = value;
    }

    const T get(const std::string& key) const {
        Node* cur = m_root;
        Node* last = NULL;
        for ( size_t i=0; i<key.length(); i++ ) {
            Node* child = cur->getChildNode(key[i]);
            if (!child) {
                if (!cur->m_content.length()) {
                    if (!last) {
                        throw KeyNotFoundException(std::string("No match found for '") + key + "'");
                    }
                    cur = last;
                }
                return cur->m_value;
            }
            cur = child;
            if (cur->m_content.length()) {
                last = cur;
            }
        }

        if (cur->m_content.length()) {
            return cur->m_value;
        }
        throw KeyNotFoundException(std::string("No match found for '") + key + "'");
    }

    const T get(const std::string& key, const F& filterKey) const {
        Node* cur = m_root;
        Node* last = NULL;
        for ( size_t i=0; i<key.length(); i++ ) {
            Node* child = cur->getChildNode(key[i]);
            if (!child) {
                if (!cur->m_content.length()) {
                    if (!last) {
                        throw KeyNotFoundException(std::string("No match found for '") + key + "'");
                    }
                    cur = last;
                }

                T t = cur->getValue(filterKey);
                if (t != NULL) {
                    return t;
                }
                throw KeyNotFoundException(std::string("No match found for '") + key + "'");
            }
            cur = child;
            if (cur->m_content.length()) {
                last = cur;
            }
        }

        T t = cur->getValue(filterKey);
        if (t != NULL) {
            return t;
        }
        throw KeyNotFoundException(std::string("No match found for '") + key + "'");
    }

    void print () const {
        std::cout << "Trie Tree :" ;
        std::map<unsigned int,unsigned int> m;
        m_root->print(m);
    }
};


}; //namespace
