#pragma once
#include <string>
#include <algorithm>
#include <map>
#include <iostream>

template <typename T>
struct Node
{
								int key;
								T value;
								struct Node* left, *right;
								Node(const int p_key, T p_value) : key(p_key), value(p_value), left(nullptr), right(nullptr)
								{}
								~Node()
								{
												delete left;
												delete right;
												left = nullptr;
												right = nullptr;
								}
};

template <typename T>
class BST
{
public:
				BST();
				~BST();
				Node<T>* Add(int p_key, T p_value);
				Node<T>* Search(int p_key);
				Node<T>* Setvalue(int p_key, T p_value);
				T GetValue(int p_key);
				bool Remove(int p_key);
				void Display();
				void ReverseDisplay();
				void Clear();
				int Count();
				int GetHeight();

private:
				Node<T>* m_root = nullptr;
				Node<T>* CheckEndingLeave(Node<T>* p_toSearch, int p_key, T p_value);
				Node<T>* SearchLeaves(Node<T>* p_toSearch, int p_key);
				Node<T>* FindMinimum(Node<T>* p_toSearch);
				Node<T>* FindMax(Node<T>* p_toSearch);
				Node<T>* Eliminate(Node<T>* p_eliminate, int p_key);
				int NodesCounter(Node<T>* p_toCount);
				int HeightCounter(Node<T>* p_toCount);
				void Inorder(Node<T>* p_root);
				void DecresingOrder(Node<T>* p_root);
};

template <typename T>
BST<T>::BST() {}

template <typename T>
BST<T>::~BST()
{
				Clear();
}

template <typename T>
Node<T>* BST<T>::Add(const int p_key, T p_value)
{
				if(Search(p_key))
								return nullptr;

				if(m_root)
				{
								if(m_root->key > p_key)
								{
												if(!m_root->left)
												{
																m_root->left = new Node<T>(p_key, p_value);
																return m_root->left;
												}
												CheckEndingLeave(m_root->left, p_key, p_value);
								}
								if(m_root->key < p_key)
								{
												if (!m_root->right)
												{
																m_root->right = new Node<T>(p_key, p_value);
																return m_root->right;
												}
											CheckEndingLeave(m_root->right, p_key, p_value);
								}
				}
				else
				{
								m_root = new Node<T>(p_key, p_value);
								return m_root;
				}
	return nullptr;
}

template <typename T>
Node<T>* BST<T>::Search(int p_key)
{
				return SearchLeaves(m_root, p_key);
}

template <typename T>
Node<T>* BST<T>::Setvalue(int p_key, T p_value)
{
				if(!Search(p_key))
								return nullptr;

				Node<T>* temp = Search(p_key);
				temp->value = p_value;
				return temp;
}

template <typename T>
T BST<T>::GetValue(int p_key)
{
				if (!Search(p_key))
								return NULL;

				Node<T>* temp = Search(p_key);
				return temp->value;
}

template <typename T>
bool BST<T>::Remove(int p_key)
{
				bool flag = false;
				if (!Eliminate(m_root, p_key))
				{
								flag = true;
				}
				return flag;
}

template <typename T>
void BST<T>::Display()
{
				Inorder(m_root);
}

template <typename T>
void BST<T>::ReverseDisplay()
{
				DecresingOrder(m_root);
}

template <typename T>
void BST<T>::Clear()
{
				delete m_root;
				m_root = nullptr;
}

template <typename T>
int BST<T>::Count()
{
				return NodesCounter(m_root);
}

template <typename T>
int BST<T>::GetHeight()
{
				return HeightCounter(m_root);
}

template <typename T>
Node<T>* BST<T>::CheckEndingLeave(Node<T>* p_toSearch, int p_key, T p_value)
{
				if (p_toSearch->key > p_key)
				{
								if (!p_toSearch->left)
								{
												p_toSearch->left = new Node<T>(p_key, p_value);
												return p_toSearch->left;
								}
								CheckEndingLeave(p_toSearch->left, p_key, p_value);
				}
				else if (p_toSearch->key < p_key)
				{
								if (!p_toSearch->right)
								{
												p_toSearch->right = new Node<T>(p_key, p_value);
												return p_toSearch->right;
								}
								CheckEndingLeave(p_toSearch->right, p_key, p_value);
				}
	return nullptr;
}

template <typename T>
Node<T>* BST<T>::SearchLeaves(Node<T>* p_toSearch, int p_key)
{
				if(!p_toSearch)
								return nullptr;

				if (p_key == p_toSearch->key)
								return p_toSearch;

				if(p_toSearch->key > p_key)
				{
								return SearchLeaves(p_toSearch->left, p_key);
				}
				else if(p_toSearch->key < p_key)
				{
								return SearchLeaves(p_toSearch->right, p_key);
				}

	return nullptr;
}

template <typename T>
Node<T>* BST<T>::FindMinimum(Node<T>* p_toSearch)
{
				if (p_toSearch == nullptr)
				{
								return nullptr;
				}
				if (p_toSearch->left == nullptr)
				{
								return p_toSearch;
				}
				return FindMinimum(p_toSearch->left);
}

template <typename T>
Node<T>* BST<T>::FindMax(Node<T>* p_toSearch)
{
				if (!p_toSearch)
				{
								return nullptr;
				}
				if (!p_toSearch->right)
				{
								return p_toSearch;
				}
				return FindMax(p_toSearch->right);
}

template <typename T>
Node<T>* BST<T>::Eliminate(Node<T>* p_eliminate, int p_key)
{
				if (!p_eliminate || !Search(p_key)) 
								return nullptr;

				if (p_key < p_eliminate->key)
								p_eliminate->left = Eliminate(p_eliminate->left, p_key);

				else if (p_key > p_eliminate->key)
								p_eliminate->right = Eliminate(p_eliminate->right, p_key);

				else
				{
								if (!p_eliminate->left)
								{
												Node<T> *temp = p_eliminate->right;
												delete(p_eliminate);
												return temp;
								}
								if (!p_eliminate->right)
								{
												Node<T> *temp = p_eliminate->left;
												delete(p_eliminate);
												return temp;
								}
								Node<T> *temp = FindMinimum(p_eliminate->right);

								p_eliminate->key = temp->key;
								p_eliminate->value = temp->value;
								p_eliminate->right = Eliminate(p_eliminate->right, temp->key);
				}
				return p_eliminate;
}

template <typename T>
int BST<T>::NodesCounter(Node<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + NodesCounter(p_toCount->left) + NodesCounter(p_toCount->right);
}

template <typename T>
int BST<T>::HeightCounter(Node<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + std::max(HeightCounter(p_toCount->left), HeightCounter(p_toCount->right));
}

template <typename T>
void BST<T>::Inorder(Node<T>* p_root)
{
				if (!p_root)
								return;

				Inorder(p_root->left);
				std::cout << "[-Key: " << p_root->key << " -Value: " << p_root->value << "]" << std::endl;
				Inorder(p_root->right);
}

template <typename T>
void BST<T>::DecresingOrder(Node<T>* p_root)
{
				if (!p_root)
								return;

				DecresingOrder(p_root->right);
				std::cout << "[-Key: " << p_root->key << " -Value: " << p_root->value << "]" << std::endl;
				DecresingOrder(p_root->left);
}
