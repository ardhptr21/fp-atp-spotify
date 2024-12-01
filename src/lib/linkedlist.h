#pragma once

#include <iostream>
namespace linkedlist
{
  template <typename T>

  struct Node
  {
    T data;
    Node<T> *next;

    Node() : data(), next(nullptr) {}

    bool isEmpty() const
    {
      return data.isEmpty();
    }
  };

  template <typename T>
  void append(Node<T> *&node, T data)
  {
    Node<T> *newNode = new Node<T>();
    newNode->data = data;
    newNode->next = nullptr;

    if (node->next == nullptr)
    {
      if (node->isEmpty())
      {
        node->data = data;
        return;
      }
      node->next = newNode;
      return;
    }

    append(node->next, data);
  }

  template <typename T>
  void removeAtBeginning(Node<T> *&node)
  {
    if (node->next == nullptr)
    {
      node = new Node<T>();
      return;
    }
    node = node->next;
  }

  template <typename T>
  void removeAt(Node<T> *&node, int index)
  {
    if (node->next == nullptr && index != 0)
    {
      std::cout << "Invalid!" << std::endl;
      return;
    }

    if (index == 0)
      return removeAtBeginning(node);

    removeAt(node->next, index - 1);
  };
}
