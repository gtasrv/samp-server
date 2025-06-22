public: OnPlayerConnectQuery(playerid) {
    new rows;
    cache_get_row_count(rows);
    if(!rows) {
        // register player
    } else {
        cache_get_value_name_int(0, "userID", PlayerInfo[playerid][e_PlayerID]);
        cache_get_value_name(0, "user_name", PlayerInfo[playerid][e_PlayerName], MAX_PLAYER_NAME);
        cache_get_value_name(0, "user_password", PlayerInfo[playerid][e_PlayerPassword], MAX_PASS_LENGTH);
        cache_get_value_name_int(0, "user_regdata", PlayerInfo[playerid][e_PlayerRegDate]);
        cache_get_value_name(0, "user_regip", PlayerInfo[playerid][e_PlayerRegIP], 16);
        cache_get_value_name(0, "user_lastip", PlayerInfo[playerid][e_PlayerLastIP], 16);
        // 
        new row; 
        for(new i = 1; i <= rows; i++ ) {
            cache_get_value_name_int(i-1, "stats_value", PlayerStats[playerid][i]);
            row++;

        }
        Dialog_Open (
            playerid, 
            Dialog:auth_login,
            DIALOG_STYLE_PASSWORD,
            "Авторизация",
            "Здравствуйте, дорогой друг\n\n\
            Приветствую вас на нашем сервере!\n\
            Ваш аккаунт уже зарегистрирован.\n\n\
            Справка: Если вы введете ваш пароль не верно\n\
            Более 3-х раз, то вы будете кикнуты сервером.\n\
            Для этого соблюдайте правильность\n\
            вводимых символов, во избжедения ошибок ввода.\n\n\
            Пожалуйста, введите ваш пароль:",
            "Далее",
            "Выход"
        );

        // Update player last IP
        // static const fmt_query[] = "UPDATE users SET user_lastip = '%s' WHERE userID = %d LIMIT 1";
        // mysql_format(dbHandle, "UPDATE users SET user_lastip = '%s' WHERE userID = %d", 
            // PlayerInfo[playerid][e_PlayerLastIP], 
            // PlayerInfo[playerid][e_PlayerID]
        // );
    }
    return 1;
}