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
    Node(const T &value) : data(value), next(nullptr) {}

    bool isEmpty() const
    {
      return data.isEmpty();
    }

    void toEmpty()
    {
      data = T();
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
  void removeByID(Node<T> *&node, std::string id)
  {
    if (node->next == nullptr)
    {
      if (node->isEmpty())
      {
        std::cout << "No songs available." << std::endl;
        return;
      }
      if (node->data.id == id)
      {
        node->toEmpty();
        return;
      }
      std::cout << "Song not found." << std::endl;
      return;
    }

    Node<T> *curr = node;
    Node<T> *prev = nullptr;

    while (curr != nullptr)
    {
      if (curr->data.id == id)
      {
        if (prev == nullptr)
        {
          node = curr->next;
        }
        else
        {
          prev->next = curr->next;
        }
        delete curr;
        std::cout << "Song deleted successfully." << std::endl;
        return;
      }
      prev = curr;
      curr = curr->next;
    }
    std::cout << "Song not found." << std::endl;
  }

  template <typename T>
  Node<T> *copy(Node<T> *node)
  {
    if (!node)
      return nullptr;

    Node<T> *copiedHead = nullptr;
    Node<T> *copiedTail = nullptr;
    Node<T> *current = node;

    while (current)
    {
      Node<T> *newNode = new Node<T>(current->data);
      if (!copiedHead)
      {
        copiedHead = copiedTail = newNode;
      }
      else
      {
        copiedTail->next = newNode;
        copiedTail = newNode;
      }
      current = current->next;
    }

    return copiedHead;
  }

  template <typename T>
  Node<T> *sort(Node<T> *node, const std::string &sortBy)
  {
    if (!node || !node->next)
      return node;

    Node<T> *sorted = copy(node);

    bool swapped;
    do
    {
      swapped = false;
      Node<T> *current = sorted;

      while (current->next)
      {
        Node<T> *nextNode = current->next;

        if (nextNode->data.getValue(sortBy) < current->data.getValue(sortBy))
        {
          std::swap(current->data, nextNode->data);
          swapped = true;
        }

        current = current->next;
      }
    } while (swapped);

    return sorted;
  }
}
