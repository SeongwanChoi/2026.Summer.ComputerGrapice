#include "Effect.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

CEffect::CEffect(int id, EEFFECT_TYPE type, EEFFECT_TARGET target, int value, std::string desc)
    : m_nID(id), m_eType(type), m_eTarget(target), m_nValue(value), m_strDescription(desc) {
}

CEffect::~CEffect() {}

void CEffect::Apply(CPlayer* pCaster, CPlayer* pTarget) {
    // 효과 대상 설정 (SELF면 Caster, TARGET이면 Target)
    CPlayer* pDestination = (m_eTarget == EEFFECT_TARGET::SELF) ? pCaster : pTarget;

    if (pDestination == nullptr) return;

    switch (m_eType) {
    case EEFFECT_TYPE::HP_RECOVER:
        pDestination->RecoceryHP(m_nValue);
        std::cout << pDestination->GetName() << "의 HP가 " << m_nValue << " 회복되었습니다." << std::endl;
        break;

    case EEFFECT_TYPE::MP_RECOVER:
        pDestination->RecoceryMP(m_nValue);
        std::cout << pDestination->GetName() << "의 MP가 " << m_nValue << " 회복되었습니다." << std::endl;
        break;

    case EEFFECT_TYPE::DAMAGE_PHYSICAL:
    case EEFFECT_TYPE::DAMAGE_MAGIC:
        pDestination->TakeDemage(m_nValue);
        std::cout << pDestination->GetName() << "에게 " << m_nValue << "의 피해를 입혔습니다." << std::endl;
        break;

    default:
        break;
    }
}

// ==========================================
// EffectManager 구현부
// ==========================================
EffectManager::~EffectManager() {
    Clear();
}

void EffectManager::Clear() {
    for (auto& pair : m_mapEffects) {
        delete pair.second;
    }
    m_mapEffects.clear();
}

bool EffectManager::LoadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Effect CSV 파일을 열 수 없습니다: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵 (Effect_ID, Type, Target, Value, Description)

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, typeStr, targetStr, valueStr, desc;

        std::getline(ss, idStr, ',');
        std::getline(ss, typeStr, ',');
        std::getline(ss, targetStr, ',');
        std::getline(ss, valueStr, ',');
        std::getline(ss, desc, ',');

        if (idStr.empty() || typeStr.empty()) continue;

        int id = std::stoi(idStr);
        int value = std::stoi(valueStr);

        // Type 문자열 매핑
        EEFFECT_TYPE eType = EEFFECT_TYPE::NONE;
        if (typeStr == "HP_RECOVER") eType = EEFFECT_TYPE::HP_RECOVER;
        else if (typeStr == "MP_RECOVER") eType = EEFFECT_TYPE::MP_RECOVER;
        else if (typeStr == "DAMAGE_PHYSICAL") eType = EEFFECT_TYPE::DAMAGE_PHYSICAL;

        // Target 문자열 매핑
        EEFFECT_TARGET eTarget = EEFFECT_TARGET::SELF;
        if (targetStr == "TARGET") eTarget = EEFFECT_TARGET::TARGET;

        CEffect* pNewEffect = new CEffect(id, eType, eTarget, value, desc);
        m_mapEffects[id] = pNewEffect;
    }

    file.close();
    std::cout << "Effect_Table 로드 완료 (" << m_mapEffects.size() << "개 등록)" << std::endl;
    return true;
}

CEffect* EffectManager::GetEffect(int nID) {
    auto iter = m_mapEffects.find(nID);
    if (iter != m_mapEffects.end()) {
        return iter->second;
    }
    return nullptr;
}