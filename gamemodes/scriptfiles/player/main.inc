enum e_PlayerInfo {
    e_PlayerID,
    e_PlayerName[MAX_PLAYER_NAME], 
    e_PlayerPassword[MAX_PASS_LENGTH],
    e_PlayerRegDate, 
    e_PlayerRegIP[16],
    e_PlayerLastIP[16],
    bool:e_PlayerLogin,
}
new PlayerInfo[MAX_PLAYERS][e_PlayerInfo];

enum {
    e_PlayerNone, // 0
    e_PlayerSex, // 1
    e_PlayerSkin, // 2
    e_PlayerScore,
    e_PlayerWanted,
    e_PlayerCash
}
new PlayerStats[MAX_PLAYERS][MAX_ITEMS_STATS];



public: Player_OnPlayerConnect(playerid) {
    for(new e_PlayerInfo:e; e < e_PlayerInfo; ++e) {
        PlayerInfo[playerid][e] = 0;
    }
    for(new i = 0; i < MAX_ITEMS_STATS; ++i) {
        PlayerStats[playerid][i] = -1;
    }
    PlayerInfo[playerid][e_PlayerLogin] = false;



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

public: Player_OnPlayerDisconnect(playerid) {
    static const fmt_str[] = "\ 
        INSERT INTO user_stats (userID, stats_key, stats_value) VALUES %s\
         ON DUPLICATE KEY UPDATE \
        stats_key = VALUES(stats_key),\
        stats_value = VALUES(stats_value);";
    new substring[11+18+3+11], string[(11+18+3+11)*MAX_ITEMS_STATS];

	for(new i = 0; i < MAX_ITEMS_STATS; ++i) {
        if(PlayerStats[playerid][i] < 0) continue;
        format(substring, sizeof substring, "('%d', '%d', '%d'),", 
            PlayerInfo[playerid][e_PlayerID], 
            i,
            PlayerStats[playerid][i]
        );
        strcat(string, substring);
    }
	strdel(string,strlen(string)-1,strlen(string));
    new query[sizeof fmt_str + ((11+18+3+11)*MAX_ITEMS_STATS)];
    mysql_format(dbHandle, query, sizeof query, fmt_str, string);
    printf("%s", query);
    mysql_tquery(dbHandle, query);
}

stock PlayerSpawn(playerid) {
    SetSpawnInfo(
        playerid, 0, PlayerStats[playerid][e_PlayerSkin], 
        134.291519, -97.582336, 1.429687, 163.224807,
        0,0, 0,0, 0,0
    );
    TogglePlayerSpectating(playerid, false);
    PlayerInfo[playerid][e_PlayerLogin] = true;
    return SpawnPlayer(playerid);
}