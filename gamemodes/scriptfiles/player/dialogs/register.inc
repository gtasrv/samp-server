DialogCreate:register_player(playerid) {
    static const fmt_str[] = "\
    "T_SERVER"Время %d:%d\n\
    Дата: %d.%d.%04d\n\n\
    "T_WHITE"Игровой никнейм: "T_SERVER"%s\n\n\
    "T_WHITE"Добро пожаловтать на сервер "T_SERVER""SERVER_NAME"\n\
    "T_WHITE"Чтобы начать игру вам необходимо пройти регистрацию\n\
    Введите пароль для вашего аккаунта\n\n\
    \t"T_GRAY"Примечание:\n\
    \t"T_WHITE"- Пароль должен состоять из латинских букв и цифр\n\
    \t- Длинна пароля от 6-ти до 30-ти символов\n\
    \t- Строчной, заглавной букв и спец символа";
    new string[sizeof fmt_str + 4 + 8 + MAX_PLAYER_NAME + 20], y,m,d, hour, mins;
    getdate(y,m,d);
    gettime(hour, mins, _);
    format(string, sizeof string, fmt_str,
        hour, mins,
        d, m, y,
        PlayerInfo[playerid][e_PlayerName]
    );
    return Dialog_Open(
        playerid, 
        Dialog:register_player,
        DIALOG_STYLE_INPUT,
        ""T_WHITE"Регистрация » "T_SERVER"Ввод пароля",
        string,
        "Далее", 
        "Выход"
    );
}

DialogR:register_player() {
    new strsize = strlen(inputtext);
    if(strsize < 6 || strsize > 30) {
        SendClientMessage(playerid, COLOR_WHITE, "Пароль должен состоять из 6 до 30 символов");
        return Dialog_Show(playerid, Dialog:register_player);
    }
    new Regex:isPlayerPasswordRegex = Regex_New("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*\\W)(?!.* ).{6,30}$");
    if(!Regex_Check(inputtext, isPlayerPasswordRegex)) {
        Regex_Delete(isPlayerPasswordRegex);
        Dialog_Show(playerid, Dialog:register_player);
        return SendClientMessage(playerid, COLOR_WHITE, "Используйте для пароля, латинские символы и цифры");
    } else {
        Regex_Delete(isPlayerPasswordRegex);
        return Player_MySQL_Registration(playerid, inputtext);
    }
}
