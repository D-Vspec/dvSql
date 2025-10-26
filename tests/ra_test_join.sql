-- SELECT with JOIN for relational algebra conversion
SELECT u.id, u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id;