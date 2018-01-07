<?php include 'mysql_start.php'; ?>
<html>
<head>
    <title>Graduate Application: Part 4</title>
</head>
<body style="background-color:#9999CC">
    <h1>Graduate Application</h1>
    <h2>Part 4 - Confirmation Page / View Application</h2>
<form action="confirm.php" method="POST">
    <table>
    <tr>
        <td>Full Name:</td>
    </tr>
    <tr>
        <td>First</td>
    </tr>
    <tr>
        <td>
            <?php $sql = "SELECT name_value, name_descr FROM applicant_name, name_type
				WHERE name_type_id = "/*PUT first name NAME_TYPE_ID HERE*/ . "applicant_id = "/*PUT this APPLICANT_ID HERE*/;
          $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row[0] . $row[1] <br>;
          }
          else {
        echo "0 results";
          }
        ?>
        </td>
        <td>
		    <?php $sql = "SELECT name_value, name_descr FROM applicant_name, name_type
				WHERE name_type_id = "/*PUT middle name NAME_TYPE_ID HERE*/ . "applicant_id = "/*PUT this APPLICANT_ID HERE*/;
          $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row[0] . $row[1] <br>;
          }
          else {
        echo "0 results";
          }
        ?>
		</td>
        <td>
    </tr>
    <tr>
        <td>Last</td>
        <td>
		    <?php $sql = "SELECT name_value, name_descr FROM applicant_name, name_type
				WHERE name_type_id = "/*PUT last name NAME_TYPE_ID HERE*/ . "applicant_id = "/*PUT this APPLICANT_ID HERE*/;
          $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row[0] . $row[1] . <br>;
          }
          else {
        echo "0 results";
          }
        ?>
		</td>
        <td>
    </tr>
</table>
<p>
    Date of Birth<br>
	<?php $sql = "SELECT date_of_birth FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
		$result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
        ?>
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
        <td>
		<?php $sql = "SELECT phone_number FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
		$result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
        ?>
		</td>
    </tr>
</table>
<p>Gender<br>
    <?php $sql = "SELECT gender_name FROM applicant, gender
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
        ?>
</p>
<p>Are you a US Citizen?<br>
    <?php $sql = "SELECT us_citizen FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
</p>
<p>Is English your native Language?<br>
    <?php $sql = "SELECT us_citizen FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
</p>
<p>
    Please tell us your veteran status<br>
    <?php $sql = "SELECT veteran_status FROM applicant, veteran
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
</p>
<p>
    Military Branch<br>
    <?php $sql = "SELECT military_branch_name FROM applicant, military_branch
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
</p>
<p>
    Optional: Are you of Hispanic/Latino origin?<br>
    <?php $sql = "SELECT hispanic FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
</p>
<p>
    Optional: Your ethnicity, please check all that apply:<br>
    <?php $sql = "SELECT ethnicity_name FROM applicant_ethnicity, ethnicity
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
<table>
<tr>
    <td>Will you be applying for financial aid?</td>
	<td>
    <?php $sql = "SELECT financial_aid FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
	</td>
</tr>
<tr>
    <td>Do you have employer tuition assistance?</td>
	<td>
    <?php $sql = "SELECT financial_aid FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
	</td>
</tr>
<tr>
    <td>Are you also applying to other programs?</td>
	<td>
    <?php $sql = "SELECT apply_other FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
	</td>
</tr>
<tr>
    <td>Have you ever been convicted of a felony or a gross misdemeanor?</td>
	<td>
    <?php $sql = "SELECT convicted FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
	</td>
</tr>
</table>
<p>
A conviction will not necessarily bar admission but will require additional documentation prior to a decision.
You will be contacted shortly via email with instructions on reporting the nature of your conviction.
Have you ever been placed on probation, suspended from, dismissed from or otherwise sanctioned by (for any period of time) any higher education institution?
<br />
    <td>Have you ever been convicted of a felony or a gross misdemeanor?</td>
	<td>
    <?php $sql = "SELECT probation FROM applicant
		WHERE applicant_id = "/*PUT this APPLICANT_ID HERE*/;
      $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
          while($row = mysqli_fetch_row($result)) {
        echo $row;
          }
          else {
        echo "0 results";
          }
    ?>
	</td>
</p>
</form>
<hr />
</body>
</html>