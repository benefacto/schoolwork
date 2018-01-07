<?php include 'mysql_start.php'; ?>

<html>
<head>
    <title>Graduate Application: Part 1</title>
</head>
<body style="background-color:#9999CC">
    <h1>Graduate Application</h1>
    <h2>Part 1: New Application</h2>
<form action="personalInformation.php" method="POST">
<!-- Use select query to populate each dropdown -->
    <table>
    <tr>
        <td>What type of Student are you?</td>
        <td>
<?php $sql = "SELECT student_type_id, student_type_name FROM student_type";
  $result = mysqli_query($conn, $sql);
  if (mysqli_num_rows($result) > 0) {
  echo "<select id='student_type'>\n";
  while($row = mysqli_fetch_row($result)) {
    echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
  }
  echo "</select>\n";
  } else {
    echo "0 results";
  }
?>
        </td>
    </tr>
    <tr>
        <td>Which College are you applying to?</td>
        <td>

<?php $sql = "SELECT college_id, college_name FROM college";
  $result = mysqli_query($conn, $sql);
  if (mysqli_num_rows($result) > 0) {
  echo "<select name ='college'>\n";
  while($row = mysqli_fetch_row($result)) {
    echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
  }
  echo "</select>\n";
  } else {
    echo "0 results";
  }
?>

        </td>
    </tr>
    <tr>
        <td>What type of degree are you applying for?</td>
        <td>
        <?php $sql = "SELECT degree_type_id, degree_type_name FROM degree_type";
        $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          echo "<select id='degree_type'>\n";
          while($row = mysqli_fetch_row($result)) {
            echo "<option value='" . $row[0] . "'>"
            . $row[1] . "</option>\n";
          }
          echo "</select>\n";
          } else {
        echo "0 results";
          }
        ?>
        </td>
    </tr>
    <tr>
        <td>What Major are you applying for?</td>
        <td>
        <?php $sql = "SELECT major_id, major_name FROM major";
        $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          echo "<select id='major'>\n";
          while($row = mysqli_fetch_row($result)) {
            echo "<option value='" . $row[0] . "'>"
            . $row[1] . "</option>\n";
          }
          echo "</select>\n";
          } else {
        echo "0 results";
          }
        ?>
        </td>
    </tr>
    <tr>
        <td>Which Term do you plan to start?</td>
        <td>
        <?php $sql = "SELECT term_id, term_name FROM term";
        $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          echo "<select id='term'>\n";
          while($row = mysqli_fetch_row($result)) {
            echo "<option value='" . $row[0] . "'>"
            . $row[1] . "</option>\n";
          }
          echo "</select>\n";
          } else {
        echo "0 results";
          }
        ?>
        </td>
    </tr>
    <tr>
        <td></td>
        <td><input type=submit name="send" value="Next" />
            <input type=reset value="Reset" /></td>
    </tr>
</table>
</form>

</body>
</html>
