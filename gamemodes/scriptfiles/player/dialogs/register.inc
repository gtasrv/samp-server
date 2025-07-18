DialogCreate:register_player(playerid) {
    static const fmt_str[] = "\
    "T_SERVER"����� %d:%d\n\
    ����: %d.%d.%04d\n\n\
    "T_WHITE"������� �������: "T_SERVER"%s\n\n\
    "T_WHITE"����� ����������� �� ������ "T_SERVER""SERVER_NAME"\n\
    "T_WHITE"����� ������ ���� ��� ���������� ������ �����������\n\
    ������� ������ ��� ������ ��������\n\n\
    \t"T_GRAY"����������:\n\
    \t"T_WHITE"- ������ ������ �������� �� ��������� ���� � ����\n\
    \t- ������ ������ �� 6-�� �� 30-�� ��������\n\
    \t- ��������, ��������� ���� � ���� �������";
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
        ""T_WHITE"����������� � "T_SERVER"���� ������",
        string,
        "�����", 
        "�����"
    );
}

DialogR:register_player() {
    new strsize = strlen(inputtext);
    if(strsize < 6 || strsize > 30) {
        SendClientMessage(playerid, COLOR_WHITE, "������ ������ �������� �� 6 �� 30 ��������");
        return Dialog_Show(playerid, Dialog:register_player);
    }
    new Regex:isPlayerPasswordRegex = Regex_New("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*\\W)(?!.* ).{6,30}$");
    if(!Regex_Check(inputtext, isPlayerPasswordRegex)) {
        Regex_Delete(isPlayerPasswordRegex);
        Dialog_Show(playerid, Dialog:register_player);
        return SendClientMessage(playerid, COLOR_WHITE, "����������� ��� ������, ��������� ������� � �����");
    } else {
        Regex_Delete(isPlayerPasswordRegex);
        return Player_MySQL_Registration(playerid, inputtext);
    }
}
