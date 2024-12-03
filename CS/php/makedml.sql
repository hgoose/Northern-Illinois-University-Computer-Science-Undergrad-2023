INSERT INTO user (name) VALUES ("Nate");
INSERT INTO user (name) VALUES ("Dave");
INSERT INTO user (name) VALUES ("Frida");
INSERT INTO user (name) VALUES ("Leslie Lamport");
INSERT INTO user (name) VALUES ("Donald Knuth");
INSERT INTO user (name) VALUES ("Dennis Ritchie");

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

INSERT INTO file (version, song_id) 
    SELECT "Solo", song_id
    FROM song WHERE song.title="Ghost inside a shadow";

INSERT INTO file (version, song_id) 
    SELECT "Solo", song_id
    FROM song WHERE song.title="I hung myself for a persona";

INSERT INTO file (version, song_id) 
    SELECT "Solo", song_id
    FROM song WHERE song.title="angeleyes";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="On the floor";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="I can't fold";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="All Cats Go to Hell";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="Tore up";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="Moving on";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="Dracula freestyle";

INSERT INTO file (version, song_id) 
    SELECT "Duet", song_id
    FROM song WHERE song.title="Talk";

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
