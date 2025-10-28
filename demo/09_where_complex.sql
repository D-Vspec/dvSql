-- Complex WHERE Clause with Multiple Conditions
-- Combining AND and OR operators

SELECT name, age, email FROM users 
WHERE (age > 20 AND age < 30) OR id = 3;
