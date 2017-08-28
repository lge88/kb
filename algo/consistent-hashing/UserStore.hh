#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include <sqlite3.h>

using RowId = int64_t;
struct UserRecord {
  RowId id;
  std::string info;
  UserRecord(RowId aId, std::string aInfo): id(aId), info(std::move(aInfo)) {}
};

class UserStore {
  sqlite3* db_;

 public:
  UserStore(const std::string& dbFileName) {
    int rc = sqlite3_open(dbFileName.c_str(), &db_);

    std::ostringstream oss;
    if( rc ) {
      oss << "Can't open database:\n" << sqlite3_errmsg(db_);
      sqlite3_close(db_);
      throw std::runtime_error(oss.str());
    }

    const char* initTableSql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, info TEXT);";
    sqlite3_exec(db_, initTableSql, nullptr, nullptr, nullptr);
  }

  ~UserStore() {
    sqlite3_close(db_);
  }

  void put(RowId userId, const std::string& info) {
    static const std::string command = "INSERT OR REPLACE INTO users (id, info) VALUES (?1, ?2);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db_, command.c_str(), command.size(), &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(userId));
    sqlite3_bind_text(stmt, 2, info.c_str(), info.size(), SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cout << "error when put: (" << userId << ", " << info << ")\n";
    }
    sqlite3_finalize(stmt);
  }

  void clear() {
    static const std::string command = "DELETE from users;";
    sqlite3_exec(db_, command.c_str(), nullptr, nullptr, nullptr);
  }

  std::vector<UserRecord> get(RowId userId) const {
    static const std::string query = "SELECT * from users where id = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db_, query.c_str(), query.size(), &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(userId));

    int status = sqlite3_step(stmt);
    std::vector<UserRecord> res;
    if (status == SQLITE_ROW) {
      res.emplace_back(
          static_cast<RowId>(sqlite3_column_int64(stmt, 0)),
          reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    sqlite3_finalize(stmt);
    return res;
  }

  std::vector<UserRecord> range(RowId start, RowId end) const {
    static const std::string query = "SELECT * from users where id BETWEEN ? and ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db_, query.c_str(), query.size(), &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(start));
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(end));

    int status = sqlite3_step(stmt);
    std::vector<UserRecord> res;
    while (status == SQLITE_ROW) {
      res.emplace_back(
          static_cast<RowId>(sqlite3_column_int64(stmt, 0)),
          reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
      status = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return res;
  }

};
