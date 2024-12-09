CREATE TABLE `contributor` (
  `contrib_id` int(32) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`contrib_id`)
);

CREATE TABLE `song` (
  `song_id` int(32) NOT NULL AUTO_INCREMENT,
  `artist` varchar(100) NOT NULL,
  `title` varchar(100) NOT NULL,
  PRIMARY KEY (`song_id`)
);

CREATE TABLE `file` (
  `file_id` int(32) NOT NULL AUTO_INCREMENT,
  `version` varchar(100) NOT NULL,
  `song_id` int(32) NOT NULL,
  PRIMARY KEY (`file_id`),
  FOREIGN KEY (`song_id`) REFERENCES `song` (`song_id`)
);

CREATE TABLE `song_contributor` (
  `song_id` int(32) NOT NULL,
  `contrib_id` int(32) NOT NULL,
  `role` varchar(100) NOT NULL,
  PRIMARY KEY (`song_id`,`contrib_id`),
  FOREIGN KEY (`song_id`) REFERENCES `song` (`song_id`),
  FOREIGN KEY (`contrib_id`) REFERENCES `contributor` (`contrib_id`)
);

CREATE TABLE `user` (
  `user_id` int(32) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`user_id`)
);

CREATE TABLE `user_song` (
    `position` int(100) NOT NULL AUTO_INCREMENT,
  `user_id` int(32) NOT NULL,
  `song_id` int(32) NOT NULL,
  `queue_type` char(1) DEFAULT NULL,
  `payment` float DEFAULT NULL,
    `date` datetime NOT NULL,
  PRIMARY KEY (`user_id`,`song_id`, date),
  FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
  FOREIGN KEY (`song_id`) REFERENCES `song` (`song_id`),
    INDEX(position)
);

INSERT INTO user (name) VALUES ("Nate");
INSERT INTO user (name) VALUES ("Dave");
INSERT INTO user (name) VALUES ("Frida");
INSERT INTO user (name) VALUES ("Leslie Lamport");
INSERT INTO user (name) VALUES ("Donald Knuth");
INSERT INTO user (name) VALUES ("Dennis Ritchie");
INSERT INTO user (name) VALUES ("Grace Hopper");
INSERT INTO user (name) VALUES ("Alan Turing");
INSERT INTO user (name) VALUES ("Ada Lovelace");
INSERT INTO user (name) VALUES ("Edsger Dijkstra");
INSERT INTO user (name) VALUES ("Linus Torvalds");

INSERT INTO song(artist, title) VALUES ("Dave Blunts", "The Cup");
INSERT INTO song(artist, title) VALUES ("Amy Winehouse", "Tears Dry On Their Own");
INSERT INTO song(artist, title) VALUES ("Beyonce","Halo");
INSERT INTO song(artist, title) VALUES ("OutKast", "Love Hater");
INSERT INTO song(artist, title) VALUES ("JPEGMAFIA, Danny Brown", "HOE(Heaven on Earth)");
INSERT INTO song(artist, title) VALUES ("Radiohead", "My Iron Lung");
INSERT INTO song(artist, title) VALUES ("Radiohead", "Paranoid Android");
INSERT INTO song(artist, title) VALUES ("She Wants Revenge", "Tear You Apart");
INSERT INTO song(artist, title) VALUES ("The Garden", "Egg");
INSERT INTO song(artist, title) VALUES ("Playboi Carti", "On That Time");
INSERT INTO song(artist, title) VALUES ("Playboi Carti, Chief Keef", "Mileage(feat. Chief Keef)");
INSERT INTO song(artist, title) VALUES ("Adele", "Rolling in the Deep");
INSERT INTO song(artist, title) VALUES ("Radiohead", "Creep");
INSERT INTO song(artist, title) VALUES ("Nirvana", "Smells Like Teen Spirit");
INSERT INTO song(artist, title) VALUES ("Kendrick Lamar", "HUMBLE");
INSERT INTO song(artist, title) VALUES ("Adele", "Someone Like You");
INSERT INTO song(artist, title) VALUES ("Micheal Jackson", "Thriller");
INSERT INTO song(artist, title) VALUES ("Billie Eilish", "Bad Guy");
INSERT INTO song(artist, title) VALUES ("Beyonce", "Drunk in Love");
INSERT INTO song(artist, title) VALUES ("Foo Fighters", "Everlong");
INSERT INTO song(artist, title) VALUES ("Kanye West", "Flashing Lights");
INSERT INTO song(artist, title) VALUES ("Kendrick Lamar", "DNA");
INSERT INTO song(artist, title) VALUES ("Travis Scott", "5% TINT");
INSERT INTO song(artist, title) VALUES ("Travis Scott", "STOP TRYING TO BE GOD");
INSERT INTO song(artist, title) VALUES ("Nirvana", "Heart-Shaped Box");
INSERT INTO song(artist, title) VALUES ("Beyonce", "Drunk in Love ft. Jay-Z");
INSERT INTO song (artist, title) VALUES ("Wifisfuneral", "Ghost inside a shadow");
INSERT INTO song (artist, title) VALUES ("$uicideboy$", "I hung myself for a persona");
INSERT INTO song (artist, title) VALUES ("Kenny mason", "angeleyes");
INSERT INTO song (artist, title) VALUES ("Yung goth", "On the floor");
INSERT INTO song (artist, title) VALUES ("Wifisfuneral", "I can't fold");
INSERT INTO song (artist, title) VALUES ("Suisside", "All Cats Go To Hell");
INSERT INTO song (artist, title) VALUES ("Don Toliver", "Tore up");
INSERT INTO song (artist, title) VALUES ("Peep", "Moving on");
INSERT INTO song (artist, title) VALUES ("93FEETOFSMOKE", "Dracula freestyle");
INSERT INTO song (artist, title) VALUES ("Yeet", "Talk");



INSERT INTO contributor(name) VALUES ("Jonh Leckie");
INSERT INTO contributor(name)  VALUES ("Colin Greenwood");
INSERT INTO contributor(name)  VALUES ("Beyonce");
INSERT INTO contributor(name)  VALUES ("Jordan Carter");
INSERT INTO contributor(name)  VALUES ("Adele Adkins") ;
INSERT INTO contributor(name)  VALUES ("Paul Epworth") ;
INSERT INTO contributor(name)  VALUES ("Kanye West") ;
INSERT INTO contributor(name)  VALUES ("Mike WiLL Made-it");
INSERT INTO contributor(name)  VALUES ("Jacques Webster") ;
INSERT INTO contributor(name)  VALUES ( "Kurt Cobain");;
INSERT INTO contributor (name) VALUES ("Isaih Rivera");
INSERT INTO contributor (name) VALUES ("Scott Arceneaux Jr");
INSERT INTO contributor (name) VALUES ("Aristos Pertrou");
INSERT INTO contributor (name) VALUES ("Edwin Green");
INSERT INTO contributor (name) VALUES ("Edward Maclin Cooper III");
INSERT INTO contributor (name) VALUES ("Lil Peep");
INSERT INTO contributor (name) VALUES ("Yunggoth");
INSERT INTO contributor (name) VALUES ("Wifisfuneral");
INSERT INTO contributor (name) VALUES ("$uicideboy$");
INSERT INTO contributor (name) VALUES ("Dairon Leonardo Cruz");
INSERT INTO contributor (name) VALUES ("Suisside");
INSERT INTO contributor (name) VALUES ("Don Toliver");
INSERT INTO contributor (name) VALUES ("BBYKOBE");
INSERT INTO contributor (name) VALUES ("Matty Spats");
INSERT INTO contributor (name) VALUES ("Gustav Ahr");
INSERT INTO contributor (name) VALUES ("Benjamin Friars-Funkhauser");
INSERT INTO contributor (name) VALUES ("93FEETOFSMOKE");
INSERT INTO contributor (name) VALUES ("Mark Androw Taylor");
INSERT INTO contributor (name) VALUES ("Yeet");
INSERT INTO contributor (name) VALUES ("Noah Smith");
INSERT INTO contributor (name) VALUES ("Benjamin Saint Fort");
INSERT INTO contributor (name) VALUES ("Kenny Mason");

INSERT INTO file (version, song_id) VALUES ("Acoustic", 014);
INSERT INTO file (version, song_id) VALUES ("Studio", 014);
INSERT INTO file (version, song_id) VALUES ("Studio", 018);
INSERT INTO file (version, song_id) VALUES ("Studio", 016);
INSERT INTO file (version, song_id) VALUES ("Piano Version", 016);
INSERT INTO file (version, song_id) VALUES ("Studio", 022);
INSERT INTO file (version, song_id) VALUES ("Live Version", 022);
INSERT INTO file (version, song_id) VALUES ("Acoustic", 019);
INSERT INTO file (version, song_id) VALUES ("Studio", 019);
INSERT INTO file (version, song_id) VALUES ("Remix", 026);
INSERT INTO file (version, song_id) VALUES ("solo", 001);
INSERT INTO file (version, song_id) VALUES ("solo", 002);
INSERT INTO file (version, song_id) VALUES ("solo", 003);
INSERT INTO file (version, song_id) VALUES ("solo", 004);
INSERT INTO file (version, song_id) VALUES ("solo", 005);
INSERT INTO file (version, song_id) VALUES ("solo", 006);
INSERT INTO file (version, song_id) VALUES ("solo", 007);
INSERT INTO file (version, song_id) VALUES ("solo", 008);
INSERT INTO file (version, song_id) VALUES ("solo", 009);
INSERT INTO file (version, song_id) VALUES ("solo", 010);
INSERT INTO file (version, song_id) VALUES ("solo", 011);
INSERT INTO file (version, song_id) VALUES ("solo", 012);
INSERT INTO file (version, song_id) VALUES ("solo", 013);
INSERT INTO file (version, song_id) VALUES ("solo", 015);
INSERT INTO file (version, song_id) VALUES ("solo", 017);
INSERT INTO file (version, song_id) VALUES ("solo", 020);
INSERT INTO file (version, song_id) VALUES ("solo", 021);
INSERT INTO file (version, song_id) VALUES ("solo", 023);
INSERT INTO file (version, song_id) VALUES ("solo", 024);
INSERT INTO file (version, song_id) VALUES ("solo", 025);
INSERT INTO file (version, song_id) VALUES ("solo", 027);
INSERT INTO file (version, song_id) VALUES ("solo", 028);
INSERT INTO file (version, song_id) VALUES ("solo", 029);
INSERT INTO file (version, song_id) VALUES ("solo", 030);
INSERT INTO file (version, song_id) VALUES ("solo", 031);
INSERT INTO file (version, song_id) VALUES ("solo", 032);
INSERT INTO file (version, song_id) VALUES ("solo", 033);
INSERT INTO file (version, song_id) VALUES ("solo", 034) ;
INSERT INTO file (version, song_id) VALUES ("solo", 035) ;
INSERT INTO file (version, song_id) VALUES ("solo", 036) ;

INSERT INTO song_contributor VALUES (006, 1, "Producer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (007, 1, "Producer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (013, 1, "Producer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (006, 2, "Composer" ) ;
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (007, 2, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (013, 2, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (003, 3, "Lyricist" ) ;
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (019, 3, "Lyricist" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (026, 3, "Lyricist" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (010, 4, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (011, 4, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (012, 5, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (016, 5, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (012, 6, "Producer" ) ;
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (021, 7, "Producer, Composer");
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (022, 8, "Producer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (015, 8, "Producer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (023, 9, "Lyricist" ) ;
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (024, 9, "Lyricist" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (014, 10, "Composer" );
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (025, 10, "Composer" );

-- Song 1
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Ghost inside a shadow"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Wifisfuneral";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Ghost inside a shadow"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Isaih Rivera";
--

-- Song 2
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I hung myself for a persona"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "$uicideboy$";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I hung myself for a persona"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Scott Arceneaux Jr";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I hung myself for a persona"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Aristos Pertrou";
--

--Song 3
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "angeleyes"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Kenny Mason";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "angeleyes"), 
    contrib_id, 
    "Composer; Lyricist"
FROM contributor
WHERE name = "Edwin Green";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "angeleyes"), 
    contrib_id, 
    "Composer; Lyricist"
FROM contributor
WHERE name = "Edward Maclin Cooper III";
--

--Song 4
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "On the floor"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Yunggoth";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "On the floor"), 
    contrib_id, 
    "Featured Artist"
FROM contributor
WHERE name = "Lil Peep";
--

--Song 5
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I can't fold"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Wifisfuneral";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I can't fold"), 
    contrib_id, 
    "Featured Artist"
FROM contributor
WHERE name = "$uicideboy$";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "I can't fold"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Isaih Rivera";
--

--Song 6
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "All Cats Go To Hell"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Suisside";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "All Cats Go To Hell"), 
    contrib_id, 
    "Lyricist"
FROM contributor
WHERE name = "Dairon Leonardo Cruz";
--

--Song 7
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Tore up"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Don Toliver";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Tore up"), 
    contrib_id, 
    "Producer"
FROM contributor
WHERE name = "BBYKOBE";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Tore up"), 
    contrib_id, 
    "Producer"
FROM contributor
WHERE name = "Matty Spats";
--

--Song 8
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Moving on"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Lil Peep";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Moving on"), 
    contrib_id, 
    "Composer; Lyricist"
FROM contributor
WHERE name = "Gustav Ahr";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Moving on"), 
    contrib_id, 
    "Composer; Lyricist"
FROM contributor
WHERE name = "Benjamin Friars-Funkhauser";
--

--Song 9
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Dracula freestyle"), 
    contrib_id, 
    "Main artist; Producer"
FROM contributor
WHERE name = "93FEETOFSMOKE";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Dracula freestyle"), 
    contrib_id, 
    "Composer; Lyricist"
FROM contributor
WHERE name = "Mark Androw Taylor";
--

--Song 10
INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Talk"), 
    contrib_id, 
    "Main Artist"
FROM contributor
WHERE name = "Yeet";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Talk"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Noah Smith";

INSERT INTO song_contributor (song_id, contrib_id, role)
SELECT 
    (SELECT song_id FROM song WHERE title = "Talk"), 
    contrib_id, 
    "Composer"
FROM contributor
WHERE name = "Benjamin Saint Fort";
--


INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (1, 003, 'F', 0,'2024-12-04 02:30:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (2, 012, 'F', 0,'2024-12-04 02:31:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (3, 020, 'F', 0,'2024-12-04 02:32:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (4, 008, 'F', 0,'2024-12-04 02:33:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (5, 030, 'F', 0,'2024-12-04 02:34:50');

INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (6, 015, 'P', 10.00,'2024-12-04 02:35:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (7, 028, 'P', 12.00,'2024-12-04 02:36:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (8, 031, 'P', 14.00,'2024-12-04 02:37:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (9, 001, 'P', 16.00,'2024-12-04 02:38:50');
INSERT INTO user_song (user_id, song_id, queue_type, payment, date) VALUES (10, 005, 'P', 18.00,'2024-12-04 02:39:50');

