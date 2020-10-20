#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"
using namespace std;

int main()
{
	vector<string> vec{ "a" , "aa" , "aaa" , "aba" , "aab" , "ac" , "ad" , "adc" , "sx" , "tree", "trees" };
	Trie trie;
	for (const auto& str : vec) trie.insert(str);
	for (const auto& str : vec) trie.insert(str);

	for (const auto& str : vec)
	{
		cout << "�ַ��� " << str << " �Ƿ����ֵ����� : " << boolalpha << trie.search(str) << endl;
	}

	cout << "\n�ַ��� aa �Ƿ����ֵ����� : " << boolalpha << trie.searchPrefix("aa") << endl;
	cout << "\n���ַ��� a Ϊǰ׺�������ַ����� : " << endl;
	auto ans = trie.perfix("a");
	for (const auto& str : ans) cout << str << " ";
	cout << endl;

	cout << "\n�ֵ����е������ַ���Ϊ : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;
	
	{
		cout << "\n�������캯������ : " << endl;
		auto trie1 = trie;
		cout << "�ַ��� sx �Ƿ����ֵ����� : " << boolalpha << trie1.search("sx") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "�ַ��� " << str << " �Ƿ����ֵ����� : " << boolalpha << trie1.search(str) << endl;
		}
	}

	{
		cout << "\n�ƶ����캯������ : " << endl;
		auto temp = trie;
		auto trie2 = std::move(temp);
		cout << "�ַ��� xs �Ƿ����ֵ����� : " << boolalpha << trie2.search("xs") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "�ַ��� " << str << " �Ƿ����ֵ����� : " << boolalpha << trie2.search(str) << endl;
		}
	}

	{
		cout << "\n������ֵ��������ز��� : " << endl;
		Trie trie3;
		trie3 = trie;
		cout << "�ַ��� tree �Ƿ����ֵ����� : " << boolalpha << trie3.search("tree") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "�ַ��� " << str << " �Ƿ����ֵ����� : " << boolalpha << trie3.search(str) << endl;
		}
	}

	{
		cout << "\n�ƶ���ֵ��������ز��� : " << endl;
		auto temp = trie;
		Trie trie4;
		trie4 = std::move(temp);
		cout << "�ַ��� treee �Ƿ����ֵ����� : " << boolalpha << trie4.search("treee") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "�ַ��� " << str << " �Ƿ����ֵ����� : " << boolalpha << trie4.search(str) << endl;
		}
	}


	// ɾ����������
	cout << "\nɾ���������� : " << endl;
	vector<string> vec1;
	for (size_t i = 0; i < vec.size(); i += 3) vec1.push_back(vec.at(i));
	cout << "��Ҫɾ�����ַ���Ϊ : " << endl;
	for (const auto& str : vec1) cout << str << " ";
	cout << endl;
	for (const auto& str : vec1) trie.erase(str);
	cout << "�ֵ��������е��ַ���Ϊ : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;

	vec1 = { "a", "aa", "aa", "aab", "sx", "sx" };
	cout << "\nɾ���ַ��� a a aa aa aab aab sx sx ���� : " << endl;
	for (const auto& str : vec1) trie.erase(str);
	cout << "�ֵ��������е��ַ���Ϊ : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;

	for (const auto& str : vec)
		cout << "�ַ���" << str << "���ֵĴ����� : " << trie.count(str) << endl;

	cout << "\n���з������Ѳ�����ϣ�" << endl;

	return 0;
}