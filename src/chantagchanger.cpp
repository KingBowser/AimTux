#include "chantagchanger.h"
#include "util.h"

std::wstring Settings::ClanTagChanger::value = L"";
bool Settings::ClanTagChanger::animation = false;
bool Settings::ClanTagChanger::enabled = false; // TODO find a way to go back to the "official" clan tag for the player?

std::vector<ClanTagChanger::Animation> ClanTagChanger::animations =
{
	Animation ("NOVAC",
		std::vector<ClanTagChanger::Frame>
		{
			Frame ("NO____", 700),
			Frame ("VAC___", 700),
			Frame ("ON_____", 850),
			Frame ("LINUX", 1700),
			Frame ("______", 600),
			Frame ("AimTux", 3000),
			Frame ("______", 700),
		}, ANIM_LOOP
	)
};
ClanTagChanger::Animation* ClanTagChanger::animation = &ClanTagChanger::animations[0];

void ClanTagChanger::CreateMove(CUserCmd* cmd)
{
	if (!Settings::ClanTagChanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (Settings::ClanTagChanger::value.size() == 0 && !Settings::ClanTagChanger::animation)
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp > ClanTagChanger::animation->GetCurrentFrame().time)
	{
		timeStamp = currentTime_ms;
		ClanTagChanger::animation->NextFrame();
	}

	if (Settings::ClanTagChanger::animation)
	{
		SendClanTag(ClanTagChanger::animation->GetCurrentFrame().text.c_str(), "");
	}
	else 
	{
		std::wstring ctWithEscapesProcessed = std::wstring(Settings::ClanTagChanger::value);
		Util::StdReplaceStr<std::wstring>(ctWithEscapesProcessed, L"\\n", L"\n"); // compute time impact? also, referential so i assume RAII builtin cleans it up...
		SendClanTag(std::string(ctWithEscapesProcessed.begin(), ctWithEscapesProcessed.end()).c_str() /* i feel dirty */, "");
	}
}
