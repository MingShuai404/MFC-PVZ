#include "Sun.h"
#include "Visible.h"
#include "PVZDoc.h"

extern PVZDoc* theDoc;

IMPLEMENT_DYNCREATE(Sun, GameElement)

Sun::Sun() : GameElement(RUNTIME_CLASS(Sun), 100 /*������ʱ����hp��ʾ*/) { }

void Sun::draw(HDC hDC) {
    // ������⶯̬��Դ
    auto &pngs = rcManage.getResource("Sun", getMapState());

    // ���֡����
    if (animateTick >= pngs.size()) animateTick = 0;

    int width = pngs[animateTick]->GetWidth();
    int height = pngs[animateTick]->GetHeight();

    // Visible::draw(hDC);

    pngs[animateTick]->AlphaBlend(hDC, leftX, topY, width, height, 0, 0, width, height); 
    
}

void Sun::update() {
    // static POINT jumpArr[]{ {1, 1}, {} };
    /*--lifeTick;

    if (lifeTick < 200) setMapState(Sun::Flash);*/
    
    if (topY < finalPoint.y) topY += 1;
    // ��������
    if (isState(Sun::JUMP)) {
        int val = sin(jumpParam += 0.15) * 8;
        topY -= val;
        // ++leftX;
        if (jumpParam > 5/*val < - 6*/) {
            cleanState(Sun::JUMP);
            jumpParam = 1;
        }
    }

    

    // ���ⱻ�ռ�
    if (isState(Sun::COLLECTED)) {
        if (moveFlg) {
            // if (leftX)
            if (leftX > theDoc->getYard().getWidth() / 6) {
                leftX -= leftX * 0.05;
            }
            else {
                leftX += leftX * 0.05;
            }
            topY = slope * leftX + intercept;
        }
        else {
            topY -= topY * 0.05;
            leftX = (topY - intercept) / slope;
        }
        /*if (leftX < 150) {
            leftX -= leftX * 0.02;
        }
        else if (leftX < 120) {
            leftX -= leftX * 0.05;
        }
        else {
            leftX -= leftX * 0.01;
        }*/
        /*leftX -= leftX * 0.01;
        topY = slope * leftX + intercept;*/
        // y = kx + b; x = (y - b)/k
        if (topY <= 0 || leftX <= theDoc->getYard().getWidth() / 6) {
            setState(Sun::FLASH);
        }
    }

}

bool Sun::onClick(int cx, int cy) {
    // Sun��ͼ������� ������Ҫ���¼���
    if (cx >= leftX + width / 4 && cx <= leftX + width - width / 4
        && cy >= topY + height / 4 && cy <= topY + height - height / 4) {
        return true;
    }
    return false;
}

int Sun::getSunValue() {
    return sunValue;
}