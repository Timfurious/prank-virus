#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void stylish_glitch(HDC hdc, int width, int height) {
    int steps = 30;
    for (int i = 0; i < steps; i++) {
        int slice_height = rand() % (height / 10) + 5;
        int y = rand() % (height - slice_height);
        int offset = (rand() % 100) - 50;
        BitBlt(hdc, 0, y, width, slice_height, hdc, offset, y, SRCCOPY);
        Sleep(10);
    }
}

void wave_invert(HDC hdc, int width, int height) {
    int waves = 20;
    for (int i = 0; i < waves; i++) {
        RECT rect;
        rect.left = (width / waves) * i;
        rect.top = 0;
        rect.right = rect.left + (width / waves / 2);
        rect.bottom = height;
        InvertRect(hdc, &rect);
        Sleep(5);
    }
}

void screen_shrink_expand(HDC hdc, int width, int height) {
    int shrink_steps = 20;
    for (int i = 0; i < shrink_steps; i++) {
        int margin = i * (width / 100);
        StretchBlt(hdc, margin, margin, width - 2 * margin, height - 2 * margin, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(20);
    }
    for (int i = shrink_steps; i >= 0; i--) {
        int margin = i * (width / 100);
        StretchBlt(hdc, margin, margin, width - 2 * margin, height - 2 * margin, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(20);
    }
}

void color_flash(HDC hdc, int width, int height) {
    COLORREF colors[] = {
        RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
        RGB(255, 255, 0), RGB(0, 255, 255), RGB(255, 0, 255)
    };
    for (int i = 0; i < 10; i++) {
        HBRUSH brush = CreateSolidBrush(colors[rand() % 6]);
        RECT rect = {0, 0, width, height};
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        Sleep(50);
    }
}

void spiral_distortion(HDC hdc, int width, int height) {
    int cx = width / 2;
    int cy = height / 2;
    for (int i = 0; i < 50; i++) {
        int size = 100 + (i * 5);
        int angle = i * 10;
        int x = cx + (int)(cos(angle * 3.14 / 180) * 100);
        int y = cy + (int)(sin(angle * 3.14 / 180) * 100);
        StretchBlt(hdc, x, y, size, size, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(10);
    }
}

void scanlines(HDC hdc, int width, int height) {
    for (int y = 0; y < height; y += 4) {
        MoveToEx(hdc, 0, y, NULL);
        LineTo(hdc, width, y);
    }
    Sleep(100);
}

void noise(HDC hdc, int width, int height) {
    for (int i = 0; i < 30000; i++) {
        SetPixel(hdc, rand() % width, rand() % height, RGB(rand()%256, rand()%256, rand()%256));
    }
    Sleep(50);
}

void wave_distort(HDC hdc, int width, int height) {
    for (int y = 0; y < height; y += 10) {
        int offset = (int)(sin(y / 20.0) * 20);
        BitBlt(hdc, offset, y, width, 10, hdc, 0, y, SRCCOPY);
    }
    Sleep(50);
}

void rgb_shift(HDC hdc, int width, int height) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hbmMem);

    BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

    // Décaler RGB
    BitBlt(hdc, 5, 0, width, height, hdcMem, 0, 0, SRCCOPY | NOMIRRORBITMAP);
    BitBlt(hdc, -5, 0, width, height, hdcMem, 0, 0, SRCCOPY | NOMIRRORBITMAP);

    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

    Sleep(50);
}

void pulse_screen(HDC hdc, int width, int height) {
    HBRUSH blackBrush = CreateSolidBrush(RGB(0,0,0));
    RECT rect = {0, 0, width, height};
    for (int i = 0; i < 5; i++) {
        FillRect(hdc, &rect, blackBrush);
        Sleep(50);
        BitBlt(hdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        Sleep(50);
    }
    DeleteObject(blackBrush);
}

void random_effects(HDC hdc, int width, int height) {
    int effect = rand() % 12;
    switch (effect) {
        case 0: stylish_glitch(hdc, width, height); break;
        case 1: wave_invert(hdc, width, height); break;
        case 2: screen_shrink_expand(hdc, width, height); break;
        case 3: color_flash(hdc, width, height); break;
        case 4: spiral_distortion(hdc, width, height); break;
        case 5: scanlines(hdc, width, height); break;
        case 6: noise(hdc, width, height); break;
        case 7: wave_distort(hdc, width, height); break;
        case 8: rgb_shift(hdc, width, height); break;
        case 9: pulse_screen(hdc, width, height); break;
        case 10: color_flash(hdc, width, height); break;
        case 11: stylish_glitch(hdc, width, height); break;
    }
    Sleep(100);
}

int main() {
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    srand(time(NULL));

    while (1) {
        random_effects(hdc, screen_width, screen_height);
    }

    ReleaseDC(hwnd, hdc);
    return 0;
}
