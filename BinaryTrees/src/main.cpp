#include <iostream>
#include "Huffman.h"
#include "RBT.h"
using namespace std;

int main() 
{
				/*
				RBTree<int> m_trees;
				m_trees.Add(30, 20);
				m_trees.Add(10, 20);
				m_trees.Add(1, 10);
				m_trees.Add(6000, 100);
				m_trees.Add(1, 30);
				
				m_trees.Display();
				m_trees.ReverseDisplay();

				m_trees.Delete(1);

				m_trees.Display();*/
				
				HuffmanTree m_tree;
				m_tree.CompressFromFile("../texts/hello.txt");
				m_tree.DecompressFromFile("../texts/Encodedstring.txt");
				m_tree.PrintFrequency();
				
				system("pause");
				return 0;
}