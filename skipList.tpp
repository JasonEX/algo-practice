#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
// SkipListNode

template <typename keyType, typename valueType>
void SkipListNode<keyType, valueType>::generateHeight()
{
  height_ = 0;
  while (rand() % 2 == 0)
    height_ += 1;
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType>::SkipListNode() : 
  prev_(NULL),
  next_(NULL),
  upperlayer_(NULL), 
  underlayer_(NULL),
  head_(false)
{
  generateHeight();
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType>::SkipListNode(const keyType &key, const valueType &value) : 
  key_(key),
  value_(value),
  prev_(NULL),
  next_(NULL),
  upperlayer_(NULL),
  underlayer_(NULL),
  head_(false)
{
  generateHeight();
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType>::SkipListNode(const SkipListNode<keyType, valueType> &node) : 
  key_(node.key_),
  value_(node.value_),
  prev_(node.prev_),
  next_(node.next_),
  upperlayer_(node.upperlayer_),
  underlayer_(node.underlayer_),
  height_(node.height_),
  head_(node.head_)
{
}

template <typename keyType, typename valueType>
keyType SkipListNode<keyType, valueType>::key() const
{
  return key_;
}

template <typename keyType, typename valueType>
valueType SkipListNode<keyType, valueType>::value() const
{
  return value_;
}

template <typename keyType, typename valueType>
valueType & SkipListNode<keyType, valueType>::mutableValue()
{
  return value_;
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType> * SkipListNode<keyType, valueType>::prev() const
{
  return prev_;
}

template <typename keyType, typename valueType>
void SkipListNode<keyType, valueType>::prev(SkipListNode<keyType, valueType> *node)
{
  prev_ = node;
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType> * SkipListNode<keyType, valueType>::next() const
{
  return next_;
}

template <typename keyType, typename valueType>
void SkipListNode<keyType, valueType>::next(SkipListNode<keyType, valueType> *node)
{
  next_ = node;
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType> * SkipListNode<keyType, valueType>::upperlayer() const
{
  return upperlayer_;
}

template <typename keyType, typename valueType>
void SkipListNode<keyType, valueType>::upperlayer(SkipListNode<keyType, valueType> *node)
{
  upperlayer_ = node;
}

template <typename keyType, typename valueType>
SkipListNode<keyType, valueType> * SkipListNode<keyType, valueType>::underlayer() const
{
  return underlayer_;
}

template <typename keyType, typename valueType>
void SkipListNode<keyType, valueType>::underlayer(SkipListNode<keyType, valueType> *node)
{
  underlayer_ = node;
}

template <typename keyType, typename valueType>
int SkipListNode<keyType, valueType>::height() const
{
  return height_;
}

template <typename keyType, typename valueType>
bool SkipListNode<keyType, valueType>::isHead() const
{
  return head_;
}

// SkipList

template <typename keyType, typename valueType>
SkipList<keyType, valueType>::SkipList() : 
  head_(NULL),
  size_(0),
  delCount_(0),
  compactTrigger_(defaultCompactTrigger)
{
}

template <typename keyType, typename valueType>
SkipList<keyType, valueType>::~SkipList()
{
  SkipListNode<keyType, valueType> *delNode = NULL;
  SkipListNode<keyType, valueType> *levelHead = head_;
  while (levelHead != NULL)
  {
    SkipListNode<keyType, valueType> *itNode = levelHead->next();
    while (itNode != NULL)
    {
      delNode = itNode;
      itNode = itNode->next();
      delete delNode;
    }
    delNode = levelHead;
    levelHead = levelHead->underlayer();
    delete delNode;
  }
}

template <typename keyType, typename valueType>
unsigned long long SkipList<keyType, valueType>::size() const
{
  return size_;
}

template <typename keyType, typename valueType>
void SkipList<keyType, valueType>::dump()
{
  SkipListNode<keyType, valueType> *levelHead = head_;
  while (levelHead != NULL)
  {
    SkipListNode<keyType, valueType> *itNode = levelHead->next();
    while (itNode != NULL)
    {
      std::cout << "[" << itNode->key() << ", " << itNode->value() << "]";
//      std::cout << "[" << itNode->key() << ", " << itNode->value() << ": " << itNode->height() << "]";
      itNode = itNode->next();
    }
    std::cout << std::endl;
    levelHead = levelHead->underlayer();
  }
}

template <typename keyType, typename valueType>
void SkipList<keyType, valueType>::compact()
{
  int headHeight = head_->height();
  SkipListNode<keyType, valueType> *delNode = head_;
  while (delNode->next() == NULL && delNode->underlayer() != NULL)
  {
    head_ = delNode->underlayer();
    head_->upperlayer(NULL);
    headHeight -= 1;
    delete delNode;
    delNode = head_;
  }
  SkipListNode<keyType, valueType> *itNode = head_;
  while (itNode != NULL)
  {
    itNode->height_ = headHeight;
    itNode = itNode->underlayer();
  }
}

template <typename keyType, typename valueType>
void SkipList<keyType, valueType>::setCompactTrigger(const unsigned long long &compactTrigger)
{
  compactTrigger_ = compactTrigger;
}

template <typename keyType, typename valueType>
bool SkipList<keyType, valueType>::insert(const SkipListNode<keyType, valueType> &node)
{
  if (size() == 0)
  {
    // Generate a head node which just hold the place
    SkipListNode<keyType, valueType> *head = new SkipListNode<keyType, valueType>();
    head->head_ = true;
    head->height_ = 0;
    head_ = head;
  }
  if (head_->height() < node.height())
  {
    // Adjust height of head node except for top level one, that one leaved to under processing code
    SkipListNode<keyType, valueType> *itNode = head_->underlayer();
    while (itNode != NULL)
    {
      itNode->height_ = node.height();
      itNode = itNode->underlayer();
    }
  }
  while (head_->height() < node.height())
  {
    // Increase height of head node
    SkipListNode<keyType, valueType> *newNode = new SkipListNode<keyType, valueType>();
    newNode->underlayer(head_);
    head_->upperlayer(newNode);
    newNode->head_ = true;
    newNode->height_ = head_->height() + 1;
    head_->height_ = node.height();
    head_ = newNode;
  }
  SkipListNode<keyType, valueType> *itNode = head_;
  SkipListNode<keyType, valueType> *floorNode = NULL;
  unsigned long long currentHeight = head_->height();
  while (itNode != NULL)
  {
    if (itNode->isHead() || itNode->key() < node.key())
      if (itNode->next() != NULL && itNode->next()->key() < node.key())
        itNode = itNode->next();
      else
      {
        if (currentHeight <= node.height())
        {
          // Add to this level
          SkipListNode<keyType, valueType> *nextNode = itNode->next();
          SkipListNode<keyType, valueType> *newNode = new SkipListNode<keyType, valueType>(node);
          itNode->next(newNode);
          newNode->prev(itNode);
          newNode->next(nextNode);
          if (nextNode != NULL)
            nextNode->prev(newNode);
          if (floorNode != NULL)
            floorNode->underlayer(newNode);
          newNode->upperlayer(floorNode);
          floorNode = newNode;
        }
        currentHeight -= 1;
        itNode = itNode->underlayer();
      }
    else
      return false;
  }
  size_ += 1;
  return true;
}

template <typename keyType, typename valueType>
bool SkipList<keyType, valueType>::remove(const keyType &key)
{
  SkipListNode<keyType, valueType> *itNode = head_;
  bool found = false;
  while (itNode != NULL)
  {
    if (itNode->isHead() || itNode->key() < key)
      if (itNode->next() != NULL && itNode->next()->key() <= key)
        itNode = itNode->next();
      else
        itNode = itNode->underlayer();
    else if (itNode->key() == key)
    {
      // Remove on this level
      found = true;
      SkipListNode<keyType, valueType> *prevNode = itNode->prev();
      SkipListNode<keyType, valueType> *nextNode = itNode->next();
      SkipListNode<keyType, valueType> *upperNode = itNode->upperlayer();
      SkipListNode<keyType, valueType> *underNode = itNode->underlayer();
      if (prevNode != NULL)
        prevNode->next(nextNode);
      if (nextNode != NULL)
        nextNode->prev(prevNode);
      if (upperNode != NULL)
        upperNode->underlayer(underNode);
      if (underNode != NULL)
        underNode->upperlayer(upperNode);
      itNode = itNode->underlayer();
    }
    else
      return false;
  }
  if (found)
  {
    size_ -= 1;
    delCount_ += 1;
    if (delCount_ == compactTrigger_)
    {
      compact();
      delCount_ = 0;
    }
  }
  return found;
}

template <typename keyType, typename valueType>
bool SkipList<keyType, valueType>::find(const keyType &key, valueType &value)
{
  SkipListNode<keyType, valueType> *itNode = head_;
  bool found = false;
  while (itNode != NULL)
  {
    if (itNode->isHead() || itNode->key() < key)
      if (itNode->next() != NULL && itNode->next()->key() <= key)
        itNode = itNode->next();
      else
        itNode = itNode->underlayer();
    else if (itNode->key() == key)
    {
      // Get value
      found = true;
      value = itNode->value();
      return true;
    }
    else
      return false;
  }
  return found;
}

template <typename keyType, typename valueType>
valueType & SkipList<keyType, valueType>::find(const keyType &key)
{
  SkipListNode<keyType, valueType> *itNode = head_;
  std::ostringstream os;
  os << "key not found" << ":[" << key << "]";
  while (itNode != NULL)
  {
    if (itNode->isHead() || itNode->key() < key)
      if (itNode->next() != NULL && itNode->next()->key() <= key)
        itNode = itNode->next();
      else
        itNode = itNode->underlayer();
    else if (itNode->key() == key)
      return itNode->mutableValue();
    else
      throw std::out_of_range(os.str());
  }
  throw std::out_of_range(os.str());
}
