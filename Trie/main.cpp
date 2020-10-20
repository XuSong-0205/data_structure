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
		cout << "×Ö·û´® " << str << " ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie.search(str) << endl;
	}

	cout << "\n×Ö·û´® aa ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie.searchPrefix("aa") << endl;
	cout << "\nÒÔ×Ö·û´® a ÎªÇ°×ºµÄËùÓÐ×Ö·û´®ÓÐ : " << endl;
	auto ans = trie.perfix("a");
	for (const auto& str : ans) cout << str << " ";
	cout << endl;

	cout << "\n×ÖµäÊ÷ÖÐµÄËùÓÐ×Ö·û´®Îª : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;
	
	{
		cout << "\n¿½±´¹¹Ôìº¯Êý²âÊÔ : " << endl;
		auto trie1 = trie;
		cout << "×Ö·û´® sx ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie1.search("sx") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "×Ö·û´® " << str << " ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie1.search(str) << endl;
		}
	}

	{
		cout << "\nÒÆ¶¯¹¹Ôìº¯Êý²âÊÔ : " << endl;
		auto temp = trie;
		auto trie2 = std::move(temp);
		cout << "×Ö·û´® xs ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie2.search("xs") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "×Ö·û´® " << str << " ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie2.search(str) << endl;
		}
	}

	{
		cout << "\n¿½±´¸³ÖµÔËËã·ûÖØÔØ²âÊÔ : " << endl;
		Trie trie3;
		trie3 = trie;
		cout << "×Ö·û´® tree ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie3.search("tree") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "×Ö·û´® " << str << " ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie3.search(str) << endl;
		}
	}

	{
		cout << "\nÒÆ¶¯¸³ÖµÔËËã·ûÖØÔØ²âÊÔ : " << endl;
		auto temp = trie;
		Trie trie4;
		trie4 = std::move(temp);
		cout << "×Ö·û´® treee ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie4.search("treee") << endl;
		cout << endl;

		for (const auto& str : vec)
		{
			cout << "×Ö·û´® " << str << " ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ : " << boolalpha << trie4.search(str) << endl;
		}
	}


	// É¾³ý·½·¨²âÊÔ
	cout << "\nÉ¾³ý·½·¨²âÊÔ : " << endl;
	vector<string> vec1;
	for (size_t i = 0; i < vec.size(); i += 3) vec1.push_back(vec.at(i));
	cout << "½«ÒªÉ¾³ýµÄ×Ö·û´®Îª : " << endl;
	for (const auto& str : vec1) cout << str << " ";
	cout << endl;
	for (const auto& str : vec1) trie.erase(str);
	cout << "×ÖµäÊ÷ÖÐËùÓÐµÄ×Ö·û´®Îª : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;

	vec1 = { "a", "aa", "aa", "aab", "sx", "sx" };
	cout << "\nÉ¾³ý×Ö·û´® a a aa aa aab aab sx sx ²âÊÔ : " << endl;
	for (const auto& str : vec1) trie.erase(str);
	cout << "×ÖµäÊ÷ÖÐËùÓÐµÄ×Ö·û´®Îª : " << endl;
	for (const auto& str : trie.allString()) cout << str << " ";
	cout << endl;

	for (const auto& str : vec)
		cout << "×Ö·û´®" << str << "³öÏÖµÄ´ÎÊýÊÇ : " << trie.count(str) << endl;

	cout << "\nËùÓÐ·½·¨¾ùÒÑ²âÊÔÍê±Ï£¡" << endl;

	return 0;
}