-- Complex SELECT with JOIN and WHERE for relational algebra conversion
SELECT u.id, u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id 
WHERE u.age > 18 AND p.published = 1;