namespace linkedlist
{
  template <typename T>

  struct Node
  {
    T data;
    Node<T> *next;
  };

  template <typename T>
  void append(Node<T> *node, T data)
  {
    if (node->next == nullptr)
    {
      Node<T> *newNode = new Node<T>{data, nullptr};
      node->next = newNode;
      return;
    }

    append(node->next, data);
  }

  template <typename T>
  void remove(Node<T> *node, T data)
  {
    if (node->next == nullptr)
      return;

    if (node->next->data == data)
    {
      Node<T> *temp = node->next;
      node->next = node->next->next;
      delete temp;
      return;
    }

    remove(node->next, data);
  }

  template <typename T>
  void removeAtBeginning(Node<T> *node)
  {
    node = node->next;
  }

  template <typename T>
  void removeAt(Node<T> *node, int index)
  {
    if (node->next == nullptr && pos != 0)
    {
      return;
    }
    if (pos == 0)
      return removeAtBeginning(node);

    deleteAt(node->next, pos - 1);
  };

}
