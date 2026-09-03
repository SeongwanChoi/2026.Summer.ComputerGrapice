#include "Effect.h"
#include "Player.h"
#include <fstream>
#include <sstream>

using namespace std;

// ==========================================
// 구체적 효과 실행(Apply) 구현부 (상속 기반)
// ==========================================

// 1. HP 회복 적용
void CHpRecoveryEffect::Apply(CPlayer* pCaster, CPlayer* pTarget)
{
    if (pCaster != nullptr)
    {
        pCaster->RecoceryHP(m_nValue);
        cout << "[상속/HP] [" << m_strName << "] " << pCaster->GetName()
            << "의 HP가 " << m_nValue << " 회복되었습니다!" << endl;
    }
}

// 2. MP 회복 적용
void CMpRecoveryEffect::Apply(CPlayer* pCaster, CPlayer* pTarget)
{
    if (pCaster != nullptr)
    {
        pCaster->RecoceryMP(m_nValue);
        cout << "[상속/MP] [" << m_strName << "] " << pCaster->GetName()
            << "의 MP가 " << m_nValue << " 회복되었습니다!" << endl;
    }
}

// 3. 데미지 타격 적용
void CDamageEffect::Apply(CPlayer* pCaster, CPlayer* pTarget)
{
    if (pTarget != nullptr)
    {
        pTarget->TakeDemage(m_nDamage);
        cout << "[상속/DAMAGE] [" << m_strName << "] " << pTarget->GetName()
            << "에게 " << m_nDamage << "의 데미지를 입혔습니다!" << endl;
    }
    else
    {
        cout << "[" << m_strName << "] 대상이 존재하지 않습니다." << endl;
    }
}

// ==========================================
// EffectManager 구현부 (상속 기반)
// ==========================================

EffectManager::~EffectManager()
{
    for (auto& pair : m_mapEffects)
    {
        if (pair.second != nullptr)
        {
            delete pair.second;
        }
    }
    m_mapEffects.clear();
}

bool EffectManager::LoadFromCSV(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Effect CSV 파일을 열 수 없습니다: " << filename << endl;
        return false;
    }

    string line;
    // 헤더 스킵: Effect_ID, Name, Type, Value
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name, typeStr, valueStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, typeStr, ',');
        getline(ss, valueStr, ',');

        if (name.empty()) continue;

        int id = stoi(idStr);
        int value = valueStr.empty() ? 0 : stoi(valueStr);

        CEffect* pNewEffect = nullptr;

        // Type 문자열에 따라 알맞은 전략 객체 동적 생성
        if (name == "HP_RECOVER")
        {
            pNewEffect = new CHpRecoveryEffect(id, name, value);
        }
        else if (name == "MP_RECOVER")
        {
            pNewEffect = new CMpRecoveryEffect(id, name, value);
        }
        else if (name == "DAMAGE_PHYSICAL")
        {
            pNewEffect = new CDamageEffect(id, name, value);
        }
        else
        {
            cout << "else: Effect" << endl;
        }

        if (pNewEffect != nullptr)
        {
            AddEffect(pNewEffect);
        }
    }

    file.close();
    cout << "TextRPG_Effect 로드 완료 (" << m_mapEffects.size() << "개 등록)" << endl;
    return true;
}

void EffectManager::ApplyEffect(int effectId, CPlayer* pCaster, CPlayer* pTarget)
{
    CEffect* pEffect = GetEffect(effectId);
    if (pEffect != nullptr)
    {
        pEffect->Apply(pCaster, pTarget);
    }
}

CEffect* EffectManager::GetEffect(int effectId)
{
    auto iter = m_mapEffects.find(effectId);
    if (iter != m_mapEffects.end())
    {
        return iter->second;
    }
    return nullptr;
}

void EffectManager::AddEffect(CEffect* pEffect)
{
    if (pEffect != nullptr)
    {
        m_mapEffects[pEffect->GetID()] = pEffect;
    }
}

// ==========================================
// DelegateEffectManager 정적 효과 함수 구현부 (가독성 향상)
// ==========================================

void DelegateEffectManager::ApplyHpRecover(CPlayer* pCaster, CPlayer* pTarget, int nValue)
{
    if (pCaster != nullptr)
    {
        pCaster->RecoceryHP(nValue);
        cout << "[델리게이트/HP] " << pCaster->GetName()
            << "의 HP가 " << nValue << " 회복되었습니다!" << endl;
    }
}

void DelegateEffectManager::ApplyMpRecover(CPlayer* pCaster, CPlayer* pTarget, int nValue)
{
    if (pCaster != nullptr)
    {
        pCaster->RecoceryMP(nValue);
        cout << "[델리게이트/MP] " << pCaster->GetName()
            << "의 MP가 " << nValue << " 회복되었습니다!" << endl;
    }
}

void DelegateEffectManager::ApplyDamagePhysical(CPlayer* pCaster, CPlayer* pTarget, int nValue)
{
    if (pTarget != nullptr)
    {
        pTarget->TakeDemage(nValue);
        cout << "[델리게이트/DAMAGE] " << pTarget->GetName()
            << "에게 " << nValue << "의 데미지를 입혔습니다!" << endl;
    }
    else
    {
        cout << "[델리게이트/DAMAGE] 대상이 존재하지 않습니다." << endl;
    }
}

// ==========================================
// DelegateEffectManager 구현부 (함수포인터 바인딩)
// ==========================================

bool DelegateEffectManager::LoadFromCSV(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "DelegateEffect CSV 파일을 열 수 없습니다: " << filename << endl;
        return false;
    }

    string line;
    // 헤더 스킵: Effect_ID, Name, Type, Value
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name, typeStr, valueStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, typeStr, ',');
        getline(ss, valueStr, ',');

        if (name.empty()) continue;

        int id = stoi(idStr);
        int value = valueStr.empty() ? 0 : stoi(valueStr);

        // 💡 람다 대신 선언해 둔 정적 함수 포인터 주소를 명확하게 직접 연결
        if (name == "HP_RECOVER")
        {
            RegisterDelegate(id, name, value, &DelegateEffectManager::ApplyHpRecover);
        }
        else if (name == "MP_RECOVER")
        {
            RegisterDelegate(id, name, value, &DelegateEffectManager::ApplyMpRecover);
        }
        else if (name == "DAMAGE_PHYSICAL")
        {
            RegisterDelegate(id, name, value, &DelegateEffectManager::ApplyDamagePhysical);
        }
        else
        {
            cout << "else: Delegate Effect" << endl;
        }
    }

    file.close();
    cout << "Delegate Effect 로드 완료 (" << m_mapDelegates.size() << "개 등록)" << endl;
    return true;
}

void DelegateEffectManager::RegisterDelegate(int id, const string& name, int value, EffectFuncPtr pFunc)
{
    if (pFunc != nullptr)
    {
        m_mapDelegates[id] = { id, name, value, pFunc };
    }
}

void DelegateEffectManager::ApplyEffect(int effectId, CPlayer* pCaster, CPlayer* pTarget)
{
    auto iter = m_mapDelegates.find(effectId);
    if (iter != m_mapDelegates.end())
    {
        // 등록된 일반 함수 포인터 직접 호출
        iter->second.pFunc(pCaster, pTarget, iter->second.value);
    }
}