CREATE DATABASE IF NOT EXISTS epytodo;
USE epytodo;

CREATE TABLE IF NOT EXISTS user (
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    email VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL,
    name VARCHAR(50) NOT NULL,
    firstname VARCHAR(50) NOT NULL,
    created_at DATETIME DEFAULT current_timestamp()
);

CREATE TABLE IF NOT EXISTS todo (
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    description TEXT NOT NULL,
    created_at DATETIME DEFAULT current_timestamp(),
    due_time DATETIME NOT NULL,
    status ENUM("not started", "todo", "in progress", "done") DEFAULT "not started",
    user_id INT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES user(id)
);