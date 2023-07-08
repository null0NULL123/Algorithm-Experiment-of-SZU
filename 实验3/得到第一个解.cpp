#include <iostream>
#include <ctime>
using namespace std;

#define COLOR 15    //��ѡ��ɫ����
#define VERTEX 450     //����
#define EDGE 8169   //����

struct Vertex
{
	int color; //�õ���ѡ����ɫ
	int state[COLOR + 1];  //��ɫ״̬��1Ϊ��ѡ����1Ϊ����ѡ
	int choice;  //��ѡ��ɫ����������state��1������
	int degree;  //���ڵ������,���õ�Ķ�
	Vertex() {
		color = 0; //Ĭ�ϸö���û��ɫ
		for (int i = 0; i <= COLOR; ++i)
			state[i] = 1; //Ĭ�ϳ�ʼ��Ϊȫ����ɫ����ѡ
		choice = COLOR; //Ĭ�ϳ�ʼ��Ϊȫ����ɫ����ѡ
		degree = 0;  //Ĭ�ϳ�ʼ����Ϊ0
	}
};

int Map[VERTEX + 1][256];  //�ڽӱ�,Map[i][0]��ʾ��i���ڵ����ڽڵ��������Map[i][j]��ʾ��i���ڵ�ĵ�j�����ڽڵ㡣
long long sum = 0;   //��¼��ĸ���
clock_t startTime, endTime;//�뼶�����ʱ

bool check(Vertex* S, int current, int i) { //�����ڵ����顢��ǰ�ڵ����current������ѡ����ɫi
	for (int k = 1; k <= Map[current][0]; ++k) { //������ǰ�ڵ���������ڽڵ�
		int j = Map[current][k]; //j�Ǳ����������ڽڵ����
		if (S[j].color == 0 && S[j].state[i] == 1) { //������jΪ����ɫ�ڵ��ҿ�������ɫi
			S[j].state[i] = -current; //��ʹ�ö���j����ѡi�����ɫ
			S[j].choice--; //����j�Ŀ�ѡ��ɫ����-1
			if (!S[j].choice) { //������j�Ŀ�ѡ��ɫ����-1֮���Ϊ��0,����false
				return false;
			}
		}
	}
	return true; //�����ᵼ�³������ڶ�����ɫ��ѡ������򷵻�true
}

int getNext(Vertex* S) {//����MRH,���DH
	auto Min = COLOR;//��С�Ŀ�ѡ��ɫ����,��ʼ��Ϊ���
	int next = 0;
	for (int i = 1; i <= VERTEX; ++i) {
		if (!S[i].color) { //��δ��ɫ�ĵ����ҵ���һ��Ҫ��ɫ�ĵ�
			if (S[i].choice == Min) {
				if (S[i].degree > S[next].degree) {
					Min = S[i].choice; //�ڿ�ѡ��ɫ����С�Ľڵ���ѡ���������Ϊ��һ����Ҫ��ɫ�Ľڵ�
					next = i;
				}
			}
			else if (S[i].choice < Min) {//����Ѱ�ҿ�ѡ��ɫ����С�Ľڵ�
				Min = S[i].choice;
				next = i;
			}
		}
	}
	return next;
}

//���ĵĻ��ݺ���
int DFS(Vertex* S, int current, int count, int usedColor) { //count���Ѿ���ɫ�ĵ������
	if (count == VERTEX) { //����Ҷ�ӽڵ�,�ҵ�һ����ɫ����
		sum += S[current].choice;
		endTime = clock();
		cout << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		exit(1);
		return S[current].choice;
	}
	else {
		int s = 0;
		for (int i = 1; i <= COLOR; i++) {
			if (S[current].state[i] == 1) {
				int ss = 0;
				S[current].color = i;
				auto isNewColor = i > usedColor;
				if (check(S, current, i)) {
					if (isNewColor)
						ss = DFS(S, getNext(S), count + 1, usedColor + 1);
					else
						ss = DFS(S, getNext(S), count + 1, usedColor);
				}
			    //����
				S[current].color = 0;
				for (int k = 1; k <= Map[current][0]; ++k) {
					int j = Map[current][k];
					if (S[j].state[i] == -current) {
						S[j].choice++;
						S[j].state[i] = 1;
					}
				}
				//�ؼ���֦
				if (isNewColor) {
					s += ss * (COLOR - usedColor);
					sum += ss * (COLOR - usedColor - 1);
					break;
				}
				s += ss;
			}
		}
		if (sum > 1000000000) {
			endTime = clock();
			cout << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
			exit(1);
		}
		else
			return s;
	}
}

int main() {
	Vertex S[VERTEX + 1];
	FILE* fp = nullptr;
	cout << "����1����ʵ��Ҫ���и�����С��ͼ���ݣ�����2����450��5ɫ������3����450��15ɫ������4����450��25ɫ���ǵ�Ҫ��������ĺ궨�����޸���Ӧ����ɫ���������ͱ�����" << endl;
	int fileNumber;
	cin >> fileNumber;
	if (fileNumber == 1) {
		if ((fp = fopen("C:\\Users\\ASUS\\Desktop\\�㷨ʵ����\\��ͼ����\\smallMapExample.txt", "r")) == nullptr) { //���ļ�
			printf("δ���ҵ��ļ�!\n");
			exit(1);
		}
	}
	else if (fileNumber == 2) {
		if ((fp = fopen("C:\\Users\\ASUS\\Desktop\\�㷨ʵ����\\��ͼ����\\le450_5a - ����.txt", "r")) == nullptr) {
			printf("δ���ҵ��ļ�!\n");
			exit(1);
		}
	}
	else if (fileNumber == 3) {
		if ((fp = fopen("C:\\Users\\ASUS\\Desktop\\�㷨ʵ����\\��ͼ����\\le450_15b - ����.txt", "r")) == nullptr) {
			printf("δ���ҵ��ļ�!\n");
			exit(1);
		}
	}
	else {
		if ((fp = fopen("C:\\Users\\ASUS\\Desktop\\�㷨ʵ����\\��ͼ����\\le450_25a - ����.txt", "r")) == nullptr) {
			printf("δ���ҵ��ļ�!\n");
			exit(1);
		}
	}
	char ch;
	int u, v;
	for (int i = 1; i <= EDGE; i++) {
		fscanf(fp, "%c%d%d\n", &ch, &u, &v);
		Map[u][0]++;
		Map[u][Map[u][0]] = v;
		Map[v][0]++;
		Map[v][Map[v][0]] = u;
		S[u].degree++;
		S[v].degree++;
	}

	printf("�ɹ���ȡ�˵�ͼ����,���е�ͼ��ɫ~\n");
	fclose(fp);
	startTime = clock();//��ʱ��ʼ
	auto ans = DFS(S, 4, 1, 0);
	endTime = clock();//��ʱ����
	cout << "����ʱ��Ϊ:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	printf("��ĸ���:%d\n", ans);
	//cout << "sum:"<<sum << endl;
	return 0;
}
