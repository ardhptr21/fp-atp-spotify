namespace linkedlist
{
  template <typename T>

  struct Node
  {
    T data;
    Node<T> *next;
  };

  template <typename T>
  void append(Node<int> *node, T data)
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
}
