#pragma once
#include <iostream>
#include <algorithm>

template<typename T>
struct AVLNode
{
				int key;
				T value;
				int height = 0;
				AVLNode<T>* left = nullptr;
				AVLNode<T>* right = nullptr;
				AVLNode(int p_key, T p_value) : key(p_key), value(p_value) {}
				~AVLNode()
				{
								delete left;
								delete right;
								left = nullptr;
								right = nullptr;
				}
};

template<typename T>
class AVLT
{
public:
				AVLT();
				~AVLT();
				void Clear();
				void Display();
				void ReverseDisplay();
				void Add(int p_key, T p_value);
				void Remove(int p_key);
				int Count();
				int GetHeight();
private:
				AVLNode<T>* m_root = nullptr;
				AVLNode<T>* Insert(AVLNode<T>* p_node, int p_key, T p_value);
				AVLNode<T>* SingleRightRotation(AVLNode<T>* p_rightRotate);
				AVLNode<T>* SingleLeftRotation(AVLNode<T>* p_leftRotate);
				AVLNode<T>* DoubleRightRotation(AVLNode<T>* p_rightRotation);
				AVLNode<T>* DoubleLeftRotation(AVLNode<T>* p_leftRotation);
				AVLNode<T>* Balance(AVLNode<T>* p_toBalance);
				AVLNode<T>* FindMax(AVLNode<T>* p_max);
				AVLNode<T>* FindMin(AVLNode<T>* p_min);
				AVLNode<T>* RemoveMin(AVLNode<T>* p_min);
				AVLNode<T>* SearchLeaves(AVLNode<T>* p_toSearch, int p_key);
				AVLNode<T>* Delete(AVLNode<T>* p_toDelete, int p_key);
				int NodesCounter(AVLNode<T>* p_toCount);
				int HeightDifference(AVLNode<T>* p_toCheck);
				int HeightCounter(AVLNode<T>* p_toCount);
				int Height(AVLNode<T>* p_height);
				void Inorder(AVLNode<T>* p_node);
				void ReverseOrder(AVLNode<T>* p_node);
				void BalanceHeight(AVLNode<T>* p_node);
};

template <typename T>
AVLT<T>::AVLT() {}

template <typename T>
AVLT<T>::~AVLT()
{
				Clear();
}

template <typename T>
void AVLT<T>::Clear()
{
				delete m_root;
				m_root = nullptr;
}

template <typename T>
void AVLT<T>::Display()
{
				Inorder(m_root);
				std::cout << std::endl;
}

template <typename T>
void AVLT<T>::ReverseDisplay()
{
				ReverseOrder(m_root);
				std::cout << std::endl;
}

template <typename T>
void AVLT<T>::Add(int p_key, T p_value)
{
				m_root = Insert(m_root, p_key, p_value);
}

template <typename T>
void AVLT<T>::Remove(int p_key)
{
				m_root = Delete(m_root, p_key);
}

template <typename T>
int AVLT<T>::Count()
{
				return NodesCounter(m_root);
}

template <typename T>
int AVLT<T>::GetHeight()
{
				return HeightCounter(m_root);
}

template <typename T>
AVLNode<T>* AVLT<T>::Insert(AVLNode<T>* p_node, int p_key, T p_value)
{
				if (SearchLeaves(p_node, p_key))
								return p_node;

				if (!p_node)
				{
								p_node = new AVLNode<T>(p_key, p_value);
				}
				else if(p_key < p_node->key)
				{
								p_node->left = Insert(p_node->left, p_key, p_value);
								if (Height(p_node->left) - Height(p_node->right) == 2)
								{
												if (p_key < p_node->left->key)
																p_node = SingleRightRotation(p_node);
												else
												{
																p_node = DoubleRightRotation(p_node);
												}
								}
				}
				else if(p_key > p_node->key)
				{
								p_node->right = Insert(p_node->right, p_key, p_value);
								if(Height(p_node->right) - Height(p_node->left) == 2)
								{
												if(p_key > p_node->right->key)
												{
																p_node = SingleLeftRotation(p_node);
												}
												else
												{
																p_node = DoubleLeftRotation(p_node);
												}
								}
				}
				p_node->height = std::max(Height(p_node->left), Height(p_node->right)) + 1;
				return p_node;
}

template <typename T>
AVLNode<T>* AVLT<T>::SingleRightRotation(AVLNode<T>* p_rightRotate)
{
				AVLNode<T>* temp = p_rightRotate->left;
				p_rightRotate->left = temp->right;
				temp->right = p_rightRotate;
				p_rightRotate->height = std::max(Height(p_rightRotate->left), Height(p_rightRotate->right)) + 1;
				temp->height = std::max(Height(temp->left), p_rightRotate->height) + 1;
				return temp;
}

template <typename T>
AVLNode<T>* AVLT<T>::SingleLeftRotation(AVLNode<T>* p_leftRotate)
{
				AVLNode<T>* temp = p_leftRotate->right;
				p_leftRotate->right = temp->left;
				temp->left = p_leftRotate;
				p_leftRotate->height = std::max(Height(p_leftRotate->left), Height(p_leftRotate->right)) + 1;
				temp->height = std::max(Height(p_leftRotate->right), p_leftRotate->height) + 1;
				return temp;
}

template <typename T>
AVLNode<T>* AVLT<T>::DoubleRightRotation(AVLNode<T>* p_rightRotation)
{
				p_rightRotation->right = SingleLeftRotation(p_rightRotation->right);
				return SingleRightRotation(p_rightRotation);
}

template <typename T>
AVLNode<T>* AVLT<T>::DoubleLeftRotation(AVLNode<T>* p_leftRotation)
{
				p_leftRotation->left = SingleRightRotation(p_leftRotation->left);
				return SingleRightRotation(p_leftRotation);
}

template <typename T>
AVLNode<T>* AVLT<T>::Balance(AVLNode<T>* p_toBalance)
{
				BalanceHeight(p_toBalance);
				if(HeightDifference(p_toBalance) == 2)
				{
								if(HeightDifference(p_toBalance->right) < 0)
								{
												p_toBalance->right = SingleRightRotation(p_toBalance->right);
												return SingleLeftRotation(p_toBalance);
								}
				}
				if(HeightDifference(p_toBalance) == -2)
				{
								if(HeightDifference(p_toBalance->left) > 0)
								{
												p_toBalance->left = SingleLeftRotation(p_toBalance->left);
												return SingleRightRotation(p_toBalance);
								}
				}
				return p_toBalance;
}

template <typename T>
AVLNode<T>* AVLT<T>::FindMax(AVLNode<T>* p_max)
{
				if(!p_max)
								return nullptr;

				if (!p_max->right)
								return p_max;

				return FindMax(p_max->right);
}

template <typename T>
AVLNode<T>* AVLT<T>::FindMin(AVLNode<T>* p_min)
{
				AVLNode<T>* current = p_min;

				while(current->left != nullptr)
				{
								current = current->left;
				}
				return current;
}

template <typename T>
AVLNode<T>* AVLT<T>::RemoveMin(AVLNode<T>* p_min)
{
				if (!p_min->left)
								return p_min->right;

				p_min->left = RemoveMin(p_min->left);
				return Balance(p_min);
}

template <typename T>
AVLNode<T>* AVLT<T>::SearchLeaves(AVLNode<T>* p_toSearch, int p_key)
{
				if (!p_toSearch)
								return nullptr;

				if (p_key == p_toSearch->key)
								return p_toSearch;

				if (p_toSearch->key > p_key)
				{
								return SearchLeaves(p_toSearch->left, p_key);
				}
				else if (p_toSearch->key < p_key)
				{
								return SearchLeaves(p_toSearch->right, p_key);
				}

				return nullptr;
}

template <typename T>
AVLNode<T>* AVLT<T>::Delete(AVLNode<T>* p_toDelete, int p_key)
{
				if(!p_toDelete || !SearchLeaves(p_toDelete, p_key))
								return p_toDelete;

				if(p_key < p_toDelete->key)
				{
								p_toDelete->left = Delete(p_toDelete->left, p_key);
				}
				else if(p_key > p_toDelete->key)
				{
								p_toDelete->right = Delete(p_toDelete->right, p_key);
				}
				else
				{	
							AVLNode<T>* temp;
							if(!p_toDelete->left || !p_toDelete->right)
							{
											temp = p_toDelete->left ? p_toDelete->left : p_toDelete->right;
										if(!temp)
										{
														temp = p_toDelete;
														p_toDelete = nullptr;
										}
										else
										{
														*p_toDelete = *temp;
										}
										delete temp;
							}
							else
							{
											temp = FindMin(p_toDelete->right);
											p_toDelete->key = temp->key;
											p_toDelete->value = temp->value;
											p_toDelete->right = Delete(p_toDelete->right, temp->key);
							}
				}
				if (!p_toDelete)
								return p_toDelete;

				p_toDelete->height = 1 + std::max(Height(p_toDelete->left), Height(p_toDelete->right));

				int balance = HeightDifference(p_toDelete);

				if(balance > 1 && HeightDifference(p_toDelete->left) >= 0)
				{
								return SingleRightRotation(p_toDelete);
				}
				if(balance > 1 && HeightDifference(p_toDelete->left) < 0)
				{
								return DoubleLeftRotation(p_toDelete);
				}
				if(balance < -1 && HeightDifference(p_toDelete->right) <= 0)
				{
								return SingleLeftRotation(p_toDelete);
				}
				if(balance < -1 && HeightDifference(p_toDelete->right) > 0)
				{
								return DoubleRightRotation(p_toDelete);
				}
				return p_toDelete;
}

template <typename T>
int AVLT<T>::NodesCounter(AVLNode<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + NodesCounter(p_toCount->left) + NodesCounter(p_toCount->right);
}

template <typename T>
int AVLT<T>::HeightDifference(AVLNode<T>* p_toCheck)
{
				return Height(p_toCheck->right) - Height(p_toCheck->left);
}

template <typename T>
int AVLT<T>::HeightCounter(AVLNode<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + std::max(HeightCounter(p_toCount->left), HeightCounter(p_toCount->right));
}

template <typename T>
int AVLT<T>::Height(AVLNode<T>* p_height)
{
				return p_height ? p_height->height : -1;
}

template <typename T>
void AVLT<T>::Inorder(AVLNode<T>* p_root)
{
				if (!p_root)
							return;

				Inorder(p_root->left);
				std::cout << "[-Key: " << p_root->key << " -Value: " << p_root->value << "]" << std::endl;
				Inorder(p_root->right);
}

template <typename T>
void AVLT<T>::ReverseOrder(AVLNode<T>* p_root)
{
				if (!p_root)
								return;

				ReverseOrder(p_root->right);
				std::cout << "[-Key: " << p_root->key << " -Value: " << p_root->value << "]" << std::endl;
				ReverseOrder(p_root->left);
}

template <typename T>
void AVLT<T>::BalanceHeight(AVLNode<T>* p_node)
{
				int left = Height(p_node->left);
				int right = Height(p_node->right);

				p_node->height = (left > right ? left : right) + 1;
}
