<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
?>

<?php
    echo <<<END
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.2/css/all.min.css">
        <link rel="stylesheet" href="./style.css">
        <title>Project Website</title>
    </head>
    <body>
    END;
?>

<?php
    function selectAll($pdo, $relation) {
        $query = "SELECT * FROM $relation";    
        $prepare = $pdo->prepare($query); 
        $success = $prepare->execute();

        if ($success) {
            return $prepare->fetchAll(PDO::FETCH_ASSOC);
        }
    }

    function getUsers($pdo) {
        $users = array();

        $query = "SELECT name FROM user";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute();
        if ($success) {
             $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
             foreach ($result as $row) {
                $users[] = $row["name"];
             }
             return $users;
        }
    }

    function getSongHeads($pdo) {
        $query = "
            SELECT title, artist, version, song.song_id, file.file_id 
                FROM song, file
                WHERE song.song_id = file.song_id ;
        ";
        $result = $pdo->query($query, PDO::FETCH_ASSOC);

        $heads = array();
        foreach($result as $row) {
            $heads = array_keys($row);
            return $heads;
        }
    }

    function querySongs($pdo, $song=null) {
        if ($song) {
            $query = "
                SELECT title, artist, version, song.song_id, file.file_id 
                    FROM song, file
                    WHERE song.song_id = file.song_id 
                    AND song.title=:title;
            ";
            $prepare = $pdo->prepare($query);
            $success = $prepare->execute(array(":title" => $song));
            if ($success) {
                return $prepare->fetchAll(PDO::FETCH_ASSOC);
            }
        }
        $query = "
            SELECT title, artist, version, song.song_id, file.file_id 
                FROM song, file
                WHERE song.song_id = file.song_id;
        ";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    function getSongList($pdo) {
        $query = "SELECT title FROM song";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute();
        if ($success) {
            $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
            $ret = array();
            foreach ($result as $row) {
                $ret[] = $row["title"];
            }
            return $ret;
        }
    }

    function getSongVersions($pdo, $song) {
        $query = "SELECT version FROM song, file WHERE song.song_id = file.song_id AND song.title=:t;";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":t" => $song));
        if ($success) {
            $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
            $ret = array();

            foreach ($result as $row) {
                $ret[] = $row["version"];
            }
            return $ret;
        }
    }

    function getUserId($pdo, $name) {
        $query = "SELECT user_id FROM user WHERE user.name=\"$name\"";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    function getSongId($pdo, $name) {
        $query = "SELECT song_id FROM song WHERE title=\"$name\"";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    function validateSong($song, $songList) {
        foreach($songList as $s) {
            if ($song == $s) {
                return true;
            }
        } 
        return false;
    }

    function validateSongandVersion($song, $version, $songList, $versionList): bool {
        $foundSong = false;
        $foundVersion = false;
        foreach($songList as $s) {
            if ($song == $s) {
                $foundSong = true; break;
            }
        } 
        foreach($versionList as $v) {
            if ($v == $version) {
                $foundVersion = true; break; // Endproc
            }
        }
        return ($foundSong && $foundVersion ? true : false);
    }

    function makeSongTable($songHeads, $songList, $tableClass) {
        echo "<table class=\"$tableClass\">";
            // Headings
            echo "<tr>";
            echo "<th> </th>";
            foreach($songHeads as $songHead) {
                echo "<th> $songHead </th>";
            }
            echo "</tr>";

            foreach($songList as $row) {
                echo "<tr>";
                echo "<td> <img src=\"noFilter.png\" id=\"songImg\" alt=\"Song Thumbnail\"></img> </td>";
                foreach($row as $item) {
                    echo "<td> $item </td>";
                }
                echo "</tr>";
            }
        // End songTable
        echo "</table>";
    }

    

    function queryContributors($pdo, $song) {
        // Idk just gonna noop

        // good to query
        $query = "
            SELECT song.title, song.artist, contributor.name, role, contributor.contrib_id 
                FROM song, contributor, song_contributor 
                    WHERE song.song_id = song_contributor.song_id 
                    AND contributor.contrib_id = song_contributor.contrib_id 
                    AND song.title = :title;
        ";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":title" => $song));
        if ($success) {
            return $prepare->fetchAll(PDO::FETCH_ASSOC);
        }
    }

    function getContributorInfoHeads($pdo, $song) {
        $rowone = queryContributors($pdo, $song)[0];
        $ret = array();
        foreach($rowone as $key => $value) {
            $ret[] = $key;
        }
        return $ret;
    }

    function makeContribTable($pdo, $song) {
        if (!validateSong($song, getSongList($pdo))) { echo "<p style='text-align:center;'>Song Not Found</p>"; return; } 
        $heads = getContributorInfoHeads($pdo, $song);
        $info = queryContributors($pdo, $song);
        echo "<table class='songTable'>";
            echo "<tr>";
                foreach($heads as $head) {
                    echo "<th> $head </th>";
                }
            echo "</tr>";
            foreach($info as $row) {
                echo "<tr>";
                    foreach($row as $item) {
                        echo "<td> $item </td>";
                    }
                echo "</tr>";
            }
        echo "</table>";
    }




?>

<!-- Page logic -->
<?php
    include 'dbconnect.php';

    echo <<<END
    <header>
        <a href="index.php" class="logo">Project Karaoke</a>
        <nav>
            <div class="nav-links">
            <a href="index.php" >Home</a>
            <a href="user.php" class="active">User Queue</a>
            <a href="dj.php">DJ Interface</a>
            <a href="signup.php">Sign Up</a>
            <div class="slider-bar"></div>
            </div>
        </nav>
    </header>
    END;

    // Start main
    echo "<main>";

    echo "<div class=\"forms\">";
        $users = getUsers($pdo);
        echo "<form action=\"user.php\" method=\"POST\" class=\"form1\">";
        echo "<select name=\"userSelect\" placeholder=\"Hello\" id=\"userSelect\">";
        foreach ($users as $user) {
            echo "<option> $user </option>";
        }
        echo "</select>";
        echo "<input type=\"text\" name=\"songTitle\" id=\"formInp1\" placeholder=\"Enter song title\" style=\"text-align: center;\">";
        echo "<input type=\"text\" name=\"songVersion\" id=\"formInp2\" placeholder=\"Enter song version\" style=\"text-align: center;\">";
        echo "<input type=\"number\" name=\"payAmount\" id=\"formInp3\" placeholder=\"Pay to enter priority queue\" style=\"text-align: center;\">";
        echo "<input type=\"submit\" id=\"songSubmit\" value=\"Enter queue\">";
        echo "</form>";

    // End Form div
    echo "</div>";

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["userSelect"]) && isset($_POST["songTitle"]) && isset($_POST["songVersion"])) {
            if (validateSongandVersion($_POST["songTitle"], $_POST["songVersion"], getSongList($pdo), getSongVersions($pdo, $_POST["songTitle"]))) {
                echo $_POST["songTitle"];
            }
        }
    }




    echo "<div class=\"songHeading\"><h1> Song Selection </h1></div>";

    echo "<div class=\"songSearch\">";
        echo "<form action=\"user.php\" method=\"POST\" class='songSearchform'>";
            echo "<input type=\"text\" id='songSearchformIN' name=\"songSearch\" placeholder=\"Search for a song\" style=\"text-align: center;\">";
            echo "<input type=\"submit\" id='songSearchformSubmit' value=\"search\">";
        echo "</form>";
    // End song search
    echo "</div>";


    echo "<div class='d1-contain'>";
    echo "<div class=\"d1\">";
            if (isset($_POST["songSearch"]) && validateSong($_POST["songSearch"], getSongList($pdo)) && $_POST["songSearch"] != "all") {
                makeSongTable(getSongHeads($pdo), querySongs($pdo, $_POST["songSearch"]), "songTable");
            } else {
                makeSongTable(getSongHeads($pdo), querySongs($pdo), "songTable");
            }
    // end d1
    echo "</div>";
    // End d1-contain
    echo "</div>";

    echo "<div class='contribHead'> <h1> View Song Contributors </h1> <hr> </hr> </div>";

    echo "<div class='contribInfo'>";
        echo "<form action='user.php' method='POST' class='songContribForm'>";
            echo "<input type='text' name='song' id='songSearchformIN' placeholder='Enter Song title' style='text-align: center;'>";
            echo "<input type='submit' id='songSearchformSubmit' value='View'>";
        echo "</form>";
    echo "</div>";

    echo "<div class='contribTable-contain'>";
    echo "<div class='contribTable'>";
        if ($_SERVER["REQUEST_METHOD"] === "POST") {
            if (isset($_POST["song"])) {
                makeContribTable($pdo, $_POST["song"]);
            }
        }
    echo "</div>";
    echo "</div>";


    // End main
    echo "</main>"
?>

<?php
    echo "</body> </html>";
?>

