#pragma once

#include <string>
#include <iostream>

//다형성: 다형성이란 상속받은 클래스의 기능과 지식의 기능은 다르지만, 인터페이스를 그대로 유지하며 재사용가능하도록 만드는것이 목적
//전략자페턴: 아이템의 효과가 추가적인 enum을 정의하지않고, 추가된 자식클래스를 추가하므로해서, 기존에 코드를 수정하짆고 기능만 바꾸어 사용이 가능하다.
//v-ptr(가상함수테이블): 부모객체에 자식의 객체의 함수를 호출하는 것.
//함수포인터: 

// 전방 선언 (CPlayer 헤더의 얽힘 방지)
class CPlayer;

// ==========================================
// [전략 인터페이스] 최상위 효과 클래스 (추상 클래스)
// ==========================================
class CEffect

//추상클래스: 순수가상함수를 1개이상가진 함수. 추상클래스는 포인터나 참조자만 생성할수있다.
{
protected: // 자식객체에만 접근가능한 멤버
    int m_nEffectID;      // CSV 로드용 식별 ID
    std::string m_strName; // 효과 이름

public:
    CEffect(int id, const std::string& name)
        : m_nEffectID(id), m_strName(name) {
        std::cout << "[Base] CEffect 생성자 호출 (" << m_strName << ", ID: " << m_nEffectID << ") [주소: " << this << "]" << std::endl;
    }
    //가상소멸자가 아닐시에 만약에 자식에서 동작할당된 객체를 할당한경우, 소멸자에서 삭제한 동적할된 메모리가 지워지지않으며, 메모리 누수를 일으킬수있다.
    // 💡 테스트 포인트: 아래 virtual 키워드를 제거하거나 주석 처리하면
    // EffectManager 등에서 delete pEffect(부모 포인터)를 실행할 때
    // 자식 소멸자(~CHpRecoveryEffect 등)가 불리지 않아 메모리 누수가 발생하는 것을 로그로 확인할 수 있습니다.
    virtual ~CEffect() {
        std::cout << "[Base] ~CEffect 소멸자 호출 (" << m_strName << ") [주소: " << this << "]" << std::endl;
    }

    // 순수 가상 함수: 각 효과 클래스에서 알맞게 구현
    // 가상함수: virtual키워드를 붙인 멤버함수. 이함수는 자식에서 오버라이딩하여 정의하면 기능을 바꿔줄수있다.
    // 자식객체에서 반드시 정의하도록 강제하는 문법.
    virtual void Apply(CPlayer* pCaster, CPlayer* pTarget) = 0;

    int GetID() const { return m_nEffectID; }
    std::string GetName() const { return m_strName; }
};

// ==========================================
// [구체적 전략] 1. HP 회복 효과
// ==========================================
class CHpRecoveryEffect : public CEffect
{
private:
    int m_nValue;

public:
    CHpRecoveryEffect(int id, const std::string& name, int value)
        : CEffect(id, name), m_nValue(value) {
        std::cout << "[Derived] CHpRecoveryEffect 자식 생성자 호출 (Value: " << m_nValue << ")" << std::endl;
    }

    ~CHpRecoveryEffect() override {
        std::cout << "[Derived] ~CHpRecoveryEffect 자식 소멸자 호출! (메모리 정상 해제)" << std::endl;
    }

    void Apply(CPlayer* pCaster, CPlayer* pTarget) override;
};

// ==========================================
// [구체적 전략] 2. MP 회복 효과
// ==========================================
class CMpRecoveryEffect : public CEffect
{
private:
    int m_nValue;

public:
    CMpRecoveryEffect(int id, const std::string& name, int value)
        : CEffect(id, name), m_nValue(value) {
        std::cout << "[Derived] CMpRecoveryEffect 자식 생성자 호출 (Value: " << m_nValue << ")" << std::endl;
    }

    ~CMpRecoveryEffect() override {
        std::cout << "[Derived] ~CMpRecoveryEffect 자식 소멸자 호출! (메모리 정상 해제)" << std::endl;
    }

    void Apply(CPlayer* pCaster, CPlayer* pTarget) override;
};

// ==========================================
// [구체적 전략] 3. 데미지 부여 효과
// ==========================================
class CDamageEffect : public CEffect
{
private:
    int m_nDamage;

public:
    CDamageEffect(int id, const std::string& name, int damage)
        : CEffect(id, name), m_nDamage(damage) {
        std::cout << "[Derived] CDamageEffect 자식 생성자 호출 (Damage: " << m_nDamage << ")" << std::endl;
    }

    ~CDamageEffect() override {
        std::cout << "[Derived] ~CDamageEffect 자식 소멸자 호출! (메모리 정상 해제)" << std::endl;
    }

    void Apply(CPlayer* pCaster, CPlayer* pTarget) override;
};

// ==========================================
// EffectManager (기존 유지 - CEffect 매핑 및 관리)
// ==========================================
#include <unordered_map>

class EffectManager
{
private:
    std::unordered_map<int, CEffect*> m_mapEffects;

public:
    ~EffectManager();

    bool LoadFromCSV(const std::string& filename);
    CEffect* GetEffect(int effectId);
    void AddEffect(CEffect* pEffect);
};