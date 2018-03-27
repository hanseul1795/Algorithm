#include "Huffman.h"
HuffmanTree::HuffmanTree() {}
HuffmanTree::~HuffmanTree() {}
void HuffmanTree::Compress(std::string p_str)
{
				CalculateFrequency(p_str);
				CompressCode(p_str.size());
				CodeToEncodedString(p_str);
}

void HuffmanTree::Decompress()
{
				m_decoded = DecompressCode(m_heapNodes.top(), m_encoded);
				std::cout << "Decoded Huffman Code:\n" << m_decoded << std::endl;
				std::cout << std::endl;
}

void HuffmanTree::PrintFrequency()
{
				PrintCodes(m_heapNodes.top(), m_decoded);
				std::cout << std::endl;
}

void HuffmanTree::CompressCode(int p_size)
{
				HuffNode* left = nullptr;
				HuffNode* right = nullptr;
				HuffNode* top = nullptr;
				for(std::map<char, int>::iterator v = m_frequency.begin(); v != m_frequency.end(); ++v)
				{
								m_heapNodes.push(new HuffNode(v->first, v->second));
				}
				while(m_heapNodes.size() != 1)
				{
								left = m_heapNodes.top();
								m_heapNodes.pop();
								right = m_heapNodes.top();
								m_heapNodes.pop();
								top = new HuffNode('$', left->frequency + right->frequency);
								top->left = left;
								top->right = right;
								m_heapNodes.push(top);
				}
				StoreCodes(m_heapNodes.top(), "");

}

void HuffmanTree::CalculateFrequency(std::string p_str)
{
				for(int i = 0; i < p_str.size(); ++i)
				{
								m_frequency[p_str[i]]++;
				}
}

void HuffmanTree::CodeToEncodedString(std::string p_str)
{
				for(auto i: p_str)
				{
								m_encoded += m_codes[i];
				}
				std::cout << "Encoded Huffman Code:\n" << m_encoded << std::endl;
				std::cout << std::endl;
}

void HuffmanTree::CompressFromFile(std::string p_path)
{
				std::ifstream toCompress;
				std::string temp;
				std::string str = "";
				toCompress.open(p_path, std::ios::in);
				if(!toCompress.good())
				{
								std::cout << "COULD NOT READ FILE FROM THE PATH: " << p_path << std::endl;
								return;
				}
				while(!toCompress.eof())
				{
								std::getline(toCompress, temp, '\0');
								str += temp;
				}
				toCompress.close();
				Compress(str);

				std::ofstream out;
				out.open("../texts/Encodedstring.txt", std::ios::out);
				if(!out.is_open())
				{
								std::cout << "UNABLE TO CREATE THE FILE: Encodedstring.txt" << std::endl;
								return;
				}
				out << m_encoded << std::endl;
				out.clear();
				out.close();
}

void HuffmanTree::DecompressFromFile(std::string p_path)
{
				std::ifstream toDecompress;
				std::string temp;
				std::string str = "";
				toDecompress.open(p_path, std::ios::in);
				if (!toDecompress.good())
				{
								std::cout << "COULD NOT READ FILE FROM THE PATH: " << p_path << std::endl;
								return;
				}
				while (!toDecompress.eof())
				{
								std::getline(toDecompress, temp, '\0');
								str += temp;
				}
				toDecompress.close();
				m_decoded = DecompressCode(m_heapNodes.top(), str);
				std::cout << "Decoded Huffman Code:\n" << m_decoded << std::endl;
				std::cout << std::endl;
}

std::string HuffmanTree::DecompressCode(HuffNode* p_root, std::string p_str)
{
				std::string toReturn = "";

				HuffNode* current = p_root;
				for(int i = 0; i < p_str.size(); ++i)
				{
								if(p_str[i] == '0')
								{
												current = current->left;
								}
								else
								{
												current = current->right;
								}
								if(!current->left && !current->right)
								{
												toReturn += current->data;
												current = p_root;
								}
				}
				return toReturn + '\0';
}

void HuffmanTree::StoreCodes(HuffNode* p_root, std::string p_str)
{
				if (!p_root)
							return;

				if(p_root->data != '$')
				{
								m_codes[p_root->data] = p_str;
				}
				StoreCodes(p_root->left, p_str + "0");
				StoreCodes(p_root->right, p_str + "1");
}

void HuffmanTree::PrintCodes(HuffNode* p_root, std::string p_str)
{
				if (!p_root)
							return;

				if(p_root->data != '$')
				{
								std::cout << p_root->data << ": " << p_root->frequency << std::endl;
				}
				PrintCodes(p_root->left, p_str + "0");
				PrintCodes(p_root->right, p_str + "1");
}
