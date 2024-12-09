<?php
include 'connect.php';

function resetDatabase($pdo)
{
    // SQL statements to drop existing tables
    $dropStatements = [
        "DROP TABLE IF EXISTS user_song;",
        "DROP TABLE IF EXISTS user;",
        "DROP TABLE IF EXISTS song_contributor;",
        "DROP TABLE IF EXISTS file;",
        "DROP TABLE IF EXISTS song;",
        "DROP TABLE IF EXISTS contributor;",
    ];

    // Execute each DROP statement
    foreach ($dropStatements as $statement) {
        $pdo->exec($statement);
    }

    // Path to sql file
    $filePath = "/home/turing/z1979867/public_html/assign9/script.sql";

    // Read the SQL file
    $sql = file_get_contents($filePath);

    // Execute the SQL commands
    $pdo->exec($sql);

    echo '<div class="admin-body">';
    echo '<h2 class="success-message">Database has been reset.</h2>';
    echo '</div>';
}

// Call the function to reset the database
resetDatabase($pdo);
?>