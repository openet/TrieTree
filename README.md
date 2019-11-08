## Building
Compile the project. 
```bash
cmake .
make
```

## Unit Test
Execute google unit test.
```bash
./gtest/runUnitTests
```

## Usage

### Initialise
In this example we initialise TrieTree::Trie with template <T = std::string>
```bash
TrieTree::Trie<std::string>* trie = new TrieTree::Trie<std::string>();
```

### Insert elements
Insert several number prefix as keys, country name as values into the trie container.
```bash
trie->insert("60", "Malaysia");
trie->insert("603", "Kuala Lumpur");
trie->insert("6012", "Maxis Mobile");
trie->insert("65", "Singapore");
trie->insert("44", "United Kingdom");
trie->insert("1300", "Hotline");
trie->insert("123", "Free");
```

### Examine the trie tree
We can examine the trie tree data structure by calling print().
```bash
trie->print();
```
The entire tree including each nodes will be output into std::cout 
###### output:
```bash
  1
  | 2
  | | 3 ---Free
  | 3
  |   0
  |     0 ---Hotline
  4
  | 4 ---United Kingdom
  6
    0 ---Malaysia
    | 1
    | | 2 ---Maxis Mobile
    | 3 ---Kuala Lumpur
    5 ---Singapore
```

### Query
Finally we can perform best-match looking by calling get() with a full number.
```bash
std::cout << trie->get("60122250110") << std::endl;
std::cout << trie->get("60377811234") << std::endl;
std::cout << trie->get("65334556123") << std::endl;
std::cout << trie->get("1300882525")  << std::endl;
```

###### output:
```bash
Maxis Mobile
Kuala Lumpur
Singapore
Hotline
```

