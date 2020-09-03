//
// Created by ariel on 9/1/20.
//

#include "database.h"
#include <sqlite3.h>
#include <cstdio>
#include <iostream>

const char* getLibVersion()
{
    return sqlite3_libversion();
}

int database::openDB(){
    rc = sqlite3_open(dbName, &db);
    return rc;
}

int database::closeDB(){
    rc = sqlite3_close(db);
    return rc;
}

void database::generateQCreateTable(char qry [], char *tableName, char* columns){
    sprintf(qry, "CREATE TABLE %s (%s);", tableName, columns);
}

void database::generateQDropTable(char qry [],char *tableName){
    sprintf(qry, "DROP TABLE %s;", tableName);
}

void database::generateQShowInfo(char qry [],char *tableName){
    sprintf(qry, "SELECT * FROM %s;", tableName);
}

void database::generateQInsertData(char qry [], char *tableName, char* dateTime, float temperature, float humidity, float pressure){
    //sprintf(qry, "INSERT INTO %s (number) values (%d);", tableName, number);
    sprintf(qry,"INSERT INTO %s(dt, temperature, humidity, pressure) values ('%s', %.2f, %.2f, %.2f);", tableName,
            dateTime, temperature, humidity,  pressure);
}

void database::checkOK(){
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
}

int database::insertQ(char qry[]){
    rc =  sqlite3_exec(db, qry, 0, 0, &zErrMsg);
    return rc;
}

void database::create_table(char qry[], char *tableName, char* columns){
    generateQCreateTable(qry, tableName, columns);
    insertQ(qry);
    if (rc=SQLITE_OK){
        std::cout << "Table was successfully created" << std::endl;
    }else{
        //std::cout << "Table was NOT created because it already exists" << std::endl;
    }
}

void database::insertData(char qry[], char *tableName, char* dateTime, float temperature, float humidity, float pressure){
    generateQInsertData(qry, tableName, dateTime,  temperature,  humidity,  pressure);
    insertQ(qry);
    //checkOK();
}

void database::showData(char qry[], char *tableName){
    generateQShowInfo(qry, tableName);
    insertQ(qry);
    //checkOK();
}