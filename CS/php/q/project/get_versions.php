<?php
include 'db_connect.php'; // Include your database connection setup

if (isset($_GET['title'])) {
    $title = $_GET['title'];

    // Use the correct query with the provided title
    $query = "SELECT song.song_id, song.title, file.version, file.file_id
              FROM song
              JOIN file ON song.song_id = file.song_id
              WHERE song.title = ?";
    $stmt = $pdo->prepare($query);
    $stmt->execute([$title]); // Bind the title parameter safely

    $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

    if ($results) {
        // Extract just the versions for the response
        $versions = array_column($results, 'version');
        echo json_encode($versions);
    } else {
        // No results found for the given title
        echo json_encode([]);
    }
} else {
    // Title not provided
    echo json_encode([]);
}
?>
