-- DDL (Data Definition Language) examples

-- Create table with various data types and constraints
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash CHAR(64) NOT NULL,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    age INT CHECK (age >= 0 AND age <= 150),
    balance DECIMAL(10,2) DEFAULT 0.00,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP
);

-- Create related table with foreign key
CREATE TABLE posts (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    user_id INTEGER NOT NULL,
    title VARCHAR(255) NOT NULL,
    content TEXT,
    published BOOLEAN DEFAULT FALSE,
    likes INTEGER DEFAULT 0,
    created_date DATE,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- Insert sample data
INSERT INTO users (username, email, password_hash, first_name, last_name, age, balance)
VALUES 
    ('john_doe', 'john@example.com', 'hash123', 'John', 'Doe', 25, 100.50),
    ('jane_smith', 'jane@example.com', 'hash456', 'Jane', 'Smith', 30, 250.75);

INSERT INTO posts (user_id, title, content, published, likes)
VALUES 
    (1, 'My First Post', 'This is my first blog post!', TRUE, 15),
    (1, 'SQL Tutorial', 'Learning SQL can be fun...', TRUE, 42),
    (2, 'Draft Post', 'This is still a draft', FALSE, 0);

-- Update statement
UPDATE users 
SET balance = balance + 50.00, updated_at = CURRENT_TIMESTAMP
WHERE username = 'john_doe';

-- Delete statement
DELETE FROM posts 
WHERE published = FALSE AND likes = 0;

-- Alter table
ALTER TABLE users ADD COLUMN phone VARCHAR(20);
ALTER TABLE users DROP COLUMN phone;

-- Drop table
DROP TABLE IF EXISTS temp_table;