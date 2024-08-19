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
    int price, villa, building, hotel; //도시가격
    int owner = 0;// 소유자
    string name; //도시이름
    int x, y;
public:
    City(int p = 0, int a = 0, int b = 0, int c = 0, string n = 0, int d = 0, int e = 0) :price{ p }, villa{ a }, building{ b }, hotel{ c }, name{ n }, x{ d }, y{ e } {}   //생성자
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
    int* pMymoney; //참가자의 현재 돈
    int* pMyplace; //참가자 현재 위치
    int myland_p[50];//그 땅가격 총합
    int myland_xi[100]; //그 땅가격 x축인덱스 값
    int myland_yi[100]; //그 땅가격 y축인덱스 값
    int* city;
    int build_cnt[50];
    int c, citynum;
    string* mal; //참가자 mal
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
                j = i; break;// 내가 가진 도시중 현재 위치의 인덱스 찾기
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
        } //만약 시작지점 지나면 월급 지급
    }
    void setMooindo(int k = 0) {
        c += 1; //무인도 턴수 카운터
        if (c == 3) {
            c = 0;
        }
        if (k == 1) {
            c = 0;
            k = 0;
        } //무인도 3턴지나면 탈출하는 함수
    }
    int getMooindo() { return c; }
    void setSpace(int sp) {
        *pMyplace = sp;
        if (*pMyplace >= 0 && *pMyplace <= 23) {
            *pMymoney = *pMymoney + 20;
        } // 우주왕복선이 시작지점을 지나면 월급 지급
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
                j = i; break;// 내가 가진 도시중 현재 위치의 인덱스 찾기
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
                break;// 내가 가진 도시중 현재 위치의 인덱스 찾기
            }
        }
    }
    void add_building(City a, int ab) {
        int num, n;
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] == ab)
            {
                num = i; break;// 내가 가진 도시중 현재 위치의 인덱스 찾기
            }
        }
        if (build_cnt[num] == 3)//땅에 건물이 3개인 경우
        {
            movecursor(110, 30);
            cout << "더 이상 건물을 지을 수 없습니다." << endl;
        }
        else {
            while (1) {
                movecursor(110, 18);
                cout << "(이전 건물 없을 시 이전 건물 합해서 차감)" << endl;
                movecursor(110, 19);
                cout << "1.펜션(" << a.getvilla() << ")" << endl;
                movecursor(110, 20);
                cout << "2.빌딩(" << a.getbuilding() << ")" << endl;
                movecursor(110, 21);
                cout << "3.호텔(" << a.gethotel() << ")" << endl;
                movecursor(110, 22);
                cout << "4.차례 종료";
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
                        cout << "잘못 입력하였습니다. 다시입력해주세요.";
                        cin.clear();
                    }
                }

                if (n == 1)
                {
                    if (*pMymoney < a.getvilla())
                    {
                        movecursor(110, 37);
                        cout << "돈이 부족합니다" << endl;
                        break;
                    }
                    if (build_cnt[num] >= 1) {
                        movecursor(110, 24);
                        cout << "이미 지어진 건물입니다." << endl;
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
                    if (*pMymoney < a.getbuilding() && build_cnt[num] == 1) // 펜션이 하나 있고, 추가로 빌딩을 지을라는데 돈이 없는 경우
                    {
                        movecursor(110, 37);
                        cout << "돈이 부족합니다. 추가로 건물을 지을 수 없습니다." << endl;
                        break;
                    }
                    else if (*pMymoney < a.getbuilding() + a.getvilla() && build_cnt[num] == 0) // 땅 밖에 없고, 한번에 두개 다살라는데 돈이 없는 경우
                    {
                        movecursor(110, 37);
                        cout << "돈이 부족합니다" << endl;
                        continue;
                    }

                    if (build_cnt[num] >= 2) {
                        movecursor(110, 24);
                        cout << "이미 지어진 건물입니다." << endl;
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
                        cout << "돈이 부족합니다. 추가로 건물을 지을 수 없습니다." << endl;
                        break;
                    }
                    else if (*pMymoney < a.gethotel() + a.getbuilding() && build_cnt[num] == 1)
                    {
                        movecursor(110, 37);
                        cout << "돈이 부족합니다" << endl;
                        continue;
                    }
                    else if (*pMymoney < a.gethotel() + a.getbuilding() + a.getvilla() && build_cnt[num] == 0) // 땅 밖에 없고, 한번에 세개 다살라는데 돈이 없는 경우
                    {
                        movecursor(110, 37);
                        cout << "돈이 부족합니다" << endl;
                        continue;
                    }

                    if (build_cnt[num] >= 3) {
                        movecursor(110, 24);
                        cout << "이미 지어진 건물입니다." << endl;
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
            cout << "1번 기부금 당첨~!!!" << endl;
            movecursor(110, 10);
            cout << "기부금을 지불합니다. 기부금은 20달러 입니다." << endl << endl;
            return 1;
        }
        else if (g == 2) {
            movecursor(110, 9);
            cout << "2번 우주왕복선 당첨~!!!" << endl;
            movecursor(110, 10);
            cout << "지금 당장 우주왕복선으로 이동합니다. " << endl << endl;
            return 2;
        }
        else if (g == 3) {
            movecursor(110, 9);
            cout << "3번 무인도 당첨~!!!" << endl;
            movecursor(110, 10);
            cout << "지금 당장 무인도로 이동합니다. " << endl << endl;
            return 3;
        }
        else if (g == 4) {
            movecursor(110, 9);
            cout << "4번 월급 보너스 당첨~!!!" << endl;
            movecursor(110, 10);
            cout << "지금 당장 월급을 한 번 더 지불 받습니다. " << endl << endl;
            *pMymoney = *pMymoney + 20;
            return 4;
        }
    } // return값마다 실행 조건 다름

    void view_land() {
        citycnt = 0;
        movecursor(15, 14);
        cout << "보유 도시";
        for (int i = 0; i < citynum; i++)
        {
            if (city[i] > 0)
            {
                movecursor(15, 15 + i);
                cout << myland_name[i] << " : " << myland_p[i] << "만원";
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
                break;// 내가 가진 도시중 현재 위치의 인덱스 찾기
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
int goldrandom(); //황금열쇠 랜덤값 반환함수
void next();

int main() {
    int n, n1, n2; //참가자수, 땅구매 결정 여부
    int nn; //도중 게임중지
    int cnt = 1; //턴수 변수
    int d = 0; //주사위 합
    int d1 = 0; //주사위1
    int d2 = 0; //주사위2
    int sp = 0; //우주왕복선 이동 변수
    int gk = 0; //황금열쇠 랜덤값
    int g = 0; //황금열쇠 번호
    int gameover = 0;
    int k = 0; //말 위치 초기화값
    string mal; //말 선정
    int just; //창 다시띄우기 위한 중간과정임
    int sell_num; //매각할 땅 번호
    int pasan = 0; //파산 카운트 게임셋

    City city[32] = {
     City(0,0,0,0,"0. 시작점",3,4),
     City(5,1,9,25,"1.타이베이",14,4),
     City(8,2,18,45,"2.베이징",25,4),
     City(8,2,18,45,"3.마닐라",36,4),
     City(0,0,0,0,"4. 황금열쇠",47,4),
     City(10,3,27,55,"5.싱가포르",58,4),
     City(10,3,27,55,"6.카이로",69,4),
     City(12,4,30,60,"7.이스탄불",80,4),
     City(0,0,0,0,"8. 무인도",91,4),
     City(14,5,45,75,"9.아테네",91,9),
     City(16,6,50,90,"10.코펜하겐",91,14),
     City(16,6,50,90,"11.스톡홀름",91,19),
     City(0,0,0,0,"12. 황금열쇠",91,24),
     City(18,7,50,95,"13.베른",91,29),
     City(18,7,50,95,"14.베를린",91,34),
     City(20,8,55,100,"15.오타와",91,39),
     City(0,0,0,0,"16.기부금",91,44),
     City(22,9,70,105,"17.부에노스아이레스",80,44),
     City(24,10,75,110,"18.상파울로",69,44),
     City(24,10,75,110,"19.시드니",58,44),
     City(0,0,0,0,"20. 황금열쇠",47,44),
     City(26,11,80,115,"21.하와이",36,44),
     City(26,11,80,115,"22.리스본",25,44),
     City(28,12,85,120,"23.마드리드",14,44),
     City(0,0,0,0,"24. 우주여행",3,44),
     City(30,13,90,127,"25.도쿄",3,39),
     City(32,15,100,140,"26.파리",3,34),
     City(32,15,100,140,"27.로마",3,29),
     City(0,0,0,0,"28. 황금열쇠",3,24),
     City(35,17,110,150,"29.런던",3,19),
     City(35,17,110,150,"30.뉴욕",3,14),
     City(100,0,0,0,"31.서울",3,9)
    }; //기본 도시 24, 황금열쇠 4, 시작지점, 무인도, 기부금 지역, 우주왕복선, 총 32개
    title();
    int menuCode = menuDraw();
    if (menuCode == 19) { cout << "게임을 종료합니다." << endl; return 0; }
    map();
    movecursor(3, 45);
    do {
        movecursor(110, 3);
        cout << "참가자 수를 설정하시오.(2~4명)";
        cin >> n;
        if (n < 2 || n>4) {
            system("cls");
            map();
            cin.clear();
            cin.ignore();
        }
        //참가자 수 2~4명 아니면 다시 입력
    } while (n < 2 || n > 4); //참가자가 2~4명이 아니면 다시 입력받게 한다.

    Player* pPlayer = new Player[n];
    Player::playernum(n);
    movecursor(110, 4);
    cout << "각자 주어진 돈은 " << pPlayer[0].getMymoney() << "달러 입니다." << endl << endl;   //게임 시작 안내문구
    next();
    system("cls");
    map();

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            pPlayer[i].setMal("★");
            k = 0;
        }
        if (i == 1) {
            pPlayer[i].setMal("●");
            k = 2;
        }
        if (i == 2) {
            pPlayer[i].setMal("◆");
            k = 4;
        }
        if (i == 3) {
            pPlayer[i].setMal("■");
            k = 6;
        }
        movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
        k = 0;
    }
    while (1) {
        movecursor(110, 3);

        cout << cnt << "번째 턴입니다." << endl << endl;
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
                cout << " 축하드립니다. 승리자는 ";
                for (int i = 0; i < n; i++) {
                    if (pPlayer[i].get_live() == 1) {
                        cout << i + 1 << "번 참가자 입니다." << endl;
                        movecursor(25, 26);
                        cout << "당신으로 인하여 나머지 " << n + 1 - i << "명은 이제 거지가 되었습니다.";
                        movecursor(25, 27); cout << i + 1 << "번 참가자의 현재 돈 : " << pPlayer[i].getMymoney();
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
            }//파산한 참가자 제외


            movecursor(110, 4);
            cout << i + 1 << "번 참가자의 차례입니다." << endl;
            if (pPlayer[i].getMooindo() != 0) {
                pPlayer[i].setMooindo();
                movecursor(110, 5);
                cout << "아직 무인도입니다." << endl;
                movecursor(110, 6);
                cout << "두 주사위의 숫자가 같으면 탈출합니다." << endl;
                d1 = dice1();
                d2 = dice2();
                if (d1 == d2) {
                    pPlayer[i].setMooindo(1);
                    movecursor(110, 7);
                    cout << d1 << " + " << d2 << " 축하합니다. 다음 턴에 무인도를 탈출합니다. " << endl << endl;
                }
                else {
                    movecursor(110, 7);
                    cout << "무인도를 탈출하지 못했습니다." << endl << endl;
                }
                k = 0;
                movecursor(110, 40);
                cout << "턴을 계속 진행하시겠습니까?(yes = 1/ no = 2)";
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
            } //참가자가 무인도에 있을경우 위에 동작만 실행

            movecursor(110, 5);
            cout << "주사위를 굴리겠습니다." << endl;
            movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
            d = dice1() + dice2(); //주사위1, 주사위2 합
            movecursor(110, 6);
            cout << d << " 이동하겠습니다." << endl;
            pPlayer[i].setMyplace(d); //참가자 주사위 수 만큼 이동
            movecursor(110, 7);
            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;

            movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
            movecursor(110, 8);
            if (pPlayer[i].getMyplace() == 0) {
                cout << "시작점입니다." << endl << endl;
                movecursor(110, 9);
                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
            } //시작지점에 걸림
            else if (pPlayer[i].getMyplace() == 8) {
                pPlayer[i].setMooindo();
                cout << "무인도 입니다. 3턴 쉽니다." << endl << endl;
            } // 참가자 무인도에 걸림
            else if (pPlayer[i].getMyplace() == 16) {
                cout << "지금까지 모인 기부금은 당신의 것입니다." << endl << endl;
                movecursor(110, 9);
                cout << "기부금 : " << Player::getgibu() << endl;
                pPlayer[i].setGibu(Player::getgibu());
                movecursor(110, 10);
                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                Player::resetgibu();
            } // 참가자 기부금 존에 걸림
            else if (pPlayer[i].getMyplace() == 24) {
                cout << "우주왕복선에 탑승했습니다. 원하는 위치를 입력하시오.";
                while (1) {

                    cin >> sp;
                    if (!cin) {
                        movecursor(20, 9);
                        cout << "다시입력해주세요";

                        cin.clear();
                        cin.ignore();

                    }
                    else if (sp >= 0 && sp <= 31) {
                        break;
                    }
                    movecursor(110, 12);
                    if (sp == 4 || sp == 12 || sp == 20 || sp == 28) {
                        cout << "황금열쇠로 이동하실 수 없습니다. 다시 입력하십시오.";
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
                cout << "에 오셨습니다." << endl;
                movecursor(110, 12);
                if (sp == 8) {
                    pPlayer[i].setMooindo();
                    cout << "무인도 입니다. 3턴 쉽니다." << endl << endl;
                }
                else if (sp == 16) {
                    cout << "지금까지 모인 기부금은 당신의 것입니다." << endl << endl;
                    movecursor(110, 13);
                    cout << "기부금 : " << Player::getgibu() << endl;
                    pPlayer[i].setGibu(Player::getgibu());
                    movecursor(110, 14);
                    cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                    Player::resetgibu();
                }
                else if (sp == 0) {
                    cout << "시작점입니다." << endl << endl;
                    movecursor(110, 13);
                    cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                }
                else {

                    if (city[pPlayer[i].getMyplace()].getowner() == 0)//주인없는 땅
                    {
                        if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//돈이 없는 경우
                        {
                            cout << city[pPlayer[i].getMyplace()].getName();
                            cout << "에서 할 수 있는 행동이 없습니다." << endl;
                        }
                        else
                        {
                            while (1)
                            {
                                cin.ignore();
                                n1 = 0;

                                cout << city[pPlayer[i].getMyplace()].getName();
                                cout << "에 오셨습니다. 땅을 사겠습니까? (yes = 1,no = 2)";
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
                                    cout << "잘못 입력하였습니다. 다시입력해주세요.";
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
                                cout << "를 구매하셨습니다." << endl;
                                movecursor(110, 14);
                                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            }
                            cout << endl;
                        }
                    }
                    else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//주인 있는 땅에 걸린경우
                    {
                        cout << city[pPlayer[i].getMyplace()].getName();
                        int own = city[pPlayer[i].getMyplace()].getowner() - 1;//현재 땅 주인 인덱스
                        cout << "에 오셨습니다." << "<" << own + 1 << "번 참가자의 땅>" << endl;
                        while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                        {
                            if (pPlayer[i].getcitycnt() == 0)
                            {
                                movecursor(25, 25);
                                cout << "ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ파산" << endl; // 우주왕복선 파산
                                pPlayer[i].bankrupt(city);
                                pasan = n - Player::getlive_cnt();
                                pPlayer[i].setMal("");
                                break;
                            }
                            else
                            {
                                movecursor(110, 9);
                                cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "만원을 지불합니다.";
                                movecursor(20, 7);
                                cout << "소지한 돈이 부족합니다. 보유한 땅을 매각하세요.";
                                movecursor(20, 8);
                                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                                pPlayer[i].view_land();
                                movecursor(20, 9);
                                cout << "매각할 땅의 번호를 선택하시오.";
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
                                    cout << "소유하지 않은 도시번호입니다." << endl;
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
                            cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게 남은 돈 " << pPlayer[i].getMymoney() << "원을 전달 후 파산합니다.";
                            pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// 파산 후 남은 돈 땅주인에게 전달
                            while (1) {
                                cin.ignore();
                                nn = 0;
                                movecursor(25, 27);
                                cout << "숫자 1을 입력하세요";
                                cin >> nn;
                                if (nn == 1) {
                                    break;
                                }
                                else {
                                    movecursor(25, 28);
                                    cout << "잘못입력하였습니다. 다시 입력해 주세요 : ";
                                    cin.clear();
                                }
                            }
                            continue;
                        }
                        pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅값만큼 차감
                        pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅주인 돈 증가;
                        movecursor(110, 26);
                        cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게";
                        cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "만원을 지불합니다." << endl;
                        movecursor(110, 27);
                        cout << "토지를 매입 하시겠습니까?(yes = 1, no = 2)";
                        cin >> n1;
                        if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                        {
                            pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                                pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                            pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                            city[pPlayer[i].getMyplace()].setowner(i + 1);//새로운 땅 주인 인덱스 설정
                            pPlayer[i].get_myland_index();
                            movecursor(110, 13);
                            cout << "토지 매입 완료" << endl;
                            movecursor(110, 14);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                        }
                        else
                        {
                            movecursor(110, 37);
                            cout << "돈이 부족합니다." << endl;
                            movecursor(110, 38);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                        }

                    }
                    else
                    {

                        cout << "에 오셨습니다." << endl;
                        movecursor(110, 13);
                        cout << "현재 건물 수 : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "개" << endl;
                        movecursor(110, 14);
                        cout << "추가건물을 짓겠습니까 ? (yes = 1, no = 2)";

                        cin >> n1;
                        if (n1 == 1)
                        {
                            pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                            movecursor(110, 25);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                        }
                        //건물 주인 건물 구매 코드

                    }
                }
                k = 0;
            }
            else if (pPlayer[i].getMyplace() == 4 || pPlayer[i].getMyplace() == 12 || pPlayer[i].getMyplace() == 20 || pPlayer[i].getMyplace() == 28) {
                cout << "황금 열쇠를 획득하셨습니다." << endl;
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
                                cout << "파산ㅋㅋㅋㅋㅋㅋ" << endl; // 기부금 파산
                                pPlayer[i].bankrupt(city);
                                pasan = n - Player::getlive_cnt();
                                pPlayer[i].setMal("");
                                break;
                            }
                            else
                            {
                                movecursor(20, 7);
                                cout << "소지한 돈이 부족합니다. 보유한 땅을 매각하세요.";
                                pPlayer[i].view_land();
                                movecursor(20, 8);
                                cout << "매각할 땅의 번호를 선택하시오.";
                                int sell_num;
                                cin >> sell_num;
                                if (pPlayer[i].matching(sell_num) == 1)
                                {
                                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                    pPlayer[i].land_sell(sell_num, city[sell_num]);
                                }
                                else {
                                    cout << "소유하지 않은 도시번호입니다." << endl;
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
                            cout << "남은 돈 " << pPlayer[i].getMymoney() << "원이 기부금 보다 적어 파산합니다.";
                            while (1) {
                                cin.ignore();
                                nn = 0;
                                movecursor(25, 27);
                                cout << "숫자 1을 입력하세요";
                                cin >> nn;
                                if (nn == 1) {
                                    break;
                                }
                                else {
                                    movecursor(25, 28);
                                    cout << "잘못입력하였습니다. 다시 입력해 주세요 : ";
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
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                    }

                }

                else if (g == 2) {
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                    pPlayer[i].setSpace(24);
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    movecursor(110, 11);
                    cout << "우주왕복선에 탑승했습니다. 원하는 위치를 입력하시오.";
                    while (1) {

                        while (1) {

                            cin >> sp;

                            if (!cin) {
                                movecursor(20, 9);
                                cout << "다시입력해주세요";

                                cin.clear();
                                cin.ignore();

                            }
                            else if (sp >= 0 && sp <= 31) {
                                break;
                            }
                        }

                        movecursor(110, 12);
                        if (sp == 4 || sp == 12 || sp == 20 || sp == 28) {
                            cout << "황금열쇠로 이동하실 수 없습니다. 다시 입력하십시오.";
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
                    cout << "에 오셨습니다." << endl;
                    movecursor(110, 15);
                    if (sp == 8) {
                        pPlayer[i].setMooindo();
                        cout << "무인도 입니다. 3턴 쉽니다." << endl << endl;
                    }
                    else if (sp == 16) {
                        cout << "지금까지 모인 기부금은 당신의 것입니다." << endl;
                        movecursor(110, 16);
                        cout << "기부금 : " << Player::getgibu() << endl;
                        pPlayer[i].setGibu(Player::getgibu());
                        movecursor(110, 17);
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                        Player::resetgibu();
                    }
                    else if (sp == 0) {
                        cout << "시작점입니다." << endl << endl;
                        movecursor(110, 16);
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                    }
                    else {

                        if (city[pPlayer[i].getMyplace()].getowner() == 0)//주인없는 땅
                        {
                            if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//돈이 없는 경우
                            {
                                cout << city[pPlayer[i].getMyplace()].getName();
                                cout << "에서할 수 있는 행동이 없습니다." << endl;
                            }
                            else
                            {
                                while (1)
                                {
                                    cin.ignore();
                                    n1 = 0;
                                    cout << city[pPlayer[i].getMyplace()].getName();
                                    cout << "에 오셨습니다. 땅을 사겠습니까? (yes = 1,no = 2)";
                                    cin >> n1;
                                    if (n1 == 1)
                                    {
                                        break;
                                    }
                                    else if (n1 == 2)
                                    {
                                        movecursor(110, 27);
                                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                                        break;
                                    }
                                    else
                                    {
                                        movecursor(15, 10);
                                        cout << "잘못 입력하였습니다. 다시입력해주세요.";
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
                                    cout << "를 구매하셨습니다." << endl;
                                    movecursor(110, 29);
                                    cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                                }
                                cout << endl;
                            }
                        }
                        else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//주인 있는 땅에 걸린경우
                        {
                            cout << city[pPlayer[i].getMyplace()].getName();
                            int own = city[pPlayer[i].getMyplace()].getowner() - 1;//현재 땅 주인 인덱스
                            cout << "에 오셨습니다." << "<" << own + 1 << "번 참가자의 땅>" << endl;
                            while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                            {
                                if (pPlayer[i].getcitycnt() == 0)
                                {
                                    movecursor(25, 25);
                                    cout << "파산ㅋㅋ" << endl; // 황금열쇠에서 우주왕복선 갔다가 주인 있는 땅 밟고 파산
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
                                    cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "만원을 지불합니다.";
                                    movecursor(20, 7);
                                    cout << "소지한 돈이 부족합니다. 보유한 땅을 매각하세요.";
                                    pPlayer[i].view_land();
                                    movecursor(20, 8);
                                    cout << "매각할 땅의 번호를 선택하시오.";
                                    int sell_num;
                                    cin >> sell_num;
                                    if (pPlayer[i].matching(sell_num) == 1)
                                    {
                                        pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                        pPlayer[i].land_sell(sell_num, city[sell_num]);
                                    }
                                    else {
                                        cout << "소유하지 않은 도시번호입니다." << endl;
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
                                cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게 남은 돈 " << pPlayer[i].getMymoney() << "원을 전달 후 파산합니다.";
                                pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// 파산 후 남은 돈 땅주인에게 전달
                                while (1) {
                                    cin.ignore();
                                    nn = 0;
                                    movecursor(25, 27);
                                    cout << "숫자 1을 입력하세요";
                                    cin >> nn;
                                    if (nn == 1) {
                                        break;
                                    }
                                    else {
                                        movecursor(25, 28);
                                        cout << "잘못입력하였습니다. 다시 입력해 주세요 : ";
                                        cin.clear();
                                    }
                                }
                                continue;
                            }
                            pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅값만큼 차감
                            pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅주인 돈 증가;
                            movecursor(110, 16);
                            cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게";
                            cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "원을 지불합니다." << endl;
                            movecursor(110, 17);
                            cout << "토지를 매입 하시겠습니까?(yes = 1, no = 2)";
                            cin >> n1;
                            movecursor(110, 18);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                            {
                                pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                                    pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                                pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                                city[pPlayer[i].getMyplace()].setowner(i + 1);//새로운 땅 주인 인덱스 설정
                                pPlayer[i].get_myland_index();
                                movecursor(110, 21);
                                cout << "토지 매입 완료" << endl;
                                movecursor(110, 22);
                                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            }
                            else
                            {
                                movecursor(110, 27);
                                cout << "돈이 부족합니다." << endl;
                                movecursor(110, 28);
                                cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            }
                        }
                        else
                        {
                            cout << city[pPlayer[i].getMyplace()].getName() << "에 오셨습니다." << endl;
                            movecursor(110, 16);
                            cout << "현재 건물 수 : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "개" << endl;
                            while (1) {
                                cin.ignore();
                                n1 = 0;
                                movecursor(110, 17);
                                cout << "추가건물을 짓겠습니까 ? (yes = 1, no = 2)";
                                cin >> n1;
                                if (n1 == 1)
                                {
                                    pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                                    movecursor(110, 26);
                                    cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                                    break;

                                }
                                else if (n1 == 2) {
                                    break;
                                }
                                else {
                                    movecursor(110, 18);
                                    cout << "잘못 입력하였습니다. 다시입력해주세요.";
                                    cin.clear();
                                }
                            }

                            //건물 주인 건물 구매 코드
                        }
                    }
                    k = 0;
                } //우주왕복선 황금열쇠 뽑을 경우
                else if (g == 3) {
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << "  " << endl;
                    pPlayer[i].setSpace(8);
                    movecursor(city[pPlayer[i].getMyplace()].getx() + k, city[pPlayer[i].getMyplace()].gety()); cout << pPlayer[i].getMal() << endl;
                    pPlayer[i].setMooindo();
                    movecursor(110, 11);
                    cout << "무인도 입니다. 3턴 쉽니다." << endl << endl;
                    k = 0;
                } //무인도 황금열쇠 뽑을 경우 , 1과 4는 goldkey함수에서 이미 동작 완료
                else if (g == 4) {
                    cout << endl;
                    movecursor(110, 13);
                    cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                }
            } //참가자 황금열쇠 획득함
            else {

                if (city[pPlayer[i].getMyplace()].getowner() == 0)//주인없는 땅
                {
                    if (pPlayer[i].getMymoney() < city[pPlayer[i].getMyplace()].getPrice())//돈이 없는 경우
                    {
                        cout << city[pPlayer[i].getMyplace()].getName();
                        cout << "에서 할 수 있는 행동이 없습니다." << endl;
                    }
                    else
                    {
                        while (1)
                        {
                            cin.ignore();
                            n1 = 0;
                            cout << city[pPlayer[i].getMyplace()].getName();
                            cout << "에 오셨습니다. 땅을 사겠습니까? (yes = 1,no = 2)";
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
                                cout << "잘못 입력하였습니다. 다시입력해주세요.";
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
                            cout << "를 구매하셨습니다." << endl;
                            movecursor(110, 14);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                        }
                        cout << endl;
                    }
                }
                else if (city[pPlayer[i].getMyplace()].getowner() != i + 1)//주인 있는 땅에 걸린경우
                {
                    cout << city[pPlayer[i].getMyplace()].getName();
                    int own = city[pPlayer[i].getMyplace()].getowner() - 1;//현재 땅 주인 인덱스
                    cout << "에 오셨습니다." << "<" << own + 1 << "번 참가자의 땅>" << endl;
                    while (pPlayer[i].getMymoney() < pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                    {
                        if (pPlayer[i].getcitycnt() == 0)
                        {
                            movecursor(25, 25);
                            cout << "ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ파산" << endl;//그냥 이동 중 파산
                            pPlayer[i].bankrupt(city);
                            pasan = n - Player::getlive_cnt();
                            pPlayer[i].setMal("");
                            break;
                        }
                        else
                        {
                            movecursor(110, 9);
                            cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "만원을 지불합니다.";
                            movecursor(110, 10);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            movecursor(20, 7);
                            cout << "소지한 돈이 부족합니다. 보유한 땅을 매각하세요.";
                            pPlayer[i].view_land();
                            movecursor(20, 8);
                            cout << "매각할 땅의 번호를 선택하시오.";
                            int sell_num;
                            cin >> sell_num;
                            if (pPlayer[i].matching(sell_num) == 1)
                            {
                                pPlayer[i].setMymoney(pPlayer[i].getMymoney() + pPlayer[i].getmyland_p(sell_num));
                                pPlayer[i].land_sell(sell_num, city[sell_num]);
                            }
                            else
                            {
                                cout << "소유하지 않은 도시번호입니다." << endl;
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
                        cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게 남은 돈 " << pPlayer[i].getMymoney() << "원을 전달 후 파산합니다.";
                        pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[i].getMymoney());// 파산 후 남은 돈 땅주인에게 전달
                        while (1) {
                            cin.ignore();
                            nn = 0;
                            movecursor(25, 27);
                            cout << "숫자 1을 입력하세요";
                            cin >> nn;
                            if (nn == 1) {
                                break;
                            }
                            else {
                                movecursor(25, 28);
                                cout << "잘못입력하였습니다. 다시 입력해 주세요 : ";
                                cin.clear();
                            }
                        }
                        continue;
                    }
                    pPlayer[i].setMymoney(pPlayer[i].getMymoney() - pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅값만큼 차감
                    pPlayer[own].setMymoney(pPlayer[own].getMymoney() + pPlayer[own].getmyland_p(pPlayer[i].getMyplace()));//땅주인 돈 증가;
                    movecursor(110, 11);
                    cout << city[pPlayer[i].getMyplace()].getowner() << "번 참가자에게";
                    cout << pPlayer[own].getmyland_p(pPlayer[i].getMyplace()) << "원을 지불합니다." << endl;
                    movecursor(110, 12);

                    while (1) {
                        cin.ignore();
                        n1 = 0;
                        cout << "토지를 매입 하시겠습니까?(yes = 1, no = 2)";
                        cin >> n1;
                        if (n1 == 1) {
                            break;
                        }
                        else if (n1 == 2)
                        {
                            movecursor(110, 13);
                            cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                            break;
                        }
                        else {
                            movecursor(15, 10);
                            cout << "잘못 입력하였습니다. 다시입력해주세요. : ";
                            cin.clear();
                            movecursor(15, 11);
                        }
                    }

                    if (n1 == 1 && pPlayer[i].getMymoney() > pPlayer[own].getmyland_p(pPlayer[i].getMyplace()))
                    {
                        pPlayer[i].land_purchase(pPlayer[own].getmyland_p(pPlayer[i].getMyplace()), pPlayer[i].getMyplace(),
                            pPlayer[own].get_buid_cnt(pPlayer[i].getMyplace()), city[pPlayer[i].getMyplace()], city[pPlayer[i].getMyplace()].getName());
                        pPlayer[own].land_sell(pPlayer[i].getMyplace(), city[pPlayer[i].getMyplace()]);
                        city[pPlayer[i].getMyplace()].setowner(i + 1);//새로운 땅 주인 인덱스 설정
                        pPlayer[i].get_myland_index();
                        movecursor(110, 13);
                        cout << "토지 매입 완료" << endl;
                        movecursor(110, 14);
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                    }
                    else if (n1 == 2)
                    {
                    }
                    else
                    {
                        movecursor(110, 27);
                        cout << "돈이 부족합니다." << endl;
                        movecursor(110, 28);
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;
                    }

                }
                else
                {
                    cout << city[pPlayer[i].getMyplace()].getName();
                    cout << "에 오셨습니다." << endl;
                    movecursor(110, 11);
                    cout << "현재 건물 수 : " << pPlayer[i].get_buid_cnt(pPlayer[i].getMyplace()) << "개" << endl;
                    movecursor(110, 12);
                    cout << "추가건물을 짓겠습니까 ? (yes = 1, no = 2)";

                    cin >> n1;
                    if (n1 == 1)
                    {
                        pPlayer[i].add_building(city[pPlayer[i].getMyplace()], pPlayer[i].getMyplace());
                        movecursor(110, 30);
                        cout << i + 1 << "번 참가자 돈 : " << pPlayer[i].getMymoney() << endl;

                    }
                    //건물 주인 건물 구매 코드
                }
            }
            movecursor(110, 40);
            while (1) {
                cin.ignore();
                nn = 0;
                cout << "턴을 계속 진행하시겠습니까?(yes = 1/ no = 9)";
                cin >> nn;
                if (nn == 1) {
                    break;
                }
                else if (nn == 9) {
                    exit(1);
                }
                else {
                    movecursor(15, 10);
                    cout << "잘못 입력하였습니다. 다시입력해주세요. : ";
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
    cout << "♥전체화면 후 space bar를 눌러 게임을 시작해주세요♥";
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
    //   temp = _getch(); //잘못입력되었으므로 다시 입력 받게끔

    //}
}
void map() {
    //system("mode con cols=150 lines=150 | title 창 제목");
    cout << " ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " ├──────────┼──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┼──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┤                                                                            ├──────────┤" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " │          │                                                                            │          │" << endl;
    cout << " ├──────────┼────────────────────────────────────────────────────────────────────────────┼──────────┤" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " │          │          │          │          │          │          │          │          │          │" << endl;
    cout << " └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘" << endl;
    movecursor(3, 2); cout << "출발-->" << endl; movecursor(3, 1); cout << "(0)" << endl;
    movecursor(14, 1); cout << "타이페이" << endl; movecursor(14, 2); cout << "5만원(1)" << endl;
    movecursor(25, 1); cout << "베이징" << endl; movecursor(25, 2); cout << "8만원(2)" << endl;
    movecursor(36, 1); cout << "마닐라" << endl; movecursor(36, 2); cout << "8만원(3)" << endl;
    movecursor(47, 2); cout << "황금열쇠!" << endl; movecursor(47, 1); cout << "(4)" << endl;
    movecursor(58, 1); cout << "싱가포르" << endl; movecursor(58, 2); cout << "10만원(5)" << endl;
    movecursor(69, 1); cout << "카이로" << endl; movecursor(69, 2); cout << "10만원(6)" << endl;
    movecursor(80, 1); cout << "이스탄불" << endl; movecursor(80, 2); cout << "12만원(7)" << endl;
    movecursor(91, 2); cout << "무인도↓" << endl; movecursor(91, 1); cout << "(8)" << endl;

    movecursor(91, 6); cout << "아테네" << endl; movecursor(91, 7); cout << "14만원(9)" << endl;
    movecursor(91, 11); cout << "코펜하겐" << endl; movecursor(91, 12); cout << "16만원(10)" << endl;
    movecursor(91, 16); cout << "스톡홀름" << endl; movecursor(91, 17); cout << "16만원(11)" << endl;
    movecursor(91, 22); cout << "황금열쇠!" << endl; movecursor(91, 21); cout << "(12)" << endl;
    movecursor(91, 26); cout << "베른" << endl; movecursor(91, 27); cout << "18만원(13)" << endl;
    movecursor(91, 31); cout << "베를린" << endl; movecursor(91, 32); cout << "18만원(14)" << endl;
    movecursor(91, 36); cout << "오타와" << endl; movecursor(91, 37); cout << "20만원(15)" << endl;
    movecursor(91, 42); cout << "←사회복지금!" << endl; movecursor(91, 41); cout << "(16)" << endl;

    movecursor(80, 41); cout << "부에노스" << endl; movecursor(80, 42); cout << "22만원(17)" << endl;
    movecursor(69, 41); cout << "상파울로" << endl; movecursor(69, 42); cout << "24만원(18)" << endl;
    movecursor(58, 41); cout << "시드니" << endl; movecursor(58, 42); cout << "24만원(19)" << endl;
    movecursor(47, 42); cout << "황금열쇠!" << endl; movecursor(47, 41); cout << "(20)" << endl;
    movecursor(36, 41); cout << "하와이" << endl; movecursor(36, 42); cout << "26만원(21)" << endl;
    movecursor(25, 41); cout << "리스본" << endl; movecursor(25, 42); cout << "26만원(22)" << endl;
    movecursor(14, 41); cout << "마드리드" << endl; movecursor(14, 42); cout << "28만원(23)" << endl;
    movecursor(3, 42); cout << "우주여행↑" << endl; movecursor(3, 41); cout << "(24)" << endl;

    movecursor(3, 36); cout << "도쿄" << endl; movecursor(3, 37); cout << "30만원(25)" << endl;
    movecursor(3, 31); cout << "파리" << endl; movecursor(3, 32); cout << "32만원(26)" << endl;
    movecursor(3, 26); cout << "로마" << endl; movecursor(3, 27); cout << "32만원(27)" << endl;
    movecursor(3, 22); cout << "황금열쇠!" << endl; movecursor(3, 21); cout << "(28)" << endl;
    movecursor(3, 16); cout << "런던" << endl; movecursor(3, 17); cout << "35만원(29)" << endl;
    movecursor(3, 11); cout << "뉴욕" << endl; movecursor(3, 12); cout << "35만원(30)" << endl;
    movecursor(3, 6); cout << "서울" << endl; movecursor(3, 7); cout << "100만원(31)" << endl;

    //movecursor(3, 45);//좌표 위치를 다른대로 보냄으로써 콘솔창에 중간에 끼는것을 방지
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
    di1 = dis(gen); //1번 주사위 1~6 랜덤지정
    return di1;      //주사위 값 반환
}
int dice2() {
    int di2 = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 6);
    di2 = dis(gen); //2번 주사위 1~6 랜덤지정
    return di2;      //주사위 값 반환
}
int goldrandom() {
    int gk = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 4);
    gk = dis(gen);
    return gk;
} //황금열쇠 랜덤값 반환5