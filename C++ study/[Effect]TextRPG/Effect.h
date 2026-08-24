#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class CPlayer;

// 효과의 종류
enum class EEFFECT_TYPE {
    NONE,
    HP_RECOVER,      // HP 회복
    MP_RECOVER,      // MP 회복
    DAMAGE_PHYSICAL, // 물리 데미지
    DAMAGE_MAGIC,    // 마법 데미지
    BUFF_ATK         // 공격력 버프
};

// 효과의 적용 대상
enum class EEFFECT_TARGET {
    SELF,            // 시전자 자신
    TARGET           // 상대방(몬스터/플레이어)
};

class CEffect {
private:
    int m_nID;
    EEFFECT_TYPE m_eType;
    EEFFECT_TARGET m_eTarget;
    int m_nValue;
    std::string m_strDescription;

public:
    CEffect(int id = 0, EEFFECT_TYPE type = EEFFECT_TYPE::NONE,
        EEFFECT_TARGET target = EEFFECT_TARGET::SELF, int value = 0, std::string desc = "");
    ~CEffect();

    int GetID() const { return m_nID; }

    // 핵심 기능: 시전 자와 대상을 받아 효과를 실행
    void Apply(CPlayer* pCaster, CPlayer* pTarget);
};

class EffectManager {
private:
    std::unordered_map<int, CEffect*> m_mapEffects; // Key: Effect_ID

public:
    ~EffectManager();

    bool LoadFromCSV(const std::string& filename);
    CEffect* GetEffect(int nID);
    void Clear();
};