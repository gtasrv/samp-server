
DialogCreate:auth_login(playerid) {
    Dialog_Open (
        playerid, 
        Dialog:auth_login,
        DIALOG_STYLE_PASSWORD,
        ""T_WHITE"����������� � "T_SERVER"���� � �������",
        ""T_SERVER"������������, ������� ����\n\n\
        "T_WHITE"����������� ��� �� ����� �������!\n\
        ��� ������� ��� "T_GREEN"���������������.\n\n\
        "T_GRAY"�������: "T_WHITE"���� �� ������� ��� ������ �� �����\n\
        ����� "T_RED"3-� ���, "T_WHITE"�� �� ������ ������� ��������.\n\
        ��� ����� ���������� ������������\n\
        �������� ��������, �� ���������� ������ �����.\n\n\
        "T_SERVER"����������, ������� ��� ������:",
        "�����",
        "�����"
    );
}
DialogR:auth_login() {
    if(!response) return Kick(playerid);
    else {
        new strsize = strlen(inputtext);
        if(strsize < 6 || strsize > 20) {
            SendClientMessage(playerid, COLOR_RED, "������ ������ ���� �� 6 �� 20 ��������.");
            return Dialog_Show(playerid, Dialog:auth_login);
        }
        if (strcmp(PlayerInfo[playerid][e_PlayerPassword], inputtext, true) != 0) {
            SendClientMessage(playerid, COLOR_RED, "�������� ������. ����������, ���������� �����.");
            return Dialog_Show(playerid, Dialog:auth_login);
        }
        return PlayerSpawn(playerid);
    }
}