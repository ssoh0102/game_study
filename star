#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846  // π 값을 직접 정의
#define WIDTH 40                    // 콘솔의 가로 크기
#define HEIGHT 20                   // 콘솔의 세로 크기

int main() {
    int radius = 7;                // 별 모양의 외접원 반지름
    int centerX = 20;              // 별 모양의 중심 X 좌표
    int centerY = 10;              // 별 모양의 중심 Y 좌표
    double angleStep = 2 * M_PI / 5;  // 각도를 나누는 간격 (별 모양이므로 5개의 꼭짓점)

    char canvas[HEIGHT][WIDTH];    // 화면을 나타내는 2차원 배열

    // 배열 초기화 (모두 공백으로)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }

    // 별 모양의 각 꼭짓점을 계산하여 배열에 '*' 설정
    int x_points[5];
    int y_points[5];
    for (int k = 0; k < 5; k++) {
        double angle = k * angleStep - M_PI / 2;  // 첫 번째 꼭짓점이 위쪽에 오도록 설정
        x_points[k] = (int)(radius * cos(angle)) + centerX;
        y_points[k] = (int)(radius * sin(angle)) + centerY;
    }

    // 별 모양의 변을 그리기 (5개의 직선을 그려 별 모양을 만듦)
    for (int k = 0; k < 5; k++) {
        int x1 = x_points[k];
        int y1 = y_points[k];
        int x2 = x_points[(k + 2) % 5];  // 두 칸 건너뛰어 꼭짓점 연결
        int y2 = y_points[(k + 2) % 5];

        // 두 점을 잇는 선분 그리기 (Bresenham's line algorithm 사용)
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (1) {
            if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH) {
                canvas[y1][x1] = '-';
            }
            if (x1 == x2 && y1 == y2) {
                break;
            }
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

    // 배열을 콘솔에 출력
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
