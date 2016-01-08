#ifndef SKIP_LIST_H
#define SKIP_LIST_H

template <typename keyType, typename valueType>
class SkipListNode
{
  template <typename T1, typename T2>
  friend class SkipList;
private:
  keyType key_;
  valueType value_;
  SkipListNode *prev_;
  SkipListNode *next_;
  SkipListNode *upperlayer_;
  SkipListNode *underlayer_;
  int height_;
  bool head_;
  void generateHeight();
public:
  SkipListNode();
  SkipListNode(const keyType &, const valueType &);
  SkipListNode(const SkipListNode<keyType, valueType> &);
  keyType key() const;
  valueType value() const;
  SkipListNode<keyType, valueType> * prev() const;
  void prev(SkipListNode<keyType, valueType> *);
  SkipListNode<keyType, valueType> * next() const;
  void next(SkipListNode<keyType, valueType> *);
  SkipListNode<keyType, valueType> * upperlayer() const;
  void upperlayer(SkipListNode<keyType, valueType> *);
  SkipListNode<keyType, valueType> * underlayer() const;
  void underlayer(SkipListNode<keyType, valueType> *);
  int height() const;
  bool isHead() const;
};

template <typename keyType, typename valueType>
class SkipList
{
private:
  SkipListNode<keyType, valueType> *head_;
  unsigned long long size_;
public:
  SkipList();
  ~SkipList();
  unsigned long long size() const;
  void dump();
  bool compact() { return true };
  bool insert(const SkipListNode<keyType, valueType> &);
  bool remove(const keyType &);
  SkipListNode<keyType, valueType> * find(const keyType &) { return 0; };
};

template <typename keyType, typename valueType>
inline SkipListNode<keyType, valueType> createNode(keyType key, valueType value)
{
  return SkipListNode<keyType, valueType>(key, value);
}

#include "skipList.tpp"

#endif
