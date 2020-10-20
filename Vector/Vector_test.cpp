#include"Vector.h"

int main()
{
	system("color 0A");

	constexpr int test_num_one = 500000;
	constexpr int test_num_two = 500000 * 10;
	constexpr int test_num_three = 500000 * 100;

	const auto Test = [](int num)
	{
		Vector<int> myvec;
		vector<int> stlvec;
		default_random_engine random;
		const uniform_int_distribution<int> range(0, 100000000);
		random.seed(time(nullptr) & 0xffffffff);

		cout << num << " �����������Կ�ʼ" << endl;
		cout << "������������������������������������������������������������������" << endl;
		cout << "|               |   push_back    |   find	 |   pop_back	 |" << endl;
		cout << "������������������������������������������������������������������" << endl;
		cout << "|     Vector    |";

		// ����
		time_t start_Vector = clock();
		for (int i = 0; i < num; ++i)
		{
			myvec.push_back(random());
		}
		time_t end_Vector = clock();
		const int myvecsize = myvec.size();
		cout << "   " << end_Vector - start_Vector << " ms	 |";

		cout << "      	 |";


		// ɾ��
		start_Vector = clock();
		for (int i = 0; i < num; ++i)
		{
			myvec.pop_back();
		}
		end_Vector = clock();
		const int myvecnowsize = myvec.size();
		cout << "   " << end_Vector - start_Vector << " ms	 |" << endl;

		cout << "������������������������������������������������������������������" << endl;
		cout << "|     vector    |";

		// STL vector
		// ����
		time_t start_vector = clock();
		for (int i = 0; i < num; ++i)
		{
			stlvec.push_back(random());
		}
		time_t end_vector = clock();
		const int stlvecsize = stlvec.size();
		cout << "   " << end_vector - start_vector << " ms	 |";

		cout << "          	 |";

		// ɾ��
		start_vector = clock();
		for (int i = 0; i < num; ++i)
		{
			stlvec.pop_back();
		}
		end_vector = clock();
		const int stlvecnowsize = stlvec.size();
		cout << "   " << end_vector - start_vector << " ms	 |" << endl;


		cout << "������������������������������������������������������������������" << endl;
		cout << "| myvec size/num|" << "   " << myvecsize << "/" << num << " 	 |"
			<< "  " << myvecnowsize << "/" << 0 << "    		 |" << endl;

		cout << "������������������������������������������������������������������" << endl;
		cout << "|stlvec size/num|" << "   " << stlvecsize << "/" << num << " 	 |"
			<< "  " << stlvecnowsize << "/" << 0 << "   		 |" << endl;

		cout << "������������������������������������������������������������������" << endl;
		cout << num << " �����������Խ���...\n" << endl;
	};

	Test(test_num_one);
	Test(test_num_two);
	Test(test_num_three);

	cout << "\n���в����ѽ��������س����˳�..." << endl;
	cin.get();
	return 0;
}
