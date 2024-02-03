#include "PeaShooterSingle.h"

#include "PVZDoc.h"
#include "ProjectilePea.h"

IMPLEMENT_DYNCREATE(PeaShooterSingle, Plant)

PeaShooterSingle::PeaShooterSingle(CRuntimeClass* theClass,
  CRuntimeClass* eject, int hp)
  : Plant(theClass, hp), ejectClass(eject) {}

void PeaShooterSingle::draw(HDC hDC, int xOffset, int yOffset) {
  Plant::draw(hDC);
}

bool PeaShooterSingle::skillCheck() {
  auto& rowZombie = theDoc->getYard().getZombieList()[plantPos.x];
  if (!rowZombie.empty()) return true;
  return false;
}

void PeaShooterSingle::skill() {
  // ����״̬
  // ���ü�����ͼ
  auto& yard = theDoc->getYard();
  // ��ȡֲ�����
  int row = plantPos.x;
  // ��Ӷ�Ӧ
  auto& ejects = yard.getEjectList();
  std::shared_ptr<Ejects> pea((Ejects*)ejectClass->CreateObject());
  pea->setState(Ejects::DEFAULT);
  pea->setLeftX(leftX + width * 0.9);
  pea->setTopY(topY + height * 0.2);
  ejects[row].push_front(pea);
}

void PeaShooterSingle::stateSwitch(bool isHalf) {
  if (isState(Plant::SKILL)) {
    if (isHalf) {
      skill();  // �ͷż���
      return;
    }
    setMapState(Plant::DefaultDynamic);
    addState(Plant::SKILL_SLEEP);  // ��������״̬
    cleanState(Plant::SKILL);
    setState(0x0);
    return;
  }

  if (isState(Plant::SKILL_REDAY) && !isHalf) {
    // �������״̬�������л���ͼ
    setMapState(Plant::SkillDynamic);
    // ��һ�ֺ���뼼��
    addState(Plant::SKILL);
    // �������״̬
    cleanState(Plant::SKILL_REDAY);
    return;
  }
}