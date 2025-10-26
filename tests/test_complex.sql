/* Complex SQL query with multiple features */
-- This is a line comment
SELECT DISTINCT u.id, u.name, p.title, COUNT(*) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
WHERE u.age BETWEEN 18 AND 65
  AND u.status = 'active'
  AND (p.published = TRUE OR p.published IS NULL)
GROUP BY u.id, u.name, p.title
HAVING COUNT(*) > 5
ORDER BY post_count DESC, u.name ASC
LIMIT 10 OFFSET 20;

-- Union query
SELECT name, 'user' as type FROM users
UNION ALL
SELECT title, 'post' as type FROM posts
WHERE created_date >= '2023-01-01';

-- Subquery with EXISTS
SELECT * FROM users u
WHERE EXISTS (
    SELECT 1 FROM posts p 
    WHERE p.user_id = u.id 
    AND p.likes > 100
);

-- Aggregate functions
SELECT 
    COUNT(*) as total_users,
    AVG(age) as avg_age,
    MIN(created_date) as first_user,
    MAX(last_login) as recent_login,
    SUM(post_count) as total_posts
FROM users;