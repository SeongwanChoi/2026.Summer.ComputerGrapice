#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

//다형성: 다형성이란 상속받은 클래스의 기능과 자식의 기능은 다르지만, 인터페이스를 그대로 유지하며 재사용가능하도록 만드는것이 목적
//전략패턴: 아이템의 효과가 추가적인 enum을 정의하지않고, 추가된 자식클래스를 추가하므로해서, 기존에 코드를 수정하지않고 기능만 바꾸어 사용이 가능하다.
//v-ptr(가상함수테이블): 부모객체에 자식의 객체의 함수를 호출하는 것.
//함수포인터: 특정 함수의 메모리 주소를 가리키는 변수.

// 전방 선언 (CPlayer 헤더의 얽힘 방지)
class CPlayer;

// ==========================================
// [공통 인터페이스] 최상위 관리자 인터페이스
// ==========================================
class IEffectManager
{
public:
    virtual ~IEffectManager() = default;
    virtual bool LoadFromCSV(const std::string& filename) = 0;
    virtual void ApplyEffect(int effectId, CPlayer* pCaster, CPlayer* pTarget) = 0;
};

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
    //가상소멸자가 아닐시에 만약에 자식에서 동적할당된 객체를 할당한경우, 소멸자에서 삭제한 동적할당된 메모리가 지워지지않으며, 메모리 누수를 일으킬수있다.
    virtual ~CEffect() {
        std::cout << "[Base] ~CEffect 소멸자 호출 (" << m_strName << ") [주소: " << this << "]" << std::endl;
    }

    // 순수 가상 함수: 각 효과 클래스에서 알맞게 구현
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
// EffectManager (상속/전략패턴 기반 - CEffect 매핑 및 관리)
// ==========================================
class EffectManager : public IEffectManager
{
private:
    std::unordered_map<int, CEffect*> m_mapEffects;

public:
    ~EffectManager() override;

    bool LoadFromCSV(const std::string& filename) override;
    void ApplyEffect(int effectId, CPlayer* pCaster, CPlayer* pTarget) override;

    CEffect* GetEffect(int effectId);
    void AddEffect(CEffect* pEffect);
};

// ==========================================
// DelegateEffectManager (함수 포인터 기반 효과 관리자)
// ==========================================

// 💡 람다 대신 순수 C++ 함수 포인터 시그니처 정의
typedef void(*EffectFuncPtr)(CPlayer* pCaster, CPlayer* pTarget, int nValue);

struct EffectDelegateData
{
    int id;
    std::string name;
    int value;
    EffectFuncPtr pFunc; // 일반 함수 포인터
};

class DelegateEffectManager : public IEffectManager
{
private:
    std::unordered_map<int, EffectDelegateData> m_mapDelegates;

public:
    ~DelegateEffectManager() override = default;

    bool LoadFromCSV(const std::string& filename) override;
    void ApplyEffect(int effectId, CPlayer* pCaster, CPlayer* pTarget) override;

    void RegisterDelegate(int id, const std::string& name, int value, EffectFuncPtr pFunc);

    // 💡 람다 대신 가독성을 위해 개별 바인딩할 명확한 정적 처리 함수들
    static void ApplyHpRecover(CPlayer* pCaster, CPlayer* pTarget, int nValue);
    static void ApplyMpRecover(CPlayer* pCaster, CPlayer* pTarget, int nValue);
    static void ApplyDamagePhysical(CPlayer* pCaster, CPlayer* pTarget, int nValue);
};