-- Assignment 7 Nate Warner z2004109 10/28/24
-- Cs-466 Section 0002

-- List authors first and last names, in ascending order
SELECT AuthorLast, AuthorFirst FROM Author ORDER BY AuthorFirst ASC;

-- Get citys that have publishers (distinct)
SELECT DISTINCT City FROM Publisher;

-- Show how many book titles exist in the database
SELECT DISTINCT Title FROM Book;

-- List the names of all of the branches along with the total number of books on hand at each of those branchs
SELECT BranchName, COUNT(OnHand) AS "Total OnHand Per Branch"
    FROM Branch JOIN Inventory 
    ON Branch.BranchNum = Inventory.BranchNum 
    GROUP BY Inventory.BranchNum;

-- Show the number of employees that work at Henry Books.
SELECT SUM(NumEmployees) AS "Number of employees" FROM Branch;

-- List the titles of all books written by Stephen King
SELECT Title AS "Books written by stephen king" FROM Book 
    WHERE Book.BookCode IN 
        (
            SELECT BookCode FROM Author 
                JOIN Wrote ON 
                Author.AuthorNum = Wrote.AuthorNum 
                AND Author.AuthorNum = 6
        );
-- List the title, type and price for all of the paperback books.
SELECT Title, Type, Price 
    FROM Book 
    WHERE PaperBack="y";

-- Show the names of all of the branches that have at least one book with ten or more copies on hand.
SELECT BranchName FROM Branch 
    WHERE BranchNum IN 
    (
        Select BranchNum FROM Inventory 
        GROUP BY BookCode 
        HAVING SUM(OnHand) > 9
    ); -- \varnothing

-- List the title and the full name of the author for each book in reverse alphabetical order by title.
-- I know theres an easier way to do this but I did this and it works so im going to keep it
SELECT Title, AuthorWrote.AuthorFirst, AuthorWrote.AuthorLast FROM Book, (SELECT AuthorFirst, AuthorLast, BookCode FROM Author JOIN Wrote   
    ON Author.AuthorNum = Wrote.AuthorNum) AS AuthorWrote
    WHERE AuthorWrote.BookCode = Book.BookCode
    ORDER BY Title DESC;

-- List all of publishers by name, along with how many books each of those publishers has published.
-- I will no longer be using INNER JOIN Syntax 
SELECT Publisher.PublisherName, COUNT(Title) AS "Number of books published" FROM Book, Publisher 
    WHERE Book.PublisherCode = Publisher.PublisherCode 
    GROUP BY Book.PublisherCode
    ORDER BY COUNT(Title) DESC;

-- Show the number of books that cost less than $10.00.
SELECT COUNT(Price) From Book 
    WHERE Price < 10.00;

-- List the last name for all of the authors published by Simon and Schuster.
SELECT AuthorLast FROM Author 
    WHERE AuthorNum IN 
    (
        SELECT AuthorNum FROM Wrote 
        WHERE Wrote.BookCode IN 
        (
            SELECT BookCode FROM Book 
            WHERE Book.PublisherCode = (SELECT Publisher.PublisherCode FROM Publisher WHERE PublisherName = "Simon and Schuster")
        )
);

-- Show a list with all the types of books and how many books there are for each of them.
SELECT Type, COUNT(Title) FROM Book GROUP BY Type;

-- Show the number of books on hand at the Brentwood Mall location.
SELECT SUM(OnHand) AS "Books at Brenntwood Mall" FROM Branch, Inventory 
    WHERE Branch.BranchNum = Inventory.BranchNum 
    AND Branch.BranchNum = 
        (
            SELECT BranchNum FROM Branch 
            WHERE Branch.BranchLocation = "Brentwood Mall"
        ) 
    GROUP BY Branch.BranchNum;

-- List all of the branch locations along with the number of employees and the number of books on hand at each of those branches.
SELECT BranchLocation, NumEmployees, joined.sumOnhand 
    FROM Branch, (
        SELECT Branch.BranchNum, SUM(OnHand) AS "sumOnhand" 
        FROM Branch, Inventory 
        WHERE Branch.BranchNum = Inventory.BranchNum 
        GROUP BY Branch.BranchNum
    ) AS joined 
    WHERE Branch.BranchNum = joined.BranchNum;

-- List the titles of all of the books which have a sequence number of one. Use a subquery to do it.
SELECT Title FROM Book 
    WHERE BookCode IN (
        Select BookCode FROM Wrote WHERE Sequence=1
    );

-- List all of the publishers whose name begins with “T”.
SELECT PublisherName From Publisher WHERE PublisherName LIKE "T%";

-- List all of the information pertaining to authors that have a double-L in their name (“ll”).
SELECT * From Publisher WHERE PublisherName LIKE "%ll%";

-- List all of the book titles that have a book code of 079x, 138x, or 669x
SELECT Title FROM Book WHERE Book.BookCode IN ("079X", "138X", "669X");

-- Show the titles of all the books, along with their author’s last name and the name of the publisher, sorted in alphabetical order by the publisher’s name.
-- This is the better way to do some of the other ones above but they work so im going to leave them
SELECT Author.AuthorLast, Publisher.PublisherName, Book.Title 
    FROM Publisher JOIN Book JOIN Wrote JOIN Author 
    ON Book.PublisherCode = Publisher.PublisherCode 
    AND Wrote.BookCode = Book.BookCode 
    AND Author.AuthorNum = Wrote.AuthorNum;


-- Do any two of the above items again, accomplishing the task in a different way. (Different SQL for same result.)

-- 1. Number 19 (List all of the book titles that have a book code of 079x, 138x, or 669x.) Using OR instead of IN SET
SELECT Title FROM Book WHERE Book.BookCode = "079X" OR Book.BookCode="138X" OR Book.BookCode = "669X";

-- 2. Number 17 (List all of the publishers whose name begins with “T”). Using SUBSTR Instead of LIKE 
SELECT PublisherName From Publisher WHERE SUBSTR(PublisherName, 1,1) = "T";

-- Get the total number of books at hand (sum of onhand at all locations)
SELECT SUM(total) FROM (
    SELECT COUNT(OnHand) AS "total" 
    FROM Branch JOIN Inventory 
    ON Branch.BranchNum = Inventory.BranchNum 
    GROUP BY Inventory.BranchNum
) as sums;
