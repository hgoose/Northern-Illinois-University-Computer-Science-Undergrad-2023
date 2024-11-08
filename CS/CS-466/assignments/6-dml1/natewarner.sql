-- Created by Nate Warner z2004109
-- Cs466 section 0002

-- Select database, list the relations
USE BabyName;
SHOW TABLES;

-- Get unique names in the year 2003
SELECT DISTINCT name FROM BabyName 
    WHERE year=2003
    LIMIT 50;

-- Describe babyname relation
DESCRIBE BabyName;


-- Get the unique name count per location
SELECT place, count(DISTINCT name) `Unique name count per location` 
    FROM BabyName 
    GROUP BY place
    LIMIT 50;


-- Get the years where name Nate appears
SELECT DISTINCT year FROM BabyName
    WHERE name="Nate"
    LIMIT 50;

-- Get the most popular male and female name for the year 1984
SELECT * FROM (
    SELECT name AS `Most popular male name in 1984`
    FROM BabyName
    WHERE gender="m" AND year=1984
    GROUP BY name
    ORDER BY (count * COUNT(name)) DESC
    LIMIT 1
) as male_result UNION 

SELECT * FROM (
    SELECT name AS `Most popular female name in 1984`
    FROM BabyName
    WHERE gender="f" AND year=1984
    GROUP BY name
    ORDER BY (count * COUNT(name)) DESC
    LIMIT 1
) as female_result;


-- Get names similar to nate
 SELECT DISTINCT *
    FROM BabyName
    WHERE name LIKE "Nat%"
    GROUP BY name
    ORDER BY name DESC, count ASC, year DESC
    LIMIT 50;


-- Get unique names in year 1949
SELECT COUNT(DISTINCT name) as name_count
    FROM BabyName
    WHERE year=1949;


-- Get the number of rows in the tabel
SELECT COUNT(*) AS `Rows in Table` FROM BabyName;


-- Get the number of names for each sex in the year 1973
SELECT 
    (SELECT COUNT(DISTINCT name) FROM BabyName WHERE gender = 'm' AND year = 1973) AS `Number of unique male names in 1973`,
    (SELECT COUNT(DISTINCT name) FROM BabyName WHERE gender = 'f' AND year = 1973) AS `Number of unique female names in 1973`;


-- Get frequency of each first letter
SELECT SUBSTR(name, 1, 1) AS "First Letter", COUNT(DISTINCT name) AS "Frequency"
    FROM BabyName
    GROUP BY SUBSTR(name, 1, 1)
    ORDER BY "First Letter";
