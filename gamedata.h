#ifndef GAMEDATA_H
#define GAMEDATA_H

const int GAME_MODE_ONE_PLAYER = 0;
const int GAME_MODE_TWO_PLAYER = 1;

class GameData
{
	protected:
		int m_turn;
		int m_gamemode;
		int m_score[2];
		std::string m_playername[2];
		int m_totalshots;
		std::vector<std::string> m_missiles[2];
		int m_curmissile[2];
	public:
		GameData(){}
		int getTurn(){return m_turn;}
		void setTurn(int turn) { m_turn = turn; }
		int getGameMode() { return m_gamemode; }
		void setGameMode(int gamemode) { m_gamemode = gamemode; }
		std::string getPlayerName(int which) { return m_playername[which]; }
		void setPlayerName(const std::string& name, int which) { m_playername[which] = name; }
		int getTotalShots() { return m_totalshots; }
		void setTotalShots(int totalshots) { m_totalshots = totalshots; }
		std::string getSelectedMissile(int whose) { return m_missiles[whose][m_curmissile[whose]]; }
		void setSelectedMissile(int which, int whose) { m_curmissile[whose] = which; }
		void addMissile(const std::string& missile, int whose) { m_missiles[whose].push_back(missile); }
		virtual ~GameData(){}
};

#endif
