<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
    session_start();
    include "db_connect.php";
?>

<?php
echo <<<END
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.2/css/all.min.css">
    <link rel="stylesheet" href="style.css">
    <title>Project Website</title>
</head>
<body>
END;
?>


<?php
// Fn
//
    function arraySwap(&$a, &$b) {
        $tmp = $a;
        $a = $b;
        $b = $tmp;
    }

    function getQueue($pdo, $type) {
        if ($type == "F") {
            $query = "
                SELECT name, title, artist, version, user.user_id, song.song_id, date 
                    FROM user, song, user_song, file
                        WHERE user.user_id = user_song.user_id 
                        AND song.song_id = user_song.song_id 
                        AND file.song_id = song.song_id
                        AND queue_type=:type
                        ORDER BY date ASC ;
            ";
        } else {
            $query = "
                SELECT name, title, artist, version, user.user_id, song.song_id, payment, date 
                    FROM user, song, user_song, file
                        WHERE user.user_id = user_song.user_id 
                        AND song.song_id = user_song.song_id 
                        AND file.song_id = song.song_id
                        AND queue_type=:type
                        ORDER BY payment DESC;
            ";
        }
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":type" => $type));
        if ($success) {
            return $prepare->fetchAll(PDO::FETCH_ASSOC);
        }
    }

    function getQueueHead($pdo, $type) {
        if ($type == "F") {
            $query = "
                SELECT name, title, artist, version, user.user_id, song.song_id, date 
                    FROM user, song, user_song, file
                        WHERE user.user_id = user_song.user_id 
                        AND song.song_id = user_song.song_id 
                        AND file.song_id = song.song_id
                        AND queue_type=:type;
            ";
        } else {
             $query = "
                SELECT name, title, artist, version, user.user_id, song.song_id, payment, date 
                    FROM user, song, user_song, file
                        WHERE user.user_id = user_song.user_id 
                        AND song.song_id = user_song.song_id 
                        AND file.song_id = song.song_id
                        AND queue_type=:type
                        ORDER BY payment DESC;
            ";
        }
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":type" => $type));
        if ($success) {
            $before =  $prepare->fetchAll(PDO::FETCH_ASSOC);
            if (sizeof($before)) {
                $result = $before[0];
                $ret = array();
                foreach ($result as $key => $value) {
                    $ret[] = $key;
                }
                return $ret;
            }
        }

    }

    function bitflip(&$c) {
       return $c++ % 2; 
    }

    function popQueue($pdo, $uid, $sid, $date, $type) {
        $query = "DELETE FROM user_song WHERE user_id='$uid' AND song_id='$sid' AND date='$date' AND queue_type='$type'";
        $prepare = $pdo->prepare($query);
        $prepare->execute();
    }

    function makeQueue($pdo, $type) {
        $heads = getQueueHead($pdo, $type);
        $rows = getQueue($pdo, $type);

        if (!isset($_SESSION["c_payment"])) {
            $_SESSION["c_payment"] = 0;
        }
        if (!isset($_SESSION["c_date"])) {
            $_SESSION["c_date"] = 0;
        }

        echo "<table class='queue'>";
            echo "<tr>";
                if ($type == "F") {
                    echo "<th> <a href='dj.php?action=popFree'> Pop </a></th>";
                } else {
                    echo "<th> <a href='dj.php?action=popPaid'> Pop </a></th>";
                }
            echo "</tr>";

            echo "<tr>";
            if (!$heads) return;
            foreach($heads as $head) {
                if ($head == "payment") break;
                echo "<th> $head </th>";
            }
            if ($type == 'P') {
                echo "<th> <a href='dj.php?action=payment'> $heads[6] </a> </th>";
                echo "<th> <a href='dj.php?action=date'> $heads[7] </a> </th>";
            }
            echo "</tr>";
            
            if (isset($_GET["action"]) && $_GET["action"] == "payment" && $type == "P") {
                if (bitflip($_SESSION["c_payment"])) {
                    usort($rows, function($a, $b) {
                        if ($a["payment"] < $b["payment"]) {
                            return -1;
                        } else if ($a["payment"] > $b["payment"]) {
                            return 1;
                        } else {
                            return 0;
                        }
                    });
                } else {
                    usort($rows, function($a, $b) {
                        if ($a["payment"] > $b["payment"]) {
                            return -1;
                        } else if ($a["payment"] < $b["payment"]) {
                            return 1;
                        } else {
                            return 0;
                        }
                    });
                }
            }

            if (isset($_GET["action"]) && $_GET["action"] == "date" && $type == "P") {
                if (bitflip($_SESSION["c_date"])) {
                    usort($rows, function($a, $b) {
                        if ($a["date"] < $b["date"]) {
                            return -1;
                        } else if ($a["date"] > $b["date"]) {
                            return 1;
                        } else {
                            return 0;
                        }
                    });
                } else {
                    usort($rows, function($a, $b) {
                        if ($a["date"] > $b["date"]) {
                            return -1;
                        } else if ($a["date"] < $b["date"]) {
                            return 1;
                        } else {
                            return 0;
                        }
                    });
                }
            }

            if (isset($_GET["action"]) && $_GET["action"] == "popFree" && $type=="F") {
                if (sizeof($rows)) {
                    $uid_front = $rows[0]["user_id"];
                    $sid_front = $rows[0]["song_id"];
                    $date_front = $rows[0]["date"];
                    popQueue($pdo, $uid_front, $sid_front, $date_front, "F");
                }
            }

            if (isset($_GET["action"]) && $_GET["action"] == "popPaid" && $type=="P") {
                if (sizeof($rows)) {
                    $uid_front = $rows[0]["user_id"];
                    $sid_front = $rows[0]["song_id"];
                    $date_front = $rows[0]["date"];

                    popQueue($pdo, $uid_front, $sid_front, $date_front, "P");
                }
            }

            if (!$rows) return;
            foreach ($rows as $row) {
                echo "<tr>";
                foreach ($row as $key => $item) {
                    if ($key == "payment") {
                        echo "<td> \$$item </td>";
                    } else {
                        echo "<td> $item </td>";
                    }
                }
                echo "</tr>";
            }
        echo "</table>";
    }

?>

<?php
    echo <<<END
    <header>
        <a href="index.php" class="logo">Project Karaoke</a>
        <nav>
            <div class="nav-links">
            <a href="index.php">Home</a>
            <a href="user.php">User Queue</a>
            <a href="dj.php" class="active">DJ Interface</a>
            <a href="signup.php">Sign Up</a>
            <div class="slider-bar"></div>
            </div>
        </nav>
    </header>
    <section class="home">
        <div class="home-img">
        </div>
        <div class="home-content">
            <h1>This is where the dj cooks</span></h1>
        </div>
    </section>
    END;

    echo "<div class='dj1'>";

        echo "<div class='freeq-contain'>";
            echo "<h1> Free Queue </h1>";

            echo "<div class='freeq'>";
                makeQueue($pdo, "F");
            echo "</div>";   

        // freeq-contain
        echo "</div>";   

        echo "<div class='paidq-contain'>";
            echo "<h1> Paid Queue </h1>";

            echo "<div class='paidq'>";
                makeQueue($pdo, "P");
            echo "</div>";   


        echo "</div>";

    echo "</div>";

?>

<?php
    echo "</body> </html>";
?>

