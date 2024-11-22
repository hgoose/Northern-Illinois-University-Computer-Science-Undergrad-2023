INSERT INTO user (name) VALUES ("hmane");
INSERT INTO user (name) VALUES ("set");
INSERT INTO user (name) VALUES ("kratomboofer69");
INSERT INTO user (name) VALUES ("doubleword");
INSERT INTO user (name) VALUES ("sigma");

INSERT INTO song (artist, title) VALUES ("set", "t1");
INSERT INTO song (artist, title) VALUES ("set", "t2");
INSERT INTO song (artist, title) VALUES ("set", "t3");
INSERT INTO song (artist, title) VALUES ("set", "t4");
INSERT INTO song (artist, title) VALUES ("set", "t5");

INSERT INTO file (version, song_id) VALUES ("standard", 1);
INSERT INTO file (version, song_id) VALUES ("standard", 2);
INSERT INTO file (version, song_id) VALUES ("standard", 3);
INSERT INTO file (version, song_id) VALUES ("standard", 4);
INSERT INTO file (version, song_id) VALUES ("standard", 5);

INSERT INTO contributor (contrib_id, name) VALUES (1, "prod");

INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (1, 1, "writer");
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (2, 1, "writer");
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (3, 1, "writer");
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (4, 1, "writer");
INSERT INTO song_contributor (song_id, contrib_id, role) VALUES (5, 1, "writer");

