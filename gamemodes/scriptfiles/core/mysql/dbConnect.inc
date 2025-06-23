
new MySQL:dbHandle;

public: MySQL_Connecting() {
    dbHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_BASE);
    new m_error = mysql_errno(dbHandle);
    if(m_error != 0) {
        printf("Проблема подключения к базе данных: %d", m_error);
        SendRconCommand("exit");
    }
    mysql_set_charset("cp1251", dbHandle);

}
public: MySQL_Disconnect() {
    mysql_close(dbHandle);
    return 1;
}