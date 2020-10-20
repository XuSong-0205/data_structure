#ifndef _TRIE_H_
#define _TRIE_H_
#include <vector>
#include <string>

/**
 * 此字典树只支持仅含小写字母的字符串！
 * 插入，查找的字符串长度过长(超过100)很可能发生栈溢出！
 */

class Trie
{
private:
	static constexpr int NODESIZE = 26;

	struct TrieNode
	{
		std::vector<TrieNode*> next;
		int count;
		bool isEnd;

		TrieNode() : next(NODESIZE, nullptr), count(0), isEnd(false) {}
	};

	TrieNode* root;

	TrieNode* clone(TrieNode* node)
	{
		if (node == nullptr) return nullptr;

		auto temp = new TrieNode;
		temp->isEnd = node->isEnd;
		for (int i = 0; i < NODESIZE; ++i) temp->next.at(i) = clone(node->next.at(i));
		return temp;
	}

	void makeEmpty(TrieNode*& node)
	{
		if (node != nullptr)
		{
			for (int i = 0; i < NODESIZE; ++i) makeEmpty(node->next.at(i));

			node->isEnd = false;
			delete node;
			node = nullptr;
		}
	}

	// 返回前缀字符串 str 在字典树 node 中的节点
	TrieNode* searchPrefix(TrieNode* node, const std::string& str)const
	{
		auto p = root;
		for (size_t i = 0; i < str.size() && p; ++i) p = p->next.at(str.at(i) - 'a');
		return p;
	}

	// 在字典树中以前序遍历查找所有以 pre 开始的字符串
	void prevOrder(TrieNode* node, std::vector<std::string>& ans, std::string& str)const
	{
		if (node == nullptr) return;

		for (int i = 0; i < NODESIZE; ++i)
		{
			auto p = node->next.at(i);
			if (p != nullptr)
			{
				str += ('a' + i);

				if (p->isEnd)
				{
					for (int i = 0; i < p->count; ++i) ans.push_back(str);
				}
				prevOrder(node->next.at(i), ans, str);
				str.pop_back();
			}
		}
	}

public:
	Trie() : root(new TrieNode) {}

	Trie(const Trie& t)
	{
		root = clone(t.root);
	}

	Trie(Trie&& t)
	{
		root = t.root;
		t.root = nullptr;
	}

	Trie& operator=(const Trie& t)
	{
		if (this != &t)
		{
			auto temp = clone(t.root);
			makeEmpty(root);
			root = temp;
		}

		return *this;
	}

	Trie& operator=(Trie&& t)
	{
		if (this != &t)
		{
			root = t.root;
			t.root = nullptr;
		}

		return* this;
	}

	~Trie()
	{
		delete root;
		root = nullptr;
	}

	// 在字典树中插入字符串 str 
	void insert(const std::string& str)
	{
		auto p = root;
		for (const auto& c : str)
		{
			if (p->next.at(c - 'a') == nullptr) p->next.at(c - 'a') = new TrieNode;
			p = p->next.at(c - 'a');
		}
		++(p->count);
		p->isEnd = true;
	}

	// 在字典树中删除字符串 str n 个，默认删除一个
	// 个数不足将全部删除
	void erase(const std::string& str, int num = 1)
	{
		std::vector<std::pair<TrieNode*, int>> sta;
		auto p = root;
		for (size_t i = 0; i < str.size() && p; ++i)
		{
			int c = str.at(i) - 'a';
			sta.push_back({ p, c});
			p = p->next.at(c);
		}

		if (p)
		{
			p->count = p->count > num ? p->count - num : 0;		// 减去 num 个

			if (!p->count)										// 若减到 0 ，向上一直删除节点
			{
				p->isEnd = false;								// 设置当前不是字符串结束节点

				while (p != root && !sta.empty())				// 最多到根节点结束，或栈为空
				{
					for (size_t i = 0; i < NODESIZE; ++i)
					{
						if (p->next.at(i)) return;				// 若此节点的 next 指针中有不为空的指针，直接返回
					}

					delete p;									// 到此处说明，该节点是子节点，可以删除
					p = nullptr;

					auto pair = sta.back();
					sta.pop_back();
					pair.first->next.at(pair.second) = nullptr;	// 取出父节点，修改对应指针

					p = pair.first;								// 指向父节点，向上继续
				}
			}
		}
	}

	// 在字典树中搜索是否存在字符串 str
	bool search(const std::string& str)const
	{
		auto p = searchPrefix(root, str);
		return p && p->isEnd;
			/*root;
		for (size_t i = 0; i < str.size() && p; ++i) p = p->next.at(str.at(i) - 'a');
		return p && p->isEnd;*/
	}

	// 搜索前缀字符串 str 是否在字典树中
	bool searchPrefix(const std::string& str)const
	{
		return searchPrefix(root, str);
	}

	// 查询字符串 str 出现的次数
	int count(const std::string& str)const
	{
		auto p = searchPrefix(root, str);
		return p ? p->count : 0;
	}

	// 返回字典树中以前缀字符串 pre 开始的所有字符串
	std::vector<std::string> perfix(std::string pre)const
	{
		std::vector<std::string> ans;
		auto node = searchPrefix(root, pre);
		for (int i = 0; node && i < node->count; ++i) ans.push_back(pre);
		prevOrder(node, ans, pre);
		return ans;
	}

	// 返回字典树中的所有字符串
	std::vector<std::string> allString()const
	{
		std::vector<std::string> ans;
		std::string str;
		prevOrder(root, ans, str);
		return ans;
	}
};

#endif // _TRIE_H_
