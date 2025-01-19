-- Created by Nate Warner z2004109

DROP TABLE Visit;
DROP TABLE Dog;

CREATE TABLE Dog (
    DogID INT NOT NULL AUTO_INCREMENT,
    Breed VARCHAR(255),
    Name VARCHAR(255),
    Weight INT,
    PRIMARY KEY(DogID)
);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('German Shepherd', 'Billy', 75);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('Bulldog', 'Princess', 65);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('Border Collie', 'Tux', 70);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('Beagle', 'Dwight', 55);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('Husky', 'Euler', 80);

INSERT INTO Dog 
    (Breed, Name, Weight)
    VALUES ('Labrador Retriever', 'Hessian', 90);

DESCRIBE Dog;
SELECT * FROM Dog;

CREATE TABLE Visit (
    VisitID INT NOT NULL AUTO_INCREMENT,
    DogID INT,
    Date TIMESTAMP,
    PRIMARY KEY(VisitID),
    FOREIGN KEY(DogID) REFERENCES Dog(DogID)
);

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-08-24 7:26:59', 3); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-08-26 3:21:59', 1);

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-08-27 1:10:59', 2); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-2 2:16:59', 2); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-4 3:14:59', 5);

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-8 6:26:59', 1); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-10 10:10:59', 2); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-12 12:06:59', 4); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-14 1:01:59', 6); 

INSERT INTO Visit
    (Date, DogID)
    Values ('2024-09-20 8:12:59', 3); 

DESCRIBE Visit;
SELECT * FROM Visit;

ALTER TABLE Visit ADD (BillAmount DECIMAL(6,2));

UPDATE Visit 
    SET BillAmount = 100.29
    WHERE DogID=1;

UPDATE Visit 
    SET BillAmount = 200.29
    WHERE DogID=2;

UPDATE Visit 
    SET BillAmount = 300.29
    WHERE DogID=3;

UPDATE Visit 
    SET BillAmount = 400.29
    WHERE DogID=4;

UPDATE Visit 
    SET BillAmount = 500.29
    WHERE DogID=5;

UPDATE Visit 
    SET BillAmount = 600.29
    WHERE DogID=6;

SELECT * FROM Visit;




