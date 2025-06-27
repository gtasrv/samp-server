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
    printf("Позиция %s: %f,%f,%f", 
        (vehID > 0) ? ("машины"):("игрока"),
        x, y, z
    );
    printf("Угол поворота: %f", angle);
    SendClientMessage(playerid, COLOR_SERVER, "[SERVER] "T_WHITE"Координаты успешно отправлены в консоль");
    return 1;
}