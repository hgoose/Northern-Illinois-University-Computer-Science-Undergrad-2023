<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
?>
<?php
    // testmane.php
?>


<?php
    // function addToQueue($pdo, $name, $song, $file, $qt) {
    //     $query = "INSERT INTO user_song"
    // }
    function getUsers($pdo) {
        $query = "SELECT name FROM user";
        $result = $pdo->query($query, PdO::FETCH_ASSOC);
        return $result;
    }

    function getSongHeads($pdo) {
        $query = "
            SELECT title, artist, version, contributor.name AS \"Contributor\", song_contributor.role, song.song_id, file.file_id 
                FROM song, file, contributor, song_contributor 
                WHERE song.song_id = file.song_id 
                AND song_contributor.song_id = song.song_id 
                AND contributor.contrib_id = song_contributor.contrib_id

        ";
        $result = $pdo->query($query, PDO::FETCH_ASSOC);

        $heads = array();
        foreach($result as $row) {
            $heads = array_keys($row);
            return $heads;
        }
    }

    function querySongs($pdo) {
        $query = "
            SELECT title, artist, version, contributor.name AS \"contributor\", song_contributor.role, song.song_id, file.file_id 
                FROM song, file, contributor, song_contributor 
                WHERE song.song_id = file.song_id 
                AND song_contributor.song_id = song.song_id 
                AND contributor.contrib_id = song_contributor.contrib_id
        ";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    function getUserId($pdo, $name) {
        $query = "SELECT user_id FROM user WHERE user.name=\"$name\"";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    function getSongId($pdo, $name) {
        $query = "SELECT song_id FROM song WHERE title=\"$name\"";
        return $pdo->query($query, PDO::FETCH_ASSOC);
    }

    // function addToQueue($pdo, $username, $songname) {
    //     $userId = getUserId($pdo, $username);
    //     $userId = getSongId($pdo, $songname);
    //     $query = "INSERT INTO user_song";
    // }
?>

<?php
    try {

        $username = "datura";
        $password = "goose";
        $db = "app";
        $host = "localhost";
        $dsn = "mysql:host=$host;dbname=$db";

        $pdo = new PDO($dsn, $username, $password);

    } catch (PDOException $e) {
        echo $e->getMessage();
    }

    echo "<div class=\"header1\"> <h1> web stuff </h1> </div>";

    echo "<div class=\"userFormContain\">";

    echo "<div class=\"userContain\">";

    $userRows = getUsers($pdo);
    echo "<table class=\"userTable\">";
        echo "<th> Users </th>";
        foreach($userRows as $row) {
            echo "<tr>";
            foreach($row as $item) {
                echo "<td> $item </td>";
            }
            echo "</tr>";
        }
    echo "</table>";

    // End userContain
    echo "</div>";

    echo "<div class=\"formContain\">";
    echo "<form action=\"testmane.php\" method=\"POST\" id=\"form1\">";
        echo "<input type=\"text\" name=\"nameIn\" id=\"nameInput\" placeholder=\"Enter name\">";
        echo "<input type=\"text\" name=\"songIn\" id=\"songInput\" placeholder=\"Enter Song\">";
        echo "<input type=\"text\" name=\"fileIn\" id=\"fileInput\" placeholder=\"Enter file\">";
        echo "<input type=\"submit\" id=\"formSubmit\" value=\"enter\">";
    echo "</form></div>";

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["nameIn"]) && isset($_POST["songIn"]) && isset($_POST["fileIn"])) {
            $thing = getUserId($pdo, $_POST["nameIn"]);
            $otherThing = getSongId($pdo, $_POST["songIn"]);
            foreach($thing as $t) {
                $userId = $t["user_id"];
            }
            foreach ($otherThing as $ot) {
                $songid = $ot["song_id"];
            }
            // addToQueue($pdo);
        }
    }


    // End userFormContain
    echo "</div>";

   $heads = getSongHeads($pdo); 
   $songRows = querySongs($pdo);
    echo "<div class=\"songList\">";
        echo "<table class=\"songTable\">";
            echo "<tr>";  
            foreach ($heads as $head) {
                echo "<th>$head</th>"; 
            }
            echo "</tr>";

            foreach ($songRows as $row) {
                echo "<tr>";  
                foreach ($row as $item) {
                    echo "<td>$item</td>";  
                }
                echo "</tr>";
            }
        echo "</table>";
    echo "</div>";

    echo "<div class=\"songList\">";
        echo "<table class=\"songTable\">";
            echo "<tr>";  
            foreach ($heads as $head) {
                echo "<th>$head</th>"; 
            }
            echo "</tr>";

            foreach ($songRows as $row) {
                echo "<tr>";  
                foreach ($row as $item) {
                    echo "<td>$item</td>";  
                }
                echo "</tr>";
            }
        echo "</table>";
    echo "</div>";




    echo "<div class=\"cornerImg\">";
    echo "<a href=\"\" target=\"_blank\">";
        echo "<img src=\"https://i.imgur.com/AP1eVGL.png\" alt=\"tux\">";
    echo "</a>";
    echo "</div>";


?>

<?php
    echo <<<END
        <style>
            * {
                margin: 0;
            }
            body {
                background-color: #282828;
                border: 5px solid #F08FFD;
                color: white;
            }

            .header1 {
                display: flex;
                justify-content: center;
                width: 100%;
                height: 5%;
                background-color: #7ED7B7;
            }

            /* pink */
            .userFormContain {
                display: flex;
                flex-direction: row;
                width: 100%;
                height: 30%;
                /* background-color: pink */;
            }

            /* blue */
            .userContain {
                display: flex;
                justify-content: center;
                width: 30%;
                height: 100%;
                /* background-color: blue; */
               overflow: scroll;

            }

            .userContain table {
               border: 2px solid; 
               width: 100%;
               font-size: 1.2rem;
               overflow: scroll;
            }

            .userTable th{
                border: 2px solid;
            }

            .userTable td {
                border: 2px solid;
                padding-left: 2%;
            }

            .userTable th:hover, td:hover {
                background-color: pink;
            }
           
            /* green */
            .formContain {
                display: flex;
                flex-wrap: wrap;
                justify-content: center;
                align-items: center;
                width: 70%;
                height: 100%;
                /* background-color: green; */
            }
            
            .formContain form {
                display: flex;
                width: 60%;
                flex-direction: row;
                flex-wrap: wrap;
            } 

            .formContain form input {
                text-align: center;
                margin-right: 5px;
                margin-top: 5px;
                border-radius: 10px;
            }

            .formContain form input:hover {
                background-color: #F8C7FF;
            }

            #nameInput, #songInput, #fileInput {
                padding: 10px;
                border: none;
                outline: none;
                margin-right; 10px;
            }

            #formSubmit {
                border: none;
                width: 20%;
                outline: none;
            }

            .songList {
                display: flex;
                justify-content: center;
                margin-top: 1%;
            }

            .songTable {
                border: 2px solid;
                width: 90%;
                text-align: center;
                font-size: 1.5rem;
            }

            .songTable tr {
                border: 2px solid;
            }

            .cornerImg a img{
                width: 5%;
                height; 5%;
                position: fixed;
                bottom: 10px;
                left: 10px;
            }

        


        </style>
    END;
?>
