new TimerPlayerSeccond[MAX_PLAYERS];


new TimerNoAuth[MAX_PLAYERS];

public: TimerPlayer_SeccondTimer(playerid) {
    if(PlayerInfo[playerid][e_PlayerLogin] == false) {
        TimerNoAuth[playerid]++;
        if(TimerNoAuth[playerid] == TIMER_NO_AUTH_PLAYER) {
            Kick(playerid);
        } 
    } 
}



stock Timer_PlayerSeccondTimer(playerid) {
    TimerPlayerSeccond[playerid] = SetTimerEx("TimerPlayer_SeccondTimer", 1000, true, "i", playerid);
}

stock Timer_DestroyPlayerSeccond(playerid) {
    return KillTimer(TimerPlayerSeccond[playerid]);
}