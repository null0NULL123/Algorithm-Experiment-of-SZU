#include<iostream>
#include<cstdio>
#include<time.h>
using namespace std;

int Partition(int* arr, int low, int high) {
	int pivotkey = arr[low]; // �����еĵ�һ��Ԫ��������Ԫ��
	while (low < high) {// �ӱ�����˽�������м�ɨ��
		// ��������Ԫ��С��Ԫ���Ƶ��Ͷ�
		while (low < high&&arr[high] >= pivotkey) --high;
		arr[low] = arr[high];
		// ��������Ԫ�ش��Ԫ���Ƶ��߶�
		while (low < high&&arr[low] <= pivotkey) ++low;
		arr[high] = arr[low];
	}
	arr[low] = pivotkey; // ����Ԫ�ص�λ
	return low; // ��������λ��
}
void QuickSort(int* a, int low,int high) {
	if (low < high) {
		int pivotloc = Partition(a, low, high); // �����ӱ��������λ�����¼
		QuickSort(a, low, pivotloc - 1); // �Ե��ӱ�ݹ�����
		QuickSort(a, pivotloc + 1, high); // �Ը��ӱ�ݹ�����
	}
}
int* countingSort(int arr[], int count, int max) {
    int index = 0;
    int* tmpArr = (int*)malloc(max * sizeof(int));
    int* result = (int*)malloc(max * sizeof(int));

    for (int k = 0; k < max; k++) {
        tmpArr[k] = 0;
    }

    for (int i = 0; i < count; i++) {
        tmpArr[arr[i]]++;
    }
    for (int j = 0; j < max; j++) {
        while (tmpArr[j]) {
            result[index++] = j;
            tmpArr[j]--;
        }
    }
    free(tmpArr);
    tmpArr = NULL;
    return result;
}
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
// ���Կ��ٻ�������������
void TestOP()
{
	srand(time(0));
	const int N = 100000000;
	int* a = new int[N];

	for (int i = 0; i < N; ++i)
		a[i] = rand();

	int begin= clock();
    countingSort(a, N,32800);
	//QuickSort(a, 0, N - 1);
	int end = clock();

	cout<<"countingSort:"<<(double)(end - begin) / CLOCKS_PER_SEC *1000<< "ms" << endl;
	//cout << "QuickSort:" << (double)(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
int main() {
    TestOP();
    return 0;
}