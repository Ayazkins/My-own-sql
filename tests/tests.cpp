#include "../lib/BD/BD.h"
#include "../lib/BD/BD.cpp"
#include "gtest/gtest.h"

TEST(SQL_TEST, CREATE) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  EXPECT_EQ(B.tables_["users"].columns_[0].Name(), "id");
  EXPECT_EQ(B.tables_["users"].columns_[0].Type(), Type::INT);
  EXPECT_EQ(B.tables_["users"].columns_[0].Key(), "PRIMARY KEY");
  EXPECT_EQ(B.tables_["users"].columns_[1].Name(), "name");
  EXPECT_EQ(B.tables_["users"].columns_[1].Type(), Type::VARCHAR);
  EXPECT_EQ(B.tables_["users"].columns_[1].Key(), "NOT KEY");
  B.Parse("SELECT * FROM users;");
}

TEST(SQL_TEST, INSERT) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  B.Parse("INSERT INTO users (id, name, email) VALUES (1, 'John', 'john@example.com');");
  B.Parse("INSERT INTO users (id, name, email) VALUES (2, 'Emma', 'emma@example.com');");
  std::vector<std::vector<std::string>>
	  a = {{"1", "'John'", "'john@example.com'"}, {"2", "'Emma'", "'emma@example.com'"}};
  for (int i = 0; i < 2; ++i) {
	int k = 0;
	for (auto x : {"id", "name", "email"}) {
	  EXPECT_EQ(B.tables_["users"].data_[i].data[x], a[i][k]);
	  k++;
	}
  }
  B.Parse("SELECT * FROM users;");
}

TEST(SQL_TEST, UPDATE) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  B.Parse("INSERT INTO users (id, name, email) VALUES (1, 'John', 'john@example.com');");
  B.Parse("INSERT INTO users (id, name, email) VALUES (2, 'Emma', 'emma@example.com');");
  B.Parse("UPDATE users SET id = 30, name = 'ayaz' WHERE id = 2;");
  std::vector<std::vector<std::string>>
	  a = {{"1", "'John'", "'john@example.com'"}, {"30", "'ayaz'", "'emma@example.com'"}};
  for (int i = 0; i < 2; ++i) {
	int k = 0;
	for (auto x : {"id", "name", "email"}) {
	  EXPECT_EQ(B.tables_["users"].data_[i].data[x], a[i][k]);
	  k++;
	}
  }
  B.Parse("SELECT * FROM users;");
}

TEST(SQL_TEST, DELETE) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  B.Parse("INSERT INTO users (id, name, email) VALUES (1, 'John', 'john@example.com');");
  B.Parse("INSERT INTO users (id, name, email) VALUES (2, 'Emma', 'emma@example.com');");
  B.Parse("DELETE FROM users WHERE name = Emma;");
  std::vector<std::vector<std::string>>
	  a = {{"1", "'John'", "'john@example.com'"}};
  for (int i = 0; i < 1; ++i) {
	int k = 0;
	for (auto x : {"id", "name", "email"}) {
	  EXPECT_EQ(B.tables_["users"].data_[i].data[x], a[i][k]);
	  k++;
	}
  }
  B.Parse("SELECT * FROM users;");
}

TEST(SQL_TEST, SELEST) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  B.Parse("INSERT INTO users (id, name, email) VALUES (1, 'John', 'john@example.com');");
  B.Parse("INSERT INTO users (id, name, email) VALUES (2, 'Emma', 'emma@example.com');");
  B.Parse("SELECT name, email FROM users WHERE id = 2, name = Emma;");
}

TEST(SQL_TEST, SAVE_LOAD) {
  MyCoolDB B;
  B.Parse("CREATE TABLE users (id int PRIMARY KEY, name varchar, email varchar);");
  B.Parse("INSERT INTO users (id, name, email) VALUES (1, 'John', 'john@example.com');");
  B.Parse("INSERT INTO users (id, name, email) VALUES (2, 'Emma', 'emma@example.com');");
  B.SaveTofIle("C:\\Users\\10a-y\\CLionProjects\\labwork-12-Ayazkins\\tests\\testing.txt");
  MyCoolDB C;
  C.LoadTables("C:\\Users\\10a-y\\CLionProjects\\labwork-12-Ayazkins\\tests\\testing.txt");
  C.Parse("SELECT * FROM users");
}