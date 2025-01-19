<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.2/css/all.min.css">
    <link rel="stylesheet" href="./style.css">
    <title>Project Website</title>
    <header>
        <a href="index.php" class="logo">Project Karaoke</a>
        <nav class="nav-links">
            <a href="index.php" class="active">Home</a>
            <a href="user.php">User Queue</a>
            <a href="dj.php">DJ Interface</a>
            <a href="signup.php">Sign Up</a>
            <div class="slider-bar"></div>
        </nav>
    </header>

    
    <!-- Hero Image Section -->
    <section class="hero">
        <div class="hero-content">
       
        </div>
    </section>

    <section class="home" id="home">
        <div class="home-content">
        </div>
    </section>

    <script>
        // Select all navigation links and the slider bar
        const navLinks = document.querySelectorAll('.nav-links a');
        const sliderBar = document.querySelector('.slider-bar');

        // Function to move the slider bar
        function moveSlider(link) {
            const linkRect = link.getBoundingClientRect();
            const navRect = link.parentElement.getBoundingClientRect();

            // Set the slider bar's position and size
            sliderBar.style.left = `${linkRect.left - navRect.left}px`;
            sliderBar.style.width = `${linkRect.width}px`;
        }

        // Initialize the slider on the active link (default: Home)
        const activeLink = document.querySelector('.nav-links .active');
        if (activeLink) moveSlider(activeLink);

        // Add event listeners to update the slider on click
        navLinks.forEach(link => {
            link.addEventListener('click', function () {
                // Remove active class from all links
                navLinks.forEach(nav => nav.classList.remove('active'));

                // Add active class to the clicked link
                this.classList.add('active');

                // Move the slider bar
                moveSlider(this);
            });
        });
    </script>

    <!----------------------mini player--------------------------->
<?php
// Include database connection
include('db_connect.php'); // Replace with your actual connection file

// Function to get the song with the lowest position for a given user ID
function getLowestPositionSong($pdo) {
    $stmt = $pdo->prepare("SELECT * FROM user_song ORDER BY position ASC LIMIT 1");
    $stmt->execute();
    return $stmt->fetch(PDO::FETCH_ASSOC);
}

// Get the song with the lowest position
$song = getLowestPositionSong($pdo);

if ($song) {
    $songId = $song['song_id'];

    // Query to get the song title based on song ID
    $stmt = $pdo->prepare("SELECT title FROM song WHERE song_id = :song_id");
    $stmt->execute(['song_id' => $songId]);
    $songData = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($songData) {
        $songTitle = strtolower(str_replace(' ', '_', $songData['title']));
        $audioFilePath = "./songFiles/$songTitle.mp3";
        $thumbnailPath = "./songThumbnails/$songTitle.jpg";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MiniPlayer</title>
</head>
<body>
    <?php if (isset($audioFilePath) && isset($thumbnailPath)): ?>
        <div>
            <img src="<?php echo $thumbnailPath; ?>" alt="Song Thumbnail" id="songImg" style="width: 150px;">
            <audio id="audioPlayer" controls>
                <source src="<?php echo $audioFilePath; ?>" type="audio/mp3">
                Your browser does not support the audio element.
            </audio>
            <br>
            <button id="playPauseButton" onclick="togglePlayPause()">Play</button>
            <button id="skipButton" onclick="skipSong()">Skip</button>
        </div>

        <script>
            function togglePlayPause() {
                var audioPlayer = document.getElementById('audioPlayer');
                var playPauseButton = document.getElementById('playPauseButton');

                if (audioPlayer.paused) {
                    audioPlayer.play();
                    playPauseButton.textContent = 'Pause';
                } else {
                    audioPlayer.pause();
                    playPauseButton.textContent = 'Play';
                }
            }

            function skipSong() {
                var audioPlayer = document.getElementById('audioPlayer');
                audioPlayer.currentTime = audioPlayer.duration; // Skip to the end
            }
        </script>
    <?php else: ?>
        <p>No song available to play.</p>
    <?php endif; ?>
</body>
</html>


<?php
include 'db_connect.php';

// Fetch songs from the database
$query = "SELECT song_id, artist, title FROM song";
$stmt = $pdo->query($query);
$songs = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>
    
    <section class="home">
        <div class="container">
            <h1>Available Songs</h1>
            <table>
                <thead>
                    <tr>
                        <th>Song ID</th>
                        <th>Artist</th>
                        <th>Title</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($songs as $song): ?>
                        <tr>
                            <td><?= htmlspecialchars($song['song_id']) ?></td>
                            <td><?= htmlspecialchars($song['artist']) ?></td>
                            <td><?= htmlspecialchars($song['title']) ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        </div>
    </section>

</body>
</html>

