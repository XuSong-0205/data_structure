#include <iostream>
#include <vector>
#include "LeftistHeap.h"
using std::vector;
using std::cin;
using std::cout;
using std::endl;

/**
 * @function : main
 * @brief    : ≤‚ ‘≥Ã–Ú
 * @input    : Œﬁ
 * @return   : int
 * @author   : sx
 * @date     : 2020-05-17
 */
int main()
{
	vector<int> arr1 = { 3, 10, 8, 21, 14, 17, 23, 26 };
	vector<int> arr2 = { 6, 12, 7, 18, 24, 37, 18, 33 };
	LeftistHeap<int> h1;
	LeftistHeap<int> h2;

	cout << "********* insert ************" << endl;
	for (int i = 0; i < 8; i++) {
		h1.insert(arr1.at(i));
		h2.insert(arr2.at(i));
	}

	const auto tf = [](bool x)noexcept {return x ? "true" : "false"; };

	cout << "********* print ************" << endl;
	cout << " the info in h1 as follows : " << endl;
	h1.print();
	cout << "h1 is a LeftistHeap : " << tf(h1.isLeftistHeap()) << endl;
	cout << " the info in h2 as follows : " << endl;
	cout << h2 << endl;
	cout << "h2 is a LeftistHeap : " << tf(h2.isLeftistHeap()) << endl;

	cout << "********* merge ************" << endl;
	h1.merge(h2);
	h1.print();

	cout << "********* deleteMin ************" << endl;
	int minItem;
	h1.deleteMin(minItem);
	cout << " the minmum value in h1 is " << minItem << endl;
	cout << "merge h1 h2 ,it is a LeftistHeap : " << tf(h1.isLeftistHeap()) << endl;

	cout << " done ." << endl;
	return 0;
}