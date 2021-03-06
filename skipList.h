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
  valueType & mutableValue();
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
  static const unsigned long long defaultCompactTrigger = 20;
  SkipListNode<keyType, valueType> *head_;
  unsigned long long size_;
  unsigned long long delCount_;
  unsigned long long compactTrigger_;
public:
  SkipList();
  ~SkipList();
  unsigned long long size() const;
  void dump();
  void compact();
  void setCompactTrigger(const unsigned long long &);
  bool insert(const SkipListNode<keyType, valueType> &);
  bool remove(const keyType &);
  bool find(const keyType &, valueType &);
  valueType & find(const keyType &);

  // Since the height would not change, the value will always get from top level
  // it should be safe to just return the value of top level node
  inline valueType & operator[](const keyType &key) { return find(key); }
  inline const valueType & operator[](const keyType &key) const { return find(key); }
};

template <typename keyType, typename valueType>
inline SkipListNode<keyType, valueType> createNode(const keyType &key, const valueType &value)
{
  return SkipListNode<keyType, valueType>(key, value);
}

#include "skipList.tpp"

#endif
