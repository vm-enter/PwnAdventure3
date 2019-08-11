#pragma once

class CAutoHackCtrl
{
public:
	CAutoHackCtrl();
	~CAutoHackCtrl();

public:
	void ToggleMobVac(BOOL bToggled);
	void ToggleItemVac(BOOL bToggled);
	void ToggleKamiVac(BOOL bToggled);

	void SetMobDistanceX(float fDistance);
	void SetMobDistanceY(float fDistance);
	void SetMobDistanceZ(float fDistance);

protected:
	BOOL m_bMobVac;
	BOOL m_bItemVac;
	BOOL m_bKamiVac;

	float m_fMobDistanceX;
	float m_fMobDistanceY;
	float m_fMobDistanceZ;
};