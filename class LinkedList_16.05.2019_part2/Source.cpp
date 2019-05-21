#include"List.h"

int main() {
	List<int> l;
	//рассматриваем блок, где может возникнуть ошибка
	try {
		l.push_back(5);
		l.push_back(6);
		l.push_back(7);
		l.push_front(200);
		l.push_front(500);
		l.insert_by_pos(777, 3);
		//l.pop_front();
		//l.pop_back();

		l.dump();
		cout << endl;
		for (int i = l.getSize(); i > 0; i--)
			cout << l[i - 1] << endl;

		cout << endl << l.operator[](0) << endl;//the same as l[0]
		//cout << l[100] << endl;//после первой же ошибки программа прерывается
		cout << l[-3] << endl;
	}
	//catch (my_exception my_ex) {
	//	//cout << my_ex.what() << endl;
	//	cout << my_ex.ErrorCode() << endl;
	//}
	catch (out_of_range my_ex) {
		cout << my_ex.what() << endl;
	}

	List<int> l2(l);
	cout << "COPY" << endl;
	l2.dump();

	l.~List();//явно деструктор вызываем




	system("pause");
	return 0;
}