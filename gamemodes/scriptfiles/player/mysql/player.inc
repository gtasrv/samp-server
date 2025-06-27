public: OnPlayerConnectQuery(playerid) {
    new rows;
    cache_get_row_count(rows);
    if(!rows) {
       Dialog_Show(playerid, Dialog:register_player);
    } else {
        cache_get_value_name_int(0, "userID", PlayerInfo[playerid][e_PlayerID]);
        cache_get_value_name(0, "user_name", PlayerInfo[playerid][e_PlayerName], MAX_PLAYER_NAME);
        cache_get_value_name(0, "user_password", PlayerInfo[playerid][e_PlayerPassword], MAX_PASS_LENGTH);
        cache_get_value_name_int(0, "user_regdata", PlayerInfo[playerid][e_PlayerRegDate]);
        cache_get_value_name(0, "user_regip", PlayerInfo[playerid][e_PlayerRegIP], 16);
        cache_get_value_name(0, "user_lastip", PlayerInfo[playerid][e_PlayerLastIP], 16);
        // 
        for(new i = 1; i <= rows; i++ ) {
            cache_get_value_name_int(i-1, "stats_value", PlayerStats[playerid][i]);

        }
        Dialog_Show(playerid, Dialog:auth_login);

        // Update player last IP
        // static const fmt_query[] = "UPDATE users SET user_lastip = '%s' WHERE userID = %d LIMIT 1";
        // mysql_format(dbHandle, "UPDATE users SET user_lastip = '%s' WHERE userID = %d", 
            // PlayerInfo[playerid][e_PlayerLastIP], 
            // PlayerInfo[playerid][e_PlayerID]
        // );
    }
    return 1;
}

public: Player_MySQL_PlayerAdd_Base(playerid) {
    PlayerInfo[playerid][e_PlayerID] = cache_insert_id();

    printf("uSERID: %d", PlayerInfo[playerid][e_PlayerID]);
    
    PlayerStats[playerid][e_PlayerSkin] = 1;
    return PlayerSpawn(playerid);
}


stock Player_MySQL_Registration(playerid, const password[]) {
    static const fmt_str[] = "\
    INSERT INTO users (user_name, user_password, user_regdata, user_regip, user_lastip) VALUES \
    ('%e', '%e', '%d', '%e', '%e')";
    new query[sizeof fmt_str + MAX_PLAYER_NAME + 30 + 11 + 16 + 16];
    mysql_format(dbHandle, query, sizeof query, fmt_str, 
        PlayerInfo[playerid][e_PlayerName],
        password, 
        gettime(), 
        PlayerInfo[playerid][e_PlayerLastIP],
        PlayerInfo[playerid][e_PlayerLastIP]
    );
    return mysql_tquery(dbHandle, query, "Player_MySQL_PlayerAdd_Base", "i", playerid);


}