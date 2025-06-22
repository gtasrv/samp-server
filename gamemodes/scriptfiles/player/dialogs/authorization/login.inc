DialogCreate:auth_login(playerid) {
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
}
DialogResponse:auth_login(playerid, response, listitem, inputtext[]) {
    if(!response) return Kick(playerid);
    else {
        new strsize = strlen(inputtext);
        if(strsize < 6 || strsize > 20) {
            SendClientMessage(playerid, COLOR_RED, "Пароль должен быть от 6 до 20 символов.");
            return Dialog_Show(playerid, Dialog:auth_login)
        }
        if (strcmp(PlayerInfo[playerid][e_PlayerPassword], inputtext, true) != 0) {
            SendClientMessage(playerid, COLOR_RED, "Неверный пароль. Пожалуйста, попробуйте снова.");
            return Dialog_Show(playerid, Dialog:auth_login)
        }
        SetSpawnInfo (
            playerid, 
            0,
            PlayerStats[playerid][e_PlayerSkin],
            0.0, 0.0, 0.0, 0.0,
            0,0, 0,0,     
            0,0, 0,0,
            0,0, 0,0
        );
        TogglePlayerSpectating(playerid, false);
        return SpawnPlayer(playerid);
    }
    return 1;
}