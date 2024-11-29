
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.2/css/all.min.css">
    <link rel="stylesheet" href="./style.css">
    <title>Sign Up - Project Karaoke</title>
</head>
<body>
    <header>
        <a href="index.php" class="logo">Project Karaoke</a>
        <nav class="nav-links">
            <a href="index.php">Home</a>
            <a href="user.php">User Queue</a>
            <a href="dj.php">DJ Interface</a>
            <a href="signup.php" class="active">Sign Up</a>
            <div class="slider-bar"></div>
        </nav>
    </header>
    
    
   
    <!-- Sign Up Section -->
    <section class="sign-up">
        <div class="container">
            <h2>Enter your social security number</h2>
            
            <!-- Sign Up Form -->
            <form action="" method="POST" class="signup-form">
                <label for="username"></label>
                <input type="text" id="username" name="username" placeholder="xxx-xx-xxxx" required>

                <button type="submit" class="submit-btn">Submit</button>
            </form>
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
</body>
</html>

<!---------------------------------------------------------------------------------------------------------------->



