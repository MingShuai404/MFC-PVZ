#include "Plant.h"

#include "PVZDoc.h"
#include "ProjectilePea.h"
#include "Yard.h"

IMPLEMENT_DYNCREATE(Plant, GameEntity)

Plant::Plant(CRuntimeClass* classMsg, int hp, int maxTime)
  : GameEntity(classMsg, hp), skillMaxWaitTime(maxTime) {
  // maxTime Ĭ��ֵ-1 �����ܲ���ʱ�����
}

void Plant::draw(HDC hDC, int xOffset, int yOffset) {
  // GameEntity::draw(hDC);

  Yard& yard = theDoc->getYard();
  // �������Ϣ
  std::string theClass = GetRuntimeClass()->m_lpszClassName;
  // �����������ض�Ӧ��
  auto& currMaps = rcManage.getResource(theClass, getMapState());
  currMaps.at(animateTick)
    ->AlphaBlend(hDC, CPoint((int)(leftX + xOffset), (int)(topY + yOffset)),
      isState(Plant::VIRTUAL) ? 130 : 255);
}

void Plant::setPosition() {
  collisioArea =
    CRect((int)(leftX + width * 0.3), (int)topY, (int)(leftX + width * 0.8), (int)(topY + height));
}

void Plant::update() {
  skillWaitTime++;  // ���Ӽ��ܵȴ�ʱ��

  setPosition();

  // �Ӵ�������ֲ��
  if (skillMaxWaitTime == -1 && skillCheck() && isOnlyState(0x0)) {
    addState(Plant::SKILL_REDAY);
    return;
  }
  // �ǽӴ�ʽ��ֲ��
  if (skillMaxWaitTime != -1 && skillWaitTime > skillMaxWaitTime) {
    skillWaitTime = 0;
    addState(Plant::SKILL_REDAY);
  }
}

void Plant::skill() {
  // �ÿռ����ۼ�ʱ��
  // skillWaitTime = 0;
}

// Ĭ�Ϸ���true  ��Ҫ������д�����
bool Plant::skillCheck() { return true; }

void Plant::stateSwitch(bool isHalf) {
  if (isState(Plant::SKILL_REDAY) && !isHalf) {
    // �������״̬�������л���ͼ
    setMapState(Plant::SkillDynamic);
    // ��һ�ֺ���뼼��
    addState(Plant::SKILL);
    // �������״̬
    cleanState(Plant::SKILL_REDAY);
    return;
  }

  if (isState(Plant::SKILL)) {
    if (isHalf) {
      skill();  // �ͷż���
      return;
    }
    setMapState(Plant::DefaultDynamic);
    cleanState(Plant::SKILL);
    return;
  }
}