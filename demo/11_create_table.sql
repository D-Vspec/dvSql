-- CREATE TABLE Statement
-- Define a new table structure

CREATE TABLE products (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    price DECIMAL,
    stock INT,
    category VARCHAR(50)
);
