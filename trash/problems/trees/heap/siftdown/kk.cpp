#include <iostream>
#include <vector>
using namespace std;

struct heap
{
	vector <int> arr;
	int size_heap;
	heap();
	void size();
	void read();
	void add_n_times();
	void get_int(int &n);
	void check_heap(int pos = 0);
	void swap_heap_up(int pos);
	void swap(int pos1, int pos2);
	void sub_n_times();
	int max_pos(int pos = 0);
	int check_heap_down(int pos = 0);
	void print();
	void print_value(int pos = 0);
};
int main() {
	heap A;
	A.sub_n_times();
	A.print();

	return 0;
}

heap::heap()
{
	size();
	read();
}

void heap::size()
{
	int temp = 0;
	cin >> temp;
	size_heap = temp;
}

void heap::read()
{
	for (int i = 0; i != size_heap; i++) {
		int temp = 0;
		cin >> temp;
		arr.push_back(temp);
	}
}

void heap::sub_n_times()
{
	int n = 0;
	get_int(n);
	for (int i = 0; i != n; i++) {
		int number = 0;
		int value = 0;
		get_int(number);
		get_int(value);
		arr[number - 1] -= value;
		//if (value != 0) {
			print_value(check_heap_down(number));
		//}
	}
}

int heap::max_pos(int pos)
{
	int& a = arr[pos - 1];
	int& b = arr[pos * 2 - 1];
	int& c = arr[pos * 2];
	int i = pos;
	if (a <= b && b < c) { 
		i = 2 * i + 1; 
	}
	else if (a <= c && c < b) {
		i = 2 * i;
	}
	else if (b < a && a < c) {
		i = 2 * i + 1; 
	}
	else if (c < a && a < b) { 
		i = 2 * i; 
	}
	return i;
}

int heap::check_heap_down(int pos)
{ 

	while (pos * 2 <= size_heap) {
		if (pos * 2 < size_heap) {
			int& a1 = arr[pos - 1];
			int& b1 = arr[pos * 2 - 1];
			int& c1 = arr[pos * 2];
			int a = pos;
			int b = pos * 2;
			int c = pos * 2 +1;
			if (a1 <= b1 && b1 < c1) { swap(a, c); pos = 2 * pos + 1; }
			else if (a1 <= c1 && c1 < b1) { swap(a, b); pos = 2 * pos; }
			else if (b1 < a1 && a1 < c1) { swap(a, c); pos = 2 * pos + 1; }
			else if (c1 < a1 && a1 < b1) { swap(a, b); pos = 2 * pos; }
			else
				break;
		}
		else {
			if (arr[pos - 1] < arr[pos * 2 - 1]) {
				swap(pos, pos * 2);
				pos = pos * 2;
			}
            else break;
			
		}
	}
	return pos;


}

void heap::add_n_times()
{
	int n = 0;
	get_int(n);
	for (int i = 0; i != n; i++) {
		int number = 0;
		int value = 0;
		get_int(number);
		get_int(value);
		arr[number - 1] += value;
		check_heap(number);
	}
}

void heap::get_int(int & n)
{
	int temp = 0;
	cin >> temp;
	n = temp;
}

void heap::check_heap(int pos)
{
	bool flag = true;
	while (flag) {
		flag = false;
		if (pos == 1) {
			cout << pos << endl;
			return;
		}
		if (arr[pos - 1] > arr[pos / 2 - 1]) {
			swap_heap_up(pos);
			flag = true;
			pos /= 2;
		}
	}
	cout << pos << endl;

}

void heap::swap_heap_up(int pos)
{
	int temp = arr[pos - 1];
	arr[pos - 1] = arr[pos / 2 - 1];
	arr[pos / 2 - 1] = temp;
}

void heap::print()
{
	int i = 0;
	for (; i != size_heap - 1; i++) {
		cout << arr[i] << " ";
	}
	cout << arr[i];
}

void heap::print_value(int pos)
{
	cout << pos << endl;
}

void heap::swap(int pos1, int pos2) {
	int pos3 = arr[pos1 - 1];
	arr[pos1 - 1] = arr[pos2 - 1];
	arr[pos2 - 1] = pos3;
}