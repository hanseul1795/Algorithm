#pragma once
#include <iostream>
#include <algorithm>

enum Color {RED, BLACK, DOUBLEBLACK};

template<typename T>
struct RBNode
{
				int key;
				T value;
				RBNode<T>* left = nullptr;
				RBNode<T>* right = nullptr;
				RBNode<T>* parent = nullptr;
				Color color = RED;
				RBNode(int p_key, T p_value) : key(p_key), value(p_value) {}
				~RBNode()
				{
								if (left)
												delete left;
								if (right)
												delete right;

								left = right = nullptr;
				}
};

template<typename T>
class RBTree
{
public:
				RBTree();
				~RBTree();
				void Add(int p_key, T p_value);
				void Delete(int p_key);
				void Display();
				void ReverseDisplay();
				int Count();
				int GetHeight();

private:
				RBNode<T>* m_root = nullptr;
				RBNode<T>* FindMin(RBNode<T>* p_root);
				RBNode<T>* FindMax(RBNode<T>* p_root);
				RBNode<T>* InsertHelper(RBNode<T>*& p_root, RBNode<T>*& p_nil);
				RBNode<T>* DeleteHelper(RBNode<T>*& p_root, int p_key);
				RBNode<T>* Search(RBNode<T>* p_toSearch, int p_key);
				void LeftRotation(RBNode<T>*& p_node);
				void RightRotation(RBNode<T>*& p_node);
				void InsertFix(RBNode<T>*& p_node);
				void DeleteFix(RBNode<T>* p_root);
				void Inorder(RBNode<T>* p_node);
				void ReverseOrder(RBNode<T>* p_node);
				void SetColor(RBNode<T>*& p_node, Color p_color);
				Color GetColor(RBNode<T>*& p_node);
				int GetBlackHeight(RBNode<T>* p_node);
				int NodesCounter(RBNode<T>* p_toCount);
				int HeightCounter(RBNode<T>* p_toCount);
};

template <typename T>
RBTree<T>::RBTree() {}

template <typename T>
RBTree<T>::~RBTree()
{
				delete m_root;
				m_root = nullptr;
}

template <typename T>
void RBTree<T>::Add(int p_key, T p_value)
{
				if (Search(m_root, p_key))
							return;

				RBNode<T>* node = new RBNode<T>(p_key, p_value);
				m_root = InsertHelper(m_root, node);
				InsertFix(node);
}

template <typename T>
void RBTree<T>::Delete(int p_key)
{
				RBNode<T>* node = DeleteHelper(m_root, p_key);
				DeleteFix(node);
}

template <typename T>
void RBTree<T>::Display()
{
				Inorder(m_root);
				std::cout << std::endl;
}

template <typename T>
void RBTree<T>::ReverseDisplay()
{
				ReverseOrder(m_root);
				std::cout << std::endl;
}

template <typename T>
int RBTree<T>::Count()
{
				return NodesCounter(m_root);
}

template <typename T>
int RBTree<T>::GetHeight()
{
				return HeightCounter(m_root);
}

template <typename T>
RBNode<T>* RBTree<T>::FindMin(RBNode<T>* p_root)
{
				RBNode<T>* node = p_root;
				while(node->left)
				{
								node = node->left;
				}
				return node;
}

template <typename T>
RBNode<T>* RBTree<T>::FindMax(RBNode<T>* p_root)
{
				RBNode<T>* node = p_root;
				while (node->right)
				{
								node = node->right;
				}
				return node;
}

template <typename T>
RBNode<T>* RBTree<T>::InsertHelper(RBNode<T>*& p_root, RBNode<T>*& p_node)
{
				if (!p_root)
								return p_node;

				if (p_node->key < p_root->key) 
				{
								p_root->left = InsertHelper(p_root->left, p_node);
								p_root->left->parent = p_root;
				}
				else if (p_node->key > p_root->key) 
				{
								p_root->right = InsertHelper(p_root->right, p_node);
								p_root->right->parent = p_root;
				}
				return p_root;
}

template <typename T>
RBNode<T>* RBTree<T>::DeleteHelper(RBNode<T>*& p_root, int p_key)
{
				if (p_root == nullptr)
								return p_root;

				if (p_key < p_root->key)
								return DeleteHelper(p_root->left, p_key);

				if (p_key > p_root->key)
								return DeleteHelper(p_root->right, p_key);

				if (p_root->left == nullptr || p_root->right == nullptr)
								return p_root;

				RBNode<T> *temp = FindMin(p_root->right);
				p_root->value = temp->value;
				p_root->key = temp->key;
				return DeleteHelper(p_root->right, temp->key);
}

template <typename T>
RBNode<T>* RBTree<T>::Search(RBNode<T>* p_toSearch, int p_key)
{
				if (!p_toSearch)
								return nullptr;

				if (p_key == p_toSearch->key)
								return p_toSearch;

				if (p_toSearch->key > p_key)
				{
								return Search(p_toSearch->left, p_key);
				}
					return Search(p_toSearch->right, p_key);
}

template <typename T>
void RBTree<T>::LeftRotation(RBNode<T>*& p_node)
{
				RBNode<T>* right_child = p_node->right;
				p_node->right = right_child->left;

				if (p_node->right != nullptr)
								p_node->right->parent = p_node;

				right_child->parent = p_node->parent;

				if (p_node->parent == nullptr)
								m_root = right_child;
				else if (p_node == p_node->parent->left)
								p_node->parent->left = right_child;
				else
								p_node->parent->right = right_child;

				right_child->left = p_node;
				p_node->parent = right_child;
}

template <typename T>
void RBTree<T>::RightRotation(RBNode<T>*& p_node)
{
				RBNode<T>* left_child = p_node->left;
				p_node->left = left_child->right;

				if (p_node->left != nullptr)
								p_node->left->parent = p_node;

				left_child->parent = p_node->parent;

				if (p_node->parent == nullptr)
								m_root = left_child;
				else if (p_node == p_node->parent->left)
								p_node->parent->left = left_child;
				else
								p_node->parent->right = left_child;

				left_child->right = p_node;
				p_node->parent = left_child;
}

template <typename T>
void RBTree<T>::InsertFix(RBNode<T>*& p_node)
{
				RBNode<T>* parent = nullptr;
				RBNode<T>* grandparent = nullptr;
				while (p_node != m_root && GetColor(p_node) == RED && GetColor(p_node->parent) == RED) 
				{
								parent = p_node->parent;
								grandparent = parent->parent;
								if (parent == grandparent->left) 
								{
												RBNode<T>* uncle = grandparent->right;
												if (GetColor(uncle) == RED) 
												{
																SetColor(uncle, BLACK);
																SetColor(parent, BLACK);
																SetColor(grandparent, RED);
																p_node = grandparent;
												}
												else 
												{
																if (p_node == parent->right) 
																{
																				LeftRotation(parent);
																				p_node = parent;
																				parent = p_node->parent;
																}
																RightRotation(grandparent);
																std::swap(parent->color, grandparent->color);
																p_node = parent;
												}
								}
								else 
								{
												RBNode<T>* uncle = grandparent->left;
												if (GetColor(uncle) == RED) {
																SetColor(uncle, BLACK);
																SetColor(parent, BLACK);
																SetColor(grandparent, RED);
																p_node = grandparent;
												}
												else 
												{
																if (p_node == parent->left) {
																				RightRotation(parent);
																				p_node = parent;
																				parent = p_node->parent;
																}
																LeftRotation(grandparent);
																std::swap(parent->color, grandparent->color);
																p_node = parent;
												}
								}
				}
				SetColor(m_root, BLACK);
}

template <typename T>
void RBTree<T>::DeleteFix(RBNode<T>* p_root)
{
				if (!p_root)
								return;

				if (p_root == m_root) 
				{
								m_root = nullptr;
								return;
				}

				if (GetColor(p_root) == RED || GetColor(p_root->left) == RED || GetColor(p_root->right) == RED) 
				{
								RBNode<T>* child = p_root->left != nullptr ? p_root->left : p_root->right;

								if (p_root == p_root->parent->left) 
								{
												p_root->parent->left = child;
												if (child)
																child->parent = p_root->parent;
												SetColor(child, BLACK);
												delete (p_root);
								}
								else 
								{
												p_root->parent->right = child;
												if (child)
																child->parent = p_root->parent;
												SetColor(child, BLACK);
												delete (p_root);
								}
				}
				else 
				{
								RBNode<T> *sibling = nullptr;
								RBNode<T> *parent = nullptr;
								RBNode<T> *ptr = p_root;
								SetColor(ptr, DOUBLEBLACK);
								while (ptr != m_root && GetColor(ptr) == DOUBLEBLACK) 
								{
												parent = ptr->parent;
												if (ptr == parent->left) 
												{
																sibling = parent->right;
																if (GetColor(sibling) == RED) 
																{
																				SetColor(sibling, BLACK);
																				SetColor(parent, RED);
																				LeftRotation(parent);
																}
																else 
																{
																				if (GetColor(sibling->left) == BLACK && GetColor(sibling->right) == BLACK) 
																				{
																								SetColor(sibling, RED);
																								if (GetColor(parent) == RED)
																												SetColor(parent, BLACK);
																								else
																												SetColor(parent, DOUBLEBLACK);
																								ptr = parent;
																				}
																				else 
																				{
																								if (GetColor(sibling->right) == BLACK) 
																								{
																												SetColor(sibling->left, BLACK);
																												SetColor(sibling, RED);
																												RightRotation(sibling);
																												sibling = parent->right;
																								}
																								SetColor(sibling, parent->color);
																								SetColor(parent, BLACK);
																								SetColor(sibling->right, BLACK);
																								LeftRotation(parent);
																								break;
																				}
																}
												}
												else 
												{
																sibling = parent->left;
																if (GetColor(sibling) == RED) 
																{
																				SetColor(sibling, BLACK);
																				SetColor(parent, RED);
																				RightRotation(parent);
																}
																else 
																{
																				if (GetColor(sibling->left) == BLACK && GetColor(sibling->right) == BLACK) 
																				{
																								SetColor(sibling, RED);
																								if (GetColor(parent) == RED)
																												SetColor(parent, BLACK);
																								else
																												SetColor(parent, DOUBLEBLACK);
																								ptr = parent;
																				}
																				else 
																				{
																								if (GetColor(sibling->left) == BLACK) 
																								{
																												SetColor(sibling->right, BLACK);
																												SetColor(sibling, RED);
																												LeftRotation(sibling);
																												sibling = parent->left;
																								}
																								SetColor(sibling, parent->color);
																								SetColor(parent, BLACK);
																								SetColor(sibling->left, BLACK);
																								RightRotation(parent);
																								break;
																				}
																}
												}
								}
								if (p_root == p_root->parent->left)
												p_root->parent->left = nullptr;
								else
												p_root->parent->right = nullptr;
								delete(p_root);
								SetColor(m_root, BLACK);
				}
}

template <typename T>
void RBTree<T>::Inorder(RBNode<T>* p_node)
{
				if (!p_node)
								return;

				Inorder(p_node->left);
				if (p_node->color == RED)
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: RED" <<"]" << std::endl;
				}
				else if(p_node->color == BLACK)
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: BLACK" << "]" << std::endl;
				}
				else
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: DOUBLE_BLACK" << "]" << std::endl;
				}
				Inorder(p_node->right);
}

template <typename T>
void RBTree<T>::ReverseOrder(RBNode<T>* p_node)
{
				if (!p_node)
								return;

				ReverseOrder(p_node->right);
				if (p_node->color == RED)
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: RED" << "]" << std::endl;
				}
				else if (p_node->color == BLACK)
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: BLACK" << "]" << std::endl;
				}
				else
				{
								std::cout << "[-Key: " << p_node->key << " -Value: " << p_node->value << " -Color: DOUBLE_BLACK" << "]" << std::endl;
				}
				ReverseOrder(p_node->left);
}

template <typename T>
void RBTree<T>::SetColor(RBNode<T>*& p_node, Color p_color)
{
				if(!p_node)
								return;

				p_node->color = p_color;
}

template <typename T>
Color RBTree<T>::GetColor(RBNode<T>*& p_node)
{
				if (!p_node)
								return BLACK;

				return p_node->color;
}

template <typename T>
int RBTree<T>::GetBlackHeight(RBNode<T>* p_node)
{
				int blackheight = 0;
				while (p_node != nullptr) {
								if (getColor(p_node) == BLACK)
												blackheight++;
								p_node = p_node->left;
				}
				return blackheight;
}

template <typename T>
int RBTree<T>::NodesCounter(RBNode<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + NodesCounter(p_toCount->left) + NodesCounter(p_toCount->right);
}

template <typename T>
int RBTree<T>::HeightCounter(RBNode<T>* p_toCount)
{
				if (!p_toCount)
								return 0;

				return 1 + std::max(HeightCounter(p_toCount->left), HeightCounter(p_toCount->right));
}