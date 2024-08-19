#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>
#include <string>
#include <conio.h>
#include "gotoxy.h"
#define UP 1
#define DOWN 2
#define SUBMIT 3
using namespace std;

class City {
    int price, villa, building, hotel; //���ð���
    int owner = 0;// ������
    string name; //�����̸�
    int x, y;
public:
    City(int p = 0, int a = 0, int b = 0, int c = 0, string n = 0, int d = 0, int e = 0) :price{ p }, villa{ a }, building{ b }, hotel{ c }, name{ n }, x{ d }, y{ e } {}   //������
    int getPrice() { return price; }
    int getvilla() { return villa; }
    int getbuilding() { return building; }
    int gethotel() { return hotel; }
    int getowner() { return owner; }
    int getx() { return x; }
    int gety() { return y; }
    string getName() { return name; }
    void setx(int d) { x = d; }
    void sety(int e) { y = e; }
    void setowner(int o) { owner = o; }
    void setPrice(int p) { price = p; }
    void setName(string n) { name = n; }
    void setvilla(int v) { villa = v; }
    void setbuilding(int b) { building = b; }
    void sethotel(int h) { hotel = h; }
    ~City() {}
};

class Player {
    int* pMymoney; //�������� ���� ��
    int* pMyplace; //������ ���� ��ġ
    int myland_p[50];//�� ������ ����
    int myland_xi[100]; //�� ������ x���ε��� ��
    int myland_yi[100]; //�� ������ y���ε��� ��
    int* city;
    int build_cnt[50];
    int c, citynum;
    string* mal; //������ mal
    int citycnt;
    string myland_name[50];
    int live;
    static int live_cnt;
    static int gibu;
    static int n;

public:
    Player() {
        pMymoney = new int{ 150 };
        pMyplace = new int{ 0 };
        city = new int[50];
        mal = new string{ 0 };
        c = 0;
        citynum = 0;
        live = 1;
    }
    int get_live() { return live; }
    int getMymoney() { return *pMymoney; }
    int getMyplace() { return *pMyplace; }
    string getMal() { return *mal; }
    void setMal(string m) { *mal = m; }
    int getmyland_p(int ab) {
        int j = 0;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == ab)
            {
                j = i; break;// ���� ���� ������ ���� ��ġ�� �ε��� ã��
            }
        };
        return myland_p[j];
    }
    void setMymoney(int m) { *pMymoney = m; }
    void setGibu(int m) { *pMymoney += m; }
    void setMyplace(int pl) {
        *pMyplace += pl;
        if (*pMyplace >= 32) {
            *pMyplace = *pMyplace - 32;
            *pMymoney = *pMymoney + 20;
        } //���� �������� ������ ���� ����
    }
    void setMooindo(int k = 0) {
        c += 1; //���ε� �ϼ� ī����
        if (c == 3) {
            c = 0;
        }
        if (k == 1) {
            c = 0;
            k = 0;
        } //���ε� 3�������� Ż���ϴ� �Լ�
    }
    int getMooindo() { return c; }
    void setSpace(int sp) {
        *pMyplace = sp;
        if (*pMyplace >= 0 && *pMyplace <= 23) {
            *pMymoney = *pMymoney + 20;
        } // ���ֿպ����� ���������� ������ ���� ����
    }
    void setmylend(City& a, int b) {
        myland_p[citynum] = a.getPrice();
        city[citynum] = b;
        build_cnt[citynum] = 0;
        myland_xi[citynum] = a.getx();
        myland_yi[citynum] = a.gety() - 1;
        myland_name[citynum] = a.getName();
        citynum++;
    }

    void get_myland_index() {
        for (int i = 0; i < citynum; i++) {
            if (build_cnt[i] == 0) {
                movecursor(myland_xi[i], myland_yi[i]); cout << getMal();
            }
            else if (build_cnt[i] == 1) {
                movecursor(myland_xi[i], myland_yi[i]); cout << getMal() << getMal();
            }
            else if (build_cnt[i] == 2) {
                movecursor(myland_xi[i], myland_yi[i]); cout << getMal() << getMal() << getMal();
            }
            else if (build_cnt[i] == 3) {
                movecursor(myland_xi[i], myland_yi[i]); cout << getMal() << getMal() << getMal() << getMal();
            }
        }
    }
    int get_buid_cnt(int ab) {
        int j = 0;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == ab)
            {
                j = i; break;// ���� ���� ������ ���� ��ġ�� �ε��� ã��
            }
        };
        return build_cnt[j];
    }
    void land_purchase(int a, int b, int c, City& d, string e) {
        *pMymoney -= a;
        myland_p[citynum] = a;
        city[citynum] = b;
        build_cnt[citynum] = c;
        myland_xi[citynum] = d.getx();
        myland_yi[citynum] = d.gety() - 1;
        myland_name[citynum] = e;
        citynum++;
    }
    void land_sell(int ab, City& o) {
        int num = 0;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == ab)
            {
                city[i] = 0;
                myland_p[i] = 0;
                build_cnt[i] = 0;
                myland_xi[i] = 0;
                myland_yi[i] = 0;
                myland_name[i] = "";
                o.setowner(0);
                break;// ���� ���� ������ ���� ��ġ�� �ε��� ã��
            }
        }
    }
    void add_building(City a, int ab) {
        int num, n;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == ab)
            {
                num = i; break;// ���� ���� ������ ���� ��ġ�� �ε��� ã��
            }
        }
        if (build_cnt[num] == 3)//���� �ǹ��� 3���� ���
        {
            movecursor(110, 30);
            cout << "�� �̻� �ǹ��� ���� �� �����ϴ�." << endl;
        }
        else {
            while (1) {
                movecursor(110, 18);
                cout << "(���� �ǹ� ���� �� ���� �ǹ� ���ؼ� ����)" << endl;
                movecursor(110, 19);
                cout << "1.���(" << a.getvilla() << ")" << endl;
                movecursor(110, 20);
                cout << "2.����(" << a.getbuilding() << ")" << endl;
                movecursor(110, 21);
                cout << "3.ȣ��(" << a.gethotel() << ")" << endl;
                movecursor(110, 22);
                cout << "4.���� ����";
                while (1) {
                    cin.ignore();
                    n = 0;
                    cin >> n;
                    if (n == 1 || n == 2 || n == 3 || n == 4)
                    {
                        break;
                    }
                    else
                    {
                        movecursor(110, 23);
                        cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���.";
                        cin.clear();
                    }
                }

                if (n == 1)
                {
                    if (*pMymoney < a.getvilla())
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�" << endl;
                        break;
                    }
                    if (build_cnt[num] >= 1) {
                        movecursor(110, 24);
                        cout << "�̹� ������ �ǹ��Դϴ�." << endl;
                    }
                    else {
                        myland_p[num] = a.getPrice() + a.getvilla();
                        build_cnt[num] = 1;

                        *pMymoney -= a.getvilla();
                        break;
                    }

                }
                else if (n == 2)
                {
                    if (*pMymoney < a.getbuilding() && build_cnt[num] == 1) // ����� �ϳ� �ְ�, �߰��� ������ ������µ� ���� ���� ���
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�. �߰��� �ǹ��� ���� �� �����ϴ�." << endl;
                        break;
                    }
                    else if (*pMymoney < a.getbuilding() + a.getvilla() && build_cnt[num] == 0) // �� �ۿ� ����, �ѹ��� �ΰ� �ٻ��µ� ���� ���� ���
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�" << endl;
                        continue;
                    }

                    if (build_cnt[num] >= 2) {
                        movecursor(110, 24);
                        cout << "�̹� ������ �ǹ��Դϴ�." << endl;
                    }

                    else {
                        myland_p[num] = a.getPrice() + a.getbuilding() + a.getvilla();
                        if (build_cnt[num] == 0)
                        {
                            *pMymoney -= (a.getvilla() + a.getbuilding());

                        }

                        else if (build_cnt[num] == 1) {
                            *pMymoney -= a.getbuilding();

                        }
                        build_cnt[num] = 2;

                        break;
                    }
                }
                else if (n == 3)
                {
                    if (*pMymoney < a.gethotel() && build_cnt[num] == 2)
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�. �߰��� �ǹ��� ���� �� �����ϴ�." << endl;
                        break;
                    }
                    else if (*pMymoney < a.gethotel() + a.getbuilding() && build_cnt[num] == 1)
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�" << endl;
                        continue;
                    }
                    else if (*pMymoney < a.gethotel() + a.getbuilding() + a.getvilla() && build_cnt[num] == 0) // �� �ۿ� ����, �ѹ��� ���� �ٻ��µ� ���� ���� ���
                    {
                        movecursor(110, 37);
                        cout << "���� �����մϴ�" << endl;
                        continue;
                    }

                    if (build_cnt[num] >= 3) {
                        movecursor(110, 24);
                        cout << "�̹� ������ �ǹ��Դϴ�." << endl;
                    }
                    else {
                        myland_p[num] = a.getPrice() + a.gethotel() + a.getbuilding() + a.getvilla();
                        if (build_cnt[num] == 0) {
                            *pMymoney -= (a.getvilla() + a.getbuilding() + a.gethotel());

                        }
                        else if (build_cnt[num] == 1) {
                            *pMymoney -= (a.getbuilding() + a.gethotel());

                        }
                        else if (build_cnt[num] == 2) {
                            *pMymoney -= a.gethotel();
                        }
                        build_cnt[num] = 3;

                        break;
                    }
                }
                else if (n == 4)
                {
                    break;
                }
            }
        }

    }

    int goldkey(int g) {
        if (g == 1) {
            movecursor(110, 9);
            cout << "1�� ��α� ��÷~!!!" << endl;
            movecursor(110, 10);
            cout << "��α��� �����մϴ�. ��α��� 20�޷� �Դϴ�." << endl << endl;
            return 1;
        }
        else if (g == 2) {
            movecursor(110, 9);
            cout << "2�� ���ֿպ��� ��÷~!!!" << endl;
            movecursor(110, 10);
            cout << "���� ���� ���ֿպ������� �̵��մϴ�. " << endl << endl;
            return 2;
        }
        else if (g == 3) {
            movecursor(110, 9);
            cout << "3�� ���ε� ��÷~!!!" << endl;
            movecursor(110, 10);
            cout << "���� ���� ���ε��� �̵��մϴ�. " << endl << endl;
            return 3;
        }
        else if (g == 4) {
            movecursor(110, 9);
            cout << "4�� ���� ���ʽ� ��÷~!!!" << endl;
            movecursor(110, 10);
            cout << "���� ���� ������ �� �� �� ���� �޽��ϴ�. " << endl << endl;
            *pMymoney = *pMymoney + 20;
            return 4;
        }
    } // return������ ���� ���� �ٸ�

    void view_land() {
        citycnt = 0;
        movecursor(15, 14);
        cout << "���� ����";
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] > 0)
            {
                movecursor(15, 15 + i);
                cout << myland_name[i] << " : " << myland_p[i] << "����";
                citycnt += 1;
            }
        }
        if (citycnt == 0) {
            citycnt = 0;
        }
        else {
            citycnt -= 1;
        }

    }
    int matching(int num) {
        int match = 0;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == num)
            {
                match = 1;
                break;// ���� ���� ������ ���� ��ġ�� �ε��� ã��
            }
        };
        return match;
    }
    int getcitycnt() { return citycnt; }
    void bankrupt(City o[])
    {
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] > 0)
            {
                o[city[i]].setowner(0);
                city[i] = 0;
                myland_p[i] = 0;
                build_cnt[i] = 0;
                myland_name[i] = "";

            }
        }
        live = 0;
        live_cnt += 1;
    }
    static void playernum(int a) {
        n = a;
    }
    static int getlive_cnt() {
        return live_cnt;
    }
    static int getgibu() {
        return gibu;
    }
    static void gogibu(int a) {
        gibu += a;
    }
    static void resetgibu() {
        gibu = 0;
    }
};
int Player::live_cnt = 0;
int Player::gibu = 0;
int Player::n = 0;

int menuDraw();
int KeyControl();
void map();
void title();
int dice1();
int dice2();
int goldrandom(); //Ȳ�ݿ��� ������ ��ȯ�Լ�
void next();

int main() {
    int n, n1, n2; //�����ڼ�, ������ ���� ����
    int nn; //���� ��������
    int cnt = 1; //�ϼ� ����
    int d = 0; //�ֻ��� ��
    int d1 = 0; //�ֻ���1
    int d2 = 0; //�ֻ���2
    int sp = 0; //���ֿպ��� �̵� ����
    int gk = 0; //Ȳ�ݿ��� ������
    int g = 0; //Ȳ�ݿ��� ��ȣ
    int gameover = 0;
    int k = 0; //�� ��ġ �ʱ�ȭ��
    string mal; //�� ����
    int just; //â �ٽö��� ���� �߰�������
    int sell_num; //�Ű��� �� ��ȣ
    int pasan = 0; //�Ļ� ī��Ʈ ���Ӽ�

    City city[32] = {
     City(0,0,0,0,"0. ������",3,4),
     City(5,1,9,25,"1.Ÿ�̺���",14,4),
     City(8,2,18,45,"2.����¡",25,4),
     City(8,2,18,45,"3.���Ҷ�",36,4),
     City(0,0,0,0,"4. Ȳ�ݿ���",47,4),
     City(10,3,27,55,"5.�̰�����",58,4),
     City(10,3,27,55,"6.ī�̷�",69,4),
     City(12,4,30,60,"7.�̽�ź��",80,4),
     City(0,0,0,0,"8. ���ε�",91,4),
     City(14,5,45,75,"9.���׳�",91,9),
     City(16,6,50,90,"10.�����ϰ�",91,14),
     City(16,6,50,90,"11.����Ȧ��",91,19),
     City(0,0,0,0,"12. Ȳ�ݿ���",91,24),
     City(18,7,50,95,"13.����",91,29),
     City(18,7,50,95,"14.������",91,34),
     City(20,8,55,100,"15.��Ÿ��",91,39),
     City(0,0,0,0,"16.��α�",91,44),
     City(22,9,70,105,"17.�ο��뽺���̷���",80,44),
     City(24,10,75,110,"18.���Ŀ��",69,44),
     City(24,10,75,110,"19.�õ��",58,44),
     City(0,0,0,0,"20. Ȳ�ݿ���",47,44),
     City(26,11,80,115,"21.�Ͽ���",36,44),
     City(26,11,80,115,"22.������",25,44),
     City(28,12,85,120,"23.���帮��",14,44),
     City(0,0,0,0,"24. ���ֿ���",3,44),
     City(30,13,90,127,"25.����",3,39),
     City(32,15,100,140,"26.�ĸ�",3,34),
     City(32,15,100,140,"27.�θ�",3,29),
     City(0,0,0,0,"28. Ȳ�ݿ���",3,24),
     City(35,17,110,150,"29.����",3,19),
     City(35,17,110,150,"30.����",3,14),
     City(100,0,0,0,"31.����",3,9)
    }; //�⺻ ���� 24, Ȳ�ݿ��� 4, ��������, ���ε�, ��α� ����, ���ֿպ���, �� 32��
    title();
    int menuCode = menuDraw();
    if (menuCode == 19) { cout << "������ �����մϴ�." << endl; return 0; }
    map();
    movecursor(3, 45);
    do {
        movecursor(110, 3);
        cout << "������ ���� �����Ͻÿ�.(2~4��)";
        cin >> n;
        if (n < 2 || n>4) {
            system("cls");
            map();
            cin.clear();
            cin.ignore();
        }
        //������ �� 2~4�� �ƴϸ� �ٽ� �Է�
    } while (n < 2 || n > 4); //�����ڰ� 2~4���� �ƴϸ� �ٽ� �Է¹ް� �Ѵ�.

    Player* pPlayer = new Player[n];
    Player::playernum(n);
    movecursor(110, 4);
    cout << "���� �־��� ���� " << pPlayer[0].getMymoney() << "�޷� �Դϴ�." << endl << endl;   //���� ���� �ȳ�����
    next();
    system("cls");
    map();

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            pPlayer[i].setMal("��");
            k = 0;
        }
        if (i == 1) {
            pPlayer[i].setMal("��");
            k = 2;
        }
        if (i == 2) {
            pPlayer[i].setMal("��");
            k = 4;
        }
        if (i == 3) {
            pPlayer[i].setMal("��");
            k = 6;
        }
        movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
        k = 0;
    }
    while (1) {
        movecursor(110, 3);

        cout << cnt << "��° ���Դϴ�." << endl << endl;
        for (int i = 0; i < n; i++) {
            if (pasan == 1) {
                system("cls");
                map();
                for (int i = 0; i < n; i++) {
                    k = 0;
                    if (i == 0) {
                        k = 0;
                    }
                    else if (i == 1) {
                        k = 2;
                    }
                    else if (i == 2) {
                        k = 4;
                    }
                    else if (i == 3) {
                        k = 6;
                    }
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    pPlayer[i].get_myland_index();
                    k = 0;
                }
                movecursor(25, 25);
                cout << " ���ϵ帳�ϴ�. �¸��ڴ� ";
                for (int i = 0; i < n; i++) {
                    if (pPlayer[i].get_live() == 1) {
                        cout << i + 1 << "�� ������ �Դϴ�." << endl;
                        movecursor(25, 26);
                        cout << "������� ���Ͽ� ������ " << n + 1 - i << "���� ���� ������ �Ǿ����ϴ�.";
                        movecursor(25, 27); cout << i + 1 << "�� �������� ���� �� : " << pPlayer[i].getMymoney();
                    }
                    return 0;
                }
            }
            if (i == 0) {
                k = 0;
            }
            else if (i == 1) {
                k = 2;
            }
            else if (i == 2) {
                k = 4;
            }
            else if (i == 3) {
                k = 6;
            }
            movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
            pPlayer[i].get_myland_index();
            k = 0;
        }
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                k = 0;
            }
            else if (i == 1) {
                k = 2;
            }
            else if (i == 2) {
                k = 4;
            }
            else if (i == 3) {
                k = 6;
            }
            if (pPlayer[i].get_live() == 0) {
                continue;
            }//�Ļ��� ������ ����


            movecursor(110, 4);
            cout << i + 1 << "�� �������� �����Դϴ�." << endl;
            if (pPlayer[i].getMooindo() != 0) {
                pPlayer[i].setMooindo();
                movecursor(110, 5);
                cout << "���� ���ε��Դϴ�." << endl;
                movecursor(110, 6);
                cout << "�� �ֻ����� ���ڰ� ������ Ż���մϴ�." << endl;
                d1 = dice1();
                d2 = dice2();
                if (d1 == d2) {
                    pPlayer[i].setMooindo(1);
                    movecursor(110, 7);
                    cout << d1 << " + " << d2 << " �����մϴ�. ���� �Ͽ� ���ε��� Ż���մϴ�. " << endl << endl;
                }
                else {
                    movecursor(110, 7);
                    cout << "���ε��� Ż������ ���߽��ϴ�." << endl << endl;
                }
                k = 0;
                movecursor(110, 40);
                cout << "���� ��� �����Ͻðڽ��ϱ�?(yes = 1/ no = 2)";
                cin >> nn;
                if (nn == 2) {
                    exit(1);
                }
                system("cls");
                map();
                for (int i = 0; i < n; i++) {
                    k = 0;
                    if (i == 0) {
                        k = 0;
                    }
                    else if (i == 1) {
                        k = 2;
                    }
                    else if (i == 2) {
                        k = 4;
                    }
                    else if (i == 3) {
                        k = 6;
                    }
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    pPlayer[i].get_myland_index();
                    k = 0;
                }
                continue;
            } //�����ڰ� ���ε��� ������� ���� ���۸� ����

            movecursor(110, 5);
            cout << "�ֻ����� �����ڽ��ϴ�." << endl;
            movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
            d = dice1() + dice2(); //�ֻ���1, �ֻ���2 ��
            movecursor(110, 6);
            cout << d << " �̵��ϰڽ��ϴ�." << endl;
            pPlayer[i].setMyplace(d); //������ �ֻ��� �� ��ŭ �̵�
            movecursor(110, 7);
            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;

            movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
            movecursor(110, 8);
            if (pPlayer[i].getMyplace() == 0) {
                cout << "�������Դϴ�." << endl << endl;
                movecursor(110, 9);
                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
            } //���������� �ɸ�
            else if (pPlayer[i].getMyplace() == 8) {
                pPlayer[i].setMooindo();
                cout << "���ε� �Դϴ�. 3�� ���ϴ�." << endl << endl;
            } // ������ ���ε��� �ɸ�
            else if (pPlayer[i].getMyplace() == 16) {
                cout << "���ݱ��� ���� ��α��� ����� ���Դϴ�." << endl << endl;
                movecursor(110, 9);
                cout << "��α� : " << Player::getgibu() << endl;
                pPlayer[i].setGibu(Player::getgibu());
                movecursor(110, 10);
                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                Player::resetgibu();
            } // ������ ��α� ���� �ɸ�
            else if (pPlayer[i].getMyplace() == 24) {
                cout << "���ֿպ����� ž���߽��ϴ�. ���ϴ� ��ġ�� �Է��Ͻÿ�.";
                while (1) {

                    cin >> sp;
                    if (!cin) {
                        movecursor(20, 9);
                        cout << "�ٽ��Է����ּ���";

                        cin.clear();
                        cin.ignore();

                    }
                    else if (sp >= 0 && sp <= 31) {
                        break;
                    }
                    movecursor(110, 12);
                    if (sp == 4 || sp == 12 || sp == 20 || sp == 28) {
                        cout << "Ȳ�ݿ���� �̵��Ͻ� �� �����ϴ�. �ٽ� �Է��Ͻʽÿ�.";
                        cin.clear();
                        cin.ignore();
                    }
                    else {
                        break;
                    }

                }
                movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                pPlayer[i].setSpace(sp);
                movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                movecursor(110, 11);
                cout << city[pPlayer[i].getMyplace()].getName();
                cout << "�� ���̽��ϴ�." << endl;
                movecursor(110, 12);
                if (sp == 8) {
                    pPlayer[i].setMooindo();
                    cout << "���ε� �Դϴ�. 3�� ���ϴ�." << endl << endl;
                }
                else if (sp == 16) {
                    cout << "���ݱ��� ���� ��α��� ����� ���Դϴ�." << endl << endl;
                    movecursor(110, 13);
                    cout << "��α� : " << Player::getgibu() << endl;
                    pPlayer[i].setGibu(Player::getgibu());
                    movecursor(110, 14);
                    cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                    Player::resetgibu();
                }
                else if (sp == 0) {
                    cout << "�������Դϴ�." << endl << endl;
                    movecursor(110, 13);
                    cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                }
                else {

                    if (city[pPlayer[i].getMyplace()].getowner() == 0)//���ξ��� ��
                    {
                        if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//���� ���� ���
                        {
                            cout << city[pPlayer[i].getMyplace()].getName();
                            cout << "���� �� �� �ִ� �ൿ�� �����ϴ�." << endl;
                        }
                        else
                        {
                            while (1)
                            {
                                cin.ignore();
                                n1 = 0;

                                cout << city[pPlayer[i].getMyplace()].getName();
                                cout << "�� ���̽��ϴ�. ���� ��ڽ��ϱ�? (yes = 1,no = 2)";
                                cin >> n1;
                                if (n1 == 1)
                                {
                                    break;
                                }
                                else if (n1 == 2)
                                {
                                    break;
                                }
                                else
                                {
                                    movecursor(15, 10);
                                    cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���.";
                                    cin.clear();
                                    movecursor(15, 12);

                                }
                            }
                            if (n1 == 1)
                            {
                                pPlayer[i].setmylend(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                                pPlayer[i].setMymoney(pPlayer[i].getMymoney() - city[pPlayer[i].getMyplace()].getPrice());
                                city[pPlayer[i].getMyplace()].setowner(i + 1);
                                pPlayer[i].get_myland_index();
                                movecursor(110, 13);
                                cout << city[pPlayer[i].getMyplace()].getName();
                                cout << "�� �����ϼ̽��ϴ�." << endl;
                                movecursor(110, 14);
                                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            }
                            cout << endl;
                        }
                    }
                    else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//���� �ִ� ���� �ɸ����
                    {
                        cout << city[pPlayer[i].getMyplace()].getName();
                        int own = city[pPlayer[i].getMyplace()].getowner() - 1;//���� �� ���� �ε���
                        cout << "�� ���̽��ϴ�." << "<" << own + 1 << "�� �������� ��>" << endl;
                        while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                        {
                            if (pPlayer[i].getcitycnt() == 0)
                            {
                                movecursor(25, 25);
                                cout << "�����������������������Ļ�" << endl; // ���ֿպ��� �Ļ�
                                pPlayer[i].bankrupt(city);
                                pasan = n - Player::getlive_cnt();
                                pPlayer[i].setMal("");
                                break;
                            }
                            else
                            {
                                movecursor(110, 9);
                                cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "������ �����մϴ�.";
                                movecursor(20, 7);
                                cout << "������ ���� �����մϴ�. ������ ���� �Ű��ϼ���.";
                                movecursor(20, 8);
                                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                                pPlayer[i].view_land();
                                movecursor(20, 9);
                                cout << "�Ű��� ���� ��ȣ�� �����Ͻÿ�.";
                                int sell_num;
                                cin >> sell_num;
                                if (pPlayer[i].matching(sell_num) == 1)
                                {
                                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                    pPlayer[i].land_sell(sell_num, city[sell_num]);
                                }
                                else
                                {
                                    movecursor(20, 25);
                                    cout << "�������� ���� ���ù�ȣ�Դϴ�." << endl;
                                }
                                system("cls");
                                map();
                                for (int i = 0; i < n; i++) {
                                    if (i == 0) {
                                        k = 0;
                                    }
                                    else if (i == 1) {
                                        k = 2;
                                    }
                                    else if (i == 2) {
                                        k = 4;
                                    }
                                    else if (i == 3) {
                                        k = 6;
                                    }
                                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                                    pPlayer[i].get_myland_index();
                                    k = 0;
                                }
                            }
                        }
                        if (pPlayer[i].getcitycnt() == 0 && pPlayer[i].getMymoney() <= pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                        {
                            movecursor(25, 26);
                            cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ��� ���� �� " << pPlayer[i].getMymoney() << "���� ���� �� �Ļ��մϴ�.";
                            pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// �Ļ� �� ���� �� �����ο��� ����
                            while (1) {
                                cin.ignore();
                                nn = 0;
                                movecursor(25, 27);
                                cout << "���� 1�� �Է��ϼ���";
                                cin >> nn;
                                if (nn == 1) {
                                    break;
                                }
                                else {
                                    movecursor(25, 28);
                                    cout << "�߸��Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ��� : ";
                                    cin.clear();
                                }
                            }
                            continue;
                        }
                        pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ŭ ����
                        pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ �� ����;
                        movecursor(110, 26);
                        cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ���";
                        cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "������ �����մϴ�." << endl;
                        movecursor(110, 27);
                        cout << "������ ���� �Ͻðڽ��ϱ�?(yes = 1, no = 2)";
                        cin >> n1;
                        if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                        {
                            pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                                pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                            pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                            city[pPlayer[i].getMyplace()].setowner(i + 1);//���ο� �� ���� �ε��� ����
                            pPlayer[i].get_myland_index();
                            movecursor(110, 13);
                            cout << "���� ���� �Ϸ�" << endl;
                            movecursor(110, 14);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                        }
                        else
                        {
                            movecursor(110, 37);
                            cout << "���� �����մϴ�." << endl;
                            movecursor(110, 38);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                        }

                    }
                    else
                    {

                        cout << "�� ���̽��ϴ�." << endl;
                        movecursor(110, 13);
                        cout << "���� �ǹ� �� : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "��" << endl;
                        movecursor(110, 14);
                        cout << "�߰��ǹ��� ���ڽ��ϱ� ? (yes = 1, no = 2)";

                        cin >> n1;
                        if (n1 == 1)
                        {
                            pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                            movecursor(110, 25);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                        }
                        //�ǹ� ���� �ǹ� ���� �ڵ�

                    }
                }
                k = 0;
            }
            else if (pPlayer[i].getMyplace() == 4 || pPlayer[i].getMyplace() == 12 || pPlayer[i].getMyplace() == 20 || pPlayer[i].getMyplace() == 28) {
                cout << "Ȳ�� ���踦 ȹ���ϼ̽��ϴ�." << endl;
                gk = goldrandom();
                g = pPlayer[i].goldkey(gk);
                if (g == 1)
                {
                    if (pPlayer[i].getMymoney() < 20) {
                        while (pPlayer[i].getMymoney() < 20)
                        {

                            if (pPlayer[i].getcitycnt() == 0)
                            {
                                movecursor(25, 25);
                                cout << "�Ļꤻ����������" << endl; // ��α� �Ļ�
                                pPlayer[i].bankrupt(city);
                                pasan = n - Player::getlive_cnt();
                                pPlayer[i].setMal("");
                                break;
                            }
                            else
                            {
                                movecursor(20, 7);
                                cout << "������ ���� �����մϴ�. ������ ���� �Ű��ϼ���.";
                                pPlayer[i].view_land();
                                movecursor(20, 8);
                                cout << "�Ű��� ���� ��ȣ�� �����Ͻÿ�.";
                                int sell_num;
                                cin >> sell_num;
                                if (pPlayer[i].matching(sell_num) == 1)
                                {
                                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                    pPlayer[i].land_sell(sell_num, city[sell_num]);
                                }
                                else {
                                    cout << "�������� ���� ���ù�ȣ�Դϴ�." << endl;
                                }
                                system("cls");
                                map();
                                for (int i = 0; i < n; i++) {
                                    if (i == 0) {
                                        k = 0;
                                    }
                                    else if (i == 1) {
                                        k = 2;
                                    }
                                    else if (i == 2) {
                                        k = 4;
                                    }
                                    else if (i == 3) {
                                        k = 6;
                                    }
                                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                                    pPlayer[i].get_myland_index();

                                    k = 0;
                                }
                            }
                        }
                        if (pPlayer[i].getcitycnt() == 0 && pPlayer[i].getMymoney() < 20)
                        {
                            movecursor(25, 26);
                            cout << "���� �� " << pPlayer[i].getMymoney() << "���� ��α� ���� ���� �Ļ��մϴ�.";
                            while (1) {
                                cin.ignore();
                                nn = 0;
                                movecursor(25, 27);
                                cout << "���� 1�� �Է��ϼ���";
                                cin >> nn;
                                if (nn == 1) {
                                    break;
                                }
                                else {
                                    movecursor(25, 28);
                                    cout << "�߸��Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ��� : ";
                                    cin.clear();
                                }
                            }
                            continue;
                        }
                        else {
                            Player::gogibu(20);
                        }

                    }
                    else {
                        Player::gogibu(20);
                        pPlayer[i].setGibu(-20);
                        movecursor(110, 11);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                    }

                }

                else if (g == 2) {
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                    pPlayer[i].setSpace(24);
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    movecursor(110, 11);
                    cout << "���ֿպ����� ž���߽��ϴ�. ���ϴ� ��ġ�� �Է��Ͻÿ�.";
                    while (1) {

                        while (1) {

                            cin >> sp;

                            if (!cin) {
                                movecursor(20, 9);
                                cout << "�ٽ��Է����ּ���";

                                cin.clear();
                                cin.ignore();

                            }
                            else if (sp >= 0 && sp <= 31) {
                                break;
                            }
                        }

                        movecursor(110, 12);
                        if (sp == 4 || sp == 12 || sp == 20 || sp == 28) {
                            cout << "Ȳ�ݿ���� �̵��Ͻ� �� �����ϴ�. �ٽ� �Է��Ͻʽÿ�.";
                            cin.clear();
                            cin.ignore();
                        }

                        else {
                            break;
                        }
                    }
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                    pPlayer[i].setSpace(sp);
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    movecursor(110, 14);
                    cout << city[pPlayer[i].getMyplace()].getName();
                    cout << "�� ���̽��ϴ�." << endl;
                    movecursor(110, 15);
                    if (sp == 8) {
                        pPlayer[i].setMooindo();
                        cout << "���ε� �Դϴ�. 3�� ���ϴ�." << endl << endl;
                    }
                    else if (sp == 16) {
                        cout << "���ݱ��� ���� ��α��� ����� ���Դϴ�." << endl;
                        movecursor(110, 16);
                        cout << "��α� : " << Player::getgibu() << endl;
                        pPlayer[i].setGibu(Player::getgibu());
                        movecursor(110, 17);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                        Player::resetgibu();
                    }
                    else if (sp == 0) {
                        cout << "�������Դϴ�." << endl << endl;
                        movecursor(110, 16);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                    }
                    else {

                        if (city[pPlayer[i].getMyplace()].getowner() == 0)//���ξ��� ��
                        {
                            if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//���� ���� ���
                            {
                                cout << city[pPlayer[i].getMyplace()].getName();
                                cout << "������ �� �ִ� �ൿ�� �����ϴ�." << endl;
                            }
                            else
                            {
                                while (1)
                                {
                                    cin.ignore();
                                    n1 = 0;
                                    cout << city[pPlayer[i].getMyplace()].getName();
                                    cout << "�� ���̽��ϴ�. ���� ��ڽ��ϱ�? (yes = 1,no = 2)";
                                    cin >> n1;
                                    if (n1 == 1)
                                    {
                                        break;
                                    }
                                    else if (n1 == 2)
                                    {
                                        movecursor(110, 27);
                                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                                        break;
                                    }
                                    else
                                    {
                                        movecursor(15, 10);
                                        cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���.";
                                        cin.clear();
                                        movecursor(15, 12);
                                    }
                                }
                                if (n1 == 1)
                                {
                                    pPlayer[i].setmylend(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() - city[pPlayer[i].getMyplace()].getPrice());
                                    city[pPlayer[i].getMyplace()].setowner(i + 1);
                                    pPlayer[i].get_myland_index();
                                    movecursor(110, 28);
                                    cout << city[pPlayer[i].getMyplace()].getName();
                                    cout << "�� �����ϼ̽��ϴ�." << endl;
                                    movecursor(110, 29);
                                    cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                                }
                                cout << endl;
                            }
                        }
                        else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//���� �ִ� ���� �ɸ����
                        {
                            cout << city[pPlayer[i].getMyplace()].getName();
                            int own = city[pPlayer[i].getMyplace()].getowner() - 1;//���� �� ���� �ε���
                            cout << "�� ���̽��ϴ�." << "<" << own + 1 << "�� �������� ��>" << endl;
                            while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                            {
                                if (pPlayer[i].getcitycnt() == 0)
                                {
                                    movecursor(25, 25);
                                    cout << "�Ļꤻ��" << endl; // Ȳ�ݿ��迡�� ���ֿպ��� ���ٰ� ���� �ִ� �� ��� �Ļ�
                                    pPlayer[i].bankrupt(city);
                                    pasan = n - Player::getlive_cnt();
                                    pPlayer[i].setMal("");
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    map();
                                    for (int i = 0; i < n; i++) {
                                        if (i == 0) {
                                            k = 0;
                                        }
                                        else if (i == 1) {
                                            k = 2;
                                        }
                                        else if (i == 2) {
                                            k = 4;
                                        }
                                        else if (i == 3) {
                                            k = 6;
                                        }
                                        movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                                        pPlayer[i].get_myland_index();
                                        k = 0;
                                    }
                                    movecursor(110, 20);
                                    cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "������ �����մϴ�.";
                                    movecursor(20, 7);
                                    cout << "������ ���� �����մϴ�. ������ ���� �Ű��ϼ���.";
                                    pPlayer[i].view_land();
                                    movecursor(20, 8);
                                    cout << "�Ű��� ���� ��ȣ�� �����Ͻÿ�.";
                                    int sell_num;
                                    cin >> sell_num;
                                    if (pPlayer[i].matching(sell_num) == 1)
                                    {
                                        pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                        pPlayer[i].land_sell(sell_num, city[sell_num]);
                                    }
                                    else {
                                        cout << "�������� ���� ���ù�ȣ�Դϴ�." << endl;
                                    }
                                    system("cls");
                                    map();
                                    for (int i = 0; i < n; i++) {
                                        if (i == 0) {
                                            k = 0;
                                        }
                                        else if (i == 1) {
                                            k = 2;
                                        }
                                        else if (i == 2) {
                                            k = 4;
                                        }
                                        else if (i == 3) {
                                            k = 6;
                                        }
                                        movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                                        pPlayer[i].get_myland_index();
                                        k = 0;
                                    }
                                }
                            }
                            if (pPlayer[i].getcitycnt() == 0 && pPlayer[i].getMymoney() <= pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                            {
                                movecursor(25, 26);
                                cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ��� ���� �� " << pPlayer[i].getMymoney() << "���� ���� �� �Ļ��մϴ�.";
                                pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// �Ļ� �� ���� �� �����ο��� ����
                                while (1) {
                                    cin.ignore();
                                    nn = 0;
                                    movecursor(25, 27);
                                    cout << "���� 1�� �Է��ϼ���";
                                    cin >> nn;
                                    if (nn == 1) {
                                        break;
                                    }
                                    else {
                                        movecursor(25, 28);
                                        cout << "�߸��Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ��� : ";
                                        cin.clear();
                                    }
                                }
                                continue;
                            }
                            pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ŭ ����
                            pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ �� ����;
                            movecursor(110, 16);
                            cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ���";
                            cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "���� �����մϴ�." << endl;
                            movecursor(110, 17);
                            cout << "������ ���� �Ͻðڽ��ϱ�?(yes = 1, no = 2)";
                            cin >> n1;
                            movecursor(110, 18);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                            {
                                pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                                    pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                                pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                                city[pPlayer[i].getMyplace()].setowner(i + 1);//���ο� �� ���� �ε��� ����
                                pPlayer[i].get_myland_index();
                                movecursor(110, 21);
                                cout << "���� ���� �Ϸ�" << endl;
                                movecursor(110, 22);
                                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            }
                            else
                            {
                                movecursor(110, 27);
                                cout << "���� �����մϴ�." << endl;
                                movecursor(110, 28);
                                cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            }
                        }
                        else
                        {
                            cout << city[pPlayer[i].getMyplace()].getName() << "�� ���̽��ϴ�." << endl;
                            movecursor(110, 16);
                            cout << "���� �ǹ� �� : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "��" << endl;
                            while (1) {
                                cin.ignore();
                                n1 = 0;
                                movecursor(110, 17);
                                cout << "�߰��ǹ��� ���ڽ��ϱ� ? (yes = 1, no = 2)";
                                cin >> n1;
                                if (n1 == 1)
                                {
                                    pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                                    movecursor(110, 26);
                                    cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                                    break;

                                }
                                else if (n1 == 2) {
                                    break;
                                }
                                else {
                                    movecursor(110, 18);
                                    cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���.";
                                    cin.clear();
                                }
                            }

                            //�ǹ� ���� �ǹ� ���� �ڵ�
                        }
                    }
                    k = 0;
                } //���ֿպ��� Ȳ�ݿ��� ���� ���
                else if (g == 3) {
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                    pPlayer[i].setSpace(8);
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    pPlayer[i].setMooindo();
                    movecursor(110, 11);
                    cout << "���ε� �Դϴ�. 3�� ���ϴ�." << endl << endl;
                    k = 0;
                } //���ε� Ȳ�ݿ��� ���� ��� , 1�� 4�� goldkey�Լ����� �̹� ���� �Ϸ�
                else if (g == 4) {
                    cout << endl;
                    movecursor(110, 13);
                    cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                }
            } //������ Ȳ�ݿ��� ȹ����
            else {

                if (city[pPlayer[i].getMyplace()].getowner() == 0)//���ξ��� ��
                {
                    if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//���� ���� ���
                    {
                        cout << city[pPlayer[i].getMyplace()].getName();
                        cout << "���� �� �� �ִ� �ൿ�� �����ϴ�." << endl;
                    }
                    else
                    {
                        while (1)
                        {
                            cin.ignore();
                            n1 = 0;
                            cout << city[pPlayer[i].getMyplace()].getName();
                            cout << "�� ���̽��ϴ�. ���� ��ڽ��ϱ�? (yes = 1,no = 2)";
                            cin >> n1;
                            if (n1 == 1)
                            {
                                break;
                            }
                            else if (n1 == 2)
                            {
                                break;
                            }
                            else
                            {
                                movecursor(15, 10);
                                cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���.";
                                cin.clear();
                                movecursor(15, 12);
                            }
                        }
                        if (n1 == 1)
                        {
                            pPlayer[i].setmylend(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                            pPlayer[i].setMymoney(pPlayer[i].getMymoney() - city[pPlayer[i].getMyplace()].getPrice());
                            city[pPlayer[i].getMyplace()].setowner(i + 1);
                            pPlayer[i].get_myland_index();
                            movecursor(110, 13);
                            cout << city[pPlayer[i].getMyplace()].getName();
                            cout << "�� �����ϼ̽��ϴ�." << endl;
                            movecursor(110, 14);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                        }
                        cout << endl;
                    }
                }
                else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//���� �ִ� ���� �ɸ����
                {
                    cout << city[pPlayer[i].getMyplace()].getName();
                    int own = city[pPlayer[i].getMyplace()].getowner() - 1;//���� �� ���� �ε���
                    cout << "�� ���̽��ϴ�." << "<" << own + 1 << "�� �������� ��>" << endl;
                    while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                    {
                        if (pPlayer[i].getcitycnt() == 0)
                        {
                            movecursor(25, 25);
                            cout << "�������������������������Ļ�" << endl;//�׳� �̵� �� �Ļ�
                            pPlayer[i].bankrupt(city);
                            pasan = n - Player::getlive_cnt();
                            pPlayer[i].setMal("");
                            break;
                        }
                        else
                        {
                            movecursor(110, 9);
                            cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "������ �����մϴ�.";
                            movecursor(110, 10);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            movecursor(20, 7);
                            cout << "������ ���� �����մϴ�. ������ ���� �Ű��ϼ���.";
                            pPlayer[i].view_land();
                            movecursor(20, 8);
                            cout << "�Ű��� ���� ��ȣ�� �����Ͻÿ�.";
                            int sell_num;
                            cin >> sell_num;
                            if (pPlayer[i].matching(sell_num) == 1)
                            {
                                pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                pPlayer[i].land_sell(sell_num, city[sell_num]);
                            }
                            else
                            {
                                cout << "�������� ���� ���ù�ȣ�Դϴ�." << endl;
                            }
                            system("cls");
                            map();
                            for (int i = 0; i < n; i++) {
                                if (i == 0) {
                                    k = 0;
                                }
                                else if (i == 1) {
                                    k = 2;
                                }
                                else if (i == 2) {
                                    k = 4;
                                }
                                else if (i == 3) {
                                    k = 6;
                                }
                                movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                                pPlayer[i].get_myland_index();
                                k = 0;
                            }
                        }
                    }
                    if (pPlayer[i].getcitycnt() == 0 && pPlayer[i].getMymoney() <= pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                    {
                        movecursor(25, 26);
                        cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ��� ���� �� " << pPlayer[i].getMymoney() << "���� ���� �� �Ļ��մϴ�.";
                        pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// �Ļ� �� ���� �� �����ο��� ����
                        while (1) {
                            cin.ignore();
                            nn = 0;
                            movecursor(25, 27);
                            cout << "���� 1�� �Է��ϼ���";
                            cin >> nn;
                            if (nn == 1) {
                                break;
                            }
                            else {
                                movecursor(25, 28);
                                cout << "�߸��Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ��� : ";
                                cin.clear();
                            }
                        }
                        continue;
                    }
                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ŭ ����
                    pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//������ �� ����;
                    movecursor(110, 11);
                    cout << city[pPlayer[i].getMyplace()].getowner() << "�� �����ڿ���";
                    cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "���� �����մϴ�." << endl;
                    movecursor(110, 12);

                    while (1) {
                        cin.ignore();
                        n1 = 0;
                        cout << "������ ���� �Ͻðڽ��ϱ�?(yes = 1, no = 2)";
                        cin >> n1;
                        if (n1 == 1) {
                            break;
                        }
                        else if (n1 == 2)
                        {
                            movecursor(110, 13);
                            cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                            break;
                        }
                        else {
                            movecursor(15, 10);
                            cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���. : ";
                            cin.clear();
                            movecursor(15, 11);
                        }
                    }

                    if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                    {
                        pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                            pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                        pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                        city[pPlayer[i].getMyplace()].setowner(i + 1);//���ο� �� ���� �ε��� ����
                        pPlayer[i].get_myland_index();
                        movecursor(110, 13);
                        cout << "���� ���� �Ϸ�" << endl;
                        movecursor(110, 14);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                    }
                    else if (n1 == 2)
                    {
                    }
                    else
                    {
                        movecursor(110, 27);
                        cout << "���� �����մϴ�." << endl;
                        movecursor(110, 28);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;
                    }

                }
                else
                {
                    cout << city[pPlayer[i].getMyplace()].getName();
                    cout << "�� ���̽��ϴ�." << endl;
                    movecursor(110, 11);
                    cout << "���� �ǹ� �� : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "��" << endl;
                    movecursor(110, 12);
                    cout << "�߰��ǹ��� ���ڽ��ϱ� ? (yes = 1, no = 2)";

                    cin >> n1;
                    if (n1 == 1)
                    {
                        pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                        movecursor(110, 30);
                        cout << i + 1 << "�� ������ �� : " << pPlayer[i].getMymoney() << endl;

                    }
                    //�ǹ� ���� �ǹ� ���� �ڵ�
                }
            }
            movecursor(110, 40);
            while (1) {
                cin.ignore();
                nn = 0;
                cout << "���� ��� �����Ͻðڽ��ϱ�?(yes = 1/ no = 9)";
                cin >> nn;
                if (nn == 1) {
                    break;
                }
                else if (nn == 9) {
                    exit(1);
                }
                else {
                    movecursor(15, 10);
                    cout << "�߸� �Է��Ͽ����ϴ�. �ٽ��Է����ּ���. : ";
                    cin.clear();
                    movecursor(15, 11);
                }
            }
            system("cls");
            map();
            for (int i = 0; i < n; i++) {
                if (i == 0) {
                    k = 0;
                }
                else if (i == 1) {
                    k = 2;
                }
                else if (i == 2) {
                    k = 4;
                }
                else if (i == 3) {
                    k = 6;
                }
                movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                pPlayer[i].get_myland_index();
                k = 0;
            }

        }

        cnt++;
    }

    return 0;
}
void next() {
    int n = KeyControl();
    if (n == SUBMIT) {}
}

int menuDraw() {
    int x = 39;
    int y = 18;
    movecursor(x, y);
    cout << "Start" << endl;
    movecursor(x, y + 1);
    cout << "end" << endl;
    movecursor(24, 16);
    cout << "����üȭ�� �� space bar�� ���� ������ �������ּ��䢾";
    while (1) {
        int n = KeyControl();
        switch (n) {
        case UP:
            if (y > 18) {
                movecursor(x - 2, y);
                cout << " " << endl;
                movecursor(x - 2, --y);
                cout << ">" << endl;
            }
            break;
        case DOWN:
            if (y < 19) {
                movecursor(x - 2, y);
                cout << " " << endl;
                movecursor(x - 2, ++y);
                cout << ">" << endl;
            }
            break;
        case SUBMIT:
            system("cls");

            return y;
        }
    }
}

int KeyControl() {
    char temp = _getch();
    if (temp == 72) {
        return UP;
    }
    else if (temp == 80) {
        return DOWN;
    }
    else if (temp == ' ') {
        return SUBMIT;
    }
    //else {
    //   temp = _getch(); //�߸��ԷµǾ����Ƿ� �ٽ� �Է� �ްԲ�

    //}
}
void map() {
    //system("mode con cols=150 lines=150 | title â ����");
    cout << " ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ������������������������                                                                            ������������������������" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��          ��                                                                            ��          ��" << endl;
    cout << " ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��          ��          ��          ��          ��          ��          ��          ��          ��          ��" << endl;
    cout << " ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
    movecursor(3, 2); cout << "���-->" << endl; movecursor(3, 1); cout << "(0)" << endl;
    movecursor(14, 1); cout << "Ÿ������" << endl; movecursor(14, 2); cout << "5����(1)" << endl;
    movecursor(25, 1); cout << "����¡" << endl; movecursor(25, 2); cout << "8����(2)" << endl;
    movecursor(36, 1); cout << "���Ҷ�" << endl; movecursor(36, 2); cout << "8����(3)" << endl;
    movecursor(47, 2); cout << "Ȳ�ݿ���!" << endl; movecursor(47, 1); cout << "(4)" << endl;
    movecursor(58, 1); cout << "�̰�����" << endl; movecursor(58, 2); cout << "10����(5)" << endl;
    movecursor(69, 1); cout << "ī�̷�" << endl; movecursor(69, 2); cout << "10����(6)" << endl;
    movecursor(80, 1); cout << "�̽�ź��" << endl; movecursor(80, 2); cout << "12����(7)" << endl;
    movecursor(91, 2); cout << "���ε���" << endl; movecursor(91, 1); cout << "(8)" << endl;

    movecursor(91, 6); cout << "���׳�" << endl; movecursor(91, 7); cout << "14����(9)" << endl;
    movecursor(91, 11); cout << "�����ϰ�" << endl; movecursor(91, 12); cout << "16����(10)" << endl;
    movecursor(91, 16); cout << "����Ȧ��" << endl; movecursor(91, 17); cout << "16����(11)" << endl;
    movecursor(91, 22); cout << "Ȳ�ݿ���!" << endl; movecursor(91, 21); cout << "(12)" << endl;
    movecursor(91, 26); cout << "����" << endl; movecursor(91, 27); cout << "18����(13)" << endl;
    movecursor(91, 31); cout << "������" << endl; movecursor(91, 32); cout << "18����(14)" << endl;
    movecursor(91, 36); cout << "��Ÿ��" << endl; movecursor(91, 37); cout << "20����(15)" << endl;
    movecursor(91, 42); cout << "���ȸ������!" << endl; movecursor(91, 41); cout << "(16)" << endl;

    movecursor(80, 41); cout << "�ο��뽺" << endl; movecursor(80, 42); cout << "22����(17)" << endl;
    movecursor(69, 41); cout << "���Ŀ��" << endl; movecursor(69, 42); cout << "24����(18)" << endl;
    movecursor(58, 41); cout << "�õ��" << endl; movecursor(58, 42); cout << "24����(19)" << endl;
    movecursor(47, 42); cout << "Ȳ�ݿ���!" << endl; movecursor(47, 41); cout << "(20)" << endl;
    movecursor(36, 41); cout << "�Ͽ���" << endl; movecursor(36, 42); cout << "26����(21)" << endl;
    movecursor(25, 41); cout << "������" << endl; movecursor(25, 42); cout << "26����(22)" << endl;
    movecursor(14, 41); cout << "���帮��" << endl; movecursor(14, 42); cout << "28����(23)" << endl;
    movecursor(3, 42); cout << "���ֿ����" << endl; movecursor(3, 41); cout << "(24)" << endl;

    movecursor(3, 36); cout << "����" << endl; movecursor(3, 37); cout << "30����(25)" << endl;
    movecursor(3, 31); cout << "�ĸ�" << endl; movecursor(3, 32); cout << "32����(26)" << endl;
    movecursor(3, 26); cout << "�θ�" << endl; movecursor(3, 27); cout << "32����(27)" << endl;
    movecursor(3, 22); cout << "Ȳ�ݿ���!" << endl; movecursor(3, 21); cout << "(28)" << endl;
    movecursor(3, 16); cout << "����" << endl; movecursor(3, 17); cout << "35����(29)" << endl;
    movecursor(3, 11); cout << "����" << endl; movecursor(3, 12); cout << "35����(30)" << endl;
    movecursor(3, 6); cout << "����" << endl; movecursor(3, 7); cout << "100����(31)" << endl;

    //movecursor(3, 45);//��ǥ ��ġ�� �ٸ���� �������ν� �ܼ�â�� �߰��� ���°��� ����
}

void title() {
    cout << "\n\n\n\n";
    cout << "          @        @       @@@@@@@@                   ##       ##        ##" << endl;
    cout << "          @        @              @                   ##       ############" << endl;
    cout << "          @@@@@@@@@@       @@@@@@@@        #######    ##       #          #" << endl;
    cout << "          @        @       @               ##   ##    ##       ############" << endl;
    cout << "          @@@@@@@@@@       @@@@@@@@        ##   ##    ##                " << endl;
    cout << "                                           ##   ##    ##     ################" << endl;
    cout << "        @@@@@@@@@@@@@@    @@@@@@@@@@@      ##   ##    #####                  " << endl;
    cout << "               @               @           #######    ##        ##########   " << endl;
    cout << "               @               @                      ##                 #   " << endl;
    cout << "               @               @                      ##        ##########   " << endl;
    cout << "               @               @                      ##        #            " << endl;
    cout << "               @               @                      ##        ##########   " << endl;
}

int dice1() {
    int di1 = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 6);
    di1 = dis(gen); //1�� �ֻ��� 1~6 ��������
    return di1;      //�ֻ��� �� ��ȯ
}
int dice2() {
    int di2 = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 6);
    di2 = dis(gen); //2�� �ֻ��� 1~6 ��������
    return di2;      //�ֻ��� �� ��ȯ
}
int goldrandom() {
    int gk = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 4);
    gk = dis(gen);
    return gk;
} //Ȳ�ݿ��� ������ ��ȯ5