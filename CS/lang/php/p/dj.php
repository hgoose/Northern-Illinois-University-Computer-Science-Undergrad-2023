<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
    include "dbconnect.php";
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

    function getQueue($pdo, $type) {
        $query = "
            SELECT name, title, artist, user.user_id, song.song_id, date 
                FROM user, song, user_song 
                    WHERE user.user_id = user_song.user_id 
                    AND song.song_id = user_song.song_id AND queue_type=:type;
        ";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":type" => $type));
        if ($success) {
            return $prepare->fetchAll(PDO::FETCH_ASSOC);
        }
    }

    function getQueueHead($pdo, $type) {
        $query = "
            SELECT name, title, artist, user.user_id, song.song_id, date 
                FROM user, song, user_song 
                    WHERE user.user_id = user_song.user_id 
                    AND song.song_id = user_song.song_id AND queue_type=:type;
        ";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute(array(":type" => $type));
        if ($success) {
            return $prepare->fetchAll(PDO::FETCH_ASSOC)[0];
        }

    }

    function makeFreeQueue($pdo) {

        $heads = getQueueHead($pdo, 'F');

        echo "<table class='queue'>";
            echo "<tr>";
            foreach($heads as $head) {
                echo "<th> $head </th>";
            }
            echo "</tr>";
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
                                makeFreeQueue($pdo);


            echo "</div>";   

        // freeq-contain
        echo "</div>";   

        echo "<div class='paidq-contain'>";
            echo "<h1> Paid Queue </h1>";

            echo "<div class='paidq'>";

            echo "</div>";   


        echo "</div>";

    echo "</div>";

?>

<?php
    echo "</body> </html>";
?>

