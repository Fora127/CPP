#pragma once

#include <new>
#include <cstddef>
#include <string>
#include <sstream>
#include <utility>

#define _DEFAULT_CAPACITY 10

template <typename TData>
class CArray
{
private:
  TData* m_arr = nullptr;
  std::size_t m_size = 0u;
  std::size_t m_capacity = 0u;

private:
  void quickSort(TData arr[], int start, int end);
  int partition(TData arr[], int start, int end);

public:
  CArray();

  CArray(
      const CArray& _arr
    );

  ~CArray();

  std::size_t size() const;

  std::size_t capacity() const;

  void reserve(
      std::size_t _newcapacity
    );

  void insert(
      std::size_t _index,
      const TData& _value
    );

  void insert(
      std::size_t _index,
      TData&& _value
    );

  void push_back(
      const TData& data
    );

  void push_back(
       TData&& data
    );

  TData& operator[](
      std::size_t _i
    );

  const TData& operator[](
      std::size_t _i
    ) const;

  void erase(
      std::size_t _index
    );

  void clear();

  void sort();

  std::string print();
};

template<typename TData>
CArray<TData>::CArray()
  : m_capacity(_DEFAULT_CAPACITY)
{
  m_arr = reinterpret_cast<TData*>(new std::byte[m_capacity * sizeof(TData)]);

  if(!m_arr)
      throw "Can't allocate memory";
}


template<typename TData>
CArray<TData>::CArray(
    const CArray& _arr
  ) : m_size (_arr.size()),
      m_capacity (_arr.capacity())
{
  if(m_capacity <= 0)
     return;

  m_arr = reinterpret_cast<TData*>(new std::byte[m_capacity * sizeof(TData)]);

  if(!m_arr)
     throw "Can't allocate memory";

  for(std::size_t i = 0; i < m_size; ++i)
  {
    new(m_arr + i) TData(_arr[i]);
  }
}

template<typename TData>
CArray<TData>::~CArray()
{
    // erase data
    clear();

    // deallocate memeory
    if(m_arr)
      delete[] reinterpret_cast<std::byte*>(m_arr);
}

template<typename TData>
std::size_t CArray<TData>::size() const
{
  return m_size;
}

template<typename TData>
std::size_t CArray<TData>::capacity() const
{
  return m_capacity;
}

template<typename TData>
void CArray<TData>::reserve(
    std::size_t _newcapacity
  )
{
  // allocate new memory
  if(_newcapacity <= 0 || _newcapacity <= m_capacity)
    return;

  TData* newarr = reinterpret_cast<TData*>(new std::byte[_newcapacity * sizeof(TData)]);

  if(!newarr)
     throw "Can't allocate memory";

  // move array from old memory
  for(std::size_t i = 0; i < m_size; ++i)
  {
      new(newarr+i) TData(std::move(m_arr[i]));
  }

  // deallocate old memeory
  if(m_arr)
    delete[] reinterpret_cast<std::byte*>(m_arr);

  m_capacity = _newcapacity;
  m_arr = newarr;
}


template<typename TData>
TData& CArray<TData>::operator[](
    std::size_t _i
  )
{
  if( _i >= m_size || !m_arr)
    throw "Index Out Of Range";

  return m_arr[_i];
}

template<typename TData>
const TData& CArray<TData>::operator[](
    std::size_t _i
  ) const
{
  if( _i >= m_size || !m_arr)
    throw "Index Out Of Range";

  return m_arr[_i];
}

template<typename TData>
void CArray<TData>::insert(
    std::size_t _index,
    const TData& _value
  )
{
  if(_index > m_size || !m_arr)
    throw "Index Out Of Range";

  if(m_size >= m_capacity)
    reserve(m_capacity * 2);

  new((m_arr + m_size)) TData(_value);

  for ( std::size_t i = m_size; i > _index; --i )
  {
      std::swap(m_arr[i], m_arr[i-1]);
  }

  ++m_size;
}


template<typename TData>
void CArray<TData>::insert(
    std::size_t _index,
    TData&& _value
  )
{
  if(_index > m_size || !m_arr)
    throw "Index Out Of Range";

  if(m_size >= m_capacity)
    reserve(m_capacity * 2);

  new(m_arr + m_size) TData(std::move(_value));

  for ( std::size_t i = m_size; i > _index; --i )
  {
      std::swap(m_arr[i], m_arr[i-1]);
  }

  ++m_size;
}


template<typename TData>
void CArray<TData>::push_back(
    const TData &data
  )
{
  insert(m_size, data);
}

template<typename TData>
void CArray<TData>::push_back(
     TData&& data
  )
{
  insert(m_size, std::move(data));
}


template<typename TData>
void CArray<TData>::erase(
    std::size_t _index
  )
{
  if(_index >= m_size || !m_arr)
    throw "Index Out Of Range";

  --m_size;

  for ( std::size_t i = _index; i < m_size; ++i )
  {
    m_arr[i] = m_arr[i+1];
  }

  (m_arr+m_size)->~TData();
}


template<typename TData>
void CArray<TData>::clear()
{
  if(!m_arr)
      return;

  // delete array from old memory
  for(std::size_t i = 0; i < m_size; ++i)
  {
     (m_arr+i)->~TData();
  }

  m_size = 0;
}

template<typename TData>
void CArray<TData>::sort()
{
  if(!m_arr)
      return;

  quickSort(m_arr, 0, m_size - 1);
}

template<typename TData>
void CArray<TData>::quickSort(
    TData arr[],
    int start, int end
  )
{
  // base case
  if (start >= end)
    return;

  // partitioning the array
  int p = partition(arr, start, end);

  // Sorting the left part
  quickSort(arr, start, p - 1);

  // Sorting the right part
  quickSort(arr, p + 1, end);
}

template<typename TData>
int CArray<TData>::partition(
    TData arr[],
    int start,
    int end
  )
{
    TData pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

template<typename TData>
std::string CArray<TData>::print()
{
  std::stringstream ss;

  if(!m_arr)
      ss << "[]";
  else
  {
      ss << "[";
      for(std::size_t i = 0; i < m_size; ++i)
      {
          ss << "'" << m_arr[i];
          if(i < (m_size - 1))
              ss << "'; ";
          else
              ss << "'";
      }
      ss << "]";
  }

  return ss.str();
}
