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
  void removeAt(Node<T> *&node, int index)
  {
    if (node == nullptr)
    {
      std::cout << "Invalid!" << std::endl;
      return;
    }

    if (index == 0)
    {
      if (node->next == nullptr)
      {
        node = new Node<T>();
        return;
      }
      Node<T> *temp = node;
      node = node->next;
      delete temp;
      return;
    }

    Node<T> *temp = node;
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
      temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr)
    {
      std::cout << "List is empty." << std::endl;
      return;
    }

    Node<T> *toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
  };
}
