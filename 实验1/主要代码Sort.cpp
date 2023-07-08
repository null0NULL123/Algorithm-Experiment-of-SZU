#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#include<algorithm>

// ���趼��������

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertSort(int* a, int n) {
	// [0, end]����  end+1λ�õ�ֵ����[0, end]����[0, end+1]����
	for (int j = 1; j <= n - 1; j++) { //n-1������
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];//�ƶ���¼
			i--;
		}
		a[i + 1] = key;//�ҵ�����λ�ò�����
	}
}

//void TestInsertSort() {
//	int a[] = { 3, 5, 2, 7, 8, 6, 1, 9, 4, 0 };
//	InsertSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void SelectSort(int* a, int n)
{
	for (int i = 0; i <= n - 2;i++) {
		int key = i; 
// ��ʣ�µ�������ѡ����С��Ԫ�ز�����λ�ø���key
		for (int j = i + 1; j <= n - 1; j++) {
			if (a[j] < a[key]) {
				key = j;
			}
		}
// ��δ���򲿷ֵ���СԪ�ػ������򲿷ֵ����λ��i
			swap(a[i], a[key]);
	}
}

//void TestSelectSort()
//{
//	int a[] = { 9, 3, 5, 2, 7, 8, 6, -1, 9, 4, 0 };
//	SelectSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void BubbleSort(int* a, int n) {
	for (int i = 0; i < n - 1; ++i) //n�����������ܹ�ɨ��n-1��
	{
		for (int j = 0; j < n - 1 - i; ++j) //ÿһ��ɨ�赽a[n-i-2]��a[n-i-1]�Ƚ�Ϊֹ����
		{
			if (a[j] > a[j + 1]) //��һλ����ǰһλ��С�Ļ����ͽ�����������λ�ã�����
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//void TestBubbleSort()
//{
//	int a[] = { 9, 3, 5, 2, 7, 8, 6, -1, 9, 4, 0 };
//	BubbleSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}
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

//void TestQuickSort() {
//	int a[] = { 3, 5, 2, 7, 8, 6, 1, 9, 4, 0 };
//	QuickSort(a, 0,sizeof(a) / sizeof(int)-1);
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void Merge(int *a,int *temp,int start,int mid,int end) {
	int i = start; 
	int j = mid + 1, k = start;
	while (i <= mid && j <= end) //�����ȽϽ���С�Ĳ���
	{
		if (a[i] < a[j])
			temp[k] = a[i++];
		else
			temp[k] = a[j++];
		k++;
	}

	while (i <= mid)//��midǰʣ��Ĳ���
		temp[k++] = a[i++];

	while (j <= end)//��mid��ʣ��Ĳ���
		temp[k++] = a[j++];
	
	// ������ȥ
	for (int i = start; i <= end; ++i)
		a[i] = temp[i];
}
void _MergeSort(int* a, int* tmp,int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) >> 1;
	// ���� [left, mid]�����[mid+1, right]����
	// ��ô���ǾͿ��Թ鲢��
	_MergeSort(a, tmp,left, mid );
	_MergeSort(a, tmp,mid + 1, right);
	Merge(a, tmp, left, mid, right);
	// �鲢
}

void MergeSort(int* a, int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, temp,0, n - 1);
	free(temp);
}

//void TestMergeSort()
//{
//	int a[] = { 10, 6, 7 ,1, 3, 9, 4, 2, 8 };
//	MergeSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

// ������������ܶԱ�
void TestOP()
{	//����һ�����������
	srand(time(0));
	//N�������ݹ�ģ
	const int N = 50000;
	int* a1 = new int[N];
	int* a2 = new int[N];
	int* a3 = new int[N];
	int* a4 = new int[N];
	int* a5 = new int[N];
	
	//5������һ�������Ʊ���
	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
	}
	//�ֱ�õ���ͬ�����㷨����Ҫ��ʱ��
	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	SelectSort(a2, N);
	int end2 = clock();

	int begin3 = clock();
	BubbleSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	MergeSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	QuickSort(a5, 0, N - 1);
	int end5 = clock();

	//�ֱ������ͬ�����㷨����Ҫ��ʱ�� 
	cout<<"InsertSort:"<<(double)(end1 - begin1) / CLOCKS_PER_SEC *1000<< "ms" << endl;
	cout << "SelectSort:" << (double)(end2 - begin2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "BubbleSort:" << (double)(end3 - begin3) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "MergeSort:" << (double)(end4 - begin4) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "QuickSort:" << (double)(end5 - begin5) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

int main()
{
	TestOP();
	return 0;
}