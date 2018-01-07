<?php
$servername = "cssql.seattleu.edu";
$username = "pierced2";
$password = "EJ46NAXJ";
$dbname = "cs5021team10";
// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}
?>
