//
// Created by ariel on 9/1/20.
//

#ifndef BME280_DATABASE_H
#define BME280_DATABASE_H
#include <string>
#include "sqlite3.h"

class database {
private:
    sqlite3* db;
    std::string dbName;
    int rc;
    char *zErrMsg;

public:
    database(sqlite3* db, std::string dbName){
        this->db=db;
        this->dbName=dbName;
        this->rc = 0;
        this->zErrMsg="null";
    }

    std::string getDBName(){
        return dbName;
    }

    int getRC(){
        return rc;
    }

    char* getzErrMsg(){
        return zErrMsg;
    }

    int openDB();
    int closeDB();

    //generating query
    void checkOK();

    std::string generateQCreateTable(std::string tableName, std::string columns);

    int insertQ(std::string qry);

    void create_table(std::string tableName, std::string columns);

    void showData(std::string tableName);

    std::string generateQShowInfo(std::string tableName);

    std::string generateQDropTable(std::string tableName);

    std::string
    generateQInsertData(std::string tableName, int64_t dateTime, float temperature, float humidity, float pressure);

    void insertData(std::string tableName, int64_t dateTime, float temperature, float humidity, float pressure);
};


#endif //BME280_DATABASE_H
