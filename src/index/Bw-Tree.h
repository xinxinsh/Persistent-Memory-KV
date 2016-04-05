
//  An Simple Implementation of Bw-Tree with Intel NVM Library, please refer to 
//    http://pmem.io/ 
//    http://www.msr-waypoint.com/pubs/178758/bw-tree-icde2013-final.pdf 
//  for more details

#ifndef PROJECT_BWTREE_H_
#define PROJECT_BWTREE_H_

#include <vector>
#include <string>

#include <libpmemobj.h>

namespace BwTree {

// Bw-Tree has two types nodes : base node and delta node, base nodes contain a set of 
// key-value pairs and delta nodes contain updates to base nodes
template <KeyType, ValueType, KeyComparator> class BwTree {
  typedef uint64_t pid;
  enum NodeType {
    InnerNode = 0,
    LeafNode,
    DeltaInsert,
    DeltaUpdate,
    DeltaDelete,
    DeltaSplit,
    DeltaSplitIndex,
    DeltaMergeRemove,
    DeltaMerge,
    DeltaMergeIndex,
  };

  // base class of node 
  class Node {  
   public:
    void Node(const NodeType& type)
      : type(type) {}
    virtual ~Node() {}
    virtual set_type(const NodeType& type) {
      type = type;
    }
    virtual const NodeType get_type {
      return type;
    }
   private:
    NodeType type;
  }

  class Delta : public Node {
   public:
    Node* get_next() {return next;}
    uint64_t get_num_entries() {return num_entries;}
   private:
    Node* next;
    uint64_t num_entries;
  }

  // leaf node
  class LeafNode : public Node {
   public:
    void LeafNode(KeyType* min_key, KeyType* max_key, pid* previous, pid* next, uint8_t num_entries);
    virtual ~LeafNode();
   private:
    KeyType min_key;
    KeyType max_key;
    KeyType* keys;
    ValueType* values;
    pid* next;
    pid* previous;
    uint8_t num_entries;
  }

  // inner node
  class InnerNode : public Node {
   public:
    void InnerNode(KeyType* min_key, KeyType* max_key, pid* previous, pid* next, uint8_t num_entries);
    virtual ~InnerNode();
   private:
    KeyType* min_key;
    KeyType* max_key;
    KeyType* keys;
    pid* pages;
    uint8_t num_entries;
  }

  // delta insert node
  class DeltaInsert : public Delta {
   public:
    void DeltaInsert(KeyType* key, ValueType* value, uint8_t num_entries);
    virtual ~DeltaInsert();
   private:
    KeyType* key;
    ValueType* value;
  }

  // delta update node
  class DeltaUpdate : public Delta {
   public:
    void DeltaUpdate(KeyType* key, ValueType* value, uint8_t num_entries);
    virtual ~DeltaUpdate();
   private:
    KeyType* key;
    ValueType* Value;
  }

  // delta delete node
  class DeltaDelete : public Delta {
   public:
    void DeltaDelete(KeyType* key, ValueType* value, uint8_t num_entries);
    virtual ~DeltaDelete();
   private:
    KeyType* key;
    ValueType* value;
  }

  // delta split node
  class DeltaSplit : public Delta {
  }

  // delta split index node
  class DeltaSplitIndex : public Delta {
  }

  // delta merge remove node
  class DeltaMergeRemove : public Delta {
  }

  // delta merge node
  class DeltaMerge : public Delta {
  }

  // delta merge index node 
  class DeltaMergeIndex : public Delta {
  }
  void BwTree() {
    // TODO
  }
 private:
  const int max_chain_length = 10;
  pid current_pid;  
} // BwTree
} // namespace BwTree

#endif // PROJECT_BWTREE_H_

