CMD:savepos(playerid) { 
    new Float:x, Float:y, Float:z, Float:angle, vehID;
    vehID = GetPlayerVehicleID(playerid);
    if(vehID > 0) {
        GetVehiclePos(vehID, x, y, z);
        GetVehicleZAngle(vehID, angle);
    } else {
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);
    }
    printf("������� %s: %f,%f,%f", 
        (vehID > 0) ? ("������"):("������"),
        x, y, z
    );
    printf("���� ��������: %f", angle);
    SendClientMessage(playerid, COLOR_SERVER, "[SERVER] "T_WHITE"���������� ������� ���������� � �������");
    return 1;
}