<!-- https://students.cs.niu.edu/~z2004109/ -->

<?php 
    // Error messages
    define("E_DPNR", "List display parameters not received.");
    define("E_MNNR", "Multiplication parameters not received");

    // Initial boilerplate
    echo <<<END
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="utf-8">
            <meta http-equiv="X-UA-Compatible" content="IE=edge">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Assignment 8</title>
            <link rel="stylesheet" href="styles.css">
            <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
        </head>
        <body>
    END;
?>

<?php
    // Main container
    echo <<<END
        <div class="main">
    END;
?>

<?php
    // Function to draw option tags
    function makeOpts($n) {
        for ($i = 0; $i <= $n; $i++) {
            echo "<option>$i</option>";
        }
        echo "hello";

   }

    // Function to draw the selects
    function makeSelect($for, $name, $desc, $class) {
        echo <<<END
            <label for="$for"> $desc: </label>
            <select name="$name" class="$class" id="$for"> 
        END;
        makeOpts(9); 
        echo <<<END
            </select>
        END;
    }

    // Heading
    echo "<h1 align=\"center\" style=\"color: #000000\"> CSCI 466 Assignment 8 </h1> <br/> <hr/>";


    // Main Form
    function form1() {
        echo <<<END
            <div class="d1">
            <form action="index.php" method="POST" class="f1">
                <label for="word"> </label>
                <input type="text" id="word" name="word" placeholder="Enter Word">
                <label for="count"> </label>
                <input type="text" id="count" name="count" placeholder="Enter Count">
                
                <label for="radio1"> Ordered
                <input type="radio" id="radio1" name="listtype" value="ordered">
                <label for="radio2"> Unordered
                <input type="radio" id="radio2" name="listtype" value="unordered">
        END;

        // Selects
        makeSelect("numstart", "startnumber", "Enter start", "selectopts");
        makeSelect("numsteps", "numbersteps", "Enter steps", "selectopts");
        makeSelect("numnums", "numnumbers", "# numbers", "selectopts");

        echo <<<END
            <input type="submit" id="submit_button" value="LET’S GOOOO">
            </form>
            </div>
        END;
    }

    form1();
?>

<?php
    // Functions to display error messages
    function _DE_DPNR() {
        echo "<p>" . E_DPNR . "</p>";
    }
    function _DE_MNNR() {
        echo "<p>" . E_MNNR . "</p>";
    }

    // Input validation
    function validateWord($str) {
        if (preg_match("/^\s*(\w+)\s*$/", $str)) {
          return true;
        }
        return false;
    }
    function validateCount($str) {
        if (preg_match("/^\s*((\d+),?(\d+))*\s*$/", $str)) {
          return true;
        }
        return false;
    }

?>

<?php
    function proc() {
        if ($_SERVER["REQUEST_METHOD"] == "POST") {

            // Check if the word was supplied 
            if (!array_key_exists("word", $_POST)) {
                _DE_DPNR();
                return;
            } 

            // Check if the word is valid
            if (!validateWord($_POST["word"])) {
                echo "Invalid word";
                return;
            }


            // Check if the count was supplied 
            if (!array_key_exists("count", $_POST)) {
                _DE_DPNR();
                return;
            } 

            // Check if the count is valid
            if (!validateCount($_POST["count"])) {
                echo "Invalid count";
                return;
            }

            // Check if listtype was supplied, draw the list
            if (array_key_exists("listtype", $_POST)) {
                // Get the requested list type
                $tag = ($_POST["listtype"] == "unordered" ? "ul" : "ol");
                // Draw the list
                echo "<$tag>";
                    for ($i = 0; $i<$_POST["count"]; $i++) {
                        echo "<li>". $_POST["word"] . "</li>";
                    }

                echo "</$tag>";
            // Display error
            } else {
                _DE_DPNR();
            }

            // Check if items are missing
            if ($_POST["startnumber"] == 0 || $_POST["numbersteps"] == 0 || $_POST["numnumbers"] == 0) {
                _DE_MNNR(); // Display error
                return;
            // Generate table
            } else {
                echo "<table>";
                echo "<tr>";
                // Column headings
                echo "<th></th>";
                for ($k=$_POST["startnumber"]; $k<=$_POST["startnumber"] * $_POST["numnumbers"]; $k+=$_POST["numbersteps"]) {
                    echo "<th>" . $k . "</th>";
                }
                echo "</tr>";

                // Table data
                for ($i=$_POST["startnumber"]; $i<=$_POST["startnumber"] * $_POST["numnumbers"]; $i+=$_POST["numbersteps"]) {
                    echo "<tr>";
                    // Row heading
                    echo "<th><b>" . $i . "</th></b>";
                    // Data
                    for ($j=$_POST["startnumber"]; $j<=$_POST["startnumber"] * $_POST["numnumbers"]; $j+=$_POST["numbersteps"]) {
                        echo "<td>" . $i * $j . "</td>";
                    }
                    echo "</tr>";
                }
                echo "</table>";
            }
        }
    }
    proc();
?>

<?php
    echo "</div> </body> </html>";
?>
