<?php include 'mysql_start.php'; ?>

<html>
<head>
    <title>Graduate Application: Part 3</title>
</head>
<body style="background-color:#9999CC">
    <h1>Graduate Application</h1>
    <h2>Part 3 - Application Information</h2>
<form action="procpostform.php" method="POST">
<table>
<tr>
    <td>Will you be applying for financial aid?</td>
    <td><label><input type="radio" name="financial_aid" id="1">Yes</label></td>
    <td><label><input type="radio" name="financial_aid" id="0">No</label></td>
</tr>
<tr>
    <td>Do you have employer tuition assistance?</td>
    <td><label><input type="radio" name="tuition_assist" id="1">Yes</label></td>
    <td><label><input type="radio" name="tuition_assist" id="0">No</label></td>
</tr>
<tr>
    <td>Are you also applying to other programs?</td>
    <td><label><input type="radio" name="apply_other" id="1">Yes</label></td>
    <td><label><input type="radio" name="apply_other" id="0">No</label></td>
</tr>
<tr>
    <td>Have you ever been convicted of a felony or a gross misdemeanor?</td>
    <td><label><input type="radio" name ="applicant_convicted" id="1">Yes</label><br></td>
    <td><label><input type="radio" name ="applicant_convicted" id="0">No</label><br></td>
</tr>
</table>
<p>
A conviction will not necessarily bar admission but will require additional documentation prior to a decision.
You will be contacted shortly via email with instructions on reporting the nature of your conviction.
Have you ever been placed on probation, suspended from, dismissed from or otherwise sanctioned by (for any period of time) any higher education institution?
<br />
<td><label><input type="radio" name ="applicant_probation" id="1">Yes</label><br></td>
<td><label><input type="radio" name ="applicant_probation" id="0">No</label><br></td>
</p>
<input type=submit name="send" value="submit" />
<input type=reset value="clear" />
</form>

</body>
</html>
