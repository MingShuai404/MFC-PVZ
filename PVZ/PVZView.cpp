#include "PVZView.h"

#include "Config.h"
#include "PVZDoc.h"
#include "Plant.h"
#include "Sun.h"
#include "Yard.h"
#include "Zombie.h"
#include "resource.h"

#define ZOOM_FACTOR 1

extern PVZDoc* theDoc;

IMPLEMENT_DYNCREATE(PVZView, CView)

BEGIN_MESSAGE_MAP(PVZView, CView)
ON_WM_MOUSEMOVE()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void PVZView::OnDraw(CDC* cDC) {
  // ���Ժ�ӵ���Ϣ
  Yard& yard = theDoc->getYard();
  SeedBank& sbank = theDoc->getSeedBank();
  Player& player = theDoc->getPlayer();
  PVZDoc::SunlightList& sunList = theDoc->getSunList();

  // ׼��˫�������������
  CDC memDC;
  CBitmap buf;
  CFont font;
  memDC.CreateCompatibleDC(cDC);
  font.CreatePointFont(170, "΢���ź�");
  buf.CreateCompatibleBitmap(cDC, yard.getWidth(), yard.getHeight());
  memDC.SelectObject(buf);
  memDC.SelectObject(font);

  // ����Ժ���ϵ�Ԫ��
  yard.draw(memDC.m_hDC);
  // ����ֲ��ѡ�
  sbank.draw(memDC.m_hDC);
  // ����ֲ�ｩʬ
  yard.foreach (yard.getPlantMatrix(), [&](Yard::plant_iter& iter, int) {
    if (*iter) (*iter)->draw(memDC.m_hDC);
  });
  yard.foreach (yard.getZombieList(), [&](Yard::zombie_iter & iter, int row) {
    if (*iter) (*iter)->draw(memDC.m_hDC);
  });
  yard.foreach (yard.getEjectList(), [&](Yard::ejects_iter& iter, int) {
    if (*iter) (*iter)->draw(memDC.m_hDC);
  });

  
  // ����ѡ�е�ֲ��
  player.drawCurrentPlant(memDC.m_hDC, yard);
  // ����̫��
  for (auto& sun : sunList) {
    sun->draw(memDC.m_hDC);
  }
  // ����˫�������
  cDC->AlphaBlend(0, 0, yard.getWidth() * ZOOM_FACTOR,
                  yard.getHeight() * ZOOM_FACTOR, &memDC, 0, 0, yard.getWidth(),
                  yard.getHeight(), {AC_SRC_OVER, 0, 255, 0});
  buf.DeleteObject();
  memDC.DeleteDC();
}

void PVZView::OnMouseMove(UINT nFlags, CPoint point) {
  Player& player = ((PVZDoc*)m_pDocument)->getPlayer();
  // �������ָ��λ��
  player.setPos({int(point.x / ZOOM_FACTOR), int(point.y / ZOOM_FACTOR)});
  CView::OnMouseMove(nFlags, point);
}

void PVZView::OnLButtonDown(UINT nFlags, CPoint point) {
  auto doc = ((PVZDoc*)m_pDocument);
  SeedBank& sbank = doc->getSeedBank();
  Player& player = doc->getPlayer();
  Yard& yard = doc->getYard();
  auto& sunList = doc->getSunList();

  player.selectPlant(yard, sbank, point);

  player.collectSun(yard, sbank, sunList, point);
}

void PVZView::OnSelect(UINT nFlags, CPoint point) {}
void PVZView::OnPlace(UINT nFlags, CPoint point) {}
