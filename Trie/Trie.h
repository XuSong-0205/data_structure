#ifndef _TRIE_H_
#define _TRIE_H_
#include <vector>
#include <string>

/**
 * ���ֵ���ֻ֧�ֽ���Сд��ĸ���ַ�����
 * ���룬���ҵ��ַ������ȹ���(����100)�ܿ��ܷ���ջ�����
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

	// ����ǰ׺�ַ��� str ���ֵ��� node �еĽڵ�
	TrieNode* searchPrefix(TrieNode* node, const std::string& str)const
	{
		auto p = root;
		for (size_t i = 0; i < str.size() && p; ++i) p = p->next.at(str.at(i) - 'a');
		return p;
	}

	// ���ֵ�������ǰ��������������� pre ��ʼ���ַ���
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

	// ���ֵ����в����ַ��� str 
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

	// ���ֵ�����ɾ���ַ��� str n ����Ĭ��ɾ��һ��
	// �������㽫ȫ��ɾ��
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
			p->count = p->count > num ? p->count - num : 0;		// ��ȥ num ��

			if (!p->count)										// ������ 0 ������һֱɾ���ڵ�
			{
				p->isEnd = false;								// ���õ�ǰ�����ַ��������ڵ�

				while (p != root && !sta.empty())				// ��ൽ���ڵ��������ջΪ��
				{
					for (size_t i = 0; i < NODESIZE; ++i)
					{
						if (p->next.at(i)) return;				// ���˽ڵ�� next ָ�����в�Ϊ�յ�ָ�룬ֱ�ӷ���
					}

					delete p;									// ���˴�˵�����ýڵ����ӽڵ㣬����ɾ��
					p = nullptr;

					auto pair = sta.back();
					sta.pop_back();
					pair.first->next.at(pair.second) = nullptr;	// ȡ�����ڵ㣬�޸Ķ�Ӧָ��

					p = pair.first;								// ָ�򸸽ڵ㣬���ϼ���
				}
			}
		}
	}

	// ���ֵ����������Ƿ�����ַ��� str
	bool search(const std::string& str)const
	{
		auto p = searchPrefix(root, str);
		return p && p->isEnd;
			/*root;
		for (size_t i = 0; i < str.size() && p; ++i) p = p->next.at(str.at(i) - 'a');
		return p && p->isEnd;*/
	}

	// ����ǰ׺�ַ��� str �Ƿ����ֵ�����
	bool searchPrefix(const std::string& str)const
	{
		return searchPrefix(root, str);
	}

	// ��ѯ�ַ��� str ���ֵĴ���
	int count(const std::string& str)const
	{
		auto p = searchPrefix(root, str);
		return p ? p->count : 0;
	}

	// �����ֵ�������ǰ׺�ַ��� pre ��ʼ�������ַ���
	std::vector<std::string> perfix(std::string pre)const
	{
		std::vector<std::string> ans;
		auto node = searchPrefix(root, pre);
		for (int i = 0; node && i < node->count; ++i) ans.push_back(pre);
		prevOrder(node, ans, pre);
		return ans;
	}

	// �����ֵ����е������ַ���
	std::vector<std::string> allString()const
	{
		std::vector<std::string> ans;
		std::string str;
		prevOrder(root, ans, str);
		return ans;
	}
};

#endif // _TRIE_H_
