﻿#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // rand() 함수 사용을 위해 필요
#include <conio.h>  // _kbhit()와 _getch() 함수를 사용하기 위해 필요 (Windows 전용)
#include <windows.h>  // Sleep() 함수를 사용하기 위해 필요 (Windows 전용)

#define M_PI 3.14159265358979323846  // π 값을 직접 정의
#define WIDTH 40                    // 콘솔의 가로 크기
#define HEIGHT 24                   // 콘솔의 세로 크기 (24로 변경)

int main() {
    int running = 1;  // 게임 루프 제어 변수
    clock_t lastTime = clock();  // 이전 프레임의 시간
    double fps = 60.0;  // 목표 FPS
    double frameDelay = 1.0 / fps;  // 각 프레임의 지연 시간

    // 장애물 위치 설정
    int obstacleX = rand() % WIDTH;
    int obstacleY = 0;  // 장애물은 위쪽에서 시작

    static int starX = WIDTH / 2;
    static int starY = HEIGHT - 2;

    while (running) {
        clock_t currentTime = clock();
        double deltaTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC;

        // 프레임 지연 시간에 도달하면 화면 업데이트
        if (deltaTime >= frameDelay) {
            lastTime = currentTime;

            // 화면 초기화
            char canvas[HEIGHT][WIDTH];
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    canvas[i][j] = ' ';
                }
            }

            // 장애물 이동
            obstacleY++;
            if (obstacleY >= HEIGHT) {
                obstacleY = 0;
                obstacleX = rand() % WIDTH;  // 장애물 위치를 다시 랜덤하게 설정
            }

            // 장애물 표시
            canvas[obstacleY][obstacleX] = 'X';

            // 별이 장애물에 부딪히면 게임 종료
            if (starX == obstacleX && starY == obstacleY) {
                running = 0;
                system("cls");
                printf("Game Over! You hit an obstacle!\n");
                Sleep(2000);
                break;
            }

            // 플레이어 표시
            canvas[starY][starX] = '*';

            // 스크린 버퍼 렌더링을 위한 문자열 생성
            char buffer[HEIGHT * (WIDTH + 1) + 1];
            int index = 0;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    buffer[index++] = canvas[i][j];
                }
                buffer[index++] = '\n';
            }
            buffer[index] = '\0';

            // 화면 출력
            system("cls");  // 화면 지우기 (Windows 콘솔 전용)
            printf("%s", buffer);

            // 사용자 입력 처리
            if (_kbhit()) {  // 키보드 입력이 있는지 확인
                char input = _getch();
                if (input == 'q') {  // 'q'를 누르면 게임 종료
                    running = 0;
                }
                else if (input == 'w' && starY > 0) {
                    starY--;
                }
                else if (input == 's' && starY < HEIGHT - 1) {
                    starY++;
                }
                else if (input == 'a' && starX > 0) {
                    starX--;
                }
                else if (input == 'd' && starX < WIDTH - 1) {
                    starX++;
                }
            }
        }
        else {
            // CPU 사용률을 낮추기 위해 Sleep 사용
            Sleep((DWORD)((frameDelay - deltaTime) * 1000));
        }
    }

    return 0;
}
