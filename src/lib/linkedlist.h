#pragma once

#include <optional>

namespace linkedlist
{
  template <typename T>

  struct Node
  {
    std::optional<T> data;
    Node<T> *next;
  };

  template <typename T>
  void append(Node<T> *node, T data)
  {
    if (node->next == nullptr)
    {
      Node<T> *newNode = new Node<T>{data, nullptr};
      if (node->data.has_value())
      {
        node->data = data;
      }
      else
      {
        node->next = newNode;
      }
      return;
    }

    append(node->next, data);
  }

  template <typename T>
  void removeAtBeginning(Node<T> *node)
  {
    node = node->next;
  }

  template <typename T>
  void removeAt(Node<T> *node, int index)
  {
    if (node->next == nullptr && index != 0)
    {
      return;
    }
    if (index == 0)
      return removeAtBeginning(node);

    removeAt(node->next, index - 1);
  };

}
