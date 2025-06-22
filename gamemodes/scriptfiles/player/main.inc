#include <YSI-Includes\YSI_Coding\y_hooks>
enum e_PlayerInfo {
    e_PlayerID,
    e_PlayerName[MAX_PLAYER_NAME], 
    e_PlayerPassword[MAX_PASS_LENGTH],
    e_PlayerRegDate, 
    e_PlayerRegIP[16],
    e_PlayerLastIP[16]
}
new PlayerInfo[MAX_PLAYERS][e_PlayerInfo];

enum {
    e_PlayerNone,
    e_PlayerSex,
    e_PlayerSkin,
    e_PlayerScore,
    e_PlayerWanted,
    e_PlayerCash,
    e_Player
}
new PlayerStats[MAX_PLAYERS][MAX_ITEMS_STATS];



hook OnPlayerConnect(playerid) {
    for(new e_PlayerInfo:e; e < e_PlayerInfo; ++e) {
        PlayerInfo[playerid][e] = 0;
    }
    for(new i = 0; i < MAX_ITEMS_STATS; ++i) {
        PlayerStats[playerid][i] = -1;
    }

    GetPlayerName(playerid, PlayerInfo[playerid][e_PlayerName], MAX_PLAYER_NAME);
    GetPlayerIp(playerid, PlayerInfo[playerid][e_PlayerLastIP], 16);
    TogglePlayerSpectating(playerid, true);


    static const fmt_query[] = "\
        SELECT users.userID, users.user_name, users.user_password, users.user_regdata, users.user_regip, users.user_lastip, user_stats.stats_key, user_stats.stats_value FROM users \
        JOIN user_stats ON users.userID = user_stats.userID \
        WHERE users.user_name = '%e' \
    ";
    new query[sizeof fmt_query + MAX_PLAYER_NAME];
    mysql_format(dbHandle, query, sizeof query, fmt_query, 
        PlayerInfo[playerid][e_PlayerName]
    );
    mysql_tquery(dbHandle, query, "OnPlayerConnectQuery", "i", playerid);

}


hook OnGameModeInit() {
    static const fmt_query[] = "\
        SELECT users.userID, users.user_name, users.user_password, users.user_regdata, users.user_regip, users.user_lastip, user_stats.stats_key, user_stats.stats_value FROM users \
        JOIN user_stats ON users.userID = user_stats.userID \
        WHERE users.user_name = '%e' \
    ";
    new query[sizeof fmt_query + MAX_PLAYER_NAME];
    mysql_format(dbHandle, query, sizeof query, fmt_query, 
       "Easy_Code" 
    );
    mysql_tquery(dbHandle, query, "OnPlayerConnectQuery", "i", 0);
}