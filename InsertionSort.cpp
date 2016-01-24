#include <iostream>
using namespace std;

int main()
{
	int size;
	cin >> size;

	int * arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		int value;
		cin >> value;
		arr[i] = value;
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
		{
			int temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << endl;
	}

    return 0;
}