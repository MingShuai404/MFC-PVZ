#include "Sun.h"

#include "PVZDoc.h"
#include "Visible.h"

extern PVZDoc* theDoc;

IMPLEMENT_DYNCREATE(Sun, GameElement)

Sun::Sun() : GameElement(RUNTIME_CLASS(Sun)), lifeTime(200) {}

void Sun::draw(HDC hDC, int xOffset, int yOffset) {
  // ������⶯̬��Դ
  auto& pngs = rcManage.getResource("Sun", getMapState());

  // ���֡����
  if (animateTick >= pngs.size()) animateTick = 0;

  int width = pngs[animateTick]->GetWidth();
  int height = pngs[animateTick]->GetHeight();

  // TODO
  // Visible::draw(hDC);

  pngs[animateTick]->AlphaBlend(hDC, (int)(leftX), (int)(topY), (int)(width), (int)(height), 0, 0, (int)(width),
    (int)(height));
}

void Sun::update() {
  if (isState(Sun::FLASH)) --lifeTime;

  if (topY >= finalPoint.y) {
    addState(Sun::FLASH);
    setMapState(Sun::Flash);
  }

  if (topY < finalPoint.y) topY += 1;
  // ��������
  if (isState(Sun::JUMP)) {
    int val = (int)(sin(jumpParam += 0.15) * 8);
    topY -= val;
    if (jumpParam > 5.5) {
      cleanState(Sun::JUMP);
      jumpParam = 1;
    }
  }
  // ���ⱻ�ռ�
  if (isState(Sun::COLLECTED)) {
    if (moveFlg) {
      leftX -= xStep;
      topY -= yStep;
    }
    if (topY <= 0 && leftX <= theDoc->getYard().getWidth() / 7) {
      lifeTime = 0;
    }
  }
}

bool Sun::onClick(int cx, int cy) {
  // Sun��ͼ������� ������Ҫ���¼���
  if (cx >= leftX + width / 4 && cx <= leftX + width - width / 4 &&
    cy >= topY + height / 4 && cy <= topY + height - height / 4) {
    return true;
  }
  return false;
}

int Sun::getSunValue() { return sunValue; }