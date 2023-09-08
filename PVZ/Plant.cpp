#include "Plant.h"
#include "Yard.h"
#include "PVZDoc.h"
#include "ProjectilePea.h"

IMPLEMENT_DYNCREATE(Plant, GameElement)

Plant::Plant(CRuntimeClass* classMsg, int hp, int maxTime) : 
    GameElement(classMsg, hp), skillMaxWaitTime(maxTime) { 
    // maxTime Ĭ��ֵ-1 �����ܲ���ʱ�����
}

void Plant::draw(HDC hDC) {

    // GameElement::draw(hDC);

    Yard &yard = theDoc->getYard();
    // �������Ϣ
    std::string theClass = GetRuntimeClass()->m_lpszClassName;
    // �����������ض�Ӧ��
    auto& currMaps = rcManage.getResource(theClass, getMapState());
    // auto& shade = rcManage.getResource("Plant", 0).at(0);
    currMaps.at(animateTick)->AlphaBlend(hDC, CPoint(leftX, topY), isState(Plant::VIRTUAL) ? 130 : 255);
}

void Plant::update() {
    if (skillWaitTime != -1)
        ++skillWaitTime;

    collisioArea = CRect(leftX + width * 0.3, topY, leftX + width * 0.8, topY + height);
}

void Plant::skill() {
    // �ÿռ����ۼ�ʱ��
    // skillWaitTime = 0;
}

bool Plant::skillCheck() {
    return false;
}

bool Plant::collisio(GameElement& e) {
    return false;
}