#pragma once
// ��ѭ����ʱ��ID
#define MAIN_LOOP_TIMER WM_USER + 10001
#define ANIMATION_LOOP_TIMER WM_USER + 10002
#define GAME_TICK_LOOP WM_USER + 10003
#define ATTACK_TICK_LOOP WM_USER + 10004
// ������Ϸ֡��
#define FLASH_TICK  1000 / 200
#define FPS         1000 / 30
#define GAME_TICK   1000 / 100//50
// ���ڴ�С px
#define WIDTH 900
#define HEIGHT 700

// ���ڻ�������
#define SLIDING_WINDOW 0
// ������ʾ���� 
#define ZOOM_FACTOR 0.5
