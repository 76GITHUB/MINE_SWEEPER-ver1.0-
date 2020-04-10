#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

struct Player { //�÷��̾�Ŀ�� ��ǥ
	int x, y;
};

void gotoxy(int x, int y){
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool check(int n, int m, int x, int y) { //���ڸ� ���ڻ�����
	if (x >= 0 && x < n) {
		if (y >= 0 && y < m) { return true; }
		else { return false; }
	}
	else { return false; }
}

void GameOver(char **r,char **map,int n, int m) { //�й�� ������ ���ڸ� �����ֱ�����
	system("cls");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (r[i][j] == '*') { cout << r[i][j] << " "; }
			else { cout << map[i][j] << " "; }
		}
		cout << endl;
	}
}

void Status(int i, int nan) { //���ӻ��� 
	gotoxy(60, 8);
	cout << "W:��, S:��, A:��, D:��, K:����, L:���/?";
	if (nan == 1) {
		gotoxy(60, 1);
		cout << "level: ����";
	}
	else if (nan == 2) {
		gotoxy(60, 1);
		cout << "level: ����";
	}
	else if (nan == 3) {
		gotoxy(60, 1);
		cout << "level: ���";
	}
	gotoxy(60, 2);
	cout << "STATUS:";
	if (i == 0) { //������
		gotoxy(61, 5);
		cout << "'";
		gotoxy(63, 5);
		cout << "'";
		gotoxy(62, 6);
		cout << "_";
	}
	else if (i == 1) { //�¸�
		gotoxy(61, 5);
		cout << "^";
		gotoxy(63, 5);
		cout << "^";
		gotoxy(62, 6);
		cout << "_";
		gotoxy(60, 3);
		cout << "WIN";
	}
	else if (i == 2) { //�й�
		gotoxy(61, 5);
		cout << "x";
		gotoxy(63, 5);
		cout << "x";
		gotoxy(62, 6);
		cout << "_";
		gotoxy(60, 3);
		cout << "YOU DIED";
	}
}

void OpenMap(char **r, char **map, int n, int m, int cx, int cy) { //���ڰ� �ƴѰ� �������� �ʿ���
	if (r[cy][cx] - '0'> 0 && r[cy][cx] - '0' <=9){
		map[cy][cx] = r[cy][cx];
		return;
	}

	else if (r[cy][cx] - '0' == 0) {	
		map[cy][cx] = '0';
		if (check(n, m, cy - 1, cx - 1)) { if (map[cy-1][cx-1]!='0') { OpenMap(r, map, n, m, cx - 1, cy - 1); } } 
		if (check(n, m, cy - 1, cx)) { if (map[cy - 1][cx] != '0') { OpenMap(r, map, n, m, cx, cy - 1); } } 
		if (check(n, m, cy - 1, cx + 1)) {  if (map[cy - 1][cx + 1] != '0') { OpenMap(r, map, n, m, cx + 1, cy - 1); } } 
		if (check(n, m, cy, cx - 1)) { if (map[cy][cx - 1] != '0') { OpenMap(r, map, n, m, cx - 1, cy); } } 
		if (check(n, m, cy, cx + 1)) { if (map[cy][cx + 1] != '0') { OpenMap(r, map, n, m, cx + 1, cy); } } 
		if (check(n, m, cy + 1, cx - 1)) { if (map[cy + 1][cx - 1] != '0'){ OpenMap(r, map, n, m, cx - 1, cy + 1); } } 
		if (check(n, m, cy + 1, cx)) { if (map[cy + 1][cx] != '0') { OpenMap(r, map, n, m, cx, cy + 1); } } 
		if (check(n, m, cy + 1, cx + 1)) { if (map[cy + 1][cx + 1] != '0') { OpenMap(r, map, n, m, cx + 1, cy + 1); } } 
	}
}

bool cmp(pair<int, string> &p1, pair<int, string> &p2) {
	if (p1.first == p2.first) {
		if (p1.second[0] == p2.second[0]) { return p1.second < p2.second; }
		else { return p1.second[0] < p2.second[0]; }
	}
	else { return p1.first < p2.first; }
}

void RecordE(int time) { //�������̵� ��� ��Ͽ�
	FILE *open = fopen("recordE.txt", "r");
	vector<pair<int, string>> v;
	int t;
	char buf[100];
	if (open != NULL) { //������ ����� ����� �ִٸ� ���̹ݿ�
		while (1) {
			fscanf(open, "%d %s", &t, buf);
			if (feof(open)) { break; }
			v.push_back(make_pair(t, buf));
		}
		fclose(open);
	}
	char name[100];
	system("cls");
	cout << "level: ����" << endl;
	cout << "����� ���:" << time << "��" << endl;
	cout << "�̸��� �Է��� �ּ���:";
	cin >> name;
	v.push_back(make_pair(time, name));
	sort(v.begin(), v.end(), cmp); //��� ����
	FILE *write = fopen("recordE.txt", "w");
	if (write != NULL) {
		for (int i = 0; i < v.size(); i++) {
			if (i == 10) { break; } //10�������� ���
			strcpy(buf, v[i].second.c_str());
			fprintf(write, "%d %s\n",v[i].first, buf);
		}
	}
	fclose(write);
	cout << "��� �Ϸ�" << endl;
	system("pause");
}

void RecordM(int time) { //���볭�̵� ��ŷ ��Ͽ�
	FILE *open = fopen("recordM.txt", "r");
	vector<pair<int, string>> v;
	int t;
	char buf[100];
	if (open != NULL) { //������ ����� ����� �ִٸ� ���̹ݿ�
		while (1) {
			fscanf(open, "%d%s", &t, buf);
			if (feof(open)) { break; }
			v.push_back(make_pair(t, buf));
		}
		fclose(open);
	}
	char name[100];
	system("cls");
	cout << "level: ����" << endl;
	cout << "����� ���:" << time << "��" << endl;
	cout << "�̸��� �Է��� �ּ���:";
	cin >> name;
	v.push_back(make_pair(time, name));
	sort(v.begin(), v.end(), cmp); //��� ����

	FILE *write = fopen("recordM.txt", "w");
	if (write != NULL) {
		for (int i = 0; i < v.size(); i++) {
			if (i == 10) { break; } //10�������� ���
			strcpy(buf, v[i].second.c_str());
			fprintf(write, "%d %s\n", v[i].first, buf);
		}
	}
	fclose(write);
	cout << "��� �Ϸ�" << endl;
	system("pause");
}

void RecordH(int time) { //������̵� ��ŷ��Ͽ�
	FILE *open = fopen("recordH.txt", "r");
	vector<pair<int, string>> v;
	int t;
	char buf[100];
	if (open != NULL) { //������ ����� ����� �ִٸ� ���̹ݿ�
		while (1) {
			fscanf(open, "%d %s", &t, buf);
			if (feof(open)) { break; }
			v.push_back(make_pair(t, buf));
		}
		fclose(open);
	}
	char name[100];
	system("cls");
	cout << "level: ���" << endl;
	cout << "����� ���:" << time << "��" << endl;
	cout << "�̸��� �Է��� �ּ���:";
	cin >> name;
	v.push_back(make_pair(time, name));
	sort(v.begin(), v.end(), cmp); //��� ����

	FILE *write = fopen("recordH.txt", "w");
	if (write != NULL) {
		for (int i = 0; i < v.size(); i++) {
			if (i == 10) { break; } //10�������� ���
			strcpy(buf, v[i].second.c_str());
			fprintf(write, "%d %s\n", v[i].first, buf);
		}
	}
	fclose(write);
	cout << "��� �Ϸ�" << endl;
	system("pause");
}

int main() {
	srand((unsigned int)time(NULL));
	int nan; //���̵�
	int n, m;// ��, ��
	char **rmap; //������
	char **map; //�÷��̾ ���Ե� ��
	int zr; //���ڰ���
	int zx, zy; //���ڸ� ������
	int i = 0; //���ڰ� �� ä�����°� Ȯ�ο�
	Player p;
	p.x = 0, p.y = 0; //�÷��̾� ������ǥ;
	bool lose;
	bool win;
	clock_t start, end;
	start = clock();
	while (1) {
		cout << "=========���� ã��========[���̵� ����]" << endl;
		cout << "1.���� 2.���� 3.��� 4.��������" << endl;
		cout << "�Է�:";
		cin >> nan;
		if (nan < 1 || nan>4) { continue; }
		if (nan == 1) { n = 10, m = 10; zr = 15; }
		else if (nan == 2) { n = 15, m = 15; zr = 25; }
		else if (nan == 3) { n = 15, m = 25; zr = 50; }
		else if (nan == 4) {
			int t;
			int s; //����
			char n[100];
			for (int i = 0; i < 3; i++) {
				s = 1;
				system("cls");
				if (i == 0) {
					FILE *read = fopen("recordE.txt", "r");
					cout << "==========���� ���=============" << endl;
					if (read != NULL) {
						while (1) {
							fscanf(read, "%d %s", &t, n);
							if (feof(read)) { break; }
							cout << s++ << ". " << n << "\t" << t << "��" <<endl;
						}
						fclose(read);
					}
					else { cout<<"��Ͼ���" << endl; }
					system("pause");
				}
				else if (i == 1) {
					FILE *read = fopen("recordM.txt", "r");
					cout << "==========���� ���=============" << endl;
					if (read != NULL) {
						while (1) {
							fscanf(read, "%d %s", &t, n);
							if (feof(read)) { break; }
							cout << s++ << ". " << n << "\t" << t << "��" << endl;
						}
						fclose(read);
					}
					else { cout << "��Ͼ���" << endl; }
					system("pause");
				}
				else if (i == 2) {
					FILE *read = fopen("recordH.txt", "r");
					cout << "==========��� ���=============" << endl;
					if (read != NULL) {
						while (1) {
							fscanf(read, "%d %s", &t, n);
							if (feof(read)) { break; }
							cout << s++ << ". " << n << "\t" << t << "��" << endl;
						}
						fclose(read);
					}
					else { cout << "��Ͼ���" << endl; }
					system("pause");
				}
			}
			system("cls");
			continue;
		}
		rmap = new char*[n];
		for (int i = 0; i < n; i++)
			rmap[i] = new char[m];

		map = new char*[n];
		for (int i = 0; i < n; i++)
			map[i] = new char[m];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				rmap[i][j] = '.';

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				map[i][j] = '.';

		while (1) {
			zx = rand() % n;
			zy = rand() % m;
			if (rmap[zx][zy] == '*') { continue; }
			else { rmap[zx][zy] = '*'; i++; }
			if (i == zr) { break; }
		}

		int count;
		for (int i = 0; i < n; i++) { //���ڸ� ����(���� ��)
			for (int j = 0; j < m; j++) {
				count = 0;
				if (rmap[i][j] == '*') { continue; }
				if (check(n, m, i - 1, j - 1)) { if (rmap[i - 1][j - 1] == '*') { count++; } }
				if (check(n, m, i - 1, j)) { if (rmap[i - 1][j] == '*') { count++; } }
				if (check(n, m, i - 1, j + 1)) { if (rmap[i - 1][j + 1] == '*') { count++; } }
				if (check(n, m, i, j - 1)) { if (rmap[i][j - 1] == '*') { count++; } }
				if (check(n, m, i, j + 1)) { if (rmap[i][j + 1] == '*') { count++; } }
				if (check(n, m, i + 1, j - 1)) { if (rmap[i + 1][j - 1] == '*') { count++; } }
				if (check(n, m, i + 1, j)) { if (rmap[i + 1][j] == '*') { count++; } }
				if (check(n, m, i + 1, j + 1)) { if (rmap[i + 1][j + 1] == '*') { count++; } }
				rmap[i][j] = count + '0';
			}
		}

		FILE * write = fopen("map.txt", "w");
		if (write != NULL) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					fprintf(write, "%c ", rmap[i][j]);
				}
				fputs("\n", write);
			}
		}

		fclose(write);
		char key;
		while (1) {
			system("cls");
			lose = false;
			win = true;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << map[i][j]<<" ";
				}
				cout << endl;
			}
			Status(0, nan);
			gotoxy(p.x, p.y);
			cout << "$";
				key = _getch();
				switch (key)
				{
				case 'w':
				case 'W':
					if (p.y == 0) { break; }
					p.y--;
					break;
				case 's':
				case 'S':
					if (p.y == n-1) { break; }
					p.y++;
					break;
				case 'a':
				case 'A':
					if (p.x == 0) { break; }
					p.x-=2;
					break;
				case 'd':
				case 'D':
					if (p.x == (m - 1)*2) { break; }
					p.x+=2;
					break;
				case 'k':
				case 'K':
					if (rmap[p.y][p.x / 2] == '*' && map[p.y][p.x/2]=='.') { GameOver(rmap, map, n, m); lose = true; break; }
					else { if (map[p.y][p.x / 2] == '.') { OpenMap(rmap, map, n, m, p.x / 2, p.y); break; } }
					break;
				case 'l':
				case 'L': //�÷���, ?
					if (map[p.y][p.x / 2] == '.') { map[p.y][p.x / 2] = 'F'; }
					else if (map[p.y][p.x / 2] == 'F') { map[p.y][p.x / 2] = '?'; }
					else if (map[p.y][p.x / 2] == '?') { map[p.y][p.x / 2] = '.'; }
					break;
			}
				if (lose) { break; } //���ڸ� �������ȴٸ� ���ӿ��� ��
				for (int i = 0; i < n; i++) //���ڰ� �ƴ� ��� ������ �����ƴ��� üũ�ϱ�����
					for (int j = 0; j < m; j++) 
						if (rmap[i][j] != '*') { if (map[i][j] == '.') { win = false; } }
				
				if (win) { break; } //�¸�		
		}
		break;
	}
	for (int i = 0; i < n; i++)
		delete[] rmap[i];
	delete[] rmap;

	for (int i = 0; i < n; i++)
		delete[] map[i];
	delete[] map;
	if (lose) { Status(2, nan); exit(-1); }
	if (win) { 
		Status(1, nan); system("pause"); end = clock();
		if(nan == 1) { RecordE((int)((end - start) / CLOCKS_PER_SEC)); }
		else if(nan ==2) { RecordM((int)((end - start) / CLOCKS_PER_SEC)); }
		else if(nan ==3) { RecordH((int)((end - start) / CLOCKS_PER_SEC)); }
	    exit(-1); }
	cout << endl;
}