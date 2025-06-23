
DialogCreate:auth_login(playerid) {
    Dialog_Open (
        playerid, 
        Dialog:auth_login,
        DIALOG_STYLE_PASSWORD,
        ""T_WHITE"Авторизация » "T_SERVER"Вход в систему",
        ""T_SERVER"Здравствуйте, дорогой друг\n\n\
        "T_WHITE"Приветствую вас на нашем сервере!\n\
        Ваш аккаунт уже "T_GREEN"зарегистрирован.\n\n\
        "T_GRAY"Справка: "T_WHITE"Если вы введете ваш пароль не верно\n\
        Более "T_RED"3-х раз, "T_WHITE"то вы будете кикнуты сервером.\n\
        Для этого соблюдайте правильность\n\
        вводимых символов, во избжедения ошибок ввода.\n\n\
        "T_SERVER"Пожалуйста, введите ваш пароль:",
        "Далее",
        "Выход"
    );
}
DialogR:auth_login() {
    if(!response) return Kick(playerid);
    else {
        new strsize = strlen(inputtext);
        if(strsize < 6 || strsize > 20) {
            SendClientMessage(playerid, COLOR_RED, "Пароль должен быть от 6 до 20 символов.");
            return Dialog_Show(playerid, Dialog:auth_login);
        }
        if (strcmp(PlayerInfo[playerid][e_PlayerPassword], inputtext, true) != 0) {
            SendClientMessage(playerid, COLOR_RED, "Неверный пароль. Пожалуйста, попробуйте снова.");
            return Dialog_Show(playerid, Dialog:auth_login);
        }
        return PlayerSpawn(playerid);
    }
}