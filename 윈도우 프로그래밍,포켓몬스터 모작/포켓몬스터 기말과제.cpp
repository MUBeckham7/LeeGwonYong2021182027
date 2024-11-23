#include <windows.h> //--- 윈도우 헤더 파일
#include <TCHAR.H>
#include "resource.h"
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "msimg32.lib")
static int scene = 0; // 장면나누기
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASSEX WndClass;
    g_hInst = hInstance;
    WndClass.cbSize = sizeof(WndClass);
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = lpszClass;
    WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WndClass);
    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW , 0, 0, 800, 680, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

void BackGround0(HDC hdc, HWND hwnd) { //뒷배경
    HDC memdc;
    HBITMAP hbitmap;
    hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP38));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, hbitmap);
    StretchBlt(hdc, 0, 150, 800, 400, memdc, 0, 0, 371, 176, SRCCOPY);
    DeleteDC(memdc);
}

void BackGround4(HDC hdc, HWND hwnd) { //뒷배경
    HDC memdc;
    HBITMAP hbitmap;
    hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP39));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, hbitmap);
    StretchBlt(hdc, 0, 150, 800, 400, memdc, 0, 0, 321, 285, SRCCOPY);
    DeleteDC(memdc);
}

void BackGround1(int HeroX,int HeroY,int BackX, int BackY, HDC hdc, HWND hwnd) { //뒷배경
    HDC memdc;
    HBITMAP hbitmap;
    hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, hbitmap);
    StretchBlt(hdc, BackX, BackY, 1000, 500, memdc, 0, 0,800,440, SRCCOPY);
    DeleteDC(memdc);
}

void BackGround2(int BackX, int BackY, HDC hdc, HWND hwnd) { //뒷배경
    HDC memdc;
    HBITMAP hbitmap;

    hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, hbitmap);
    StretchBlt(hdc, BackX, BackY, 1200, 500, memdc, 0 , 0 ,800, 400, SRCCOPY);
    DeleteDC(memdc);
}

void AnimationR(int HeroX, int HeroY, HDC hdc, HWND hwnd) {
    HDC memdc;
    HBITMAP WalkBit[3], Mask[3];
    static int count = 0;
    int i = 0;
    count++;

    count = count % 3;
    WalkBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
    WalkBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
    WalkBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
    Mask[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    Mask[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
    Mask[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, Mask[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCAND);
    SelectObject(memdc, WalkBit[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCPAINT);
    DeleteObject(WalkBit[0]);
    DeleteObject(WalkBit[1]);
    DeleteObject(WalkBit[2]);
    DeleteObject(Mask[0]);
    DeleteObject(Mask[1]);
    DeleteObject(Mask[2]);
    DeleteDC(memdc);
    //SetTimer(hwnd, 22, 1000, NULL);
}

void AnimationU(int HeroX, int HeroY, HDC hdc, HWND hwnd) {
    HDC memdc;
    HBITMAP WalkBit[3], Mask[3];
    static int count=0;
    int i=0;
    count++;

    count = count % 3;
    WalkBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
    WalkBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
    WalkBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
    Mask[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
    Mask[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
    Mask[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, Mask[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCAND);
    SelectObject(memdc, WalkBit[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCPAINT);
    DeleteObject(WalkBit[0]);
    DeleteObject(WalkBit[1]);
    DeleteObject(WalkBit[2]);
    DeleteObject(Mask[0]);
    DeleteObject(Mask[1]);
    DeleteObject(Mask[2]);
    DeleteDC(memdc);
    //SetTimer(hwnd, 22, 1000, NULL);
}

void AnimationL(int HeroX, int HeroY, HDC hdc, HWND hwnd) {
    HDC memdc;
    HBITMAP WalkBit[3], Mask[3];
    static int count=0;
    int i = 0;
    count++;

    count = count % 3;
    WalkBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22));
    WalkBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
    WalkBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24));
    Mask[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP25));
    Mask[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26));
    Mask[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP27));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, Mask[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCAND);
    SelectObject(memdc, WalkBit[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCPAINT);
    DeleteObject(WalkBit[0]);
    DeleteObject(WalkBit[1]);
    DeleteObject(WalkBit[2]);
    DeleteObject(Mask[0]);
    DeleteObject(Mask[1]);
    DeleteObject(Mask[2]);
    DeleteDC(memdc);
    //SetTimer(hwnd, 44, 1000, NULL);
}

void AnimationD(int HeroX, int HeroY, HDC hdc, HWND hwnd) {
    HDC memdc;
    HBITMAP WalkBit[3], Mask[3];
    static int count=0;
    int i=0;
    count++;

    count = count % 3;
    WalkBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
    WalkBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
    WalkBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));
    Mask[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
    Mask[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
    Mask[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, Mask[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCAND);
    SelectObject(memdc, WalkBit[count]);
    BitBlt(hdc, HeroX, HeroY, 70, 70, memdc, 0, 0, SRCPAINT);
    DeleteObject(WalkBit[0]);
    DeleteObject(WalkBit[1]);
    DeleteObject(WalkBit[2]);
    DeleteObject(Mask[0]);
    DeleteObject(Mask[1]);
    DeleteObject(Mask[2]);
    DeleteDC(memdc);
    //SetTimer(hwnd, 33, 1000, NULL);
}
//이제 충돌 함수 구현하고
// 죽는 애니메이션 구현하면 끝.


void P_SHOWS(HDC hdc, HDC memdc); // 피카츄 
void F_SHOWS(HDC hdc, HDC memdc, int a); // 파이리
void B_SHOWS(HDC hdc, HDC memdc, int a); // 잠만보
void G_SHOWS(HDC hdc, HDC memdc, int a); // 이상해씨
void R_SHOWS(HDC hdc, HDC memdc, int a); // 롱스톤
void W_SHOWS(HDC hdc, HDC memdc, int a); // 꼬부기
void M1_SHOWS(HDC hdc, HDC memdc);
void M2_SHOWS(HDC hdc, HDC memdc);
void M3_SHOWS(HDC hdc, HDC memdc);

void M1_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 갸라도스
void M2_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 코뿌리
void M3_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 망나뇽

void P_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 피카츄 기술
void F_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 파이리 
void B_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 잠만보
void G_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 이상해씨
void R_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 롱스톤
void W_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a); // 꼬부기

void P_SKILL_BUTTON(HDC hdc, HDC memdc); // 피카츄
void B_SKILL_BUTTON(HDC hdc, HDC memdc); // 파이리
void G_SKILL_BUTTON(HDC hdc, HDC memdc); // 잠만보
void R_SKILL_BUTTON(HDC hdc, HDC memdc); // 이상해씨
void W_SKILL_BUTTON(HDC hdc, HDC memdc); // 롱스톤
void F_SKILL_BUTTON(HDC hdc, HDC memdc); // 꼬부기

void GET_POKEMON(HDC hdc, HDC memdc); // 잡기
void APPEAR_POKEMON(HDC hdc, HDC memdc); // 볼에서 등장(주인공)
void D_APPEAR_POKEMON(HDC hdc, HDC memdc); // 볼에서 등장(적)

static int xpos = 80, ypos = 220, d_xpos = 550, d_ypos = 30, size = 200, xsize = 200, d_xsize = 200, ysize = 200, d_ysize = 200;
static HBITMAP background, P, F, B, G, R, W, oldbit;
static HBITMAP hpbar0,hpbar1,hpbar2,hpbar3,hpbar4,hpbar5,hpbar7,hpbar8,hpbar9,hpbar10,hpbar11;
static HBITMAP P_SKILL[2], F_SKILL[3], W_SKILL[3], R_SKILL[2], G_SKILL[2], B_SKILL[3];
static HBITMAP M1, M2, M3;                      // 목호(최종전) 포켓몬
static HBITMAP M3_SKILL;
static BOOL P_SHOW = true, F_SHOW = true, B_SHOW = true, G_SHOW = true, R_SHOW = true, W_SHOW = true; // 나와있는 포켓몬마다 스킬 유무
static BOOL M1_SHOW = true, M2_SHOW = true, M3_SHOW = true;  // 나와있는 포켓몬마다 스킬 유무
static BOOL hit = false, d_hit = false, skill[18]; // 주인공, 상대 맞는거
static BOOL RETURNMAP = false;
static int cnt = 0, s_cnt = 0;
static HBITMAP POKE_BALL;
static int s1=0, s2=0, s3=0, s4=0, s5=0, s6=0;

static HBITMAP ELECTRO_BUTTON, STEAL_BUTTON, NORMAL_BUTTON, GRASS_BUTTON, POISON_BUTTON, ROCK_BUTTON, GROUND_BUTTON, WATER_BUTTON, FIRE_BUTTON, DRAGON_BUTTON;
static BOOL THROW_ball = false, d_THROW_ball = false, GET_poke = false, disappear = false;
static int ball_cnt = 0; // 몬스터볼
static int ball_xpos = -30, ball_ypos = 120, d_ball_xpos = 800, d_ball_ypos = -80, g_ball_xpos = -30, g_ball_ypos = 280; // 볼 시작위치
static int xscript = 0, yscript = 0, d_xscript = 161 * 2, d_yscript = 0;

static int f1_cnt = 0; // 화염방사
static int f2_cnt = 0; // 드래곤테일

static int w_xpos[2] = { 20, 500 }, w_ypos[2] = { 170, -50 }, w1_cnt = 0; // 파도타기
static int w2_cnt = 0;                                         // 고속스핀

static int r_xpos[2] = { 550, 80 }, r_ypos[2] = { -50, 140 }, r1_cnt = 0; // 돌떨구기
static int r2_xpos = 0, r2_ypos = 0, r2_cnt = 0;                     // 지진

static int g_xpos[2] = { 80, 550 }, g_ypos[2] = { 220, 30 }, g1_cnt = 0; // 꽃잎댄스
static int g2_xpos[2] = { 80, 550 }, g2_ypos[2] = { 220, 30 }, g2_cnt = 0; // 오물폭탄

static int b_xpos[2] = { 80, 550 }, b_ypos[2] = { 220, 30 }, b1_cnt = 0; // 기가임팩트
static int b2_cnt = 0;                                        // 파괴광선
// M1_1(W1) 파도타기
 // M2_1(R2) 지진 M2_2(B1) 기가임팩트
// M3_1(F1) 화염방사 M3_2 드래곤다이브
// P1 10만볼트 P2 아이언테일
// F1 화염방사 F2 드래곤테일
// B1 기가임팩트 B2 파괴광선
// G1 꽃잎댄스 G2 오물폭탄
// R1 돌떨구기 R2 지진
// W1 파도타기 W2 고속스핀
static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4,  Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
static int M1hp = 8, M2hp = 8,  M3hp = 8;//갸라도스,코뿌리,망나뇽 hp
static int Patt1 = 2, Patt2 = 2;//피카츄 스킬  백만볼트 데미지 2 아이언테일 2
static int Fatt1 = 1, Fatt2 = 1;//파이리 스킬  
static int Batt1 = 2, Batt2 = 2;
static int Gatt1 = 1, Gatt2 = 1;
static int Ratt1 = 1, Ratt2 = 1;
static int Watt1 = 1, Watt2 = 1;
static int M1att = 2, M2att = 2, M3att1 = 2, M3att2 = 2;
static int a_cnt = 0;
static int timecnt = 0;
 static int map1=0, map2=0;
 static int enter = 0;
 static int finish_cnt;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc,memdc;
    PAINTSTRUCT ps;
    static int BackX, BackY;
    static int HeroX, HeroY;
    static int RA, LA, UA, DA;
   
    static int mx, my;
    switch (uMsg) {
    case WM_CREATE:
        BackX = 0, BackY = 0;
        HeroX = 240, HeroY = 270;
        RA = 0, LA = 0, DA = 0, UA = 0;
     

        background = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_0BACKGROUND));

        for (int i = 0; i < 13; i++) {
            skill[i] = false;
        }

       SetTimer(hwnd, 1, 200, NULL);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        memdc = CreateCompatibleDC(hdc);
       
      
        if (scene == 0 && map1 == 0) {
            if (enter == 0) {
                BackGround0(hdc, hwnd);
            }
            else if(enter == 1)
            BackGround1(HeroX, HeroY, BackX, BackY, hdc, hwnd);

           // PlaySound(L"46-Route-32.wav", NULL, SND_LOOP);
        }
                if (enter != 2 && scene == 0 && map2 == 1) {
                    if( enter==1 )
                    BackGround2(BackX, BackY, hdc, hwnd);
                }
                if(scene ==0 && RA == 1)
                    AnimationR(HeroX, HeroY, hdc, hwnd);
                if (scene == 0 &&  UA== 1)
                    AnimationU(HeroX, HeroY, hdc, hwnd);
                if (scene == 0 && DA == 1)
                    AnimationD(HeroX, HeroY, hdc, hwnd);
                if(scene == 0 && LA==1)
                    AnimationL(HeroX, HeroY, hdc, hwnd);  
                if (enter == 2) {
                    InvalidateRect(hwnd, NULL, TRUE);
                    scene = 0;
                    enter = 3;
                }
                if (enter == 3) {
                    LA = 0, UA = 0, DA = 0, RA = 0;
                    BackGround4(hdc, hwnd);
                }

        if (scene > 0) {
            memdc = CreateCompatibleDC(hdc);

            oldbit = (HBITMAP)SelectObject(memdc, background);
            StretchBlt(hdc, 0, 0, 790, 650, memdc, 0, 0, 779, 709, SRCCOPY);
        }

        if (scene == 1) {
            if (!THROW_ball)
                P_SHOWS(hdc, memdc);
            if (!disappear)B_SHOWS(hdc, memdc, 1);

        }
        if (scene == 2) {
            if (P_SHOW)
                if (!THROW_ball)P_SHOWS(hdc, memdc);
            if (!P_SHOW)
                if (!THROW_ball)B_SHOWS(hdc, memdc, 0);

            if (!disappear)G_SHOWS(hdc, memdc, 1);
        }
        if (scene == 3) {
            if (P_SHOW)
                if (!THROW_ball)P_SHOWS(hdc, memdc);
            if (!P_SHOW) {
                if (B_SHOW)
                    if (!THROW_ball)B_SHOWS(hdc, memdc, 0);
                if (!B_SHOW)
                    if (!THROW_ball)G_SHOWS(hdc, memdc, 0);
            }
            if (!disappear)R_SHOWS(hdc, memdc, 1);
        }
        if (scene == 4) {
            if (P_SHOW)
                if (!THROW_ball) P_SHOWS(hdc, memdc);
            if (!P_SHOW) {
                if (B_SHOW)
                    if (!THROW_ball)B_SHOWS(hdc, memdc, 0);
                if (!B_SHOW) {
                    if (G_SHOW)
                        if (!THROW_ball)G_SHOWS(hdc, memdc, 0);
                    if (!G_SHOW)
                        if (!THROW_ball)R_SHOWS(hdc, memdc, 0);
                }
            }
            if (!disappear)W_SHOWS(hdc, memdc, 1);
        }
        if (scene == 5) {
            if (P_SHOW)
                if (!THROW_ball)P_SHOWS(hdc, memdc);
            if (!P_SHOW) {
                if (B_SHOW)
                    if (!THROW_ball)B_SHOWS(hdc, memdc, 0);
                if (!B_SHOW) {
                    if (G_SHOW)
                        if (!THROW_ball)G_SHOWS(hdc, memdc, 0);
                    if (!G_SHOW) {
                        if (R_SHOW)
                            if (!THROW_ball)R_SHOWS(hdc, memdc, 0);
                        if (!R_SHOW)
                            if (!THROW_ball)W_SHOWS(hdc, memdc, 0);
                    }
                }
            }
            if (!disappear)F_SHOWS(hdc, memdc, 1);
        }
        if (scene == 6) {
            if (P_SHOW)
                if (!THROW_ball)P_SHOWS(hdc, memdc);
            if (!P_SHOW) {
                if (B_SHOW)
                    if (!THROW_ball)B_SHOWS(hdc, memdc, 0);
                if (!B_SHOW) {
                    if (G_SHOW)
                        if (!THROW_ball)G_SHOWS(hdc, memdc, 0);
                    if (!G_SHOW) {
                        if (R_SHOW)
                            if (!THROW_ball)R_SHOWS(hdc, memdc, 0);
                        if (!R_SHOW) {
                            if (W_SHOW)
                                if (!THROW_ball)W_SHOWS(hdc, memdc, 0);
                            if (!W_SHOW)
                                if (!THROW_ball && F_SHOW)F_SHOWS(hdc, memdc, 0);
                        }
                    }
                }
            }
            if (M1_SHOW)
                if (!d_THROW_ball) M1_SHOWS(hdc, memdc);
            if (!M1_SHOW) {
                if (M2_SHOW)
                    if (!d_THROW_ball)M2_SHOWS(hdc, memdc);
                if (!M2_SHOW)
                    if (!d_THROW_ball&&M3_SHOW)M3_SHOWS(hdc, memdc);
            }
        }
        if (P_SHOW) {
            if (skill[0])
                P_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[11])
                P_SKILLS(hdc, ps, hwnd, memdc, 2);
        }
        if (F_SHOW) {
            if (skill[1])
                F_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[10])
                F_SKILLS(hdc,ps, hwnd, memdc, 2);
        }
        if (W_SHOW) {
            if (skill[2])
                W_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[6])
                W_SKILLS(hdc,ps, hwnd, memdc, 2);
        }
        if (R_SHOW) {
            if (skill[3])
                R_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[8])
                R_SKILLS(hdc,ps, hwnd, memdc, 2);
        }
        if (G_SHOW) {
            if (skill[4])
                G_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[7])
                G_SKILLS(hdc,ps, hwnd, memdc, 2);
        }
        if (B_SHOW) {
            if (skill[5] && s_cnt == 2)
                B_SKILLS(hdc,ps, hwnd, memdc, 1);
            if (skill[9])
                B_SKILLS(hdc,ps, hwnd, memdc, 2);
        }
        if (M1_SHOW) {
            if (skill[2])
                M1_SKILLS(hdc,ps, hwnd, memdc, 0);
        }
        if (M2_SHOW) {
            if (skill[5])
                M2_SKILLS(hdc,ps, hwnd, memdc, 0);
            if (skill[8])
                M2_SKILLS(hdc,ps, hwnd, memdc, 1);
        }
        if (M3_SHOW) {
            if (skill[1])
                M3_SKILLS(hdc,ps, hwnd, memdc, 0);
            if (skill[12])
                M3_SKILLS(hdc,ps, hwnd, memdc, 1);
        }
        if (THROW_ball)
            APPEAR_POKEMON(hdc, memdc);
        if (d_THROW_ball)
            D_APPEAR_POKEMON(hdc, memdc);
        if (GET_poke)
            GET_POKEMON(hdc, memdc);
        DeleteDC(memdc);
        EndPaint(hwnd, &ps);
        break;
    case WM_KEYDOWN:

        switch (wParam) {
        case '1':
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 1;
            P_SHOW = true;
            break;
        case '2':
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 2;
            P_SHOW = true;
            break;
        case '3':
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 3;
            P_SHOW = true;
            break;
        case '4':
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 4;
            P_SHOW = true;
            break;
        case '5':
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 5;
            P_SHOW = true;
            break;
        case '6':
            THROW_ball = true;
            d_THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 6;
            P_SHOW = true;
            M1_SHOW = true;
            break;
        case 'p': case 'P':
            P_SHOW = false;
            B_SHOW = true;
            THROW_ball = true;
            break;
        case 'b': case 'B':
            B_SHOW = false;
            G_SHOW = true;
            THROW_ball = true;
            break;
        case 'g': case 'G':
            G_SHOW = false;
            R_SHOW = true;
            THROW_ball = true;
            break;
        case 'r': case 'R':
            R_SHOW = false;
            W_SHOW = true;
            THROW_ball = true;
            break;
        case 'w': case 'W':
            W_SHOW = false;
            F_SHOW = true;
            THROW_ball = true;
            break;
        case 'f': case 'F':
            F_SHOW = false;
            break;
        case 'q': case 'Q':
            M1_SHOW = false; M2_SHOW = true;
            d_THROW_ball = true;
            break;
        case 't': case 'T':
            M2_SHOW = false; M3_SHOW = true;
            d_THROW_ball = true;
            break;
        case 'o': case 'O':
            M3_SHOW = false;
            break;
        case '7':
            skill[2] = true;
            w1_cnt = 1;
            break;
        case '8':
            skill[5] = true;
            b1_cnt = 1;
            break;
        case '9':
            skill[8] = true;
            r2_cnt = 1;
            break;
        case '0':
            skill[1] = true;
            f1_cnt = 1;
            break;
        case 'l': case 'L':
            skill[12] = true;
            break;
        case 'a': case'A':
            skill[9] = true;
            b2_cnt = 1;
            break;
        case 'i': case'I':
            THROW_ball = true;
            break;
        case 'k': case 'K':
            KillTimer(hwnd, 1);
            break;
        case 'c': case 'C':
            GET_poke = true;
            break;
        }

        if (wParam == VK_RIGHT) {
            LA=0,DA=0,UA=0,RA = 1;
            HeroX += 3;
                BackX += 3;
                if (HeroX > 600) {
                    BackX -= 3;
                    HeroX -= 3;
                }
            if (BackX < -200) {
                HeroX += 3;
                if (HeroX > 800) {
                    map1 = 1;
                    map2 = 1;
                    HeroX = 0;
                    HeroY = 150;
                    BackX = 0;
                    BackY = 0;
                }
            }
            else {
                BackX -= 3;
            }
            if (map2 != 1 &&HeroX > 270 && HeroX <600 && HeroY >210) {
                HeroX -= 3;
            }
        if (s1 ==0 &&map2 != 1 && HeroX > 380 && HeroX < 440 && HeroY > 180 && HeroY < 220) { // 첫 번째 npc 좌표
                    map1 = 3;
                    THROW_ball = true;

                    disappear = false; GET_poke = false;
                    g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화
                    s1 = 1;
                    scene = 1;
                    P_SHOW = true;
                    static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4, Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
                    static int M1hp = 8, M2hp = 8, M3hp = 16;//갸라도스,코뿌리,망나뇽 hp
                }

        if (s2 == 0 && map2 != 1 && HeroX > 600 && HeroX < 650 && HeroY < 120 && HeroY >30) {
            map1 = 3;
            THROW_ball = true;

            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화
            s2 = 1;
            scene = 2;
            P_SHOW = true;
            static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4, Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
            static int M1hp = 8, M2hp = 8, M3hp = 16;//갸라도스,코뿌리,망나뇽 hp
        }
        if (s3==0 && map2 == 1 && HeroX >120 && HeroX< 180 && HeroY >200 && HeroY <220) {
            map2 = 3;
            THROW_ball = true;
            s3 = 1;
            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 3;
            P_SHOW = true;
        }           
        if (s4==0 && map2 == 1 && HeroX > 300 && HeroX < 330 && HeroY>140 && HeroY < 150) {
            map2 = 3;
            THROW_ball = true;
            s4 = 1;
            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 4;
            P_SHOW = true;
            static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4, Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
            static int M1hp = 8, M2hp = 8, M3hp = 16;//갸라도스,코뿌리,망나뇽 hp
        }
        if(s5==0 && map2 ==1 && HeroX>420 && HeroX <450 && HeroY>120 && HeroY <140 ){
            map2 = 3;
            THROW_ball = true;
            s5 == 1;
            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 5;
            P_SHOW = true;
            static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4, Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
            static int M1hp = 8, M2hp = 8, M3hp = 16;//갸라도스,코뿌리,망나뇽 hp
        }
        if (s6==0 && map2 == 1 && BackX<-150 && HeroX>=600 && HeroY > 90 && HeroY < 110) {
            map2 = 3;
            THROW_ball = true;
            d_THROW_ball = true;
            s6 = 1;
            disappear = false; GET_poke = false;
            g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

            scene = 6;
            P_SHOW = true;
            M1_SHOW = true;
            static int Php = 4, Fhp = 4, Whp = 4, Ghp = 4, Bhp = 4, Rhp = 4;//피카츄,파이리,꼬부기,이상해씨,잠만보,롱스톤 hp
            static int M1hp = 8, M2hp = 8, M3hp = 16;//갸라도스,코뿌리,망나뇽 hp
        }
        }
        if (wParam == VK_LEFT) {
            if (BackX != 0) {
                  BackX += 3;
            }
            LA = 1, DA = 0, UA = 0, RA = 0;
            if (BackX == 0) {
                HeroX -= 3;
                if (HeroX < 0)
                    HeroX += 3;
            }
            if (map2 != 1 && HeroX < 215&& HeroY>210)
                HeroX += 3;
            if (map2 == 1 && HeroX > 0 && HeroX < 110 && HeroY > 180) {
                HeroX += 3;
            }
            if (s1==0 && map2 != 1 && HeroX > 380 && HeroX < 440 && HeroY > 180 && HeroY < 220) { // 첫 번째 npc 좌표
                map1 = 3;
                map1 = 3;
                THROW_ball = true;
                s1 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 1;
                P_SHOW = true;
            }
            if (s2==0&&map2 != 1 && HeroX > 600 && HeroX < 650 && HeroY < 120 && HeroY >30) {
                map1 = 3;
                THROW_ball = true;
                s2 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 2;
                P_SHOW = true;
            }
            if (s3==0&&map2 == 1 && HeroX > 120 && HeroX < 180 && HeroY >200 && HeroY < 220) {
                map2 = 3;
                THROW_ball = true;
                s3 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 3;
                P_SHOW = true;
            }
            if (s4==0&&map2 == 1 && HeroX > 300 && HeroX < 330 && HeroY>140 && HeroY < 150) {
                map2 = 3;
                THROW_ball = true;
                s4 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 4;
                P_SHOW = true;
            }
            if (s5==0&&map2 == 1 && HeroX > 420 && HeroX < 450 && HeroY>120 && HeroY < 140) {
                map2 = 3;
                THROW_ball = true;
                s5 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 5;
                P_SHOW = true;
            }
            if (s6==0&&map2 == 1 && BackX < -150 && HeroX >= 600 && HeroY > 90 && HeroY < 110) {
                map2 = 3;
                THROW_ball = true;
                d_THROW_ball = true;
                s6 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 6;
                P_SHOW = true;
                M1_SHOW = true;
            }
        }
        if (wParam == VK_UP) {
            LA = 0, DA = 0, UA = 1, RA = 0;
            HeroY -= 3;
            if (map2 != 1 &&HeroX > 0 && HeroX < 600 && HeroY < 100) {
                HeroY += 3;
            }
            if (map2 == 1 && HeroX > 0 && HeroX < 250 && HeroY < 120) {
                HeroY += 3;
            }
            if (map2 == 1 && HeroX > 250 && HeroX < 800 && HeroY < 80) {
                HeroY += 3;
            }
            if (s1==0 && map2 != 1 && HeroX > 380 && HeroX < 440 && HeroY > 180 && HeroY < 220) { // 첫 번째 npc 좌표
                map1 = 3;
                THROW_ball = true;
                s1 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 1;
                P_SHOW = true;
            }
            if (s2 == 0&& map2 != 1 && HeroX > 600 && HeroX < 650 && HeroY < 120 && HeroY >30) {
                map1 = 3;
                THROW_ball = true;
                s2 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 2;
                P_SHOW = true;

            }
            if (s3==0 && map2 == 1 && HeroX > 120 && HeroX < 180 && HeroY >200 && HeroY < 220) {
                map2 = 3;
                THROW_ball = true;
                s3=1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 3;
                P_SHOW = true;
            }
            if (s4==0 && map2 == 1 && HeroX > 300 && HeroX < 330 && HeroY>140 && HeroY < 150) {
                map2 = 3;
                THROW_ball = true;
                s4 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 4;
                P_SHOW = true;
            }
            if (s5==0 && map2 == 1 && HeroX > 420 && HeroX < 450 && HeroY>120 && HeroY < 140) {
                map2 = 3;
                THROW_ball = true;
                s5 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 5;
                P_SHOW = true;
            }
            if (s6==0 && map2 == 1 && BackX < -150 && HeroX >= 600 && HeroY > 90 && HeroY < 110) {
                map2 = 3;
                THROW_ball = true;
                d_THROW_ball = true;
                s6 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 6;
                P_SHOW = true;
                M1_SHOW = true;
            }
        }
        if (wParam == VK_DOWN) {
            LA = 0, RA = 0, UA = 0, DA = 1;
            HeroY += 3;
            if (map2 != 1 && HeroX > 270 && HeroX < 600 && HeroY >210) {
                HeroY -= 3;
            }
            if (map2 != 1 && HeroX < 215 && HeroY>210)
                HeroY -= 3;
            if (map2 == 1 && HeroX > 0 && HeroX < 110 && HeroY > 180) {
                HeroY -= 3;
            }
            if (map2 == 1 && HeroX > 110 && HeroX < 200 && HeroY >250) {
                HeroY -= 3;
            }
            if (map2 == 1 && HeroX > 200 && HeroY > 200) {
                HeroY -= 3;
            }
            if (s1==0 && map2 != 1 && HeroX > 380 && HeroX < 440 && HeroY > 180 && HeroY < 220) { // 첫 번째 npc 좌표
                map1 = 3;
                THROW_ball = true;
                s1 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 1;
                P_SHOW = true;
            }
            if (s2==0 && map2 != 1 && HeroX > 600 && HeroX < 650 && HeroY < 120 && HeroY >30) {
                map1 = 3;
                map1 = 3;
                THROW_ball = true;
                s2 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 2;
                P_SHOW = true;
            }
            if (s3==0&&map2 == 1 && HeroX > 120 && HeroX < 180 && HeroY >200 && HeroY < 220) {
                map2 = 3;
                THROW_ball = true;
                s3 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 3;
                P_SHOW = true;
            }
            if (s4==0 && map2 == 1 && HeroX > 300 && HeroX < 330 && HeroY>140 && HeroY < 150) {
                map2 = 3;
                THROW_ball = true;
                s4 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 4;
                P_SHOW = true;
            }
            if (s5==0 && map2 == 1 && HeroX > 420 && HeroX < 450 && HeroY>120 && HeroY < 140) {
                map2 = 3;
                THROW_ball = true;
                s5 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 5;
                P_SHOW = true;
            }
            if (s6==0 && map2 == 1 && BackX < -150 && HeroX >= 600 && HeroY > 90 && HeroY < 110) {
                map2 = 3;
                THROW_ball = true;
                d_THROW_ball = true;
                s6 = 1;
                disappear = false; GET_poke = false;
                g_ball_xpos = -30, g_ball_ypos = 280; // 잡기 초기화

                scene = 6;
                P_SHOW = true;
                M1_SHOW = true;
            }
        }

        if (wParam == VK_ESCAPE) {
            InvalidateRect(hwnd, NULL, TRUE);
            scene = 0;
            if (map2 != 1) 
                map1 = 0;
            if (map2 == 3) {
                map1 = 1;
                map2 = 1;
            }
        }
        if (wParam == VK_RETURN) {
            InvalidateRect(hwnd, NULL, TRUE);
            enter = 1;
            UA = 1;
        }
        InvalidateRect(hwnd, NULL,FALSE );
        break;
        case WM_LBUTTONDOWN:
                mx = LOWORD(lParam);
                my = HIWORD(lParam);
       
                if (P_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        skill[0] = true;
                        a_cnt = 1;
                        if (scene == 1)
                            b1_cnt = 1;
                        else if (scene == 2)
                            g1_cnt = 1;
                        else if (scene == 3)
                            r1_cnt = 1;
                        else if (scene == 4)
                            w2_cnt = 1;
                        else if (scene == 5)
                            f1_cnt = 1;
                        else if (scene == 6 && M1_SHOW)
                            w1_cnt = 1;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        skill[11] = true;
                        a_cnt = 1;
                        if (scene == 1)
                            b1_cnt = 1;
                        else if (scene == 2)
                            g1_cnt = 1;
                        else if (scene == 3)
                            r1_cnt = 1;
                        else if (scene == 4)
                            w2_cnt = 1;
                        else if (scene == 5)
                            f1_cnt = 1;
                        else if (scene == 6 && M1_SHOW)
                            w1_cnt = 1;
                        else if (scene == 6 && M2_SHOW) {
                            r2_cnt = 1;
                            b2_cnt = 0;
                        }
                    }
                }
                else if (B_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        b1_cnt = 0;
                        skill[5] = true;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        skill[9] = true;
                    }
                }
                else if (G_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        g1_cnt = 0;
                        skill[4] = true;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        g2_cnt = 0;
                        skill[7] = true;
                        if (scene == 6 && M3_SHOW) {
                            f1_cnt = 1;

                        }
                    }
                }
                else if (R_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        r1_cnt = 0;
                        skill[3] = true;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        r2_cnt = 0;
                        skill[8] = true;
                    }
                }
                else if (W_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        w1_cnt = 1;
                        skill[2] = true;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        w2_cnt = 0;
                        skill[6] = true;
                    }
                }
                else if (F_SHOW) {
                    if ((mx >= 102 && mx <= 352) && (my >= 479 && 629)) {
                        f1_cnt = 0;
                        skill[1] = true;
                    }
                    if ((mx >= 452 && mx <= 702) && (my >= 479 && 629)) {
                        f2_cnt = 0;
                        skill[10] = true;
                    }
                }
            
            InvalidateRect(hwnd, NULL, true);
            break;
    case WM_TIMER: 
        if (RETURNMAP) {
            InvalidateRect(hwnd, NULL, TRUE);
            scene = 0;
            if (map2 != 1)
                map1 = 0;
            if (map2 == 3) {
                map1 = 1;
                map2 = 1;
            }
            RETURNMAP = false;
        }
        if (hit) {
            cnt++;
            if (xpos == 110)
                xpos -= 30;
            if (xpos == 50)
                xpos += 60;
            if (xpos == 80)
                xpos -= 30;
            if (cnt == 3) {
                cnt = 0;
                hit = false;
            }
        }
        if (d_hit) {
            cnt++;
            if (d_xpos == 520) {
                d_xpos += 30;
            }
            if (d_xpos == 580)
                d_xpos -= 60;
            if (d_xpos == 550)
                d_xpos += 30;
            if (cnt == 2) {
                cnt = 0;
                d_hit = false;
            }
        }

        if (skill[0]) {
            //P1 10만볼트 
            d_hit = true;
            s_cnt++;
            if (s_cnt == 5) {
                skill[0] = false;
                s_cnt = 0;
                if (scene==1 && P_SHOW == true && B_SHOW==true) {               //피카츄 vs 잠만보 10만볼트 공격
                    if (skill[0] == false) {
                        Bhp -= Patt1; 
                        if (a_cnt == 1 && Bhp != 0 ) {
                            skill[5] = true;
                            
                        }
                    }
                }
                if (scene==2 && P_SHOW == true && G_SHOW == true) {             //피카츄 vs 이상해씨 10만 볼트 공격
                    if (skill[0] == false) {
                        Ghp -= Patt1;
                        if (a_cnt == 1 && Ghp != 0) {
                            skill[4] = true;
                            if (skill[4] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene==3 && P_SHOW == true && R_SHOW == true) {             //피카츄 vs 롱스톤 10만볼트 공격
                    if (skill[0] == false) {                        //효과가 약했다.
                        Rhp -= (Patt1 / 2);
                        if (a_cnt == 1 && Rhp != 0) {
                            skill[3] = true;
                            if (skill[3] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene==4 && P_SHOW == true && W_SHOW == true) {             //피카츄 vs 꼬부기 10만볼트 공격
                    if (skill[0] == false) {                        //효과가 굉장했다.
                        Whp -= (Patt1 * 2);
                    }
                }
                if (scene==5 && P_SHOW == true && F_SHOW == true) {             //피카츄 vs 파이리 10만볼트 공격
                    if (skill[0] == false) {                        
                        Fhp -= (Patt1);
                        if (a_cnt == 1 && Fhp != 0) {
                            skill[1] = true;
                            if (skill[1] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene == 6 && P_SHOW == true && M1_SHOW == true) {          //피카츄 vs 갸라도스 
                    if (skill[0] == false)
                        M1hp -= (Patt1 * 2);
                    if (a_cnt == 1 && M1hp != 0) {
                        skill[2] = true;
                        if (skill[2] == false)
                            a_cnt = 0;
                    }
                }
            }
           
        }
        if (skill[1]) {
            //F1 화염방사
            if (f1_cnt == 0) {
                s_cnt++;
                
                if (s_cnt == 10) {
                    d_hit = true;
                    skill[1] = false;
                    s_cnt = 0;
                    if (scene == 6 && F_SHOW == true && M3_SHOW == true) {
                        if (skill[1] == false) {
                            M3hp -= Fatt1;
                        }
                    }
                }
            }
            if (f1_cnt == 1) {
                s_cnt++;
                if (s_cnt == 10) {
                    hit = true;
                    skill[1] = false;
                    Ghp -= (M3att1 * 2);
                    Php -= Fatt1;
                    s_cnt = 0;
                }
            }
        }
        if (skill[2]) {
            //W1 파도타기
            if (w1_cnt == 0) {
                w_xpos[0] += 80;
                w_ypos[0] -= 32;

                if (w_xpos[0] > 400 && w_ypos[0] < 100)
                    d_hit = true;
                if (w_xpos[0] > 570 && w_ypos[0] < 10) {
                    skill[2] = false;
                    w_xpos[0] = 20;
                    w_ypos[0] = 170;
                }
                if (scene == 6 && P_SHOW == true && M1_SHOW) {
                    if (skill[2] == false) {
                        M1hp -= Patt1;
                    }
                }
            }
            if (w1_cnt == 1) {
                w_xpos[1] -= 80;
                w_ypos[1] += 32;

                if (w_xpos[1] < 200 && w_ypos[1] > 100)
                    hit = true;
                if (w_xpos[1] < 40 && w_ypos[1] > 170) {
                    skill[2] = false;
                    Php -= M1att;
                    w_xpos[1] = 500;
                    w_ypos[1] = -50;
                }
            }
        }
        if (skill[3]) {
            // R1 돌떨구기
            if (r1_cnt == 0) {
                r_ypos[0] += 15;

                if (r_ypos[0] == 10) {
                    d_ypos = 130;
                    d_ysize = 100;
                }
                if (r_ypos[0] == 40) {
                    d_ysize = 200;
                    d_ypos = 30;
                    r_ypos[0] = -50;
                    r_xpos[0] = 550;
                    skill[3] = false;
                    if (scene == 6 && R_SHOW == true && M3_SHOW) {
                        if (skill[3] == false) {
                            M3hp -= (Ratt1 * 2);
                            if (a_cnt == 1 && M3hp != 0) {
                                f2_cnt = 1;
                                skill[10] = true;
                                if (skill[10] == false)
                                    a_cnt = 0;
                            }
                        }
                    }
                }
            }
            if (r1_cnt == 1) {
                r_ypos[1] += 15;

                if (r_ypos[1] == 200) {
                    ysize = 100;
                    ypos = 320;
                }
                if (r_ypos[1] == 230) {
                    ysize = 200;
                    ypos = 220;
                    r_ypos[1] = 140;
                    r_xpos[1] = 80;
                    skill[3] = false;
                    Php -= Ratt1;
                    a_cnt = 0;
                }
            }
        }
        if (skill[4]) {
            //G1 꽃잎댄스
            static int m_count = 20;
            if (g1_cnt == 0) {
                s_cnt++;
                if (s_cnt % 2 == 0) {
                    g_ypos[1] += m_count;
                    d_ypos += m_count;
                }
                else {
                    g_ypos[1] -= m_count;
                    d_ypos -= m_count;
                }
                if (s_cnt == 3) {
                    skill[4] = false;
                    s_cnt = 0;
                    if (scene == 6 && G_SHOW == true && M2_SHOW == true) {
                        if (skill[4] == false) {
                            M2hp -= (Gatt1 * 2);

                        }
                    }
                    if (scene == 6 && G_SHOW == true && M3_SHOW == true) {
                        if (skill[4] == false) {
                            M3hp -= (Gatt1);
                        }
                    }
                }
            }
            if (g1_cnt == 1) {
                s_cnt++;
                if (s_cnt % 2 == 0) {
                    g_ypos[0] += m_count;
                    ypos += m_count;
                }
                else {
                    g_ypos[0] -= m_count;
                    ypos -= m_count;
                }
                if (s_cnt == 3) {
                    skill[4] = false;
                    Php -= Gatt1;
                    s_cnt = 0;
                    a_cnt = 0;
                }
            }
        }
        if (skill[5]) {
            // B1 기가임팩트
            static int m_count = 30;
            if (b1_cnt == 0) {
                xpos += m_count;
                ypos -= m_count;
                if (s_cnt == 2) {
                    s_cnt = 0;
                    skill[5] = false;
                    xpos = 80;
                    ypos = 220;

                    if (scene == 6 && B_SHOW == true && M2_SHOW) {
                        if (skill[5] == false) {
                            M2hp -= (Batt1/2);
                        }
                        if (a_cnt == 1 && M2hp != 0) {
                            skill[8] = true;
                            if (skill[8] == false)
                                a_cnt = 0;
                        }
                    }
                  
                }
                s_cnt++;
            }
            if (b1_cnt == 1) {
                d_xpos -= m_count;
                d_ypos += m_count; 

                if (s_cnt == 2) {
                    s_cnt = 0;
                    skill[5] = false;
                    Php -= Batt1;
                    d_xpos = 550;
                    d_ypos = 30; 
                    a_cnt = 0;
                }
                s_cnt++;
            }
        }
        if (skill[6]) {
            // W2 고속스핀
            static int m_count = 30;
            if (w2_cnt == 0) {
                xpos += m_count;
                ypos -= m_count;
                if (s_cnt == 2) {
                    s_cnt = 0;
                    xpos = 80;
                    ypos = 220;
                    skill[6] = false;
                    d_hit = true;
                    if (scene == 6 && W_SHOW == true && M3_SHOW) {
                        if (skill[6] == false) {
                            M3hp -= Watt2;

                            skill[10] = true;
                            if (skill[10] == false) {
                                a_cnt = 0;
                            }
                        }
                    }

                }
                s_cnt++;
            }
            if (w2_cnt == 1) {
                d_xpos -= m_count;
                d_ypos += m_count;
                if (s_cnt == 2) {
                    s_cnt = 0;
                    d_xpos = 550;
                    d_ypos = 30;
                    skill[6] = false;
                    hit = true;
                }
                s_cnt++;
            }
        }
        if (skill[7]) {
            // G2 오물폭탄
            if (g2_cnt == 0) {
                g2_xpos[0] += 80;
                g2_ypos[0] -= 32;

                if (g2_xpos[0] > 400 && g2_ypos[0] < 100)
                    d_hit = true;
                if (g2_xpos[0] > 570 && g2_ypos[0] < 10) {
                    skill[7] = false;
                    g2_xpos[0] = 80;
                    g2_ypos[0] = 220;
                    if (scene == 6 && G_SHOW == true && M3_SHOW == true) {
                        if (skill[7] == false) {
                            M3hp -= (Gatt1);
                            if (a_cnt == 1 && M3hp != 0) {
                                skill[1] = true;
                                if (skill[1] == false)
                                    a_cnt = 0;
                            }
                        }
                    }
                }
            }
            if (g2_cnt == 1) {
                g2_xpos[1] -= 80;
                g2_ypos[1] += 32;

                if (g2_xpos[1] < 200 && g2_ypos[1] > 100)
                    hit = true;
                if (g2_xpos[1] < 40 && g2_ypos[1] > 170) {
                    skill[7] = false;
                    g2_xpos[0] = 550;
                    g2_ypos[0] = 30;
                }
            }
        }
        if (skill[8]) {
            // R2 지진
            if (r2_xpos == -80) {
                r2_xpos += 80;
                s_cnt++;
            }
            if (s_cnt == 6) {
                if (r2_cnt == 0)
                    d_hit = true;
                if (r2_cnt == 1)
                    hit = true;
            }
            if (s_cnt == 7) {
                skill[8] = false;
                if (P_SHOW == true) {
                    Php -= (M2att * 2);
                }
                if (B_SHOW == true)
                    Bhp -= M2att;
                s_cnt = 0;
            }
            if (r2_xpos == 0)
                r2_xpos -= 80;
        }
        if (skill[9]) {
            // B2 파괴광선
            s_cnt++;
            if (b2_cnt == 0)
                d_hit = true;
            if (b2_cnt == 1)
                hit = true;
            if (s_cnt == 5) {
                skill[9] = false;
                s_cnt = 0;

                if (b2_cnt==0 && scene == 6 && B_SHOW == true && M2_SHOW) {
                    if (skill[9] == false) {
                        M2hp -= (Batt2 / 2);
                        if (a_cnt == 1 && M2hp != 0) {
                            skill[8] = true;
                            if (skill[8] == false)
                                a_cnt = 0;
                        }
                    }
                }
            }

            
        }
        if (skill[10]) {
            // F2 드래곤테일
            static int m_count = 30;
            if (f2_cnt == 0) {
                xpos += m_count;
                ypos -= m_count;
                if (s_cnt == 2) {
                    s_cnt = 0;
                    skill[10] = false;
                    xpos = 80;
                    ypos = 220;
                    if (scene == 6 && F_SHOW == true && M3_SHOW == true) {
                        if (skill[10] == false) {
                            M3hp -= Fatt2;
                        }
                    }
                }
                s_cnt++;
            }
            if (f2_cnt == 1) {
                d_xpos -= m_count;
                d_ypos += m_count;
                if (s_cnt == 2) {
                    s_cnt = 0;
                    skill[10] = false;
                    if(R_SHOW==true)
                    Rhp -= M3att2;
                    if (W_SHOW == true)
                        Whp -= M3att2;
                    d_xpos = 550;
                    d_ypos = 30;
                }
                s_cnt++;
            }
        }
        if (skill[11]) {
            // P2 아이언테일
            static int m_count = 30;
            xpos += m_count;
            ypos -= m_count;
            if (s_cnt == 2) {
                s_cnt = 0;
                skill[11] = false;
                xpos = 80;
                ypos = 220;
                if (scene==1 && P_SHOW == true && B_SHOW == true) {             //피카츄 vs 잠만보 아이언테일 공격
                    if (skill[11] == false) {
                        Bhp -= Patt2;
                        if (a_cnt == 1 && Bhp != 0) {
                            skill[5] = true;
                            if (skill[5] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene == 2 && P_SHOW == true && G_SHOW == true) {             //피카츄 vs 이상해씨 아이언테일 공격
                    if (skill[11] == false) {
                        Ghp -= Patt2;
                        if (a_cnt == 1 && Ghp != 0) {
                            skill[4] = true;
                            if (skill[4] == false)
                                a_cnt = 0;
                        }
                    }
                } 
                if (scene == 3 && P_SHOW == true && R_SHOW == true) {             //피카츄 vs 롱스톤 아이언테일 공격
                    if (skill[11] == false) {
                        Rhp -= (Patt2*2);
                    }
                }
                if (scene == 4 && P_SHOW == true && W_SHOW == true) {             //피카츄 vs 꼬부기 아이언태일 공격
                    if (skill[11] == false) {
                        Whp -= Patt2;
                        if (a_cnt == 1 && Whp != 0) {
                            skill[6] = true;
                            if (skill[6] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene == 5 && P_SHOW == true && F_SHOW == true) {             //피카츄 vs 파이리 아이언태일 공격
                    if (skill[11] == false) {                       //효과가 약했다.
                        Fhp -= (Patt2/2);              
                        if (a_cnt == 1 && Fhp != 0) {
                            skill[1] = true;
                            if (skill[1] == false)
                                a_cnt = 0;
                        }
                    }
                }
                if (scene == 6 && P_SHOW == true && M2_SHOW == true) {              //피카츄 vs 코뿌리 아이언      
                    if (skill[11] == false)
                        M2hp -= (Patt2 * 2);
                    if (a_cnt == 1 && M2hp != 0) {
                        skill[8] = true;
                        if (skill[8] == false)
                            a_cnt = 0;
                    }

                }
            }
            s_cnt++;
        }
        if (skill[12]) {
            // M3_2 드래곤다이브
            if (d_xpos == 550)
                d_ypos -= 10;
            if (d_ypos == 0)
                d_xpos = 80;
            if (d_xpos == 80) {
                d_ypos += 50;
                if (d_ypos == 150) {
                    hit = true;
                    skill[12] = false;
                    d_xpos = 550;
                    d_ypos = 30;
                }
            }
        }
        if (THROW_ball) {
            if (P_SHOW) {
                xscript = 0; yscript = 0;
            }
            else if (B_SHOW) {
                xscript = 161 * 4; yscript = 140;
            }
            else if (G_SHOW) {
                xscript = 161; yscript = 0;
            }
            else if (R_SHOW) {
                xscript = 161 * 4; yscript = 140 * 3;
            }
            else if (W_SHOW) {
                xscript = 0; yscript = 140 * 3;
            }
            else if (F_SHOW) {
                xscript = 161; yscript = 140 * 2;
            }

            ball_xpos += 30;
            ball_ypos += 30;
            if (ball_xpos >= 150 && ball_ypos >= 290) {
                THROW_ball = false;
                ball_xpos = -30;
                ball_ypos = 120;
            }
        }
        if (d_THROW_ball) {
            d_ball_xpos -= 30;
            d_ball_ypos += 30;
            if (d_ball_xpos >= 620 && d_ball_ypos >= 100) {
                d_THROW_ball = false;
                d_ball_xpos = 800;
                d_ball_ypos = -80;
            }
        }
        if (GET_poke) {
            if (scene == 1) {
                xscript = 161 * 4; yscript = 140;
            }
            else if (scene == 2) {
                xscript = 161; yscript = 0;
            }
            else if (scene == 3) {
                xscript = 161 * 4; yscript = 140 * 3;
            }
            else if (scene == 4) {
                xscript = 0; yscript = 140 * 3;
            }
            else if (scene == 5) {
                xscript = 161; yscript = 140 * 2;
            }

            if (g_ball_xpos >= 620 && g_ball_ypos <= 130) {
                g_ball_xpos = 620;
                g_ball_ypos = 130;
                disappear = true;
            }
            else {
                g_ball_xpos += 60;
                g_ball_ypos -= 15;
            }
            timecnt++;

            if (timecnt == 20) {
                GET_poke = false;
                RETURNMAP = true;  
                timecnt = 0;
                Php = 4;
            }
        }

        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case WM_DESTROY:
        DeleteObject(background);
        PlaySound(NULL, NULL, NULL);
        DeleteObject(P); DeleteObject(F);
        DeleteObject(B); DeleteObject(G);
        DeleteObject(R); DeleteObject(W);
        DeleteObject(M1);
        DeleteObject(M2);
        DeleteObject(M3);
        for (int i = 0; i < 2; i++)
            DeleteObject(P_SKILL[i]);
        for (int i = 0; i < 3; i++)
            DeleteObject(F_SKILL[i]);
        for (int i = 0; i < 3; i++)
            DeleteObject(W_SKILL[i]);
        for (int i = 0; i < 2; i++)
            DeleteObject(R_SKILL[i]);
        for (int i = 0; i < 2; i++)
            DeleteObject(G_SKILL[i]);
        for (int i = 0; i < 3; i++)
            DeleteObject(B_SKILL[i]);
        DeleteObject(M3_SKILL);
        KillTimer(hwnd, 1);
        KillTimer(hwnd, 11);
        KillTimer(hwnd, 22);
        KillTimer(hwnd, 33);
        KillTimer(hwnd, 44);
        DeleteObject(POKE_BALL);

        DeleteObject(ELECTRO_BUTTON); DeleteObject(STEAL_BUTTON);
        DeleteObject(NORMAL_BUTTON); DeleteObject(GRASS_BUTTON);
        DeleteObject(POISON_BUTTON); DeleteObject(ROCK_BUTTON);
        DeleteObject(GROUND_BUTTON); DeleteObject(WATER_BUTTON);
        DeleteObject(FIRE_BUTTON); DeleteObject(DRAGON_BUTTON);
        PostQuitMessage(0);
        break;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}

void P_SKILLS(HDC hdc,PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    P_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PSKILL1)); // 0
    P_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PSKILL2)); // 11
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, P_SKILL[0]);
        TransparentBlt(hdc, 430, 0, size * 2, size, memdc, 0, 0, 778, 1000, RGB(255, 0, 0));
    }
    if (a == 2) {
        (HBITMAP)SelectObject(memdc, P_SKILL[1]);
        TransparentBlt(hdc, d_xpos, d_ypos, size, size, memdc, 0, 0, 247, 192, RGB(255, 0, 0));
    }
}
void F_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    F_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_FSKILL1)); // 1
    F_SKILL[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_FSKILL12)); // 1-2
    F_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_FSKILL2)); // 10
    if (a == 1) {
        if (f1_cnt == 0) {
            (HBITMAP)SelectObject(memdc, F_SKILL[0]);
            TransparentBlt(hdc, 450, 0, size * 2, size, memdc, 0, 0, 1580, 654, RGB(0, 255, 0));
        }
        if (f1_cnt == 1) {
            (HBITMAP)SelectObject(memdc, F_SKILL[2]);
            TransparentBlt(hdc, 0, 270, size * 2, size, memdc, 0, 0, 1580, 654, RGB(0, 255, 0));
        }
    }
    if (a == 2) {
        (HBITMAP)SelectObject(memdc, F_SKILL[1]);
        if (f2_cnt == 0)
            TransparentBlt(hdc, d_xpos, d_ypos, size, size, memdc, 0, 0, 1912, 1044, RGB(255, 0, 0));
        if (f2_cnt == 1)
            TransparentBlt(hdc, xpos, ypos, size, size, memdc, 0, 0, 1912, 1044, RGB(255, 0, 0));
    }
}
void B_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    B_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BSKILL1)); // 5
    B_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BSKILL2)); // 9
    B_SKILL[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BSKILL22)); // 9-2
    if (a == 1) {
        if (b1_cnt == 0) {
            (HBITMAP)SelectObject(memdc, B_SKILL[0]);
            TransparentBlt(hdc, b_xpos[1], b_ypos[1], size, size, memdc, 0, 0, 2894, 4093, RGB(255, 255, 255));
        }
        if (b1_cnt == 1) {
            (HBITMAP)SelectObject(memdc, B_SKILL[0]);
            TransparentBlt(hdc, b_xpos[0], b_ypos[0], size, size, memdc, 0, 0, 2894, 4093, RGB(255, 255, 255));
        }
    }
    if (a == 2) {
        if (b2_cnt == 0) {
            (HBITMAP)SelectObject(memdc, B_SKILL[1]);
            TransparentBlt(hdc, 170, 40, size * 2, size * 2, memdc, 0, 0, 729, 635, RGB(255, 0, 255));
        }
        if (b2_cnt == 1) {
            (HBITMAP)SelectObject(memdc, B_SKILL[2]);
            TransparentBlt(hdc, 170, 40, size * 2, size * 2, memdc, 0, 0, 729, 635, RGB(255, 0, 255));
        }
    }
}
void G_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    G_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_GSKILL1)); // 4
    G_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_GSKILL2)); // 7
    if (a == 1) {
        if (g1_cnt == 0) {
            (HBITMAP)SelectObject(memdc, G_SKILL[0]);
            TransparentBlt(hdc, g_xpos[1], g_ypos[1], size, size, memdc, 0, 0, 800, 800, RGB(255, 255, 255));
        }
        if (g1_cnt == 1) {
            (HBITMAP)SelectObject(memdc, G_SKILL[0]);
            TransparentBlt(hdc, g_xpos[0], g_ypos[0], size, size, memdc, 0, 0, 800, 800, RGB(255, 255, 255));
        }
    }
    if (a == 2) {
        if (g2_cnt == 0) {
            (HBITMAP)SelectObject(memdc, G_SKILL[1]);
            TransparentBlt(hdc, g2_xpos[0], g2_ypos[0], size, size, memdc, 0, 0, 630, 516, RGB(255, 255, 255));
        }
        if (g2_cnt == 1) {
            (HBITMAP)SelectObject(memdc, G_SKILL[1]);
            TransparentBlt(hdc, g2_xpos[1], g2_ypos[1], size, size, memdc, 0, 0, 630, 516, RGB(255, 255, 255));
        }
    }
}
void R_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    R_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_RSKILL1)); // 3
    R_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_RSKILL2)); // 8
    if (a == 1) {
        if (r1_cnt == 0) {
            (HBITMAP)SelectObject(memdc, R_SKILL[0]);
            TransparentBlt(hdc, r_xpos[0], r_ypos[0], size / 2, size / 2, memdc, 0, 0, 1213, 1022, RGB(255, 255, 255));
        }
        if (r1_cnt == 1) {
            (HBITMAP)SelectObject(memdc, R_SKILL[0]);
            TransparentBlt(hdc, r_xpos[1], r_ypos[1], size / 2, size / 2, memdc, 0, 0, 1213, 1022, RGB(255, 255, 255));
        }
    }
    if (a == 2) {
        (HBITMAP)SelectObject(memdc, R_SKILL[1]);
        TransparentBlt(hdc, r2_xpos, r2_ypos, 790, 650, memdc, 0, 0, 501, 397, RGB(255, 255, 255));
    }
}
void W_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    W_SKILL[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_WSKILL1)); // 2
    W_SKILL[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_WSKILL12)); // 2-2
    W_SKILL[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_WSKILL2)); // 6
    if (a == 1) {
        if (w1_cnt == 0) {
            (HBITMAP)SelectObject(memdc, W_SKILL[0]);
            TransparentBlt(hdc, w_xpos[0], w_ypos[0], size + 50, size + 50, memdc, 0, 0, 1024, 702, RGB(255, 255, 255));
        }
        if (w1_cnt == 1) {
            (HBITMAP)SelectObject(memdc, W_SKILL[1]);
            TransparentBlt(hdc, w_xpos[1], w_ypos[1], size + 50, size + 50, memdc, 0, 0, 1181, 1181, RGB(255, 255, 255));
        }
    }
    if (a == 2) {
        if (w2_cnt == 0) {
            (HBITMAP)SelectObject(memdc, W_SKILL[2]);
            TransparentBlt(hdc, xpos - 50, ypos, size + 75, size, memdc, 0, 0, 1100, 457, RGB(255, 255, 255));
        }
        if (w2_cnt == 1) {
            (HBITMAP)SelectObject(memdc, W_SKILL[2]);
            TransparentBlt(hdc, d_xpos - 50, d_ypos, size + 75, size, memdc, 0, 0, 1100, 457, RGB(255, 255, 255));
        }
    }
}

void M1_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    if (a == 0) {
        (HBITMAP)SelectObject(memdc, W_SKILL[1]);
        TransparentBlt(hdc, w_xpos[1], w_ypos[1], size + 50, size + 50, memdc, 0, 0, 1181, 1181, RGB(255, 255, 255));
    }
}
void M2_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    if (a == 0) {
        (HBITMAP)SelectObject(memdc, B_SKILL[0]);
        TransparentBlt(hdc, b_xpos[0], b_ypos[0], size, size, memdc, 0, 0, 2894, 4093, RGB(255, 255, 255));
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, R_SKILL[1]);
        TransparentBlt(hdc, r2_xpos, r2_ypos, 790, 650, memdc, 0, 0, 501, 397, RGB(255, 255, 255));
    }
}
void M3_SKILLS(HDC hdc, PAINTSTRUCT ps, HWND hwnd, HDC memdc, int a) {
    M3_SKILL = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_M3SKILL)); // 12
    if (a == 0) {
        (HBITMAP)SelectObject(memdc, F_SKILL[2]);
        TransparentBlt(hdc, 0, 270, size * 2, size, memdc, 0, 0, 1580, 654, RGB(0, 255, 0));
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, M3_SKILL);
        TransparentBlt(hdc, d_xpos, d_ypos, size, size, memdc, 0, 0, 4583, 4583, RGB(255, 255, 255));
    }
}

void M1_SHOWS(HDC hdc, HDC memdc) {
    M1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_M1)); // M1_1(W1) 파도타기
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar8= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP32));
    (HBITMAP)SelectObject(memdc, M1);
    TransparentBlt(hdc, d_xpos, d_ypos, xsize, ysize, memdc, 0, 0, 343, 289, RGB(248, 248, 248));
    if(M1hp==8)
    SelectObject(memdc, hpbar1);
    else if (M1hp == 4) {
        SelectObject(memdc, hpbar8);
    }
    else if (M1hp == 0) {
        M1_SHOW = false; M2_SHOW = true;
        d_THROW_ball = true;
        return;
    }
    BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
}
void M2_SHOWS(HDC hdc, HDC memdc) {
    M2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_M2)); // M2_1(R2) 지진 M2_2(B1) 기가임팩트
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar8 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP32));
    hpbar9 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP33));
    hpbar10= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP34));
    hpbar11= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP35));
    (HBITMAP)SelectObject(memdc, M2);
    TransparentBlt(hdc, d_xpos, d_ypos, xsize, ysize, memdc, 0, 0, 328, 274, RGB(248, 248, 248));
    if (M2hp == 8)
        SelectObject(memdc, hpbar1);
    if (M2hp == 4) {
        SelectObject(memdc, hpbar8);
    }
    if (M2hp == 3) {
        SelectObject(memdc, hpbar9);
    }
    if (M2hp == 2) {
        SelectObject(memdc, hpbar10);
    }
    if (M2hp == 1) {
        SelectObject(memdc, hpbar11);
    }
    if (M2hp == 0) {
        M2_SHOW = false; M3_SHOW = true;
        d_THROW_ball = true;
        M3hp = 8;
        return;
    }
    BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
}
void M3_SHOWS(HDC hdc, HDC memdc) {
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    M3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_M3)); // M3_1(F1) 화염방사 M3_2 드래곤다이브
    hpbar5= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP36));
    hpbar7 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP37));
    hpbar9 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP33));
    hpbar10 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP34));
    hpbar11 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP35));
    (HBITMAP)SelectObject(memdc, M3);
    TransparentBlt(hdc, d_xpos, d_ypos, xsize, ysize, memdc, 0, 0, 234, 182, RGB(0, 255, 0));

    if (M3hp == 8)
        SelectObject(memdc, hpbar1);
    if(M3hp==7)
        SelectObject(memdc, hpbar5);
    if(M3hp==5)
        SelectObject(memdc, hpbar7);
    if(M3hp==3)
        SelectObject(memdc, hpbar9);
    if(M3hp==2)
        SelectObject(memdc, hpbar10);
    if(M3hp==1)
        SelectObject(memdc, hpbar11);
    if (M3hp == 0) {
        M3_SHOW = false;
        enter = 2;
        return;
    }

    BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);

}

void P_SHOWS(HDC hdc, HDC memdc) {
    P_SKILL_BUTTON(hdc, memdc);
    P = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_P)); // P1 10만볼트 P2 아이언테일
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar2= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP30));
    hpbar3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
    (HBITMAP)SelectObject(memdc, P);
    TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 234, 163, RGB(247, 247, 247));

    if(Php==4)
    SelectObject(memdc, hpbar1);
    if(Php==3)
    SelectObject(memdc, hpbar2);
    if(Php==2)
    SelectObject(memdc, hpbar3);
    if (Php <= 0) {
        P_SHOW = false;
        B_SHOW = true;
        THROW_ball = true;
        Bhp = 4;
        return;
    }
    BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
}
void F_SHOWS(HDC hdc, HDC memdc, int a) {
    F = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_F)); // F1 화염방사 F2 드래곤테일
        hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
        hpbar3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
        hpbar2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP30));
        hpbar4= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP31));
    if (a == 0) {
        F_SKILL_BUTTON(hdc, memdc);
        (HBITMAP)SelectObject(memdc, F);
        TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 205, 169, RGB(248, 248, 248));
            if (Fhp == 4)
                SelectObject(memdc, hpbar1);
            BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, F);
        TransparentBlt(hdc, d_xpos, d_ypos, d_xsize, d_ysize, memdc, 0, 0, 205, 169, RGB(248, 248, 248));
        if (Fhp == 2) {
            SelectObject(memdc, hpbar3);
        }
        else if (Fhp == 3) {
            SelectObject(memdc, hpbar2);
        }
        else if (Fhp == 1) {
            SelectObject(memdc, hpbar4);
        }
        else if (Fhp == 0) {
            GET_poke = true;
            return;
        }
        else if (Fhp == 4)
            SelectObject(memdc, hpbar1);
        BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
    }
}
void B_SHOWS(HDC hdc, HDC memdc, int a) { 
    int cnt = 0;
    B = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_B)); // B1 기가임팩트 B2 파괴광선
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar3= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
    if (a == 0) {
        B_SKILL_BUTTON(hdc, memdc);
        (HBITMAP)SelectObject(memdc, B);
        TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 192, 166, RGB(248, 248, 248));
        if (Bhp == 4)
            SelectObject(memdc, hpbar1);
        else if(Bhp==2)
            SelectObject(memdc, hpbar3);
        else if (Bhp == 0) {
            B_SHOW = false;
            G_SHOW = true;
            THROW_ball = true;
            Ghp = 4;
            return;
        }

            BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, B);
        TransparentBlt(hdc, d_xpos, d_ypos, d_xsize, d_ysize, memdc, 0, 0, 192, 166, RGB(248, 248, 248));
        if (Bhp == 2) {
            SelectObject(memdc, hpbar3);
        }
        else if (Bhp == 0) {
            GET_poke = true;
            return;
        }
        else if(Bhp==4)
            SelectObject(memdc, hpbar1);
        BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
    }
}
void G_SHOWS(HDC hdc, HDC memdc, int a) {
    G = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_G)); // G1 꽃잎댄스 G2 오물폭탄
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
    if (a == 0) {
        G_SKILL_BUTTON(hdc, memdc);
        (HBITMAP)SelectObject(memdc, G);
        TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 181, 148, RGB(248, 248, 248));
        if (Ghp == 4)
            SelectObject(memdc, hpbar1);
        if (Ghp == 0) {
            G_SHOW = false;
            R_SHOW = true;
            THROW_ball = true;
            Rhp = 4;
            return;
        }

        BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, G);
         TransparentBlt(hdc, d_xpos, d_ypos, d_xsize, d_ysize, memdc, 0, 0, 181, 148, RGB(248, 248, 248));
        if (Ghp == 2) {
            SelectObject(memdc, hpbar3);
        }
        else if (Ghp == 0) {
            GET_poke = true;
            return;
        }
        else if (Ghp == 4)
            SelectObject(memdc, hpbar1);
        BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
    }
}
void R_SHOWS(HDC hdc, HDC memdc, int a) {
    R = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_R)); // R1 돌떨구기 R2 지진
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP30));
    hpbar3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
    hpbar4 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP31));
    if (a == 0) {
        R_SKILL_BUTTON(hdc, memdc);
        (HBITMAP)SelectObject(memdc, R);
        TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 589, 526, RGB(248, 248, 248));
        if (Rhp == 4)
            SelectObject(memdc, hpbar1);
        if (Rhp == 2)
            SelectObject(memdc, hpbar3);
        if (Rhp == 0) {
            R_SHOW = false;
            W_SHOW = true;
            THROW_ball = true;
            Whp = 4;
            return;
        }

        BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, R);
        TransparentBlt(hdc, d_xpos, d_ypos, d_xsize, d_ysize, memdc, 0, 0, 589, 526, RGB(248, 248, 248));
        if (Rhp == 2) {
            SelectObject(memdc, hpbar3);
        }
        else if (Rhp == 3) {
            SelectObject(memdc, hpbar2);
        }
        else if (Rhp == 1) {
            SelectObject(memdc, hpbar4);
        }
        else if (Rhp <= 0) {
            GET_poke = true;
            return;
        }
        else if (Rhp == 4)
            SelectObject(memdc, hpbar1);
        BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
    
    
    }
}
void W_SHOWS(HDC hdc, HDC memdc, int a) {
    W = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_W)); // W1 파도타기 W2 고속스핀
    hpbar1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
    hpbar3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
    if (a == 0) {
        W_SKILL_BUTTON(hdc, memdc);
        (HBITMAP)SelectObject(memdc, W);
        TransparentBlt(hdc, xpos, ypos, xsize, ysize, memdc, 0, 0, 205, 184, RGB(248, 248, 248));
        if (Whp == 4)
            SelectObject(memdc, hpbar1);
        if (Whp == 2)
            SelectObject(memdc, hpbar3);
        if (Whp == 0) {
            Fhp = 4;
            W_SHOW = false;
            F_SHOW = true;
            THROW_ball = true;
            return;
        }

        BitBlt(hdc, 480, 340, 250, 20, memdc, 0, 0, SRCCOPY);
    }
    if (a == 1) {
        (HBITMAP)SelectObject(memdc, W);
        TransparentBlt(hdc, d_xpos, d_ypos, d_xsize, d_ysize, memdc, 0, 0, 205, 184, RGB(248, 248, 248));
    
        if (Whp==0) {
            GET_poke = true;
            return;
        }
        else if (Whp == 2) {
            SelectObject(memdc, hpbar2);
        }
        else
            SelectObject(memdc, hpbar1);
            BitBlt(hdc, 155, 85, 250, 20, memdc, 0, 0, SRCCOPY);
        }
}

void P_SKILL_BUTTON(HDC hdc, HDC memdc) {
    ELECTRO_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ELECTRO_BUTTON));
    STEAL_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_STEAL_BUTTON));
    (HBITMAP)SelectObject(memdc, ELECTRO_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, STEAL_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}
void B_SKILL_BUTTON(HDC hdc, HDC memdc) {
    NORMAL_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NORMAL_BUTTON));
    (HBITMAP)SelectObject(memdc, NORMAL_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, NORMAL_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}
void G_SKILL_BUTTON(HDC hdc, HDC memdc) {
    GRASS_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_GRASS_BUTTON));
    POISON_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_POISON_BUTTON));
    (HBITMAP)SelectObject(memdc, GRASS_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, POISON_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}
void R_SKILL_BUTTON(HDC hdc, HDC memdc) {
    ROCK_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ROCK_BUTTON));
    GROUND_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_GROUND_BUTTON));
    (HBITMAP)SelectObject(memdc, ROCK_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, GROUND_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}
void W_SKILL_BUTTON(HDC hdc, HDC memdc) {
    WATER_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_WATER_BUTTON));
    NORMAL_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NORMAL_BUTTON));

    (HBITMAP)SelectObject(memdc, WATER_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, NORMAL_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}
void F_SKILL_BUTTON(HDC hdc, HDC memdc) { 
    FIRE_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_FIRE_BUTTON));
    DRAGON_BUTTON = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DRAGON_BUTTON));
    (HBITMAP)SelectObject(memdc, FIRE_BUTTON);
    StretchBlt(hdc, 102, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);

    (HBITMAP)SelectObject(memdc, DRAGON_BUTTON);
    StretchBlt(hdc, 452, 479, 250, 150, memdc, 0, 0, 968, 699, SRCCOPY);
}

void GET_POKEMON(HDC hdc, HDC memdc) {
     POKE_BALL = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BALL));
    (HBITMAP)SelectObject(memdc, POKE_BALL);
    TransparentBlt(hdc, g_ball_xpos, g_ball_ypos, 35, 30, memdc, xscript, yscript, 161, 140, RGB(0, 255, 0));
}
void APPEAR_POKEMON(HDC hdc, HDC memdc) {
    POKE_BALL = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BALL));
    (HBITMAP)SelectObject(memdc, POKE_BALL);
    TransparentBlt(hdc, ball_xpos, ball_ypos, 35, 30, memdc, xscript, yscript, 161, 140, RGB(0, 255, 0));
}
void D_APPEAR_POKEMON(HDC hdc, HDC memdc) {
    POKE_BALL = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BALL));
    (HBITMAP)SelectObject(memdc, POKE_BALL);
    TransparentBlt(hdc, d_ball_xpos, d_ball_ypos, 35, 30, memdc, d_xscript, d_yscript, 161, 140, RGB(0, 255, 0));
}