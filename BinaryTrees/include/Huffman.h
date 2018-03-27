#pragma once
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct HuffNode
{
				char data;
				int frequency;
				HuffNode* left = nullptr;
				HuffNode* right = nullptr;
				HuffNode(char p_data, int p_frequency) : data(p_data), frequency(p_frequency)
				{}
				~HuffNode()
				{
								delete left;
								delete right;
								left = right = nullptr;
				}
};

struct Compare
{
				bool operator()(HuffNode* p_left, HuffNode* p_right) const
				{
								return p_left->frequency > p_right->frequency;
				}
};

class HuffmanTree
{
public:
				HuffmanTree();
				~HuffmanTree();	
				void CompressFromFile(std::string p_path);
				void DecompressFromFile(std::string p_path);
				void Compress(std::string p_str);
				void Decompress();
				void PrintFrequency();
private:
				std::string m_encoded;
				std::string m_decoded;
				std::map<char, std::string> m_codes;
				std::map<char, int> m_frequency;
				std::priority_queue<HuffNode*, std::vector<HuffNode*>, Compare> m_heapNodes;

				void StoreCodes(HuffNode* p_root, std::string p_str);
				void PrintCodes(HuffNode* p_root, std::string p_str);
				void CompressCode(int p_size);
				void CalculateFrequency(std::string p_str);
				void CodeToEncodedString(std::string p_str);
				std::string DecompressCode(HuffNode* p_root, std::string p_str);
};