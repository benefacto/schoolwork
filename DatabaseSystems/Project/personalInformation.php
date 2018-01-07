<?php include 'mysql_start.php'; ?>

<html>
<head>
    <title>Graduate Application: Part 2</title>
</head>
<body style="background-color:#9999CC">
    <h1>Graduate Application</h1>
    <h2>Part 2 - Personal Information</h2>
<form action="applicationInformation.php" method="POST">
    <table>
    <tr>
        <td>Full Name:</td>
    </tr>
    <tr>
        <td>First</td>
        <td><input type="text" size=50 name="first_name" required></td>
    </tr>
    <tr>
        <td>
        <!-- Populate just middle, last and n/a name options, disable textbox if n/a -->
            <?php $sql = "SELECT name_type, name_descr FROM name_type";
          $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          echo "<select name ='name_type'>\n";
          while($row = mysqli_fetch_row($result)) {
        echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
          }
          echo "</select>\n";
          } else {
        echo "0 results";
          }
        ?>
        </td>
        <td><input type="text" size=50 name="middle_name1" /></td>
        <!-- Info on adding additional fields here:
        http://www.randomsnippets.com/2008/02/21/how-to-dynamically-add-form-elements-via-javascript/
        -->
        <td><button type="button" name="add_name">+</button><!-- a button to add text fields --></td>
    </tr>
    <tr>
        <td>Last</td>
        <td><input type="text" size=50 name="last_name" required></td>
    </tr>
</table>
<p>
    Date of Birth<br>
    <input type="date" size=50 name="date_of_birth" />
</p>
<p>
    Mailing Address<br />
    <input type="text" size=40 name="address_street" placeholder="Street address" required><br>
    <input type="text" size=15 name="address_city" placeholder="City" required> <input type="text" size=8 name="address_zip" placeholder="ZIP Code" required>
    <?php $sql = "SELECT us_state_id, us_state_name FROM us_state";
      $result = mysqli_query($conn, $sql);
      if (mysqli_num_rows($result) > 0) {
      echo "<select name ='state'>\n";
      while($row = mysqli_fetch_row($result)) {
    echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
      }
      echo "</select>\n";
      } else {
        echo "0 results";
      }
    ?>
</p>
<table>
    <tr>
        <td>Preferred Phone number: </td>
        <td><input type="tel" size=20 name="phone_number" required></td>
    </tr>
</table>
<p>Gender<br>
    <?php $sql = "SELECT gender_id, gender_name FROM gender";
      $result = mysqli_query($conn, $sql);
      if (mysqli_num_rows($result) > 0) {
      echo "<select name ='gender'>\n";
      while($row = mysqli_fetch_row($result)) {
    echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
      }
      echo "</select>\n";
      } else {
        echo "0 results";
      }
    ?>
</p>
<p>Are you a US Citizen?<br>
    <label><input type="radio" name ="us_citizen" id="1">Yes</label><br>
    <label><input type="radio" name ="us_citizen" id="0">No</label>
</p>
<p>Is English your native Language?<br>
    <label><input type="radio" name ="english_native" id="1">Yes</label><br>
    <label><input type="radio" name ="english_native" id="0">No</label>
</p>
<p>
    Please tell us your veteran status<br>
    <?php $sql = "SELECT veteran_id, veteran_status FROM veteran";
      $result = mysqli_query($conn, $sql);
      if (mysqli_num_rows($result) > 0) {
      echo "<select name ='veteran_status'>\n";
      while($row = mysqli_fetch_row($result)) {
    echo "<option value='" . $row[0] . "'>" . $row[1] . "</option>\n";
      }
      echo "</select>\n";
      } else {
        echo "0 results";
      }
    ?>
</p>
<p>
    Military Branch<br>
    <?php $sql = "SELECT military_branch_id, military_branch_name FROM military_branch";
        $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          echo "<select id='military_branch'>\n";
          while($row = mysqli_fetch_row($result)) {
            echo "<option value='" . $row[0] . "'>"
            . $row[1] . "</option>\n";
          }
          echo "</select>\n";
          } else {
        echo "0 results";
          }
        ?>
</p>
<p>
    Optional: Are you of Hispanic/Latino origin?<br>
    <label><input type="radio" name ="student_type" id="1">Yes</label><br>
    <label><input type="radio" name ="student_type" id="0">No</label><br>
    <label><input type="radio" name ="student_type">Decline to answer</label>
</p>
<p>
    Optional: Your ethnicity, please check all that apply:<br>
    <!-- sql select to populate checkboxes:
    http://stackoverflow.com/questions/21368369/creating-checkboxes-from-mysql-database-then-echo-selections
    -->
<p>
<input type=submit name="send" value="Next" />
<input type=reset value="Reset" />
</form>
<hr />
</body>
</html>
