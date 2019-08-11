#pragma once

// extras
struct Player;

class CMainHack
{
public:
	CMainHack();
	~CMainHack();

	static CMainHack *GetInstance()
	{
		static CMainHack instance;
		return &instance;
	}

public:
	void ProcessPlayerHack(Player *pPlayer);

public:
	void ToggleUnlimitedHealth(BOOL bToggled);
	void ToggleUnlimitedMana(BOOL bToggled);
	void ToggleUnlimitedItem(BOOL bToggled);
	void ToggleNoCooldown(BOOL bToggled);
	void ToggleWalkingSpeedHack(BOOL bToggled);
	void ToggleJumpSpeedHack(BOOL bToggled);

	void SetWalkingSpeed(float fSpeed);
	void SetJumpSpeed(float fSpeed);
	
private:
	BOOL m_bUnlimitedHealth;
	BOOL m_bUnlimitedMana;
	BOOL m_bUnlimitedItem;
	BOOL m_bNoCooldown;
	BOOL m_bWalkingSpeed;
	float m_fWalkingSpeed;
	BOOL m_bJumpSpeed;
	float m_fJumpSpeed;

};