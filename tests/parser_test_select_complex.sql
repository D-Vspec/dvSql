-- Complex SELECT with WHERE, JOIN, and ORDER BY
SELECT u.id, u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id 
WHERE u.age > 18 AND p.published = 1 
ORDER BY u.name;