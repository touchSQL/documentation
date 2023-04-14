<?php 
// POST DATA 
if(isset($_POST["submit"])){
$name = $_POST["name"];
$lname = $_POST["lname"];
$query_c = "INSERT INTO `test`(`name`,`lname`) VALUES ('$name','$lname')";
$query = preg_replace("/ /i", "+", "INSERT INTO `test`(`name`,`lname`) VALUES ('$name','$lname')");
$url = "https://touchsql.com/api-in.php?database=mydb&api=Your_API&key=Your_Key&query=$query";
$ch = curl_init();
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_URL, $url);
$exec = curl_exec($ch);
$data = json_decode($exec, true);
echo "<pre>";
print_r($data);
echo "</pre>";

if($data["TRUE"] == "TRUE")
{
echo "Data inserted";
}
elseif($data["FALSE"] == "FALSE"){
echo "Try again";
}
}
?>
<form method="post">
    <input type="text" name="name" placeholder="FIRST NAME">
    <input type="text" name="lname" placeholder="LAST NAME">
    <input type="submit" name="submit" value="Insert">
</form>