#pragma once

#include <sstream>

template <typename TData>
struct Node
{
  TData val;
  Node *prev;
  Node *next;

  Node() : prev(nullptr), next (nullptr) {}
  Node(TData x) : val(x), prev(nullptr), next(nullptr) {}
  ~Node(){}
};

template <typename TData>
class CArray
{
private:
    unsigned int m_Count;
    Node<TData> * m_pHead;
    Node<TData> * m_pTail;

private:
    Node<TData> * getByIndex(
        unsigned int _index
      );

    void split(
        Node<TData> * _head,
        Node<TData> ** _right
      );

    Node<TData> * merge(
        Node<TData> * _left,
        Node<TData> * _right
      );

    void mergesort(
        Node<TData> ** _head
      );

public:
   CArray();

   CArray(
       const CArray& _array
     );

   ~CArray();

   void push_back(
       const TData& _value
     );

   void insert(
       unsigned int _index,
       const TData& _value
     );

   void erase(
       unsigned int _index
     );

   void clear();

   inline unsigned int size() const
   {
     return m_Count;
   }

   TData& operator[](
       unsigned int _index
     );

   void sort();

   std::string printArray();
};

template <typename TData>
CArray<TData>::CArray()
    : m_Count (0)
    , m_pHead(nullptr)
    , m_pTail(nullptr)
{

}

template <typename TData>
CArray<TData>::CArray(
    const CArray<TData> &_array
  )
{
  m_Count = _array.m_Count;
  m_pHead = _array.m_pHead;
  m_pTail = _array.m_pTail;
}

template <typename TData>
CArray<TData>::~CArray()
{
  clear();
}

template <typename TData>
void CArray<TData>::push_back(
    const TData &_value
  )
{
  if( !m_pHead )
  {
    m_pHead = new Node<TData>(_value);
    m_pTail = m_pHead;
    ++m_Count;
  }
  else
  {
     Node<TData> * node = new Node<TData>(_value);
     m_pTail->next = node;
     node->prev = m_pTail;
     m_pTail = node;
     ++m_Count;
  }
}

template <typename TData>
std::string CArray<TData>::printArray()
{
  std::stringstream ss;
  ss << "[";

  Node<TData> * curNode = m_pHead;
  while(curNode)
  {
     ss << "'";
     ss << curNode->val;
     if(curNode->next)
         ss << "'; ";
     else
         ss << "'";
     curNode = curNode->next;
  }

  ss << "]";

  return ss.str();
}

template <typename TData>
Node<TData>* CArray<TData>::getByIndex(
    unsigned int _index
  )
{
  if(_index < 0 || _index >= m_Count)
    throw "Index Is Out Of Range";

  int curIndex;
  Node<TData> * curNode;

  if( _index <= m_Count / 2 )
  {
      //from head
      curIndex = 0;
      curNode = m_pHead;

      while( curIndex < _index )
      {
          curNode = curNode->next;
          ++curIndex;
      }
      return curNode;
  }
  else
  {
      //from tail
      curIndex = size() - 1;
      curNode = m_pTail;

      while( curIndex > _index )
      {
          curNode = curNode->prev;
          --curIndex;
      }
      return curNode;
  }
}

template <typename TData>
TData& CArray<TData>::operator[](
    unsigned int _index
  )
{
  // save because getByIndex function checks null pointer and throws exception
  return getByIndex( _index )->val;
}

template <typename TData>
void CArray<TData>::insert(
    unsigned int _index,
    const TData& _value
  )
{
  Node<TData> * newNode = new Node<TData>(_value);

  if( ( _index == 0 && m_Count == 0 ) || _index == m_Count)
  {
    push_back( _value );
  }
  else if( _index == 0 )
  {
    newNode->next = m_pHead;
    m_pHead->prev = newNode;
    m_pHead = newNode;
    ++m_Count;
  }
  else
  {
    Node<TData> * curNode;
    curNode = getByIndex( _index );

    newNode->prev = curNode->prev;
    newNode->next = curNode;
    curNode->prev->next = newNode;
    curNode->prev = newNode;
    ++m_Count;
  }

  return;
}

template <typename TData>
void CArray<TData>::erase(
    unsigned int _index
  )
{
  Node<TData> * curNode;
  // save because getByIndex function checks null pointer and throws exception
  curNode = getByIndex( _index );

  if(curNode == m_pHead)
  {
     m_pHead = curNode->next;
     delete curNode;
     curNode = nullptr;

     if( !m_pHead )
     {
       m_pTail = nullptr;
     }
  }
  else if(curNode == m_pTail)
  {
      m_pTail = curNode->prev;
      m_pTail->next = nullptr;
      delete curNode;
      curNode = nullptr;
  }
  else
  {
      curNode->prev->next = curNode->next;
      curNode->next->prev = curNode->prev;
      delete curNode;
      curNode = nullptr;
  }

  --m_Count;
}

template <typename TData>
void CArray<TData>::clear()
{
  while (m_pHead && m_pHead->next)
  {
     m_pHead = m_pHead->next;
     delete m_pHead->prev;
     m_pHead->prev = nullptr;
  }

  delete m_pHead;
  m_pHead = nullptr;
  m_pTail = nullptr;
  m_Count = 0;
}

//split array for two parts in the middle
template <typename TData>
void CArray<TData>::split(
    Node<TData> * _head,
    Node<TData> ** _right
  )
{
  Node<TData>* slow = _head;
  Node<TData>* fast = _head->next;

  while (fast != nullptr)
  {
     fast = fast->next;
     if (fast != nullptr)
     {
         slow = slow->next;
         fast = fast->next;
     }
  }

  *_right = slow->next;
  slow->next = nullptr;
}


template <typename TData>
Node<TData> * CArray<TData>::merge(
   Node<TData>* _left,
   Node<TData>* _right
  )
{
  if (_left == nullptr) {
    return _right;
  }

  if (_right == nullptr) {
    return _left;
  }

  if (_left->val <= _right->val)
  {
     _left->next = merge(_left->next, _right);
     _left->next->prev = _left;
     _left->prev = nullptr;
     return _left;
  }
  else {
     _right->next = merge(_left, _right->next);
     _right->next->prev = _right;
     _right->prev = nullptr;
     return _right;
  }
}

template <typename TData>
void CArray<TData>::mergesort(
    Node<TData> ** _head
  )
{
  if ( *_head == nullptr || (*_head)->next == nullptr)
  {
    return;
  }

  Node<TData> * pLeft = *_head;
  Node<TData> * pRight = nullptr;
  split(*_head, &pRight);

  mergesort(&pLeft);
  mergesort(&pRight);

  *_head = merge(pLeft, pRight);
}

template <typename TData>
void CArray<TData>::sort()
{
  mergesort(&m_pHead);
  Node<TData>* curNode = m_pHead;
  while (curNode->next)
  {
    curNode = curNode->next;
  }
  m_pTail = curNode;
}
