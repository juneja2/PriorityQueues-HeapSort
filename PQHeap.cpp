
#include <iostream>
#include <random>
#include <ctime>

struct S {
	double x;
	int n;
	char c;

	S(double x = 0, int n = 0, char c = '\0') : x(x), n(n), c(c) {} // Intializer list
};

bool sbb0(const S &a, const S &b);
bool sbb1(const S &a, const S &b);

void show(const S ar[], unsigned els);

void heapify(S bt[], unsigned els, bool(*sbb)(const S &a, const S &b));
void demote(S ar[], unsigned pos, unsigned els, bool(*sbb)(const S &a, const S &b));
unsigned larger(S ar[], unsigned pos1, unsigned pos2, bool(*sbb)(const S &a, const S &b));

void heapSort(S ar[], unsigned els, bool(*sbb)(const S &a, const S &b));

using namespace std;
const int sizeOfbt = 11;

int main() {
	srand((unsigned)time(NULL)); // Provides seed for random so we get different value each time we execute random

	S bt[sizeOfbt];
	bt[0] = {}; // We leave the first element of the array so 
				// that it makes the math easier to find the child and parent

	for (int i = 1; i < sizeOfbt; i++) {
		bt[i] = { (double)rand() / rand(), rand() / 1000, (char)(rand() / 256) };
	} // Gives me random struct

	show(bt, sizeOfbt);
	
	heapify(bt, sizeOfbt, sbb0);
	heapSort(bt, sizeOfbt, sbb0);
	show(bt, sizeOfbt);
	
	heapify(bt, sizeOfbt, sbb1);
	heapSort(bt, sizeOfbt, sbb1);
	show(bt, sizeOfbt);

	return 0;
}
bool sbb0(const S &a, const S &b) {
	if (a.x > b.x)
		return true;
	else if (b.x > a.x)
		return false;
	else if (a.n < b.n)
		return true;
	else if (b.n < a.n)
		return false;
	else if (isdigit(a.c) && !isdigit(b.c))
		return true;
	else if (isdigit(b.c) && !isdigit(a.c))
		return false;
	else if (a.c > b.c)
		return true;
	else if (b.c > a.c)
		return false;
	
	// If none of the condition above are satisfied a is going to precede since a.x, a.b, a.c all are equal at that point
	return true;
}
bool sbb1(const S &a, const S &b) {
	if (a.n < b.n)
		return false;
	
	return true;
}

void show(const S ar[], unsigned els) {
	for (unsigned i = 1; i < els; i++)
		cout << "Pos = " << i <<" X = " << ar[i].x << " N = " << ar[i].n << " C = " << ar[i].c << endl;
	cout << endl;
}

void heapify(S bt[], unsigned els, bool(*sbb)(const S &a, const S &b)) {
	for (unsigned pos = (els - 1) / 2; pos > 0; pos--)
		demote(bt, pos, els, sbb); // Doesn't demote always checks if it needs to demote
}
void heapSort(S ar[], unsigned els, bool(*sbb)(const S &a, const S &b)) {
	while (els != 1){
		swap(ar[1], ar[--els]);
		demote(ar, 1, els, sbb);
	}

}
void demote(S ar[], unsigned pos, unsigned els, bool(*sbb)(const S &a, const S &b)) {
	unsigned left_child = 2 * pos;

	if (left_child < els) {
		if (left_child + 1 < els) {
			unsigned larger_child_index = larger(ar, left_child, left_child + 1, sbb);
			if (larger(ar, pos, larger_child_index, sbb) == larger_child_index) {
				swap(ar[pos], ar[larger_child_index]);
				demote(ar, larger_child_index, els, sbb);
			}
		}
		else {
			if (larger(ar, pos, left_child, sbb) == left_child) {
				swap(ar[pos], ar[left_child]);
				demote(ar, left_child, els, sbb);
			}
		}
	}
}
unsigned larger(S ar[], unsigned pos1, unsigned pos2, bool(*sbb)(const S &a, const S &b)) {
	return !sbb(ar[pos1], ar[pos2]) ? pos1 : pos2;
}
